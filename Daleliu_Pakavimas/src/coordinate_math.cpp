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
REAL coordinate_math::dot_prod(REAL4 &vec_a, REAL4 &vec_b){
    REAL dot_prod_rez;
    dot_prod_rez=vec_a[0]*vec_b[0] + vec_a[1]*vec_b[1] + vec_a[2]*vec_b[2];
    return dot_prod_rez;
}
REAL4 coordinate_math::cross_prod(REAL4 &vec_a, REAL4 &vec_b){
    REAL4 prod_rez;
    prod_rez[0]=vec_a[1]*vec_b[2]-vec_a[2]*vec_b[1];
    prod_rez[1]=vec_a[2]*vec_b[0]-vec_a[0]*vec_b[2];
    prod_rez[2]=vec_a[0]*vec_b[1]-vec_a[1]*vec_b[0];
    //cout <<vec_a[0] << " " << vec_b[1] << " " << vec_b[1] << " " << vec_a[0] << endl;
    return prod_rez;
}


void coordinate_math::coordinate_math_(Dalele &particle, MAP_BOUNDS boundai)
{

    REAL4 particle_coords, further_coords, third_coords, tetrahedron_top_coords; // S1 S2 S3 with radii at 4th coord
    REAL4 result_tetrahedron_coords;
    REAL4 triangle_sides, tetrahedron_sides;

    particle_coords[0]=boundai.MAP_BOUNDS_MAX[0]-(boundai.MAP_BOUNDS_MAX[0]/2);
    particle_coords[1]=boundai.MAP_BOUNDS_MAX[1]-(boundai.MAP_BOUNDS_MAX[1]/2);
    particle_coords[2]=0;
    //cout << particle_coords[0] << particle_coords[1]<< particle_coords[2]  << endl;
    INT spind;
    spind=rand()%particle.Distribution.size(); // spindulio gavimas is pasiskirstymo. Kintamieji kolkas vienodi
    particle_coords[3]=particle.Distribution[spind];
    //cout << particle_coords[3] << endl;
    particle.F.push_back(particle_coords);

    further_coords[0]=(boundai.MAP_BOUNDS_MAX[0]-(boundai.MAP_BOUNDS_MAX[0]/2))+2*particle_coords[3];
    further_coords[1]=(boundai.MAP_BOUNDS_MAX[1]-(boundai.MAP_BOUNDS_MAX[1]/2));
    further_coords[2]=0;
    //cout <<[0] << particle_coords[1]<< particle_coords[2]  << endl;
    spind=rand()%particle.Distribution.size();
    further_coords[3]=particle.Distribution[spind];
    particle.F.push_back(further_coords);

    spind=rand()%particle.Distribution.size();
    third_coords[3]=particle.Distribution[spind];

    triangle_sides[0]=further_coords[3]+third_coords[3]; // a
    triangle_sides[1]=particle_coords[3]+third_coords[3]; // b
    triangle_sides[2]=particle_coords[3]+further_coords[3];// c

   // cout << triangle_sides[0] << " " << triangle_sides[1] << " " << triangle_sides[2] << endl;



    third_coords[0]=particle_coords[0]+particle_coords[3]; //e
    third_coords[1]=particle_coords[0]+((particle_coords[3]*2)*sqrt(3)/2); // f
    third_coords[2]=0;
    //cout << third_coords[0] << " " << third_coords[1] << " " << third_coords[2] << endl;
    particle.F.push_back(third_coords);
    spind=rand()%particle.Distribution.size();

    tetrahedron_top_coords[3]=particle.Distribution[spind];

    tetrahedron_sides[0]=particle_coords[3]+tetrahedron_top_coords[3]; // m
    tetrahedron_sides[1]=further_coords[3]+tetrahedron_top_coords[3]; // n
    tetrahedron_sides[2]=third_coords[3]+tetrahedron_top_coords[3]; // p

    tetrahedron_top_coords[0]=(pow(tetrahedron_sides[0],2)+pow(triangle_sides[2],2)-pow(tetrahedron_sides[1],2))/2*triangle_sides[2];

    tetrahedron_top_coords[1]=(pow(third_coords[1],2)*triangle_sides[2]+pow(tetrahedron_sides[0],2)*triangle_sides[2]-
            pow(tetrahedron_sides[0],2)*third_coords[0]+pow(tetrahedron_sides[1],2)*third_coords[0]-
            pow(tetrahedron_sides[2],2)*triangle_sides[2]-pow(triangle_sides[2],2)*third_coords[0]+
            pow(third_coords[0],2)*triangle_sides[2])/2*third_coords[1]*triangle_sides[2];

    tetrahedron_top_coords[2]=sqrt(pow(tetrahedron_sides[0],2)-pow(tetrahedron_top_coords[0],2)-pow(tetrahedron_top_coords[1],2));
// 3D skaiciavimai ////////////
    REAL4 S1, S2, S3;
    S1=particle_coords;
    S2=further_coords;
    S3=third_coords;


    //cout << S1 << " " << S2 << " " << S3  << endl;
            //d^2=sqrt((x0-x1)^2+(y0-y1)^2+(z0-z1)^2)
    REAL4 vector_u, vector_v, vector_w;
    vector_u=(S1-S2)/(sqrt(pow(S1[0]-S2[0],2)+pow(S1[1]-S2[1],2)+pow(S1[2]-S2[2],2)));
    vector_v=(S1-S3)/(sqrt(pow(S1[0]-S3[0],2)+pow(S1[1]-S3[1],2)+pow(S1[2]-S3[2],2)));

    //vector_w=-2*S1;
    //vector_w=S1*-2;
    vector_w=S1*-2;
    //cout << S1 << " " << S1*-2 << endl;
    REAL a, b, c;
    //(√ax2 + ay2 + az2)
    REAL result_calc_a, result_calc_b, result_calc_c_positive, result_calc_c_negative; // rezultatui skaiciuoti skirtos reiksmes alpha beta gamma
    REAL4 vector_t;
    REAL result_calc_d;// papildoma reiksme reikalinga skaiciavimams;
    a=(pow(S2[3],2)-pow(S1[3],2)+pow(S1[0],2)-pow(S2[0],2)+pow(S1[1],2)-pow(S2[1],2)+pow(S1[2],2)-pow(S2[2],2))
            /(2*sqrt(pow(S1[0]-S2[0],2)+pow(S1[1]-S2[1],2)+pow(S1[2]-S2[2],2)));

    b=(pow(S3[3],2)-pow(S1[3],2)+pow(S1[0],2)-pow(S3[0],2)+pow(S1[1],2)-pow(S3[1],2)+pow(S1[2],2)-pow(S3[2],2))
            /(2*sqrt(pow(S1[0]-S3[0],2)+pow(S1[1]-S3[1],2)+pow(S1[2]-S3[2],2)));

    c=pow(S1[3],2)-pow(S1[0],2)-pow(S1[1],2)-pow(S1[2],2);

    //cout << (pow(S3[3],2)-pow(S1[3],2)+pow(S1[0],2)-pow(S3[0],2)+pow(S1[1],2)-pow(S3[1],2)+pow(S1[2],2)-pow(S3[2],2))
         //  / (2*sqrt(pow(S1[0]-S3[0],2)+pow(S1[1]-S3[1],2)+pow(S1[2]-S3[2],2))) << endl;
    //cout << a << " " << b << " " << c  << endl;
    REAL4 Xproduktas=cross_prod(vector_u, vector_v); // skaiciavimams skirto X produkto reiksme
    //cout << Xproduktas << endl;
    vector_t=Xproduktas/sqrt(pow(Xproduktas[0],2)+pow(Xproduktas[1],2)+pow(Xproduktas[2],2));
    //cout << vector_u << " " << vector_v << " " << vector_t << endl;
    //cout << vector_u << " " << vector_v << endl;
    //cout << cross_prod(vector_u, vector_v) << " " <<  Xproduktas << endl;

    //cout << vector_t << endl;
    result_calc_a=(a-b*dot_prod(vector_u, vector_v))/(1-pow(dot_prod(vector_u, vector_v),2));
    result_calc_b=(b-a*dot_prod(vector_u, vector_v))/(1-pow(dot_prod(vector_u, vector_v),2)); //virsuje ir apacioje . produktas tarp vektoriu

    //cout << result_calc_a << " " << result_calc_b << endl;
    //cout <<a-b*dot_prod(vector_u, vector_v)<< " " << 1-pow(dot_prod(vector_u, vector_v),2) << "  " << result_calc_b <<  endl;
    //cout << dot_prod(vector_u, vector_v) << endl;
    result_calc_d=pow(result_calc_a,2)+pow(result_calc_b,2)+2*result_calc_a*result_calc_b*dot_prod(vector_u, vector_v)
            +result_calc_a*dot_prod(vector_u, vector_w)+result_calc_b*dot_prod(vector_v, vector_w)-c;

    //cout << vector_u << " " << vector_w << " " << vector_v << endl;
   //cout << pow(result_calc_a,2)<< "+" << pow(result_calc_b,2) << "+" << 2*result_calc_a*result_calc_b*dot_prod(vector_u, vector_v)
     //   << "+" << result_calc_a<< "*" <<dot_prod(vector_u, vector_w)<< "+" <<result_calc_b*dot_prod(vector_v, vector_w)<< "-" << c << endl;

    //cout << 2<<" " << result_calc_a<<" " << result_calc_b<<" "<<dot_prod(vector_u, vector_v)<< endl;
    //cout << dot_prod(vector_v, vector_t) << endl;

    //cout << result_calc_d << endl;
    result_calc_c_positive=1/2*(-dot_prod(vector_w, vector_t)+sqrt(pow(dot_prod(vector_w,vector_t),2)-4*result_calc_d));
    result_calc_c_negative=1/2*(-dot_prod(vector_w, vector_t)-sqrt(pow(dot_prod(vector_w,vector_t),2)-4*result_calc_d));

    //cout << result_calc_c_negative <<" " << result_calc_c_positive << endl;
   //cout <<pow(dot_prod(vector_w,vector_t),2) << endl;
  // cout << -dot_prod(vector_w, vector_t) << " " <<pow(dot_prod(vector_w,vector_t),2)<< " " << 4*result_calc_d << endl;

    //cout <<result_calc_d<< endl;
    //cout << result_calc_c_positive << " " << result_calc_c_negative << endl;
    result_tetrahedron_coords=result_calc_a*vector_u+result_calc_b*vector_v+result_calc_c_positive*vector_t;
    //cout << result_tetrahedron_coords << endl;
    particle.F.push_back(result_tetrahedron_coords);


}
