#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TProfile.h"

#include "../interface/jseCommon.h"



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

  int nVert;
  tree->SetBranchAddress("nVert", &nVert );
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
  float jet_mcPt[999];
  tree->SetBranchAddress("jet_mcPt", jet_mcPt );

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

  TH1D* h1_nVertex = new TH1D( "nVertex", "", 51, -0.5, 50.5); 
  TH1D* h1_rho     = new TH1D( "rho", "", 20, 0., 20.); 

  float etaMax = 3.2;
  int nBins_eta = 64;

  TProfile* hp_chEF_vs_eta    = new TProfile( "chEF_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_nhEF_vs_eta    = new TProfile( "nhEF_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_phEF_vs_eta    = new TProfile( "phEF_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_elEF_vs_eta    = new TProfile( "elEF_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_muEF_vs_eta    = new TProfile( "muEF_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfhadEF_vs_eta = new TProfile( "hfhadEF_vs_eta", "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfemEF_vs_eta  = new TProfile( "hfemEF_vs_eta" , "", nBins_eta, -etaMax, etaMax );


  std::vector<float> ptBins  = jseCommon::ptBins();
  std::vector<float> etaBins = jseCommon::etaBins();

  std::map< std::string, TH1D* > map_resp, map_respRaw;

  for(unsigned iPt=0; iPt<ptBins.size()-1; ++iPt) {

    for(unsigned iEta=0; iEta<etaBins.size()-1; ++iEta) {

      std::string thisHistoName( jseCommon::getPtEtaHistoName( "resp", iPt, iEta ) ); 
      TH1D* h1_thisResponse = new TH1D( thisHistoName.c_str(), "", 100, 0., 2. );
      map_resp[thisHistoName] = h1_thisResponse;

      std::string thisHistoNameRaw( jseCommon::getPtEtaHistoName( "respRaw", iPt, iEta ) ); 
      TH1D* h1_thisResponseRaw = new TH1D( thisHistoNameRaw.c_str(), "", 100, 0., 2. );
      map_respRaw[thisHistoNameRaw] = h1_thisResponseRaw;

    } // for eta

  } // for pt



  int nentries = tree->GetEntries();


  for( unsigned iEntry=0; iEntry<nentries; ++iEntry ) {

    tree->GetEntry( iEntry );

    if( iEntry % 100000 == 0 ) std::cout << "  Entry: " << iEntry << " / " << nentries << std::endl;

    h1_nVertex->Fill( nVert );
    h1_rho->Fill( rho );

    for( unsigned ijet=0; ijet<njet; ++ijet ) {

      hp_chEF_vs_eta   ->Fill( jet_eta[ijet], jet_chEF[ijet]    );
      hp_nhEF_vs_eta   ->Fill( jet_eta[ijet], jet_nhEF[ijet]    );
      hp_phEF_vs_eta   ->Fill( jet_eta[ijet], jet_phEF[ijet]    );
      hp_elEF_vs_eta   ->Fill( jet_eta[ijet], jet_elEF[ijet]    );
      hp_muEF_vs_eta   ->Fill( jet_eta[ijet], jet_muEF[ijet]    );
      hp_hfhadEF_vs_eta->Fill( jet_eta[ijet], jet_hfhadEF[ijet] );
      hp_hfemEF_vs_eta ->Fill( jet_eta[ijet], jet_hfemEF[ijet]  );


      std::string histoName = jseCommon::findHistoName( "resp", jet_pt[ijet], jet_eta[ijet] );
      if( map_resp.find(histoName) != map_resp.end() )
        map_resp[histoName]->Fill( jet_pt[ijet]/jet_mcPt[ijet] );

      std::string histoNameRaw = jseCommon::findHistoName( "respRaw", jet_pt[ijet], jet_eta[ijet] );
      if( map_respRaw.find(histoNameRaw) != map_respRaw.end() )
        map_respRaw[histoNameRaw]->Fill( jet_rawPt[ijet]/jet_mcPt[ijet] );


    }  // for jets

  } // for entries


  outfile->cd();

  h1_nVertex->Write();
  h1_rho->Write();

  hp_chEF_vs_eta   ->Write();
  hp_nhEF_vs_eta   ->Write();
  hp_phEF_vs_eta   ->Write();
  hp_elEF_vs_eta   ->Write();
  hp_muEF_vs_eta   ->Write();
  hp_hfhadEF_vs_eta->Write();
  hp_hfemEF_vs_eta ->Write();

  for( std::map<std::string,TH1D*>::const_iterator iresp=map_resp.begin(); iresp!=map_resp.end(); ++iresp )
    iresp->second->Write();

  for( std::map<std::string,TH1D*>::const_iterator iresp=map_respRaw.begin(); iresp!=map_respRaw.end(); ++iresp )
    iresp->second->Write();

  outfile->Close();

  std::cout << "-> Done. Find your stuff in: " << outfile->GetName() << std::endl;
  
  return 0;

}
