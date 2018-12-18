#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
#include <boost/compute/types.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/sha1.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
#include <fstream>
#include "Resource.h"
#include <boost/compute/types.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/sha1.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/utility/program_cache.hpp>
#include <boost/lockfree/queue.hpp>
#include <experimental/filesystem>
#include <iostream>
#include <boost/compute/utility/wait_list.hpp>
#include <vector>
#include <math.h>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/stable_sort_by_key.hpp>
#include <cstddef>
#include <algorithm>
#include <boost/assert.hpp>
#include <ctime>
#include <ratio>
#include <stdlib.h>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/is_sorted.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/compute/core.hpp>
#include <boost/assert.hpp>
#include <algorithm>
#include <boost/compute/algorithm/stable_sort.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/math.hpp>
#include <chrono>"
#include <CL/cl.h>
using boost::compute::int_;
#include <boost/compute/algorithm/sort_by_key.hpp>
namespace compute = boost::compute;
using namespace std;
#include "vtkDataSetReader.h"
#include "vtkPointData.h"
#include <iterator>
#include "vtkPolyData.h"
#include <vtkPolyData.h>
#include "boost/multi_array.hpp"
#include "vtkDataSet.h"
#include <vtkDataSet.h>
#include "vtkDataArray.h"
#include "vtkDataSetWriter.h"
#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkCellData.h"
#include "vtkIOInfovisModule.h"
#include "vtkTableAlgorithm.h"
#include <boost/compute/utility/source.hpp>
#include <boost/compute/utility/program_cache.hpp>
#include <boost/lockfree/queue.hpp>
#include <experimental/filesystem>
#include "Resource.h"
#include <iostream>
#include <boost/compute/utility/wait_list.hpp>
#include <vector>
#include <math.h>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/container/vector.hpp>

#include <boost/compute/container/vector.hpp>
#include <boost/compute/types.hpp>

#define PI_VALUE 3.141592653589793238

#ifdef DOUBLE_NUMBER_PRECISION
typedef boost::compute::double_ REAL;
typedef boost::compute::double4_ REAL4;
#else
typedef boost::compute::float_ REAL;
typedef boost::compute::float4_ REAL4;
#endif
typedef boost::compute::uint_ UINT;
typedef boost::compute::int_ INT;
typedef boost::compute::int2_ INT2;
typedef boost::compute::uint4_ UINT4;
typedef boost::compute::ulong_ ULONG;
typedef boost::compute::uchar_ UCHAR;

template <typename T> using CONTAINER_TYPE = boost::compute::vector<T>;

typedef CONTAINER_TYPE<REAL> REAL_ARRAY;
typedef CONTAINER_TYPE<REAL4> REAL4_ARRAY;
typedef CONTAINER_TYPE<UINT> UINT_ARRAY;
typedef CONTAINER_TYPE<INT> INT_ARRAY;
typedef CONTAINER_TYPE<INT2> INT2_ARRAY;
typedef CONTAINER_TYPE<UINT4> UINT4_ARRAY;
typedef CONTAINER_TYPE<ULONG> ULONG_ARRAY;
typedef CONTAINER_TYPE<UCHAR> UCHAR_ARRAY;

#define MAKE_REAL4(x, y, z, w) REAL4(x, y, z, w)
#define MAKE_REAL4_ZERO() REAL4(0, 0, 0, 0)
#define MAKE_UINT4(x, y, z, w) UINT4(x, y, z, w)


class Inicializacija{
public:

};

class ParticleArrays {
public:
  REAL4_ARRAY POSITIONS;
  INT_ARRAY NN_COUNT;
  INT_ARRAY NN_IDS;
  INT PARTICLE_AMOUNT;
  INT_ARRAY GRID_COUNT;
  REAL_ARRAY DEVICE_BOUNDS;
  REAL RMAX;
  REAL CELLSIZE;
  REAL Nx, Ny, Nz;
  INT_ARRAY OFFSET;
  REAL_ARRAY IDS;
  REAL NN_MAX;

  void FILL(REAL4_ARRAY &POSITIONS, INT &PARTICLE_AMOUNT, REAL &RMAX, REAL &CELLSIZE, REAL_ARRAY &DEVICE_BOUNDS,
            REAL &Nx, REAL &Ny, REAL &Nz, INT_ARRAY &GRID_COUNT, INT_ARRAY &OFFSET, REAL_ARRAY &IDS,
            INT_ARRAY &NN_COUNT, INT_ARRAY &NN_IDS, REAL &NN_MAX);
  void KernelsEnqeue(REAL_ARRAY IDS, REAL Nx, REAL Ny, REAL Nz, INT_ARRAY GRID_COUNT,
                     INT_ARRAY OFFSET, REAL4_ARRAY POSITIONS,  REAL_ARRAY DEVICE_BOUNDS, REAL CELLSIZE, INT_ARRAY NN_COUNT, INT_ARRAY NN_IDS,
                     REAL NN_MAX, INT PARTICLE_AMOUNT);

};

