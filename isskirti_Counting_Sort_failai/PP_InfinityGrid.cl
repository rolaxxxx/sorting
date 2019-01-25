#pragma OPENCL EXTENSION cl_khr_fp64 : enable
__kernel
void GridAddition(__global double4* POSITIONS, double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  __global int* GRID_COUNT,  double CELLSIZE, int Nx, int Ny, int Nz)
{
        uint idx=get_global_id(0);
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        atomic_add(&GRID_COUNT[BENDRAS_ID],1);
}
__kernel
void GridCountSort(__global int* OFFSET, __global int* IDS,  __global double4* POSITIONS,    int Nx,   int Ny,  int Nz,  __global int* GRID_COUNT,  double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  double CELLSIZE)
{
        int idx=get_global_id(0);
        double4 temp, bounds_temp;
        temp=POSITIONS[idx];
        double4 coords;
        int sena_reiksme;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        sena_reiksme=atom_add(&GRID_COUNT[BENDRAS_ID],1);
        IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
}
__kernel
void NeighbourSearch(__global double4 *POSITIONS,  __global int* GRID_COUNT, __global int* OFFSET, __global int* NN_COUNT, __global int* NN_IDS,   double CELLSIZE,  int Nx,  int Ny,   int Nz,   int NN_MAX, double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX, __global int* IDS,  int KIEKIS)
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
    for(int x=coords.x-1;x<=coords.x+1;x++){
     for(int y=coords.y-1;y<=coords.y+1;y++){
      for(int k=coords.z-1;k<=coords.z+1;k++){
         if(x<Nx&&y<Ny&&k<Nz&&x>=0&&y>=0&&k>=0)
           {  
             ID=x+y*Nx+k*Nx*Ny;
              c=GRID_COUNT[ID];
               offset=OFFSET[ID];
                 for(int l=0;l<c;l++){
                    pid=IDS[offset+l];
                     if(pid!=idx){
                       tempPID=POSITIONS[pid];
                        tempPIdRadius=tempPID.w;
                         tempPID.w=0;
                          tempIlgis=distance(temp,tempPID);
                           L=length(temp-tempPID)-(tempCurrentRadius+tempPIdRadius);
			    	if(L<=0){
                              	     NN_IDS[idx*NN_MAX+kiekis]=pid;
                                     kiekis++;
                            }
		                  NN_COUNT[idx]=kiekis;
                                }
                                     }

             }
                                             }
                                            }
                                           }



}
