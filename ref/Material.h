

#ifndef _MATERIAL_H_
#define _MATERIAL_H_ 1


#include "Vector2.h"
#include "rgb.h"
#include "ONB.h"
#include "Surface.h"

class Material 
{
public:
   virtual bool emits() const {return false;}
   
   virtual rgb emittedRadiance(const ONB&,      // ONB of hit point
         const Vector3&,                        // outgoing direction from light
         const Vector3&,                        // Texture point 
         const Vector2&)                        // Texture coordinate 
   { return rgb(0,0,0); }

   virtual rgb ambientResponse(const ONB&,      // ONB of hit point
         const Vector3&,                        // incident direction
         const Vector3&,                        // Texture point
         const Vector2& )                       // Texture coordinate
   { return rgb(0,0,0); }

   virtual bool explicitBrdf(const ONB&,        // ONB of hit point
         const Vector3&,                        // outgoing vector v0
         const Vector3&,                        // outgoing vector v1
         const Vector3&,                        // Texture point
         const Vector2&,                        // Texture coordinate
         rgb&) { return false; }

   virtual bool scatterDirection(const Vector3&,// incident Vector
         const SurfaceHitRecord&,               // hit we are shading
         Vector2&,                              // random seed                    
         rgb&,                                  // color to attenuate by
         bool&,                                 // count emitted light?
         float&,                                // brdf scale 
         Vector3&)=0;                           // scattered direction

   virtual bool isSpecular() { return false; }
   virtual bool isTransmissive() { return false; }
   virtual int causticPhotons() { return 0; }   
   virtual int globalPhotons() { return 0; } 
   virtual rgb photonColor() { return rgb(0.0f, 0.0f, 0.0f); }
};

#endif // _MATERIAL_H_
