#ifndef COORDINATE_MATH_H
#define COORDINATE_MATH_H
#include "dalele.h"
#include "map_bounds.h"
#include "includes.h"
#include "grid_count.h"


class coordinate_math
{
public:
    REAL4 sphere_coords_4th;
    void coordinate_math_(Dalele &particle, MAP_BOUNDS boundai, GRID_COUNT gridas);
    void first_three_cells(Dalele &particle, MAP_BOUNDS boundai);
    REAL4 cross_prod(REAL4 &vec_a, REAL4 &vec_b);
    REAL dot_prod(REAL4 &vec_a, REAL4 &vec_b);
    void testine_matematika(REAL4 S1, REAL4 S2, REAL4 S3, REAL spindulys);

};

#endif // COORDINATE_MATH_H
