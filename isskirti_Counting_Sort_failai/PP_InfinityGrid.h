#ifndef PP_InfinityGrid_H
#define PP_InfinityGrid_H
#define MAX_VALUE 256
#include "core/IModule.h"
class PP_InfinityGrid : public IModule {
public:
  ULONG_ARRAY IDS;
  ULONG_ARRAY OFFSET;
  ULONG_ARRAY GRID_COUNT;  

  boost::compute::kernel GRID_ADD;
  boost::compute::kernel GRID_COUNTSORT;
  boost::compute::kernel GRID_NEIGHBOUR_SEARCH;  
};
#endif // PP_InfinityGrid_H
