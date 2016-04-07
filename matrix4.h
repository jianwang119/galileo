#ifndef _MATRIX4_H
#define _MATRIX4_H

#include "math_utils.h"
#include "vector3.h"

namespace galileo
{
	class matrix4
	{
	public:
		matrix4()
		{
		}

		matrix4(const matrix4& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] = m.data[i][j];
		}

		void inverse();
		void transpose();
		float determinant();

		inline matrix4 get_inverse()
		{
			matrix4 ret = *this;
			ret.inverse();
			return ret;
		}

		inline matrix4 get_transpose()
		{
			matrix4 ret = *this;
			ret.transpose();
			return ret;
		}

		matrix4& operator+=(const matrix4& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] += m.data[i][j];
			return *this;
		}

		matrix4& operator-=(const matrix4& m)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] -= m.data[i][j];
			return *this;
		}

		matrix4& operator*=(const matrix4& m)
		{
			matrix4 ret = *this;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					float sum = 0;
					for (int k = 0; k < 4; k++)
						sum += ret.data[i][k] * m.data[k][j];
					data[i][j] = sum;
				}
			return *this;
		}

		matrix4& operator*=(FLOAT f)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					data[i][j] *= f;
			return *this;
		}

	public:
		float data[4][4];

	public:
		static matrix4 zero()
		{
			matrix4 ret;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					ret.data[i][j] = 0.0f;
			return ret;
		}

		static matrix4 identity()
		{
			matrix4 ret;
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

	inline std::ostream& operator<<(std::ostream& os, const matrix4& m)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				os << m.data[i][j];
		return os;
	}

	inline matrix4 operator+(const matrix4& m1, const matrix4& m2)
	{
		matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.data[i][j] = m1.data[i][j] + m2.data[i][j];
		return ret;
	}

	inline matrix4 operator-(const matrix4& m1, const matrix4& m2)
	{
		matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.data[i][j] = m1.data[i][j] - m2.data[i][j];
		return ret;
	}

	inline matrix4 operator*(const matrix4& m1, const matrix4& m2)
	{
		matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				float subt = 0.0;
				for (int k = 0; k < 4; k++)
					subt += m1.data[i][k] * m2.data[k][j];
				ret.data[i][j] = subt;
			}
		return ret;
	}

	inline vector3 operator*(const matrix4& m, const vector3& v)
	{
		vector3 ret;
		float temp;
		ret[0] = v[0] * m.data[0][0] + v[1] * m.data[0][1] + v[2] * m.data[0][2] + m.data[0][3];
		ret[1] = v[0] * m.data[1][0] + v[1] * m.data[1][1] + v[2] * m.data[1][2] + m.data[1][3];
		ret[2] = v[0] * m.data[2][0] + v[1] * m.data[2][1] + v[2] * m.data[2][2] + m.data[2][3];
		temp   = v[0] * m.data[3][0] + v[1] * m.data[3][1] + v[2] * m.data[3][2] + m.data[3][3];
		ret /= temp;
		return ret;
	}
	
	inline matrix4 operator* (const matrix4 & m, float f)
	{
		matrix4 ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				ret.data[i][j] = m.data[i][j] * f;
		return ret;
	}

	inline vector3 transform_point(const matrix4& m, const vector3& pt)
	{
		return m * pt;
	}

	inline vector3 transform_vector(const matrix4& m, const vector3& v)
	{
		vector3 ret;
		ret[0] = v[0] * m.data[0][0] + v[1] * m.data[0][1] + v[2] * m.data[0][2];
		ret[1] = v[0] * m.data[1][0] + v[1] * m.data[1][1] + v[2] * m.data[1][2];
		ret[2] = v[0] * m.data[2][0] + v[1] * m.data[2][1] + v[2] * m.data[2][2];
		return ret;
	}

	inline matrix4 translate(FLOAT x, FLOAT y, FLOAT z)
	{
		matrix4 ret = matrix4::identity();
		ret.data[0][3] = x;
		ret.data[1][3] = y;
		ret.data[2][3] = z;
		return ret;

	}

	inline matrix4 scale(FLOAT x, FLOAT y, FLOAT z)
	{
		matrix4 ret = matrix4::zero();
		ret.data[0][0] = x;
		ret.data[1][1] = y;
		ret.data[2][2] = z;
		ret.data[3][3] = 1.0;
		return ret;
	}

	inline matrix4 rotateX(FLOAT radian)
	{
		matrix4 ret = matrix4::identity();
		float cosine = cos(radian);
		float sine = sin(radian);
		ret.data[1][1] = cosine;
		ret.data[1][2] = -sine;
		ret.data[2][1] = sine;
		ret.data[2][2] = cosine;
		return ret;
	}

	inline matrix4 rotateY(FLOAT radian)
	{
		matrix4 ret = matrix4::identity();
		float cosine = cos(radian);
		float sine = sin(radian);
		ret.data[0][0] = cosine;
		ret.data[0][2] = sine;
		ret.data[2][0] = -sine;
		ret.data[2][2] = cosine;
		return ret;
	}

	inline matrix4 rotateZ(FLOAT radian)
	{
		matrix4 ret = matrix4::identity();
		float cosine = cos(radian);
		float sine = sin(radian);
		ret.data[0][0] = cosine;
		ret.data[0][1] = -sine;
		ret.data[1][0] = sine;
		ret.data[1][1] = cosine;
		return ret;
	}

	matrix4 rotate(const vector3 & axis, FLOAT angle);

	matrix4 view(const vector3& eye, const vector3 & lookat, const vector3& up);
}

#endif
