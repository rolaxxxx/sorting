#include "includes.h"
#include "skirstinys.h"
#include "dalele.h"
#include "mapaddandparticlesearch.h"
#include "map_bounds.h"
#include "coordinate_math.h"
int main(int, char *[])
{
    Dalele particle;
    Skirstinys geometrija;
    MAP_BOUNDS boundai;
    MapAddAndParticleSearch gridas;
    coordinate_math kordinaciu_skaiciavimas;

    boundai.MAP_DUOMENYS();
    REAL4 dalele1, dalele2, dalele3;
    vector<REAL4> temp_F;
    INT rand_particle_index;
    dalele1={0.5,0.3,0.2,1};
    dalele2={1.75,1.599,-0.666,1};
    dalele3={0.375,2.24856,0.633012,1};



    gridas.GRIDAS_MAP_ADD(dalele1, boundai);
   kordinaciu_skaiciavimas.add_cell(particle, dalele1, geometrija.NextSpindulys());
    gridas.GRIDAS_MAP_ADD(dalele2, boundai);
   kordinaciu_skaiciavimas.add_cell(particle, dalele2, geometrija.NextSpindulys());
    gridas.GRIDAS_MAP_ADD(dalele3, boundai);
    kordinaciu_skaiciavimas.add_cell(particle, dalele3, geometrija.NextSpindulys());

    particle.V=particle.F;

    vector<INT> rand_daleles_kaimynai; // random daleles kaimynai kuriuos po tris tikrinsiu ir desiu dalele
    vector<REAL4> group;
    REAL4 tempdal, temporcords;
    vector<REAL4> calculated_neighbor_spot;
    INT IDX;
    map<INT, vector<INT>>::iterator it;
    for(INT i=0;i<10;i++){

        rand_particle_index=rand()%particle.F.size();
            rand_daleles_kaimynai=gridas.MAP_NEIGHBOR_SEARCH(particle, rand_particle_index, boundai);

            for(INT j=0;j<rand_daleles_kaimynai.size();j++){

                //cout << rand_daleles_kaimynai[j] <<" "<<rand_particle_index<<  endl;
                if(j+1<rand_daleles_kaimynai.size()){

                group.push_back(particle.F[rand_daleles_kaimynai[j]]);
                group.push_back(particle.F[rand_daleles_kaimynai[j+1]]);
                group.push_back(particle.F[rand_particle_index]);
                //cout << group[j] << " " << group[j+1] << "  " << group[rand_particle_index] << endl;
                //cout << rand_daleles_kaimynai[j] << endl;
                calculated_neighbor_spot=kordinaciu_skaiciavimas.coordinate_math_(group, 1);
                //cout << calculated_neighbor_spot[0] << " " << calculated_neighbor_spot[1] << endl;
                if(gridas.NEIGHBOR_SEARCH(particle, rand_daleles_kaimynai, calculated_neighbor_spot[0], boundai)){
                    if(gridas.NEIGHBOR_SEARCH(particle, rand_daleles_kaimynai, calculated_neighbor_spot[1], boundai)){
                        particle.F.erase(particle.F.begin()+rand_particle_index);
                    }
                    else{
                        gridas.GRIDAS_MAP_ADD(calculated_neighbor_spot[1],boundai);
                        //cout << particle.F.size() << endl;
                        particle.F.push_back(calculated_neighbor_spot[1]);
                        //cout << "size pries sulyginima " << particle.V.size() << endl;
                        particle.V=particle.F;
                        //cout << "size po sulyginimo  " << particle.V.size() << endl;


                    }
                }
                else{
                    gridas.GRIDAS_MAP_ADD(calculated_neighbor_spot[0], boundai);
                    particle.F.push_back(calculated_neighbor_spot[0]);
                    particle.V=particle.F;
                }
              }
}
                rand_daleles_kaimynai.erase(rand_daleles_kaimynai.begin(), rand_daleles_kaimynai.end());
        particle.particle_Generator( boundai);
        group.erase(group.begin(), group.end());


    }

        }






