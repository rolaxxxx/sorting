#include "mapaddandparticlesearch.h"
#include "dalele.h"
void MapAddAndParticleSearch::GRIDAS_MAP_ADD( REAL4 add_particle, MAP_BOUNDS map_boundai){
    REAL4 temp_coords;
    INT TEMP_ID;
    REAL4 MAP_BOUNDS_MAX=map_boundai.getMAP_BOUNDS_MAX();
    REAL4 MAP_BOUNDS_MIN=map_boundai.getMAP_BOUNDS_MIN();
    REAL CELLSIZE=map_boundai.getCELLSIZE();
    INT nx, ny, nz;
    nx=map_boundai.getNx();
    ny=map_boundai.getNy();
    nz=map_boundai.getNz();
    //cout << CELLSIZE << endl;
    //cout << MAP_BOUNDS_MAX << " " << MAP_BOUNDS_MIN << endl;
        temp_coords[0]=floor((add_particle[0]-MAP_BOUNDS_MIN[0])/CELLSIZE);
        temp_coords[1]=floor((add_particle[1]-MAP_BOUNDS_MIN[1])/CELLSIZE);
        temp_coords[2]=floor((add_particle[2]-MAP_BOUNDS_MIN[2])/CELLSIZE);
        TEMP_ID=temp_coords[0]+temp_coords[1]*nx+temp_coords[2]*nx*ny;
        //cout <<add_particle << " " <<TEMP_ID << endl;
        //cout << SUFORMUOTAS_GRIDAS.size() << endl;
        //cout << SUFORMUOTAS_GRIDAS.size() << endl;
        INT temp=0;
        temp=SUFORMUOTAS_GRIDAS.size();
        SUFORMUOTAS_GRIDAS[TEMP_ID].push_back(temp);
}

vector<INT> MapAddAndParticleSearch::MAP_NEIGHBOR_SEARCH(Dalele particle, INT search_particle_index, MAP_BOUNDS map_boundai){
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
    //cout << nx << " " << ny << " " << nz << endl;

    INT kiekis=0;

    temp=particle.F[search_particle_index];
    //cout << particle.F[search_particle_index] << endl;
    //cout <<MAP_BOUNDS_MIN << " " << CELLSIZE << endl;
    coords[0]=floor((temp[0]-MAP_BOUNDS_MIN[0])/CELLSIZE);
    coords[1]=floor((temp[1]-MAP_BOUNDS_MIN[1])/CELLSIZE);
    coords[2]=floor((temp[2]-MAP_BOUNDS_MIN[2])/CELLSIZE);
    temp_cur_rad=1;// kol vienodi spinduliai bus vienas o po to reikia keisti

   // cout << CE
    //cout << temp << endl;
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
                                            //cout << pid << " " <<particle.F[pid] << endl;
                                       if(pid!=search_particle_index)
                                               {
                                               tempPID=particle.F[pid];
                                               temp_pid_rad=tempPID[3];
                                               tempPID[3]=0;

                                       TEMP_LEN=sqrt(pow(temp[0]-tempPID[0],2)+pow(temp[1]-tempPID[1],2)+pow(temp[2]-tempPID[2],2));
                                       L=TEMP_LEN-(temp_cur_rad+temp_pid_rad);
                                       //cout <<particle.F.size() << " "<<search_particle_index<< "nuo ieskomo kaimyno nutole " <<  L << " " << 2*temp_cur_rad << endl;
                                       if(L<=2*temp_cur_rad){
                                          // cout << rasti_kaimynu_indexai[kiekis] << endl;
                                           rasti_kaimynu_indexai.push_back(pid);
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
bool MapAddAndParticleSearch::NEIGHBOR_SEARCH(Dalele particle, vector<INT> rand_daleles_kaimynai, REAL4 kaimynas, MAP_BOUNDS map_boundai){
    REAL4 temp, tempPID;
    REAL4 coords;
    INT pid;
    REAL L;
    REAL temp_cur_rad, temp_pid_rad;
    REAL TEMP_LEN;
    INT TEMP_ID;
    vector<INT> potencialus_kaimynai;
    vector<INT> rasti_kaimynu_indexai;
    REAL LEN1, LEN2;


    REAL4 MAP_BOUNDS_MAX=map_boundai.getMAP_BOUNDS_MAX();
    REAL4 MAP_BOUNDS_MIN=map_boundai.getMAP_BOUNDS_MIN();
    REAL CELLSIZE=map_boundai.getCELLSIZE();
    INT nx, ny, nz;
    nx=map_boundai.getNx();
    ny=map_boundai.getNy();
    nz=map_boundai.getNz();

    INT kiekis=0;

    temp=kaimynas;
    coords[0]=floor((temp[0]-MAP_BOUNDS_MIN[0])/CELLSIZE);
    coords[1]=floor((temp[1]-MAP_BOUNDS_MIN[1])/CELLSIZE);
    coords[2]=floor((temp[2]-MAP_BOUNDS_MIN[2])/CELLSIZE);
    coords[3]=0;
    LEN1=sqrt(pow(kaimynas[0],2)+pow(kaimynas[1],2)+pow(kaimynas[2],2));
    bool ans=false;
    for(INT i=0;i<rand_daleles_kaimynai.size();i++)
    {
        tempPID=particle.F[rand_daleles_kaimynai[i]];
        tempPID[3]=0;
        LEN2=sqrt(pow(tempPID[0],2)+pow(tempPID[1],2)+pow(tempPID[2],2));
        if(fabs(LEN1-LEN2)<0.01)
        {ans=true;
        }
    }

    return ans;

}
map<INT, vector<INT> > MapAddAndParticleSearch::getSUFORMUOTAS_GRIDAS() const
{
    return SUFORMUOTAS_GRIDAS;
}

void MapAddAndParticleSearch::setSUFORMUOTAS_GRIDAS(const map<INT, vector<INT> > &value)
{
    SUFORMUOTAS_GRIDAS = value;
}





