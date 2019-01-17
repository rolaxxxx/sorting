#include "main.h"

int main()
{


        ParticleArrays coordinates;
        coordinates.FILL(coordinates.POSITIONS, coordinates.PARTICLE_AMOUNT,
                         coordinates.RMAX, coordinates.CELLSIZE, coordinates.DEVICE_BOUNDS_MIN, coordinates.DEVICE_BOUNDS_MAX,
                         coordinates.Nx, coordinates. Ny, coordinates.Nz, coordinates.GRID_COUNT,
                         coordinates.OFFSET, coordinates.IDS, coordinates.NN_COUNT, coordinates.NN_IDS, coordinates.NN_MAX);

        coordinates.KernelsEnqeue(coordinates.IDS, coordinates.Nx, coordinates.Ny, coordinates.Nz, coordinates.GRID_COUNT,
                                    coordinates.OFFSET, coordinates.POSITIONS, coordinates.DEVICE_BOUNDS_MIN, coordinates.DEVICE_BOUNDS_MAX,
                                   coordinates.CELLSIZE, coordinates.NN_COUNT, coordinates.NN_IDS, coordinates.NN_MAX, coordinates.PARTICLE_AMOUNT, coordinates.KIEKIS);

}

