#define MAX_VALUE 256 
#define BLOCKS 512  
#define THREADS 64


void mymemcpy(__global uint *B,__local int *count, size_t N)
  {
     size_t i;

     for(i=0;i<N;i++)
       B[i] = count[i];
  }
__kernel void count(__global uint *A, __global uint *B, int n) {
			int b_id = get_group_id(0);
			int b_num = get_num_groups(0);
                        int b_size;
                        int b_offset;
                        int t_id    = get_local_id(0);
                        int t_num   = get_local_size(0);
                        int t_size;
                        int t_offset;
                        int offset;

        // initialize a shared memory array to store the count for each block.
        __local int count[MAX_VALUE];

        // set intial values to zeros. Each thread sets its own share to zero.
        t_size = (t_num > MAX_VALUE ? 1 : MAX_VALUE / t_num);
        offset = t_id * t_size;
        for (int i = offset; i < offset + t_size && i < MAX_VALUE; ++i)
                count[i] = 0;

        // wait until all threads have completed the initialization process.
	barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        // accumulate the counts of each value. Each thread counts a certain portain
        // of the unsorted array.
        b_size = (b_num > n ? 1 : n / b_num);
        b_offset = b_id * b_size;

        t_size = (t_num > b_size ? 1 : b_size / t_num);

        offset = b_offset + t_id * t_size;
        for (int i = offset; i < offset + t_size && i < b_offset + b_size && i < n; ++i)
                atomic_add(&count[A[i]], 1);

        // wait until all threads have completed the couting phase.
	barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        // copy the block count into global memory. Each thread copies its portioin to
        // the global memory.
        t_size = (t_num > MAX_VALUE ? 1 : MAX_VALUE / t_num);
        t_offset = t_id * t_size;
        offset = b_id * MAX_VALUE + t_offset;

        if (offset + t_size <= (b_id + 1) * MAX_VALUE)
               mymemcpy(&B[offset], &count[t_offset], sizeof(int) * t_size);
}


__kernel void merge(__global uint *B) {

        int b_id        = get_group_id(0),
                b_num   = get_num_groups(0),
                b_size,
                b_offset,
                t_id    = get_local_id(0),
                t_num   = get_local_size(0),
                t_size,
                offset;

        // loop through and merge until all arrays are merged.
        for (int i = b_num, j = 2; i != 1; i /= 2, j *= 2) {

                // each block will operate on b_size values which equal, the number of
                // count arrays * size of count arrays / number of blocks / 2. The final 2
                // represents the merge process.
                b_size = i * MAX_VALUE / b_num / 2;
                b_offset = (b_id / j) * (j * MAX_VALUE) + b_size * (b_id % j);

                t_size = (t_num > b_size ? 1 : b_size / t_num);

                // calculate the offset that each thread will start at and sum counts.
                offset = b_offset + t_id * t_size;
                for (int k = offset, l = offset + (MAX_VALUE * (j / 2));
                        k < offset + t_size && k < b_offset + b_size; ++k, ++l)
                        B[k] += B[l];

                // wait untill all arrays are merged for every step.
		barrier(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE);

        }

}