void ParticleArrays::FILL(REAL4_ARRAY &POSITIONS, INT &PARTICLE_AMOUNT, REAL &RMAX, REAL &CELLSIZE, REAL_ARRAY &DEVICE_BOUNDS, REAL &Nx, REAL &Ny, REAL &Nz, INT_ARRAY &GRID_COUNT, INT_ARRAY &OFFSET, REAL_ARRAY &IDS, INT_ARRAY &NN_COUNT, INT_ARRAY &NN_IDS, REAL &NN_MAX){

    compute::device device = compute::system::default_device();
        RMAX=0;
        using compute::int2_;
        NN_MAX=2;
        vtkDataSetReader* reader=vtkDataSetReader::New();
        DEVICE_BOUNDS.resize(6);
        reader->SetFileName("input.vtk");
        reader->Update();
        double* BOUNDS;
       BOUNDS=reader->GetOutput()->GetBounds();
        compute::copy(BOUNDS, BOUNDS+6, DEVICE_BOUNDS.begin(), compute::system::default_queue());
        compute::system::default_queue().finish();

        PARTICLE_AMOUNT=reader->GetOutput()->GetNumberOfPoints();
       // cout << PARTICLE_AMOUNT << endl;
        POSITIONS.resize(PARTICLE_AMOUNT*4);
                for(int i=0;i<PARTICLE_AMOUNT;i+=4)
                {
                double  p[4];
            reader->GetOutput()->GetPoint(i,p);
                POSITIONS[i]   =(boost::compute::float4_)p[0];
                POSITIONS[i+1] =(boost::compute::float4_)p[1];
                POSITIONS[i+2] =(boost::compute::float4_)p[2];
                //
                 p[3]=reader->GetOutput()->GetPointData()->GetArray("RADIUS")->GetTuple1(0); // radiusas ketvirtame elemente;
                //cout <<  POSITIONS[i] <<  " " << POSITIONS[i+1] << " " << POSITIONS[i+2] << " " << POSITIONS[i+3] <<  endl;
                if(RMAX<p[3])
                    RMAX=p[3];
                POSITIONS[i+3] =(boost::compute::float4_)p[3];

                }
        CELLSIZE=2*RMAX;
        Nx=ceil((BOUNDS[1]-BOUNDS[0])/CELLSIZE);
        Ny=ceil((BOUNDS[3]-BOUNDS[2])/CELLSIZE);
        Nz=ceil((BOUNDS[5]-BOUNDS[4])/CELLSIZE);
        GRID_COUNT.resize(Nx*Ny*Nz);
        cout << Nx << " " <<Ny << " " << Nz<< endl;

        GRID_COUNT={0};
        //std::fill(GRID_COUNT.begin(), GRID_COUNT.end(), 0);
        OFFSET.resize(Nx*Ny*Nz);
        IDS.resize(PARTICLE_AMOUNT);
        NN_COUNT.resize(PARTICLE_AMOUNT);
        NN_IDS.resize(PARTICLE_AMOUNT*NN_MAX);


}

void ParticleArrays::KernelsEnqeue( REAL_ARRAY IDS, REAL Nx, REAL Ny, REAL Nz, INT_ARRAY GRID_COUNT, INT_ARRAY OFFSET, REAL4_ARRAY POSITIONS,  REAL_ARRAY DEVICE_BOUNDS, REAL CELLSIZE, INT_ARRAY NN_COUNT, INT_ARRAY NN_IDS, REAL NN_MAX, INT PARTICLE_AMOUNT){

    //cout << PARTICLE_AMOUNT << " " << CELLSIZE << endl;
    compute::device device = compute::system::default_device();
    Resource sourceCode = LOAD_RESOURCE(Kernel_cl);
    std::stringstream source;
    //source<<"__constant double x_koef="<<5;
    source << std::string(sourceCode.data(), sourceCode.size());
    boost::compute::system::default_queue().finish();
    boost::compute::program program =
    boost::compute::program::create_with_source(source.str(), boost::compute::system::default_context());
    program.build("-I../ ");
    boost::compute::kernel kernel(program, "GridAddition");
    boost::compute::kernel kernel2(program, "GridCountSort");
    boost::compute::kernel kernel3(program, "NeighbourSearch");
    kernel.set_arg(0, POSITIONS);
    kernel.set_arg(1, DEVICE_BOUNDS);
    kernel.set_arg(2, GRID_COUNT);
    kernel.set_arg(3, CELLSIZE);
    kernel.set_arg(4, PARTICLE_AMOUNT);
    kernel.set_arg(5, Nx);
    kernel.set_arg(6, Ny);
    kernel.set_arg(7, Nz);

    // cout <<  POSITIONS[0] <<  endl;



    boost::compute::inclusive_scan(GRID_COUNT.begin(), GRID_COUNT.end(), OFFSET.begin());

    kernel2.set_arg(0, OFFSET);
    kernel2.set_arg(1, IDS);
    kernel2.set_arg(2, POSITIONS);
    kernel2.set_arg(3, Nx);
    kernel2.set_arg(4, Ny);
    kernel2.set_arg(5, Nz);
    kernel2.set_arg(6, GRID_COUNT);
    kernel2.set_arg(7, DEVICE_BOUNDS);
    kernel2.set_arg(8, CELLSIZE);

    kernel3.set_arg(0, POSITIONS);
    kernel3.set_arg(1, GRID_COUNT);
    kernel3.set_arg(2, OFFSET);
    kernel3.set_arg(3, NN_COUNT);
    kernel3.set_arg(4, NN_IDS);
    kernel3.set_arg(5, CELLSIZE);
    kernel3.set_arg(6, Nx);
    kernel3.set_arg(7, Ny);
    kernel3.set_arg(8, Nz);
    kernel3.set_arg(9, NN_MAX);
    kernel3.set_arg(10, DEVICE_BOUNDS);
    kernel3.set_arg(11, IDS);

   // cout << PARTICLE_AMOUNT << endl;
    compute::system::default_queue().enqueue_1d_range_kernel(kernel , 0, PARTICLE_AMOUNT , 0).wait();
    //compute::system::default_queue().enqueue_1d_range_kernel(kernel2, 0, PARTICLE_AMOUNT, 0).wait();
   // compute::system::default_queue().enqueue_1d_range_kernel(kernel3, 0, PARTICLE_AMOUNT, 0).wait();


}
