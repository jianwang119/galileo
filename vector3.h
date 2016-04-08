#ifndef _VECTOR3_H
#define _VECTOR3_H

#include "global_define.h"
#include "math_utils.h"

namespace galileo
{
	class c_vector3
	{
	public:
		c_vector3()
		{
			data[0] = data[1] = data[2] = 0;
		}

		c_vector3(t_float f0, t_float f1, t_float f2)
		{
			data[0] = f0;
			data[1] = f1;
			data[2] = f2;
		}

		c_vector3(const c_vector3& v)
		{
			data[0] = v.data[0];
			data[1] = v.data[1];
			data[2] = v.data[2];
		}

		t_float x() const
		{
			return data[0];
		}

		t_float y() const
		{
			return data[1];
		}

		t_float z() const
		{
			return data[2];
		}

		void set_x(t_float f)
		{
			data[0] = f;
		}

		void set_y(t_float f)
		{
			data[1] = f;
		}

		void set_z(t_float f)
		{
			data[2] = f;
		}

		t_float length() const
		{
			return sqrt(squared_length());
		}

		t_float squared_length() const
		{
			return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
		}

		void normalize();

		t_float min_component() const
		{
			return data[index_Of_min_component()];
		}

		t_float max_component() const
		{
			return data[index_of_max_component()];
		}

		t_float min_abs_component() const
		{
			return data[index_of_min_abs_component()];
		}

		t_float max_abs_component() const
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

		c_vector3 operator+() const
		{
			return *this;
		}

		c_vector3 operator-() const
		{
			return c_vector3(-data[0], -data[1], -data[2]);
		}

		t_float operator[](int i) const
		{
			return data[i];
		}

		t_float& operator[](int i)
		{
			return data[i];
		}

		c_vector3& operator+=(const c_vector3& v)
		{
			data[0] += v.data[0];
			data[1] += v.data[1];
			data[2] += v.data[2];
			return *this;
		}

		c_vector3& operator-=(const c_vector3& v)
		{
			data[0] -= v.data[0];
			data[1] -= v.data[1];
			data[2] -= v.data[2];
			return *this;
		}

		c_vector3& operator+=(t_float f)
		{
			data[0] += f;
			data[1] += f;
			data[2] += f;
			return *this;
		}

		c_vector3& operator-=(t_float f)
		{
			data[0] -= f;
			data[1] -= f;
			data[2] -= f;
			return *this;
		}

		c_vector3& operator*=(const t_float f)
		{
			data[0] *= f;
			data[1] *= f;
			data[2] *= f;
			return *this;
		}

		c_vector3& operator/=(const t_float f)
		{
			data[0] /= f;
			data[1] /= f;
			data[2] /= f;
			return *this;
		}
	public:
		t_float data[3];
	};

	inline void c_vector3::normalize()
	{
		t_float len = length();
		if (len > 0)
		{
			t_float k = 1.0f / len;
			data[0] *= k;
			data[1] *= k;
			data[2] *= k;
		}
	}

	inline bool operator==(const c_vector3& v1, const c_vector3& v2)
	{
		return (fequal(v1[0], v2[0]) && fequal(v1[1], v2[1]) && fequal(v1[2], v2[2]));
	}

	inline bool operator!=(const c_vector3& v1, const c_vector3& v2)
	{
		return (!fequal(v1[0], v2[0]) || !fequal(v1[1], v2[1]) || !fequal(v1[2], v2[2]));
	}

	inline std::istream& operator>>(std::istream& is, c_vector3& v)
	{
		return (is >> v[0] >> v[1] >> v[2]);
	}

	inline std::ostream& operator<<(std::ostream& os, const c_vector3& v)
	{
		return (os << v[0] << v[1] << v[2]);
	}

	inline c_vector3 operator+(const c_vector3& v1, const c_vector3& v2)
	{
		return c_vector3(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1], v1.data[2] + v2.data[2]);
	}

	inline c_vector3 operator-(const c_vector3& v1, const c_vector3& v2)
	{
		return c_vector3(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1], v1.data[2] - v2.data[2]);
	}

	inline c_vector3 operator+(const c_vector3& v, t_float f)
	{
		return c_vector3(v.data[0] + f, v.data[1] + f, v.data[2] + f);
	}

	inline c_vector3 operator-(const c_vector3& v, t_float f)
	{
		return c_vector3(v.data[0] - f, v.data[1] - f, v.data[2] - f);
	}

	inline c_vector3 operator*(t_float f, const c_vector3& v)
	{
		return c_vector3(v.data[0] * f, v.data[1] * f, v.data[2] * f);
	}

	inline c_vector3 operator*(const c_vector3& v, t_float f)
	{
		return c_vector3(v.data[0] * f, v.data[1] * f, v.data[2] * f);
	}

	inline c_vector3 operator/(const c_vector3 &v, t_float f)
	{
		return c_vector3(v.data[0] / f, v.data[1] / f, v.data[2] / f);
	}

	inline c_vector3 min(const c_vector3& v1, const c_vector3& v2)
	{
		return c_vector3(min(v1.x(), v2.x()), min(v1.y(), v2.y()), min(v1.z(), v2.z()));
	}

	inline c_vector3 max(const c_vector3& v1, const c_vector3& v2)
	{
		return c_vector3(max(v1.x(), v2.x()), max(v1.y(), v2.y()), max(v1.z(), v2.z()));
	}
	
	inline c_vector3 normalize(const c_vector3& v)
	{
		t_float k = 1.0f / sqrt(v.data[0] * v.data[0] + v.data[1] * v.data[1] + v.data[2] * v.data[2]);
		return c_vector3(v.data[0] * k, v.data[1] * k, v.data[2] * k);
	}

	inline t_float dot(const c_vector3& v1, const c_vector3& v2)
	{
		return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] + v1.data[2] * v2.data[2];
	}

	inline c_vector3 cross(const c_vector3 &v1, const c_vector3 &v2)
	{
		return c_vector3(
			(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1]),
			(v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2]),
			(v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]));
	}

	inline c_vector3 reflect(const c_vector3& in, const c_vector3& normal)
	{
		// assumes unit length normal
		return in - normal * (2 * dot(in, normal));
	}
}

#endif
