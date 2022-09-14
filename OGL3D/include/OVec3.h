#pragma once
#include "Oprerequisites.h"

class OVec3
{
public:
    OVec3()
    {
    }
    OVec3(f32 x, f32 y, f32 z): x(x), y(y), z(z)
    {
    }

public:
    f32 x = 0, y = 0, z = 0;
};