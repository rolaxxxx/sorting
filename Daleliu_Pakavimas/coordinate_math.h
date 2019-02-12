#ifndef COORDINATE_MATH_H
#define COORDINATE_MATH_H
#include "dalele.h"
#include "map_bounds.h"
#include "includes.h"

class coordinate_math
{
public:
    REAL4 sphere_coords_4th;
    void coordinate_math_(Dalele particle, REAL4 &sphere_coords_4th);
};

#endif // COORDINATE_MATH_H
