#ifndef LUMINAIRE_MATERIAL_H
#define LUMINAIRE_MATERIAL_H


#include "Material.h"
#include "SimpleTexture.h"



class LuminaireMaterial : public Material  {
 public:

   
   LuminaireMaterial(Texture *t, float mult, float pexp, Material *m, 
        int caustic_p = 0, int global_p = 0) 
   { 
      E = t; multiplier = mult;  mat_ptr = m; phong_exp = pexp; 
      caustic_photons = caustic_p; global_photons = global_p;
   }
   virtual bool emits() const {return true;}
 
   virtual rgb emittedRadiance(const ONB&,
                               const Vector3&,
                               const Vector3&,
                               const Vector2&) ;

   virtual rgb ambientResponse(const ONB&,
                              const Vector3&, // incident direction
                              const Vector3&, // Texture point
                              const Vector2& ) ; // Texture coordinate

   virtual bool explicitBrdf(const ONB&,
                              const Vector3&, // unit vector v1
                              const Vector3&, // unit vector v0
                              const Vector3&, // Texture point
                              const Vector2&, // Texture coordinate
                              rgb&) ;

   virtual bool scatterDirection(const Vector3&,// incident Vector
         const SurfaceHitRecord&,               // hit we are shading
         Vector2&,                              // random seed                    
         rgb&,                                  // color to attenuate by
         bool&,                                 // count emitted light?
         float&,                                // brdf scale
         Vector3&);                             // scattered direction

   virtual int causticPhotons() { return caustic_photons; }
   virtual int globalPhotons() { return global_photons; }
   virtual rgb photonColor();
         
    int caustic_photons;
    int global_photons;
    Texture *E;
    Material *mat_ptr;
    float phong_exp;
    float multiplier;
   
};


#endif
