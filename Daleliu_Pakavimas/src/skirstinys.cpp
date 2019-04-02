#include "skirstinys.h"
#include "includes.h"
REAL Skirstinys::NextSpindulys()
{
    srand (time(NULL));
       REAL lower_bound = 1;
       REAL upper_bound = 1;
       std::uniform_real_distribution<REAL> unif(lower_bound,upper_bound);
       std::default_random_engine re;
       REAL a_random_double = unif(re);
       return a_random_double;
}
