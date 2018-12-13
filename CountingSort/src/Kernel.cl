#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
__kernel
void GridAddition(__global float4* POSITIONS, __global float* DEVICE_BOUNDS, __global float* GRID_COUNT, float CELLSIZE, uint PARTICLE_AMOUNT, float Nx, float Ny, float Nz)
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

        ix=(coords.x-bounds[0]) / CELLSIZE;
        jy=(coords.y-bounds[1]) / CELLSIZE;
        kz=(coords.z-bounds[2]) / CELLSIZE;
        uint BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        atomic_add(GRID_COUNT[BENDRAS_ID],1);
}

__kernel
void GridCountSort(__global float* OFFSET, __global float* IDS, __global float4* POSITIONS, __global float Nx, __global float Ny, __global float Nz, __global float* GRID_COUNT, __global float* DEVICE_BOUNDS, float CELLSIZE)
{
        uint idx=get_global_id(0);
        __local float4 temp;
        temp=POSITIONS[idx];

        __local float3 coords;
        coords.x=temp.x;
        coords.y=temp.y;
        coords.z=temp.z;
        float ix, jy, kz;

        ix=(coords.x-bounds[0]) / CELLSIZE;
        jy=(coords.y-bounds[1]) / CELLSIZE;
        kz=(coords.z-bounds[2]) / CELLSIZE;
        uint BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        uint sena_reiksme=atom_add(GRID_COUNT[BENDRAS_ID],1);
        IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
}
__kernel
void NeighbourSearch(__global float4* POSITIONS, __global float* GRID_COUNT, __global float* OFFSET, __global uint* NN_COUNT, __global uint* NN_IDS, __global float Nx, __global float Ny, __global float Nz )
{
    float4 temp, tempPID;
    temp=POSITIONS[idx];

    float ix, jy, kz, c, pid, OFFSET, tempCurrentRadius, tempPIdRadius, L;

    ix=(temp.x-bounds[0]) / CELLSIZE;
    jy=(temp.y-bounds[1]) / CELLSIZE;
    kz=(temp.z-bounds[2]) / CELLSIZE;
    tempCurrentRadius=temp.w;
    temp.w=0;
    for(uint x=ix-1;x<=ix+1;x++){
        for(uint y=jy-1;y<=jy+1;y++){
            for(uint k=kz-1;k<=kz+1;k++){
                    if(x<Nx&&y<Ny&&z<Nz)
                        {
                           ID=ix+jy*Nx+kz*Nx*Ny;
                           c=GRID_COUNT[ID];
                           offset=OFFSET[ID];
                           for(int k=0;k<c;k++){
                                    pid=IDS[OFFSET+k];
                                    tempPID=POSITIONS[pid];
                                        if(pid!=idx){
                                            tempPIdRadius=POSITIONS[pid].w;
                                                POSITIONS[pid].w=0;
                                                    L=fmod(temp-tempPID)-tempCurrentRadius+tempPIdRadius;
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
