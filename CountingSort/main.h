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
  void FILL(REAL4_ARRAY POSITIONS, INT PARTICLE_AMOUNT);
};

void ParticleArrays::FILL(REAL4_ARRAY POSITIONS, INT PARTICLE_AMOUNT){
	
	compute::device device = compute::system::default_device();
        Resource sourceCode = LOAD_RESOURCE(Kernels_cl);
        std::stringstream source;
        //source<<"__constant double x_koef="<<5;
        source << std::string(sourceCode.data(), sourceCode.size());
        boost::compute::system::default_queue().finish();
        boost::compute::program program = boost::compute::program::create_with_source(source.str(), boost::compute::system::default_context());
        program.build("-I../ ");///////////////////// programa luzta sitoje vietoje /////////////////////////
        using compute::int2_;

        vtkDataSetReader* reader=vtkDataSetReader::New();
        reader->SetFileName("input.vtk");
        reader->Update();

        PARTICLE_AMOUNT=reader->GetOutput()->GetNumberOfPoints();
	
                for(int i=0;i<PARTICLE_AMOUNT;i+=4) // po keturis kad neperasyti jau buvusiu daleliu
                {
                REAL4  p[3]; // ar galima sitaip castinti nuskaitant elementus
                reader->GetOutput()->GetPoint(i,p);
                POSITIONS[i]   =(REAL4)p[0];
                POSITIONS[i+1] =(REAL4)p[1];
                POSITIONS[i+2] =(REAL4)p[2];
                POSITIONS[i+3] =(REAL4)reader->GetOutput()->GetPointData()->GetArray("RADIUS")->GetTuple1(0); // radiusas ketvirtame elemente;
                cout <<  POSITIONS[i] <<  " " << POSITIONS[i+1] << " " << POSITIONS[i+2] << " " << POSITIONS[i+3] <<  endl;
                }	
}
