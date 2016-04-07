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
			data[0] = data[1] = 0;
		}

		vector2(float f0, float f1)
		{
			data[0] = f0;
			data[1] = f1;
		}

		vector2(const vector2& v)
		{
			data[0] = v.data[0];
			data[1] = v.data[1];
		}

		float x() const
		{
			return data[0];
		}

		float y() const
		{
			return data[1];
		}

		void set_x(float f)
		{
			data[0] = f;
		}

		void set_y(float f)
		{
			data[1] = f;
		}

		FLOAT length() const
		{
			return sqrt(squraed_length());
		}

		FLOAT squraed_length() const
		{
			return data[0] * data[0] + data[1] * data[1];
		}

		void normalize();

		void scramble();

		vector2 operator+() const
		{
			return *this;
		}

		vector2 operator-() const
		{
			return vector2(-data[0], -data[1]);
		}

		FLOAT operator[](int i) const
		{
			return data[i];
		}

		FLOAT& operator[](int i)
		{
			return data[i];
		}

		vector2& operator+=(const vector2& v)
		{
			data[0] += v.data[0];
			data[1] += v.data[1];
			return *this;
		}

		vector2& operator-=(const vector2& v)
		{
			data[0] -= v.data[0];
			data[1] -= v.data[1];
			return *this;
		}

		vector2& operator+=(const FLOAT f)
		{
			data[0] += f;
			data[1] += f;
			return *this;
		}

		vector2& operator-=(const FLOAT f)
		{
			data[0] -= f;
			data[1] -= f;
			return *this;
		}

		vector2& operator*=(const FLOAT f)
		{
			data[0] *= f;
			data[1] *= f;
			return *this;
		}

		vector2& operator/=(const FLOAT f)
		{
			data[0] /= f;
			data[1] /= f;
			return *this;
		}

	public:
		FLOAT data[2];
	};

	inline void vector2::scramble()
	{
		float _x;
		float _y = data[0];

		_x = data[1] * 1234.12345054321f;
		data[0] = _x - (int)_x;
		_y = _y * 7654.54321012345f;
		data[1] = _y - (int)_y;
	}

	inline void vector2::normalize()
	{
		FLOAT len = length();
		if (len > 0)
		{
			float k = 1.0f / len;
			data[0] *= k;
			data[1] *= k;
		}
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
		return vector2(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1]);
	}

	inline vector2 operator-(const vector2& v1, const vector2& v2)
	{
		return vector2(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1]);
	}

	inline vector2 operator+(const vector2& v, float f)
	{
		return vector2(v.data[0] + f, v.data[1] + f);
	}

	inline vector2 operator-(const vector2& v, float f)
	{
		return vector2(v.data[0] - f, v.data[1] - f);
	}

	inline vector2 operator*(float f, const vector2& v)
	{
		return vector2(v.data[0] * f, v.data[1] * f);
	}

	inline vector2 operator*(const vector2& v, float f)
	{
		return vector2(v.data[0] * f, v.data[1] * f);
	}

	inline vector2 operator/(const vector2 &v, float f)
	{
		return vector2(v.data[0] / f, v.data[1] / f);
	}

	inline vector2 min(const vector2& v1, const vector2& v2)
	{
		return vector2(min(v1.x(), v2.x()), min(v1.y(), v2.y()));
	}

	inline vector2 max(const vector2& v1, const vector2& v2)
	{
		return vector2(max(v1.x(), v2.x()), max(v1.y(), v2.y()));
	}

	inline vector2 unit(const vector2& v)
	{
		float k = 1.0f / sqrt(v.data[0] * v.data[0] + v.data[1] * v.data[1]);
		return vector2(v.data[0] * k, v.data[1] * k);
	}

	inline float dot(const vector2& v1, const vector2& v2)
	{
		return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1];
	}
}

#endif
