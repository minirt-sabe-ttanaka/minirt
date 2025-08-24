/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesouichirou <abesouichirou@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:45:47 by abesouichir       #+#    #+#             */
/*   Updated: 2025/08/22 14:56:18 by abesouichir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <libft.h>
# include <float.h>
# include "mlx.h"
#include <sys/time.h>

/*
 * 基本ベクトル / 点 / 色 / レイ / 画像構造体
 * - 必要最小限のメンバだけ定義しています。演算関数は .c 側で実装してください。
 */

/* 3要素ベクトル */
typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}               t_vec3;

/* 点と色はベクタの別名 */
typedef t_vec3  t_point3;
typedef t_vec3  t_color3;

/* レイ (原点 + 方向) */
typedef struct s_ray
{
    t_point3    origin;
    t_vec3      dir;
}               t_ray;

/* 画像情報（MLX用） */
typedef struct s_img
{
    void    *img;           /* mlx image pointer */
    char    *addr;          /* pixel buffer addr */
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;          /* optional: 画像幅 */
    int     height;         /* optional: 画像高さ */
}               t_img;

/* 既存ユーザ定義の world 構造体は残す（必要なら拡張可） */
typedef struct s_world
{
    void    *mlx;
    void    *win;
    t_img   img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     screen_width;
    int     screen_height;
}               t_world;

/* 前方宣言（相互参照用） */
struct s_hit_record;

/* マテリアル vtable */
typedef struct s_material_vtable
{
    bool    (*scatter)(const void *object, const t_ray *r_in,
                       const struct s_hit_record *rec,
                       t_color3 *attenuation, t_ray *scattered);
}               t_material_vtable;

/* マテリアル wrapper */
typedef struct s_material
{
    const void                  *object; /* 実際のマテリアル実体へのポインタ */
    const t_material_vtable     *vtable;
}               t_material;

typedef struct s_lambertian {
    t_color3 albedo;
} t_lambertian;

typedef struct s_metal {
    t_color3 albedo;
    double fuzz; /* 金属の粗さ（0.0 以上 1.0 以下） */
} t_metal;

typedef struct s_dielectric {
    t_color3 albedo; /* 屈折率に関係なく、色を持つ */
    double ref_idx;
} t_dielectric;

/* ヒットレコード（衝突情報） */
typedef struct s_hit_record
{
    t_point3    p;
    t_vec3      normal;
    t_material  mat;
    double      t;
    bool        front_face;
}               t_hit_record;

/* ヒッタブル vtable */
typedef struct s_hittable_vtable
{
    bool    (*hit)(const void *object, const t_ray *r,
                   double t_min, double t_max, t_hit_record *rec);
}               t_hittable_vtable;

/* ヒッタブル wrapper */
typedef struct s_hittable
{
    const void                  *object; /* 実体へのポインタ（sphere 等） */
    const t_hittable_vtable     *vtable;
}               t_hittable;

/* ヒッタブル配列（単純実装） */
typedef struct s_hittable_lst
{
    t_hittable  *objects;
    int         size;
    int         capacity;
}               t_hittable_lst;

typedef struct s_sphere {
    t_vec3 center;
    double radius;
    t_material mat; /* マテリアル情報を持つ */
} t_sphere;

typedef struct s_camera {
    t_point3 origin;
    t_vec3 horizontal;
    t_vec3 vertical;
    t_vec3 lower_left_corner;
}               t_camera;

/* ユーティリティ / I/O のプロトタイプ（必要なら追加） */
void    my_mlx_pixel_put(t_img *data, int x, int y, int color);

// vector関連
/* コンストラクタ風 */
t_vec3 vec3_create(double x, double y, double z);
t_vec3 vec3_zero(void);

/* 四則演算 */
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul_v(t_vec3 a, t_vec3 b); /* 要素ごとの乗算 (Hadamard) */
t_vec3 vec3_mul_s(t_vec3 v, double s);
t_vec3 vec3_div_s(t_vec3 v, double s); /* s == 0 の場合の挙動は呼び出し側で避ける */
t_vec3 vec3_neg(t_vec3 v);

/* 内積・外積 */
double  vec3_dot(t_vec3 a, t_vec3 b);
t_vec3  vec3_cross(t_vec3 a, t_vec3 b);

/* 長さ・距離 */
double vec3_length2(t_vec3 v); /* ノルムの二乗 */
double vec3_length(t_vec3 v);
double vec3_distance(t_vec3 a, t_vec3 b);

/* 正規化 */
t_vec3 unit_vector(t_vec3 v); /* 長さ0に対してはゼロベクトルを返す */

/* その他ユーティリティ */
bool    vec3_near_zero(t_vec3 v); /* 要素が小さいかの判定 */
t_vec3  vec3_reflect(t_vec3 v, t_vec3 n); /* v: 入射（方向）、n: 法線（正規化想定） */
/* 屈折: v: 入射（正規化想定）, n: 法線（正規化想定）, eta_ratio = eta_in / eta_out
   全反射の場合はゼロベクトルを返す */
t_vec3  vec3_refract(t_vec3 v, t_vec3 n, double eta_ratio);

/* 線形補間 */
t_vec3 vec3_lerp(t_vec3 a, t_vec3 b, double t);

/* 要素ごとの min/max/clamp */
t_vec3 vec3_min(t_vec3 a, t_vec3 b);
t_vec3 vec3_max(t_vec3 a, t_vec3 b);
t_vec3 vec3_clamp(t_vec3 v, double lo, double hi);
t_vec3 vec3_random(double min, double max);
t_vec3 vec3_random_in_unit_sphere(void);

// オブジェクト
t_vec3 ray_at(const t_ray r, double t);
void hittable_lst_init(t_hittable_lst *lst);
int hittable_lst_push(t_hittable_lst *lst, const void *object, const t_hittable_vtable *vtable);
bool hit_sphere(const void *object, const t_ray *r, double t_min, double t_max, t_hit_record *rec);
bool hit_hittable_lst(const t_hittable_lst *lst, const t_ray *r, double t_min, double t_max, t_hit_record *rec);
int hittable_lst_push(t_hittable_lst *lst, const void *object, const t_hittable_vtable *vtable);
void set_face_normal(t_hit_record *rec, const t_ray *r, const t_vec3 outward_normal);
int32_t rand_int(void);
double rand_double(double min, double max);
t_camera camera_create(t_point3 origin, t_vec3 horizontal, t_vec3 vertical, t_vec3 lower_left_corner);
t_ray camera_get_ray(const t_camera *cam, double u, double v);
t_vec3 vec3_sqrt(t_vec3 v);
t_material *lambertian_new(t_color3 albedo);
void sphere_create(t_hittable_lst *lst, t_vec3 center, double radius, t_material mat);
t_material *metal_new(t_color3 albedo, double fuzz);
double degrees_to_radians(double degrees);
t_vec3 refract(t_vec3 v, t_vec3 n, double eta_ratio);
t_material *dielectric_new(t_color3 albedo, double ref_idx);
double schlick(double cos_theta, double eta_ratio);

#endif /* MINIRT_H */
