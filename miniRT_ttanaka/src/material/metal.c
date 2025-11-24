#include "material.h"

bool		metal_scatter(const void *object, t_scatter_ctx *ctx);
t_material	create_metal(t_metal *metal, t_color3 albedo, double fuzz);

bool	metal_scatter(const void *object, t_scatter_ctx *ctx)
{
	const t_metal	*mat = (const t_metal *)object;
	t_vec3			reflected_dir;
	t_vec3			fuzzed_dir;

	reflected_dir = vec_reflect(vec_normalize(ctx->r_in->dir),
			ctx->rec->normal);
	fuzzed_dir = vec_add(reflected_dir,
			vec_scale(random_in_unit_sphere(ctx->seed), mat->fuzz));
	ctx->scattered = ray_init(ctx->rec->p, fuzzed_dir);
	ctx->attenuation = mat->albedo;
	return (vec_dot(ctx->scattered.dir, ctx->rec->normal) > 0);
}

t_material	create_metal(t_metal *metal, t_color3 albedo, double fuzz)
{
	static const t_material_vtable	metal_vtable = {metal_scatter,
			material_default_emitted, destroy_default_material };
	t_material						m;

	metal->albedo = albedo;
	metal->fuzz = fmin(fuzz, 1);
	m.object = metal;
	m.vtable = &metal_vtable;
	return (m);
}
