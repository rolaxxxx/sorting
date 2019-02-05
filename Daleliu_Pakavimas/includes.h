#ifndef INCLUDES_H
#define INCLUDES_H
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
#include <boost/compute/types.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/sha1.hpp>
#include <stdio.h>
#include <boost/chrono/duration.hpp>
#include <stdlib.h>
#include <time.h>
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
#include <boost/compute/container/vector.hpp>
#include <boost/compute/algorithm/stable_sort_by_key.hpp>
#include <cstddef>
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
#include <boost/compute/algorithm/stable_sort.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/functional/math.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/utility/program_cache.hpp>
#include <boost/lockfree/queue.hpp>
#include <experimental/filesystem>
#include <iostream>
#include <boost/compute/utility/wait_list.hpp>
#include <vector>
#include <chrono>
#include <math.h>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkGlyph3D.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPointData.h>
#include <vtkCubeSource.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vtkDoubleArray.h>
//#include "geometry.h"
typedef boost::compute::double_ REAL;
typedef boost::compute::double4_ REAL4;
typedef boost::compute::uint_ UINT;
typedef boost::compute::int_ INT;
typedef boost::compute::int2_ INT2;
typedef boost::compute::double2_ REAL2;
typedef boost::compute::uint4_ UINT4;
typedef boost::compute::ulong_ ULONG;
typedef boost::compute::uchar_ UCHAR;
template <typename T> using CONTAINER_TYPE = boost::compute::vector<T>;

typedef CONTAINER_TYPE<REAL> REAL_ARRAY;
typedef CONTAINER_TYPE<REAL4> REAL4_ARRAY;
typedef CONTAINER_TYPE<REAL2> REAL2_ARRAY;
typedef CONTAINER_TYPE<UINT> UINT_ARRAY;
typedef CONTAINER_TYPE<INT> INT_ARRAY;
typedef CONTAINER_TYPE<INT2> INT2_ARRAY;
typedef CONTAINER_TYPE<UINT4> UINT4_ARRAY;
typedef CONTAINER_TYPE<ULONG> ULONG_ARRAY;
typedef CONTAINER_TYPE<UCHAR> UCHAR_ARRAY;

#endif // INCLUDES_H
