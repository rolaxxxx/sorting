__kernel
void GridAddition(__global float4* POSITIONS, __global float* DEVICE_BOUNDS,  __global int * GRID_COUNT, float CELLSIZE, uint PARTICLE_AMOUNT, float Nx, float Ny, float Nz)
{
        uint idx=get_global_id(0);

         __local float ix, jy, kz;

        ix=(POSITIONS[idx].x-DEVICE_BOUNDS[0]) / CELLSIZE;
        jy=(POSITIONS[idx].y-DEVICE_BOUNDS[2]) / CELLSIZE;
        kz=(POSITIONS[idx].z-DEVICE_BOUNDS[4]) / CELLSIZE;
       // printf(" %f %f %f \n",  ix, jy, kz);
        //printf("%f %f %f  device bounds min x y z  %f %f %f  CELLSIZE IS MAINO %f\n",ix, jy, kz, DEVICE_BOUNDS[0], DEVICE_BOUNDS[2], DEVICE_BOUNDS[4], CELLSIZE);
        uint BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        //printf("%d \n", BENDRAS_ID);
        //printf("%d %f %f %f \n", BENDRAS_ID, temp.x, temp.y, temp.z);
        //printf("%d", GRID_COUNT[BENDRAS_ID]);
        atomic_add(&GRID_COUNT[BENDRAS_ID],1);

}

__kernel
void GridCountSort(__global uint* OFFSET, __global float* IDS, __global float4* POSITIONS,  float Nx,  float Ny,  float Nz, __global int* GRID_COUNT, __global float* DEVICE_BOUNDS, float CELLSIZE)
{
       uint idx=get_global_id(0);
        __local float4 temp;
        temp=POSITIONS[idx];


        __local float ix, jy, kz;

        ix=(POSITIONS[idx].x-DEVICE_BOUNDS[0]) / CELLSIZE;
        jy=(POSITIONS[idx].y-DEVICE_BOUNDS[2]) / CELLSIZE;
        kz=(POSITIONS[idx].z-DEVICE_BOUNDS[4]) / CELLSIZE;
        uint BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        uint sena_reiksme=atom_add(&GRID_COUNT[BENDRAS_ID],1);
        IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
}

__kernel
void NeighbourSearch(__global float4* POSITIONS, __global int* GRID_COUNT, __global uint* OFFSET, __global uint* NN_COUNT, __global uint* NN_IDS,  float CELLSIZE, float Nx, float Ny,  float Nz,  uint NN_MAX, __global float* DEVICE_BOUNDS, __global float* IDS)
{
    uint idx=get_global_id(0);
    float4 temp, tempPID;



    float ix, jy, kz, c, tempCurrentRadius, tempPIdRadius,L, tempIlgis;

    uint pid, ID, offset;
    uint kiekis=0;
    ix=(POSITIONS[idx].x-DEVICE_BOUNDS[0]) / CELLSIZE;
    jy=(POSITIONS[idx].y-DEVICE_BOUNDS[2]) / CELLSIZE;
    kz=(POSITIONS[idx].z-DEVICE_BOUNDS[4]) / CELLSIZE;
    tempCurrentRadius=temp.w;
    temp.w=0;
    for(uint x=ix-1;x<=ix+1;x++){
        for(uint y=jy-1;y<=jy+1;y++){
            for(uint k=kz-1;k<=kz+1;k++){
                    if(x<Nx&&y<Ny&&k<Nz&&x>0&&y>0&&k>0)
                        {
                          ID=x+y*Nx+k*Nx*Ny;
                           c=GRID_COUNT[ID];
                           offset=OFFSET[ID];
                           for(int k=0;k<c;k++){
                                    pid=IDS[offset+k];
                                    tempPID=POSITIONS[pid];
                                        if(pid!=idx){
                                            tempPIdRadius=POSITIONS[pid].w;
                                                POSITIONS[pid].w=0;
                                                  tempIlgis=distance(temp,tempPID);
                                                     L=tempIlgis-tempCurrentRadius+tempPIdRadius;
                                                        if(L<0){
                                                            NN_IDS[idx*NN_MAX+kiekis]=pid;
                                                                kiekis++;
                                                                     }
            }
            NN_COUNT[idx]=kiekis;
        }

    }

   }

  }


 }


}
