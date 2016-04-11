

// DiffuseMaterial.h

#ifndef _DIFFUSE_MATERIAL_H_
#define _DIFFUSE_MATERIAL_H_ 1

#include <Material.h>
#include <SimpleTexture.h>

class DiffuseMaterial : public Material  
{
public:
   DiffuseMaterial(Texture *t ) { R = t; } 

   virtual rgb ambientResponse(const ONB&,
         const Vector3&,                        // incident direction
         const Vector3&,                        // Texture point
         const Vector2&);                       // Texture coordinate

   virtual bool explicitBrdf(const ONB&,
         const Vector3&,                        // unit vector v1
         const Vector3&,                        // unit vector v0
         const Vector3&,                        // Texture point
         const Vector2&,                        // Texture coordinate
         rgb&);

   virtual bool scatterDirection(const Vector3&,// incident Vector
         const SurfaceHitRecord&,               // hit we are shading
         Vector2&,                              // random seed                    
         rgb&,                                  // color to attenuate by
         bool&,                                 // count emitted light?
         float&,                                // brdf scale
         Vector3&);                             // scattered direction

   Texture *R;
};

#endif // _DIFFUSE_MATERIAL_H_
