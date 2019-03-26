#ifndef MAP_BOUNDS_H
#define MAP_BOUNDS_H
#include "includes.h"

class MAP_BOUNDS
{
public:
    REAL4 getMAP_BOUNDS_MIN() const;
    void setMAP_BOUNDS_MIN(const REAL4 &value);

    REAL4 getMAP_BOUNDS_MAX() const;
    void setMAP_BOUNDS_MAX(const REAL4 &value);

    REAL getCELLSIZE() const;
    void setCELLSIZE(const REAL &value);

    INT getNx() const;
    void setNx(const INT &value);

    INT getNy() const;
    void setNy(const INT &value);

    INT getNz() const;
    void setNz(const INT &value);

    void MAP_DUOMENYS();

private:
    REAL4 MAP_BOUNDS_MIN;
    REAL4 MAP_BOUNDS_MAX;
    REAL CELLSIZE=3;
    INT Nx, Ny, Nz;

};

#endif // MAP_BOUNDS_H
