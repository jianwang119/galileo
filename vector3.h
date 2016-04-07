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
			data[0] = data[1] = data[2] = 0;
		}

		vector3(float f0, float f1, float f2)
		{
			data[0] = f0;
			data[1] = f1;
			data[2] = f2;
		}

		vector3(const vector3& v)
		{
			data[0] = v.data[0];
			data[1] = v.data[1];
			data[2] = v.data[2];
		}

		float x() const
		{
			return data[0];
		}

		float y() const
		{
			return data[1];
		}

		float z() const
		{
			return data[2];
		}

		void set_x(float f)
		{
			data[0] = f;
		}

		void set_y(float f)
		{
			data[1] = f;
		}

		void set_z(float f)
		{
			data[2] = f;
		}

		FLOAT length() const
		{
			return sqrt(squared_length());
		}

		FLOAT squared_length() const
		{
			return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
		}

		void normalize();

		FLOAT min_component() const
		{
			return data[index_Of_min_component()];
		}

		FLOAT max_component() const
		{
			return data[index_of_max_component()];
		}

		FLOAT min_abs_component() const
		{
			return data[index_of_min_abs_component()];
		}

		FLOAT max_abs_component() const
		{
			return data[index_of_max_abs_component()];
		}
		
		int index_Of_min_component() const
		{
			return (data[0] < data[1] && data[0] < data[2]) ? 0 : (data[1] < data[2] ? 1 : 2);
		}

		int index_of_min_abs_component() const
		{
			if (fabs(data[0]) < fabs(data[1]) && fabs(data[0]) < fabs(data[2]))
				return 0;
			else if (fabs(data[1]) < fabs(data[2]))
				return 1;
			else
				return 2;
		}

		int index_of_max_component() const
		{
			return (data[0] > data[1] && data[0] > data[2]) ? 0 : (data[1] > data[2] ? 1 : 2);
		}

		int index_of_max_abs_component() const
		{
			if (fabs(data[0]) > fabs(data[1]) && fabs(data[0]) > fabs(data[2]))
				return 0;
			else if (fabs(data[1]) > fabs(data[2]))
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
			return vector3(-data[0], -data[1], -data[2]);
		}

		FLOAT operator[](int i) const
		{
			return data[i];
		}

		FLOAT& operator[](int i)
		{
			return data[i];
		}

		vector3& operator+=(const vector3& v)
		{
			data[0] += v.data[0];
			data[1] += v.data[1];
			data[2] += v.data[2];
			return *this;
		}

		vector3& operator-=(const vector3& v)
		{
			data[0] -= v.data[0];
			data[1] -= v.data[1];
			data[2] -= v.data[2];
			return *this;
		}

		vector3& operator+=(FLOAT f)
		{
			data[0] += f;
			data[1] += f;
			data[2] += f;
			return *this;
		}

		vector3& operator-=(FLOAT f)
		{
			data[0] -= f;
			data[1] -= f;
			data[2] -= f;
			return *this;
		}

		vector3& operator*=(const FLOAT f)
		{
			data[0] *= f;
			data[1] *= f;
			data[2] *= f;
			return *this;
		}

		vector3& operator/=(const FLOAT f)
		{
			data[0] /= f;
			data[1] /= f;
			data[2] /= f;
			return *this;
		}
	public:
		FLOAT data[3];
	};

	inline void vector3::normalize()
	{
		FLOAT len = length();
		if (len > 0)
		{
			float k = 1.0f / len;
			data[0] *= k;
			data[1] *= k;
			data[2] *= k;
		}
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
		return vector3(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1], v1.data[2] + v2.data[2]);
	}

	inline vector3 operator-(const vector3& v1, const vector3& v2)
	{
		return vector3(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1], v1.data[2] - v2.data[2]);
	}

	inline vector3 operator+(const vector3& v, float f)
	{
		return vector3(v.data[0] + f, v.data[1] + f, v.data[2] + f);
	}

	inline vector3 operator-(const vector3& v, float f)
	{
		return vector3(v.data[0] - f, v.data[1] - f, v.data[2] - f);
	}

	inline vector3 operator*(float f, const vector3& v)
	{
		return vector3(v.data[0] * f, v.data[1] * f, v.data[2] * f);
	}

	inline vector3 operator*(const vector3& v, float f)
	{
		return vector3(v.data[0] * f, v.data[1] * f, v.data[2] * f);
	}

	inline vector3 operator/(const vector3 &v, float f)
	{
		return vector3(v.data[0] / f, v.data[1] / f, v.data[2] / f);
	}

	inline vector3 min(const vector3& v1, const vector3& v2)
	{
		return vector3(min(v1.x(), v2.x()), min(v1.y(), v2.y()), min(v1.z(), v2.z()));
	}

	inline vector3 max(const vector3& v1, const vector3& v2)
	{
		return vector3(max(v1.x(), v2.x()), max(v1.y(), v2.y()), max(v1.z(), v2.z()));
	}
	
	inline vector3 normalize(const vector3& v)
	{
		float k = 1.0f / sqrt(v.data[0] * v.data[0] + v.data[1] * v.data[1] + v.data[2] * v.data[2]);
		return vector3(v.data[0] * k, v.data[1] * k, v.data[2] * k);
	}

	inline float dot(const vector3& v1, const vector3& v2)
	{
		return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] + v1.data[2] * v2.data[2];
	}

	inline vector3 cross(const vector3 &v1, const vector3 &v2)
	{
		return vector3(
			(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1]),
			(v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2]),
			(v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]));
	}

	inline vector3 reflect(const vector3& in, const vector3& normal)
	{
		// assumes unit length normal
		return in - normal * (2 * dot(in, normal));
	}
}

#endif
