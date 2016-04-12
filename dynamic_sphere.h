#ifndef _DYNAMIC_SPHERE_H
#define _DYNAMIC_SPHERE_H

#include "surface.h"

namespace galileo
{
	class c_dynamic_sphere : public c_surface
	{
	public:
		c_dynamic_sphere(c_vector3 _center, t_float _radius, c_material* _mat,
			t_float _min_time, t_float _max_time,
			c_vector3(*_get_center)(float, const c_vector3&));

		virtual bool hit(const c_ray& r, t_float tmin, t_float tmax, t_float time,
			c_surface_hit_record& rec) const;

		virtual bool shadow_hit(const c_ray& r, t_float tmin, t_float tmax, t_float time) const;

		virtual bool random_point(const c_vector3& view_point, const c_vector2& aseed,
			t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf,
			c_rgb& emitted_radiance) const;

		virtual c_bounds aabb(t_float time0, t_float time1) const
		{
			c_vector3 c1 = get_center(time0, center);
			c_vector3 c2 = get_center(time1, center);

			c_bounds b1 = c_bounds(
				c1 - c_vector3(radius, radius, radius),
				c1 + c_vector3(radius, radius, radius));
			c_bounds b2 = c_bounds(
				c2 - c_vector3(radius, radius, radius),
				c2 + c_vector3(radius, radius, radius));

			return surround(b1, b2);
		}

	public:
		c_vector3 center;
		t_float radius;
		t_float min_time;
		t_float max_time;
		c_material* mat;
		c_vector3(*get_center)(float, const c_vector3&);
	};
}

#endif
