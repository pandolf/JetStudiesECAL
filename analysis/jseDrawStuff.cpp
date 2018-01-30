#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TProfile.h"

#include "../interface/jseDataset.h"
#include "../interface/jseCommon.h"



void drawAllPlots( const std::vector< jseDataset* >& datasets, const std::string& prodName, const std::string& comparisonName );
void drawProfileVsEta( const std::string& outdir, std::vector< jseDataset* > datasets, const std::string& varName, const std::string& axisName, float yMin, float yMax );
void drawResponseResolution( const std::string& outdir, std::vector<jseDataset*> datasets );
std::vector<TH1D*> getHistoVector( const std::string& name, const std::vector<float>& ptBins, const std::vector<float>& etaBins );
TH1D* getTruncatedHisto( TH1D* h1, float frac );


bool noEPS = false;

int main( int argc, char* argv[] ) {
  
  if( argc<2 ) {
    std::cout << "Usage: ./jseDrawStuff [productionName] [noEPS=false]" << std::endl;
    exit(1);
  }

  jseCommon::setStyle();
 
  std::string prodName(argv[1]);

  if( argc>2 ) {
    std::string noEPS_str(argv[2]);
    if( noEPS_str=="true" || noEPS_str=="True" || noEPS_str=="TRUE" || noEPS_str=="noEPS" || noEPS_str=="fast" ) {
      noEPS=true;
      std::cout << "-> Will not save eps files, only PDF." << std::endl;
    }
  }

  std::vector< jseDataset* > datasets;
  datasets.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON" , "SR@PF:ON"  ) );
  datasets.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF", "SR@PF:OFF" ) );

  drawAllPlots( datasets, prodName, "SRON_vs_SROFF" );

  std::vector< jseDataset* > datasets2;
  datasets2.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF", "SR@PF:OFF"  ) );
  datasets2.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF_noPU", "SR@PF:OFF noPU" ) );

  drawAllPlots( datasets2, prodName, "PU_vs_noPU" );

  std::vector< jseDataset* > datasets3;
  datasets3.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SRON", "ECALnoise:OFF SR@PF:ON") );
  datasets3.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF", "ECALnoise:OFF SR@PF:OFF") );
  datasets3.push_back( new jseDataset( prodName, "RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF_noPU", "ECALnoise:OFF SR@PF:OFF noPU") );

  drawAllPlots( datasets3, prodName, "ECALnoiseOFF" );

  return 0;

}


void drawAllPlots( const std::vector< jseDataset* >& datasets, const std::string& prodName, const std::string& comparisonName ) {

  std::string outdir( Form("%s/plots/%s", prodName.c_str(), comparisonName.c_str()) );
  system( Form("mkdir -p %s", outdir.c_str()) );

  drawProfileVsEta( outdir, datasets, "phEF", "Jet Photon Energy Fraction", 0., 0.5 );
  drawProfileVsEta( outdir, datasets, "nhEF", "Jet Neutral Hadron Energy Fraction", 0., 0.3 );
  drawProfileVsEta( outdir, datasets, "chEF", "Jet Charged Hadron Energy Fraction", 0., 0.85 );

  drawResponseResolution( outdir, datasets );

}


void drawProfileVsEta( const std::string& outdir, std::vector< jseDataset* > datasets, const std::string& varName, const std::string& axisName, float yMin, float yMax ) {


  std::vector<int> colors;
  colors.push_back( 38 );
  colors.push_back( 46 );

  std::string profileName(Form("%s_vs_eta", varName.c_str()));
 
  TCanvas* c1 = new TCanvas("c1", "", 600, 600);
  c1->cd();

  TH2D* h2_axes = new TH2D( "axes", "", 10, -3.2, 3.2, 10, yMin, yMax );
  h2_axes->SetXTitle("Jet #eta");
  h2_axes->SetYTitle(axisName.c_str());
  h2_axes->Draw();

  TLegend* legend = new TLegend( 0.3, 0.15, 0.7, 0.35 );
  legend->SetTextSize(0.035);
  legend->SetFillColor(0);

  for( unsigned i=0; i<datasets.size(); ++i ) {

    TProfile* thisProfile = (TProfile*)datasets[i]->file->Get( profileName.c_str() );
    thisProfile->SetLineColor(colors[i]);
    thisProfile->SetLineWidth(2);

    thisProfile->Draw("same");
    legend->AddEntry( thisProfile, datasets[i]->prettyName.c_str() );

  } // for datasets

  legend->Draw("same");

  gPad->RedrawAxis();
 
  if( !noEPS )
    c1->SaveAs( Form("%s/%s.eps", outdir.c_str(), profileName.c_str()) );
  c1->SaveAs( Form("%s/%s.pdf", outdir.c_str(), profileName.c_str()) );

  delete c1;
  delete h2_axes;

}



