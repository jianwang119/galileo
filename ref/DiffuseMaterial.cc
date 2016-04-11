
#include "DiffuseMaterial.h"

rgb DiffuseMaterial::ambientResponse(const ONB&, const Vector3&,
      const Vector3& p, const Vector2& uv) 
{ return R->value(uv, p); }

bool DiffuseMaterial::explicitBrdf(const ONB&, const Vector3&,    
      const Vector3&, const Vector3& p, const Vector2& uv, rgb& brdf) 
{ 
    float k = .318309886184f; // 1.0 / M_PI
    brdf = k * R->value(uv, p);
    return true;
}

bool DiffuseMaterial::scatterDirection (const Vector3& in_dir,
      const SurfaceHitRecord& rec, Vector2& seed, rgb& color, bool& CEL, 
      float& brdf, Vector3& v_out)
{
   ONB uvw    = rec.uvw;
   Vector3 p  = rec.p;
   Vector2 uv = rec.uv;
    
   CEL = false;
   brdf = 1.0f; 
   
   float two_pi = 6.28318530718f;
   float phi = two_pi * seed.x();
   float r = sqrt(seed.y());
   float x = r * cos(phi);
   float y = r * sin(phi);
   float z = sqrt(1 - x*x - y*y);

   color = R->value(uv, p); 
   v_out = x*uvw.u() + y*uvw.v() + z*uvw.w();

   seed.scramble();
   return true; 
}


