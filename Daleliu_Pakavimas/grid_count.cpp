#include "grid_count.h"
#include "dalele.h"
void GRID_COUNT::GRIDAS(REAL4 MAP_BOUNDS_MIN, REAL4 MAP_BOUNDS_MAX, INT CELLSIZE, INT Nx, INT Ny, INT Nz, REAL4_ARRAY F, map<INT, INT> &SUFORMUOTAS_GRIDAS){
    REAL4 temp_coords;
    INT TEMP_ID;
    map<INT, INT>::iterator it;
    REAL4 TEMP_PARTICLE_COORDS;
            INT indeksas=0;
    INT daleliuKiekis;
    for(int i=0;i<F.size();i++){
         cout << "hi "<< endl;
        TEMP_PARTICLE_COORDS=F[i];
        temp_coords[0]=(TEMP_PARTICLE_COORDS[0]-MAP_BOUNDS_MIN[0])/CELLSIZE;
        temp_coords[1]=(TEMP_PARTICLE_COORDS[1]-MAP_BOUNDS_MIN[1])/CELLSIZE;
        temp_coords[2]=(TEMP_PARTICLE_COORDS[2]-MAP_BOUNDS_MIN[2])/CELLSIZE;
        TEMP_ID=temp_coords[0]+temp_coords[1]*Nx+temp_coords[2]*Nx*Ny;

        it = SUFORMUOTAS_GRIDAS.find(TEMP_ID);
            if(it != SUFORMUOTAS_GRIDAS.end())
                SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second++;
            else {
                SUFORMUOTAS_GRIDAS.insert(pair<INT, INT>(TEMP_ID, indeksas));
                SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second++;

         }
    }
}
