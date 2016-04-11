
/*****************************************************************************\
 *                                                                           *
 *  filename : Parallelogram.h                                               *
 *  author   : R. Keith Morley                                               *
 *  last mod : 10/04/02                                                      *
 *                                                                           *
\*****************************************************************************/ 
 
#include <Parallelogram.h>
#include <stdio.h>

Parallelogram::Parallelogram(const Vector3& _base, const Vector3& _u, 
                            const Vector3& _v, Material* _mptr)
   : base(_base), u(_u), v(_v)
{
   mptr  = _mptr;
   norm  = unitVector(cross(u,v));
   unorm = unitVector(u);
   vnorm = unitVector(v);
  
   uv0 = Vector2(0, 0); 
   uv1 = Vector2(1, 0); 
   uv2 = Vector2(0, 1); 
   // find area of parallelogram 
   double width  = u.length();
   Vector3 proj  = v - ((dot(v, u) / (width*width)) * u);
   double height = proj.length();
   double area   = width * height;

   _pdf = 1.0f / area; 
}

Parallelogram::Parallelogram(const Vector3& _base, const Vector3& _u,
      const Vector3& _v, const Vector2& _uv0, const Vector2& _uv1,
      const Vector2& _uv2, Material* _mptr)
: base(_base), u(_u), v(_v), uv0(_uv0), uv1(_uv1), uv2(_uv2)
{
   mptr = _mptr;
   norm  = unitVector(cross(u,v));
   unorm = unitVector(u);
   vnorm = unitVector(v);

   // find area of parallelogram 
   double width  = u.length();
   Vector3 proj = v - ((dot(v, u) / (width*width)) * u);
   double height = proj.length();
   double area   = width * height;

   _pdf = 1.0f / area;
}

bool Parallelogram::hit(const Ray& r, float tmin, float tmax, float time, 
      SurfaceHitRecord& rec) const
{
   double dot1 = dot(r.direction(), norm);

   // check to see if ray is parallel to surface plane 
   if (dot1 < PARALLEL_EPSILON && dot1 > -PARALLEL_EPSILON) return false;
   
   // find distance to surface plane
   float dot2 = dot(norm, base);
   float t    = (dot2 - dot(norm, r.origin())) / dot1; 
   if (t > tmax || t < tmin) return false;
   
   // see if point of plane intersection is within parallelogram
   Vector3 hit_plane(r.origin() + r.direction() * t);
   Vector3 offset(hit_plane - base);

   float u1 = dot(unorm, offset) / u.length();
   if (u1 < 0.0f || u1 > 1.0f) return false;
   
   float v1 = dot(vnorm, offset) / v.length();
   if (v1 < 0.0f || v1 > 1.0f) return false;
   
   
   // fill hit record 
   rec.mat_ptr = mptr;
   rec.p = rec.texp = hit_plane; 
   rec.t = t;

   rec.uvw.initFromW(norm);
   rec.uv = v1 * uv2 + (1.0f - v1) * uv0 + u1 * uv1; 
   return true;
}

BBox Parallelogram::boundingBox(float time0, float time1) const
{
   const float epsilon = 0.00001f;

   Vector3 min;
   Vector3 max;

   Vector3 p0 = base;
   Vector3 p1 = base + u;
   Vector3 p2 = base + v;
   Vector3 p3 = base + u + v;

   min.setX(p0.x() < p1.x() ? p0.x() : p1.x());
   min.setY(p0.y() < p1.y() ? p0.y() : p1.y());
   min.setZ(p0.z() < p1.z() ? p0.z() : p1.z());

   min.setX(p2.x() < min.x() ? p2.x() : min.x());
   min.setY(p2.y() < min.y() ? p2.y() : min.y());
   min.setZ(p2.z() < min.z() ? p2.z() : min.z());

   min.setX(p3.x() < min.x() ? p3.x() : min.x());
   min.setY(p3.y() < min.y() ? p3.y() : min.y());
   min.setZ(p3.z() < min.z() ? p3.z() : min.z());
   
   max.setX(p0.x() > p1.x() ? p0.x() : p1.x());
   max.setY(p0.y() > p1.y() ? p0.y() : p1.y());
   max.setZ(p0.z() > p1.z() ? p0.z() : p1.z());

   max.setX(p2.x() > max.x() ? p2.x() : max.x());
   max.setY(p2.y() > max.y() ? p2.y() : max.y());
   max.setZ(p2.z() > max.z() ? p2.z() : max.z());

   max.setX(p3.x() > max.x() ? p3.x() : max.x());
   max.setY(p3.y() > max.y() ? p3.y() : max.y());
   max.setZ(p3.z() > max.z() ? p3.z() : max.z());

   min.setX(min.x() - epsilon);
   min.setY(min.y() - epsilon);
   min.setZ(min.z() - epsilon);

   max.setX(max.x() + epsilon);
   max.setY(max.y() + epsilon);
   max.setZ(max.z() + epsilon);

   return BBox(min, max);
}

bool Parallelogram::randomPoint(const Vector3& viewpoint, const Vector2& seed, 
      float time, Vector3& light_point, Vector3& N, float & pdf, 
      rgb& radiance) const
{
   light_point = Vector3(base + seed.x() * u + seed.y() * v);
   pdf = _pdf;
   
   Vector3 from_light = unitVector(viewpoint - light_point);
   ONB uvw; 
   uvw.initFromW(norm);
   N = uvw.w();

   radiance = mptr->emittedRadiance(uvw, from_light, light_point, 
                                 Vector2(0.0f,0.0f));
   
   return true; 
}

bool Parallelogram::generatePhoton(Ray & ray, const Vector2 & seed1,
            const Vector2 & seed2)
{
   Vector3 point;
   Vector3 direction;

   point = Vector3(base + seed1.x() * u + seed1.y() * v);

   float pi = M_PI;
   float phi = 2.0f * pi * seed2.x();
   float r = sqrt(seed2.y());
   float x = r * cos(phi);
   float y = r * sin(phi);
   float z = sqrt(1 - x*x - y*y);

   ONB uvw;
   uvw.initFromW (norm);
   
   direction = x*uvw.u() + y*uvw.v() + z*uvw.w();
   ray = Ray(point, direction);

   return true;
}
