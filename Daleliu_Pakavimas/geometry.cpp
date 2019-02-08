#include "geometry.h"
#include "includes.h"
void Geometry::skirstinioFormavimas(Dalele &particle)
{
    srand( time(NULL) );
        for(int i=0;i<particle.daleliuKiekis;i++){
            //particle.Distribution.push_back(rand()%particle.max+particle.min);
            particle.Distribution.push_back(1);
            //  cout << particle.Distribution[i] << endl;
        }

}
