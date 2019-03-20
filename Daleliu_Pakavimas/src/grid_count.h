#ifndef GRID_COUNT_H
#define GRID_COUNT_H
#include "includes.h"
#include "dalele.h"
#include "geometry.h"
#include "map_bounds.h"

class GRID_COUNT
{
    void GRIDAS_MAP_ADD(REAL4 add_particle);
    vector<INT> MAP_NEIGHBOR_SEARCH(REAL4_ARRAY F, INT search_particle_id);
    bool Neighbor_Search( REAL4_ARRAY F);

private:
    map<INT, vector<INT>> SUFORMUOTAS_GRIDAS;
    MAP_BOUNDS map_boundai;
    Dalele particle;
};

#endif // GRID_COUNT_H
