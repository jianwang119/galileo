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

	float r() const
	{
		return data[0];
	}

	float g() const
	{
		return data[1];
	}

	float b() const
	{
		return data[2];
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

inline bool operator==(rgb c1, rgb c2)
{
	return fequal(c1.r(), c2.r())&&fequal(c1.g(), c2.g())&&fequal(c1.b(), c2.b());
}

inline bool operator!=(rgb c1, rgb c2)
{
	return !(c1 == c2);
}

inline std::istream& operator>>(std::istream& is, rgb& c)
{
	return (is >> c[0] >> c[1] >> c[2]);
}

inline std::ostream& operator<<(std::ostream& os, rgb& c)
{
	return (os << c[0] << c[1] << c[2]);
}

inline rgb operator+(rgb c1, rgb c2) 
{
	return rgb(c1.r() + c2.r(), c1.g() + c2.g(), c1.b() + c2.b());
}

inline rgb operator-(rgb c1, rgb c2) 
{
	return rgb(c1.r() - c2.r(), c1.g() - c2.g(), c1.b() - c2.b());
}

inline rgb operator*(rgb c1, rgb c2) 
{
	return rgb(c1.r()*c2.r(), c1.g()*c2.g(), c1.b()*c2.b());
}

inline rgb operator/(rgb c1, rgb c2) 
{
	return rgb(c1.r() / c2.r(), c1.g() / c2.g(), c1.b() / c2.b());
}

inline rgb operator*(rgb c, float f)
{
	return rgb(c.r()*f, c.g()*f, c.b()*f);
}

inline rgb operator*(float f, rgb c) 
{
	return rgb(c.r()*f, c.g()*f, c.b()*f);
}

inline rgb operator/(rgb c, float f) 
{
	return rgb(c.r() / f, c.g() / f, c.b() / f);
}

#endif