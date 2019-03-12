#ifndef MAP_BOUNDS_H
#define MAP_BOUNDS_H
#include "includes.h"

class MAP_BOUNDS
{
public:
    REAL4 MAP_BOUNDS_MIN;
    REAL4 MAP_BOUNDS_MAX;
    REAL CELLSIZE=2;
    INT Nx, Ny, Nz;
    void MAP_DUOMENYS(REAL4 &MAP_BOUNDS_MIN,  REAL4 &MAP_BOUNDS_MAX, REAL &CELLSIZE, INT &Nx, INT &Ny, INT &Nz);
};

#endif // MAP_BOUNDS_H
