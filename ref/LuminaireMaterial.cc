#include "LuminaireMaterial.h"

rgb LuminaireMaterial::emittedRadiance(const ONB& uvw,
      const Vector3& v_out,
      const Vector3& p,
      const Vector2& uv) 
{
   float co = dot(uvw.w(), v_out) / v_out.length();
   return multiplier*(phong_exp+1)*pow(co, phong_exp) * E->value(uv,p);
}

rgb LuminaireMaterial::ambientResponse(const ONB& uvw,
      const Vector3& v,
      const Vector3& p, 
      const Vector2& uv) 
{ return mat_ptr->ambientResponse(uvw, v, p, uv); }

bool LuminaireMaterial::explicitBrdf(const ONB& uvw,
      const Vector3& v1,    
      const Vector3& v0,   
      const Vector3& p,  
      const Vector2& uv,
      rgb& brdf) 
{ return mat_ptr->explicitBrdf(uvw, v1, v0, p, uv, brdf); }

bool LuminaireMaterial::scatterDirection (const Vector3& v_in,
      const SurfaceHitRecord& rec, 
      Vector2& seed, 
      rgb& color, 
      bool& CEL,
      float& brdf,
      Vector3& v_out)
{ return mat_ptr->scatterDirection(v_in, rec, seed, color, CEL, brdf, v_out); }

rgb LuminaireMaterial::photonColor()
{
   Vector2 dummy1;
   Vector3 dummy2;
   return E->value(dummy1, dummy2);
}

