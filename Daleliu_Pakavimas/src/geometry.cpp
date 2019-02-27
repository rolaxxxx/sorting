#include "geometry.h"
#include "includes.h"
void Geometry::skirstinioFormavimas(Dalele &particle)
{
    srand (time(NULL));
       // for(int i=0;i<particle.daleliuKiekis;i++){
            //particle.Distribution.push_back(rand()%particle.max+particle.min);
       REAL lower_bound = 0.95;
       REAL upper_bound = 1.2;
       std::uniform_real_distribution<REAL> unif(lower_bound,upper_bound);
       std::default_random_engine re;
       REAL a_random_double;

       for(INT i=0;i<100;i++){
           a_random_double = unif(re);
       particle.Distribution.push_back(a_random_double);
        //cout << particle.Distribution[i] << endl;
        }

}
