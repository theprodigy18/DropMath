#pragma once

#include <DM_Vector.h>
#include <iostream>

using namespace Drop;

int main()
{
    Vec2 v1 {2.000001f, 2};
    Vec2 v2 {2.000003f, 2};
    std::cout << Vec2::Dot(v1, v2) << std::endl;

	bool eq = v1 == v2;
	std::cout << eq << std::endl;

    return 0;
}