#include "hittable/bvh.h"

static bool	satisfy_bucket_condition(const t_bvh_build_info *info,
				const t_bucket_predicate *pred);
int	partition_infos(t_bvh_build_info *info, t_range *range,
				const t_bucket_predicate *pred);

bool	satisfy_bucket_condition(const t_bvh_build_info *info,
		const t_bucket_predicate *pred)
{
	int	id;

	id = get_bucket_id(info, pred);
	return ((bool)(id < pred->split_bucket_id));
}

int	partition_infos(t_bvh_build_info *info, t_range *range,
		const t_bucket_predicate *pred)
{
	int	i;
	int	j;

	i = range->start;
	j = range->start;
	while (j < range->end)
	{
		if (satisfy_bucket_condition(&info[j], pred))
		{
			swap_t_hittable(info[i].hittable_p, info[j].hittable_p);
			swap_build_info(&info[i], &info[j]);
			i++;
		}
		j++;
	}
	return (i);
}
