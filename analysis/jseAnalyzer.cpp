#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TProfile.h"




int main( int argc, char* argv[] ) {

  if( argc<3 ) {
    std::cout << "Usage: ./jseAnalyzer [productionName] [datasetName]" << std::endl;
    exit(1);
  }

  std::string prodName(argv[1]);
  std::string datasetName(argv[2]);
  

  std::cout << "-> Starting analysis for prod: " << prodName << " dataset: " << datasetName << std::endl;

  TFile* file = TFile::Open( Form("%s/miniTrees/%s.root", prodName.c_str(), datasetName.c_str()) );
  TTree* tree = (TTree*)file->Get("mt2");

  int nvert;
  tree->SetBranchAddress("nVert", &nvert );
  float rho;
  tree->SetBranchAddress("rho", &rho );

  int njet;
  tree->SetBranchAddress("njet", &njet );
  float jet_pt[999];
  tree->SetBranchAddress("jet_pt", jet_pt );
  float jet_eta[999];
  tree->SetBranchAddress("jet_eta", jet_eta );
  float jet_phi[999];
  tree->SetBranchAddress("jet_phi", jet_phi );
  float jet_mass[999];
  tree->SetBranchAddress("jet_mass", jet_mass );
  float jet_rawPt[999];
  tree->SetBranchAddress("jet_rawPt", jet_rawPt );

  int jet_id[999];
  tree->SetBranchAddress("jet_id", jet_id );
  int jet_puId[999];
  tree->SetBranchAddress("jet_puId", jet_puId );

  float jet_chEF[999];
  tree->SetBranchAddress("jet_chEF", jet_chEF );
  float jet_nhEF[999];
  tree->SetBranchAddress("jet_nhEF", jet_nhEF );
  float jet_phEF[999];
  tree->SetBranchAddress("jet_phEF", jet_phEF );
  float jet_elEF[999];
  tree->SetBranchAddress("jet_eEF", jet_elEF );
  float jet_muEF[999];
  tree->SetBranchAddress("jet_muEF", jet_muEF );
  float jet_hfhadEF[999];
  tree->SetBranchAddress("jet_HFHEF", jet_hfhadEF );
  float jet_hfemEF[999];
  tree->SetBranchAddress("jet_HFEMEF", jet_hfemEF );



  system( Form("mkdir -p %s/histoFiles", prodName.c_str()) );

  TFile* outfile = TFile::Open( Form("%s/histoFiles/%s.root", prodName.c_str(), datasetName.c_str()), "RECREATE" );
  outfile->cd();

  TProfile* hp_phEF_vs_eta = new TProfile( "phEF_vs_eta", "", 64, -3.2, 3.2 );


  int nentries = tree->GetEntries();


  for( unsigned iEntry=0; iEntry<nentries; ++iEntry ) {

    tree->GetEntry( iEntry );

    if( iEntry % 100000 == 0 ) std::cout << "  Entry: " << iEntry << " / " << nentries << std::endl;

    for( unsigned ijet=0; ijet<njet; ++ijet ) {

      hp_phEF_vs_eta->Fill( jet_eta[ijet], jet_phEF[ijet] );

    }  // for jets


  } // for entries


  outfile->cd();

  hp_phEF_vs_eta->Write();

  outfile->Close();

  std::cout << "-> Done. Find your stuff in: " << outfile->GetName() << std::endl;
  
  return 0;

}
