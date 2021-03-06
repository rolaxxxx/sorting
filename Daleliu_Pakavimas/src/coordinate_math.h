#ifndef COORDINATE_MATH_H
#define COORDINATE_MATH_H
#include "dalele.h"
#include "map_bounds.h"
#include "includes.h"
#include "mapaddandparticlesearch.h"


class coordinate_math
{
public:
    vector<REAL4> coordinate_math_(vector<REAL4> particles, REAL radius); // grazina teigiama ir neigiama reiksmes
    void add_cell(Dalele &particle, REAL4 cell, REAL spind); // prideda dalele prie F vektoriaus
    REAL4 cross_prod(REAL4 &vec_a, REAL4 &vec_b);
    REAL dot_prod(REAL4 &vec_a, REAL4 &vec_b);
    REAL4 testine_matematika(REAL4 S1, REAL4 S2, REAL4 S3, REAL spindulys);
private:
};

#endif // COORDINATE_MATH_H
