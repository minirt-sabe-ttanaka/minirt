#include "engine/pdf.h"

t_pdf	*create_cosine_pdf(t_vec3 w);

static double	cosine_pdf_value(const void *self, const t_vec3 *direction)
{
	const t_cosine_data	*data = (const t_cosine_data *)self;
	double				cosine;
	t_vec3				unit_dir;

	unit_dir = vec_normalize(*direction);
	cosine = vec_dot(unit_dir, data->uvw.w);
	if (cosine <= 0)
		return (0.0);
	return (cosine / M_PI);
}

static t_vec3	cosine_pdf_generate(const void *self, unsigned int *seed)
{
	const t_cosine_data	*data;
    t_vec3 local_dir;
    
    data = (const t_cosine_data *)self;
    local_dir = random_cosine_direction(seed);
    return (onb_local2world(&data->uvw, local_dir.x, local_dir.y, local_dir.z));
}

t_pdf	*create_cosine_pdf(t_vec3 w)
{
	t_pdf *pdf;
	t_cosine_data *data;
	static const t_pdf_vtable vtable = {cosine_pdf_value, cosine_pdf_generate};

	pdf = malloc(sizeof(t_pdf));
	data = malloc(sizeof(t_cosine_data));
	onb_build_from_w(&data->uvw, w);
	pdf->data = data;
	pdf->vtable = &vtable;
	return (pdf);
}
