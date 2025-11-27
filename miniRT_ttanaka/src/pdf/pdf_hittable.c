#include "engine/pdf.h"

t_pdf   *create_hittable_pdf(t_hittable *obj, t_point3 origin);

static t_vec3   hittable_pdf_generate(const void *self, unsigned int *seed)
{
    const t_hittable_pdf_data *data = (const t_hittable_pdf_data *)self;

    return (data->obj->vtable->random(data->obj->object, data->origin, seed));
}

static double   hittable_pdf_value(const void *self, const t_vec3 *direction)
{
    const t_hittable_pdf_data *data = (const t_hittable_pdf_data *)self;

    return (data->obj->vtable->pdf_value(data->obj->object, data->origin, *direction));
}

t_pdf   *create_hittable_pdf(t_hittable *obj, t_point3 origin)
{
    t_pdf                   *pdf;
    t_hittable_pdf_data     *data;
    static const t_pdf_vtable vtable = {hittable_pdf_value, hittable_pdf_generate};

    pdf = malloc(sizeof(t_pdf));
    data = malloc(sizeof(t_hittable_pdf_data));
    data->obj = obj;
    data->origin = origin;
    pdf->data = data;
    pdf->vtable = &vtable;
    return (pdf);
}
