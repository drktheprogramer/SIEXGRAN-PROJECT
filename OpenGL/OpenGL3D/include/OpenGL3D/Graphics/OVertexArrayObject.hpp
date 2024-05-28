#pragma once
#include<OPrerequisites.hpp>

struct OVertexArrayObject {
 OVertexArrayObject();
 ~OVertexArrayObject();

private:
 ui32 m_vertexBufferId=0;
};