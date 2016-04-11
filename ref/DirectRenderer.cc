#include <DirectRenderer.h>
#include <Material.h>
#include <stdio.h>
#include <float.h>

rgb DirectRenderer::color(        
      const Ray& r,             // Ray being sent
      const Scene* s,
      float tmin,              // minimum hit parameter to be searched for
      float tmax,              // maximum hit parameter to be searched for
      float time,
      Vector2& sseed,
      Vector2& rseed,
      int depth,
      int spec_depth,
      bool CEL,           // count emitted light?
      PhotonMaps* maps) const 
{

   SurfaceHitRecord rec;
   bool cel;
   float brdf_scale;
   rgb c(0,0,0);

   // check if a surface is intersected
   if ( s->surfaces->hit(r, tmin, tmax, time, rec) ) 
   {
      Vector3 v_out;
      rgb R;
      
      // find emitted radiance
      if (CEL) c += rec.mat_ptr->emittedRadiance(rec.uvw, -r.direction(), 
                                                 rec.texp, rec.uv);
      
      // find ambient 
      c += ambient*rec.mat_ptr->ambientResponse(rec.uvw, 
            r.direction(), 
            rec.p, 
            rec.uv);
      
      // trace reflected ray
      if (rec.mat_ptr->scatterDirection(r.direction(), rec, rseed, R, cel, 
               brdf_scale, v_out))
      {
         if (!cel)  // diffuse scatter
         {
            if (depth < dmax_depth)
            {
               Ray ref(rec.p, v_out);
               c += R*color(ref, s, 0.03f, FLT_MAX,time, sseed, rseed, depth+1,
                    spec_depth, cel, NULL);
            }  
            c += brdf_scale * directLight(r,s,time,sseed,rec);
         }
         else       // specular scatter
         {
            if (spec_depth < smax_depth)
            {
               Ray ref(rec.p, v_out);
               c += brdf_scale * R * color(ref, s, 0.05, FLT_MAX,time, sseed, 
                     rseed, depth, spec_depth+1, cel, NULL);
            }
         }
      }
      return c;
   }
   else
      return s->background->value( Vector2(0,0), r.direction() );
}


rgb DirectRenderer::directLight(const Ray& r,
                                const Scene* s,
                                float time,         
                                const Vector2& seed,
                                const SurfaceHitRecord& rec) const {
   rgb c(0,0,0);
   for (int i = 0; i < s->lights.length(); i++) {
      Vector3 on_light;
      float pdf;
      rgb E;
      Vector3 N;
      if (s->lights[i]->randomPoint(rec.p, seed, time, on_light, N, pdf, E)) {
         Ray sr(rec.p, on_light- rec.p);
         double dist = sr.direction().length();
         double cosine0 = dot(sr.direction(), rec.uvw.w()) / dist;
         if (cosine0 > 0.0f && !s->surfaces->shadowHit(sr, 0.00001f, 0.9999f, time) ) {
            rgb brdf;
            if (rec.mat_ptr->explicitBrdf(rec.uvw, -r.direction(),
                     sr.direction(), rec.texp, rec.uv, brdf)) {
               float cosine1 = dot(-sr.direction(), N) / dist;

               if (cosine1 > 0.0f) {
                  c += brdf * E * (cosine0*cosine1/(dist*dist*pdf));
               }
         
            }
         }
      }
   }
   return c;
}


