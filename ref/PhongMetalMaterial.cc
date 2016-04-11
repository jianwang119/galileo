

// PhongMetalMaterial.cc

#include "PhongMetalMaterial.h"

rgb PhongMetalMaterial::ambientResponse(const ONB&, const Vector3&,
      const Vector3& p, const Vector2& uv) 
{ return R->value(uv, p); }

bool PhongMetalMaterial::scatterDirection (const Vector3& v_in,
      const SurfaceHitRecord& rec, Vector2& seed, rgb& color, bool& CEL,
      float& brdf, Vector3& v_out)
{ 
   ONB uvw    = rec.uvw;
   Vector3 p  = rec.p;
   Vector2 uv = rec.uv;

   CEL = true;
   brdf = 1.0f;

   ONB basis;
   Vector3 w = v_in - 2.0f*dot(v_in,uvw.w())*uvw.w();
   basis.initFromW( w );

   int counter = 0;
   do {
       float two_pi = 6.28318530718f;
       float phi = two_pi * seed.x();
       float exponent = phong_exp->value(uv, p).r();
       float cosTheta = pow(1.0f-seed.y(),  1.0f/(exponent+1.0f));
       float sinTheta = sqrt(1.0f - cosTheta*cosTheta);
       float x = cos(phi) * sinTheta;
       float y = sin(phi) * sinTheta;
       float z = cosTheta;


       v_out = x*basis.u() + y*basis.v() + z*basis.w();
       seed.scramble();
       counter++;
    } while (dot(uvw.w(), v_out) <= 0.0f && counter < 30);
    color = R->value(uv, p); 
    double cosine = -dot( v_in, uvw.w()) / v_in.length();
    color = color + (rgb(1,1,1) -color)*pow(1-cosine, 5);

   return  (dot(v_out, uvw.w()) > 0.0f);
}

