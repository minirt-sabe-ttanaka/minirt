/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:40 by ttanaka           #+#    #+#             */
/*   Updated: 2025/11/27 19:52:57 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCT_H
# define RT_STRUCT_H

typedef enum e_element_type			t_element_type;
typedef enum e_material_type		t_material_type;

typedef struct s_vec3				t_vec3;
typedef struct s_onb				t_onb;
typedef struct s_hit_record			t_hit_record;
typedef struct s_camera				t_camera;
typedef struct s_camera_config		t_camera_config;
typedef struct s_renderer			t_renderer;
typedef struct s_thread_data		t_thread_data;
typedef struct s_ambient			t_ambient;
typedef struct s_light				t_light;
typedef struct s_scene				t_scene;
typedef struct s_range				t_range;
typedef struct s_bvh_build_node		t_bvh_build_node;
typedef struct s_bvh_build			t_bvh_build;
typedef struct s_bvh_build_info		t_bvh_build_info;
typedef struct s_linear_bvh_node	t_linear_bvh_node;
typedef struct s_linear_bvh			t_linear_bvh;
typedef struct s_bucket				t_bucket;
typedef struct s_bucket_predicate	t_bucket_predicate;
typedef struct s_bvh_traversal		t_bvh_traversal;
typedef struct s_hittable_vtable	t_hittable_vtable;
typedef struct s_hittable			t_hittable;
typedef struct s_hittable_lst		t_hittable_lst;
typedef struct s_aabb				t_aabb;
typedef struct s_scatter_ctx		t_scatter_ctx;
typedef struct s_material_vtable	t_material_vtable;
typedef struct s_hit_record			t_hit_record;
typedef struct s_lambertian			t_lambertian;
typedef struct s_metal				t_metal;
typedef struct s_dielectric			t_dielectric;
typedef struct s_diffuse_light		t_diffuse_light;
typedef struct s_material_config	t_material_config;
typedef struct s_pdf_vtable			t_pdf_vtable;
typedef struct s_pdf				t_pdf;
typedef struct s_cosine_data		t_cosine_data;
typedef struct s_hittable_pdf_data	t_hittable_pdf_data;
typedef struct s_pixel_data			t_pixel_data;
#endif