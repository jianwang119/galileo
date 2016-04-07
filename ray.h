#ifndef _RAY_H
#define _RAY_H

#include "vector3.h"

namespace galileo
{
	class ray
	{
	public:
		ray()
		{
		}

		ray(const vector3& o, const vector3& d)
		{
			data[0] = o;
			set_direction(d);
		}

		ray(const ray& r)
		{
			*this = r;
		}

		const vector3& origin() const
		{
			return data[0];
		}

		const vector3& direction() const
		{
			return data[1];
		}

		const vector3& direction_inv() const
		{
			return data[2];
		}

		void set_origin(const vector3& v)
		{
			data[0] = v;
		}

		void set_direction(const vector3& v)
		{
			data[1] = v;
			data[2] = vector3(1.0f / v.x(), 1.0f / v.y(), 1.0f / v.z());

			posneg[0] = (data[1].x() > 0 ? 0 : 1);
			posneg[1] = posneg[0] ^ 1;

			posneg[2] = (data[1].y() > 0 ? 0 : 1);
			posneg[3] = posneg[2] ^ 1;

			posneg[4] = (data[1].z() > 0 ? 0 : 1);
			posneg[5] = posneg[4] ^ 1;
		}

		vector3 get_point(FLOAT t)
		{
			return data[0] + t * data[1];
		}

	public:
		vector3 data[3];
		int posneg[6];
	};

	inline std::ostream &operator<<(std::ostream &os, const ray &r)
	{
		return os << r.origin() << r.direction();
	}
}

#endif
