#include<OVertexArrayObject.hpp>
#include<glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferData& data)
{
 glGenBuffers(1,&m_vertexBufferId);
 glGenVertexArrays(1,&m_vertexArrayObjectId);

 glBindVertexArray(m_vertexArrayObjectId);

 glBindBuffer(GL_ARRAY_BUFFER,m_vertexBufferId);
 glBufferData(GL_ARRAY_BUFFER,data.vertexSize*data.listSize,data.verticesList,GL_STATIC_DRAW);

 glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,data.vertexSize,0);

 glBindVertexArray(0);
}

OVertexArrayObject::~OVertexArrayObject()
{
}

//min 27:41