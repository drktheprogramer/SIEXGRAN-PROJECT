#pragma once
#include<OPrerequisites.hpp>

struct OVertexArrayObject {
 OVertexArrayObject(const OVertexBufferData& data);
 ~OVertexArrayObject();

private:
 ui32 m_vertexBufferId=0;
 ui32 m_vertexArrayObjectId=0;
};