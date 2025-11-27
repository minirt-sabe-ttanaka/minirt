#include "engine/pdf.h"

t_pdf   *create_mixture_pdf(t_pdf *p0, t_pdf *p1);

typedef struct s_mixture_data
{
    t_pdf   *p[2];
} t_mixture_data;

static double   mixture_pdf_value(const void *self, const t_vec3 *direction)
{
    const t_mixture_data *data = (const t_mixture_data *)self;
    double val0;
    double val1;

    val0 = data->p[0]->vtable->value(data->p[0]->data, direction);
    val1 = data->p[1]->vtable->value(data->p[1]->data, direction);
    return (0.5 * val0 + 0.5 * val1);
}

static t_vec3   mixture_pdf_generate(const void *self, unsigned int *seed)
{
    const t_mixture_data *data = (const t_mixture_data *)self;

    if (random_double(seed) < 0.5)
        return (data->p[0]->vtable->generate(data->p[0]->data, seed));
    else
        return (data->p[1]->vtable->generate(data->p[1]->data, seed));
}

t_pdf   *create_mixture_pdf(t_pdf *p0, t_pdf *p1)
{
    t_pdf           *pdf;
    t_mixture_data  *data;
    static const t_pdf_vtable vtable = {mixture_pdf_value, mixture_pdf_generate};

    pdf = malloc(sizeof(t_pdf));
    data = malloc(sizeof(t_mixture_data));
    data->p[0] = p0;
    data->p[1] = p1;
    pdf->data = data;
    pdf->vtable = &vtable;
    return (pdf);
}
