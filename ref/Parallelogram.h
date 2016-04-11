
/*****************************************************************************\
 *                                                                           *
 *  filename : Parallelogram.h                                               *
 *  author   : R. Keith Morley                                               *
 *  last mod : 10/04/02                                                      *
 *                                                                           *
\*****************************************************************************/ 

#ifndef _PARALLELOGRAM_H_
#define _PARALLELOGRAM_H_ 1

#include <Surface.h>
#include <Material.h>
#include <BBox.h>

#define PARALLEL_EPSILON 0.00000001f

class Parallelogram : public Surface 
{
public:
   Parallelogram(const Vector3& _base, const Vector3& _u, const Vector3& _v,
         Material* _mptr); 
   Parallelogram(const Vector3& _base, const Vector3& _u, const Vector3& _v,
         const Vector2& _uv0, const Vector2& _uv1, const Vector2& _uv2,
         Material* _mptr);
   bool hit(const Ray& r, float tmin, float tmax, float time, 
         SurfaceHitRecord& rec) const;

   BBox boundingBox(float time0, float time1) const;

   bool randomPoint(const Vector3& viewpoint, const Vector2& seed , float time, 
         Vector3& light_point, Vector3& N,
         float& pdf, rgb& radiance) const; 

   int causticPhotons() { return mptr->causticPhotons(); }
   int globalPhotons() { return mptr->globalPhotons(); }
   rgb photonColor() { return  (1.0f/_pdf) * mptr->photonColor(); }
   bool generatePhoton(Ray & ray, const Vector2 & seed1,
         const Vector2 & seed2);

   Vector3 base;  //
   Vector3 u;     //  One vertex and the offsets to its neighbors     
   Vector3 v;     //

   Vector3 norm;  //  normal of the parallelogram
   Vector3 unorm; //  normalized u offset
   Vector3 vnorm; //  normalized v offset

   Vector2 uv0;   //
   Vector2 uv1;   //  texture coords
   Vector2 uv2;   // 

   float _pdf;    // precomputed constant pdf
   Material* mptr; 
};

#endif //_PARALLELOGRAM_H_
