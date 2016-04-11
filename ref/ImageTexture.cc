#include <ImageTexture.h>
#include <Image.h>
#include <string.h>
ImageTexture::ImageTexture(char* filename)
{
   image = new Image();
   image->readPPM(filename);
}

rgb ImageTexture::value(const Vector2& uv, const Vector3& texp) const 
{
   // u & v *= dimensions minus the slop(2) and the zero base difference (1)
   // for a total of 3
   float u = uv.x() - int(uv.x());
   float v = uv.y() - int(uv.y()); 
   u *= (image->width()-3);
   v *= (image->height()-3);

   int iu = (int)u;
   int iv = (int)v;

   float tu = u-iu;
   float tv = v-iv;
   
   rgb c = image->getPixel(iu,iv)*(1-tu)*(1-tv)+
      image->getPixel(iu+1,iv)*tu*(1-tv)+
      image->getPixel(iu,iv+1)*(1-tu)*tv+
      image->getPixel(iu+1,iv+1)*tu*tv;

   return c;
}
