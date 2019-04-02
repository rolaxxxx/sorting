#ifndef GRID_COUNT_H
#define GRID_COUNT_H
#include "includes.h"
#include "dalele.h"
#include "skirstinys.h"
#include "map_bounds.h"

class MapAddAndParticleSearch
{
public:
    vector<INT> MAP_NEIGHBOR_SEARCH(Dalele dal, INT search_particle_id, MAP_BOUNDS map_boundai);

    bool NEIGHBOR_SEARCH( Dalele dal, vector<INT> temp_kaimynai, REAL4 kaimynai, MAP_BOUNDS map_boundai);

    void GRIDAS_MAP_ADD(REAL4 add_particle, MAP_BOUNDS boundai);

    map<INT, vector<INT> > getSUFORMUOTAS_GRIDAS() const;
    void setSUFORMUOTAS_GRIDAS(const map<INT, vector<INT> > &value);

    map<INT, vector<INT>> SUFORMUOTAS_GRIDAS;
};

#endif // GRID_COUNT_H
