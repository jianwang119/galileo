

// DiffSpecMaterial.cc

#include "DiffSpecMaterial.h"

rgb DiffSpecMaterial::ambientResponse(const ONB& uvw, const Vector3& v_in,
      const Vector3& p, const Vector2& uv) 
{
   float cosine = dot(v_in, uvw.w());
   if (cosine < 0.0f) cosine = -cosine;
   float temp1 = 1.0f - cosine;
   float R = R0 + (1.0f - R0) * temp1*temp1*temp1*temp1*temp1;
   float P = (R + 0.5f) / 2.0f;

   if (rng() <= P)
     return spec_mat->ambientResponse(uvw, v_in, p, uv);
   else 
     return diff_mat->ambientResponse(uvw, v_in, p, uv);
}

bool DiffSpecMaterial::explicitBrdf(const ONB& uvw, const Vector3& v0,
      const Vector3& v1, const Vector3& p, const Vector2& uv, rgb& brdf)
{ return diff_mat->explicitBrdf(uvw, v0, v1, p, uv, brdf); }

bool DiffSpecMaterial::scatterDirection (const Vector3& v_in,
      const SurfaceHitRecord& rec, Vector2& seed, rgb& color, bool& CEL,
      float& brdf, Vector3& v_out)
{ 
   float cosine = dot(v_in, rec.uvw.w());
   if (cosine < 0.0f) cosine = -cosine;
   float temp1 = 1.0f - cosine;
   float R = R0 + (1.0f - R0) * temp1*temp1*temp1*temp1*temp1;
   float P = (R + 0.5f) / 2.0f;

   // we assume that spec_mat and diff_mat return brdf_scales of 1
   if (rng() <= P)
   {
      brdf = R / P;
      return spec_mat->scatterDirection(v_in, rec, seed, color, CEL, temp1, v_out);
   }
   else 
   {
      brdf = (1.0f - R) / (1.0f - P);
      return diff_mat->scatterDirection(v_in, rec, seed, color, CEL, temp1, v_out);
   }
}

