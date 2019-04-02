#include "coordinate_math.h"
#include "includes.h"
#include "dalele.h"
#include "map_bounds.h"

REAL4 operator * (REAL4 A, INT B)
        {
           A[0]*=B;
           A[1]*=B;
           A[2]*=B;
           A[3]*=B;
            return A;
        }

REAL4 operator + (REAL4 A, REAL4 B)
        {
           A[0]+=B[0];
           A[1]+=B[1];
           A[2]+=B[2];
           A[3]+=B[3];
            return A;
        }
REAL4 operator * (REAL A, REAL4 B)
        {
           B[0]*=A;
           B[1]*=A;
           B[2]*=A;
           B[3]*=A;
            return B;
        }
REAL4 operator * (REAL4 A, REAL4 B)
        {
           A[0]*=B[0];
           A[1]*=B[1];
           A[2]*=B[2];
           A[3]*=B[3];
            return A;
        }

REAL4 operator / (REAL4 A,  REAL B )
{
            A[0]/=B;
            A[1]/=B;
            A[2]/=B;
            A[3]/=B;
             return A;
}
REAL4 operator - (REAL4 A,  REAL4 B )
{
            A[0]-=B[0];
            A[1]-=B[1];
            A[2]-=B[2];
            A[3]-=B[3];
             return A;
}
REAL coordinate_math::dot_prod(REAL4 &vec_a, REAL4 &vec_b){  // dot produkto skaiciavimas
    REAL dot_prod_rez;
    dot_prod_rez=vec_a[0]*vec_b[0] + vec_a[1]*vec_b[1] + vec_a[2]*vec_b[2];
    return dot_prod_rez;
}
REAL4 coordinate_math::cross_prod(REAL4 &vec_a, REAL4 &vec_b){ //  cross produkto skaiciavimas
    REAL4 prod_rez;
    prod_rez[0]=vec_a[1]*vec_b[2]-vec_a[2]*vec_b[1];
    prod_rez[1]=vec_a[2]*vec_b[0]-vec_a[0]*vec_b[2];
    prod_rez[2]=vec_a[0]*vec_b[1]-vec_a[1]*vec_b[0];
    return prod_rez;
}
void coordinate_math::add_cell(Dalele &particle, REAL4 cell, REAL spind){
    cell[3]=spind;
    particle.F.push_back(cell);
}
vector<REAL4> coordinate_math::coordinate_math_(vector<REAL4> coordinates, REAL radius)
{
    INT spind;
// 3D skaiciavimai ////////////
    REAL ds1, ds2, ds3;
    REAL4 S1, S2, S3;
         REAL4 rez_sphere_coords_positive, rez_sphere_coords_negative;
         REAL saved_R;
         spind=radius;
         //rez_sphere_coords[3]=particle.Distribution[spind];
         rez_sphere_coords_positive[3]=1;
         rez_sphere_coords_negative[3]=1;
         saved_R=rez_sphere_coords_positive[3];

    S1=coordinates[0];
    S2=coordinates[1];
    S3=coordinates[2];

    ds1=S1[3]+rez_sphere_coords_positive[3];
    ds2=S2[3]+rez_sphere_coords_positive[3];
    ds3=S3[3]+rez_sphere_coords_positive[3];

    //cout << S1 << " " << S2 << " " << S3 << endl;
    REAL4 vector_u, vector_v, vector_w;
    REAL4 temporS1, temporS3;

    temporS1=S1-S2;
    temporS3=S1-S3;

    vector_u=temporS1/(sqrt(pow(temporS1[0],2)+pow(temporS1[1],2)+pow(temporS1[2],2)));
    vector_v=temporS3/(sqrt(pow(temporS3[0],2)+pow(temporS3[1],2)+pow(temporS3[2],2)));

    //cout << vector_w << endl;
    vector_w=S1*(-2);
    //cout << vector_w << endl;

    REAL calc_a, calc_b, calc_c;
    calc_a=(pow(ds2,2)-pow(ds1,2)+pow(S1[0],2)-pow(S2[0],2)+pow(S1[1],2)-pow(S2[1],2)+pow(S1[2],2)-pow(S2[2],2))/
            (2*sqrt(pow(temporS1[0],2)+pow(temporS1[1],2)+pow(temporS1[2],2)));
    calc_b=(pow(ds3,2)-pow(ds1,2)+pow(S1[0],2)-pow(S3[0],2)+pow(S1[1],2)-pow(S3[1],2)+pow(S1[2],2)-pow(S3[2],2))/
            (2*sqrt(pow(temporS3[0],2)+pow(temporS3[1],2)+pow(temporS3[2],2)));
    calc_c=pow(ds1,2)-pow(S1[0],2)-pow(S1[1],2)-pow(S1[2],2);

    REAL4 vector_t;
    REAL4 xProd=cross_prod(vector_u, vector_v);
    vector_t=xProd/(sqrt(pow(xProd[0],2)+pow(xProd[1],2)+pow(xProd[2],2)));
    //cout << vector_t<< endl;

    REAL rez_calc_a, rez_calc_b, rez_calc_c, rez_calc_d_positive, rez_calc_d_negative;
    rez_calc_a=(calc_a-calc_b*dot_prod(vector_u, vector_v))/(1-pow(dot_prod(vector_u, vector_v),2));
    rez_calc_b=(calc_b-calc_a*dot_prod(vector_u, vector_v))/(1-pow(dot_prod(vector_u, vector_v),2));

    vector<REAL4>rezultatai;
    rez_calc_c=pow(rez_calc_a,2)+pow(rez_calc_b,2)+2*rez_calc_a*rez_calc_b*dot_prod(vector_u, vector_v)
            +rez_calc_a*dot_prod(vector_u, vector_w)+rez_calc_b*dot_prod(vector_v, vector_w)-calc_c;

    rez_calc_d_positive=(0.5)*(-dot_prod(vector_w, vector_t)+sqrt(pow(dot_prod(vector_w, vector_t),2)-4*rez_calc_c)); // ar reikia minusines reiksmes
    rez_calc_d_negative=(0.5)*(-dot_prod(vector_w, vector_t)-sqrt(pow(dot_prod(vector_w, vector_t),2)-4*rez_calc_c));

    rez_sphere_coords_positive=rez_calc_a*vector_u+rez_calc_b*vector_v+rez_calc_d_positive*vector_t;
    rez_sphere_coords_negative=rez_calc_a*vector_u+rez_calc_b*vector_v+rez_calc_d_negative*vector_t;

    rez_sphere_coords_positive[3]=1;
    rez_sphere_coords_negative[3]=1;
    rezultatai.push_back(rez_sphere_coords_positive);
    rezultatai.push_back(rez_sphere_coords_negative);
    return rezultatai;
}


