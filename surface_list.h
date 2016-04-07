#ifndef _SURFACE_LIST_H
#define _SURFACE_LIST_H

#include "surface.h"
#include "dynamic_array.h"

namespace galileo
{
	class surface_list : public surface
	{
	public:
		surface_list()
		{
		}

		virtual ~surface_list()
		{
		}

		virtual bool hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time,
			surface_hit_record& rec) const;

		virtual bool random_point(const vector3& view_point, const vector2& aseed,
			FLOAT time, vector3& on_light, vector3& normal, FLOAT& pdf,
			rgb& emitted_radiance) const
		{
			return false;
		}

		virtual bounds aabb(FLOAT time0, FLOAT time1) const;

		bool add(surface *s) 
		{ 
			return surfaces.append(s); 
		}

		int length() const 
		{ 
			return surfaces.length(); 
		}

	public:
		dynamic_array< surface* > surfaces;
	};
}

#endif
