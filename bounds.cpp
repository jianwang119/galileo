
#include "bounds.h"
#include "math_geo.h"

bool galileo::c_bounds::ray_intersect(const c_ray& r, t_float tmin, t_float tmax) const
{
	return bounds_intersect(r, tmin, tmax, pp);
}
