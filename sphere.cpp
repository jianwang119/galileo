
#include "sphere.h"
#include "material.h"
#include "math_geo.h"

bool galileo::sphere::hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time,
	surface_hit_record& rec) const
{
	FLOAT t;
	if (sphere_intersect(r, tmin, tmax, center, radius, t))
	{
		rec.instance_id = instance_id;
		rec.mat = mat;
		rec.pt = rec.tex_pt = r.get_point(t);
		rec.t = t;

		vector3 n = (rec.pt - center);
		FLOAT theta = acos(0.9999f * n.z());
		FLOAT sinTheta = sin(theta);
		FLOAT phi = acos(n.x() / (1.0001f * sinTheta));
		if (n.y() < 0.0f)
			phi = TWO_PI - phi;
		rec.uv = vector2(phi / TWO_PI, 1.0f - theta / PI);
		rec.frame.init_from_w(n);
		return true;
	}

	return false;
}

bool galileo::sphere::shadow_hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time) const
{
	FLOAT t;
	return sphere_intersect(r, tmin, tmax, center, radius, t);
}

bool galileo::sphere::random_point(const vector3& view_point, const vector2& aseed,
	FLOAT time, vector3& on_light, vector3& normal, FLOAT& pdf, rgb& emitted_radiance) const
{
	FLOAT d = (view_point - center).length();
	if (d < radius) 
		return false;

	FLOAT r = radius;
	vector2 seed = aseed;

	FLOAT sin_alpha_max = (r / d);
	FLOAT cos_alpha_max = sqrt(1 - sin_alpha_max * sin_alpha_max);
	FLOAT q = 1.0f / (TWO_PI * (1 - cos_alpha_max));
	int counter = 0;
	
	do 
	{
		FLOAT cos_alpha = 1 + seed.x()*(cos_alpha_max - 1);
		FLOAT sin_alpha = sqrt(1 - cos_alpha * cos_alpha);

		FLOAT phi = TWO_PI * seed.y();
		FLOAT cos_phi = cos(phi);
		FLOAT sin_phi = sin(phi);

		vector3 k_i(cos_phi * sin_alpha, sin_phi * sin_alpha, cos_alpha);

		orthonormal_basis uvw;
		uvw.init_from_w(center - view_point);

		ray to_light(view_point, k_i.x() * uvw.u() + k_i.y() * uvw.v() + k_i.z() * uvw.w());

		surface_hit_record rec;
		if (this->hit(to_light, 0.00001f, FLT_MAX, time, rec)) 
		{
			on_light = rec.pt;
			FLOAT cos_theta_prime = -dot(rec.frame.w(), to_light.direction());
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
