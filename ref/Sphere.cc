#include <float.h>
#include <Sphere.h>
#include <Material.h>

Sphere::Sphere(Vector3 c, float r, Material *p)  
{ center = c; radius = r; mat_ptr = p; }

bool Sphere::hit(const Ray& r, float tmin, float tmax, float, 
      SurfaceHitRecord& rec)const 
{
       Vector3 temp = r.origin() - center;
       float twoa = 2.0f*dot( r.direction(), r.direction() );
       float b = 2.0f*dot( r.direction(), temp );
       float c = dot( temp, temp ) - radius*radius;
       float discriminant = b*b- 2.0f*twoa*c; 
       if (discriminant > 0.0f) 
       {
           discriminant = sqrt(discriminant);
           float t = (-b - discriminant) / twoa;
           if (t < tmin) t = (-b + discriminant) / twoa;
           if (t < tmin || t > tmax) return false;

           // we have a hit -- populat hit record 
           rec.p = rec.texp = r.pointAtParameter(t);
           rec.t = t;
           Vector3 n = (rec.p - center);
           float pi = 3.14159265359f;
           float theta = acos( 0.9999f * n.z() ); 
           float sinTheta = sin(theta);
           float phi = acos( n.x() / (1.0001f * sinTheta) );
           if (n.y() < 0.0f) phi = 2*pi - phi;
           rec.uv = Vector2(phi/(2.0f*pi), 1.0f - theta/pi);
           rec.mat_ptr = mat_ptr;
           rec.uvw.initFromW(n);
           return true;
       }
       else
          return false;
}

bool Sphere::shadowHit(const Ray& r, float tmin, float tmax, float time) const 
{
       Vector3 temp = r.origin() - center;
       float twoa = 2.0f*dot( r.direction(), r.direction() );
       float b = 2.0f*dot( r.direction(), temp );
       float c = dot( temp, temp ) - radius*radius;
       float discriminant = b*b- 2.0f*twoa*c; 
       if ( discriminant > 0.0f ) 
       {
           discriminant = sqrt(discriminant);
           float t = (- b - discriminant) / twoa;
           if (t < tmin) t = (- b + discriminant) / twoa;
           return (!(t < tmin || t > tmax));
       }
       return false;
}

BBox Sphere::boundingBox(float, float) const 
{
      return BBox(center - Vector3(radius,radius,radius),
                  center + Vector3(radius,radius,radius));
}

bool Sphere::randomPoint(const Vector3& viewpoint, const Vector2& aseed, 
      float time, Vector3& on_light, Vector3& N, float& pdf, rgb& E)const  
{
   float d = (viewpoint - center).length();
   if (d < radius) return false;
   float r = radius;
   float pi = M_PI;
   Vector2 seed = aseed;

   // internal angle of cone surrounding light seen from viewpoint
   float sin_alpha_max = (r / d); 
   float cos_alpha_max = sqrt(1 - sin_alpha_max*sin_alpha_max);
   float q = 1. / (2*pi*(1- cos_alpha_max));
   int counter = 0;
   do {
      float cos_alpha = 1 + seed.x()*(cos_alpha_max-1);
      float sin_alpha = sqrt(1 - cos_alpha*cos_alpha);

      float phi = 2 * pi * seed.y();
      float cos_phi = cos(phi);
      float sin_phi = sin(phi);
   
      Vector3 k_i(cos_phi * sin_alpha, sin_phi * sin_alpha, cos_alpha);
   
      // Construct the local coordinate system UVW where viewpoint is at
      // the origin and the Sphere is at (0,0,d) in UVW.
      ONB UVW;
      UVW.initFromW(center - viewpoint);
      Ray to_light(viewpoint,
                     k_i.x() * UVW.u() + k_i.y() * UVW.v() + k_i.z() * UVW.w());
   
      SurfaceHitRecord rec;
      if (this->hit(to_light, 0.00001, FLT_MAX, time, rec)) {
           on_light = rec.p;
           float cos_theta_prime = -dot(rec.uvw.w(), to_light.direction());
           pdf = q * cos_theta_prime / ( on_light - viewpoint ).squaredLength();
           N = rec.uvw.w();
           E = mat_ptr->emittedRadiance( rec.uvw, -to_light.direction(),
                                         on_light, rec.uv );
           return true;
      }
      counter++;
      seed.scramble();
    } while (counter < 30);
    return false;
}
