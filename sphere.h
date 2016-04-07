#ifndef _SPHERE_H
#define _SPHERE_H

#include "surface.h"

namespace galileo
{
	class sphere : public surface
	{
	public:
		sphere(vector3 c, FLOAT r, material* m)
		{
			center = c; 
			radius = r; 
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
			return bounds(center - vector3(radius, radius, radius),
				center + vector3(radius, radius, radius));
		}

	public:
		vector3 center;
		float radius;
		material* mat;
	};
}

#endif
