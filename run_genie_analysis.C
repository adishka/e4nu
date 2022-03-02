#ifndef rungenieanalysis
#define rungenieanalysis
#include "genie_analysis.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{


  if( argc < 3 ){
    std::cout<<"Please specify the target (3He, 56Fe, C12, 4He), the beam energy (1161, 2261, 4461),"<< endl;
    std::cout << " the data type (CLAS data = 0, simulation = 1) "<<std::endl;
    std::cout<<"================= Usage ==============="<<std::endl;
    std::cout<<"./genie_analysis target beam_energy 0/1"<<std::endl;
    exit(1);
  }


  std::string target  = argv[1];
  std::string beam_en = argv[2];

  genie_analysis  t(target,beam_en);
  t.Loop();


  return 0;
}
#endif
