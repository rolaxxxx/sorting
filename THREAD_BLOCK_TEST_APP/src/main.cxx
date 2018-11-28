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
 #include <CL/cl.hpp>
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
#include <iostream>
#include <boost/compute/utility/wait_list.hpp>
#include <vector>
#include <math.h>  
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/container/vector.hpp>
//#define GROUP_SIZE 64
using namespace std;
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
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
#include <boost/compute/device.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/assert.hpp>
#include <algorithm>
#include <boost/compute/algorithm/stable_sort.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/math.hpp>
#include <chrono>
#include <boost/compute/algorithm/sort_by_key.hpp>
int main() {
		
		const char source[] =BOOST_COMPUTE_STRINGIZE_SOURCE(
    __kernel void sum()
    {
         printf("local id dim 0  %d \n", get_local_id(0));
	 //printf("local id kitimas %d \n", get_global_id());
         barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);
    }
);
	 size_t NUM_BLOCKS=10000;
	 size_t THREADS=64;
    	compute::program program =
        compute::program::create_with_source(source, boost::compute::system::default_context());

    	program.build();

	compute::kernel kernel = program.create_kernel("sum");			
	compute::system::default_queue().enqueue_nd_range_kernel(kernel,  size_t(1),   0,  cl::NDRange(NUM_BLOCKS), cl::NDRange(THREADS)).wait(); 
}

