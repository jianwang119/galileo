
/*****************************************************************************\
 *                                                                           *
 *  filename: Triangle.h                                                     *
 *  author  : Russell K. Morley                                              *
 *  lastmod : 09/30/02                                                       *
 *                                                                           *
\*****************************************************************************/

#ifndef _TRIANGLE_H_ 
#define _TRIANGLE_H_

#include <Material.h>
#include <Vector3.h>
#include <Surface.h>
#include <BBox.h>

class Triangle : public Surface 
{
public:
   Triangle();
   ~Triangle();
   Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2,
            Material* mat);   
   Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2,
            const Vector2& _u0, const Vector2& _u1, const Vector2& _u2,   
            Material* mat);   
    virtual bool hit(const Ray& r, float tmin, float tmax, float time, 
	     SurfaceHitRecord& rec) const;

    virtual BBox boundingBox(float time0, float time1) const;

    virtual bool randomPoint(const Vector3&, const Vector2&,
                            float time, Vector3&, Vector3&, 
	                   float&, rgb&) const;

    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
    Vector2 u0;
    Vector2 u1;
    Vector2 u2;
    Material* mptr;   
};


#endif // _TRIANGLE_H_
