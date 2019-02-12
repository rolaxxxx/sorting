#include "grid_count.h"
#include "dalele.h"
void GRID_COUNT::GRIDAS(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, INT> &SUFORMUOTAS_GRIDAS){
    REAL4 temp_coords;
    INT TEMP_ID;
    map<INT, INT>::iterator it;
    REAL4 TEMP_PARTICLE_COORDS;
            INT indeksas=0;
    INT daleliuKiekis;
    for(int i=0;i<F.size();i++){
         //cout << "hi "<< endl;
        TEMP_PARTICLE_COORDS=F[i];
        temp_coords[0]=(TEMP_PARTICLE_COORDS[0]-map_boundai.MAP_BOUNDS_MIN[0])/map_boundai.CELLSIZE;
        temp_coords[1]=(TEMP_PARTICLE_COORDS[1]-map_boundai.MAP_BOUNDS_MIN[1])/map_boundai.CELLSIZE;
        temp_coords[2]=(TEMP_PARTICLE_COORDS[2]-map_boundai.MAP_BOUNDS_MIN[2])/map_boundai.CELLSIZE;
        TEMP_ID=temp_coords[0]+temp_coords[1]*map_boundai.Nx+temp_coords[2]*map_boundai.Nx*map_boundai.Ny;
        //cout << TEMP_PARTICLE_COORDS[0] << " " << TEMP_PARTICLE_COORDS[1] << " " << TEMP_PARTICLE_COORDS[2] << endl;
        //cout << map_boundai.MAP_BOUNDS_MIN[0] << " " << map_boundai.MAP_BOUNDS_MIN[1] << " " << map_boundai.MAP_BOUNDS_MIN[2] << " " << map_boundai.CELLSIZE << endl;
        //cout << "suskaiciuotas temp id " << TEMP_ID  << endl;
        it = SUFORMUOTAS_GRIDAS.find(TEMP_ID);
            if(it != SUFORMUOTAS_GRIDAS.end())
                SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second++;
            else {
                SUFORMUOTAS_GRIDAS.insert(pair<INT, INT>(TEMP_ID, indeksas));
                SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second++;
                //cout <<SUFORMUOTAS_GRIDAS.find(TEMP_ID)->first << " " << SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second++;

         }
    }
}
