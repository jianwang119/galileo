
//  ONB.cc
#include "ONB.h"

#define ONB_EPSILON 0.01f 

void ONB::initFromU( const Vector3& u ) {
   Vector3 n(1.0f, 0.0f, 0.0f);
   Vector3 m(0.0f, 1.0f, 0.0f);
   
   U = unitVector(u);
   V = cross(U, n);
   if (V.length() < ONB_EPSILON)
      V = cross(U, m); 
   W = cross( U, V );
}

void  ONB::initFromV( const Vector3& v ) {
   Vector3 n(1.0f, 0.0f, 0.0f);
   Vector3 m(0.0f, 1.0f, 0.0f);
   
   V = unitVector(v);
   U = cross(V, n);
   if (U.squaredLength() < ONB_EPSILON)
      U = cross(V, m); 
   W = cross(U, V);
}

void  ONB::initFromW( const Vector3& w ) {
   Vector3 n(1.0f, 0.0f, 0.0f);
   Vector3 m(0.0f, 1.0f, 0.0f);
   
   W = unitVector(w);
   U = cross(W, n);
   if (U.length() < ONB_EPSILON)
      U = cross(W, m); 
   V = cross(W, U);
}

void ONB::initFromUV( const Vector3& u, const Vector3& v ) {
   U = unitVector( u );
   W = unitVector( cross(u, v) );
   V = cross( W, U);
}

void ONB::initFromVU( const Vector3& v, const Vector3& u ) {
   V = unitVector( v );
   W = unitVector( cross(u, v) );
   U = cross( V, W );
}

void ONB::initFromUW( const Vector3& u, const Vector3& w ) {
   U = unitVector( u );
   V = unitVector( cross(w, u) );
   W = cross( U, V );
}

void  ONB::initFromWU( const Vector3& w, const Vector3& u ) {
   W = unitVector( w );
   V = unitVector( cross(w, u) );
   U = cross(V, W);
}

void  ONB::initFromVW( const Vector3& v, const Vector3& w ) {
   V = unitVector( v );
   U = unitVector( cross(v, w) );
   W = cross( U, V );
}

void ONB::initFromWV( const Vector3& w, const Vector3& v ) {
   W = unitVector( w );
   U = unitVector( cross(v, w) );
   V = cross( W, U );
}

bool  operator==( const ONB & o1, const ONB & o2 )
{ return( o1.u() == o2.u() && o1.v() == o2.v() && o1.w() == o2.w()); }

istream & operator>>( istream & is, ONB & t ) {
   Vector3 new_u, new_v, new_w;
   is >> new_u >> new_v >> new_w;
   t.initFromUV( new_u, new_v );

   return is;
}

ostream & operator<<( ostream & os, const ONB & t ) {
   os << t.u() << "\n" << t.v() << "\n" << t.w() << "\n";
   return os;
}


