#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "surface.h"

namespace galileo
{
	class c_triangle : public c_surface
	{
	public:
		c_triangle()
		{
		}
		
		c_triangle(const c_vector3& _p0, const c_vector3& _p1, const c_vector3& _p2,
			c_material* m)
		{
			p0 = _p0;
			p1 = _p1;
			p2 = _p2;
			mat = m;
		}

		c_triangle(const c_vector3& _p0, const c_vector3& _p1, const c_vector3& _p2,
			const c_vector2& _u0, const c_vector2& _u1, const c_vector2& _u2,
			c_material* m)
		{
			p0 = _p0;
			p1 = _p1;
			p2 = _p2;
			u0 = _u0;
			u1 = _u1;
			u2 = _u2;
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
			c_vector3 m1 = min(min(p0, p1), p2);
			c_vector3 m2 = max(max(p0, p1), p2);
			m1 -= FLT_EPSILON;
			m2 += FLT_EPSILON;
			return c_bounds(m1, m2);
		}

	public:
		c_vector3 p0;
		c_vector3 p1;
		c_vector3 p2;
		c_vector2 u0;
		c_vector2 u1;
		c_vector2 u2;
		c_material* mat;
	};
}

#endif
