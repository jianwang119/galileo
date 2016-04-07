
#include "bounds.h"
#include "math_geo.h"

bool galileo::bounds::ray_intersect(const ray& r, FLOAT tmin, FLOAT tmax) const
{
	return bounds_intersect(r, tmin, tmax, pp);
}
