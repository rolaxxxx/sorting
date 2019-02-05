#ifndef DALELE_H
#define DALELE_H
#include "includes.h"
#include "map_bounds.h"
class Dalele {
public:

    REAL4_ARRAY koordinates;
    INT min, max;
    REAL spindulys;
    REAL_ARRAY Distribution;
    INT daleliuKiekis;
    REAL4 MIN_BOUNDS;
    REAL4 MAX_BOUNDS;
    REAL4_ARRAY F; // daleles salia kuriu dar galima kazka lipdyti
    REAL4_ARRAY V; // daleles kurios yra iskeltos is F ir jau turi visus kaimynus
    void DalelesDuomenuApibrezimas();
    void Triju_DaleliuGeneracija(INT min, INT max, MAP_BOUNDS map_boundai, Dalele particle);
};

#endif // DALELE_H
