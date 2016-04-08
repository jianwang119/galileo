#ifndef _MATH_GEO_H
#define _MATH_GEO_H

#include "math_utils.h"

#include "vector3.h"
#include "ray.h"

namespace galileo
{
	inline bool bounds_intersect(const c_ray& r, t_float tmin, t_float tmax, const c_vector3 pp[])
	{
		t_float interval_min = tmin;
		t_float interval_max = tmax;

		t_float t0 = (pp[r.posneg[0]].x() - r.origin().x()) * r.direction_inv().x();
		t_float t1 = (pp[r.posneg[1]].x() - r.origin().x()) * r.direction_inv().x();
		if (t0 > interval_min) interval_min = t0;
		if (t1 < interval_max) interval_max = t1;
		if (interval_min > interval_max)
			return false;

		t0 = (pp[r.posneg[2]].y() - r.origin().y()) * r.direction_inv().y();
		t1 = (pp[r.posneg[3]].y() - r.origin().y()) * r.direction_inv().y();
		if (t0 > interval_min) interval_min = t0;
		if (t1 < interval_max) interval_max = t1;
		if (interval_min > interval_max)
			return false;

		t0 = (pp[r.posneg[4]].z() - r.origin().z()) * r.direction_inv().z();
		t1 = (pp[r.posneg[5]].z() - r.origin().z()) * r.direction_inv().z();
		if (t0 > interval_min) interval_min = t0;
		if (t1 < interval_max) interval_max = t1;
		if (interval_min > interval_max)
			return false;

		return true;
	}

	inline bool sphere_intersect(const c_ray& r, t_float tmin, t_float tmax,
		const c_vector3& center, t_float radius, t_float& t)
	{
		c_vector3 temp = r.origin() - center;
		t_float twoa = 2.0f * dot(r.direction(), r.direction());
		t_float b = 2.0f * dot(r.direction(), temp);
		t_float c = dot(temp, temp) - radius*radius;
		t_float discriminant = b * b - 2.0f * twoa * c;

		if (discriminant > 0.0f)
		{
			discriminant = sqrt(discriminant);
			t = (-b - discriminant) / twoa;
			if (t < tmin)
				t = (-b + discriminant) / twoa;
			return (!(t < tmin || t > tmax));
		}
		return false;
	}

	inline bool triangle_intersect(const c_ray& r, t_float tmin, t_float tmax,
		const c_vector3& p0, const c_vector3& p1, const c_vector3& p2,
		t_float& t, t_float& beta, t_float& gamma)
	{
		t_float A = p0.x() - p1.x();
		t_float B = p0.y() - p1.y();
		t_float C = p0.z() - p1.z();

		t_float D = p0.x() - p2.x();
		t_float E = p0.y() - p2.y();
		t_float F = p0.z() - p2.z();

		t_float G = r.direction().x();
		t_float H = r.direction().y();
		t_float I = r.direction().z();

		t_float J = p0.x() - r.origin().x();
		t_float K = p0.y() - r.origin().y();
		t_float L = p0.z() - r.origin().z();

		t_float EIHF = E*I - H*F;
		t_float GFDI = G*F - D*I;
		t_float DHEG = D*H - E*G;

		t_float denom = (A*EIHF + B*GFDI + C*DHEG);

		beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

		if (beta <= 0.0 || beta >= 1)
			return false;

		t_float AKJB = A*K - J*B;
		t_float JCAL = J*C - A*L;
		t_float BLKC = B*L - K*C;

		gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
		if (gamma <= 0.0 || beta + gamma >= 1.0)
			return false;

		t = -(F*AKJB + E*JCAL + D*BLKC) / denom;
		return (t >= tmin && t <= tmax);
	}
}

#endif
