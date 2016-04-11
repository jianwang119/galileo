#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H


#include "Texture.h"
#include "SolidNoise.h"


class NoiseTexture : public Texture {
 public:

   virtual ~NoiseTexture() {}
   NoiseTexture(float multiplier) {
        k = multiplier;
   }

   virtual rgb value(const Vector2&, const Vector3&) const;

   float k;
   SolidNoise noise;
   
};


#endif
