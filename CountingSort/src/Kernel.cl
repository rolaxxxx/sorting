__kernel
void GridAddition(constant double4* POSITIONS,  double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  __global int* GRID_COUNT,  double CELLSIZE, int Nx,  int Ny,   int Nz)
{
        uint idx=get_global_id(0);
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        uint BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        //printf("bendras ID %d \n" , BENDRAS_ID);
        atomic_add(&GRID_COUNT[BENDRAS_ID],1);
}

__kernel
void GridCountSort(__global uint* OFFSET, __global double* IDS,  __constant double4* POSITIONS,    int Nx,   int Ny,  int Nz,  __global int* GRID_COUNT,  double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  double CELLSIZE)
{

        uint idx=get_global_id(0);
        double4 temp, bounds_temp;
        temp=POSITIONS[idx];
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
         uint BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        uint sena_reiksme=atom_add(&GRID_COUNT[BENDRAS_ID],1);
        IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;

}

__kernel
void NeighbourSearch(__constant double4 *POSITIONS,  __constant int* GRID_COUNT, __constant uint* OFFSET, __global uint* NN_COUNT, __global uint* NN_IDS,   double CELLSIZE,  int Nx,  int Ny,   int Nz,   int NN_MAX, double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX, __global double* IDS)
{
    uint idx=get_global_id(0);
    double4 temp, tempPID;
    double  tempCurrentRadius, tempPIdRadius,L, tempIlgis;
    uint c;
    uint pid, ID, offset;
    uint kiekis=0;
    double4 coords;
    temp=POSITIONS[idx];
    coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
    tempCurrentRadius=temp.w;
    temp.w=0;
    //printf("koordinates idx daleles %f  %f  %f  %f  ",temp.x,temp.y,temp.z,temp.w);
    for(int x=coords.x-1;x<=coords.x+1;x++){
        for(int y=coords.y-1;y<=coords.y+1;y++){
            for(int k=coords.z-1;k<=coords.z+1;k++){
                    if(x<Nx&&y<Ny&&k<Nz&&x>=0&&y>=0&&k>=0)
                        {
                           ID=x+y*Nx+k*Nx*Ny;
                             c=GRID_COUNT[ID];
                               offset=OFFSET[ID];
                              // printf("offsetas  % d  ir c indexas %d ",c, offset);
                                 for(int k=0;k<c;k++){
                                    pid=IDS[offset+k];
                                      tempPID=POSITIONS[pid];
                                     // printf("indexo pid numeris %d" , pid );
                                      //printf("koordinates idx daleles %f  %f  %f  %f  ",tempPID.x,tempPID.y,tempPID.z,tempPID.w);
                                        if(pid!=idx){
                                            tempPIdRadius=tempPID.w;
                                                tempPID.w=0;
                                                  tempIlgis=distance(temp,tempPID);
                                                  printf("%f temp ilgio reiksme", tempIlgis);
                                                    // L=tempIlgis-tempCurrentRadius+tempPIdRadius;
                                                        //printf("ilgis tarp dvieju vektoriu %f  idx daleles radius %f  pid indexo daleles radius %f /n", tempIlgis, tempCurrentRadius, tempPIdRadius);
                                                            //printf("ilgis tarp dvieju vektoriu %d ", L);
                                                                if(L<0){
                                                                    NN_IDS[idx*NN_MAX+kiekis]=pid;
                                                                       kiekis++;
                                                                       // printf("indexo pid numeris %d" , pid );
                                                                    //printf("indeksas %d max kaimynu skaicius %d, uzpildymo kiekis kiekvienoje celeje %d" , idx, NN_MAX, kiekis);

                                                                     }
            }
            NN_COUNT[idx]=kiekis;
           // printf("idx daleles indexas %d ir kiekis kiek kaimynu ji turi %d \n",idx, kiekis);
        }

    }

   }

  }


 }


}
