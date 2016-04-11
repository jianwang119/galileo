
/******************************************************************************\
 *                                                                            *
 *  filename   : Matrix.h                                                     *
 *  author     : R. Keith Morley                                              *
 *  last mod   : 2/28/02                                                      * 
 *                                                                            *
 *  Matrix class for use in graphics applications                             *
 *                                                                            * 
\******************************************************************************/

#ifndef _MATRIX_H_
#define _MATRIX_H_ 1

#include <Vector3.h>
#include <iostream.h>
#include <iomanip.h>
#include <math.h>

class Matrix
{
public:
   Matrix() {}
   Matrix(const Matrix & orig);
   
   void invert();
   void transpose();
   Matrix getInverse()const;
   Matrix getTranspose()const;
   
   Matrix & operator+= (const Matrix& right_op);
   Matrix & operator-= (const Matrix& right_op);
   Matrix & operator*= (const Matrix& right_op);
   Matrix & operator*= (float right_op);

   friend Matrix operator- (const Matrix& left_op, const Matrix& right_op);
   friend Matrix operator+ (const Matrix& left_op, const Matrix& right_op);
   friend Matrix operator* (const Matrix& left_op, const Matrix& right_op);
   // matrix mult. performed left to right
   friend Vector3 operator* (const Matrix& left_op, const Vector3& right_op);
   // transform vector by a matrix
   friend Matrix operator* (const Matrix & left_op, float right_op);

   friend Vector3 transformLoc(const Matrix& left_op, const Vector3& right_op); 
   friend Vector3 transformVec(const Matrix& left_op, const Vector3& right_op); 
   
   friend Matrix zeroMatrix();
   friend Matrix identityMatrix();
   friend Matrix translate(float _x, float _y, float _z);
   friend Matrix scale(float _x, float _y, float _z);
   friend Matrix rotate(const Vector3 & axis, float angle);
   friend Matrix rotateX(float angle);    //
   friend Matrix rotateY(float angle);    // More efficient than arbitrary axis
   friend Matrix rotateZ(float angle);    //
   friend Matrix viewMatrix(const Vector3& eye, const Vector3 & gaze, 
         const Vector3& up);
   friend ostream & operator<< (ostream& out, const Matrix& right_op);

   float determinant(); 
   float x[4][4];
};

// 3x3 matrix determinant -- helper function 
inline float det3 (float a, float b, float c, 
                   float d, float e, float f, 
                   float g, float h, float i)
{ return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f; }

#endif   // _MATRIX_H_
