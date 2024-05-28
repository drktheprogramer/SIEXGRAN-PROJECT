#include<OVertexArrayObject.hpp>
#include<glad.h>

OVertexArrayObject::OVertexArrayObject()
{
 glGenBuffers(1,&m_vertexBufferId);
 glGenVertexArrays(1, &m_vertexArrayObjectId);
}

OVertexArrayObject::~OVertexArrayObject()
{
}