#pragma once
#include<OVec4.hpp>
#include<ORect.hpp>
#include<OPrerequisites.hpp>

struct OGraphicsEngine {
	OGraphicsEngine();
	~OGraphicsEngine();

OVertexArrayObjectPtr createArrayObject(const OVertexBufferData& data);
	void clear(const OVec4& color);
 void setViewport(const ORect& size);
 void setVertexArrayObject(const OVertexArrayObjectPtr& vao);
 void drawTriangles(ui32 vertexCount,ui32 offset);
 
};

