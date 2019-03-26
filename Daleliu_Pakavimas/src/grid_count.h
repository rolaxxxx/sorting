#ifndef GRID_COUNT_H
#define GRID_COUNT_H
#include "includes.h"
#include "dalele.h"
#include "geometry.h"
#include "map_bounds.h"

class GRID_COUNT
{




public:

    vector<INT> MAP_NEIGHBOR_SEARCH(REAL4_ARRAY F, INT search_particle_id, MAP_BOUNDS map_boundai);

    bool NEIGHBOR_SEARCH( REAL4_ARRAY F, vector<INT> temp_kaimynai, REAL4 kaimynai, MAP_BOUNDS map_boundai);

    void GRIDAS_MAP_ADD(REAL4 add_particle, MAP_BOUNDS boundai);

    map<INT, vector<INT> > getSUFORMUOTAS_GRIDAS() const;
    void setSUFORMUOTAS_GRIDAS(const map<INT, vector<INT> > &value);

    MAP_BOUNDS getMap_boundai() const;
    void setMap_boundai(const MAP_BOUNDS &value);

    Dalele getParticle() const;
    void setParticle(const Dalele &value);

private:
    map<INT, vector<INT>> SUFORMUOTAS_GRIDAS;
    Dalele particle;
};

#endif // GRID_COUNT_H
