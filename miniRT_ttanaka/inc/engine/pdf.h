#ifndef PDF_H
# define PDF_H

# include "core/utils.h"
# include "scene/hittable.h"

typedef struct s_pdf_vtable
{
	double				(*value)(const void *self, const t_vec3 *dir);
	t_vec3				(*generate)(const void *self, unsigned int *seed);
}						t_pdf_vtable;

typedef struct s_pdf
{
	void				*data;
	const t_pdf_vtable	*vtable;
}						t_pdf;

typedef struct s_cosine_data
{
	t_onb				uvw;
}						t_cosine_data;

typedef struct s_hittable_pdf_data
{
	t_point3			origin;
	t_hittable			*obj;
}						t_hittable_pdf_data;

t_pdf					*create_cosine_pdf(t_vec3 w);
t_pdf					*create_hittable_pdf(t_hittable *obj, t_point3 origin);
t_pdf					*create_mixture_pdf(t_pdf *p0, t_pdf *p1);

#endif