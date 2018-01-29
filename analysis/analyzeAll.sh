if [ $# -lt 1 ]
then
  echo "Please provide production name and pass it as first argument: ./analyzeAll [productionName]"
else
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF_noPU
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SRON
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF_noPU
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON
  ./jseAnalyzer $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON_noPU
fi
