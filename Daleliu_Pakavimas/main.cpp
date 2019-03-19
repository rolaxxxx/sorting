#include "includes.h"
#include "geometry.h"
#include "dalele.h"
#include "grid_count.h"
#include "map_bounds.h"
#include "coordinate_math.h"
int main(int, char *[])
{
    Dalele particle;
    Geometry geometrija;
    MAP_BOUNDS boundai;
    GRID_COUNT gridas;
    coordinate_math kordinaciu_skaiciavimas;

    particle.DalelesDuomenuApibrezimas();
    boundai.MAP_DUOMENYS(boundai.MAP_BOUNDS_MIN,boundai.MAP_BOUNDS_MAX,boundai.CELLSIZE, boundai.Nx, boundai.Ny, boundai.Nz);
    geometrija.skirstinioFormavimas(particle);
    kordinaciu_skaiciavimas.first_three_cells(particle, boundai);
    kordinaciu_skaiciavimas.coordinate_math_(particle, boundai, gridas);
    particle.Triju_DaleliuGeneracija(boundai, particle.Distribution, particle.F);
    gridas.GRIDAS_MAP_ADD(boundai, particle.F, gridas.SUFORMUOTAS_GRIDAS);
    //cout << gridas.rasti_kaimynu_indexai.size() << endl;

    vector<INT> testas;

    INT spind;
    spind=rand()%particle.F.size(); // spindulio gavimas is pasiskirstymo. Kintamieji kolkas vienodi;

    for(INT i=0 ;i<10;i++){
    //cout << gridas.rasti_kaimynu_indexai.size() << endl;
    INT_ARRAY tuscias;
    gridas.rasti_kaimynu_indexai.clear();

    //cout <<" po istrinimo " <<  gridas.rasti_kaimynu_indexai.size() << endl;
    spind=rand()%particle.F.size();
    //cout << spind << endl;
    gridas.search_particle_id=spind;
    //cout << gridas.rasti_kaimynu_indexai.size() << endl;
    gridas.MAP_NEIGHBOR_SEARCH(boundai, particle.F, gridas.SUFORMUOTAS_GRIDAS, gridas.search_particle_id, gridas.rasti_kaimynu_indexai);
   // cout << gridas.rasti_kaimynu_indexai.size() << endl;
    kordinaciu_skaiciavimas.coordinate_math_(particle, boundai, gridas);
    gridas.GRIDAS_MAP_ADD(boundai, particle.F, gridas.SUFORMUOTAS_GRIDAS);
    particle.Triju_DaleliuGeneracija(boundai, particle.Distribution, particle.F);
    //cout << " gale for ciklo " << gridas.rasti_kaimynu_indexai.size() << endl;

    }

}
