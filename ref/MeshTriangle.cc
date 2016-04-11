
/*****************************************************************************\
 *                                                                           *
 *  filename : MeshTriangle.cc                                               *
 *  author   : R. Keith Morley / Pete Shirley                                *
 *  last mod : 12/26/02                                                      *
 *                                                                           *
\*****************************************************************************/

#include <Mesh.h>
#include <MeshTriangle.h>

MeshTriangle::MeshTriangle(){}

MeshTriangle::MeshTriangle(Mesh* _Mesh, int p0, int p1, int p2, int index)
   : mesh_ptr(_Mesh), mat_index(index)
{
   p[0] = p0;
   p[1] = p1;
   p[2] = p2;
}

MeshTriangle::~MeshTriangle(){}

bool
MeshTriangle::hit(const Ray& r, float tmin, float tmax,
                  float time, SurfaceHitRecord& rec)const
{
   Vector3 p0((mesh_ptr->verts[p[0]]));
   Vector3 p1((mesh_ptr->verts[p[1]]));
   Vector3 p2((mesh_ptr->verts[p[2]]));

   float t, beta, gamma; 
   Vector3 dir = r.direction();
   Vector3 orig = r.origin();
   if (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma))
   {
      rec.p = rec.texp = r.pointAtParameter(t);
      rec.t = t;
      rec.mat_ptr = mesh_ptr->mptr[mat_index];
      Vector3 norm(unitVector(cross((p1 - p0), (p2 - p0))));
      rec.uvw.initFromW(norm);      

      return true;
   }
   return false;
   
}

bool
MeshTriangle::shadowHit(const Ray& r, float tmin, float tmax,
                  float time)const
{
   Vector3 p0((mesh_ptr->verts[p[0]]));
   Vector3 p1((mesh_ptr->verts[p[1]]));
   Vector3 p2((mesh_ptr->verts[p[2]]));

   float beta, gamma, t;
   return (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma));
}

BBox
MeshTriangle::boundingBox (float time0, float time1)const
{
   const float epsilon = 0.00001f;
   Vector3 min;
   Vector3 max;

   Vector3 p0((mesh_ptr->verts[p[0]]));
   Vector3 p1((mesh_ptr->verts[p[1]]));
   Vector3 p2((mesh_ptr->verts[p[2]]));

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
MeshTriangle::randomPoint(const Vector3&, const Vector2&, float time, 
      Vector3&, Vector3&, float&, rgb&)const
{
   cerr << "\n\n    WARNING -- " 
        << "randomPoint() not implemented for class Mesh \n\n";
   return false;
}

MeshTriangleUV::MeshTriangleUV(){}

MeshTriangleUV::MeshTriangleUV(Mesh* _Mesh, int p0, int p1, int p2, int index)
   : mesh_ptr(_Mesh), mat_index(index)
{
   p[0] = p0;
   p[1] = p1;
   p[2] = p2;
}

MeshTriangleUV::~MeshTriangleUV(){}

bool
MeshTriangleUV::hit(const Ray& r, float tmin, float tmax,
                  float time, SurfaceHitRecord& rec)const
{
   Vector3 p0((mesh_ptr->vertUVs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertUVs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertUVs[p[2]]).vertex);

   float t, beta, gamma; 
   Vector3 dir = r.direction();
   Vector3 orig = r.origin();
   if (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma))
   {
      // if prim is hit, fill hit_rec
      double alpha = 1.0 - beta - gamma;
      Vector2 u0((mesh_ptr->vertUVs[p[0]]).uv);
      Vector2 u1((mesh_ptr->vertUVs[p[1]]).uv);
      Vector2 u2((mesh_ptr->vertUVs[p[2]]).uv);
      rec.uv = Vector2(alpha*u0.x() + beta*u1.x() + gamma*u2.x(),
            alpha*u0.y() + beta*u1.y() + gamma*u2.y());
      
      rec.mat_ptr = mesh_ptr->mptr[mat_index];
      rec.p = rec.texp = r.pointAtParameter(t);
      rec.t = t;

      Vector3 normal = unitVector(cross((p1 - p0), (p2 - p0)));
      rec.uvw.initFromW(normal);      
      return true;
   }
   return false;
}


bool
MeshTriangleUV::shadowHit(const Ray& r, float tmin, float tmax,
                  float time)const
{
   Vector3 p0((mesh_ptr->vertUVs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertUVs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertUVs[p[2]]).vertex);

   float beta, gamma, t;
   return (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma));
}

