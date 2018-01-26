#include "../interface/jseDataset.h"



jseDataset::jseDataset( const std::string& a_prodName, const std::string& a_name, const std::string& a_prettyName ) {

  prodName = a_prodName;
  name = a_name;
  prettyName = a_prettyName;

  file = TFile::Open( Form("%s/miniTrees/%s.root", prodName.c_str(), name.c_str()) );
  tree = (TTree*)file->Get("mt2");

}
