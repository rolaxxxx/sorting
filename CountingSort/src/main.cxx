#include "main.h"

int main()
{
	ParticleArrays coordinates;
    coordinates.FILL(coordinates.POSITIONS, coordinates.PARTICLE_AMOUNT, coordinates.RMAX,
                     coordinates.CELLSIZE, coordinates.DEVICE_BOUNDS, coordinates.Nx, coordinates.Ny,
                     coordinates.Nz, coordinates.GRID_COUNT);

    coordinates.KernelsEnqeue(coordinates.POSITIONS, coordinates.DEVICE_BOUNDS, coordinates.GRID_COUNT,
                              coordinates.CELLSIZE, coordinates.PARTICLE_AMOUNT);
}
