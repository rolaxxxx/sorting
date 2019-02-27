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
    kordinaciu_skaiciavimas.coordinate_math_(particle, boundai);
    particle.Triju_DaleliuGeneracija(boundai, particle.Distribution, particle.F);
    gridas.GRIDAS(boundai, particle.F ,gridas.SUFORMUOTAS_GRIDAS, gridas.OFFSET, gridas.IDS);
}


