#ifndef SURFACELIST_H  
#define SURFACELIST_H  


#include "Surface.h"
#include "DynArray.h"




class SurfaceList : public Surface {
 public:

   SurfaceList() {}
   virtual ~SurfaceList() {}

   virtual bool hit(        
      const Ray& r,             // Ray being sent
      float tmin,              // minimum hit parameter to be searched for
      float tmax,              // maximum hit parameter to be searched for
      float time,
      SurfaceHitRecord& rec 
    ) const;

    virtual BBox boundingBox(float time0, float time1) const;

    virtual bool randomPoint(const Vector3&,  // lighted point
                              const Vector2&,  // random seed
                              float time,
                              Vector3&,        // normal vector
                              Vector3&,        // random point
                              float&,         // pdf
                              rgb&             // emitted radiance
    ) const { return false;}

    bool add( Surface *s ) { return surfaces.append( s ); }

    int length() const {return surfaces.length();}

    DynArray< Surface* > surfaces;

};


#endif
