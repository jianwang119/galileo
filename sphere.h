#ifndef _SPHERE_H
#define _SPHERE_H

#include "surface.h"

namespace galileo
{
	class c_sphere : public c_surface
	{
	public:
		c_sphere(c_vector3 c, t_float r, c_material* m)
		{
			center = c; 
			radius = r; 
			mat = m;
		}

		virtual bool hit(const c_ray& r, t_float tmin, t_float tmax, t_float time,
			c_surface_hit_record& rec) const;

		virtual bool shadow_hit(const c_ray& r, t_float tmin, t_float tmax, t_float time) const;

		virtual bool random_point(const c_vector3& view_point, const c_vector2& aseed,
			t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf,
			c_rgb& emitted_radiance) const;

		virtual c_bounds aabb(t_float time0, t_float time1) const
		{
			return c_bounds(center - c_vector3(radius, radius, radius),
				center + c_vector3(radius, radius, radius));
		}

	public:
		c_vector3 center;
		t_float radius;
		c_material* mat;
	};
}

#endif
