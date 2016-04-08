#ifndef _MATH_GEO_H
#define _MATH_GEO_H

#include "math_utils.h"

#include "vector3.h"
#include "ray.h"

namespace galileo
{
	inline bool bounds_intersect(const ray& r, FLOAT tmin, FLOAT tmax, const vector3 pp[])
	{
		float interval_min = tmin;
		float interval_max = tmax;

		float t0 = (pp[r.posneg[0]].x() - r.origin().x()) * r.direction_inv().x();
		float t1 = (pp[r.posneg[1]].x() - r.origin().x()) * r.direction_inv().x();
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

	inline bool sphere_intersect(const ray& r, float tmin, float tmax,
		const vector3& center, FLOAT radius, FLOAT& t)
	{
		vector3 temp = r.origin() - center;
		FLOAT twoa = 2.0f * dot(r.direction(), r.direction());
		FLOAT b = 2.0f * dot(r.direction(), temp);
		FLOAT c = dot(temp, temp) - radius*radius;
		FLOAT discriminant = b * b - 2.0f * twoa * c;

		if (discriminant > 0.0f)
		{
			discriminant = sqrt(discriminant);
			FLOAT t = (-b - discriminant) / twoa;
			if (t < tmin)
				t = (-b + discriminant) / twoa;
			return (!(t < tmin || t > tmax));
		}
		return false;
	}

	inline bool triangle_intersect(const ray& r, float tmin, float tmax,
		const vector3& p0, const vector3& p1, const vector3& p2,
		FLOAT& t, FLOAT& beta, FLOAT& gamma)
	{
		FLOAT A = p0.x() - p1.x();
		FLOAT B = p0.y() - p1.y();
		FLOAT C = p0.z() - p1.z();

		FLOAT D = p0.x() - p2.x();
		FLOAT E = p0.y() - p2.y();
		FLOAT F = p0.z() - p2.z();

		FLOAT G = r.direction().x();
		FLOAT H = r.direction().y();
		FLOAT I = r.direction().z();

		FLOAT J = p0.x() - r.origin().x();
		FLOAT K = p0.y() - r.origin().y();
		FLOAT L = p0.z() - r.origin().z();

		FLOAT EIHF = E*I - H*F;
		FLOAT GFDI = G*F - D*I;
		FLOAT DHEG = D*H - E*G;

		FLOAT denom = (A*EIHF + B*GFDI + C*DHEG);

		beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

		if (beta <= 0.0 || beta >= 1)
			return false;

		float AKJB = A*K - J*B;
		float JCAL = J*C - A*L;
		float BLKC = B*L - K*C;

		gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
		if (gamma <= 0.0 || beta + gamma >= 1.0)
			return false;

		t = -(F*AKJB + E*JCAL + D*BLKC) / denom;
		return (t >= tmin && t <= tmax);
	}
}

#endif
