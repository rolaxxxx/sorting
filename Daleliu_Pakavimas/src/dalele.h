#ifndef DALELE_H
#define DALELE_H
#include "includes.h"
#include "map_bounds.h"
#include "skirstinys.h"
class Dalele: public MAP_BOUNDS{

public:
    void particle_Generator( MAP_BOUNDS boundai);

    vector<REAL4> getF() const;
    void setF(const vector<REAL4> &value);
    void setFvec(const REAL4 value);

    vector<REAL4> getV() const;
    void setV(const vector<REAL4> &value);

    vector<REAL4> F; // aktyvus frontas kuriame ieskau kaimynu
    vector<REAL4> V; // visu daleliu vektorius kuri naudoju atvaizdavimui
};

#endif // DALELE_H
