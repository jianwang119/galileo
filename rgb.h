#ifndef _RGB_H
#define _RGB_H

#include "global_define.h"
#include "math_utils.h"

class rgb
{
public:
	rgb() 
	{
	}

	rgb(FLOAT r, FLOAT b, FLOAT a)
	{
		data[0] = r;
		data[1] = b;
		data[2] = a;	
	}

	rgb(const rgb& c)
	{
		data[0] = c.data[0];
		data[1] = c.data[1];
		data[2] = c.data[2];
	}

	inline void set(FLOAT r, FLOAT g, FLOAT b)
	{
		data[0] = r;
		data[1] = g;
		data[2] = b;
	}

	inline FLOAT r() const
	{
		return data[0];
	}

	inline FLOAT g() const
	{
		return data[1];
	}

	inline FLOAT b() const
	{
		return data[2];
	}

	inline void set_u8(U8 r, U8 g, U8 b)
	{
		data[0] = ((FLOAT(r) + 0.5f) / 256.0f);
		data[1] = ((FLOAT(g) + 0.5f) / 256.0f);
		data[2] = ((FLOAT(b) + 0.5f) / 256.0f);
	}

	inline U8 r_u8() const
	{
		U32 i = (U32)(256.0 * data[0]);
		if (i > 255) i = 255;
		return (U8)i;
	}

	inline U8 g_u8() const
	{
		U32 i = (U32)(256.0 * data[1]);
		if (i > 255) i = 255;
		return (U8)i;
	}

	inline U8 b_u8() const
	{
		U32 i = (U32)(256.0 * data[2]);
		if (i > 255) i = 255;
		return (U8)i;
	}

	inline void clamp()
	{
		data[0] = fclamp01(data[0]);
		data[1] = fclamp01(data[1]);
		data[2] = fclamp01(data[2]);
	}

	inline rgb gamma(FLOAT gamma = 1.0f / 2.2f) const
	{
		return rgb(pow(data[0], gamma), pow(data[1], gamma), pow(data[2], gamma));
	}
		
	rgb operator+() const
	{
		return rgb(data[0], data[1], data[2]);
	}

	rgb operator-() const
	{
		return rgb(-data[0], -data[1], -data[2]);
	}

	FLOAT operator[](int i) const
	{
		return data[i];
	}

	FLOAT& operator[](int i)
	{
		return data[i];
	}

	rgb& operator+=(const rgb& c)
	{
		data[0] += c.data[0];
		data[1] += c.data[1];
		data[2] += c.data[2];
		return *this;
	}

	rgb& operator-=(const rgb& c)
	{
		data[0] -= c.data[0];
		data[1] -= c.data[1];
		data[2] -= c.data[2];
		return *this;
	}

	rgb& operator*=(const rgb& c)
	{
		data[0] *= c.data[0];
		data[1] *= c.data[1];
		data[2] *= c.data[2];
		return *this;
	}

	rgb& operator/=(const rgb& c)
	{
		data[0] /= c.data[0];
		data[1] /= c.data[1];
		data[2] /= c.data[2];
		return *this;
	}

	rgb& operator*=(FLOAT f)
	{
		data[0] *= f;
		data[1] *= f;
		data[2] *= f;
		return *this;
	}

	rgb& operator/=(FLOAT f)
	{
		data[0] /= f;
		data[1] /= f;
		data[2] /= f;
		return *this;
	}

public:
	FLOAT data[3];
};

inline bool operator==(const rgb& c1, const rgb& c2)
{
	return (fequal(c1[0], c2[0]) && fequal(c1[1], c2[1]) && fequal(c1[2], c2[2]));
}

inline bool operator!=(const rgb& c1, const rgb& c2)
{
	return (!fequal(c1[0], c2[0]) || !fequal(c1[1], c2[1]) || !fequal(c1[2], c2[2]));
}

inline std::istream& operator>>(std::istream& is, rgb& c)
{
	return (is >> c[0] >> c[1] >> c[2]);
}

inline std::ostream& operator<<(std::ostream& os, const rgb& c)
{
	return (os << c[0] << c[1] << c[2]);
}

inline rgb operator+(const rgb& c1, const rgb& c2)
{
	return rgb(c1.r() + c2.r(), c1.g() + c2.g(), c1.b() + c2.b());
}

inline rgb operator-(const rgb& c1, const rgb& c2)
{
	return rgb(c1.r() - c2.r(), c1.g() - c2.g(), c1.b() - c2.b());
}

inline rgb operator*(const rgb& c1, const rgb& c2) 
{
	return rgb(c1.r()*c2.r(), c1.g()*c2.g(), c1.b()*c2.b());
}

inline rgb operator/(const rgb& c1, const rgb& c2) 
{
	return rgb(c1.r() / c2.r(), c1.g() / c2.g(), c1.b() / c2.b());
}

inline rgb operator*(const rgb& c, float f)
{
	return rgb(c.r() * f, c.g() * f, c.b() * f);
}

inline rgb operator*(float f, const rgb& c) 
{
	return rgb(c.r() * f, c.g() * f, c.b() * f);
}

inline rgb operator/(const rgb& c, float f) 
{
	return rgb(c.r() / f, c.g() / f, c.b() / f);
}

#endif