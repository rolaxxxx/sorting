#include "includes.h"
#include "geometry.h"
#include "dalele.h"
#include "grid_count.h"
#include "map_bounds.h"
#include "coordinate_math.h"
int main(int, char *[])
{
    Dalele particle;
    Geometry geometrija;
    MAP_BOUNDS boundai;
    GRID_COUNT gridas;
    coordinate_math kordinaciu_skaiciavimas;

    boundai.MAP_DUOMENYS();
    geometrija.skirstinioFormavimas();
    REAL4 dalele1, dalele2, dalele3;
    vector<REAL4> temp_F;
    INT rand_cell_index;
    dalele1={0.5,0.3,0.2,1};
    dalele2={1.75,1.599,-0.666,1};
    dalele3={0.375,2.24856,0.633012,1};



    gridas.GRIDAS_MAP_ADD(dalele1, boundai);
    kordinaciu_skaiciavimas.add_cell(particle, dalele1, geometrija.getDistribution());
    gridas.GRIDAS_MAP_ADD(dalele2, boundai);
    kordinaciu_skaiciavimas.add_cell(particle, dalele2, geometrija.getDistribution());
    gridas.GRIDAS_MAP_ADD(dalele3, boundai);
    //cout << gridas.getSUFORMUOTAS_GRIDAS().size() << endl;
    kordinaciu_skaiciavimas.add_cell(particle, dalele3, geometrija.getDistribution());
    particle.setV(particle.getF());



    vector<INT> rand_daleles_kaimynai; // random daleles kaimynai kuriuos po tris tikrinsiu ir desiu dalele
    vector<REAL4> group;
    vector<REAL4> calculated_neighbor_spot;
    for(INT i=0;i<10;i++){
        temp_F=particle.getF();
        rand_cell_index=rand()%temp_F.size();
        //cout << rand_cell_index << endl;

        rand_daleles_kaimynai=gridas.MAP_NEIGHBOR_SEARCH(temp_F, rand_cell_index, boundai);

        //cout << "________________" << endl;
        //cout << rand_daleles_kaimynai.size() << endl;

        for(INT j=0;j<rand_daleles_kaimynai.size();j+=2){

            //cout << rand_daleles_kaimynai.size() << endl;
            group.push_back(temp_F[rand_daleles_kaimynai[j]]);
            group.push_back(temp_F[rand_daleles_kaimynai[j+1]]);
            group.push_back(temp_F[rand_cell_index]);
            //cout << rand_daleles_kaimynai[j] << endl;
            calculated_neighbor_spot=kordinaciu_skaiciavimas.coordinate_math_(group, 1);
            //cout << calculated_neighbor_spot[0] << " " << calculated_neighbor_spot[1] << endl;
            if(gridas.NEIGHBOR_SEARCH(particle.getF(), rand_daleles_kaimynai, calculated_neighbor_spot[0], boundai)){
                if(gridas.NEIGHBOR_SEARCH(particle.getF(), rand_daleles_kaimynai, calculated_neighbor_spot[1], boundai)){
                    temp_F.erase(temp_F.begin()+rand_cell_index);
                    particle.setF(temp_F);
                }
                else{
                    gridas.GRIDAS_MAP_ADD(calculated_neighbor_spot[1],boundai);
                    temp_F.push_back(calculated_neighbor_spot[1]);
                    particle.setF(temp_F);
                    particle.setV(temp_F);
                }
            }
            else{
                gridas.GRIDAS_MAP_ADD(calculated_neighbor_spot[0], boundai);
                temp_F.push_back(calculated_neighbor_spot[0]);
                particle.setF(temp_F);
                particle.setV(temp_F);
            }


            }

   // particle.particle_Generator(geometrija.getDistribution(), boundai);
}


        }






