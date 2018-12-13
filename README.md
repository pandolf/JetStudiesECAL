- first checkout CMGTools: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CMGToolsReleasesExperimental
- then source JetStudiesECAL/cmg_stuff/copyToCMG.sh
- then go to CMGTools and create the ntuples


so, in particular:
- for studies done in 10_X we're still running CMSSW_9_4 so go to: /afs/cern.ch/work/p/pandolf/CMSSW_9_4_1_CMG/src/CMGTools/TTHAnalysis/cfg
- you're gonna have to add the datasets to: /afs/cern.ch/work/p/pandolf/CMSSW_9_4_1_CMG/src/CMGTools/RootTools/python/samples/samples_13TeV_RunIISummer16MiniAODv2_QCD.py 
- then use /afs/cern.ch/work/p/pandolf/CMSSW_9_4_1_CMG/src/CMGTools/TTHAnalysis/cfg/sendOnBatch.sh:  ./sendOnBatch.sh [productionName]
