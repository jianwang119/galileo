#ifndef PATH_RENDERER_H
#define PATH_RENDERER_H


#include "Renderer.h"



class PathRenderer : public Renderer {
 public:

   PathRenderer(int md, rgb a) { max_depth = md; ambient = a; }

   virtual rgb color(        
      const Ray& r,      // Ray being sent
      const Scene* s,
      float tmin,        // minimum hit parameter to be searched for
      float tmax,        // maximum hit parameter to be searched for
      float time,
      Vector2& sseed,
      Vector2& rseed,
      int depth,
      int spec_depth,
      bool corl,         // count only reflected light? (not emitted)
      PhotonMaps* maps
    ) const;

    rgb ambient;
    int max_depth;

};


#endif
