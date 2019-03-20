#ifndef DALELE_H
#define DALELE_H
#include "includes.h"
#include "map_bounds.h"
#include "geometry.h"
class Dalele: public MAP_BOUNDS{

public:
    void particle_Generator(REAL_ARRAY distribution);
private:
    MAP_BOUNDS map_boundai;
    REAL4_ARRAY F;
};

#endif // DALELE_H
