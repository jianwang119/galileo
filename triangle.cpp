
#include "triangle.h"
#include "material.h"
#include "math_geo.h"

bool galileo::c_triangle::hit(const c_ray& r, t_float tmin, t_float tmax, t_float time, 
	c_surface_hit_record& rec) const
{
	t_float t, beta, gamma;
	
	if (triangle_intersect(r, tmin, tmax, p0, p1, p2, t, beta, gamma))
	{
		rec.instance_id = instance_id;
		rec.mat = mat;
		rec.pt = rec.tex_pt = r.get_point(t);
		rec.t = t;
		
		t_float alpha = 1.0f - beta - gamma;
		rec.uv = c_vector2(
			alpha * u0.x() + beta * u1.x() + gamma * u2.x(),
			alpha * u0.y() + beta * u1.y() + gamma * u2.y());

		c_vector3 norm = normalize(cross((p1 - p0), (p2 - p0)));
		if (norm.z() < -0.9999f || norm.z() > 0.9999f)
			rec.frame.init_from_wv(norm, c_vector3(0, 1, 0));
		else
			rec.frame.init_from_wv(norm, c_vector3(0, 0, 1));

		return true;
	}

	return false;
}

bool galileo::c_triangle::shadow_hit(const c_ray& r, t_float tmin, t_float tmax, t_float time) const
{
	t_float t, beta, gamma;
	return triangle_intersect(r, tmin, tmax, p0, p1, p2, t, beta, gamma);
}

bool galileo::c_triangle::random_point(const c_vector3& view_point, const c_vector2& aseed,
	t_float time, c_vector3& on_light, c_vector3& normal, t_float& pdf, c_rgb& emitted_radiance) const
{
	t_float temp = sqrt(1.0f - aseed.x());
	t_float beta = (1.0f - temp);
	t_float gamma = temp * aseed.y();
	on_light = (1.0f - beta - gamma) * p0 + beta * p1 + gamma * p2;

	c_vector3 from_light = normalize(view_point - on_light);

	normal = normalize(cross((p1 - p0), (p2 - p0)));

	c_ortho_basis uvw;
	uvw.init_from_w(normal);

	emitted_radiance = mat->emitted_radiance(uvw, from_light, on_light, c_vector2(0.0f, 0.0f));

	return true;
}
