#ifndef RENDERER_H
#define RENDERER_H


#include "Ray.h"
#include "Scene.h"


class PhotonMaps;

class Renderer {
 public:

   virtual rgb color(        
      const Ray& r,        // Ray being sent
      const Scene* s,
      float tmin,          // minimum hit parameter to be searched for
      float tmax,          // maximum hit parameter to be searched for
      float time,
      Vector2& sseed,      // seed for reflection ray
      Vector2& rseed,      // seed for point on light
      int depth,           // diffuse recursive depth     
      int spec_depth,      // specular recursive depth      
      bool CEL,            // count emitted light? 
      PhotonMaps* maps     // maps for use in Photon Mapping
    ) const = 0;

};


#endif
