#ifndef DIRECT_RENDERER_H
#define DIRECT_RENDERER_H


#include "Renderer.h"


class DirectRenderer : public Renderer {
 public:

   DirectRenderer(int dmd, int smd, rgb a) 
   { ambient = a; dmax_depth = dmd; smax_depth = smd; }

   rgb directLight(const Ray& r, const Scene* s,
                float time, const Vector2&, const SurfaceHitRecord& rec) const;

   virtual rgb color(        
      const Ray& r,       // Ray being sent
      const Scene* s,
      float tmin,         // minimum hit parameter to be searched for
      float tmax,         // maximum hit parameter to be searched for
      float time,
      Vector2& seed1,     // direct lighting dseed
      Vector2& seed2,     // reflection seed
      int depth,
      int spec_depth,
      bool CEL,           // count emitted light?
      PhotonMaps* maps
      ) const;

    rgb ambient;
    int dmax_depth;
    int smax_depth;

};


#endif
