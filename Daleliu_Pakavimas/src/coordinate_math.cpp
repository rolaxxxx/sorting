#include "coordinate_math.h"
#include "includes.h"
#include "dalele.h"
#include <map_bounds.h>

void coordinate_math::coordinate_math_(Dalele &particle, MAP_BOUNDS boundai)
{
    REAL4 particle_coords, further_coords, third_coords, tetrahedron_top_coords;
    REAL4 triangle_sides, tetrahedron_sides;
    particle_coords[0]=boundai.MAP_BOUNDS_MAX[0]-(boundai.MAP_BOUNDS_MAX[0]/2);
    particle_coords[1]=boundai.MAP_BOUNDS_MAX[1]-(boundai.MAP_BOUNDS_MAX[1]/2);
    particle_coords[2]=0;
    INT spind;
    spind=rand()%particle.Distribution.size(); // spindulio gavimas is pasiskirstymo. Kintamieji kolkas vienodi
    particle_coords[3]=particle.Distribution[spind];
    particle.F.push_back(particle_coords);

    further_coords[0]=(boundai.MAP_BOUNDS_MAX[0]-(boundai.MAP_BOUNDS_MAX[0]/2))+particle_coords[3];
    further_coords[1]=(boundai.MAP_BOUNDS_MAX[1]-(boundai.MAP_BOUNDS_MAX[1]/2));
    further_coords[2]=0;
    spind=rand()%particle.Distribution.size();
    further_coords[3]=particle.Distribution[spind];
    particle.F.push_back(further_coords);

    spind=rand()%particle.Distribution.size();
    third_coords[3]=particle.Distribution[spind];

    triangle_sides[0]=further_coords[3]+third_coords[3]; // a
    triangle_sides[1]=particle_coords[3]+third_coords[3]; // b
    triangle_sides[2]=particle_coords[3]+further_coords[3];// c

    third_coords[0]=(pow(triangle_sides[1],2)+pow(triangle_sides[2],2)-pow(triangle_sides[0],2))/2*triangle_sides[2]; // e
    third_coords[1]=sqrt(pow(triangle_sides[1],2)-third_coords[0]); // f
    third_coords[2]=0;
    particle.F.push_back(third_coords);
    spind=rand()%particle.Distribution.size();
    tetrahedron_top_coords[3]=particle.Distribution[spind];
    tetrahedron_sides[0]=particle_coords[3]+tetrahedron_top_coords[3]; // m
    tetrahedron_sides[1]=further_coords[3]+tetrahedron_top_coords[3]; // n
    tetrahedron_sides[2]=third_coords[3]+tetrahedron_top_coords[3]; // p

    tetrahedron_top_coords[0]=(pow(tetrahedron_sides[0],2)+pow(triangle_sides[2],2)-pow(tetrahedron_sides[1],2))/2*triangle_sides[2];

    tetrahedron_top_coords[1]=(pow(third_coords[1],2)*triangle_sides[2]+pow(tetrahedron_sides[0],2)*triangle_sides[2]-
            pow(tetrahedron_sides[0],2)*third_coords[0]+pow(tetrahedron_sides[1],2)*third_coords[0]-
            pow(tetrahedron_sides[2],2)*triangle_sides[2]-pow(triangle_sides[2],2)*third_coords[0]+
            pow(third_coords[0],2)*triangle_sides[2])/2*third_coords[1]*triangle_sides[2];

    tetrahedron_top_coords[2]=sqrt(pow(tetrahedron_sides[0],2)-pow(tetrahedron_top_coords,2)-pow(tetrahedron_top_coords[1],2));



}
