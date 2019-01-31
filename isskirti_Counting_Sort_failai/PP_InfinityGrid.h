#ifndef PP_InfinityGrid_H
#define PP_InfinityGrid_H
#define MAX_VALUE 256
#include "core/IModule.h"
class PP_InfinityGrid : public IModule {
public:
  PP_InfinityGrid();
  virtual void Init(SimulationParameters &simulationParameters, Data &duomenys);
  virtual void PostExecuteModule(SimulationParameters &simulationParameters,
                                 Data &duomenys);
  virtual void PreExecuteModule(SimulationParameters &simulationParameters,
                                Data &duomenys);

  ULONG_ARRAY CELL_AND_PARTICLE_IDS;
  ULONG_ARRAY NEW_CELL_AND_PARTICLE_IDS;
  ULONG_ARRAY STARTAS;
  ULONG_ARRAY ENDAS;

  INT_ARRAY IDS;
  INT_ARRAY OFFSET;
  INT_ARRAY GRID_COUNT;  

  boost::compute::kernel GRID_ADD;
  boost::compute::kernel GRID_COUNTSORT;
  boost::compute::kernel GRID_NEIGHBOUR_SEARCH;  
};



#endif // PP_InfinityGrid_H
