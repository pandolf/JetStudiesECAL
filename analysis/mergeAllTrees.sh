if [ $# -lt 1 ]
then
  echo "Please provide production name and pass it as first argument: ./mergeAllTrees.sh [productionName]"
else
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SROFF_noPU
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_ECALnoiseOFF_SRON
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SROFF_noPU
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON
#  ./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13UP17_GRv2_SRON_noPU
  #./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13_noPU_30fb
  #./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13_noPU_0fb
  #./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13_noPU_60fb
  #./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13_30fb
  #./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13_0fb
  #./jseMergeTrees 10X $1 RelValQCD_FlatPt_15_3000HS_13_60fb
  #./jseMergeTrees 10X $1  RelValZEE_rel2007_GTv4
  #./jseMergeTrees 10X $1  RelValZEE_rel2008_GTv4
  #./jseMergeTrees 10X $1  RelValZEE_rel2008_GTv7
  ./jseMergeTrees 10X $1  RelValQCD_FlatPt_15_3000_PFthA_noPU
  ./jseMergeTrees 10X $1  RelValQCD_FlatPt_15_3000_PFthB_noPU
  ./jseMergeTrees 10X $1  RelValQCD_FlatPt_15_3000_PFthC_noPU
fi
