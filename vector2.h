#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "global_define.h"
#include "math_utils.h"

namespace galileo
{
	class c_vector2
	{
	public:
		c_vector2()
		{
			data[0] = data[1] = 0;
		}

		c_vector2(t_float f0, t_float f1)
		{
			data[0] = f0;
			data[1] = f1;
		}

		c_vector2(const c_vector2& v)
		{
			data[0] = v.data[0];
			data[1] = v.data[1];
		}

		t_float x() const
		{
			return data[0];
		}

		t_float y() const
		{
			return data[1];
		}

		void set_x(t_float f)
		{
			data[0] = f;
		}

		void set_y(t_float f)
		{
			data[1] = f;
		}

		t_float length() const
		{
			return sqrt(squraed_length());
		}

		t_float squraed_length() const
		{
			return data[0] * data[0] + data[1] * data[1];
		}

		void normalize();

		void scramble();

		c_vector2 operator+() const
		{
			return *this;
		}

		c_vector2 operator-() const
		{
			return c_vector2(-data[0], -data[1]);
		}

		t_float operator[](int i) const
		{
			return data[i];
		}

		t_float& operator[](int i)
		{
			return data[i];
		}

		c_vector2& operator+=(const c_vector2& v)
		{
			data[0] += v.data[0];
			data[1] += v.data[1];
			return *this;
		}

		c_vector2& operator-=(const c_vector2& v)
		{
			data[0] -= v.data[0];
			data[1] -= v.data[1];
			return *this;
		}

		c_vector2& operator+=(const t_float f)
		{
			data[0] += f;
			data[1] += f;
			return *this;
		}

		c_vector2& operator-=(const t_float f)
		{
			data[0] -= f;
			data[1] -= f;
			return *this;
		}

		c_vector2& operator*=(const t_float f)
		{
			data[0] *= f;
			data[1] *= f;
			return *this;
		}

		c_vector2& operator/=(const t_float f)
		{
			data[0] /= f;
			data[1] /= f;
			return *this;
		}

	public:
		t_float data[2];
	};

	inline void c_vector2::scramble()
	{
		t_float _x;
		t_float _y = data[0];

		_x = data[1] * 1234.12345054321f;
		data[0] = _x - (int)_x;
		_y = _y * 7654.54321012345f;
		data[1] = _y - (int)_y;
	}

	inline void c_vector2::normalize()
	{
		t_float len = length();
		if (len > 0)
		{
			t_float k = 1.0f / len;
			data[0] *= k;
			data[1] *= k;
		}
	}

	inline bool operator==(const c_vector2& v1, const c_vector2& v2)
	{
		return (fequal(v1[0], v2[0]) && fequal(v1[1], v2[1]));
	}

	inline bool operator!=(const c_vector2& v1, const c_vector2& v2)
	{
		return (!fequal(v1[0], v2[0]) || !fequal(v1[1], v2[1]));
	}

	inline std::istream& operator>>(std::istream& is, c_vector2& v)
	{
		return (is >> v[0] >> v[1]);
	}

	inline std::ostream& operator<<(std::ostream& os, const c_vector2& v)
	{
		return (os << v[0] << v[1]);
	}

	inline c_vector2 operator+(const c_vector2& v1, const c_vector2& v2)
	{
		return c_vector2(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1]);
	}

	inline c_vector2 operator-(const c_vector2& v1, const c_vector2& v2)
	{
		return c_vector2(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1]);
	}

	inline c_vector2 operator+(const c_vector2& v, t_float f)
	{
		return c_vector2(v.data[0] + f, v.data[1] + f);
	}

	inline c_vector2 operator-(const c_vector2& v, t_float f)
	{
		return c_vector2(v.data[0] - f, v.data[1] - f);
	}

	inline c_vector2 operator*(t_float f, const c_vector2& v)
	{
		return c_vector2(v.data[0] * f, v.data[1] * f);
	}

	inline c_vector2 operator*(const c_vector2& v, t_float f)
	{
		return c_vector2(v.data[0] * f, v.data[1] * f);
	}

	inline c_vector2 operator/(const c_vector2 &v, t_float f)
	{
		return c_vector2(v.data[0] / f, v.data[1] / f);
	}

	inline c_vector2 min(const c_vector2& v1, const c_vector2& v2)
	{
		return c_vector2(min(v1.x(), v2.x()), min(v1.y(), v2.y()));
	}

	inline c_vector2 max(const c_vector2& v1, const c_vector2& v2)
	{
		return c_vector2(max(v1.x(), v2.x()), max(v1.y(), v2.y()));
	}

	inline c_vector2 unit(const c_vector2& v)
	{
		t_float k = 1.0f / sqrt(v.data[0] * v.data[0] + v.data[1] * v.data[1]);
		return c_vector2(v.data[0] * k, v.data[1] * k);
	}

	inline t_float dot(const c_vector2& v1, const c_vector2& v2)
	{
		return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1];
	}
}

#endif
