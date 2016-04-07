
#include "triangle.h"
#include "material.h"
#include "math_geo.h"

bool galileo::triangle::hit(const ray& r, FLOAT tmin, FLOAT tmax, FLOAT time, 
	surface_hit_record& rec) const
{
	FLOAT t, beta, gamma;
	
	if (triangle_intersect(r, tmin, tmax, p0, p1, p2, t, beta, gamma))
	{
		rec.mat = mat;
		rec.pt = rec.tex_pt = r.get_point(t);
		rec.t = t;
		
		FLOAT alpha = 1.0f - beta - gamma;
		rec.uv = vector2(
			alpha * u0.x() + beta * u1.x() + gamma * u2.x(),
			alpha * u0.y() + beta * u1.y() + gamma * u2.y());

		vector3 norm = normalize(cross((p1 - p0), (p2 - p0)));
		if (norm.z() < -0.9999f || norm.z() > 0.9999f)
			rec.frame.init_from_wv(norm, vector3(0, 1, 0));
		else
			rec.frame.init_from_wv(norm, vector3(0, 0, 1));

		return true;
	}

	return false;
}

bool galileo::triangle::random_point(const vector3& view_point, const vector2& aseed, 
	FLOAT time, vector3& on_light, vector3& normal, FLOAT& pdf, rgb& emitted_radiance) const
{
	float temp = sqrt(1.0f - aseed.x());
	float beta = (1.0f - temp);
	float gamma = temp * aseed.y();
	on_light = (1.0f - beta - gamma) * p0 + beta * p1 + gamma * p2;

	vector3 from_light = normalize(view_point - on_light);

	normal = normalize(cross((p1 - p0), (p2 - p0)));

	orthonormal_basis uvw;
	uvw.init_from_w(normal);

	emitted_radiance = mat->emitted_radiance(uvw, from_light, on_light, vector2(0.0f, 0.0f));

	return true;
}
