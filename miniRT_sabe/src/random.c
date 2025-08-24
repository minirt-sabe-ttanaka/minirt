/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:14:55 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/19 22:14:57 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* random.c
 * 高品質・グローバル変数なし・APIそのまま実装
 */
#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#if defined(__linux__)
# include <sys/random.h> /* getrandom */
#endif

/* Park–Miller modulus for compatibility with your existing code expectations */
#define PM_M 2147483647U /* 2^31 - 1 */
#define PM_M_MINUS1 (PM_M - 1ULL)

/* Try getrandom() (Linux). Return 0 on success, -1 on failure. */
static int try_getrandom_bytes(void *buf, size_t len) {
#if defined(__linux__)
    size_t off = 0;
    while (off < len) {
        ssize_t r = getrandom((char *)buf + off, len - off, 0);
        if (r < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        off += (size_t)r;
    }
    return 0;
#else
    (void)buf; (void)len;
    return -1;
#endif
}

/* Try /dev/urandom. Return 0 on success, -1 on failure. */
static int try_dev_urandom_bytes(void *buf, size_t len) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) return -1;
    unsigned char *p = (unsigned char *)buf;
    size_t off = 0;
    while (off < len) {
        ssize_t r = read(fd, p + off, len - off);
        if (r < 0) {
            if (errno == EINTR) continue;
            close(fd);
            return -1;
        }
        if (r == 0) { close(fd); return -1; }
        off += (size_t)r;
    }
    close(fd);
    return 0;
}

/* fallback entropy: mix time, pid, stack address into a 64-bit value */
static uint64_t fallback_entropy_u64(void) {
    struct timeval tv;
    (void)gettimeofday(&tv, NULL);
    uint64_t mix = ((uint64_t)tv.tv_sec << 32) ^ (uint64_t)tv.tv_usec;
    mix ^= (uint64_t)(uintptr_t)&mix;
    mix ^= ((uint64_t)getpid() << 16);
    /* small scramble (splitmix-like) */
    mix += 0x9e3779b97f4a7c15ULL;
    mix = (mix ^ (mix >> 30)) * 0xbf58476d1ce4e5b9ULL;
    mix = (mix ^ (mix >> 27)) * 0x94d049bb133111ebULL;
    mix = mix ^ (mix >> 31);
    return mix;
}

/* Fill a uint64_t with secure/random bytes using best available source.
   Returns 0 on success, -1 only if fallback used (still fills out). */
static int get_secure_u64(uint64_t *out) {
    if (!out) return -1;
    /* try getrandom */
    if (try_getrandom_bytes(out, sizeof(*out)) == 0) return 0;
    /* try /dev/urandom */
    if (try_dev_urandom_bytes(out, sizeof(*out)) == 0) return 0;
    /* fallback */
    *out = fallback_entropy_u64();
    return -1;
}

/* rand_seed: keep signature. Return an int32 seed (>=1). */
int32_t rand_seed(void)
{
    uint64_t v;
    (void)get_secure_u64(&v);
    int32_t s = (int32_t)(v % PM_M);
    if (s <= 0) s = 1;
    return s;
}

/* rand_int: return uniform int in 1 .. PM_M-1 (inclusive),
   using rejection sampling on 64-bit random values to avoid bias. */
int32_t rand_int(void)
{
    uint64_t bound = PM_M_MINUS1; /* we want 1..PM_M-1, so mod by PM_M-1 then +1 */
    if (bound == 0) return 1;
    /* compute threshold to avoid bias: largest multiple of bound <= UINT64_MAX */
    const uint64_t limit = UINT64_MAX - (UINT64_MAX % bound);
    while (1) {
        uint64_t r;
        get_secure_u64(&r); /* always returns something (fallback if needed) */
        if (r >= limit) continue; /* reject to avoid bias */
        uint64_t v = (r % bound) + 1ULL; /* now 1..bound */
        return (int32_t)v;
    }
}

/* rand_double(min, max): returns double in [min, max) with 53-bit precision */
double rand_double(double min, double max)
{
    if (!(min < max)) return min;
    uint64_t r;
    get_secure_u64(&r);
    /* take top 53 bits */
    const uint64_t r53 = r >> (64 - 53); /* 0 .. 2^53-1 */
    double u = (double)r53 / (double)(1ULL << 53); /* 0 <= u < 1 */
    return min + (max - min) * u;
}
