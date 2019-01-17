#pragma OPENCL EXTENSION cl_khr_fp64 : enable
__kernel
void GridAddition(__global double4* POSITIONS, double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  __global int* GRID_COUNT,  double CELLSIZE, int Nx, int Ny, int Nz)
{

        uint idx=get_global_id(0);
        double4 coords;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        //printf("atimties koordinates %d %f %f %f %f %f %f \n",idx, POSITIONS[idx].x, POSITIONS[idx].y, POSITIONS[idx].z, DEVICE_BOUNDS_MIN.x, DEVICE_BOUNDS_MIN.y, DEVICE_BOUNDS_MIN.z);

        int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        //printf("suskaiciuotas bendras ID is koordinaciu %f %f %f \n", coords.x, coords.y, coords.z);
        //printf("coords.y  %f Nx %d  sudauginta bendra reiksme %f \n" ,coords.y, Nx, coords.y*Nx);
        //printf("suskaiciuotas bendras ID is koordinaciu %d ", BENDRAS_ID);
        atomic_add(&GRID_COUNT[BENDRAS_ID],1);
	//printf(" grid count reiksmes %d  \n ", GRID_COUNT[BENDRAS_ID]);

}
__kernel
void GridCountSort(__global int* OFFSET, __global int* IDS,  __global double4* POSITIONS,    int Nx,   int Ny,  int Nz,  __global int* GRID_COUNT,  double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX,  double CELLSIZE)
{

        int idx=get_global_id(0);
        double4 temp, bounds_temp;
        temp=POSITIONS[idx];
        double4 coords;
	int sena_reiksme;
        coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
        //printf("bendras id suskaiciavus nenucastinus i inta %d  \n" ,coords.x+coords.y*Nx+coords.z*Nx*Ny);
        
	int BENDRAS_ID=coords.x+coords.y*Nx+coords.z*Nx*Ny;
        
	//printf("bendras id suskaiciavus nucastinus i inta %d \n  " ,BENDRAS_ID);
        //printf("GRID COUNT masyvo reiksmes  %d  ", GRID_COUNT[BENDRAS_ID]);
	 sena_reiksme=atom_add(&GRID_COUNT[BENDRAS_ID],1);
        
	//printf("  IDS indeksas %d  sena reiksme %d  \n" , OFFSET[BENDRAS_ID], sena_reiksme);

	IDS[OFFSET[BENDRAS_ID]+sena_reiksme]=idx;
        //printf("idx daleles reiksme %d " , idx);
        //printf("  IDS indeksas %d   \n" , OFFSET[BENDRAS_ID]+sena_reiksme);

}

