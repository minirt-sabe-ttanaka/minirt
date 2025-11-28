/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:21:14 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/28 23:40:16 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine/raytracing.h"

void			display_progress_bar(int current, int total);
t_color3		calc_direct_light(t_scene *scene, t_hit_record *rec,
					t_color3 albedo);
t_color3		ray_color(const t_ray *r, t_scene *scene, int depth,
					unsigned int *seed);
t_color3		sampling_ray(t_scene *scene, t_camera *cam, int x, int y,
					unsigned int *seed);
void			get_gbuffer_info(t_scene *scene, t_camera *cam, int x, int y,
					t_pixel_data *data);

void	display_progress_bar(int current, int total)
{
	double	percent;
	int		filled_len;
	int		i;

	if (total == 0)
		return ;
	percent = (double)current / total;
	filled_len = (int)(BAR_WIDTH * percent);
	write(STDOUT_FILENO, "\r", 1);
	write(STDOUT_FILENO, "[", 1);
	i = -1;
	while (++i < BAR_WIDTH)
	{
		if (i < filled_len)
			write(STDOUT_FILENO, "=", 1);
		else if (i == filled_len)
			write(STDOUT_FILENO, ">", 1);
		else
			write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, "] ", 2);
	ft_putnbr_fd((int)(percent * 100.0), STDOUT_FILENO);
	write(STDOUT_FILENO, "%", 1);
	if (current == total)
		write(STDOUT_FILENO, "\n", 1);
}

t_color3	calc_direct_light(t_scene *scene, t_hit_record *rec,
		t_color3 albedo)
{
	t_vec3			light_dir;
	double			dist;
	double			cos_theta;
	t_ray			shadow_ray;
	t_hit_record	tmp_rec;

	light_dir = vec_sub(scene->light.origin, rec->p);
	dist = vec_norm(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray = ray_init(vec_add(rec->p, vec_scale(rec->normal, SHADOW_BIAS)),
			light_dir);
	if (scene->bvh && scene->bvh->vtable->hit(scene->bvh->object, &shadow_ray,
			(t_double_range){SHADOW_BIAS, dist - SHADOW_BIAS}, &tmp_rec))
		return (color_init(0, 0, 0));
	cos_theta = vec_dot(rec->normal, light_dir);
	if (cos_theta < 0)
		return (color_init(0, 0, 0));
	return (vec_scale(vec_mult(albedo, vec_scale(scene->light.color,
					scene->light.ratio)), cos_theta));
}

static void	free_pdfs(t_pdf *p1, t_pdf *p2, t_pdf *mix)
{
	if (p1)
	{
		free(p1->data);
		free(p1);
	}
	if (p2)
	{
		free(p2->data);
		free(p2);
	}
	if (mix)
	{
		free(mix->data);
		free(mix);
	}
}

static t_color3	calc_diffuse(t_scene *scene, t_scatter_record *srec,
		t_scatter_ctx *ctx, int depth)
{
	t_pdf			*light_pdf;
	t_pdf			*active_pdf;
	t_ray			scattered;
	t_color3		color;
	double			pdf_val;
	t_hittable_lst	*lights_lst;

	lights_lst = (t_hittable_lst *)scene->light_group.object;
	if (lights_lst->size > 0)
	{
		light_pdf = create_hittable_pdf(&scene->light_group, ctx->rec->p);
		active_pdf = create_mixture_pdf(light_pdf, srec->pdf_ptr);
	}
	else
	{
		light_pdf = NULL;
		active_pdf = srec->pdf_ptr;
	}
	scattered = ray_init(ctx->rec->p,
			active_pdf->vtable->generate(active_pdf->data, ctx->seed));
	pdf_val = active_pdf->vtable->value(active_pdf->data, &scattered.dir);
	if (pdf_val == 0)
	{
		if (light_pdf)
			free_pdfs(light_pdf, srec->pdf_ptr, active_pdf);
		else
			free_pdfs(light_pdf, srec->pdf_ptr, NULL);
		return (color_init(0, 0, 0));
	}
	color = vec_mult(srec->attenuation, ray_color(&scattered, scene, depth - 1,
				ctx->seed));
	color = vec_scale(color,
			ctx->rec->mat.vtable->scattering_pdf(ctx->rec->mat.object,
				ctx->r_in, ctx->rec, &scattered) / pdf_val);
	if (light_pdf)
		free_pdfs(light_pdf, srec->pdf_ptr, active_pdf);
	else
		free_pdfs(light_pdf, srec->pdf_ptr, NULL);
	return (color);
}

t_color3	ray_color(const t_ray *r, t_scene *scene, int depth,
		unsigned int *seed)
{
	t_hit_record		rec;
	t_scatter_record	srec;
	t_scatter_ctx		ctx;
	t_color3			color;

	if (depth <= 0)
		return (vec_scale(scene->ambient.color, scene->ambient.ratio));
	if (!scene->bvh || !scene->bvh->vtable->hit(scene->bvh->object, r,
			(t_double_range){0.001, INFINITY}, &rec))
		return (vec_scale(scene->ambient.color, scene->ambient.ratio));
	color = rec.mat.vtable->emitted(rec.mat.object, 0, 0, &rec.p);
	ctx.r_in = r;
	ctx.rec = &rec;
	ctx.seed = seed;
	if (!rec.mat.vtable->scatter(rec.mat.object, &ctx, &srec))
		return (color);
	if (srec.is_specular)
		return (vec_add(color, vec_mult(srec.attenuation,
					ray_color(&srec.specular_ray, scene, depth - 1, seed))));
	color = vec_add(color, calc_direct_light(scene, &rec, srec.attenuation));
	return (vec_add(color, calc_diffuse(scene, &srec, &ctx, depth)));
}

t_color3	sampling_ray(t_scene *scene, t_camera *cam, int x, int y,
		unsigned int *seed)
{
	t_color3	pixel_color;
	double		u;
	double		v;
	int			s;
	t_ray		r;

	pixel_color = color_init(0, 0, 0);
	s = 0;
	while (s < SAMPLE_PER_PIXEL)
	{
		u = (x + random_double(seed)) / (scene->screen_width - 1);
		v = (scene->screen_height - 1 - y + random_double(seed))
			/ (scene->screen_height - 1);
		r = camera_get_ray(cam, u, v);
		pixel_color = color_add(pixel_color, ray_color(&r, scene, MAX_DEPTH,
					seed));
		s++;
	}
	return (color_init(ft_clamp(sqrt(pixel_color.r / SAMPLE_PER_PIXEL), 0, 1),
			ft_clamp(sqrt(pixel_color.g / SAMPLE_PER_PIXEL), 0, 1),
			ft_clamp(sqrt(pixel_color.b / SAMPLE_PER_PIXEL), 0, 1)));
}

void	get_gbuffer_info(t_scene *scene, t_camera *cam, int x, int y,
		t_pixel_data *data)
{
	double u;
	double v;
	t_ray r;
	t_hit_record rec;

	u = (double)x / (scene->screen_width - 1);
	v = (scene->screen_height - 1 - (double)y) / (scene->screen_height - 1);
	r = camera_get_ray(cam, u, v);

	if (scene->bvh->vtable->hit(scene->bvh->object, &r, (t_double_range){0.001,
			INFINITY}, &rec))
	{
		data->normal = rec.normal;
		data->position = rec.p;
		data->depth = rec.t;
	}
	else
	{
		data->normal = vec_init(0, 0, 0);
		data->position = vec_init(0, 0, 0);
		data->depth = -1.0;
	}
}