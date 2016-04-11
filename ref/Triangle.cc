
/*****************************************************************************\
 *                                                                           *
 * filename : Mesh.cc                                                        *
 * last mod : 08/06/02                                                       *
 * author   : R. Keith Morley / Peter Shirley                                *
 *                                                                           *
\*****************************************************************************/


#include <float.h>
#include <stdio.h>
#include <Triangle.h>


Triangle::Triangle(){}

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, 
                   Material* mat) :
   p0(_p0),  p1(_p1),  p2(_p2)
{
   mptr = mat; 
}

Triangle::Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, 
                   const Vector2& _u0, const Vector2& _u1, const Vector2& _u2,
		   Material* mat) :
   p0(_p0),  p1(_p1),  p2(_p2), u0(_u0),  u1(_u1),  u2(_u2)
{
      mptr = mat;
}

Triangle::~Triangle(){}

bool
Triangle::hit(const Ray& r, float tmin, float tmax, 
                  float time, SurfaceHitRecord& rec)const
{
   double t;
   double A = p0.e[0] - p1.e[0];
   double B = p0.e[1] - p1.e[1];
   double C = p0.e[2] - p1.e[2];

   double D = p0.e[0] - p2.e[0];
   double E = p0.e[1] - p2.e[1];
   double F = p0.e[2] - p2.e[2];

   double G = r.direction().x();
   double H = r.direction().y();
   double I = r.direction().z();

   double J = p0.x() - r.origin().x();
   double K = p0.y() - r.origin().y();
   double L = p0.z() - r.origin().z();

   double EIHF = E*I-H*F;
   double GFDI = G*F-D*I;
   double DHEG = D*H-E*G;

   double denom = (A*EIHF + B*GFDI + C*DHEG);

   double beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

   if (beta <= 0.0 || beta >= 1) 
   {
      
      return false;
   }
   
   double AKJB = A*K - J*B;
   double JCAL = J*C - A*L;
   double BLKC = B*L - K*C;

   double gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
   if (gamma <= 0.0 || beta + gamma >= 1.0) return false;

   t =  -(F*AKJB + E*JCAL + D*BLKC)/denom;
   if (t >= tmin && t <= tmax)
   {
      // if prim is hitfill hit_rec
      Vector3 norm;
      double alpha = 1.0 - beta - gamma;
      rec.uv = Vector2(alpha*u0.x() + beta*u1.x() + gamma*u2.x(),
	    alpha*u0.y() + beta*u1.y() + gamma*u2.y());
      rec.mat_ptr = mptr;
      rec.p = rec.texp = r.pointAtParameter(t);
      rec.t = t;
      norm = unitVector(cross((p1 - p0), (p2 - p0)));
  if (norm.z() < -0.9999 || norm.z() > 0.9999)
              rec.uvw.initFromWV( norm, Vector3(0, 1, 0) );
        else
                    rec.uvw.initFromWV( norm, Vector3(0, 0, 1) );
        
      //rec.uvw.initFromW(norm);   
		       
      return true;
   }
   return false;
}


BBox
Triangle::boundingBox (float time0, float time1)const
{
   const float epsilon = 0.00001f;
   Vector3 min;
   Vector3 max;

   min.setX(p0.x() < p1.x() ? p0.x() : p1.x());
   min.setY(p0.y() < p1.y() ? p0.y() : p1.y());
   min.setZ(p0.z() < p1.z() ? p0.z() : p1.z());

   min.setX(p2.x() < min.x() ? p2.x() : min.x());
   min.setY(p2.y() < min.y() ? p2.y() : min.y());
   min.setZ(p2.z() < min.z() ? p2.z() : min.z());
  
   max.setX(p0.x() > p1.x() ? p0.x() : p1.x());
   max.setY(p0.y() > p1.y() ? p0.y() : p1.y());
   max.setZ(p0.z() > p1.z() ? p0.z() : p1.z());
   
   max.setX(p2.x() > max.x() ? p2.x() : max.x());
   max.setY(p2.y() > max.y() ? p2.y() : max.y());
   max.setZ(p2.z() > max.z() ? p2.z() : max.z());

   min.setX(min.x() - epsilon);
   min.setY(min.y() - epsilon);
   min.setZ(min.z() - epsilon);

   max.setX(max.x() + epsilon);
   max.setY(max.y() + epsilon);
   max.setZ(max.z() + epsilon);
   return BBox(min, max);
}

bool
Triangle::randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, 
      Vector3& light_point, Vector3& N, float& pdf, rgb& radiance)const
{
   float temp  = sqrt(1.0f - seed.x());
   float beta  = (1.0f - temp);
   float gamma = temp*seed.y();
   light_point = (1.0f - beta - gamma)*p0 + beta*p1 + gamma*p2;

   Vector3 from_light = unitVector(viewpoint - light_point);
   ONB uvw;
   N = unitVector(cross((p1 - p0), (p2 - p0))); 
   uvw.initFromW(N);

   radiance = mptr->emittedRadiance(uvw, from_light, light_point,
         Vector2(0.0f,0.0f));

   return true;


   
}


