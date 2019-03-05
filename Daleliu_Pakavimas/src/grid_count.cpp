#include "grid_count.h"
#include "dalele.h"
void GRID_COUNT::GRIDAS_MAP_ADD(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, vector<INT>> &SUFORMUOTAS_GRIDAS){
    REAL4 temp_coords;
    INT TEMP_ID;
    map<INT, vector<INT>>::iterator it;
    REAL4 TEMP_PARTICLE_COORDS;
            INT indeksas=0;
    INT daleliuKiekis;
    for(int i=0;i<F.size();i++){
         //cout << "hi "<< endl;
        TEMP_PARTICLE_COORDS=F[i];
        temp_coords[0]=floor((TEMP_PARTICLE_COORDS[0]-map_boundai.MAP_BOUNDS_MIN[0])/map_boundai.CELLSIZE);
        temp_coords[1]=floor((TEMP_PARTICLE_COORDS[1]-map_boundai.MAP_BOUNDS_MIN[1])/map_boundai.CELLSIZE);
        temp_coords[2]=floor((TEMP_PARTICLE_COORDS[2]-map_boundai.MAP_BOUNDS_MIN[2])/map_boundai.CELLSIZE);
        TEMP_ID=temp_coords[0]+temp_coords[1]*map_boundai.Nx+temp_coords[2]*map_boundai.Nx*map_boundai.Ny;
        //cout << temp_coords << endl;
        //cout << TEMP_ID << endl;
        //cout << TEMP_PARTICLE_COORDS[0] << " " << TEMP_PARTICLE_COORDS[1] << " " << TEMP_PARTICLE_COORDS[2] << endl;
        //cout << map_boundai.MAP_BOUNDS_MIN[0] << " " << map_boundai.MAP_BOUNDS_MIN[1] << " " << map_boundai.MAP_BOUNDS_MIN[2] << " " << map_boundai.CELLSIZE << endl;
        //cout << "suskaiciuotas temp id " << TEMP_ID  << endl;
        it = SUFORMUOTAS_GRIDAS.find(TEMP_ID);
            if(it != SUFORMUOTAS_GRIDAS.end())
                SUFORMUOTAS_GRIDAS[TEMP_ID].push_back(i);
            else {
                SUFORMUOTAS_GRIDAS.insert(pair<INT, vector<INT>>(TEMP_ID, vector<INT>()));
                SUFORMUOTAS_GRIDAS[TEMP_ID].push_back(i);
                //cout <<SUFORMUOTAS_GRIDAS.find(TEMP_ID)->first << " " << SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second << endl;
         }
    }
}
void GRID_COUNT::MAP_NEIGHBOR_SEARCH(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, vector<INT>> &SUFORMUOTAS_GRIDAS, INT search_particle_index, INT_ARRAY rasti_kaimynu_indexai){
    REAL4 temp, tempPID;
    REAL4 coords, pid_coords;
    INT particle_ammount;
    INT offset_val;
    INT pid;
    REAL L;
    REAL temp_cur_rad, temp_pid_rad, two_vector_length, temp_ilgis;
    REAL TEMP_LEN;
    INT TEMP_ID;
    vector<INT> PARTICLES;
    INT kiekis=0;
    temp=F[search_particle_index];
    coords[0]=(temp[0]-map_boundai.MAP_BOUNDS_MIN[0])/map_boundai.CELLSIZE;
    coords[1]=(temp[1]-map_boundai.MAP_BOUNDS_MIN[1])/map_boundai.CELLSIZE;
    coords[2]=(temp[2]-map_boundai.MAP_BOUNDS_MIN[2])/map_boundai.CELLSIZE;
    temp_cur_rad=temp[3];
    temp[3]=0;

    for(INT x=coords[0]-1;x<=coords[0]+1;x++){
        for(INT y=coords[1]-1;y<=coords[1]+1;y++){
            for(INT z=coords[2]-1;z<=coords[2]+1;z++){
                if(x<map_boundai.Nx&&y<map_boundai.Ny&&z<map_boundai.Nz&&x>=0&&y>=0&&z>=0){
                     TEMP_ID=x+y*map_boundai.Nx+z*map_boundai.Nx*map_boundai.Ny;

                         PARTICLES=SUFORMUOTAS_GRIDAS.find(TEMP_ID)->second;
                            for(int g=0;g<PARTICLES.size();g++){
                               pid=PARTICLES[g];
                               //cout << particle_ammount << endl;
                                if(pid!=search_particle_index)
                                {
                                    tempPID=F[pid];
                                    temp_pid_rad=tempPID[3];
                                    tempPID[3]=0;
                                    TEMP_LEN=sqrt(pow(temp[0]-tempPID[0],2)+pow(temp[1]-tempPID[1],2)+pow(temp[2]-tempPID[2],2));
                                    L=TEMP_LEN-(temp_cur_rad+temp_pid_rad);
                                    //cout << L << endl;
                                    if(L<=0){
                                        rasti_kaimynu_indexai[kiekis]=pid;
                                        cout << pid << endl;
                                        kiekis++;
                                    }
                                    if(kiekis==3)
                                        break;

                                }
                      }
                }
            }
        }
    }
}
/*void GRID_COUNT::Neighbor_Search(MAP_BOUNDS map_boundai, REAL4_ARRAY F, map<INT, vector<INT>> SUFORMUOTAS_GRIDAS, INT search_particle_index, INT_ARRAY &rasti_kaimynu_indexai, INT_ARRAY OFFSET){

    REAL4 temp, tempPID;
    REAL4 coords, pid_coords;
    INT particle_ammount;
    INT offset_val;
    REAL L;
    REAL TEMP_LEN;
    INT TEMP_ID;
    INT kiekis=0; // rastu kaimynu kiekis kai jis pasiekia tris kaimynu paieska sustoja
    REAL temp_cur_rad, temp_pid_rad, two_vector_length, temp_ilgis;
    temp=F[search_particle_index];
    coords[0]=(temp[0]-map_boundai.MAP_BOUNDS_MIN[0])/map_boundai.CELLSIZE;
    coords[1]=(temp[1]-map_boundai.MAP_BOUNDS_MIN[1])/map_boundai.CELLSIZE;
    coords[2]=(temp[2]-map_boundai.MAP_BOUNDS_MIN[2])/map_boundai.CELLSIZE;
    temp_cur_rad=temp[3];
    temp[3]=0;
    for(INT x=coords[0]-1;x<=coords[0]+1;x++){
        for(INT y=coords[1]-1;y<=coords[1]+1;y++){
            for(INT z=coords[2]-1;z<=coords[2]+1;z++){
                if(x<map_boundai.Nx&&y<map_boundai.Ny&&z<map_boundai.Nz&&x>=0&&y>=0&&z>=0){
                    TEMP_ID=x+y*map_boundai.Nx+z*map_boundai.Nx*map_boundai.Ny;
                    particle_ammount=SUFORMUOTAS_GRIDAS[TEMP_ID].size();
                    offset_val=OFFSET[TEMP_ID];
                    for(INT l=0;l<particle_ammount;l++){
                        tempPID=F[offset_val+l];
                        if(tempPID!=search_particle_index){
                            pid_coords=F[tempPID];
                            temp_pid_rad=pid_coords[3];
                            pid_coords[3]=0;
                            //Distance between u⃗  and v⃗  is d(u⃗ ,v⃗ )=∥u⃗ −v⃗ ∥=sqrt((u1−v1)2+(u2−v2)2...(un−vn)2)−−−−−−−−−−−−−−−−−−−−−−−−−−−−−√.
                            TEMP_LEN=sqrt(pow(coords[0]-pid_coords[0],2)+pow(coords[1]-pid_coords[1],2)+pow(coords[2]-pid_coords[2],2));
                            L=TEMP_LEN-(temp_cur_rad+temp_pid_rad);
                            if(L<=0){
                                rasti_kaimynu_indexai.push_back(tempPID);
                                kiekis++;
                            }
                            if(kiekis=3)
                                break;
                        }
                    }
                }
            }
        }
    }



}
*/
