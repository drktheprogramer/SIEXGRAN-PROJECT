#include<OVertexArrayObject.hpp>
#include<glad.h>

OVertexArrayObject::OVertexArrayObject()
{
 glGenBuffers(1,&m_vertexBufferId);
 glGenVertexArrays(1,&m_vertexArrayObjectId);

 glBindVertexArray(m_vertexArrayObjectId);

 glBindBuffer(GL_ARRAY_BUFFER,m_vertexBufferId);
 glBufferData(GL_ARRAY_BUFFER,);

 glBindVertexArray(0);
}

OVertexArrayObject::~OVertexArrayObject()
{
}