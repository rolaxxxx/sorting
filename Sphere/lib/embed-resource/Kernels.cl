#define MAX_VALUE 256 
#define BLOCKS 1024  
#define THREADS 128

/*
kuo skiriasi isvedimas /n /r/n
kaip veikia bitmaskai
kodel masyve atsiranda tiek nuliu
ar galima kopijuoti duomenis is vieno masyvo i kita prilyginant ar reikia naudoti copy funkcija
ar galima ziureti tiesiog i mortonkodus ir tikrinti salia esancius kaimynus kol radius nevirsys pacios daleles 
kaip pakeisti bitmaskus kad mortoncodai nebutu 30ties bitu 
*/

void mymemcpy(__global uint *B,__local int *count, size_t N)
  {
     size_t i;

     for(i=0;i<N;i++)
       B[i] = count[i];
}

unsigned int expandBits(unsigned int  v) // kaip veikia expand bits funkcija ir kaip atskirti bitus 
{
    v = (v * 0x00010001u) & 0xFF0000FFu;
    v = (v * 0x00000101u) & 0x0F00F00Fu;
    v = (v * 0x00000011u) & 0xC30C30C3u;
    v = (v * 0x00000005u) & 0x49249249u;
    return v;
}
__kernel
void morton3D(__global double4* data, __global int* mortonCodes, __global double* device_bounds, __global int* device_particle_indexes)
{
    uint i=get_global_id(0);
    double4 pointas=data[i];
    
    pointas.x=(pointas.x-device_bounds[0])/(device_bounds[1]-device_bounds[0]);
    pointas.y=(pointas.y-device_bounds[2])/(device_bounds[3]-device_bounds[2]);
    pointas.z=(pointas.z-device_bounds[4])/(device_bounds[5]-device_bounds[4]);


// galiniai du skaiciai turi buti su float raide 
    pointas.x = min(max(pointas.x * 1024.0f, 0.0), 1023.0);
    pointas.y = min(max(pointas.y * 1024.0f, 0.0), 1023.0);
    pointas.z = min(max(pointas.z * 1024.0f, 0.0), 1023.0);
    //printf("reiksmes x,y,z pries expandinima %f   %f   %f  \n  ", pointas.x, pointas.y, pointas.z );

    unsigned int xx = expandBits((unsigned int)pointas.x); // kaip nusicastina reiksmes
    unsigned int yy = expandBits((unsigned int)pointas.y);
    unsigned int zz = expandBits((unsigned int)pointas.z);
    //printf("reiksmes x,y,z  %d   %d   %d  \n  " , xx, yy,zz );	
    mortonCodes[i]=0;

    mortonCodes[i]=xx * 4 + yy * 2 + zz; 
    device_particle_indexes[i]=mortonCodes[i];
    //printf("device particle indexes daleliu morton kodai %d  \n ", device_particle_indexes[i]);
}
__kernel
void nodeKurimas(__global double4* data, __global uint* mortonCodes, __global int* device_particle_indexes, uint n)
{
	uint idx= get_global_id(0);
	unsigned int first_node_part=device_particle_indexes[idx];
	unsigned int second_node_part=device_particle_indexes[idx+1];
	int  first_node_three_bits;
	int  second_node_three_bits;
	int  result_final_node=0;
	int  levels=0; // 10 lygiu numatyta su for ciklu 
	bool check_zeroes=false;
	for(int i=28;i>=3;i-=3){ // iki kiek turi testis ciklas kad paimtu tik du skaicius o ne visus skaicius
	first_node_three_bits=(((1 << 3) - 1) & (first_node_part >> (i - 1))); 	// im
	second_node_three_bits=(((1 << 3) - 1) & (second_node_part >> (i - 1)));
			if(first_node_three_bits==second_node_three_bits&&first_node_three_bits!=0){ // jeigu nors vieni trys bitai bus ne nuliai tikriname ar jie yra lygus
				//printf("result final node pries tris pastumtus bitus %d \n " , result_final_node);
				result_final_node<<=3;// pastumiu 3 bitus
				//printf("result final node po pastumtu triju bitu %d \n " , result_final_node); 
				result_final_node|=first_node_three_bits; // pridedu po tris bitus-lygi prie bendro formuojamo node 
				//printf("result final node po pridetu triju bitu gale %d \n " , result_final_node);
				levels++;// pliusinu lygius kad zinociau ar result node bus -1				
			}
			else {}
			if(first_node_three_bits!=second_node_three_bits&&levels>0)   	
				break;	
			else if(first_node_three_bits!=second_node_three_bits&&levels==0&&result_final_node==0)
				{
					result_final_node=1;
					break;
				}
	}
	device_particle_indexes[n-1+idx]=result_final_node*(-1);

	//printf("node'u rezultatai %d \n ", device_particle_indexes[n-1+idx]);
}
__kernel
void nodeHierarhija(__global int* device_particle_indexes, __global int2* device_tree_with_connections, uint n)
{
	 uint idx= get_global_id(0);
	 int2 temp;
	 if(device_particle_indexes[idx]>0){
	 temp.x=device_particle_indexes[idx];
	 temp.y=idx;
	 device_tree_with_connections[2*n+idx]=-temp;
	 //printf("tempor values %d   %d   \r\n", temp.x, temp.y);
	 }
	 else if(device_particle_indexes[idx]<0){
	 temp.x=(((1 << 28) - 1) & (device_particle_indexes[idx] >> (0 - 1))); // issaugoti node kuris butu trijais bitais aukstesnis kad gauti aukstesni node 
	 temp.y=idx; // nuemu 3 bitus nuo galo ir gaunu aukstesni node kuri issaugau kartu su lokacija 
	 device_tree_with_connections[2*n+idx]=-temp;
	 //printf("tempor values %d   %d   \r\n", temp.x, temp.y);
         }

}
 
  
