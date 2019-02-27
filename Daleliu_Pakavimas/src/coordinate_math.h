#ifndef COORDINATE_MATH_H
#define COORDINATE_MATH_H
#include "dalele.h"
#include "map_bounds.h"
#include "includes.h"


class coordinate_math
{
public:
    REAL4 sphere_coords_4th;
    void coordinate_math_(Dalele &particle, MAP_BOUNDS boundai);
    void first_three_cells(Dalele &particle, MAP_BOUNDS boundai);
    REAL4 cross_prod(REAL4 &vec_a, REAL4 &vec_b);
    REAL dot_prod(REAL4 &vec_a, REAL4 &vec_b);

};

#endif // COORDINATE_MATH_H
