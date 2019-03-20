#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "includes.h"
#include "dalele.h"
typedef boost::compute::double_ REAL;
class Geometry
{
public:
    void skirstinioFormavimas();
    REAL_ARRAY getDistribution() const;
    void setDistribution(const REAL_ARRAY &value);

private:
    REAL_ARRAY distribution;
};

#endif // GEOMETRY_H
