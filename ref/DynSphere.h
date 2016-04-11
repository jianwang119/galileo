
/*****************************************************************************\
 *                                                                           *
 * filename : DynSphere.h                                                    *
 * author   : R. Keith Morley                                                *
 * last mod : 10/10/02                                                       *
 *                                                                           *
 * Sphere class for use in raytracing                                        *
 *                                                                           *
\*****************************************************************************/

#ifndef _DYN_SPHERE_H_
#define _DYN_SPHERE_H_

#include "Surface.h"
#include "Vector3.h"
#include "Ray.h"
#include "rgb.h"
#include "BBox.h"

class DynSphere : public Surface
{
public:
   DynSphere(const Vector3& _ocenter, float _radius, Material* _mat_ptr, 
         float mintime, float maxtime, Vector3(*_getCenter)(float, Vector3));
   bool hit(const Ray& r, float tmin, float tmax, float time, 
         SurfaceHitRecord& rec) const;
   bool shadowHit(const Ray& r, float tmin, float tmax, float time) const;
   BBox boundingBox(float time0, float time1) const;
   virtual bool randomPoint(const Vector3&,  const Vector2&,  float time,
         Vector3&, Vector3&, float&, rgb&) const { return false;}

   
   Vector3(*getCenter)(float, Vector3); 
   
   Vector3 ocenter;
   float mintime;
   float maxtime;
   float radius;
   Material* mat_ptr;
};

#endif // _DYN_SPHERE_H__
