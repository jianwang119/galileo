#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_

#include "Texture.h"

class Image;

class ImageTexture : public Texture 
{
public:
   ImageTexture(char* file_name);
   virtual rgb value(const Vector2&, const Vector3&) const;

   Image* image;   
};


#endif // _IMAGE_TEXTURE_H_
