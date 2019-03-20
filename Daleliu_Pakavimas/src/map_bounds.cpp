#include "map_bounds.h"

REAL4 MAP_BOUNDS::getMAP_BOUNDS_MIN() const
{
    return MAP_BOUNDS_MIN;
}

void MAP_BOUNDS::setMAP_BOUNDS_MIN(const REAL4 &value)
{
    MAP_BOUNDS_MIN = value;
}

REAL4 MAP_BOUNDS::getMAP_BOUNDS_MAX() const
{
    return MAP_BOUNDS_MAX;
}

void MAP_BOUNDS::setMAP_BOUNDS_MAX(const REAL4 &value)
{
    MAP_BOUNDS_MAX = value;
}

REAL MAP_BOUNDS::getCELLSIZE() const
{
    return CELLSIZE;
}

void MAP_BOUNDS::setCELLSIZE(const REAL &value)
{
    CELLSIZE = value;
}

INT MAP_BOUNDS::getNx() const
{
    return Nx;
}

void MAP_BOUNDS::setNx(const INT &value)
{
    Nx = value;
}

INT MAP_BOUNDS::getNy() const
{
    return Ny;
}

void MAP_BOUNDS::setNy(const INT &value)
{
    Ny = value;
}

INT MAP_BOUNDS::getNz() const
{
    return Nz;
}

void MAP_BOUNDS::setNz(const INT &value)
{
    Nz = value;
}

void MAP_BOUNDS::MAP_DUOMENYS(REAL4 &MAP_BOUNDS_MIN, REAL4 &MAP_BOUNDS_MAX, REAL &CELLSIZE, INT &Nx, INT &Ny, INT &Nz){
    REAL4 TEMP_MIN, TEMP_MAX;

    //cin >> TEMP_MIN[0] >> TEMP_MIN[1] >> TEMP_MIN[2];
        TEMP_MIN[0]=0;
        TEMP_MAX[0]=10;

        TEMP_MIN[1]=0;
        TEMP_MAX[1]=10;

        TEMP_MIN[2]=0;
        TEMP_MAX[2]=10;
    MAP_BOUNDS_MIN = TEMP_MIN;
    MAP_BOUNDS_MAX = TEMP_MAX;
    Nx=ceil((MAP_BOUNDS_MAX[0]-MAP_BOUNDS_MIN[0])/CELLSIZE);
    Ny=ceil((MAP_BOUNDS_MAX[1]-MAP_BOUNDS_MIN[1])/CELLSIZE);
    Nz=ceil((MAP_BOUNDS_MAX[2]-MAP_BOUNDS_MIN[2])/CELLSIZE);
}
