#include "PP_InfinityGrid.h"
#include <iostream>
using namespace std;
PP_InfinityGrid::PP_InfinityGrid() {}
void PP_InfinityGrid::Init(SimulationParameters &simulationParameters,
                           Data &duomenys) {
  std::stringstream source;
  simulationParameters.CONTACT_SEARCH.CELL_SIZE = simulationParameters.READER.MAX_RADIUS*2;
  source << "__constant "
         << " REAL CELL_SIZE="
         << GetDoubleFloatString(simulationParameters.CONTACT_SEARCH.CELL_SIZE)
         << ";\n";

  Resource text = LOAD_RESOURCE(PP_InfinityGrid_cl);
  source << std::string(text.data(), text.size());

  Logger::getInstance()->LoggerBuild->info(std::string(
      GetDefaultSources(simulationParameters, duomenys) + source.str()));
  program = boost::compute::program::create_with_source(
      GetDefaultSources(simulationParameters, duomenys) + source.str(),
      boost::compute::system::default_context());
  program.build(OPENCL_COMPILE_OPTIONS);
  
  GRID_ADD = boost::compute::kernel(program, "GridAddition");
  GRID_COUNTSORT= boost::compute::kernel(program, "GridCountSort");   
  GRID_NEIGHBOUR_SEARCH= boost::compute::kernel(program, "NeighbourSearch");
 
  INT Nx, Ny, Nz;
  Nx=ceil((simulationParameters.READER.BOUNDS_MAX[0]-simulationParameters.READER.BOUNDS_MIN[0])/simulationParameters.CONTACT_SEARCH.CELL_SIZE);
  Ny=ceil((simulationParameters.READER.BOUNDS_MAX[1]-simulationParameters.READER.BOUNDS_MIN[1])/simulationParameters.CONTACT_SEARCH.CELL_SIZE);
  Nz=ceil((simulationParameters.READER.BOUNDS_MAX[2]-simulationParameters.READER.BOUNDS_MIN[2])/simulationParameters.CONTACT_SEARCH.CELL_SIZE);
    
  RESIZE(GRID_COUNT, (Nx*Ny*Nz));
  RESIZE(IDS, duomenys.PARTICLES.NUMBER_OF_PARTICLES);
  RESIZE(OFFSET, (Nx*Ny*Nz));
  RESIZE(duomenys.PARTICLES.NN_COUNT, duomenys.PARTICLES.NUMBER_OF_PARTICLES);
  RESIZE(duomenys.PARTICLES.NN_IDS, duomenys.PARTICLES.NUMBER_OF_PARTICLES*simulationParameters.GPU.NN_MAX);
  
    GRID_ADD.set_arg(0, duomenys.PARTICLES.POSITIONS);
    GRID_ADD.set_arg(1, simulationParameters.READER.BOUNDS_MIN);
    GRID_ADD.set_arg(2, simulationParameters.READER.BOUNDS_MAX);
    GRID_ADD.set_arg(3, GRID_COUNT);
    GRID_ADD.set_arg(4, Nx);
    GRID_ADD.set_arg(5, Ny);
    GRID_ADD.set_arg(6, Nz);

    GRID_COUNTSORT.set_arg(0, OFFSET);
    GRID_COUNTSORT.set_arg(1, IDS);
    GRID_COUNTSORT.set_arg(2, duomenys.PARTICLES.POSITIONS);
    GRID_COUNTSORT.set_arg(3, Nx);
    GRID_COUNTSORT.set_arg(4, Ny);
    GRID_COUNTSORT.set_arg(5, Nz);
    GRID_COUNTSORT.set_arg(6, GRID_COUNT);
    GRID_COUNTSORT.set_arg(7, simulationParameters.READER.BOUNDS_MIN); // issaugoti sale Data klases
    GRID_COUNTSORT.set_arg(8, simulationParameters.READER.BOUNDS_MAX);

    GRID_NEIGHBOUR_SEARCH.set_arg(0, duomenys.PARTICLES.POSITIONS);
    GRID_NEIGHBOUR_SEARCH.set_arg(1, GRID_COUNT);
    GRID_NEIGHBOUR_SEARCH.set_arg(2, OFFSET);
    GRID_NEIGHBOUR_SEARCH.set_arg(3, duomenys.PARTICLES.NN_COUNT);
    GRID_NEIGHBOUR_SEARCH.set_arg(4, duomenys.PARTICLES.NN_IDS);
    GRID_NEIGHBOUR_SEARCH.set_arg(5, Nx);
    GRID_NEIGHBOUR_SEARCH.set_arg(6, Ny);
    GRID_NEIGHBOUR_SEARCH.set_arg(7, Nz);
    GRID_NEIGHBOUR_SEARCH.set_arg(8, simulationParameters.READER.BOUNDS_MIN);
    GRID_NEIGHBOUR_SEARCH.set_arg(9, simulationParameters.READER.BOUNDS_MAX);
    GRID_NEIGHBOUR_SEARCH.set_arg(10,IDS);

}
void PP_InfinityGrid::PostExecuteModule(
    SimulationParameters &simulationParameters, Data &duomenys) {     
     boost::compute::fill(GRID_COUNT.begin(), GRID_COUNT.end(),0);  
     boost::compute::system::default_queue().enqueue_1d_range_kernel(GRID_ADD , 0, duomenys.PARTICLES.NUMBER_OF_PARTICLES, 0).wait();
     boost::compute::exclusive_scan(GRID_COUNT.begin(), GRID_COUNT.end(), OFFSET.begin());
     boost::compute::system::default_queue().finish();
     boost::compute::fill(GRID_COUNT.begin(),GRID_COUNT.end(),0);
     boost::compute::system::default_queue().finish();     
     boost::compute::system::default_queue().enqueue_1d_range_kernel(GRID_COUNTSORT, 0, duomenys.PARTICLES.NUMBER_OF_PARTICLES, 0).wait(); 
     boost::compute::system::default_queue().enqueue_1d_range_kernel(GRID_NEIGHBOUR_SEARCH, 0, duomenys.PARTICLES.NUMBER_OF_PARTICLES, 0).wait();
}

void PP_InfinityGrid::PreExecuteModule(
    SimulationParameters &simulationParameters, Data &duomenys) {}
	

