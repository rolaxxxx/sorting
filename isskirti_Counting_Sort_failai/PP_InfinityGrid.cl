#define MAX_VALUE 64
__kernel void GridAddition(__global REAL4* POSITIONS, REAL4 DEVICE_BOUNDS_MIN,
  REAL4 DEVICE_BOUNDS_MAX,__global INT* GRID_COUNT, INT Nx, INT Ny, INT Nz)
{
        uint idx=get_global_id(0);
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELL_SIZE);
        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
	atomic_add(&GRID_COUNT[BENDRAS_ID],1);
}
__kernel void GridCountSort(__global INT* OFFSET, __global INT* IDS,  __global REAL4* POSITIONS, INT Nx,   INT Ny,  INT Nz,
  __global INT* GRID_COUNT,  REAL4 DEVICE_BOUNDS_MIN,  REAL4 DEVICE_BOUNDS_MAX)
{
        int idx=get_global_id(0);
        double4 temp, bounds_temp;
        temp=POSITIONS[idx];
        double4 coords;
	int sena_reiksme;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELL_SIZE);	
        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        sena_reiksme=atom_add(&GRID_COUNT[BENDRAS_ID],1);
	IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
}

__kernel void NeighbourSearch(__global REAL4 *POSITIONS,  __global INT* GRID_COUNT, __global INT* OFFSET, __global INT* NN_COUNT, 
__global INT* NN_IDS,  INT Nx,  INT Ny, INT Nz,  REAL4 DEVICE_BOUNDS_MIN,  REAL4 DEVICE_BOUNDS_MAX, __global INT* IDS)
{
    int idx=get_global_id(0);
    double4 temp, tempPID;
    double  tempCurrentRadius, tempPIdRadius,L, tempIlgis;
    int c;
    int pid, ID, offset;
    int kiekis=0;
    double4 coords;
    temp=POSITIONS[idx];
    coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELL_SIZE);    
    tempCurrentRadius  = RADIUS[GetFirstFromUINT((unsigned int)temp.w)];
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
                         tempPIdRadius= RADIUS[GetFirstFromUINT((unsigned int)tempPID.w)];
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

