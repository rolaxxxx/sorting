#include "includes.h"
#include "skirstinys.h"
#include "dalele.h"
#include "mapaddandparticlesearch.h"
#include "map_bounds.h"
#include "coordinate_math.h"
#include "coordinate_math.cpp"

int main(int, char *[])
{


    coordinate_math test_math;
    REAL4_ARRAY S1;
    REAL4_ARRAY S2;
    REAL4_ARRAY S3;
    REAL radius;
    REAL4 temp1, temp2, temp3;
    REAL4 cp1, cp2, cp3;

   //TESTAS NR1
        cp1[0]=0.781398;
        cp1[1]=0.242197;
        cp1[2]=0.797176;
        cp1[3]=1;

        cp2[0]=0.932159;
        cp2[1]=1.30012;
        cp2[2]=-0.893409;
        cp2[3]=1;

        cp3[0]=-0.409861;
        cp3[1]=1.8201;
        cp3[2]=0.495329;
        cp3[3]=1;

        S1.push_back(cp1);
        S2.push_back(cp2);
        S3.push_back(cp3);

        //TESTAS NR2
             cp1[0]=0;
             cp1[1]=0;
             cp1[2]=0;
             cp1[3]=1;

             cp2[0]=2;
             cp2[1]=0;
             cp2[2]=0;
             cp2[3]=1;

             cp3[0]=1;
             cp3[1]=1.73205;
             cp3[2]=0;
             cp3[3]=1;

             S1.push_back(cp1);
             S2.push_back(cp2);
             S3.push_back(cp3);


             //TESTAS NR3
                  cp1[0]=0.5;
                  cp1[1]=0.3;
                  cp1[2]=0.2;
                  cp1[3]=1;

                  cp2[0]=1.75;
                  cp2[1]=1.599;
                  cp2[2]=-0.666;
                  cp2[3]=1;

                  cp3[0]=0.375;
                  cp3[1]=2.24856;
                  cp3[2]=0.633012;
                  cp3[3]=1;

                  S1.push_back(cp1);
                  S2.push_back(cp2);
                  S3.push_back(cp3);

REAL4 centras;

    for(int i=0;i<S1.size();i++)
        {
        temp1=S1[i];
        temp2=S2[i];
        temp3=S3[i];

      centras=test_math.testine_matematika(temp1, temp2, temp3, radius );

      //cout << centras << endl;

            REAL ilgis1=sqrt((temp1[0]-centras[0])*(temp1[0]-centras[0])+
                    (temp1[1]-centras[1])*(temp1[1]-centras[1])
                    +(temp1[2]-centras[2])*(temp1[2]-centras[2]))-(centras[3]+temp1[3]);

            REAL ilgis2=sqrt((temp2[0]-centras[0])*(temp2[0]-centras[0])+
                    (temp2[1]-centras[1])*(temp2[1]-centras[1])
                    +(temp2[2]-centras[2])*(temp2[2]-centras[2]))-(centras[3]+temp2[3]);

            REAL ilgis3=sqrt((temp3[0]-centras[0])*(temp3[0]-centras[0])+
                    (temp3[1]-centras[1])*(temp3[1]-centras[1])
                    +(temp3[2]-centras[2])*(temp3[2]-centras[2]))-(centras[3]+temp3[3]);

        std::cout<<"Testas NR "<<i<<" ilgis ="<<ilgis1<< " " << ilgis2 << " " << ilgis3 << endl;

    }

}
