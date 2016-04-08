#ifndef _SURFACE_LIST_H
#define _SURFACE_LIST_H

#include "surface.h"
#include "dynamic_array.h"

namespace galileo
{
	class c_surface_list : public c_surface
	{
	public:
		c_surface_list()
		{
		}

		virtual ~c_surface_list()
		{
		}

		virtual bool hit(const c_ray& r, t_float tmin, t_float tmax, t_float time,
			c_surface_hit_record& rec) const;

		virtual bool random_point(const c_vector3& view_point, const c_vector2& aseed,
			t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf,
			c_rgb& emitted_radiance) const
		{
			return false;
		}

		virtual c_bounds aabb(t_float time0, t_float time1) const;

		bool add(c_surface *s) 
		{ 
			return surfaces.append(s); 
		}

		int length() const 
		{ 
			return surfaces.length(); 
		}

	public:
		c_dynamic_array< c_surface* > surfaces;
	};
}

#endif
