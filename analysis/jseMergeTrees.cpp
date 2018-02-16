#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"




int main( int argc, char* argv[] ) {

  if( argc<4 ) {
    std::cout << "Usage: ./jseMergeTrees [version] [productionName] [datasetName]" << std::endl;
    exit(1);
  }

  std::string cmsswVersion(argv[1]);
  std::string prodName(argv[2]);
  std::string datasetName(argv[3]);

  std::string path("/eos/cms/store/group/phys_higgs/pandolf/JetStudiesECAL/");
  //std::string path("/eos/cms/store/user/pandolf/JetStudiesECAL/");


  TChain* chain = new TChain("mt2");


  std::cout << "-> Starting: " << datasetName << std::endl;

  //chain->Add( Form( "%s/%s/%s_Chunk*/mt2.root/mt2", path.c_str(), prodName.c_str(), datasets[iDataset].c_str()) );
  for( unsigned iChunk=0; iChunk<26; ++iChunk ) {

    std::string chunkName( Form( "%s/%s/%s/%s_Chunk%d/mt2.root/mt2", path.c_str(), cmsswVersion.c_str(), prodName.c_str(), datasetName.c_str(), iChunk) );
    std::cout << "   Adding: " << chunkName << std::endl;

    chain->Add( chunkName.c_str() );

  } // for chunks

  std::cout << "   Added chunks. Total entries: " << chain->GetEntries() << std::endl;

  chain->SetBranchStatus("*"         , 0);
  chain->SetBranchStatus("nVert"     , 1);
  chain->SetBranchStatus("rho"       , 1);

  chain->SetBranchStatus("njet"      , 1);
  chain->SetBranchStatus("jet_pt"    , 1);
  chain->SetBranchStatus("jet_eta"   , 1);
  chain->SetBranchStatus("jet_phi"   , 1);
  chain->SetBranchStatus("jet_mass"  , 1);
  chain->SetBranchStatus("jet_rawPt" , 1);
  chain->SetBranchStatus("jet_mcPt"  , 1);
  chain->SetBranchStatus("jet_id"    , 1);
  chain->SetBranchStatus("jet_puId"  , 1);

  chain->SetBranchStatus("jet_chHEF" , 1);
  chain->SetBranchStatus("jet_neHEF" , 1);
  chain->SetBranchStatus("jet_phEF"  , 1);
  chain->SetBranchStatus("jet_eEF"   , 1);
  chain->SetBranchStatus("jet_muEF"  , 1);
  chain->SetBranchStatus("jet_HFHEF" , 1);
  chain->SetBranchStatus("jet_HFEMEF", 1);


  std::string outdir( Form("%s/miniTrees", prodName.c_str()) );
  system( Form("mkdir -p %s", outdir.c_str()) );

  std::string outfileName( Form("%s/%s.root", outdir.c_str(), datasetName.c_str()));
  TFile* outfile = TFile::Open( outfileName.c_str(), "RECREATE" );
  outfile->cd();

  std::cout << "   Merging..." << std::endl;
  TTree* tree = chain->CloneTree();

  outfile->cd();
  tree->Write();
  outfile->Close();

  std::cout << "   Written merged chunks in: " << outfileName.c_str() << std::endl;


  return 0;

}
