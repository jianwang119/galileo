#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "rgb.h"
#include "vector3.h"
#include "orthonormal_basis.h"
#include "surface.h"

namespace galileo
{
	class material
	{
	public:
		virtual bool emits() const 
		{ 
			return false; 
		}

		virtual rgb emitted_radiance(const orthonormal_basis& frame,
			const vector3& v_out, const vector3& p, const vector2& uv)
		{
			return rgb(0, 0, 0);
		}

		virtual rgb ambient_response(const orthonormal_basis& frame,
			const vector3& v, const vector3& p, const vector2& uv)
		{
			return rgb(0, 0, 0);
		}

		virtual bool explicit_brdf(const orthonormal_basis& frame,
			const vector3& v1, const vector3& v0, const vector3& p, 
			const vector2& uv, rgb& brdf) 
		{
			return false;
		}

		virtual bool scatter_direction(const vector3& v_in,
			const surface_hit_record& rec, vector2& seed, rgb& color, 
			bool& count_emitted_light, float& brdf_scale, vector3& v_out) = 0;                           // scattered direction

		virtual bool is_specular() 
		{ 
			return false; 
		}
		
		virtual bool isTransmissive() 
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

		virtual rgb photon_color() 
		{ 
			return rgb(0.0f, 0.0f, 0.0f); 
		}
	};

}

#endif
