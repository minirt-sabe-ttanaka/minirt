/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:23 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 15:13:57 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "core/ray.h"
# include "core/utils.h"
# include "engine/pdf.h"
# include "rt_struct.h"

# define SHADOW_BIAS 1e-2

typedef struct s_scatter_ctx
{
	const t_ray				*r_in;
	const t_hit_record		*rec;
	unsigned int			*seed;
}							t_scatter_ctx;

typedef struct s_scatter_record
{
	t_ray					specular_ray;
	bool					is_specular;
	t_color3				attenuation;
	t_pdf					*pdf_ptr;
}							t_scatter_record;

typedef struct s_material_vtable
{
	bool					(*scatter)(const void *object,
							const t_scatter_ctx *in, t_scatter_record *out);
	double					(*scattering_pdf)(const void *obj,
							const t_ray *r_in, const t_hit_record *rec,
							const t_ray *scattered);
	t_color3				(*emitted)(const void *object, double u, double v,
						const t_point3 *p);
	void					(*destroy)(void **object_ptr);
}							t_material_vtable;

typedef enum e_material_type
{
	lambertian,
	metal,
	dielectric,
	diffuse_light,
	other
}							t_material_type;

typedef struct s_material
{
	const void				*object;
	const t_material_vtable	*vtable;
}							t_material;

typedef struct s_hit_record
{
	t_point3				p;
	t_vec3					normal;
	t_material				mat;
	double					t;
	bool					front_face;
}							t_hit_record;

typedef struct s_lambertian
{
	t_color3				albedo;
}							t_lambertian;

typedef struct s_metal
{
	t_color3				albedo;
	double					fuzz;
}							t_metal;

typedef struct s_dielectric
{
	double					ref_idx;
}							t_dielectric;

typedef struct s_diffuse_light
{
	t_color3				emit_color;
}							t_diffuse_light;

typedef struct s_material_config
{
	t_color3				color;
	double					parameter;
	t_material_type			type;
}							t_material_config;

void						set_face_normal(t_hit_record *rec, const t_ray *r,
								const t_vec3 *outward_normal);

t_color3					material_default_emitted(const void *object,
								double u, double v, const t_point3 *p);
double						dummy_scattering_pdf(const void *obj,
								const t_ray *r_in, const t_hit_record *rec,
								const t_ray *scattered);

void						destroy_default_material(void **object_ptr);

bool						lambertian_scatter(const void *object,
								const t_scatter_ctx *in, t_scatter_record *out);
double						lambertian_scattering_pdf(const void *obj,
								const t_ray *r_in, const t_hit_record *rec,
								const t_ray *scattered);
t_material					create_lambertian(t_lambertian *l, t_color3 albedo);

bool						metal_scatter(const void *object,
								const t_scatter_ctx *in, t_scatter_record *out);
t_material					create_metal(t_metal *metal, t_color3 albedo,
								double fuzz);

bool						dielectric_scatter(const void *object,
								const t_scatter_ctx *in, t_scatter_record *out);
t_material					create_dielectric(t_dielectric *d, double ref_idx);

bool						diffuse_light_scatter(const void *object,
								const t_scatter_ctx *in, t_scatter_record *out);
t_color3					diffuse_light_emitted(const void *object, double u,
								double v, const t_point3 *p);
t_material					create_diffuse_light(t_diffuse_light *l,
								t_color3 emit_color);

#endif