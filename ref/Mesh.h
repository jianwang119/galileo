
/*****************************************************************************\
 *                                                                           *
 * filename : Mesh.h                                                         *
 * last mod : 08/06/02                                                       *
 * author   : R. Keith Morley / Peter Shirley                                *
 *                                                                           *
\*****************************************************************************/

#ifndef _MESH_H_
#define _MESH_H_ 1

#include <Vertex.h>
#include <Surface.h>
#include <Material.h>


class Mesh 
{
public:   
   ~Mesh() {}
   Material* getMaterial(int index)const;
   
   // data members
   Material**  mptr;
   Vector3*   verts;
   VertexUV*  vertUVs;
   VertexN*   vertNs;
   VertexUVN* vertUVNs;
};

inline
Material* Mesh::getMaterial(int index)const { return mptr[index]; }

#endif // _MESH_H_
