#ifndef GRID_COUNT_H
#define GRID_COUNT_H
#include "includes.h"
#include "dalele.h"
#include "geometry.h"
#include "map_bounds.h"

class GRID_COUNT
{
public:
    map<INT, vector<INT>> SUFORMUOTAS_GRIDAS;
    INT_ARRAY OFFSET;
    INT_ARRAY IDS;
    INT search_particle_id;
    INT_ARRAY rasti_kaimynu_indexai;
    void GRIDAS_MAP_ADD(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, vector<INT>> &SUFORMUOTAS_GRIDAS);
    void MAP_NEIGHBOR_SEARCH(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, vector<INT>> &SUFORMUOTAS_GRIDAS, INT search_particle_id, INT_ARRAY &rasti_kaimynu_indexai);
    void Neighbor_Search(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, vector<INT>> SUFORMUOTAS_GRIDAS, INT search_particle_id, INT_ARRAY &rasti_kaimynu_indexai, INT_ARRAY OFFSET);


};

#endif // GRID_COUNT_H
