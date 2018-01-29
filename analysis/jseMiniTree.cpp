#include <iostream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"




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

  int nvert0;
  chain->SetBranchAddress("nVert", &nvert0 );
  float rho0;
  chain->SetBranchAddress("rho", &rho0 );

  int njet0;
  chain->SetBranchAddress("njet", &njet0 );
  float jet0_pt[999];
  chain->SetBranchAddress("jet_pt", jet0_pt );
  float jet0_eta[999];
  chain->SetBranchAddress("jet_eta", jet0_eta );
  float jet0_phi[999];
  chain->SetBranchAddress("jet_phi", jet0_phi );
  float jet0_mass[999];
  chain->SetBranchAddress("jet_mass", jet0_mass );
  float jet0_rawPt[999];
  chain->SetBranchAddress("jet_rawPt", jet0_rawPt );

  int jet0_id[999];
  chain->SetBranchAddress("jet0_id", jet0_id );
  int jet0_puId[999];
  chain->SetBranchAddress("jet0_puId", jet0_puId );

  float jet0_chEF[999];
  chain->SetBranchAddress("jet_chEF", jet0_chEF );
  float jet0_nhEF[999];
  chain->SetBranchAddress("jet_nhEF", jet0_nhEF );
  float jet0_phEF[999];
  chain->SetBranchAddress("jet_phEF", jet0_phEF );
  float jet0_elEF[999];
  chain->SetBranchAddress("jet_eEF", jet0_elEF );
  float jet0_muEF[999];
  chain->SetBranchAddress("jet_muEF", jet0_muEF );
  float jet0_hfhadEF[999];
  chain->SetBranchAddress("jet_HFHEF", jet0_hfhadEF );
  float jet0_hfemEF[999];
  chain->SetBranchAddress("jet_HFEMEF", jet0_hfemEF );

  int ngenjet;
  chain->SetBranchAddress("ngenjet", &ngenjet );
  float genjet_pt[999];
  chain->SetBranchAddress("genjet_pt", genjet_pt );
  float genjet_eta[999];
  chain->SetBranchAddress("genjet_eta", genjet_eta );
  float genjet_phi[999];
  chain->SetBranchAddress("genjet_phi", genjet_phi );
  float genjet_mass[999];
  chain->SetBranchAddress("genjet_mass", genjet_mass );



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
    float rho;
    tree->Branch("rho", &rho, "rho/F");

    int run;
    tree->Branch("run", &run, "run/I");
    int lumi;
    tree->Branch("lumi", &lumi, "lumi/I");
    Long64_t event;
    tree->Branch("event", &event, "event/L");

    int njet;
    tree->Branch("njet", &njet, "njet/I");
    float jet_pt[999];
    tree->Branch("jet_pt", jet_pt, "jet_pt[njet]/F");
    float jet_eta[999];
    tree->Branch("jet_eta", jet_eta, "jet_eta[njet]/F");
    float jet_phi[999];
    tree->Branch("jet_phi", jet_phi, "jet_phi[njet]/F");
    float jet_mass[999];
    tree->Branch("jet_mass", jet_mass, "jet_mass[njet]/F");
    float jet_rawpt[999];
    tree->Branch("jet_rawpt", jet_rawpt, "jet_rawpt[njet]/F");
    float jet_genpt[999];
    tree->Branch("jet_genpt", jet_genpt, "jet_genpt[njet]/F");
    int jet_id[999];
    tree->Branch("jet_id", jet_id, "jet_id[njet]/I");
    int jet_puid[999];
    tree->Branch("jet_puid", jet_puid, "jet_puid[njet]/I");

    float jet_chEF[999];
    tree->Branch("jet_chEF", jet_chEF, "jet_chEF[njet]/F");
    float jet_nhEF[999];
    tree->Branch("jet_nhEF", jet_nhEF, "jet_nhEF[njet]/F");
    float jet_phEF[999];
    tree->Branch("jet_phEF", jet_phEF, "jet_phEF[njet]/F");
    float jet_elEF[999];
    tree->Branch("jet_elEF", jet_elEF, "jet_elEF[njet]/F");
    float jet_muEF[999];
    tree->Branch("jet_muEF", jet_muEF, "jet_muEF[njet]/F");
    float jet_hfhadEF[999];
    tree->Branch("jet_hfhadEF", jet_hfhadEF, "jet_hfhadEF[njet]/F");
    float jet_hfemEF[999];
    tree->Branch("jet_hfemEF", jet_hfemEF, "jet_hfemEF[njet]/F");

    
    int nentries = chain->GetEntries();
    nentries = 1000;

    std::cout << "   Starting loop on entries." << std::endl;

    for( unsigned iEntry=0; iEntry<nentries; ++iEntry) {

      chain->GetEntry(iEntry);

      if( iEntry % 20000 == 0 ) std::cout << "   Entry: " << iEntry << " / " << nentries << std::endl;


      njet = 0;
 
      for( unsigned ijet=0; ijet<njet0; ++ijet ) {

        TLorentzVector this_jet;
        this_jet.SetPtEtaPhiM( jet_pt[ijet], jet_eta[ijet], jet_phi[ijet], jet_mass[ijet] );

        if( this_jet.Pt() < 20. ) continue; 

        // matching
        float best_deltaR = 999.;
        float ptGenFound = -999.;

        for( unsigned igenjet=0; igenjet<ngenjet; ++ngenjet ) {

          TLorentzVector this_genjet;
          this_genjet.SetPtEtaPhiM( genjet_pt[igenjet], genjet_eta[igenjet], genjet_phi[igenjet], genjet_mass[igenjet] );
          
          float this_deltaR = this_jet.DeltaR( this_genjet );
          if( this_deltaR < best_deltaR ) {
            best_deltaR = this_deltaR;
            if( best_deltaR < 0.3 ) {
              ptGenFound = this_genjet.Pt();
            }
          }

        } // for genjets

        
        jet_pt  [njet] = this_jet.Pt();        
        jet_eta [njet] = this_jet.Eta();        
        jet_phi [njet] = this_jet.Phi();        
        jet_mass[njet] = this_jet.M();        

        jet_rawpt[njet] = jet0_rawPt[ijet];
        jet_genpt[njet] = ptGenFound;

        jet_id   [njet] = jet0_id  [ijet];
        jet_puid [njet] = jet0_puId[ijet];

        jet_chEF [njet] = jet0_chEF[ijet];
        jet_nhEF [njet] = jet0_nhEF[ijet];
        jet_phEF [njet] = jet0_phEF[ijet];
        jet_elEF [njet] = jet0_elEF[ijet];
        jet_muEF [njet] = jet0_muEF[ijet];
        jet_hfhadEF [njet] = jet0_hfhadEF[ijet];
        jet_hfemEF  [njet] = jet0_hfemEF [ijet];

        njet += 1;

      } // for jets

      tree->Fill();
 
    }  // for entries

    outfile->cd();
    tree->Write();
    outfile->Close();

  } // for datasets

  return 0;

}
