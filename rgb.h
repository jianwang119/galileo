#ifndef _RGB_H
#define _RGB_H

#include "global_define.h"
#include "math_utils.h"

namespace galileo
{
	class c_rgb
	{
	public:
		c_rgb()
		{
		}

		c_rgb(t_float r, t_float b, t_float a)
		{
			data[0] = r;
			data[1] = b;
			data[2] = a;
		}

		c_rgb(const c_rgb& c)
		{
			data[0] = c.data[0];
			data[1] = c.data[1];
			data[2] = c.data[2];
		}

		inline void set(t_float r, t_float g, t_float b)
		{
			data[0] = r;
			data[1] = g;
			data[2] = b;
		}

		inline t_float r() const
		{
			return data[0];
		}

		inline t_float g() const
		{
			return data[1];
		}

		inline t_float b() const
		{
			return data[2];
		}

		inline void set_u8(t_u8 r, t_u8 g, t_u8 b)
		{
			data[0] = ((t_float(r) + 0.5f) / 256.0f);
			data[1] = ((t_float(g) + 0.5f) / 256.0f);
			data[2] = ((t_float(b) + 0.5f) / 256.0f);
		}

		inline t_u8 r_u8() const
		{
			t_u32 i = (t_u32)(256.0 * data[0]);
			if (i > 255) i = 255;
			return (t_u8)i;
		}

		inline t_u8 g_u8() const
		{
			t_u32 i = (t_u32)(256.0 * data[1]);
			if (i > 255) i = 255;
			return (t_u8)i;
		}

		inline t_u8 b_u8() const
		{
			t_u32 i = (t_u32)(256.0 * data[2]);
			if (i > 255) i = 255;
			return (t_u8)i;
		}

		inline void clamp()
		{
			data[0] = fclamp01(data[0]);
			data[1] = fclamp01(data[1]);
			data[2] = fclamp01(data[2]);
		}

		inline c_rgb gamma(t_float gamma = 1.0f / 2.2f) const
		{
			return c_rgb(pow(data[0], gamma), pow(data[1], gamma), pow(data[2], gamma));
		}

		c_rgb operator+() const
		{
			return c_rgb(data[0], data[1], data[2]);
		}

		c_rgb operator-() const
		{
			return c_rgb(-data[0], -data[1], -data[2]);
		}

		t_float operator[](int i) const
		{
			return data[i];
		}

		t_float& operator[](int i)
		{
			return data[i];
		}

		c_rgb& operator+=(const c_rgb& c)
		{
			data[0] += c.data[0];
			data[1] += c.data[1];
			data[2] += c.data[2];
			return *this;
		}

		c_rgb& operator-=(const c_rgb& c)
		{
			data[0] -= c.data[0];
			data[1] -= c.data[1];
			data[2] -= c.data[2];
			return *this;
		}

		c_rgb& operator*=(const c_rgb& c)
		{
			data[0] *= c.data[0];
			data[1] *= c.data[1];
			data[2] *= c.data[2];
			return *this;
		}

		c_rgb& operator/=(const c_rgb& c)
		{
			data[0] /= c.data[0];
			data[1] /= c.data[1];
			data[2] /= c.data[2];
			return *this;
		}

		c_rgb& operator*=(t_float f)
		{
			data[0] *= f;
			data[1] *= f;
			data[2] *= f;
			return *this;
		}

		c_rgb& operator/=(t_float f)
		{
			data[0] /= f;
			data[1] /= f;
			data[2] /= f;
			return *this;
		}

	public:
		t_float data[3];
	};

	inline bool operator==(const c_rgb& c1, const c_rgb& c2)
	{
		return (fequal(c1[0], c2[0]) && fequal(c1[1], c2[1]) && fequal(c1[2], c2[2]));
	}

	inline bool operator!=(const c_rgb& c1, const c_rgb& c2)
	{
		return (!fequal(c1[0], c2[0]) || !fequal(c1[1], c2[1]) || !fequal(c1[2], c2[2]));
	}

	inline std::istream& operator>>(std::istream& is, c_rgb& c)
	{
		return (is >> c[0] >> c[1] >> c[2]);
	}

	inline std::ostream& operator<<(std::ostream& os, const c_rgb& c)
	{
		return (os << c[0] << c[1] << c[2]);
	}

	inline c_rgb operator+(const c_rgb& c1, const c_rgb& c2)
	{
		return c_rgb(c1.r() + c2.r(), c1.g() + c2.g(), c1.b() + c2.b());
	}

	inline c_rgb operator-(const c_rgb& c1, const c_rgb& c2)
	{
		return c_rgb(c1.r() - c2.r(), c1.g() - c2.g(), c1.b() - c2.b());
	}

	inline c_rgb operator*(const c_rgb& c1, const c_rgb& c2)
	{
		return c_rgb(c1.r()*c2.r(), c1.g()*c2.g(), c1.b()*c2.b());
	}

	inline c_rgb operator/(const c_rgb& c1, const c_rgb& c2)
	{
		return c_rgb(c1.r() / c2.r(), c1.g() / c2.g(), c1.b() / c2.b());
	}

	inline c_rgb operator*(const c_rgb& c, t_float f)
	{
		return c_rgb(c.r() * f, c.g() * f, c.b() * f);
	}

	inline c_rgb operator*(t_float f, const c_rgb& c)
	{
		return c_rgb(c.r() * f, c.g() * f, c.b() * f);
	}

	inline c_rgb operator/(const c_rgb& c, t_float f)
	{
		return c_rgb(c.r() / f, c.g() / f, c.b() / f);
	}
}

#endif