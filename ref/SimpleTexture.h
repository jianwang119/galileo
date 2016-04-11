#ifndef SIMPLE_TEXTURE_H
#define SIMPLE_TEXTURE_H


#include "Texture.h"



class SimpleTexture : public Texture {
 public:

   SimpleTexture(rgb c) { color = c;}
   virtual rgb value(const Vector2&, const Vector3&) const;
   
   rgb color;
};


#endif
