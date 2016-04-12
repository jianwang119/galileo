
#include "dynamic_sphere.h"
#include "material.h"
#include "math_geo.h"

galileo::c_dynamic_sphere::c_dynamic_sphere(c_vector3 _center, t_float _radius, 
	c_material* _mat, t_float _min_time, t_float _max_time,
	c_vector3(*_get_center)(float, const c_vector3&))
{
	center = _center;
	radius = _radius;
	min_time = _min_time;
	max_time = _max_time;
	mat = mat;
	get_center = _get_center;
}

bool galileo::c_dynamic_sphere::hit(const c_ray& r, t_float tmin, t_float tmax, t_float time,
	c_surface_hit_record& rec) const
{
	c_vector3 cur_center = get_center(time, center);
	t_float t;
	if (sphere_intersect(r, tmin, tmax, cur_center, radius, t))
	{
		rec.instance_id = instance_id;
		rec.mat = mat;
		rec.pt = rec.tex_pt = r.get_point(t);
		rec.t = t;

		c_vector3 n = (rec.pt - cur_center);
		t_float theta = acos(0.9999f * n.z());
		t_float sinTheta = sin(theta);
		t_float phi = acos(n.x() / (1.0001f * sinTheta));
		if (n.y() < 0.0f)
			phi = TWO_PI - phi;
		rec.uv = c_vector2(phi / TWO_PI, 1.0f - theta / PI);
		if (n.z() < -0.9999 || n.z() > 0.9999)
			rec.frame.init_from_wv(n, c_vector3(0, 1, 0));
		else
			rec.frame.init_from_wv(n, c_vector3(0, 0, 1));
		return true;
	}

	return false;
}

bool galileo::c_dynamic_sphere::shadow_hit(const c_ray& r, t_float tmin, t_float tmax, t_float time) const
{
	c_vector3 cur_center = get_center(time, center);
	t_float t;
	return sphere_intersect(r, tmin, tmax, cur_center, radius, t);
}

bool galileo::c_dynamic_sphere::random_point(const c_vector3& view_point, const c_vector2& aseed,
	t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf, c_rgb& emitted_radiance) const
{
	return false;
}
