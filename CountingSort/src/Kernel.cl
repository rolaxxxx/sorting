#pragma OPENCL EXTENSION cl_khr_fp64 : enable
__kernel
void GridAddition(constant double4* POSITIONS,  double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  __global int* GRID_COUNT,  double CELLSIZE, int Nx,  int Ny,   int Nz)
{
        uint idx=get_global_id(0);
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        //printf("coords.y  %f Nx %d  sudauginta bendra reiksme %f \n" ,coords.y, Nx, coords.y*Nx);
        atomic_add(&GRID_COUNT[BENDRAS_ID],1);
}

__kernel
void GridCountSort(__global int* OFFSET, __global int* IDS,  __constant double4* POSITIONS,    int Nx,   int Ny,  int Nz,  __global int* GRID_COUNT,  double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  double CELLSIZE)
{

        int idx=get_global_id(0);
        double4 temp, bounds_temp;
        temp=POSITIONS[idx];
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        //printf("bendras id suskaiciavus nenucastinus i inta %d  \n" ,coords.x+coords.y*Nx+coords.z*Nx*Ny);
        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        //printf("bendras id suskaiciavus nucastinus i inta %d \n  " ,BENDRAS_ID);
        int sena_reiksme=atom_add(&GRID_COUNT[BENDRAS_ID],1);
        IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
        //printf("idx daleles reiksme %d " , idx);
        //printf("IDS reiksme %d  IDS indeksas %d  idx reiksme %d \n" , IDS[OFFSET[BENDRAS_ID]+sena_reiksme], OFFSET[BENDRAS_ID]+sena_reiksme, idx);
}

__kernel
void NeighbourSearch(__constant double4 *POSITIONS,  __constant int* GRID_COUNT, __constant int* OFFSET, __global int* NN_COUNT, __global int* NN_IDS,   double CELLSIZE,  int Nx,  int Ny,   int Nz,   int NN_MAX, double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX, __global int* IDS)
{
    int idx=get_global_id(0);
    double4 temp, tempPID;
    double  tempCurrentRadius, tempPIdRadius,L, tempIlgis;
    int c;
    int pid, ID, offset;
    int kiekis=0;
    double4 coords;
    temp=POSITIONS[idx];
    coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
    tempCurrentRadius=temp.w;
    temp.w=0;
    //printf("koordinates idx daleles %f  %f  %f  %f \n ",temp.x,temp.y,temp.z,temp.w);

    for(int x=coords.x-1;x<=coords.x+1;x++){
        for(int y=coords.y-1;y<=coords.y+1;y++){
            for(int k=coords.z-1;k<=coords.z+1;k++){

                    if(x<Nx&&y<Ny&&k<Nz&&x>=0&&y>=0&&k>=0)
                        {  kiekis=0;
                           ID=x+y*Nx+k*Nx*Ny;
                           //printf("aplinkines koordinates %d  %d  %d \n", x, y ,k );
                           //printf("suskaiciuota ID reiksme %d \n", ID );
                             c=GRID_COUNT[ID];
                               offset=OFFSET[ID];
                                 //printf("offset reiksme %d  c reiksme for ciklui %d \n ", c , offset);
                                   for(int l=0;l<c;l++){

                                     pid=IDS[offset+l];

                                     //printf("offset+l indeksas %d   IDS reiksme offset+l indekse %d  \n",offset+l, IDS[offset+l]);
                                     //printf("indexo pid numeris %d \n" , pid );

                                        if(pid!=idx){
                                         tempPID=POSITIONS[pid];
                                         //printf("indexo pid numeris %d \n" , pid );
                                         //printf("positions reiksmes %lf %lf %lf %lf",
                                         //printf("koordinates idx daleles %lf  %lf  %lf  %lf  ",tempPID.x,tempPID.y,tempPID.z,tempPID.w);
                                         tempPIdRadius=tempPID.w;
                                         //printf("PID indexo daleles spindulys %f \n", tempPIdRadius);
                                         tempPID.w=0;
                                         tempIlgis=distance(temp,tempPID);

                                       // printf(" temp ilgio reiksme", tempIlgis);
                                        L=tempIlgis-(tempCurrentRadius+tempPIdRadius);

                                                        //printf("ilgis tarp dvieju vektoriu %f  idx daleles radius %f  pid indexo daleles radius %f \n", tempIlgis, tempCurrentRadius, tempPIdRadius);
                                                            //printf("ilgis tarp dvieju vektoriu %f \n", L);
                                                              if(L<0){
                                                                    NN_IDS[idx*NN_MAX+kiekis]=pid;
                                                                       kiekis++;
                                                                        //printf("indexo pid numeris %d" , pid );
                                                                    //printf("indeksas %d max kaimynu skaicius %d, uzpildymo kiekis kiekvienoje celeje %d" , idx, NN_MAX, kiekis);
                                                                }
           NN_COUNT[idx]=kiekis;

}
   }

  }


 }


}
}
}

