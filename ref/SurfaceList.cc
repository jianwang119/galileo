#include <float.h>
#include "SurfaceList.h"




bool SurfaceList::hit(        
      const Ray& r,             // Ray being sent
      float tmin,              // minimum hit parameter to be searched for
      float tmax,              // maximum hit parameter to be searched for
      float time,
      SurfaceHitRecord& rec 
    ) const {

    SurfaceHitRecord temp;
    rec.t = tmax;
    bool hit_something = false;
    for (int i = 0; i < length(); i++) {
        if ( surfaces[i]->hit(r, tmin, rec.t, time, temp) ) {
              rec = temp;
              hit_something = true;
        }
    }
    return hit_something;
}

BBox SurfaceList::boundingBox(float t0, float t1) const {
      Vector3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
      Vector3 min( FLT_MAX,  FLT_MAX,  FLT_MAX);
      for (int i = 0; i < length(); i++) {
          BBox box = surfaces[i]->boundingBox(t0, t1);
          if (box.min().x() < min.x()) min.setX( box.min().x() );
          if (box.min().y() < min.y()) min.setY( box.min().y() );
          if (box.min().z() < min.z()) min.setZ( box.min().z() );
          if (box.max().x() > max.x()) max.setX( box.max().x() );
          if (box.max().y() > max.y()) max.setY( box.max().y() );
          if (box.max().z() > max.z()) max.setZ( box.max().z() );
      }
      return BBox(min, max);
}

