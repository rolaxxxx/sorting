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
   /*for(auto it=gridas.SUFORMUOTAS_GRIDAS.begin();it!=gridas.SUFORMUOTAS_GRIDAS.end();it++)
    {
        testas=it->second;
        for(auto it2=testas.begin();it2!=testas.end();it2++)
        {
            cout << *it2 << endl;
        }
    }
*/
    gridas.search_particle_id=1;
    /*for(auto it=gridas.SUFORMUOTAS_GRIDAS.begin();it!=gridas.SUFORMUOTAS_GRIDAS.end();it++){
        cout << it->first << endl;
        for(vector<INT>::iterator it2=gridas.SUFORMUOTAS_GRIDAS.begin();it2!=gridas.SUFORMUOTAS_GRIDAS.end();it2++){
            cout << *it2 << endl;
        }
    }
    */
    gridas.MAP_NEIGHBOR_SEARCH(boundai, particle.F, gridas.SUFORMUOTAS_GRIDAS, gridas.search_particle_id, gridas.rasti_kaimynu_indexai);

   // cout << gridas.rasti_kaimynu_indexai.size() << endl;
    kordinaciu_skaiciavimas.coordinate_math_(particle, boundai, gridas);

    particle.Triju_DaleliuGeneracija(boundai, particle.Distribution, particle.F);


    //gridas.Neighbor_Search(boundai, F, gridas.SUFORMUOTAS_GRIDAS, gridas.search_particle_id, gridas.rasti_kaimynu_indexai);
    //cout << gridas.SUFORMUOTAS_GRIDAS.size() << endl;
    //for (std::map<INT , vector<INT>>::iterator it=gridas.SUFORMUOTAS_GRIDAS.begin(); it!=gridas.SUFORMUOTAS_GRIDAS.end(); ++it)
        //for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            //cout << *it2 << " ";
    for(int i=0;i<particle.F.size();i++)
    {
        //cout << particle.F[i] << endl;
    }

}
