import PhysicsTools.HeppyCore.framework.config as cfg
import os

#####COMPONENT CREATOR

from CMGTools.RootTools.samples.ComponentCreator import ComponentCreator
kreator = ComponentCreator()


### QCD RelVal for Jet Calibrations

RelValQCD_FlatPt_15_3000HS_13_noPU_30fb  = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000HS_13_noPU_30fb" , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_0-100X_upgrade2018_realistic_v7_HS1M-v1/MINIAODSIM"             , "CMS", ".*root", 1. )
RelValQCD_FlatPt_15_3000HS_13_noPU_0fb   = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000HS_13_noPU_0fb"  , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_0-100X_upgrade2018_realistic_Version0fb_v1_HS1M-v1/MINIAODSIM"  , "CMS", ".*root", 1. )
RelValQCD_FlatPt_15_3000HS_13_noPU_60fb  = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000HS_13_noPU_60fb" , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_0-100X_upgrade2018_realistic_Version60fb_v1_HS1M-v1/MINIAODSIM" , "CMS", ".*root", 1. )

RelValQCD_FlatPt_15_3000HS_13_30fb       = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000HS_13_30fb"      , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_0-PU25ns_100X_upgrade2018_realistic_v7_HS1Mrsb-v1/MINIAODSIM"             , "CMS", ".*root", 1. )
RelValQCD_FlatPt_15_3000HS_13_0fb        = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000HS_13_0fb"       , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_0-PU25ns_100X_upgrade2018_realistic_Version0fb_v1_HS1Mrsb-v1/MINIAODSIM"  , "CMS", ".*root", 1. )
RelValQCD_FlatPt_15_3000HS_13_60fb       = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000HS_13_60fb"      , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_0-PU25ns_100X_upgrade2018_realistic_Version60fb_v1_HS1Mrsb-v1/MINIAODSIM" , "CMS", ".*root", 1. )

RelValQCD_FlatPt_15_3000_PFthA_noPU      = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000_PFthA_noPU"     , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_3-100X_upgrade2018_realistic_v11_thA_HS1M-v1/MINIAODSIM" , "CMS", ".*root", 1. )
RelValQCD_FlatPt_15_3000_PFthB_noPU      = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000_PFthB_noPU"     , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_3-100X_upgrade2018_realistic_v11_thB_HS1M-v2/MINIAODSIM" , "CMS", ".*root", 1. )
RelValQCD_FlatPt_15_3000_PFthC_noPU      = kreator.makeMCComponent("RelValQCD_FlatPt_15_3000_PFthC_noPU"     , "/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_0_3-100X_upgrade2018_realistic_v11_thC_HS1M-v2/MINIAODSIM" , "CMS", ".*root", 1. )

QCDRelVal = [
   #RelValQCD_FlatPt_15_3000HS_13_noPU_30fb,
   #RelValQCD_FlatPt_15_3000HS_13_noPU_0fb,
   #RelValQCD_FlatPt_15_3000HS_13_noPU_60fb,
   #RelValQCD_FlatPt_15_3000HS_13_30fb,
   #RelValQCD_FlatPt_15_3000HS_13_0fb,
   #RelValQCD_FlatPt_15_3000HS_13_60fb,
   RelValQCD_FlatPt_15_3000_PFthA_noPU,
   RelValQCD_FlatPt_15_3000_PFthB_noPU,
   RelValQCD_FlatPt_15_3000_PFthC_noPU 
    ]



### ----------------------------- summary ----------------------------------------

mcSamples = QCDRelVal


#mcSamples = TTs + SingleTop + VJets + DYJetsM50HT + DYJetsM5to50HT + WJetsToLNuHT + WNJets + GJetsHT + ZJetsToNuNuHT + QCDHT + QCDPtbcToE + QCDPt + QCDPtEMEnriched + [QCD_Mu15] + QCD_Mu5 +  DiBosons + TriBosons + TTV + Higgs + Rares + EWKV2Jets + [TChiSlepSnu,T1tttt_2016,T5qqqqVV_2016]

samples = mcSamples

### ---------------------------------------------------------------------

from CMGTools.TTHAnalysis.setup.Efficiencies import *
dataDir = "$CMSSW_BASE/src/CMGTools/TTHAnalysis/data"

#Define splitting
for comp in mcSamples:
    comp.isMC = True
    comp.isData = False
    comp.splitFactor = 250 #  if comp.name in [ "WJets", "DY3JetsM50", "DY4JetsM50","W1Jets","W2Jets","W3Jets","W4Jets","TTJetsHad" ] else 100
    comp.puFileMC=dataDir+"/puProfile_Summer12_53X.root"
    comp.puFileData=dataDir+"/puProfile_Data12.root"
    comp.efficiency = eff2012

if __name__ == "__main__":
    from CMGTools.RootTools.samples.tools import runMain
    runMain(samples)
