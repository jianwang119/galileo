
/*****************************************************************************\
 *                                                                           *
 * filename : Camera.h                                                       *
 * author   : Peter Shirley / Russell Morley                                 *
 * last mod : 09/06/02                                                       *
 *                                                                           *
\*****************************************************************************/


#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include "ONB.h"

class Camera  
{
public:
    
   Camera() {}
   Camera(const Camera& orig)
   {
      center = orig.center;
      corner = orig.corner;
      across = orig.across;
      up     = orig.up;
      uvw    = orig.uvw;
      l      = orig.l;
      r      = orig.r;
      b      = orig.b;
      t      = orig.t;
      d      = orig.d;
      lens_radius = orig.lens_radius;

   } 
   Camera(Vector3 c, Vector3 gaze, Vector3 vup, float aperture, float left, 
         float right, float bottom, float top, float distance) 
      : center(c), d(distance), l(left), r(right), b(bottom), t(top)  
   {
      lens_radius = aperture/2.0F;
      uvw.initFromWV( -gaze, vup );
      corner = center + l*uvw.u() + b*uvw.v() - d*uvw.w();
      across = (r-l)*uvw.u();
      up = (t-b)*uvw.v();
   } 

   Ray getRay(float a, float b, float xi1, float xi2) 
   {
      Vector3 origin = center + 2.0F*(xi1-0.5F)*lens_radius*uvw.u() +
         2.0F*(xi2-0.5F)*lens_radius*uvw.v();
      Vector3 target = corner + across*a + up*b;
      return Ray(origin, unitVector(target-origin));
   }

   Vector3 center, corner, across, up;
   ONB uvw;
   float lens_radius;
   float l, r, b, t;
   float d;
};


#endif
