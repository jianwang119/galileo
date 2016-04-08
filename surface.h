#ifndef _SURFACE_H
#define _SURFACE_H

#include "rgb.h"
#include "bounds.h"
#include "vector2.h"
#include "vector3.h"
#include "ortho_basis.h"

namespace galileo
{
	class c_material;

	class c_surface_hit_record 
	{
	public:
		t_float t;
		c_vector3 pt;
		c_vector3 tex_pt;
		c_ortho_basis frame;
		c_vector2 uv;
		c_material* mat;
		t_u32 instance_id;
	};

	class c_surface
	{
	public:
		c_surface()
		{
			instance_id = instance_id_counter++;
		}

		t_u32 id() const
		{
			return instance_id;
		}

		virtual bool hit(const c_ray& r, t_float tmin, t_float tmax, t_float time,
			c_surface_hit_record& rec) const = 0;

		virtual bool shadow_hit(const c_ray& r, t_float tmin, t_float tmax, t_float time) const
		{
			c_surface_hit_record rec;
			return hit(r, tmin, tmax, time, rec);
		}

		virtual bool random_point(const c_vector3& view_point, const c_vector2& aseed, 
			t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf,
			c_rgb& emitted_radiance) const = 0;

		virtual c_bounds aabb(t_float time0, t_float time1) const = 0;

		virtual t_s32 caustic_photons() 
		{ 
			return 0; 
		}
		
		virtual t_s32 global_photons()
		{ 
			return 0; 
		}

		virtual c_rgb photon_color() 
		{ 
			return c_rgb(0, 0, 0); 
		}

		virtual bool generate_photon(c_ray& r, const c_vector2&, const c_vector2&)
		{
			return false;
		}

	protected:
		t_u32 instance_id;

	protected:
		static t_u32 instance_id_counter;
	};
}

#endif
