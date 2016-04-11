#ifndef TEXTURE_H
#define TEXTURE_H


#include "Vector2.h"
#include "Vector3.h"
#include "rgb.h"



class Texture {
 public:

   virtual rgb value(const Vector2&, const Vector3&) const = 0;
   
};


#endif
