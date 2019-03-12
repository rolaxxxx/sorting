#include "includes.h"
#include "geometry.h"
#include "dalele.h"
#include "grid_count.h"
#include "map_bounds.h"
#include "coordinate_math.h"

int main(int, char *[])
{

    coordinate_math test_math;
    std::vector<REAL4> S1;
    std::vector<REAL4> S2;
    std::vector<REAL4> S3;
    REAL radius;

   //TESTAS NR1
        S1[0]=0.781398;
        S1[1]=0.242197;
        S1[2]=0.797176;
        S1[3]=1;

        S2[0]=0.932159;
        S2[1]=1.30012;
        S2[2]=-0.893409;
        S2[3]=1;

        S3[0]=-0.409861;
        S3[1]=1.8201;
        S3[2]=0.495329;
        S3[3]=1;


    for(int i=0;i<S1.size();i++)
        {
            REAL4 centras=test_math();
            double ilgis1=std::sqrt((S1[i][0]-centras[0])*(S1[i][0]-centras[0])+
                    (S1[i][1]-centras[1])*(S1[i][2]-centras[1])
                    +(S1[i][2]-centras[2])*(S1[i][1]-centras[2]))-(centras[3]+S1[3]);
            double ilgis1=??? centas su S1  -R1 R2  turetai gauti apie 0
            double ilgis2=??? centras su S2
            double ilgis3=??? centras su S3
        std::cout<<"Testas NR "<<i<<" iglis1 ="<<ilgis1<<
        }



    REAL4 S1, S2, S3, spind
    test_math();




}