__kernel
void NeighbourSearch(__global double4 *POSITIONS,  __global int* GRID_COUNT, __global int* OFFSET, __global int* NN_COUNT, __global int* NN_IDS,   double CELLSIZE,  int Nx,  int Ny,   int Nz,   int NN_MAX, double4 DEVICE_BOUNDS_MIN,  double4 DEVICE_BOUNDS_MAX, __global int* IDS,  int KIEKIS)
{
    int idx=get_global_id(0);
    double4 temp, tempPID;
    double  tempCurrentRadius, tempPIdRadius,L, tempIlgis;
    int c;
    int pid, ID, offset;
    int kiekis=0;
    double4 coords;
    temp=POSITIONS[idx];
    coords=floor((POSITIONS[idx]-DEVICE_BOUNDS_MIN)/CELLSIZE);
    tempCurrentRadius=temp.w;
    temp.w=0;
    //printf("koordinates idx daleles %f  %f  %f  %f \n ",temp.x,temp.y,temp.z,temp.w);

    for(int x=coords.x-1;x<=coords.x+1;x++){
        for(int y=coords.y-1;y<=coords.y+1;y++){
            for(int k=coords.z-1;k<=coords.z+1;k++){

                    if(x<Nx&&y<Ny&&k<Nz&&x>=0&&y>=0&&k>=0)
                        {  
                           ID=x+y*Nx+k*Nx*Ny;
                           //printf("aplinkines koordinates %d  %d  %d \n", x, y ,k );
                           //printf("suskaiciuota ID reiksme %d \n", ID );
                             c=GRID_COUNT[ID];
                               offset=OFFSET[ID];
                                 //printf("offset reiksme %d  c reiksme for ciklui %d \n ", offset , c);
                                   for(int l=0;l<c;l++){

                                     pid=IDS[offset+l];

                                     //printf("offset+l indeksas %d   IDS reiksme offset+l indekse %d  \n",offset+l, IDS[offset+l]);
                                     //printf("indexo pid numeris %d \n" , pid );

                                        if(pid!=idx){
                                         tempPID=POSITIONS[pid];
                                         //printf("indexo pid numeris %d \n" , pid );
                                         //printf("positions reiksmes %lf %lf %lf %lf",
                                         //printf("koordinates idx daleles %lf  %lf  %lf  %lf  \n",tempPID.x,tempPID.y,tempPID.z,tempPID.w);
                                         tempPIdRadius=tempPID.w;
                                         //printf("PID indexo daleles spindulys %f \n", tempPIdRadius);
                                         tempPID.w=0;
                                         //tempIlgis=distance(temp,tempPID); // ???
					//printf("temp vector ilgis %f  tempPID vector ilgis %f  vieno is kito ilgiu atimtis %f  distance funckijos rezultatas %f  radiusu sudetis %f  bendr rez %f  \n ", length(temp), length(tempPID), length(temp)-length(tempPID), distance(temp, tempPID), (tempCurrentRadius+tempPIdRadius), ((length(temp)-length(tempPID))-(tempCurrentRadius+tempPIdRadius)));
					//printf("%f %f %f ||  %f %f %f   ilgis gautas is koordinaciu  %f \n" , temp.x, temp.y, temp.z, tempPID.x, tempPID.y, tempPID.z, tempIlgis);
                                        //printf(" temp ilgio reiksme  %f  ", tempIlgis);
					  //printf("pirmas spindulys %f antras spindulys %f ",tempCurrentRadius, tempPIdRadius);
					//tempIlgis=sqrt(pow((temp.x-tempPID.x),2)+pow((temp.y-tempPID.y),2)+pow((temp.z-tempPID.z),2));
					tempIlgis=distance(temp,tempPID);

                                        L=length(temp-tempPID)-(tempCurrentRadius+tempPIdRadius); // ??

                                                        //printf("ilgis tarp dvieju vektoriu %f  idx daleles radius %f  pid indexo daleles radius %f  \n", tempIlgis, tempCurrentRadius, tempPIdRadius);
                                                            //printf("temp ilgis tarp dvieju vektoriu  %f  atimame is spinduliu sumos %f    gautas skirtumas %f  \n", tempIlgis, (tempCurrentRadius+tempPIdRadius), L);
                                                             // printf("bendras tikrinimas ilgis %f \n",L);
								if(L<=0){ // ???
                                                                    NN_IDS[idx*NN_MAX+kiekis]=pid;
                                                                      kiekis++;
									 //NN_COUNT[idx]=kiekis;
										 //NN_COUNT[idx]=kiekis;
									    //printf("pripliusinto kiekio reiksme %d \n " , kiekis);
                                                                      //atomic_add(&kiekis, 1 );
									//printf("kaimyno numeris   %d  \n" , pid );
                                                                    //printf("indeksas %d max kaimynu skaicius %d, uzpildymo kiekis kiekvienoje celeje %d \n" , idx, NN_MAX, kiekis);
                                                                }
           //NN_COUNT[idx]=kiekis;
		 NN_COUNT[idx]=kiekis;
	//KIEKIS+=kiekis;
		//printf("   %d     \n" , kiekis);
		

}
   }

  }


 }


}
}

//printf("kaimynu skaicius %d", kiekis);
}

