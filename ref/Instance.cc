
#include <Instance.h>
#include <BBox.h>

Instance::Instance(Matrix trans, Matrix trans_inverse, Surface* _prim)
: M(trans), N(trans_inverse), prim(_prim) {}

Instance::Instance(Matrix trans, Surface* _prim)
: M(trans), N(trans) ,prim(_prim)   
{ N.invert(); }

bool Instance::hit(const Ray& r, float tmin, float tmax, float time,
      SurfaceHitRecord& rec)const 
{
   Vector3 no = transformLoc(N, r.origin());
   Vector3 nd = transformVec(N, r.direction());
   Ray tray(no, nd);
  
   if (prim->hit(tray, tmin, tmax, time, rec))
   {
      rec.p = transformLoc(M, rec.p);
      Vector3 normal = transformVec(N.getTranspose(), rec.uvw.w());
      ONB uvw; 
      uvw.initFromW(normal);
      rec.uvw = uvw;
      return true;
   }
   else return false; 
}

bool Instance::shadowHit(const Ray& r, float tmin, float tmax, float time)const
{
   Vector3 no = transformLoc(N, r.origin());
   Vector3 nd = transformVec(N, r.direction());
   Ray tray(no, nd);

   return (prim->shadowHit(tray, tmin, tmax, time));
}

BBox Instance::boundingBox( float time0, float time1 )const
{
   // this needs to be fixed
   BBox temp = prim->boundingBox(time0, time1);
   return BBox (transformLoc(M, temp.min()), transformLoc(M, temp.max()));
}

bool Instance::randomPoint(const Vector3&, const Vector2&, float time, 
      Vector3&, Vector3&, float&, rgb&)const
{ return false; }

