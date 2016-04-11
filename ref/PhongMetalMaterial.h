

// PhongMetalMaterial.h

#ifndef _PHONG_METAL_MATERIAL_H_
#define _PHONG_METAL_MATERIAL_H_ 1

#include "Material.h"
#include "SimpleTexture.h"

class PhongMetalMaterial : public Material  
{
public:

   PhongMetalMaterial(Texture *rt, Texture *et) 
   { R = rt; phong_exp = et;}

   virtual rgb ambientResponse(const ONB&,
         const Vector3&,                        // incident direction
         const Vector3&,                        // Texture point
         const Vector2&);                       // Texture coordinate

   virtual bool scatterDirection(const Vector3&,// incident Vector
         const SurfaceHitRecord&,               // hit we are shading
         Vector2&,                              // random seed                    
         rgb&,                                  // color to attenuate by
         bool&,                                 // count emitted light?
         float&,                                // brdf scale
         Vector3&);                             // scattered direction

    Texture *R;
    Texture *phong_exp;
};


#endif // _PHONG_METAL_MATERIAL_H_
