#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "rgb.h"
#include "vector3.h"
#include "ortho_basis.h"
#include "surface.h"

namespace galileo
{
	class c_material
	{
	public:
		virtual bool emits() const 
		{ 
			return false; 
		}

		virtual c_rgb emitted_radiance(const c_ortho_basis& frame,
			const c_vector3& v_out, const c_vector3& on_light, const c_vector2& uv)
		{
			return c_rgb(0, 0, 0);
		}

		virtual c_rgb ambient_response(const c_ortho_basis& frame,
			const c_vector3& v, const c_vector3& on_light, const c_vector2& uv)
		{
			return c_rgb(0, 0, 0);
		}

		virtual bool explicit_brdf(const c_ortho_basis& frame,
			const c_vector3& v1, const c_vector3& v0, const c_vector3& on_light,
			const c_vector2& uv, c_rgb& brdf) 
		{
			return false;
		}

		virtual bool scatter_direction(const c_vector3& v_in,
			const c_surface_hit_record& rec, c_vector2& seed, c_rgb& color, 
			bool& count_emitted_light, t_float& brdf_scale, c_vector3& v_out) = 0;                           // scattered direction

		virtual bool is_specular() 
		{ 
			return false; 
		}
		
		virtual bool is_transmissive() 
		{ 
			return false; 
		}

		virtual int caustic_photons() 
		{ 
			return 0; 
		}

		virtual int global_photons() 
		{ 
			return 0; 
		}

		virtual c_rgb photon_color() 
		{ 
			return c_rgb(0.0f, 0.0f, 0.0f); 
		}
	};

}

#endif
