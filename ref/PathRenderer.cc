#include <PathRenderer.h>
#include <Surface.h>
#include <Material.h>
#include <stdio.h>
#include <float.h>

rgb PathRenderer::color(        
      const Ray& r,             // Ray being sent
      const Scene* s,
      float tmin,              // minimum hit parameter to be searched for
      float tmax,              // maximum hit parameter to be searched for
      float time,
      Vector2& sseed,
      Vector2& rseed,
      int depth,
      int spec_depth,
      bool corl,           // count only reflected light? (not emitted)
      PhotonMaps* maps
      ) const {
    
    SurfaceHitRecord rec;
    bool dummy_bool = true;
    float brdf_scale;
    
    if ( s->surfaces->hit(r, tmin, tmax, time, rec) ) 
    {
          rgb c(0,0,0);
          c += rec.mat_ptr->emittedRadiance(rec.uvw, -r.direction(),
                rec.texp, rec.uv);
          
          Vector3 v_out;
          rgb R;
          if(depth < max_depth && rec.mat_ptr->scatterDirection(r.direction(),
                   rec, sseed, R, dummy_bool, brdf_scale, v_out)) 
          {
                  Ray ref(rec.p, v_out);
                  c += brdf_scale*R*color(ref, s, 0.01, FLT_MAX, time, sseed, 
                        rseed, depth+1, 0, false, NULL);
          }
       return c + ambient*rec.mat_ptr->ambientResponse(rec.uvw, r.direction(), 
             rec.p, rec.uv);
    }
    else
       return s->background->value( Vector2(0,0), r.direction() );
}


