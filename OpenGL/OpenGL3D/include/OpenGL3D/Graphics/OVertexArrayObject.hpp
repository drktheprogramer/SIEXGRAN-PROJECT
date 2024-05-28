#pragma once
#include<OPrerequisites.hpp>

struct OVertexArrayObject {
 OVertexArrayObject();
 ~OVertexArrayObject();

private:
 ui32 m_vertexBufferId=0;
 ui32 m_vertexArrayObjectId=0;
};