

#ifndef _DIFF_SPEC_MATERIAL_H_
#define _DIFF_SPEC_MATERIAL_H_ 1

#include <Material.h>
#include <RNG.h>

class DiffSpecMaterial : public Material 
{
public:
   DiffSpecMaterial() {}
   DiffSpecMaterial(Material* d, Material* s, float r0=.05f)
   { diff_mat = d; spec_mat = s; R0 = r0; } 
   
   virtual rgb ambientResponse(const ONB&,      // ONB of hit point
         const Vector3&,                        // incident direction
         const Vector3&,                        // Texture point
         const Vector2& );                      // Texture coordinate

   virtual bool explicitBrdf(const ONB&,        // ONB of hit point
         const Vector3&,                        // outgoing vector v0
         const Vector3&,                        // outgoing vector v1
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

   float R0;
   RNG rng; 
   Material* diff_mat;
   Material* spec_mat;
};

#endif // _GLOSSY_MATERIAL_H_
