#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <includes.h>
typedef boost::compute::double_ REAL;
class Geometry
{
public:
    Geometry();
    REAL newSpindulys;
    REAL min,max;
    void skirstinioFormavimas();
};
void Geometry::skirstinioFormavimas()
{
    Geometry geometry;
    cout << "Iveskite skirstinio ribas  min   max   " << endl;
    cin >> geometry.min >> geometry.max;

}
#endif // GEOMETRY_H
