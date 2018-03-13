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
  tree->SetBranchAddress("jet_chHEF", jet_chEF );
  float jet_nhEF[999];
  tree->SetBranchAddress("jet_neHEF", jet_nhEF );
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

  int jet_chMult[999];
  tree->SetBranchAddress("jet_chHMult", jet_chMult );
  int jet_nhMult[999];
  tree->SetBranchAddress("jet_neHMult", jet_nhMult );
  int jet_phMult[999];
  tree->SetBranchAddress("jet_phMult", jet_phMult );
  int jet_elMult[999];
  tree->SetBranchAddress("jet_eMult", jet_elMult );
  int jet_muMult[999];
  tree->SetBranchAddress("jet_muMult", jet_muMult );
  int jet_hfhadMult[999];
  tree->SetBranchAddress("jet_HFHMult", jet_hfhadMult );
  int jet_hfemMult[999];
  tree->SetBranchAddress("jet_HFEMMult", jet_hfemMult );



  system( Form("mkdir -p %s/histoFiles", prodName.c_str()) );

  TFile* outfile = TFile::Open( Form("%s/histoFiles/%s.root", prodName.c_str(), datasetName.c_str()), "RECREATE" );
  outfile->cd();

  TH1D* h1_nVertex = new TH1D( "nVertex", "", 51, -0.5, 50.5); 
  TH1D* h1_rho     = new TH1D( "rho", "", 100, 0., 100.); 


  TH1D* h1_pt  = new TH1D( "pt" , "", 100, 0., 500. );
  TH1D* h1_eta = new TH1D( "eta", "", 100, -5., 5. );


  float etaMax = 3.2;
  int nBins_eta = 64;

  TProfile* hp_chEF_vs_eta      = new TProfile( "chEF_vs_eta"     , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_nhEF_vs_eta      = new TProfile( "nhEF_vs_eta"     , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_phEF_vs_eta      = new TProfile( "phEF_vs_eta"     , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_elEF_vs_eta      = new TProfile( "elEF_vs_eta"     , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_muEF_vs_eta      = new TProfile( "muEF_vs_eta"     , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfhadEF_vs_eta   = new TProfile( "hfhadEF_vs_eta"  , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfemEF_vs_eta    = new TProfile( "hfemEF_vs_eta"   , "", nBins_eta, -etaMax, etaMax );

  TProfile* hp_chE_vs_eta       = new TProfile( "chE_vs_eta"      , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_nhE_vs_eta       = new TProfile( "nhE_vs_eta"      , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_phE_vs_eta       = new TProfile( "phE_vs_eta"      , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_elE_vs_eta       = new TProfile( "elE_vs_eta"      , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_muE_vs_eta       = new TProfile( "muE_vs_eta"      , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfhadE_vs_eta    = new TProfile( "hfhadE_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfemE_vs_eta     = new TProfile( "hfemE_vs_eta"    , "", nBins_eta, -etaMax, etaMax );

  TProfile* hp_chMult_vs_eta    = new TProfile( "chMult_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_nhMult_vs_eta    = new TProfile( "nhMult_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_phMult_vs_eta    = new TProfile( "phMult_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_elMult_vs_eta    = new TProfile( "elMult_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_muMult_vs_eta    = new TProfile( "muMult_vs_eta"   , "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfhadMult_vs_eta = new TProfile( "hfhadMult_vs_eta", "", nBins_eta, -etaMax, etaMax );
  TProfile* hp_hfemMult_vs_eta  = new TProfile( "hfemMult_vs_eta" , "", nBins_eta, -etaMax, etaMax );


  std::vector<float> ptBins  = jseCommon::ptBins();
  std::vector<float> etaBins = jseCommon::etaBins();
  std::vector<float> phiBins = jseCommon::phiBins();

  std::map< std::string, TH1D* > map_resp , map_respRaw;
  //std::map< std::string, TH1D* > map2_resp, map2_respRaw;

  std::vector< TProfile* > vhp_chEF_vs_eta;
  std::vector< TProfile* > vhp_nhEF_vs_eta;
  std::vector< TProfile* > vhp_phEF_vs_eta;
  //std::vector< TProfile* > vhp_elEF_vs_eta;
  //std::vector< TProfile* > vhp_muEF_vs_eta;
  //std::vector< TProfile* > vhp_hfhadEF_vs_eta;
  //std::vector< TProfile* > vhp_hfemEF_vs_eta;

  std::vector< TProfile* > vhp_chE_vs_eta;
  std::vector< TProfile* > vhp_nhE_vs_eta;
  std::vector< TProfile* > vhp_phE_vs_eta;
  //std::vector< TProfile* > vhp_elE_vs_eta;
  //std::vector< TProfile* > vhp_muE_vs_eta;
  //std::vector< TProfile* > vhp_hfhadE_vs_eta;
  //std::vector< TProfile* > vhp_hfemE_vs_eta;

  std::vector< TProfile* > vhp_chMult_vs_eta;
  std::vector< TProfile* > vhp_nhMult_vs_eta;
  std::vector< TProfile* > vhp_phMult_vs_eta;
  //std::vector< TProfile* > vhp_elMult_vs_eta;
  //std::vector< TProfile* > vhp_muMult_vs_eta;
  //std::vector< TProfile* > vhp_hfhadMult_vs_eta;
  //std::vector< TProfile* > vhp_hfemMult_vs_eta;


  for(unsigned iPt=0; iPt<ptBins.size()-1; ++iPt) {

    TProfile* new_profile_chEF = new TProfile( jseCommon::getProfileVsEtaName( "chEF", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_chEF_vs_eta.push_back( new_profile_chEF );

    TProfile* new_profile_phEF = new TProfile( jseCommon::getProfileVsEtaName( "phEF", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_phEF_vs_eta.push_back( new_profile_phEF );

    TProfile* new_profile_nhEF = new TProfile( jseCommon::getProfileVsEtaName( "nhEF", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_nhEF_vs_eta.push_back( new_profile_nhEF );



    TProfile* new_profile_chE = new TProfile( jseCommon::getProfileVsEtaName( "chE", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_chE_vs_eta.push_back( new_profile_chE );

    TProfile* new_profile_phE = new TProfile( jseCommon::getProfileVsEtaName( "phE", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_phE_vs_eta.push_back( new_profile_phE );

    TProfile* new_profile_nhE = new TProfile( jseCommon::getProfileVsEtaName( "nhE", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_nhE_vs_eta.push_back( new_profile_nhE );



    TProfile* new_profile_chMult = new TProfile( jseCommon::getProfileVsEtaName( "chMult", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_chMult_vs_eta.push_back( new_profile_chMult );

    TProfile* new_profile_phMult = new TProfile( jseCommon::getProfileVsEtaName( "phMult", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_phMult_vs_eta.push_back( new_profile_phMult );

    TProfile* new_profile_nhMult = new TProfile( jseCommon::getProfileVsEtaName( "nhMult", iPt ).c_str(), "", nBins_eta, -etaMax, etaMax );
    vhp_nhMult_vs_eta.push_back( new_profile_nhMult );



    for(unsigned iEta=0; iEta<etaBins.size()-1; ++iEta) {

      std::string thisHistoName( jseCommon::getHistoName( "resp", iPt, iEta ) ); 
      TH1D* h1_thisResponse = new TH1D( thisHistoName.c_str(), "", 100, 0., 2. );
      map_resp[thisHistoName] = h1_thisResponse;

      std::string thisHistoNameRaw( jseCommon::getHistoName( "respRaw", iPt, iEta ) ); 
      TH1D* h1_thisResponseRaw = new TH1D( thisHistoNameRaw.c_str(), "", 100, 0., 2. );
      map_respRaw[thisHistoNameRaw] = h1_thisResponseRaw;

      //for( unsigned iPhi=0; iPhi<phiBins.size()-1; ++iPhi ) {

      //  std::string thisHistoNamePhi( jseCommon::getHistoName( "resp", iPt, iEta, iPhi ) ); 
      //  TH1D* h1_thisResponsePhi = new TH1D( thisHistoNamePhi.c_str(), "", 100, 0., 2. );
      //  map2_resp[thisHistoNamePhi] = h1_thisResponsePhi;

      //  std::string thisHistoNameRawPhi( jseCommon::getHistoName( "respRaw", iPt, iEta, iPhi ) ); 
      //  TH1D* h1_thisResponseRawPhi = new TH1D( thisHistoNameRawPhi.c_str(), "", 100, 0., 2. );
      //  map2_respRaw[thisHistoNameRawPhi] = h1_thisResponseRawPhi;

      //} // for phi

    } // for eta

  } // for pt



  int nentries = tree->GetEntries();


  for( unsigned iEntry=0; iEntry<nentries; ++iEntry ) {

    tree->GetEntry( iEntry );

    if( iEntry % 100000 == 0 ) std::cout << "  Entry: " << iEntry << " / " << nentries << std::endl;

    h1_nVertex->Fill( nVert );
    h1_rho->Fill( rho );

    for( unsigned ijet=0; ijet<njet; ++ijet ) {

      h1_pt ->Fill( jet_pt [ijet] );
      h1_eta->Fill( jet_eta[ijet] );

      hp_chEF_vs_eta     ->Fill( jet_eta[ijet], jet_chEF[ijet]    );
      hp_nhEF_vs_eta     ->Fill( jet_eta[ijet], jet_nhEF[ijet]    );
      hp_phEF_vs_eta     ->Fill( jet_eta[ijet], jet_phEF[ijet]    );
      hp_elEF_vs_eta     ->Fill( jet_eta[ijet], jet_elEF[ijet]    );
      hp_muEF_vs_eta     ->Fill( jet_eta[ijet], jet_muEF[ijet]    );
      hp_hfhadEF_vs_eta  ->Fill( jet_eta[ijet], jet_hfhadEF[ijet] );
      hp_hfemEF_vs_eta   ->Fill( jet_eta[ijet], jet_hfemEF[ijet]  );

      hp_chE_vs_eta      ->Fill( jet_eta[ijet], jet_chEF[ijet]    * jet_pt[ijet] );
      hp_nhE_vs_eta      ->Fill( jet_eta[ijet], jet_nhEF[ijet]    * jet_pt[ijet] );
      hp_phE_vs_eta      ->Fill( jet_eta[ijet], jet_phEF[ijet]    * jet_pt[ijet] );
      hp_elE_vs_eta      ->Fill( jet_eta[ijet], jet_elEF[ijet]    * jet_pt[ijet] );
      hp_muE_vs_eta      ->Fill( jet_eta[ijet], jet_muEF[ijet]    * jet_pt[ijet] );
      hp_hfhadE_vs_eta   ->Fill( jet_eta[ijet], jet_hfhadEF[ijet] * jet_pt[ijet] );
      hp_hfemE_vs_eta    ->Fill( jet_eta[ijet], jet_hfemEF[ijet]  * jet_pt[ijet] );

      hp_chMult_vs_eta   ->Fill( jet_eta[ijet], jet_chMult[ijet]    );
      hp_nhMult_vs_eta   ->Fill( jet_eta[ijet], jet_nhMult[ijet]    );
      hp_phMult_vs_eta   ->Fill( jet_eta[ijet], jet_phMult[ijet]    );
      hp_elMult_vs_eta   ->Fill( jet_eta[ijet], jet_elMult[ijet]    );
      hp_muMult_vs_eta   ->Fill( jet_eta[ijet], jet_muMult[ijet]    );
      hp_hfhadMult_vs_eta->Fill( jet_eta[ijet], jet_hfhadMult[ijet] );
      hp_hfemMult_vs_eta ->Fill( jet_eta[ijet], jet_hfemMult[ijet]  );


      int iPt = jseCommon::findBin( jet_pt[ijet], ptBins );
      
      if( iPt>=0 ) {

        vhp_chEF_vs_eta  [iPt]->Fill( jet_eta[ijet], jet_chEF[ijet]   );
        vhp_phEF_vs_eta  [iPt]->Fill( jet_eta[ijet], jet_phEF[ijet]   );
        vhp_nhEF_vs_eta  [iPt]->Fill( jet_eta[ijet], jet_nhEF[ijet]   );

        vhp_chE_vs_eta   [iPt]->Fill( jet_eta[ijet], jet_chEF[ijet] * jet_pt[ijet] );
        vhp_phE_vs_eta   [iPt]->Fill( jet_eta[ijet], jet_phEF[ijet] * jet_pt[ijet] );
        vhp_nhE_vs_eta   [iPt]->Fill( jet_eta[ijet], jet_nhEF[ijet] * jet_pt[ijet] );

        vhp_chMult_vs_eta[iPt]->Fill( jet_eta[ijet], jet_chMult[ijet] );
        vhp_phMult_vs_eta[iPt]->Fill( jet_eta[ijet], jet_phMult[ijet] );
        vhp_nhMult_vs_eta[iPt]->Fill( jet_eta[ijet], jet_nhMult[ijet] );

      }


      std::string histoName = jseCommon::findHistoName( "resp", jet_pt[ijet], jet_eta[ijet] );
      if( map_resp.find(histoName) != map_resp.end() )
        map_resp[histoName]->Fill( jet_pt[ijet]/jet_mcPt[ijet] );

      std::string histoNameRaw = jseCommon::findHistoName( "respRaw", jet_pt[ijet], jet_eta[ijet] );
      if( map_respRaw.find(histoNameRaw) != map_respRaw.end() )
        map_respRaw[histoNameRaw]->Fill( jet_rawPt[ijet]/jet_mcPt[ijet] );

      //std::string histoNamePhi = jseCommon::findHistoName( "resp", jet_pt[ijet], jet_eta[ijet], jet_phi[ijet] );
      //if( map2_resp.find(histoNamePhi) != map2_resp.end() )
      //  map2_resp[histoNamePhi]->Fill( jet_pt[ijet]/jet_mcPt[ijet] );

      //std::string histoNameRawPhi = jseCommon::findHistoName( "respRaw", jet_pt[ijet], jet_eta[ijet], jet_phi[ijet] );
      //if( map2_respRaw.find(histoNameRawPhi) != map2_respRaw.end() )
      //  map2_respRaw[histoNameRawPhi]->Fill( jet_rawPt[ijet]/jet_mcPt[ijet] );


    }  // for jets

  } // for entries


  outfile->cd();

  h1_nVertex->Write();
  h1_rho->Write();

  h1_pt ->Write();
  h1_eta->Write();

  hp_chEF_vs_eta     ->Write();
  hp_nhEF_vs_eta     ->Write();
  hp_phEF_vs_eta     ->Write();
  hp_elEF_vs_eta     ->Write();
  hp_muEF_vs_eta     ->Write();
  hp_hfhadEF_vs_eta  ->Write();
  hp_hfemEF_vs_eta   ->Write();

  hp_chE_vs_eta      ->Write();
  hp_nhE_vs_eta      ->Write();
  hp_phE_vs_eta      ->Write();
  hp_elE_vs_eta      ->Write();
  hp_muE_vs_eta      ->Write();
  hp_hfhadE_vs_eta   ->Write();
  hp_hfemE_vs_eta    ->Write();

  hp_chMult_vs_eta   ->Write();
  hp_nhMult_vs_eta   ->Write();
  hp_phMult_vs_eta   ->Write();
  hp_elMult_vs_eta   ->Write();
  hp_muMult_vs_eta   ->Write();
  hp_hfhadMult_vs_eta->Write();
  hp_hfemMult_vs_eta ->Write();


  for( unsigned iPt=0; iPt<ptBins.size()-1; ++iPt ) {

    vhp_chEF_vs_eta  [iPt]->Write();
    vhp_phEF_vs_eta  [iPt]->Write();
    vhp_nhEF_vs_eta  [iPt]->Write();

    vhp_chE_vs_eta   [iPt]->Write();
    vhp_phE_vs_eta   [iPt]->Write();
    vhp_nhE_vs_eta   [iPt]->Write();

    vhp_chMult_vs_eta[iPt]->Write();
    vhp_phMult_vs_eta[iPt]->Write();
    vhp_nhMult_vs_eta[iPt]->Write();

  }


  for( std::map<std::string,TH1D*>::const_iterator iresp=map_resp.begin(); iresp!=map_resp.end(); ++iresp )
    iresp->second->Write();

  for( std::map<std::string,TH1D*>::const_iterator iresp=map_respRaw.begin(); iresp!=map_respRaw.end(); ++iresp )
    iresp->second->Write();

  //for( std::map<std::string,TH1D*>::const_iterator iresp=map2_resp.begin(); iresp!=map2_resp.end(); ++iresp )
  //  iresp->second->Write();

  //for( std::map<std::string,TH1D*>::const_iterator iresp=map2_respRaw.begin(); iresp!=map2_respRaw.end(); ++iresp )
  //  iresp->second->Write();

  outfile->Close();

  std::cout << "-> Done. Find your stuff in: " << outfile->GetName() << std::endl;
  
  return 0;

}
