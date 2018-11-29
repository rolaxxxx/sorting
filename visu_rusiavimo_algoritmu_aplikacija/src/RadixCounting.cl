
__constant int RADIX = 8;                                                        // Number of bits per radix sort pass
__constant int RADIXBITS = 32;                                                   // Number of bits to sort over
__constant int RADIXTHREADS = 16;                                                // Number of threads sharing each radix counter
// Prefix sum variables

__global__ void insertParticles ( bufList buf, int pnum )
{
	uint i = __mul24(blockIdx.x, blockDim.x) + threadIdx.x;	// particle index				
	if ( i >= pnum ) return;

	register float3 gridMin = simData.gridMin;
	register float3 gridDelta = simData.gridDelta;
	register int3 gridRes = simData.gridRes;
	register int3 gridScan = simData.gridScanMax;
	register float poff = simData.psmoothradius / simData.psimscale;

	register int		gs;
	register float3		gcf;
	register int3		gc;

	gcf = (buf.mpos[i] - gridMin) * gridDelta; 
	gc = make_int3( int(gcf.x), int(gcf.y), int(gcf.z) );
	gs = (gc.y * gridRes.z + gc.z)*gridRes.x + gc.x;
	if ( gc.x >= 1 && gc.x <= gridScan.x && gc.y >= 1 && gc.y <= gridScan.y && gc.z >= 1 && gc.z <= gridScan.z ) {
		buf.mgcell[i] = gs;											// Grid cell insert.
		buf.mgndx[i] = atomicAdd ( &buf.mgridcnt[ gs ], 1 );		// Grid counts.
		gcf = (-make_float3(poff,poff,poff) + buf.mpos[i] - gridMin) * gridDelta;
		gc = make_int3( int(gcf.x), int(gcf.y), int(gcf.z) );
		gs = ( gc.y * gridRes.z + gc.z)*gridRes.x + gc.x;
		//buf.mcluster[i] = gs;				-- make sure it is allocated!
	} else {
		buf.mgcell[i] = GRID_UNDEF;
		//buf.mcluster[i] = GRID_UNDEF;		-- make sure it is allocated!
	}
}
__global__ void countingSortIndex ( bufList buf, int pnum )
{
	uint i = __mul24(blockIdx.x, blockDim.x) + threadIdx.x;		// particle index				
	if ( i >= pnum ) return;

	uint icell = buf.mgcell[i];
	uint indx =  buf.mgndx[i];
	int sort_ndx = buf.mgridoff[ icell ] + indx;				// global_ndx = grid_cell_offet + particle_offset
	if ( icell != GRID_UNDEF ) {
		buf.mgrid[ sort_ndx ] = i;					// index sort, grid refers to original particle order
	}
}
__global__ void countingSortFull ( bufList buf, int pnum )
{
	uint i = __mul24(blockIdx.x, blockDim.x) + threadIdx.x;		// particle index				
	if ( i >= pnum ) return;

	uint icell = *(uint*) (buf.msortbuf + pnum*BUF_GCELL + i*sizeof(uint) );
	uint indx =  *(uint*) (buf.msortbuf + pnum*BUF_GNDX + i*sizeof(uint) );
	int sort_ndx = buf.mgridoff[ icell ] + indx;				// global_ndx = grid_cell_offet + particle_offset
	if ( icell != GRID_UNDEF ) {
		buf.mgrid[ sort_ndx ] = sort_ndx;			// full sort, grid indexing becomes identity
		char* bpos = buf.msortbuf + i*sizeof(float3);
		buf.mpos[ sort_ndx ] =		*(float3*) (bpos);
		buf.mvel[ sort_ndx ] =		*(float3*) (bpos + pnum*BUF_VEL );
		buf.mveleval[ sort_ndx ] =	*(float3*) (bpos + pnum*BUF_VELEVAL );
		buf.mforce[ sort_ndx ] =	*(float3*) (bpos + pnum*BUF_FORCE );
		buf.mpress[ sort_ndx ] =	*(float*) (buf.msortbuf + pnum*BUF_PRESS + i*sizeof(float) );
		buf.mdensity[ sort_ndx ] =	*(float*) (buf.msortbuf + pnum*BUF_DENS + i*sizeof(float) );
		buf.mclr[ sort_ndx ] =		*(uint*) (buf.msortbuf + pnum*BUF_CLR+ i*sizeof(uint) );		// ((uint) 255)<<24; -- dark matter
		buf.mgcell[ sort_ndx ] =	icell;
		buf.mgndx[ sort_ndx ] =		indx;		
	}
}
