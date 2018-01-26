#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"




int main( int argc, char* argv[] ) {

  if( argc<2 ) {
    std::cout << "Usage: ./jseMiniTree [productionName]" << std::endl;
    exit(1);
  }

  std::string prodName(argv[1]);

  std::string path("/eos/cms/store/user/pandolf/JetStudiesECAL/94X/");

  std::vector< std::string > datasets;
  datasets.push_back( "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON_noPU" );

  TChain* chain = new TChain("mt2");

  for( unsigned iDataset=0; iDataset<datasets.size(); ++iDataset ) {

    std::cout << "-> Starting: " << datasets[iDataset] << std::endl;

    for( unsigned iChunk=0; iChunk<26; ++iChunk ) {

      std::string chunkName( Form( "%s/%s/%s_Chunk%d/mt2.root/mt2", path.c_str(), prodName.c_str(), datasets[iDataset].c_str(), iChunk) );
      std::cout << "   Adding: " << chunkName << std::endl;

      chain->Add( chunkName.c_str() );

    } // for chunks

    std::string outdir( Form("%s/miniTrees", prodName.c_str()) );
    system( Form("mkdir -p %s", outdir.c_str()) );

    TFile* outfile = TFile::Open( Form("%s/%s.root", outdir.c_str(), datasets[iDataset].c_str()), "RECREATE" );
    outfile->cd();

    TTree* tree = new TTree("jseMini", "");

    int nvert;
    tree->Branch("nvert", &nvert, "nvert/I");

    int njet;
    tree->Branch("njet", &njet, "njet/I");
    float jet_pt[999];
    tree->Branch("jet_pt", jet_pt, "jet_pt[njet]/F");

    
    int nentries = chain->GetEntries();
    nentries = 1000;

    std::cout << "   Starting loop on entries." << std::endl;

    for( unsigned iEntry=0; iEntry<nentries; ++iEntry) {

      chain->GetEntry(iEntry);

      if( iEntry % 20000 == 0 ) std::cout << "   Entry: " << iEntry << " / " << nentries << std::endl;

      njet = 1;
      jet_pt[0] = 95.;

      tree->Fill();
 
    }  // for entries

    outfile->cd();
    tree->Write();
    outfile->Close();

  } // for datasets

  return 0;

}
