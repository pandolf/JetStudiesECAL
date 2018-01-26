if [ $# -lt 1 ]
then
  echo "Please provide production name and pass it as first argument: ./mergeAllTrees.sh [productionName]"
else
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF_noPU
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SRON
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF_noPU
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON
  ./jseMergeTrees $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON_noPU
fi