REAL4 coordinate_math::testine_matematika(REAL4 S1, REAL4 S2, REAL4 S3, REAL spindulys)
{
    INT spind;
// 3D skaiciavimai ////////////
    REAL ds1, ds2, ds3;

    ds1=S1[3]+S1[3];
    ds2=S2[3]+S2[3];
    ds3=S3[3]+S3[3];

    //cout << S1 << " " << S2 << " " << S3 << endl;
    REAL4 vector_u, vector_v, vector_w;
    REAL4 temporS1, temporS3;

    temporS1=S1-S2;
    temporS3=S1-S3;

    vector_u=temporS1/(sqrt(pow(temporS1[0],2)+pow(temporS1[1],2)+pow(temporS1[2],2)));
    vector_v=temporS3/(sqrt(pow(temporS3[0],2)+pow(temporS3[1],2)+pow(temporS3[2],2)));

    //cout << vector_w << endl;
    vector_w=S1*(-2);
    //cout << vector_w << endl;

    REAL calc_a, calc_b, calc_c;
    calc_a=(pow(ds2,2)-pow(ds1,2)+pow(S1[0],2)-pow(S2[0],2)+pow(S1[1],2)-pow(S2[1],2)+pow(S1[2],2)-pow(S2[2],2))/
            (2*sqrt(pow(temporS1[0],2)+pow(temporS1[1],2)+pow(temporS1[2],2)));
    calc_b=(pow(ds3,2)-pow(ds1,2)+pow(S1[0],2)-pow(S3[0],2)+pow(S1[1],2)-pow(S3[1],2)+pow(S1[2],2)-pow(S3[2],2))/
            (2*sqrt(pow(temporS3[0],2)+pow(temporS3[1],2)+pow(temporS3[2],2)));
    calc_c=pow(ds1,2)-pow(S1[0],2)-pow(S1[1],2)-pow(S1[2],2);



    REAL4 vector_t;
    REAL4 xProd=cross_prod(vector_u, vector_v);
    vector_t=xProd/(sqrt(pow(xProd[0],2)+pow(xProd[1],2)+pow(xProd[2],2)));
    //cout << vector_t<< endl;

    REAL rez_calc_a, rez_calc_b, rez_calc_c, rez_calc_d;
    rez_calc_a=(calc_a-calc_b*dot_prod(vector_u, vector_v))/(1-pow(dot_prod(vector_u, vector_v),2));
    rez_calc_b=(calc_b-calc_a*dot_prod(vector_u, vector_v))/(1-pow(dot_prod(vector_u, vector_v),2));

    rez_calc_c=pow(rez_calc_a,2)+pow(rez_calc_b,2)+2*rez_calc_a*rez_calc_b*dot_prod(vector_u, vector_v)
            +rez_calc_a*dot_prod(vector_u, vector_w)+rez_calc_b*dot_prod(vector_v, vector_w)-calc_c;

    rez_calc_d=(0.5)*(-dot_prod(vector_w, vector_t)+sqrt(pow(dot_prod(vector_w, vector_t),2)-4*rez_calc_c)); // ar reikia minusines reiksmes

    REAL4 rez_sphere_coords;
    rez_sphere_coords=rez_calc_a*vector_u+rez_calc_b*vector_v+rez_calc_d*vector_t;
    rez_sphere_coords[3]=spindulys;
    return rez_sphere_coords;

}
