
/*****************************************************************************\
 *                                                                           *
 * filename : DielectricMaterial.h                                           *
 * author   : R. Keith Morley / Pete Shirley                                 *
 * lastmod  : 11/02/02                                                       *
 *                                                                           *
 * Material that uses Fresnell's equation and Beer's law to simulate         *
 * dielectrics.                                                              *
 *                                                                           *     
\*****************************************************************************/

#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_ 1

#include <Material.h>
#include <rgb.h>
#include <RNG.h>
#include <Vector3.h>

class Texture;
class RNG;

class DielectricMaterial : public Material
{
public:
   DielectricMaterial() {} 
   DielectricMaterial(float nt, const rgb& _ex); 

   virtual bool scatterDirection(const Vector3&,// incident Vector
         const SurfaceHitRecord&,               // hit we are shading
         Vector2&,                              // random seed                    
         rgb&,                                  // color to attenuate by
         bool&,                                 // count emitted light?
         float&,                                // brdf scale
         Vector3&);                             // scattered direction

   float R0;
   float nt;
   rgb   extinction;
   RNG rng;
};
#endif // _DIELECTRIC_H_
