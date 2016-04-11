#ifndef SCENE_H
#define SCENE_H


#include "SurfaceList.h"
#include "Texture.h"
#include "DynArray.h"


class Scene {
 public:
   Scene();
   void setView(const Vector3& e, 
	        const Vector3& g, 
		const Vector3& u,
	        float aper, 
		float l, 
		float r, 
		float t, 
		float b, 
		float d) 
   { 
      eye = e; gaze = g; up = u; aperture = aper; 
      left = l; right = r; top = t; bottom = b; distance = d; 
   }
   
   // viewing parameters
   Vector3 eye;
   Vector3 gaze;
   Vector3 up;
   float aperture;
   float left;
   float right;
   float top;
   float bottom;
   float distance;
   
   // scene geometry
   Surface* surfaces;
   DynArray<Surface*> lights;
   Texture *background;
};


#endif
