
/*****************************************************************************\
 *                                                                           *
 *  filename :  Vertex.h                                                     *
 *  author   :  R. Keith Morley                                              *
 *  last mod :  1/24/03                                                      *
 *                                                                           *
\*****************************************************************************/

#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <Vector2.h>
#include <Vector3.h>

struct VertexUV
{
   Vector3 vertex;
   Vector2 uv; 
};

struct VertexN
{
   Vector3 vertex;
   Vector3 normal;
};

struct VertexUVN
{
   Vector3 vertex;
   Vector3 normal;
   Vector2 uv;
};

#endif // _VERTEX_H_
