#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "global_define.h"
#include "math_utils.h"

namespace galileo
{
	class vector3
	{
	public:
		vector3()
		{
			e[0] = e[1] = e[2] = 0;
		}

		vector3(float e0, float e1, float e2)
		{
			e[0] = e0;
			e[1] = e1;
			e[2] = e2;
		}

		vector3(const vector3& v)
		{
			e[0] = v.e[0];
			e[1] = v.e[1];
			e[2] = v.e[2];
		}

		float x() const
		{
			return e[0];
		}

		float y() const
		{
			return e[1];
		}

		float z() const
		{
			return e[2];
		}

		void set_x(float f)
		{
			e[0] = f;
		}

		void set_y(float f)
		{
			e[1] = f;
		}

		void set_z(float f)
		{
			e[2] = f;
		}

		FLOAT length() const
		{
			return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		}

		FLOAT squared_length() const
		{
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		void normalize();

		FLOAT min_component() const
		{
			return e[index_Of_min_component()];
		}

		FLOAT max_component() const
		{
			return e[index_of_max_component()];
		}

		FLOAT min_abs_component() const
		{
			return e[index_of_min_abs_component()];
		}

		FLOAT max_abs_component() const
		{
			return e[index_of_max_abs_component()];
		}
		
		int index_Of_min_component() const
		{
			return (e[0] < e[1] && e[0] < e[2]) ? 0 : (e[1] < e[2] ? 1 : 2);
		}

		int index_of_min_abs_component() const
		{
			if (fabs(e[0]) < fabs(e[1]) && fabs(e[0]) < fabs(e[2]))
				return 0;
			else if (fabs(e[1]) < fabs(e[2]))
				return 1;
			else
				return 2;
		}

		int index_of_max_component() const
		{
			return (e[0] > e[1] && e[0] > e[2]) ? 0 : (e[1] > e[2] ? 1 : 2);
		}

		int index_of_max_abs_component() const
		{
			if (fabs(e[0]) > fabs(e[1]) && fabs(e[0]) > fabs(e[2]))
				return 0;
			else if (fabs(e[1]) > fabs(e[2]))
				return 1;
			else
				return 2;
		}

		vector3 operator+() const
		{
			return *this;
		}

		vector3 operator-() const
		{
			return vector3(-e[0], -e[1], -e[2]);
		}

		FLOAT operator[](int i) const
		{
			return e[i];
		}

		FLOAT& operator[](int i)
		{
			return e[i];
		}

		vector3& operator+=(const vector3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}

		vector3& operator-=(const vector3& v)
		{
			e[0] -= v.e[0];
			e[1] -= v.e[1];
			e[2] -= v.e[2];
			return *this;
		}

		vector3& operator*=(const FLOAT f)
		{
			e[0] *= f;
			e[1] *= f;
			e[2] *= f;
			return *this;
		}

		vector3& operator/=(const FLOAT f)
		{
			e[0] /= f;
			e[1] /= f;
			e[2] /= f;
			return *this;
		}
	public:
		FLOAT e[3];
	};

	inline void vector3::normalize()
	{
		float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
	}

	inline bool operator==(const vector3& v1, const vector3& v2)
	{
		return (fequal(v1[0], v2[0]) && fequal(v1[1], v2[1]) && fequal(v1[2], v2[2]));
	}

	inline bool operator!=(const vector3& v1, const vector3& v2)
	{
		return (!fequal(v1[0], v2[0]) || !fequal(v1[1], v2[1]) || !fequal(v1[2], v2[2]));
	}

	inline std::istream& operator>>(std::istream& is, vector3& v)
	{
		return (is >> v[0] >> v[1] >> v[2]);
	}

	inline std::ostream& operator<<(std::ostream& os, const vector3& v)
	{
		return (os << v[0] << v[1] << v[2]);
	}

	inline vector3 operator+(const vector3& v1, const vector3& v2)
	{
		return vector3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
	}

	inline vector3 operator-(const vector3& v1, const vector3& v2)
	{
		return vector3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
	}

	inline vector3 operator*(float f, const vector3& v)
	{
		return vector3(f * v.e[0], f * v.e[1], f * v.e[2]);
	}

	inline vector3 operator*(const vector3& v, float f)
	{
		return vector3(f * v.e[0], f * v.e[1], f * v.e[2]);
	}

	inline vector3 operator/(const vector3 &v, float f)
	{
		return vector3(v.e[0] / f, v.e[1] / f, v.e[2] / f);
	}

	inline vector3 normalize(const vector3& v)
	{
		float k = 1.0f / sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
		return vector3(v.e[0] * k, v.e[1] * k, v.e[2] * k);
	}

	inline float dot(const vector3& v1, const vector3& v2)
	{
		return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
	}

	inline vector3 cross(const vector3 &v1, const vector3 &v2)
	{
		return vector3(
			(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
			(v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2]),
			(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
	}

	inline vector3 reflect(const vector3& in, const vector3& normal)
	{
		// assumes unit length normal
		return in - normal * (2 * dot(in, normal));
	}
}

#endif
