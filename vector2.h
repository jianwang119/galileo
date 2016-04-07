#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "global_define.h"
#include "math_utils.h"

namespace galileo
{
	class vector2
	{
	public:
		vector2()
		{
			e[0] = e[1] = 0;
		}

		vector2(float e0, float e1)
		{
			e[0] = e0;
			e[1] = e1;
		}

		vector2(const vector2& v)
		{
			e[0] = v.e[0];
			e[1] = v.e[1];
		}

		float x() const
		{
			return e[0];
		}

		float y() const
		{
			return e[1];
		}

		void set_x(float f)
		{
			e[0] = f;
		}

		void set_y(float f)
		{
			e[1] = f;
		}

		FLOAT length() const
		{
			return sqrt(e[0] * e[0] + e[1] * e[1]);
		}

		FLOAT squraed_length() const
		{
			return e[0] * e[0] + e[1] * e[1];
		}

		void normalize();

		void scramble();

		vector2 operator+() const
		{
			return *this;
		}

		vector2 operator-() const
		{
			return vector2(-e[0], -e[1]);
		}

		FLOAT operator[](int i) const
		{
			return e[i];
		}

		FLOAT& operator[](int i)
		{
			return e[i];
		}

		vector2& operator+=(const vector2& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			return *this;
		}

		vector2& operator-=(const vector2& v)
		{
			e[0] -= v.e[0];
			e[1] -= v.e[1];
			return *this;
		}

		vector2& operator*=(const FLOAT f)
		{
			e[0] *= f;
			e[1] *= f;
			return *this;
		}

		vector2& operator/=(const FLOAT f)
		{
			e[0] /= f;
			e[1] /= f;
			return *this;
		}
	public:
		FLOAT e[2];
	};

	inline void vector2::scramble()
	{
		float _x;
		float _y = e[0];

		_x = e[1] * 1234.12345054321f;
		e[0] = _x - (int)_x;
		_y = _y * 7654.54321012345f;
		e[1] = _y - (int)_y;
	}

	inline void vector2::normalize()
	{
		float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1]);
		e[0] *= k;
		e[1] *= k;
	}

	inline bool operator==(const vector2& v1, const vector2& v2)
	{
		return (fequal(v1[0], v2[0]) && fequal(v1[1], v2[1]));
	}

	inline bool operator!=(const vector2& v1, const vector2& v2)
	{
		return (!fequal(v1[0], v2[0]) || !fequal(v1[1], v2[1]));
	}

	inline std::istream& operator>>(std::istream& is, vector2& v)
	{
		return (is >> v[0] >> v[1]);
	}

	inline std::ostream& operator<<(std::ostream& os, const vector2& v)
	{
		return (os << v[0] << v[1]);
	}

	inline vector2 operator+(const vector2& v1, const vector2& v2)
	{
		return vector2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
	}

	inline vector2 operator-(const vector2& v1, const vector2& v2)
	{
		return vector2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
	}

	inline vector2 operator*(float f, const vector2& v)
	{
		return vector2(f * v.e[0], f * v.e[1]);
	}

	inline vector2 operator*(const vector2& v, float f)
	{
		return vector2(f * v.e[0], f * v.e[1]);
	}

	inline vector2 operator/(const vector2 &v, float f)
	{
		return vector2(v.e[0] / f, v.e[1] / f);
	}

	inline vector2 unit(const vector2& v)
	{
		float k = 1.0f / sqrt(v.e[0] * v.e[0] + v.e[1] * v.e[1]);
		return vector2(v.e[0] * k, v.e[1] * k);
	}

	inline float dot(const vector2& v1, const vector2& v2)
	{
		return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1];
	}
}

#endif
