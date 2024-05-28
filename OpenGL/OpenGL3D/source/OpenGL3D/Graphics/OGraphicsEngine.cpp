#include<OGraphicsEngine.hpp>
#include<glad_wgl.h>
#include<glad.h>
#include<cassert>
#include<stdexcept>


void OGraphicsEngine::clear(const OVec4 &color)
{
	glClearColor(color.x,color.y,color.z,color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OGraphicsEngine::setViewport(const ORect& size)
{
 glViewport(size.left, size.top, size.width, size.heigth);

}

OVertexArrayObjectPtr OGraphicsEngine::createArrayObject(const OVertexBufferData& data)
{
 return std::make_shared<OVertexArrayObjectPtr>(data);
}
