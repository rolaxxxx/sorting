#include "includes.h"
int main(int argc, char* argv[])
{
	vector<string>sortai{"radix", "stable", "merge-gpu", "merge-cpu", "stable-by-key", "radix-by-key", "bitonic", "counting", "RadixCount"};
	if (argc < 3) {
		cout << "turite ivesti 3 argumentus" << endl;

		cout << "pirmas argumentas yra kiek sortu noresite leisti" << endl;
		cout << "antras argumentas yra kiek elementu noresite rusiuoti" << endl;
		cout << "trecias elementas yra koki sorta noresite naudoti pvz : " << endl;
	 	for(int i=0;i<sortai.size();i++)
		cout << sortai[i] << endl;
		exit(1);
	}
 	compute::device device = compute::system::default_device();
	 
	std::stringstream source;

    	Resource sourceCode = LOAD_RESOURCE(BitonicSort_cl);
        source << std::string(sourceCode.data(), sourceCode.size());
	
    	boost::compute::program program = boost::compute::program::create_with_source(
        source.str(),
        boost::compute::system::default_context());
    	program.build(OPENCL_COMPILE_OPTIONS);
	boost::compute::kernel kernel(program, "bitonicSort");
	//program.build("-DNUM_SMS=6");
	//boost::compute::kernel kernel(program, "bitonicSort");

	std::stringstream source2;
	Resource sourceCode2 = LOAD_RESOURCE(CountingSort_cl);
        source2 << std::string(sourceCode2.data(), sourceCode2.size());
        boost::compute::system::default_queue().finish();
        program = boost::compute::program::create_with_source(
        source2.str(),
	boost::compute::system::default_context());
        program.build(OPENCL_COMPILE_OPTIONS);
        boost::compute::kernel kernel2 = boost::compute::kernel(program, "count");	
        boost::compute::kernel kernel3 = boost::compute::kernel(program, "merge");


	std::stringstream source3;

	int n=atoi(argv[1]);
        int elements=atoi(argv[2]); // visi rusiuojami elementai

	 const size_t NUM_SMS = 16;
         const size_t NUM_THREADS_PER_SM = 192;
         const size_t NUM_THREADS_PER_BLOCK = 64;
	 const size_t NUM_BLOCKS = (NUM_THREADS_PER_SM / NUM_THREADS_PER_BLOCK)*NUM_SMS; 
 
	 const size_t RADIX=8; // pakeiciau i 32 bitus                                                         // Number of bits per radix sort pass
	 const size_t RADICES=1 << RADIX;
	 const size_t RADIXTHREADS = 16;                                                // Number of threads sharing each radix counter
	 const size_t RADIXGROUPS=NUM_THREADS_PER_BLOCK / RADIXTHREADS;
	 const size_t TOTALRADIXGROUPS = NUM_BLOCKS * RADIXGROUPS;                      // Number of radix groups for each radix
	 const size_t SORTRADIXGROUPS = TOTALRADIXGROUPS * RADICES;                     // Total radix count
	 const size_t GRFELEMENTS = (NUM_THREADS_PER_BLOCK / RADIXTHREADS) * RADICES;
	 const size_t GRFSIZE = GRFELEMENTS * sizeof(uint);
	// Prefix sum variables
	
	 const size_t PREFIX_NUM_THREADS_PER_SM = NUM_THREADS_PER_SM; 
	 const size_t PREFIX_NUM_THREADS_PER_BLOCK = PREFIX_NUM_THREADS_PER_SM; 

	 const size_t PREFIX_NUM_BLOCKS = (PREFIX_NUM_THREADS_PER_SM / PREFIX_NUM_THREADS_PER_BLOCK) * NUM_SMS;
	 const size_t PREFIX_BLOCKSIZE = SORTRADIXGROUPS / PREFIX_NUM_BLOCKS;
	 const size_t PREFIX_GRFELEMENTS = PREFIX_BLOCKSIZE + 2 * PREFIX_NUM_THREADS_PER_BLOCK;
	 const size_t PREFIX_GRFSIZE = PREFIX_GRFELEMENTS * sizeof(uint);

// Shuffle variables
	 const size_t SHUFFLE_GRFOFFSET = RADIXGROUPS * RADICES;
	 const size_t SHUFFLE_GRFELEMENTS = SHUFFLE_GRFOFFSET + PREFIX_NUM_BLOCKS;
	 const size_t SHUFFLE_GRFSIZE = SHUFFLE_GRFELEMENTS * sizeof(uint);		
	 const size_t RAD_PREFIX=(RADICES/PREFIX_NUM_BLOCKS)*TOTALRADIXGROUPS;

	source3 <<"__constant int NUM_SMS="<<16<<";\n";
	source3 <<"__constant int NUM_THREADS_PER_SM="<<192<<";\n";
	source3 <<"__constant int NUM_THREADS_PER_BLOCK="<<64<<";\n";	
	source3 <<"__constant int NUM_BLOCKS="<<(NUM_THREADS_PER_SM / NUM_THREADS_PER_BLOCK)*NUM_SMS<<";\n";
	source3 <<"__constant int PREFIX_NUM_THREADS_PER_SM="<<NUM_THREADS_PER_SM<<";\n";
	source3 <<"__constant int PREFIX_NUM_THREADS_PER_BLOCK="<<PREFIX_NUM_THREADS_PER_SM<<";\n";
	source3 <<"__constant int RADICES="<<(1 << RADIX)<<";\n";  
	source3 <<"__constant int RADIXGROUPS="<<NUM_THREADS_PER_BLOCK / RADIXTHREADS<<";\n";
	source3 <<"__constant int TOTALRADIXGROUPS="<<NUM_BLOCKS * RADIXGROUPS<<";\n";
	source3 <<"__constant int SORTRADIXGROUPS="<<TOTALRADIXGROUPS * RADICES<<";\n";
	source3 <<"__constant int GRFELEMENTS="<<(NUM_THREADS_PER_BLOCK / RADIXTHREADS) * RADICES<<";\n";
	source3 <<"__constant int GRFSIZE="<<GRFELEMENTS * sizeof(uint)<<";\n";
	source3 <<"__constant int PREFIX_NUM_BLOCKS ="<<(PREFIX_NUM_THREADS_PER_SM/PREFIX_NUM_THREADS_PER_BLOCK)*NUM_SMS<<";\n";
	source3 <<"__constant int RAD_PREFIX ="<<(RADICES/PREFIX_NUM_BLOCKS)*TOTALRADIXGROUPS<<";\n";
	

	source3 <<"__constant int PREFIX_BLOCKSIZE="<< SORTRADIXGROUPS / PREFIX_NUM_BLOCKS<<";\n"; 
	source3 <<"__constant int PREFIX_GRFELEMENTS ="<<PREFIX_BLOCKSIZE + 2 * PREFIX_NUM_THREADS_PER_BLOCK<<";\n";
	source3 <<"__constant int PREFIX_GRFSIZE=" <<PREFIX_GRFELEMENTS * sizeof(uint)<<";\n";
	
	source3 <<"__constant int SHUFFLE_GRFOFFSET="<< RADIXGROUPS * RADICES<< ";\n";
	source3 <<"__constant int SHUFFLE_GRFELEMENTS="<<  SHUFFLE_GRFOFFSET + PREFIX_NUM_BLOCKS << ";\n";
	source3 <<"__constant int SHUFFLE_GRFSIZE="<< SHUFFLE_GRFELEMENTS * sizeof(uint) << ";\n";
	source3 <<"__constant int RADIXMASK =" <<  RADICES - 1  <<  ";\n";
	 boost::compute::vector<int> gRadixSum(TOTALRADIXGROUPS * RADICES);
	 boost::compute::vector<int> dRadixSum(TOTALRADIXGROUPS * RADICES);
	 boost::compute::vector<int> gRadixBlockSum(PREFIX_NUM_BLOCKS);
	 boost::compute::vector<int> dRadixBlockSum(PREFIX_NUM_BLOCKS);
        Resource sourceCode3 = LOAD_RESOURCE(RadixCounting_cl);
        source3 << std::string(sourceCode3.data(), sourceCode3.size());
        boost::compute::system::default_queue().finish();
        program = boost::compute::program::create_with_source(
        source3.str(),
        boost::compute::system::default_context());
        
	program.build(OPENCL_COMPILE_OPTIONS); // programos esamas erroras kai viskas sukompiliuojama
        boost::compute::kernel kernel4 = boost::compute::kernel(program, "RadixSum");
	boost::compute::kernel kernel5 = boost::compute::kernel(program, "RadixPrefixSum");
	boost::compute::kernel kernel6 = boost::compute::kernel(program, "RadixAddOffsetsAndShuffle");
	
		

	//int n=atoi(argv[1]);
	//int elements=atoi(argv[2]); // visi rusiuojami elementai 
	string sort=argv[3];

	vector<int> host_vector(elements);
	compute::vector<int>B(elements);
	vector<int> host_key_vector(elements);
        generate(host_vector.begin(), host_vector.end(), rand_int);
	boost::compute::system::default_queue().finish();

	generate(host_key_vector.begin(), host_key_vector.end(), rand_int);
	boost::compute::system::default_queue().finish();
	//KeyValuePair *pData0, *pData1;
        
	compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
	compute::vector<int> device_key_vector(host_key_vector.size(), compute::system::default_context());

	compute::vector<int> out_device_vector(host_vector.size(), compute::system::default_context());
        compute::vector<int> out_device_key_vector(host_vector.size(), compute::system::default_context());

	compute::vector<int> temp_device_vector(host_vector.size(), compute::system::default_context());
        compute::vector<int> temp_device_key_vector(host_vector.size(), compute::system::default_context());


	boost::compute::copy(host_vector.begin(), host_vector.end(), device_vector.begin(),  compute::system::default_queue());
	compute::system::default_queue().finish();
	boost::compute::copy(host_key_vector.begin(), host_key_vector.end(), device_key_vector.begin(), compute::system::default_queue());
	compute::system::default_queue().finish();
	


	kernel4.set_arg(0, device_key_vector);
	kernel4.set_arg(1, device_vector);

	kernel6.set_arg(0, device_key_vector);
	kernel6.set_arg(1, device_vector);
	kernel6.set_arg(2, out_device_key_vector);
	kernel6.set_arg(3, out_device_vector);
	kernel6.set_arg(4, elements);
	// ar reikia apibrezti ir paduoti globalius kintamuosius per kernel funkcija nes dabar globalus kintamieji yra apibrezti dvejose vietose ir viskas maisosi 
	kernel6.set_arg(7, gRadixSum);
	kernel6.set_arg(8, dRadixSum);
	kernel6.set_arg(9, gRadixBlockSum);
	kernel6.set_arg(10,dRadixBlockSum);
        clSetKernelArg(kernel6, 11, SHUFFLE_GRFSIZE, NULL);

	kernel5.set_arg(0, gRadixSum);
	kernel5.set_arg(1, dRadixSum);
	kernel5.set_arg(2, gRadixBlockSum);
	kernel5.set_arg(3, dRadixBlockSum);
	clSetKernelArg(kernel5, 4, PREFIX_GRFSIZE, NULL);
	kernel4.set_arg(5, gRadixSum);
	kernel4.set_arg(6, dRadixSum);
	kernel4.set_arg(7, gRadixBlockSum);
	kernel4.set_arg(8, dRadixBlockSum);
	clSetKernelArg(kernel4, 9, GRFSIZE, NULL);

	

				 cl_uint sortOrder = 1; // descending order else 1 for ascending order
				 //APIBREZTI KERNEL4 RADIXCOUNTA

				 kernel2.set_arg(0, device_vector);
				 kernel2.set_arg(1, device_key_vector);
                                 kernel2.set_arg(2, B);
                                 kernel2.set_arg(3, elements); //invalid memory object error 
			  	 kernel3.set_arg(0, B);
				 kernel.set_arg(0, device_vector);
                                 kernel.set_arg(3, sortOrder);

	double timer=0;
	for(int g=0;g<n;g++){
			 	compute::copy(host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue());
                                compute::system::default_queue().finish();
				if(sort=="radix-by-key" || sort=="stable-by-key"){
				compute::copy(host_key_vector.begin(), host_key_vector.end(), device_key_vector.begin(), compute::system::default_queue());
                                compute::system::default_queue().finish();}
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
			if(sort=="radix"){
				radixSort(device_vector);
			}			
			else if(sort=="stable"){
                                stableSort(device_vector);
                        }
			else if(sort=="merge-gpu"){
                                mergeSortGpu(device_vector);
                        }
			else if(sort=="merge-cpu"){
                                mergeSortCpu(device_vector);
                        }
			else if(sort=="stable-by-key"){
                                stableSortByKey(device_vector, device_key_vector);
                        }
			else if(sort=="radix-by-key"){
                                radixSortByKey(device_vector, device_key_vector);
                        }
			else if(sort=="RadixCount"){
				 // Round element count to total number of threads for efficiency
    				uint elements_rounded_to_3072;
    				int modval = elements % 3072;
    				if( modval == 0 )
        				elements_rounded_to_3072 = elements;
    						else
        						elements_rounded_to_3072 = elements + (3072 - (modval));
    				// Iterate over n bytes of y bit word, using each byte to sort the list in turn

    					kernel4.set_arg(2, elements);
					kernel6.set_arg(5, elements_rounded_to_3072);
					kernel4.set_arg(3, elements_rounded_to_3072);

					for (uint shift = 0; shift < RADIXBITS; shift += RADIX)
    					{

					kernel4.set_arg(4, shift);
					kernel6.set_arg(6, shift);

 						compute::system::default_queue().enqueue_nd_range_kernel(kernel4, size_t(1), 0, NUM_BLOCKS, 	0).wait();    
						compute::system::default_queue().enqueue_nd_range_kernel(kernel5, size_t(1), 0, PREFIX_NUM_BLOCKS, 0  ).wait();
						compute::system::default_queue().enqueue_nd_range_kernel(kernel6, size_t(1), 0, NUM_BLOCKS, 	NUM_THREADS_PER_BLOCK   ).wait();

					temp_device_key_vector = device_key_vector;
					device_key_vector = out_device_key_vector;
					out_device_key_vector=temp_device_key_vector;

					temp_device_vector = device_vector;
                                        device_vector = out_device_vector;
                                        out_device_vector=temp_device_vector;
      					}
			}
			else if(sort=="counting"){
				boost::compute::system::default_queue().enqueue_1d_range_kernel(kernel2, 0, elements , 0).wait();
				boost::compute::system::default_queue().enqueue_1d_range_kernel(kernel3, 0, elements , 0).wait();
                                B.clear();
                        }
			else if(sort=="bitonic"){
        			cl_uint stages = 0;
	
        			for(unsigned int i = elements; i > 1; i >>= 1) 
            				++stages;
				for(cl_uint stage = 0; stage < stages; ++stage) {
            			kernel.set_arg(1, stage);

            			for(cl_uint subStage = 0; subStage < stage +1; subStage++) {
					kernel.set_arg(2, subStage);
					boost::compute::system::default_queue().enqueue_1d_range_kernel(kernel, 0, elements ,0).wait();
				}	
				
				}
				boost::compute::system::default_queue().finish();
                        }
			
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
                                duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
                                timer+=time_span.count();
			
     }
	cout <<sort <<  " sortu kiekis " << n << " elementu kiekis " << elements <<  " rusiavimo laikas " << timer/n << endl;

    return 0;

}
