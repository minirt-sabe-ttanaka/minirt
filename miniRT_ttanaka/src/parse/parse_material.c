#include "engine/parse.h"

bool parse_material_format(char *color, char *type, char *param, t_material_config *config);

static bool parse_material_type(char *s, t_material_type *type)
{
    if (ft_strcmp(s, "lambertian") == 0)
        return (*type =lambertian, true);
    if (ft_strcmp(s, "metal") == 0)
        return (*type = metal, true);
    if (ft_strcmp(s, "dielectric") == 0)
        return (*type = dielectric, true);
    if (ft_strcmp(s, "diffuse_light") == 0)
        return (*type = diffuse_light, true);
    return (false);
}

bool parse_material_format(char *color, char *type, char *param, t_material_config *config)
{
    if (parse_color_format(color, &(config->color)) == false)
		return (false);
    if (parse_material_type(type, &(config->type)) == false)
        return (false);
    if (config->type == lambertian || config->type == diffuse_light)
        return (!param);
    else
    {
        if (!param)
            return (false);
        if (parse_double(param, &(config->parameter)) == false)
            return (false);
        if (config->type == metal)
            return (0.0 <= config->parameter && config->parameter <= 1.0);
        else
            return (config->parameter >= 0.0);
    }
}

bool create_material(t_material_config *m_config, t_material *material)
{
    void *mat;

    if (m_config->type == lambertian)
        mat = malloc(sizeof(t_lambertian));
    else if (m_config->type == metal)
        mat = malloc(sizeof(t_metal));
    else if (m_config->type == dielectric)
        mat = malloc(sizeof(t_dielectric));
    else if (m_config->type == diffuse_light)
        mat = malloc(sizeof(t_diffuse_light));
    else
        return (false);
    if (!mat)
        return (false);
    if (m_config->type == lambertian)
        *material = create_lambertian((t_lambertian *)mat, m_config->color);
    if (m_config->type == metal)
        *material = create_metal((t_metal *)mat, m_config->color, m_config->parameter);
    if (m_config->type == dielectric)
        *material = create_dielectric((t_dielectric *)mat, m_config->parameter);
    if (m_config->type == diffuse_light)
        *material = create_diffuse_light((t_diffuse_light *)mat, m_config->color);
    return (true);
}
