__kernel
void GridAddition(__global float4* POSITIONS, __global float* DEVICE_BOUNDS, volatile __global int * GRID_COUNT, float CELLSIZE, uint PARTICLE_AMOUNT, float Nx, float Ny, float Nz)
{
        uint idx=get_global_id(0);
        float4 temp;
        temp=POSITIONS[idx];

        __local float3 coords;
         float cellId;
         float ix, jy, kz;

            coords.x=temp.x;
            coords.y=temp.y;
            coords.z=temp.z;

        ix=(coords.x-DEVICE_BOUNDS[0]) / CELLSIZE;
        jy=(coords.y-DEVICE_BOUNDS[1]) / CELLSIZE;
        kz=(coords.z-DEVICE_BOUNDS[2]) / CELLSIZE;
        uint BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        atomic_add(GRID_COUNT[BENDRAS_ID],1);
}

__kernel
void GridCountSort(__global uint* OFFSET, __global float* IDS, __global float4* POSITIONS, __global float Nx, __global float Ny, __global float Nz, __global int* GRID_COUNT, __global float* DEVICE_BOUNDS, float CELLSIZE)
{
        uint idx=get_global_id(0);
        __local float4 temp;
        temp=POSITIONS[idx];

        __local float3 coords;
        coords.x=temp.x;
        coords.y=temp.y;
        coords.z=temp.z;
        float ix, jy, kz;

        ix=(coords.x-DEVICE_BOUNDS[0]) / CELLSIZE;
        jy=(coords.y-DEVICE_BOUNDS[1]) / CELLSIZE;
        kz=(coords.z-DEVICE_BOUNDS[2]) / CELLSIZE;
        uint BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        uint sena_reiksme=atom_add(GRID_COUNT[BENDRAS_ID],1);
        IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
}



__kernel
void NeighbourSearch(__global float4* POSITIONS, __global int* GRID_COUNT, __global uint* OFFSET, __global uint* NN_COUNT, __global uint* NN_IDS, __global float CELLSIZE, __global float Nx, __global float Ny, __global float Nz, __global float NN_MAX, __global float* DEVICE_BOUNDS, __global float* IDS)
{
    uint idx=get_global_id(0);
    float4 temp, tempPID, L;
    temp=POSITIONS[idx];

    float ix, jy, kz, c, tempCurrentRadius, tempPIdRadius;

    uint pid, ID, offset;
    uint kiekis=0;
    ix=(temp.x-DEVICE_BOUNDS[0]) / CELLSIZE;
    jy=(temp.y-DEVICE_BOUNDS[1]) / CELLSIZE;
    kz=(temp.z-DEVICE_BOUNDS[2]) / CELLSIZE;
    tempCurrentRadius=temp.w;
    temp.w=0;
    for(uint x=ix-1;x<=ix+1;x++){
        for(uint y=jy-1;y<=jy+1;y++){
            for(uint k=kz-1;k<=kz+1;k++){
                    if(x<Nx&&y<Ny&&k<Nz)
                        {
                           ID=ix+jy*Nx+kz*Nx*Ny;
                           c=GRID_COUNT[ID];
                           offset=OFFSET[ID];
                           for(int k=0;k<c;k++){
                                    pid=IDS[offset+k];
                                    tempPID=POSITIONS[pid];
                                        if(pid!=idx){
                                            tempPIdRadius=POSITIONS[pid].w;
                                                POSITIONS[pid].w=0;
                                                    L=fmod(temp,tempPID)-tempCurrentRadius+tempPIdRadius;
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
