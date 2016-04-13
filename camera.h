#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector3.h"
#include "ray.h"
#include "ortho_basis.h"

namespace galileo
{
	class c_camera
	{
	public:
		c_camera()
		{
		}

		c_camera(const c_camera& rhs)
		{
			center = rhs.center;
			corner = rhs.corner;
			across = rhs.across;
			up = rhs.up;
			frame = rhs.frame;
			left = rhs.left;
			right = rhs.right;
			bottom = rhs.bottom;
			top = rhs.top;
			distance = rhs.distance;
			lens_radius = rhs.lens_radius;
		}

		c_camera(const c_vector3& _center, const c_vector3& gaze, const c_vector3& _up,
			t_float aperture, t_float l, t_float r, t_float b, t_float t, t_float d)
		{
			center = _center;
			frame.init_from_wv(-gaze, _up);
			corner = center + l * frame.u() + b * frame.v() - d * frame.w();
			across = (r - l) * frame.u();
			up = (t - b) * frame.v();
			left = l;
			right = r;
			bottom = b;
			top = t;
			distance = d;
			lens_radius = aperture / 2.0f;
		}

		c_ray get_ray(t_float a, t_float b, t_float xi1, t_float xi2)
		{
			c_vector3 origin = center + 
				2.0f * (xi1 - 0.5F) * lens_radius * frame.u() +
				2.0f * (xi2 - 0.5F) * lens_radius * frame.v();
			c_vector3 target = corner + across * a + up * b;
			return c_ray(origin, normalize(target - origin));
		}

	public:
		c_vector3 center;
		c_vector3 up;
		c_vector3 corner;
		c_vector3 across;
		c_ortho_basis frame;
		t_float left;
		t_float right;
		t_float bottom;
		t_float top;
		t_float distance;
		t_float lens_radius;
	};
}

#endif
