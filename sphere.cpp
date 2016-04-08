
#include "sphere.h"
#include "material.h"
#include "math_geo.h"

bool galileo::c_sphere::hit(const c_ray& r, t_float tmin, t_float tmax, t_float time,
	c_surface_hit_record& rec) const
{
	t_float t;
	if (sphere_intersect(r, tmin, tmax, center, radius, t))
	{
		rec.instance_id = instance_id;
		rec.mat = mat;
		rec.pt = rec.tex_pt = r.get_point(t);
		rec.t = t;

		c_vector3 n = (rec.pt - center);
		t_float theta = acos(0.9999f * n.z());
		t_float sinTheta = sin(theta);
		t_float phi = acos(n.x() / (1.0001f * sinTheta));
		if (n.y() < 0.0f)
			phi = TWO_PI - phi;
		rec.uv = c_vector2(phi / TWO_PI, 1.0f - theta / PI);
		rec.frame.init_from_w(n);
		return true;
	}

	return false;
}

bool galileo::c_sphere::shadow_hit(const c_ray& r, t_float tmin, t_float tmax, t_float time) const
{
	t_float t;
	return sphere_intersect(r, tmin, tmax, center, radius, t);
}

bool galileo::c_sphere::random_point(const c_vector3& view_point, const c_vector2& aseed,
	t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf, c_rgb& emitted_radiance) const
{
	t_float d = (view_point - center).length();
	if (d < radius) 
		return false;

	t_float r = radius;
	c_vector2 seed = aseed;

	t_float sin_alpha_max = (r / d);
	t_float cos_alpha_max = sqrt(1 - sin_alpha_max * sin_alpha_max);
	t_float q = 1.0f / (TWO_PI * (1 - cos_alpha_max));
	int counter = 0;
	
	do 
	{
		t_float cos_alpha = 1 + seed.x()*(cos_alpha_max - 1);
		t_float sin_alpha = sqrt(1 - cos_alpha * cos_alpha);

		t_float phi = TWO_PI * seed.y();
		t_float cos_phi = cos(phi);
		t_float sin_phi = sin(phi);

		c_vector3 k_i(cos_phi * sin_alpha, sin_phi * sin_alpha, cos_alpha);

		c_ortho_basis uvw;
		uvw.init_from_w(center - view_point);

		c_ray to_light(view_point, k_i.x() * uvw.u() + k_i.y() * uvw.v() + k_i.z() * uvw.w());

		c_surface_hit_record rec;
		if (this->hit(to_light, 0.00001f, FLT_MAX, time, rec))
		{
			on_light = rec.pt;
			t_float cos_theta_prime = -dot(rec.frame.w(), to_light.direction());
			pdf = q * cos_theta_prime / (on_light - view_point).squared_length();
			normal = rec.frame.w();
			emitted_radiance = mat->emitted_radiance(rec.frame, -to_light.direction(),
				on_light, rec.uv);
			return true;
		}
		counter++;
		seed.scramble();
	} while (counter < 30);

	return false;
}
