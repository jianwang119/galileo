#include "MarbleTexture.h"


rgb MarbleTexture::value(const Vector2&, const Vector3& p) const 
{
   float t = (sin(freq*p.x() + scale*noise->turbulence(freq*p, octaves))) +1.0f;
   //float t = 2.0f*fabs(sin(freq*p.x() + scale*noise.turbulence(freq*p, octaves)));
   
   if (t < 1.0f)
      return (c1*t + (1.0f - t)*c2);
   else
   {
      t -= 1.0f;
      return (c0*t + (1.0f - t)*c1);
   }
}
