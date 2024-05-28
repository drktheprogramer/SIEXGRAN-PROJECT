#pragma once
#include<OVec4.hpp>
#include<ORect.hpp>

struct OGraphicsEngine {
	OGraphicsEngine();
	~OGraphicsEngine();

	void clear(const OVec4& color);
 void setViewport(const ORect& size);
};

