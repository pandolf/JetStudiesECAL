#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

#include "../interface/jseDataset.h"



void drawProfileVsEta( const std::string& outdir, const std::string& varName, float ptMin, float ptMax, std::vector< jseDataset* > datasets );


int main( int argc, char* argv[] ) {

  
  if( argc<2 ) {
    std::cout << "Usage: ./jseDrawStuff [productionName]" << std::endl;
    exit(1);
  }

  std::string prodName(argv[1]);

  std::string outdir( Form("%s/plots/", prodName.c_str()) );

  system( Form("mkdir -p %s", outdir.c_str()) );

  //RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF
  //RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF_noPU
  //RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SRON
  //RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF
  //RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF_noPU
  std::vector< jseDataset* > datasets;
  datasets.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON" , "GRv2 SR@PF:ON"  ) );
  datasets.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF", "GRv2 SR@PF:OFF" ) );

  std::vector<float> ptBins;
  ptBins.push_back( 20. );
  ptBins.push_back( 25. );
  ptBins.push_back( 30. );
  ptBins.push_back( 40. );
  ptBins.push_back( 55. );
  ptBins.push_back( 80. );
  ptBins.push_back( 100. );
  ptBins.push_back( 140. );
  ptBins.push_back( 200. );
  ptBins.push_back( 300. );

  for( unsigned iPt=0; iPt<ptBins.size()-1; ++iPt ) {
    drawProfileVsEta( outdir, "jet_phEF", ptBins[iPt], ptBins[iPt+1], datasets );
  }

  return 0;

}


void drawProfileVsEta( const std::string& outdir, const std::string& varName, float ptMin, float ptMax, std::vector< jseDataset* > datasets ) {

  


}
