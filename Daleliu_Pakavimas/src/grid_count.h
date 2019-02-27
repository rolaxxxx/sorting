#ifndef GRID_COUNT_H
#define GRID_COUNT_H
#include "includes.h"
#include "dalele.h"
#include "geometry.h"
#include "map_bounds.h"

class GRID_COUNT
{
public:
    map<INT, INT> SUFORMUOTAS_GRIDAS;
    INT_ARRAY OFFSET;
    INT_ARRAY IDS;
    void GRIDAS(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, INT> &SUFORMUOTAS_GRIDAS, INT_ARRAY &OFFSET, INT_ARRAY &IDS);
    /*GRID_COUNT operator-()  {
        REAL4 TEMP_PARTICLE_COORDS;
        MAP_BOUNDS map_boundai;
        REAL4 coord_rez;
         coord_rez=TEMP_PARTICLE_COORDS-map_boundai.MAP_BOUNDS_MIN;
                 return coord_rez;
       }
      */
};

#endif // GRID_COUNT_H
