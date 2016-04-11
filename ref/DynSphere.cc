
#include "DynSphere.h"

DynSphere::DynSphere(const Vector3& _ocenter, float _radius, Material* _mat_ptr, 
               float min_time, float max_time, 
               Vector3(*_getCenter)(float, Vector3))
   : ocenter(_ocenter), radius(_radius), mintime(min_time), 
     maxtime(max_time) { mat_ptr = _mat_ptr; getCenter = _getCenter; }
   
BBox DynSphere::boundingBox(float time0, float time1) const
{
   Vector3 c1 = getCenter(time0, ocenter); 
   Vector3 c2 = getCenter(time1, ocenter); 
   
   BBox b1 = BBox(c1 - Vector3(radius,radius,radius),
                  c1 + Vector3(radius,radius,radius));
   BBox b2 = BBox(c2 - Vector3(radius,radius,radius),
	          c2 + Vector3(radius,radius,radius));

   return surround(b1, b2);
}

bool DynSphere::hit(const Ray& r, float tmin, float tmax, float time, 
      SurfaceHitRecord& rec) const
{
   Vector3 new_center = getCenter(time, ocenter);  
   Vector3 temp = r.origin() - new_center;
   
   float twoa = 2*dot( r.direction(), r.direction() );
   float b = 2*dot( r.direction(), temp );
   float c = dot( temp, temp ) - radius*radius;
   float discriminant = b*b- 2*twoa*c;
   if ( discriminant > 0 ) 
   {
      discriminant = sqrt( discriminant );
      float t = (- b - discriminant) / twoa;
      if (t < tmin)
         t = (- b + discriminant) / twoa;
      if (t < tmin || t > tmax)
         return false;

      // we have a hit -- populat hit record 
      rec.p = rec.texp = r.pointAtParameter(t);
      rec.t = t;
      Vector3 n = (rec.p - new_center);
      float pi = M_PI;
      float theta = acos( 0.9999 * n.z() );
      float sinTheta = sin(theta);
      float phi = acos( n.x() / (1.0001 * sinTheta) );
      if (n.y() < 0.0) phi = 2*pi - phi;
      rec.uv = Vector2(phi/(2*pi), 1.0 - theta/pi);
      rec.mat_ptr = mat_ptr;
      if (n.z() < -0.9999 || n.z() > 0.9999)
         rec.uvw.initFromWV( n, Vector3(0, 1, 0) );
      else
         rec.uvw.initFromWV( n, Vector3(0, 0, 1) );

      return true;
   }
   else
      return false;


}

bool DynSphere::shadowHit(const Ray& r, float tmin, float tmax, float time) const
{
   Vector3 new_center = getCenter(time, ocenter);  
   Vector3 temp = r.origin() - new_center;

   float twoa = 2*dot( r.direction(), r.direction() );
   float b = 2*dot( r.direction(), temp );
   float c = dot( temp, temp ) - radius*radius;
   float discriminant = b*b- 2*twoa*c;
   if ( discriminant > 0 ) {
      discriminant = sqrt( discriminant );
      float t = (- b - discriminant) / twoa;
      if (t < tmin)
         t = (- b + discriminant) / twoa;
      return (!(t < tmin || t > tmax));
   }
   return false;
}
