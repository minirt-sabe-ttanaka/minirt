/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 09:23:16 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/19 21:44:52 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <float.h>

/* コンストラクタ */
t_vec3 vec3_create(double x, double y, double z) {
    t_vec3 v;
    v.x = x; v.y = y; v.z = z;
    return v;
}
t_vec3 vec3_zero(void) {
    return vec3_create(0.0, 0.0, 0.0);
}

/* 四則演算 */
t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
    return vec3_create(a.x + b.x, a.y + b.y, a.z + b.z);
}
t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
    return vec3_create(a.x - b.x, a.y - b.y, a.z - b.z);
}
t_vec3 vec3_mul_v(t_vec3 a, t_vec3 b) {
    return vec3_create(a.x * b.x, a.y * b.y, a.z * b.z);
}
t_vec3 vec3_mul_s(t_vec3 v, double s) {
    return vec3_create(v.x * s, v.y * s, v.z * s);
}
t_vec3 vec3_div_s(t_vec3 v, double s) {
    double inv = 1.0 / s;
    return vec3_create(v.x * inv, v.y * inv, v.z * inv);
}
t_vec3 vec3_neg(t_vec3 v) {
    return vec3_create(-v.x, -v.y, -v.z);
}

/* 内積・外積 */
double vec3_dot(t_vec3 a, t_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
    return vec3_create(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

/* 長さ・距離 */
double vec3_length2(t_vec3 v) {
    return vec3_dot(v, v);
}
double vec3_length(t_vec3 v) {
    return sqrt(vec3_length2(v));
}
double vec3_distance(t_vec3 a, t_vec3 b) {
    return vec3_length(vec3_sub(a, b));
}

/* 正規化（長さ0ならゼロベクトル） */
t_vec3 unit_vector(t_vec3 v) {
    double len2 = vec3_length2(v);
    if (len2 <= DBL_EPSILON) return vec3_zero();
    return vec3_div_s(v, sqrt(len2));
}

/* 近似ゼロ判定（デフォルト閾値は 1e-8） */
bool vec3_near_zero(t_vec3 v) {
    const double s = 1e-8;
    return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s);
}

/* 反射: r = v - 2*(v·n)*n  (n は法線) */
t_vec3 vec3_reflect(t_vec3 v, t_vec3 n) {
    double d = vec3_dot(v, n);
    return vec3_sub(v, vec3_mul_s(n, 2.0 * d));
}

/* 屈折 (Snell)
   v: 入射ベクトル（正規化されている前提が望ましい）
   n: 法線（正規化されている前提が望ましい）
   eta_ratio = eta_in / eta_out
   全反射時はゼロベクトルを返す */
t_vec3 vec3_refract(t_vec3 v, t_vec3 n, double eta_ratio) {
    /* cos_theta = min(dot(-v, n), 1.0) */
    t_vec3 neg_v = vec3_neg(v);
    double cos_theta = vec3_dot(neg_v, n);
    if (cos_theta > 1.0) cos_theta = 1.0;
    if (cos_theta < -1.0) cos_theta = -1.0;

    /* r_out_perp = eta_ratio * (v + cos_theta * n) */
    t_vec3 tmp = vec3_add(v, vec3_mul_s(n, cos_theta));
    t_vec3 r_out_perp = vec3_mul_s(tmp, eta_ratio);

    double k = 1.0 - vec3_length2(r_out_perp);
    if (k < 0.0) {
        /* 全反射 */
        return vec3_zero();
    }
    t_vec3 r_out_parallel = vec3_mul_s(n, -sqrt(k));
    return vec3_add(r_out_perp, r_out_parallel);
}

/* 線形補間 */
t_vec3 vec3_lerp(t_vec3 a, t_vec3 b, double t) {
    return vec3_add(vec3_mul_s(a, 1.0 - t), vec3_mul_s(b, t));
}

/* 要素ごとの min/max/clamp */
t_vec3 vec3_min(t_vec3 a, t_vec3 b) {
    return vec3_create(
        fmin(a.x, b.x),
        fmin(a.y, b.y),
        fmin(a.z, b.z)
    );
}
t_vec3 vec3_max(t_vec3 a, t_vec3 b) {
    return vec3_create(
        fmax(a.x, b.x),
        fmax(a.y, b.y),
        fmax(a.z, b.z)
    );
}
t_vec3 vec3_clamp(t_vec3 v, double lo, double hi) {
    double cx = fmin(fmax(v.x, lo), hi);
    double cy = fmin(fmax(v.y, lo), hi);
    double cz = fmin(fmax(v.z, lo), hi);
    return vec3_create(cx, cy, cz);
}

t_vec3 ray_at(const t_ray r, double t) {
    return vec3_add(r.origin, vec3_mul_s(r.dir, t));
}

t_vec3 vec3_random(double min, double max) {
    return vec3_create(
        rand_double(min, max),
        rand_double(min, max),
        rand_double(min, max)
    );
}

t_vec3 vec3_random_in_unit_sphere(void) {
    while (true) {
        t_vec3 p = vec3_random(-1.0, 1.0);
        if (vec3_length2(p) >= 1.0) continue;
        return p;
    }
}

t_vec3 vec3_sqrt(t_vec3 v) {
    return vec3_create(
        sqrt(v.x),
        sqrt(v.y),
        sqrt(v.z)
    );
}