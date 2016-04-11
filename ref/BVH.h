
#ifndef _BVH_H_
#define _BVH_H_

#include "Surface.h"
#include "BBox.h"

class SurfaceList;

class BVH : public Surface
{
public:
   BVH();
   BVH(SurfaceList* surfaces);
   BVH(Surface** surfaces, int num_surfaces);
   BVH(Surface* prim1, Surface* prim2);
   BVH(Surface* prim1, Surface* prim2, const BBox& _bbox);
   bool hit(const Ray& r, float tmin, float tmax, float time, 
         SurfaceHitRecord& rec)const;
   bool shadowHit(const Ray& r, float tmin, float tmax, float time) const;
   BBox boundingBox( float time0, float time1 )const;
   Surface* buildBranch (Surface** surfaces, int num_surfaces, int axis = 0);
   bool randomPoint(const Vector3&, const Vector2&, float time, Vector3&, 
         Vector3&, float&, rgb& )const { return false; }

   BBox bbox;
   Surface* left;
   Surface* right;
};

inline BVH::BVH(Surface* prim1, Surface* prim2, const BBox& _bbox) {
   bbox = _bbox;
   left  = prim1;
   right = prim2;
}
inline BVH::BVH(Surface* prim1, Surface* prim2) {
   left  = prim1;
   right = prim2;
   bbox = surround(prim1->boundingBox(0.0f, 0.0f), 
                   prim2->boundingBox(0.0f, 0.0f));
}

#endif // _BVH_H_
