
/*****************************************************************************\
 *                                                                           *
 *  filename : TriangleMesh.h                                                *
 *  author   : R. Keith Morley / Peter Shirley                               *
 *  last mod : 12/26/02                                                      *
 *                                                                           *
\*****************************************************************************/

#ifndef _MESH_TRI_H_
#define _MESH_TRI_H_

#include <Surface.h>

class Mesh;
class Material;

class MeshTriangle : public Surface
{
public:
   MeshTriangle();
   // takes in pointer to its Mesh and three indices into the arRay
   MeshTriangle(Mesh* _Mesh, int p0, int p1, int p2, int index);
   ~MeshTriangle();

   bool hit (const Ray& r,          // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time,
         SurfaceHitRecord& rec) const;
   bool shadowHit (const Ray& r,    // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time) const;

   BBox boundingBox (float time0, float time1)const;

   bool randomPoint(const Vector3&,
         const Vector2&,
         float time,
         Vector3&,
         Vector3&,
         float&,
         rgb&)const;

   // data members
   int p[3];
   int mat_index;
   Mesh* mesh_ptr;
};

class MeshTriangleUV : public Surface 
{
public:
   MeshTriangleUV();
   MeshTriangleUV(Mesh* _Mesh, int p0, int p1, int p2, int index);
   ~MeshTriangleUV();
   BBox boundingBox(float time0, float time1)const;

   bool hit (const Ray& r,          // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time,
         SurfaceHitRecord& rec) const;
   bool shadowHit (const Ray& r,    // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time) const;

   bool randomPoint(const Vector3&,
         const Vector2&,
         float time,
         Vector3&,
         Vector3&,
         float&,
         rgb&)const { return false; }


   // data members
   int p[3];
   int mat_index;
   Mesh* mesh_ptr;
};

class MeshTriangleN : public Surface 
{
public:
   MeshTriangleN();
   MeshTriangleN(Mesh* _Mesh, int p0, int p1, int p2, int index);
   ~MeshTriangleN();
   BBox boundingBox(float time0, float time1)const;

   bool hit (const Ray& r,          // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time,
         SurfaceHitRecord& rec) const;
   bool shadowHit (const Ray& r,    // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time  ) const;
   bool randomPoint(const Vector3&,
         const Vector2&,
         float time,
         Vector3&,
         Vector3&,
         float&,
         rgb&)const { return false; }

   // data members
   int p[3];
   int mat_index;
   Mesh* mesh_ptr;
};

class MeshTriangleUVN : public Surface 
{
public:
   MeshTriangleUVN();
   MeshTriangleUVN(Mesh* _Mesh, int p0, int p1, int p2, int index);
   ~MeshTriangleUVN();
   BBox boundingBox(float time0, float time1)const;

   bool hit (const Ray& r,          // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time,
         SurfaceHitRecord& rec) const;
   bool shadowHit (const Ray& r,    // Ray to be tested
         float tmin,                // min valid t val
         float tmax,                // max of t interval 
         float time  ) const;
   bool randomPoint(const Vector3&,
         const Vector2&,
         float time,
         Vector3&,
         Vector3&,
         float&,
         rgb&)const { return false; }

   // data members
   int p[3];
   int mat_index;
   Mesh* mesh_ptr;
};

inline bool
triangleIntersect(Ray r, const Vector3& p0, const Vector3& p1, const Vector3& p2,
      float tmin, float tmax, float& t, float& beta, float& gamma)
{
   float A = p0.x() - p1.x();
   float B = p0.y() - p1.y();
   float C = p0.z() - p1.z();

   float D = p0.x() - p2.x();
   float E = p0.y() - p2.y();
   float F = p0.z() - p2.z();

   float G = r.direction().x();
   float H = r.direction().y();
   float I = r.direction().z();

   float J = p0.x() - r.origin().x();
   float K = p0.y() - r.origin().y();
   float L = p0.z() - r.origin().z();

   float EIHF = E*I-H*F;
   float GFDI = G*F-D*I;
   float DHEG = D*H-E*G;

   float denom = (A*EIHF + B*GFDI + C*DHEG);

   beta = (J*EIHF + K*GFDI + L*DHEG) / denom;

   if (beta <= 0.0 || beta >= 1) return false;

   float AKJB = A*K - J*B;
   float JCAL = J*C - A*L;
   float BLKC = B*L - K*C;

   gamma = (I*AKJB + H*JCAL + G*BLKC)/denom;
   if (gamma <= 0.0 || beta + gamma >= 1.0) return false;

   t =  -(F*AKJB + E*JCAL + D*BLKC)/denom;
   return (t >= tmin && t <= tmax);
}

#endif // _MESH_TRI_H_

