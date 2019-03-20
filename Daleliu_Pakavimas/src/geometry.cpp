#include "geometry.h"
#include "includes.h"
void Geometry::skirstinioFormavimas()
{
    srand (time(NULL));
       REAL lower_bound = 1;
       REAL upper_bound = 1;
       std::uniform_real_distribution<REAL> unif(lower_bound,upper_bound);
       std::default_random_engine re;
       REAL a_random_double;
       for(INT i=0;i<100;i++){
            a_random_double = unif(re);
            distribution.push_back(a_random_double);
        }

}

REAL_ARRAY Geometry::getDistribution() const
{
    return distribution;
}

void Geometry::setDistribution(const REAL_ARRAY &value)
{
    distribution = value;
}