void drawResponseResolution( const std::string& outdir, std::vector<jseDataset*> datasets ) {


  std::vector<float> ptBins  = jseCommon::ptBins();
  std::vector<float> etaBins = jseCommon::etaBins();

  Double_t etaBins_lower[etaBins.size()];
  for( unsigned i=0; i<etaBins.size(); ++i ) etaBins_lower[i] = etaBins[i];

  std::vector<int> colors = jseCommon::colors();


  for( unsigned iPt=0; iPt<ptBins.size()-1; ++iPt ) {


    std::string ptText( Form("%.0f < p_{T} < %.0f GeV", ptBins[iPt], ptBins[iPt+1]) );

    float xMin = etaBins[0];
    float xMax = etaBins[etaBins.size()-1];


    // prepare response plot

    TCanvas* c1_resp = new TCanvas( "c1_resp", "", 600, 600 );
    c1_resp->cd();

    TH2D* h2_axes_resp = new TH2D( "axes_resp", "", 10, xMin, xMax, 10, 0.75, 1.3 );
    h2_axes_resp->SetXTitle( "Jet #eta" );
    h2_axes_resp->SetYTitle( "Jet Response" );
    h2_axes_resp->Draw();

    TLine* lineOne = new TLine( xMin, 1., xMax, 1. );
    lineOne->Draw("same");

    TLegend* legend_resp = new TLegend( 0.3, 0.2, 0.7, 0.4, ptText.c_str() );
    legend_resp->SetTextSize(0.038);
    legend_resp->SetFillColor(0);

    // prepare resolution plot

    TCanvas* c1_reso = new TCanvas( "c1_reso", "", 600, 600 );
    c1_reso->cd();

    TH2D* h2_axes_reso = new TH2D( "axes_reso", "", 10, xMin, xMax, 10, 0., 0.5 );
    h2_axes_reso->SetXTitle( "Jet #eta" );
    h2_axes_reso->SetYTitle( "Jet Resolution" );
    h2_axes_reso->Draw();

    TLegend* legend_reso = new TLegend( 0.3, 0.7, 0.7, 0.9, ptText.c_str() );
    legend_reso->SetTextSize(0.038);
    legend_reso->SetFillColor(0);


    for( unsigned iDataset=0; iDataset<datasets.size(); ++iDataset ) {

      TFile* file = datasets[iDataset]->file;

      std::string respDir( Form("%s/resp/%s", outdir.c_str(), datasets[iDataset]->name.c_str()) );

      if( iPt==0 )
        system( Form("mkdir -p %s", respDir.c_str()) );


      TH1D* h1_resp_vs_eta = new TH1D( Form("resp_vs_eta_%s_pt%d", datasets[iDataset]->name.c_str(), iPt), "", etaBins.size()-1, etaBins_lower );
      TH1D* h1_reso_vs_eta = new TH1D( Form("reso_vs_eta_%s_pt%d", datasets[iDataset]->name.c_str(), iPt), "", etaBins.size()-1, etaBins_lower );

      for( unsigned iEta=0; iEta<etaBins.size()-1; ++iEta ) {

        std::string thisHistoName( jseCommon::getPtEtaHistoName( "resp", iPt, iEta ) ); 
        TH1D* h1_response = (TH1D*)file->Get( thisHistoName.c_str() );
        float truncFrac = 0.99;
        TH1D* h1_responseTrunc = getTruncatedHisto( h1_response, truncFrac );

        float xMin = h1_response->GetXaxis()->GetXmin();
        float xMax = h1_response->GetXaxis()->GetXmax();

        // first plot

        TCanvas* c1 = new TCanvas( "c1", "", 600, 600 );
        c1->cd();

        TH2D* h2_axes = new TH2D("axes", "", 10, xMin, xMax, 10, 0., 1.2*h1_response->GetMaximum());
        h2_axes->SetXTitle( "Reco p_{T} / Gen p_{T}" );
        h2_axes->SetYTitle( "Entries" );
        h2_axes->Draw();

        h1_response->SetLineColor(kBlack);
        h1_response->SetFillColor(kWhite);
        h1_response->SetLineWidth(2);

        h1_responseTrunc->SetFillStyle(3004);
        h1_responseTrunc->SetFillColor(46);
        h1_responseTrunc->SetLineColor(46);
        h1_responseTrunc->SetLineWidth(2);

        TLegend* legend = new TLegend( 0.7, 0.75, 0.9, 0.9 );
        legend->SetFillColor(0);
        legend->SetTextSize(0.035);
        legend->AddEntry( h1_response, "All", "F" );
        legend->AddEntry( h1_responseTrunc, Form("%.1f%%", truncFrac*100.), "F" );
        legend->Draw("same");
       
        h1_response->Draw("same");
        h1_responseTrunc->Draw("same");

        TPaveText* labelTop = jseCommon::getLabelTopSimulation();
        labelTop->Draw("same");

        TPaveText* labelEta = new TPaveText( 0.65, 0.65, 0.9, 0.7, "brNDC" );
        labelEta->SetTextSize( 0.035 );
        labelEta->SetFillColor(0);
        labelEta->AddText( Form("%.1f < #eta < %.1f", etaBins[iEta], etaBins[iEta+1]) );
        labelEta->Draw("same");

        TPaveText* labelPt = new TPaveText( 0.65, 0.6, 0.9, 0.65, "brNDC" );
        labelPt->SetTextSize( 0.035 );
        labelPt->SetFillColor(0);
        labelPt->AddText( Form("%.0f < p_{T} < %.0f GeV", ptBins[iPt], ptBins[iPt+1]) );
        labelPt->Draw("same");

        gPad->RedrawAxis();
  
        if( !noEPS )
          c1->SaveAs( Form("%s/resp_pt%d_eta%d.eps", respDir.c_str(), iPt, iEta) );
        c1->SaveAs( Form("%s/resp_pt%d_eta%d.pdf", respDir.c_str(), iPt, iEta) );

        delete c1;
        delete h2_axes;
        delete legend;

        // end plotting 

        h1_resp_vs_eta->SetBinContent( iEta+1, h1_responseTrunc->GetMean() );
        h1_resp_vs_eta->SetBinError  ( iEta+1, h1_responseTrunc->GetMeanError() );

        h1_reso_vs_eta->SetBinContent( iEta+1, h1_responseTrunc->GetRMS() );
        h1_reso_vs_eta->SetBinError  ( iEta+1, h1_responseTrunc->GetRMSError() );

        delete h1_responseTrunc;
 
      }  // eta

      c1_resp->cd();

      h1_resp_vs_eta->SetMarkerStyle(20);
      h1_resp_vs_eta->SetMarkerSize(1.3);
      h1_resp_vs_eta->SetMarkerColor(colors[iDataset]);
      h1_resp_vs_eta->SetLineColor(colors[iDataset]);
      h1_resp_vs_eta->Draw("p same");

      legend_resp->AddEntry( h1_resp_vs_eta, datasets[iDataset]->prettyName.c_str(), "P" );

      c1_reso->cd();

      h1_reso_vs_eta->SetMarkerStyle(20);
      h1_reso_vs_eta->SetMarkerSize(1.3);
      h1_reso_vs_eta->SetMarkerColor(colors[iDataset]);
      h1_reso_vs_eta->SetLineColor(colors[iDataset]);
      h1_reso_vs_eta->Draw("p same");

      legend_reso->AddEntry( h1_reso_vs_eta, datasets[iDataset]->prettyName.c_str(), "P" );


    } // dataset

    c1_resp->cd();

    legend_resp->Draw("same");


    gPad->RedrawAxis();

    if( !noEPS )
      c1_resp->SaveAs( Form( "%s/resp_vs_eta_pt%d.eps", outdir.c_str(), iPt ) );
    c1_resp->SaveAs( Form( "%s/resp_vs_eta_pt%d.pdf", outdir.c_str(), iPt ) );

    c1_reso->cd();

    legend_reso->Draw("same");

    gPad->RedrawAxis();

    c1_reso->SaveAs( Form( "%s/reso_vs_eta_pt%d.eps", outdir.c_str(), iPt ) );
    c1_reso->SaveAs( Form( "%s/reso_vs_eta_pt%d.pdf", outdir.c_str(), iPt ) );

    delete c1_reso;
    delete c1_resp;
    delete h2_axes_reso;
    delete h2_axes_resp;

  } // pt



}


