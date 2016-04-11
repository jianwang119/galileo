#ifndef BBOX_H
#define BBOX_H


#include <math.h>
#include <Ray.h>

class BBox {
public:
      BBox(const Vector3& a, const Vector3& b) { pp[0] = a; pp[1] = b; }
      BBox() {}
      Vector3 min() const { return pp[0]; }
      Vector3 max() const { return pp[1]; }
      bool rayIntersect(const Ray& r, float tmin, float tmax) const;
protected:
      Vector3 pp[2]; 
};

inline bool BBox::rayIntersect(const Ray& r, float tmin, float tmax) const {

   float interval_min = tmin;
   float interval_max = tmax;

   float t0 = (pp[r.posneg[0]].e[0] - r.data[0].e[0]) * r.data[2].e[0];
   float t1 = (pp[r.posneg[1]].e[0] - r.data[0].e[0]) * r.data[2].e[0];
   if (t0 > interval_min) interval_min = t0;
   if (t1 < interval_max) interval_max = t1;
   if (interval_min > interval_max) return false;

   t0 = (pp[r.posneg[2]].e[1] - r.data[0].e[1]) * r.data[2].e[1];
   t1 = (pp[r.posneg[3]].e[1] - r.data[0].e[1]) * r.data[2].e[1];
   if (t0 > interval_min) interval_min = t0;
   if (t1 < interval_max) interval_max = t1;
   if (interval_min > interval_max) return false;

   t0 = (pp[r.posneg[4]].e[2] - r.data[0].e[2]) * r.data[2].e[2];
   t1 = (pp[r.posneg[5]].e[2] - r.data[0].e[2]) * r.data[2].e[2];
   if (t0 > interval_min) interval_min = t0;
   if (t1 < interval_max) interval_max = t1;
   return (interval_min <= interval_max);
}


inline BBox surround(const BBox& b1, const BBox& b2) {
    return BBox(
         Vector3( b1.min().x() < b2.min().x() ? b1.min().x() : b2.min().x(),
                  b1.min().y() < b2.min().y() ? b1.min().y() : b2.min().y(),
                  b1.min().z() < b2.min().z() ? b1.min().z() : b2.min().z() ),
         Vector3( b1.max().x() > b2.max().x() ? b1.max().x() : b2.max().x(),
                  b1.max().y() > b2.max().y() ? b1.max().y() : b2.max().y(),
                  b1.max().z() > b2.max().z() ? b1.max().z() : b2.max().z() ));

}


#endif
