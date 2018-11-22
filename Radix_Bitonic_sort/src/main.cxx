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
//#define GROUP_SIZE 64
using namespace std;
#include "radixsort.h"
#include "Radix_Count.cl"

extern "C"
{
namespace compute = boost::compute;


int rand_int()
{
    return rand() % 60000000; // 60 milijonu skaiciu generavimas 
}

void RadixSort(KeyValuePair *pData0, KeyValuePair *pData1, uint elements, uint bits)
{
    // Round element count to total number of threads for efficiency
    uint elements_rounded_to_3072;
    int modval = elements % 3072;
    if( modval == 0 )
        elements_rounded_to_3072 = elements;
    else
        elements_rounded_to_3072 = elements + (3072 - (modval));

    // Iterate over n bytes of y bit word, using each byte to sort the list in turn
    for (uint shift = 0; shift < bits; shift += RADIX)
    {
        // Perform one round of radix sorting

        // Generate per radix group sums radix counts across a radix group
        RadixSum<<<NUM_BLOCKS, NUM_THREADS_PER_BLOCK, GRFSIZE>>>(pData0, elements, elements_rounded_to_3072, shift);
        // Prefix sum in radix groups, and then between groups throughout a block
        RadixPrefixSum<<<PREFIX_NUM_BLOCKS, PREFIX_NUM_THREADS_PER_BLOCK, PREFIX_GRFSIZE>>>();
        // Sum the block offsets and then shuffle data into bins
        RadixAddOffsetsAndShuffle<<<NUM_BLOCKS, NUM_THREADS_PER_BLOCK, SHUFFLE_GRFSIZE>>>(pData0, pData1, elements, elements_rounded_to_3072, shift); 

        // Exchange data pointers
        KeyValuePair* pTemp = pData0;
        pData0 = pData1;
        pData1 = pTemp;
    }
}
}
int main() {

			

}
