#include "grid_count.h"
#include "dalele.h"
void GRID_COUNT::GRIDAS_MAP_ADD( REAL4 add_particle){
    REAL4 temp_coords;
    INT TEMP_ID;
    REAL4 MAP_BOUNDS_MAX=map_boundai.getMAP_BOUNDS_MAX();
    REAL4 MAP_BOUNDS_MIN=map_boundai.getMAP_BOUNDS_MIN();
    REAL CELLSIZE=map_boundai.getCELLSIZE();
    INT nx, ny, nz;
    nx=map_boundai.getNx();
    ny=map_boundai.getNy();
    nz=map_boundai.getNz();
        temp_coords[0]=floor((add_particle[0]-MAP_BOUNDS_MIN[0])/CELLSIZE);
        temp_coords[1]=floor((add_particle[1]-MAP_BOUNDS_MIN[1])/CELLSIZE);
        temp_coords[2]=floor((add_particle[2]-MAP_BOUNDS_MIN[2])/CELLSIZE);
        TEMP_ID=temp_coords[0]+temp_coords[1]*nx+temp_coords[2]*nx*ny;
        SUFORMUOTAS_GRIDAS[TEMP_ID].push_back(SUFORMUOTAS_GRIDAS.size()+1);
}
vector<INT> GRID_COUNT::MAP_NEIGHBOR_SEARCH( REAL4_ARRAY F, INT search_particle_index){
    REAL4 temp, tempPID;
    REAL4 coords;
    INT pid;
    REAL L;
    REAL temp_cur_rad, temp_pid_rad;
    REAL TEMP_LEN;
    INT TEMP_ID;
    vector<INT> potencialus_kaimynai;
    vector<INT> rasti_kaimynu_indexai;

    REAL4 MAP_BOUNDS_MAX=map_boundai.getMAP_BOUNDS_MAX();
    REAL4 MAP_BOUNDS_MIN=map_boundai.getMAP_BOUNDS_MIN();
    REAL CELLSIZE=map_boundai.getCELLSIZE();
    INT nx, ny, nz;
    nx=map_boundai.getNx();
    ny=map_boundai.getNy();
    nz=map_boundai.getNz();

    INT kiekis=0;

    temp=F[search_particle_index];
    coords[0]=floor((temp[0]-MAP_BOUNDS_MIN[0])/CELLSIZE);
    coords[1]=floor((temp[1]-MAP_BOUNDS_MIN[1])/CELLSIZE);
    coords[2]=floor((temp[2]-MAP_BOUNDS_MIN[2])/CELLSIZE);
   // cout << CE
    rasti_kaimynu_indexai.push_back(search_particle_index);
    temp_cur_rad=temp[3];
    temp[3]=0;

    for(INT x=coords[0]-1;x<=coords[0]+1;x++){ // pakeliau atstuma nes neradau kaimynu
        for(INT y=coords[1]-1;y<=coords[1]+1;y++){
            for(INT z=coords[2]-1;z<=coords[2]+1;z++){
               // if(x<map_boundai.Nx&&y<map_boundai.Ny&&z<map_boundai.Nz&&x>=0&&y>=0&&z>=0){
                     TEMP_ID=x+y*nx+z*nx*ny;
                        //cout << TEMP_ID << endl;
                                 potencialus_kaimynai=SUFORMUOTAS_GRIDAS[TEMP_ID];
                                        //cout << potencialus_kaimynai.size() << endl;
                                 for(auto it=potencialus_kaimynai.begin();it!=potencialus_kaimynai.end();it++){
                                         pid=*it;
                                        // cout << pid << " " << search_particle_index << endl;
                                    if(pid!=search_particle_index)
                                    {
                                    tempPID=F[pid];
                                    temp_pid_rad=tempPID[3];
                                    tempPID[3]=0;

                                    TEMP_LEN=sqrt(pow(temp[0]-tempPID[0],2)+pow(temp[1]-tempPID[1],2)+pow(temp[2]-tempPID[2],2));
                                    L=TEMP_LEN-(temp_cur_rad+temp_pid_rad);
                                    //cout << L << " " << 2*temp_cur_rad << endl;
                                    if(L<=2*temp_cur_rad){
                                       // cout << rasti_kaimynu_indexai[kiekis] << endl;
                                        rasti_kaimynu_indexai.push_back(pid);
                                        //cout << L << " " << pid << endl;
                                        //cout << rasti_kaimynu_indexai.size() << endl;
                                        kiekis++;
                                        //cout << pid << endl;

                                    }

                                    }
                                     }
                      }
                }
            }
    return rasti_kaimynu_indexai;
  }

