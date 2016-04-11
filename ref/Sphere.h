

#ifndef _SPHERE_H_  
#define _SPHERE_H_ 1 

#include "Surface.h"

class Material;

class Sphere : public Surface 
{
public:

   Sphere( Vector3 c, float r, Material* mptr);

   virtual bool hit(const Ray& r,           
         float tmin,              
         float tmax,             
         float time,
         SurfaceHitRecord& rec)const;

    virtual bool shadowHit(
          const Ray& r,            
          float tmin,             
          float tmax,           
          float time)const; 

    virtual bool randomPoint(const Vector3&,  
          const Vector2&,  
          float time,
          Vector3&,        
          Vector3&,        
          float&,          
          rgb&)const;

    virtual BBox boundingBox(float time0, float time1)const;
    
    Vector3 center;
    float radius;
    Material *mat_ptr;
};

#endif // _SPHERE_H_
