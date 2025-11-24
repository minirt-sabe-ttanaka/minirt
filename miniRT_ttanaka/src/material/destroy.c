#include "material.h"

void destroy_default_material(void **object_ptr)
{
    if (object_ptr && *object_ptr)
    {
        free(*object_ptr);
        *object_ptr = NULL;
    }
}