std::vector<TH1D*> getHistoVector( const std::string& name, const std::vector<float>& ptBins, const std::vector<float>& etaBins ) {

  std::vector<TH1D*> vh1;

  Double_t etaBins_lower[etaBins.size()];
  for( unsigned i=0; i<etaBins.size(); ++i ) etaBins_lower[i] = etaBins[i];

  for( unsigned iPt=0; iPt<ptBins.size()-1; ++iPt ) {
     TH1D* newhisto = new TH1D( Form("%s_vs_eta_pt%d", name.c_str(), iPt), "", etaBins.size()-1, etaBins_lower );
     vh1.push_back(newhisto);
  }

  return vh1;

}


TH1D* getTruncatedHisto( TH1D* h1, float frac ) {

  int nBins = h1->GetXaxis()->GetNbins();
  float xMin = h1->GetXaxis()->GetXmin();
  float xMax = h1->GetXaxis()->GetXmax();

  TH1D* h1_trunc = new TH1D( Form("%s_trunc", h1->GetName()), "", nBins, xMin, xMax );

  int binMax = h1->GetMaximumBin();

  float intTot = h1->Integral();

  int currentBin = binMax;

  int sign=1;
  int delta_bin=1;

  bool stopJumping = false;
  bool stopGoingRight = false;
  bool stopGoingLeft = false;

  while( h1_trunc->Integral()<frac*intTot ) {

    h1_trunc->SetBinContent( currentBin, h1->GetBinContent(currentBin) );

    if( stopGoingRight ) currentBin-=1;
    else if( stopGoingLeft  ) currentBin+=1; 
    else currentBin += sign*delta_bin;

    if( currentBin == 1 ) stopGoingLeft = true;
    if( currentBin == nBins-1 ) stopGoingRight = true;

    if( !stopJumping ) {

      delta_bin += 1;
      sign *= -1; // makes it add one bin to the right, one to the left

      if( stopGoingLeft || stopGoingRight ) stopJumping = true;

    } // if stop jumping

  }

  return h1_trunc;

} 
