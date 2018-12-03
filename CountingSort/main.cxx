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
#include "main.h"
#include <boost/compute/utility/wait_list.hpp>
#include <vector>
#include <math.h>  
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/container/vector.hpp>

int main()
{
	compute::device device = compute::system::default_device();
        Resource sourceCode = LOAD_RESOURCE(Kernels_cl);
        std::stringstream source;
        //source<<"__constant double x_koef="<<5;
        source << std::string(sourceCode.data(), sourceCode.size());
        boost::compute::system::default_queue().finish();
        boost::compute::program program =
        boost::compute::program::create_with_source(source.str(), boost::compute::system::default_context());
        program.build("-I../ ");///////////////////// programa luzta sitoje vietoje /////////////////////////
        //boost::compute::kernel kernel(program, "morton3D");
        //boost::compute::kernel kernel2(program, "nodeKurimas");
        //boost::compute::kernel kernel3(program, "nodeHierarhija");
        using compute::int2_;
	
	REAL4_ARRAY POSITIONS;
	INT PARTICLE_AMOUNT;
	
	ParticleArrays coordinates;
	coordinates.FILL(coordinates.POSITIONS, coordinates.PARTICLE_AMOUNT);
	          
}
