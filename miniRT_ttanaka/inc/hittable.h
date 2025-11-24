#ifndef HITTABLE_H
#define HITTABLE_H

# include "hittable/base_hittable.h"
# include "hittable/hittable_lst.h"
# include "hittable/bvh.h"

void		destroy_bvh_build(t_bvh_build *bvh_build);
void		destroy_hittable_lst(t_hittable_lst *lst);
void		destroy_linear_bvh(t_linear_bvh *bvh);

#endif