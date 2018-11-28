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
#include "Logger.h"
#include <boost/lockfree/queue.hpp>
#include "Timer.h"
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
#include "Resource.h" 
#include <boost/compute/algorithm/sort_by_key.hpp>


static const int RADIXBITS = 16; 

namespace compute = boost::compute;
using namespace std;
using namespace std::chrono;

/* Radixsort project which demonstrates the use of CUDA in a multi phase
 * sorting computation.
 * Type definitions.
 */

#ifndef _RADIXSORT_H_
#define _RADIXSORT_H_


#define SYNCIT __syncthreads()


typedef unsigned int uint;
typedef unsigned short ushort;


#endif // #ifndef _RADIXSORT_H_


int RADIX = 8; 
int RADICES = 1 << RADIX; 

int rand_int()
{
    return rand() % 1000000; // 60000000
}


#define SDATA( index)      CUT_BANK_CHECKER(sdata, index)

// Prefix sum data
void radixSort(compute::vector<int> device_vector)
{
        compute::detail::radix_sort(device_vector.begin(), device_vector.end(), compute::system::default_queue());
        compute::system::default_queue().finish();
}

void stableSort(compute::vector<int> device_vector)
{
        compute::stable_sort(device_vector.begin(), device_vector.end(), compute::system::default_queue());
        compute::system::default_queue().finish();
}

void mergeSortGpu(compute::vector<int> device_vector)
{
	compute::greater<int> greater;
        compute::detail::merge_sort_on_gpu(device_vector.begin(), device_vector.end(), greater, compute::system::default_queue());
        compute::system::default_queue().finish();
}

void mergeSortCpu(compute::vector<int> device_vector)
{
	compute::greater<int> greater;
        compute::detail::merge_sort_on_cpu(device_vector.begin(), device_vector.end(), greater, compute::system::default_queue());
        compute::system::default_queue().finish();
}


void stableSortByKey(compute::vector<int> device_vector, compute::vector<int> device_key_vector)
{
        compute::stable_sort_by_key(device_key_vector.begin(), device_key_vector.end(), device_vector.begin(), compute::system::default_queue());
        compute::system::default_queue().finish();
}

void radixSortByKey(compute::vector<int> device_vector, compute::vector<int> device_key_vector)
{
        compute::detail::radix_sort_by_key(device_key_vector.begin(), device_key_vector.end(), device_vector.begin(),compute::system::default_queue());
        compute::system::default_queue().finish();
}
