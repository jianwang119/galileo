
#include "surface_list.h"

bool galileo::c_surface_list::hit(const c_ray& r, t_float tmin, t_float tmax, t_float time, 
	c_surface_hit_record& rec) const
{
	c_surface_hit_record temp;
	rec.t = tmax;
	bool hit_something = false;
	for (int i = 0; i < length(); i++) 
	{
		if (surfaces[i]->hit(r, tmin, rec.t, time, temp))
		{
			rec = temp;
			hit_something = true;
		}
	}
	return hit_something;
}

galileo::c_bounds galileo::c_surface_list::aabb(t_float time0, t_float time1) const
{
	c_vector3 _min(FLT_MAX, FLT_MAX, FLT_MAX);
	c_vector3 _max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int i = 0; i < length(); i++)
	{
		c_bounds box = surfaces[i]->aabb(time0, time1);
		if (box.min().x() < _min.x()) _min.set_x(box.min().x());
		if (box.min().y() < _min.y()) _min.set_y(box.min().y());
		if (box.min().z() < _min.z()) _min.set_z(box.min().z());
		if (box.max().x() > _max.x()) _max.set_x(box.max().x());
		if (box.max().y() > _max.y()) _max.set_y(box.max().y());
		if (box.max().z() > _max.z()) _max.set_z(box.max().z());
	}
	return c_bounds(_min, _max);
}
