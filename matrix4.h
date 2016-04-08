#ifndef _MATRIX4_H
#define _MATRIX4_H

#include "math_utils.h"
#include "vector3.h"

namespace galileo
{
	class c_matrix4
	{
	public:
		c_matrix4()
		{
		}

		c_matrix4(const c_matrix4& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] = m.data[i][j];
		}

		void inverse();
		void transpose();
		t_float determinant();

		inline c_matrix4 get_inverse()
		{
			c_matrix4 ret = *this;
			ret.inverse();
			return ret;
		}

		inline c_matrix4 get_transpose()
		{
			c_matrix4 ret = *this;
			ret.transpose();
			return ret;
		}

		c_matrix4& operator+=(const c_matrix4& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] += m.data[i][j];
			return *this;
		}

		c_matrix4& operator-=(const c_matrix4& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] -= m.data[i][j];
			return *this;
		}

		c_matrix4& operator*=(const c_matrix4& m)
		{
			c_matrix4 ret = *this;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					t_float sum = 0;
					for (int k = 0; k < 4; k++)
						sum += ret.data[i][k] * m.data[k][j];
					data[i][j] = sum;
				}
			return *this;
		}

		c_matrix4& operator*=(t_float f)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] *= f;
			return *this;
		}

	public:
		t_float data[4][4];

	public:
		static c_matrix4 zero()
		{
			c_matrix4 ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.data[i][j] = 0.0f;
			return ret;
		}

		static c_matrix4 identity()
		{
			c_matrix4 ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.data[i][j] = 0.0f;
			ret.data[0][0] = 1.0;
			ret.data[1][1] = 1.0;
			ret.data[2][2] = 1.0;
			ret.data[3][3] = 1.0;
			return ret;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const c_matrix4& m)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				os << m.data[i][j];
		return os;
	}

	inline c_matrix4 operator+(const c_matrix4& m1, const c_matrix4& m2)
	{
		c_matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.data[i][j] = m1.data[i][j] + m2.data[i][j];
		return ret;
	}

	inline c_matrix4 operator-(const c_matrix4& m1, const c_matrix4& m2)
	{
		c_matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.data[i][j] = m1.data[i][j] - m2.data[i][j];
		return ret;
	}

	inline c_matrix4 operator*(const c_matrix4& m1, const c_matrix4& m2)
	{
		c_matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				t_float subt = 0.0;
				for (int k = 0; k < 4; k++)
					subt += m1.data[i][k] * m2.data[k][j];
				ret.data[i][j] = subt;
			}
		return ret;
	}

	inline c_vector3 operator*(const c_matrix4& m, const c_vector3& v)
	{
		c_vector3 ret;
		t_float temp;
		ret[0] = v[0] * m.data[0][0] + v[1] * m.data[0][1] + v[2] * m.data[0][2] + m.data[0][3];
		ret[1] = v[0] * m.data[1][0] + v[1] * m.data[1][1] + v[2] * m.data[1][2] + m.data[1][3];
		ret[2] = v[0] * m.data[2][0] + v[1] * m.data[2][1] + v[2] * m.data[2][2] + m.data[2][3];
		temp   = v[0] * m.data[3][0] + v[1] * m.data[3][1] + v[2] * m.data[3][2] + m.data[3][3];
		ret /= temp;
		return ret;
	}
	
	inline c_matrix4 operator* (const c_matrix4 & m, t_float f)
	{
		c_matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.data[i][j] = m.data[i][j] * f;
		return ret;
	}

	inline c_vector3 transform_point(const c_matrix4& m, const c_vector3& pt)
	{
		return m * pt;
	}

	inline c_vector3 transform_vector(const c_matrix4& m, const c_vector3& v)
	{
		c_vector3 ret;
		ret[0] = v[0] * m.data[0][0] + v[1] * m.data[0][1] + v[2] * m.data[0][2];
		ret[1] = v[0] * m.data[1][0] + v[1] * m.data[1][1] + v[2] * m.data[1][2];
		ret[2] = v[0] * m.data[2][0] + v[1] * m.data[2][1] + v[2] * m.data[2][2];
		return ret;
	}

	inline c_matrix4 translate(t_float x, t_float y, t_float z)
	{
		c_matrix4 ret = c_matrix4::identity();
		ret.data[0][3] = x;
		ret.data[1][3] = y;
		ret.data[2][3] = z;
		return ret;

	}

	inline c_matrix4 scale(t_float x, t_float y, t_float z)
	{
		c_matrix4 ret = c_matrix4::zero();
		ret.data[0][0] = x;
		ret.data[1][1] = y;
		ret.data[2][2] = z;
		ret.data[3][3] = 1.0;
		return ret;
	}

	inline c_matrix4 rotateX(t_float radian)
	{
		c_matrix4 ret = c_matrix4::identity();
		t_float cosine = cos(radian);
		t_float sine = sin(radian);
		ret.data[1][1] = cosine;
		ret.data[1][2] = -sine;
		ret.data[2][1] = sine;
		ret.data[2][2] = cosine;
		return ret;
	}

	inline c_matrix4 rotateY(t_float radian)
	{
		c_matrix4 ret = c_matrix4::identity();
		t_float cosine = cos(radian);
		t_float sine = sin(radian);
		ret.data[0][0] = cosine;
		ret.data[0][2] = sine;
		ret.data[2][0] = -sine;
		ret.data[2][2] = cosine;
		return ret;
	}

	inline c_matrix4 rotateZ(t_float radian)
	{
		c_matrix4 ret = c_matrix4::identity();
		t_float cosine = cos(radian);
		t_float sine = sin(radian);
		ret.data[0][0] = cosine;
		ret.data[0][1] = -sine;
		ret.data[1][0] = sine;
		ret.data[1][1] = cosine;
		return ret;
	}

	c_matrix4 rotate(const c_vector3 & axis, t_float angle);

	c_matrix4 view(const c_vector3& eye, const c_vector3 & lookat, const c_vector3& up);
}

#endif
