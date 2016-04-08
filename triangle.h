#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "surface.h"

namespace galileo
{
	class triangle : public surface
	{
	public:
		triangle()
		{
		}
		
		triangle(const vector3& _p0, const vector3& _p1, const vector3& _p2,
			material* m)
		{
			p0 = _p0;
			p1 = _p1;
			p2 = _p2;
			mat = m;
		}

		triangle(const vector3& _p0, const vector3& _p1, const vector3& _p2,
			const vector2& _u0, const vector2& _u1, const vector2& _u2,
			material* m)
		{
			p0 = _p0;
			p1 = _p1;
			p2 = _p2;
			u0 = _u0;
			u1 = _u1;
			u2 = _u2;
			mat = m;
		}

		virtual bool hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time,
			surface_hit_record& rec) const;

		virtual bool shadow_hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time) const;

		virtual bool random_point(const vector3& view_point, const vector2& aseed,
			FLOAT time, vector3& on_light, vector3& normal, FLOAT& pdf,
			rgb& emitted_radiance) const;

		virtual bounds aabb(FLOAT time0, FLOAT time1) const
		{
			vector3 m1 = min(min(p0, p1), p2);
			vector3 m2 = max(max(p0, p1), p2);
			m1 -= FLOAT_EPSILON;
			m2 += FLOAT_EPSILON;
			return bounds(m1, m2);
		}

	public:
		vector3 p0;
		vector3 p1;
		vector3 p2;
		vector2 u0;
		vector2 u1;
		vector2 u2;
		material* mat;
	};
}

#endif
