#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable
__kernel
void GridAddition(__global float4* POSITIONS, __global float* DEVICE_BOUNDS, __global float* GRID_COUNT, float CELLSIZE, uint PARTICLE_AMOUNT )
{
        uint idx=get_global_id(0);
        __local float4 temp;
        temp=POSITIONS[idx];

        __local float3 coords;
        __local float cellId;

            coords.x= temp.x;
            coords.y=temp.y;
            coords.z=temp.z;

        ix=(coords.x-bounds[0]) / CELLSIZE;
        jy=(coords.y-bounds[1]) / CELLSIZE;
        kz=(coords.z-bounds[2]) / CELLSIZE;
        BENDRAS_ID=ix+jy*Nx+kz*Nx*Ny;
        atomic_add(GRID_COUNT[BENDRAS_ID],1);
}
