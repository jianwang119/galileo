#ifndef _SURFACE_H
#define _SURFACE_H

#include "rgb.h"
#include "bounds.h"
#include "vector2.h"
#include "vector3.h"
#include "orthonormal_basis.h"

namespace galileo
{
	class material;

	class surface_hit_record 
	{
	public:
		FLOAT t;
		vector3 pt;
		vector3 tex_pt;
		orthonormal_basis frame;
		vector2 uv;
		material* mat;
	};

	class surface
	{
	public:
		virtual bool hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time,
			surface_hit_record& rec) const = 0;

		virtual bool fast_hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time) const
		{
			surface_hit_record rec;
			return hit(r, tmin, tmax, time, rec);
		}

		virtual bool random_point(const vector3& view_point, const vector2& aseed, 
			FLOAT time, vector3& on_light, vector3& normal, FLOAT& pdf,
			rgb& emitted_radiance) const = 0;

		virtual bounds aabb(FLOAT time0, FLOAT time1) const = 0;

		virtual S32 caustic_photons() 
		{ 
			return 0; 
		}
		
		virtual S32 global_photons()
		{ 
			return 0; 
		}

		virtual rgb photon_color() 
		{ 
			return rgb(0, 0, 0); 
		}

		virtual bool generate_photon(ray& r, const vector2&, const vector2&)
		{
			return false;
		}
	};
}

#endif