BBox
MeshTriangleUV::boundingBox(float time0, float time1)const
{
   const float epsilon = 0.00001f;
   Vector3 min;
   Vector3 max;

   Vector3 p0((mesh_ptr->vertUVs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertUVs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertUVs[p[2]]).vertex);

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

MeshTriangleN::MeshTriangleN(){}

MeshTriangleN::MeshTriangleN(Mesh* _Mesh, int p0, int p1, int p2, int index)
   : mesh_ptr(_Mesh), mat_index(index)
{
   p[0] = p0;
   p[1] = p1;
   p[2] = p2;
}

MeshTriangleN::~MeshTriangleN(){}

bool
MeshTriangleN::hit(const Ray& r, float tmin, float tmax,
                  float time, SurfaceHitRecord& rec)const
{
   Vector3 p0((mesh_ptr->vertNs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertNs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertNs[p[2]]).vertex);

   float t, beta, gamma; 
   Vector3 dir = r.direction();
   Vector3 orig = r.origin();
   if (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma))
   {
      // if prim is hitfill hit_rec
      
      rec.mat_ptr = mesh_ptr->mptr[mat_index];
      rec.p = rec.texp = r.pointAtParameter(t);
      rec.t = t;

      // interpolate normal
      p0 = ((mesh_ptr->vertNs[p[0]]).normal);
      p1 = ((mesh_ptr->vertNs[p[1]]).normal);
      p2 = ((mesh_ptr->vertNs[p[2]]).normal);
      
      double alpha = 1.0 - beta - gamma;
      Vector3 normal = unitVector(alpha*p0 + beta*p1 + gamma*p2);
      rec.uvw.initFromW(normal);      
      return true;
   }
   return false;
}

bool
MeshTriangleN::shadowHit(const Ray& r, float tmin, float tmax,
                  float time)const
{
   Vector3 p0((mesh_ptr->vertNs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertNs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertNs[p[2]]).vertex);

   float beta, gamma, t;
   return (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma));
}

BBox
MeshTriangleN::boundingBox (float time0, float time1)const
{
   const float epsilon = 0.00001f;
   Vector3 min;
   Vector3 max;

   Vector3 p0((mesh_ptr->vertNs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertNs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertNs[p[2]]).vertex);

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

MeshTriangleUVN::MeshTriangleUVN(Mesh* _Mesh, int p0, int p1, int p2, int index)
   : mesh_ptr(_Mesh), mat_index(index)
{
   p[0] = p0;
   p[1] = p1;
   p[2] = p2;
}
bool
MeshTriangleUVN::hit(const Ray& r, float tmin, float tmax,
                  float time, SurfaceHitRecord& rec)const
{
   Vector3 p0((mesh_ptr->vertUVNs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertUVNs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertUVNs[p[2]]).vertex);

   float t, beta, gamma; 
   Vector3 dir = r.direction();
   Vector3 orig = r.origin();
   if (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma))
   {
      // if prim is hitfill hit_rec
      double alpha = 1.0 - beta - gamma;
      Vector2 u0((mesh_ptr->vertUVNs[p[0]]).uv);
      Vector2 u1((mesh_ptr->vertUVNs[p[1]]).uv);
      Vector2 u2((mesh_ptr->vertUVNs[p[2]]).uv);
      rec.uv = Vector2(alpha*u0.x() + beta*u1.x() + gamma*u2.x(),
            alpha*u0.y() + beta*u1.y() + gamma*u2.y());
      
      rec.mat_ptr = mesh_ptr->mptr[mat_index];
      rec.p = rec.texp = r.pointAtParameter(t);
      rec.t = t;

      // interpolate normal
      p0 = ((mesh_ptr->vertUVNs[p[0]]).normal);
      p1 = ((mesh_ptr->vertUVNs[p[1]]).normal);
      p2 = ((mesh_ptr->vertUVNs[p[2]]).normal);
      
      Vector3 normal = unitVector(alpha*p0 + beta*p1 + gamma*p2);
      rec.uvw.initFromW(normal);      
      return true;
   }
   return false;
}

bool
MeshTriangleUVN::shadowHit(const Ray& r, float tmin, float tmax,
                  float time)const
{
   Vector3 p0((mesh_ptr->vertUVNs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertUVNs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertUVNs[p[2]]).vertex);

   float beta, gamma, t;
   return (triangleIntersect(r, p0, p1, p2, tmin, tmax, t, beta, gamma));
}

BBox
MeshTriangleUVN::boundingBox (float time0, float time1)const
{
   const float epsilon = 0.00001f;
   Vector3 min;
   Vector3 max;

   Vector3 p0((mesh_ptr->vertUVNs[p[0]]).vertex);
   Vector3 p1((mesh_ptr->vertUVNs[p[1]]).vertex);
   Vector3 p2((mesh_ptr->vertUVNs[p[2]]).vertex);

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

