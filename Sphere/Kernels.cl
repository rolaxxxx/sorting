#include "headers.h"
struct int_pair {
    double first;
    double second;
    double third;
};
int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
__kernel
void mortonCode(__global double* x, __global double* y, __global double* z, __global double* mortonCodes) {

    uint i = get_global_id(0);
    int stride=0
    __local double x=data[i+stride];
    __local double y=data[i+1+stride];
    __local double z=data[i+2+stride];
	stride+=3;    
         string cordx;
         string cordy;
         string cordz;
	 string tempfull;
	sprintf(cordx, "%f", x);
	sprintf(cordy, "%f", y);
	sprintf(cordz, "%f", z);
	int cordxlen=strlen(cordx);
	int cordylen=strlen(cordy);
	int cordzlen=strlen(cordz);


    for(int h=cordxlen;h>=0;h--){
	tempfull+=cordx[h]+[cordy[h]+cordz[h];
}
    mortonCodes[i]=convertBinaryToDecimal(atof(tempfull));
}
__kernel
void hierarchy(__global double* x, __global double* y, __global double* z, __global double* hierarchy, __global double* mortonCodes){
	uint i= get_global_data(0);
	struct int_pair NWBpair;	
	struct int_pair SWBpair;
	struct int_pair NEBpair;
	struct int_pair SEBpair;
	struct int_pair NWTpair;
        struct int_pair SWTpair;
        struct int_pair NETpair;
        struct int_pair SETpair;
	
	NWBpair.xmax=50;
	NWBpair.ymax=50;
	NWBpair.zmax=50;
	SWBpair.xmax=100;
        SWBpair.ymax=50;
        SWBpair.zmax=50;
        NEBpair.xmax=50;
        NEBpair.ymax=100;
        NEBpair.zmax=50;
	SEBpair.xmax=100;
        SEBpair.ymax=100;
        SEBpair.zmax=50;
	
	NWTpair.xmax=50;
        NWTpair.ymax=50;
        NWTpair.zmax=100;
        SWTpair.xmax=100;
        SWTpair.ymax=50;
        SWTpair.zmax=100;
        NETpair.xmax=50;
        NETpair.ymax=50;
        NETpair.zmax=100;
        SETpair.xmax=100;
        SETpair.ymax=100;
        SETpair.zmax=100;

	if(x[i]<NWBpair.xmax && x[i]>=0 && y[i]<NWBpair.ymax && y[i]>=0 && z[i]<NWBpair.zmax && z[i]>=0)
		hierarchy[1]++;
	else if(x[i]<SWBpair.xmax && x[i]>=50 && y[i]<SWBpair.ymax && y[i]>=0 && z[i]<SWBpair.zmax && z[i]>=0)
		hierarchy[2]++;
	else if(x[i]>NEBpair.xmax && x[i]<=100 && y[i]<NEBpair.ymax && y[i]>=50 && z[i]<NEBpair.zmax && z[i]>=0)
                hierarchy[3]++;
	else if(x[i]<SEBpair.xmax && x[i]>=50 && y[i]<SEBpair.ymax && y[i]>=50 && z[i]<SEBpair.zmax && z[i]>=0)
                hierarchy[4]++;
	
	else if(x[i]<NWTpair.xmax && x[i]>=0 && y[i]<NWTpair.ymax && y[i]>=0 && z[i]<NWTpair.zmax && z[i]>=0)
                hierarchy[5]++;
        else if(x[i]<SWTpair.xmax && x[i]>=50 && y[i]<SWTpair.ymax && y[i]>=0 && z[i]<SWTpair.zmax && z[i]>=0)
                hierarchy[6]++;
        else if(x[i]>NETpair.xmax && x[i]<=100 && y[i]<NETpair.ymax && y[i]>=50 && z[i]<NETpair.zmax && z[i]>=0)
                hierarchy[7]++;
        else if(x[i]<SETpair.xmax && x[i]>=50 && y[i]<SETpair.ymax && y[i]>=50 && z[i]<SETpair.zmax && z[i]>=0)
                hierarchy[8]++;

		


}

__kernel
void quadTree(__global double* x, __global double* y, __global double* z, __global double* mortonCodes __global double* radius) {

	uint i= get_global_data(0);
	double dalxcord=x[i];
	double dalycord=y[i];
	double dalzcord=z[i];
	__local vector<uint>hierarchy(0);	
		
		

}
