#pragma once
#include<OPrerequisites.hpp>

struct OVec4 {
    OVec4()
    {

    }
    OVec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)
    {

    }
    ~OVec4()
    {

    }

//  >>  MEMBERS
   f32 x=0,y=0,z=0,w=0;
};
