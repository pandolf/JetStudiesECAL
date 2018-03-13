import PhysicsTools.HeppyCore.framework.config as cfg


#Load all analyzers
from CMGTools.TTHAnalysis.analyzers.susyCore_modules_cff import *

# Comment this line if you want the diagnostic folders produced along with the output root file
cfg.Analyzer.nosubdir = True


# Load the producer module to build full 5x5 cluster shapes and whatever 
# else is needed for IDs
from RecoEgamma.PhotonIdentification.PhotonIDValueMapProducer_cfi import *

# Load the producer for MVA IDs. Make sure it is also added to the sequence!
from RecoEgamma.PhotonIdentification.PhotonMVAValueMapProducer_cfi import *

#and subsequently add these producers to the main sequence, like (order is important!)
#process.p = cms.Path(process.photonIDValueMapProducer * process.photonMVAValueMapProducer * process.myAnalyzer)



### jet pt treshold for mt2 calculation
mt2JPt = 30.0

#JSON
jsonAna.useLumiBlocks = True

#Vertex
vertexAna.keepFailingEvents = True # keep events with no good vertices

#Lepton
lepAna.loose_muon_dxy = 0.2
lepAna.loose_muon_dz  = 0.5
lepAna.loose_muon_relIso  = 0.15
lepAna.loose_muon_isoCut = lambda muon :muon.miniRelIso < 0.2

lepAna.loose_electron_pt  = 5
lepAna.loose_electron_eta    = 2.4
lepAna.loose_electron_relIso = 0.15
lepAna.loose_electron_isoCut = lambda electron : electron.miniRelIso < 0.1

lepAna.loose_electron_id  = "MVA_ID_NonTrig_Spring16_VLooseSI"
lepAna.loose_electron_lostHits = 999. # no cut
lepAna.loose_electron_dxy    = 999.
lepAna.loose_electron_dz     = 999.

lepAna.inclusive_electron_id  = "MVA_ID_NonTrig_Spring16_VLooseSI"
lepAna.inclusive_electron_lostHits = 999. # no cut since embedded in ID
lepAna.inclusive_electron_dxy    = 999. # no cut since embedded in ID
lepAna.inclusive_electron_dz     = 999. # no cut since embedded in ID

lepAna.mu_isoCorr = "deltaBeta"
lepAna.ele_isoCorr = "deltaBeta"
lepAna.ele_tightId = "MVA_ID_NonTrig_Spring16_VLooseSI"
lepAna.notCleaningElectrons = True
lepAna.doMiniIsolation = True
lepAna.miniIsolationPUCorr = 'rhoArea'
lepAna.ele_effectiveAreas = 'Spring15_25ns_v1'             #new default 
lepAna.mu_effectiveAreas = 'Spring15_25ns_v1'              #new default
lepAna.rhoMuon= 'fixedGridRhoFastjetCentralNeutral',      #new default
lepAna.rhoElectron = 'fixedGridRhoFastjetCentralNeutral', #new default
lepAna.doIsoAnnulus = True



# JET (for event variables do apply the jetID and not PUID yet)
jetAna.relaxJetId = True
jetAna.doPuId = False
jetAna.doQG = True
jetAna.jetEta = 4.7
jetAna.jetEtaCentral = 2.4
jetAna.jetPt = 20. #was 10
#jetAna.mcGT     = "Spring16_25nsV6_MC" # jec corrections
#jetAna.dataGT   = "Spring16_25nsV6_DATA" # jec corrections

jetAna.mcGT="Summer16_23Sep2016V4_MC"
jetAna.dataGT = [ [ -1, "Summer16_23Sep2016BCDV4_DATA"], [276831 ,"Summer16_23Sep2016EFV4_DATA"] , [278802 ,"Summer16_23Sep2016GV4_DATA"] , [ 280919  ,"Summer16_23Sep2016HV4_DATA"]  ]

#jetAna.mcGT="Summer16_25nsV5_MC"    
#jetAna.dataGT = "Spring16_23Sep2016BCDV2_DATA Spring16_23Sep2016EFV2_DATA Spring16_23Sep2016GV2_DATA  Spring16_23Sep2016HV2_DATA"
#jetAna.dataGT = [ [ -1, "Spring16_23Sep2016BCDV2_DATA"], [276831 ,"Spring16_23Sep2016EFV2_DATA"] , [278820 ,"Spring16_23Sep2016GV2_DATA"] , [ 280919  ,"Spring16_23Sep2016HV2_DATA"]  ]


# jetAna.recalibrateJets = False # False or False
# jetAna.applyL2L3Residual = False # 'Data'
# jetAna.calculateSeparateCorrections = False
# jetAna.calculateType1METCorrection = False

# #NOMINAL, go back to this change
jetAna.recalibrateJets = True # True or False
jetAna.applyL2L3Residual = True # 'Data'
jetAna.calculateSeparateCorrections = True
jetAna.calculateType1METCorrection = True

jetAna.jetLepDR = 0.4
jetAna.smearJets = False
jetAna.jetGammaDR = 0.4
jetAna.cleanFromLepAndGammaSimultaneously = True
jetAna.jetGammaLepDR = 0.4
jetAna.minGammaPt = 20.
jetAna.gammaEtaCentral = 2.4
#jetAna.cleanJetsFromFirstPhoton = True
jetAna.cleanJetsFromFirstPhoton = False
jetAna.cleanJetsFromIsoTracks = False ## added for Dominick
jetAna.doJetCleaning = False
#jetAna.alwaysCleanPhotons = True
jetAna.shiftJEC = 0



# TAU 
tauAna.inclusive_ptMin = 20.0
tauAna.inclusive_etaMax = 2.3
tauAna.inclusive_dxyMax = 99999.
tauAna.inclusive_dzMax = 99999.
tauAna.inclusive_vetoLeptons = False
tauAna.inclusive_vetoLeptonsPOG = False
#tauAna.inclusive_decayModeID = "byLooseCombinedIsolationDeltaBetaCorr3Hits" # ignored if not set or ""

tauAna.loose_ptMin = 20.0
tauAna.loose_etaMax = 2.3
tauAna.loose_dxyMax = 99999.
tauAna.loose_dzMax = 99999.
tauAna.loose_vetoLeptons = False
tauAna.loose_vetoLeptonsPOG = False
#tauAna.loose_decayModeID = "byLooseCombinedIsolationDeltaBetaCorr3Hits" # ignored if not set or ""

# Photon
photonAna.etaCentral = 2.5
photonAna.ptMin = 20
photonAna.gammaID = "POG_Spring17_Loose"
photonAna.do_randomCone = False
photonAna.do_mc_match = False

# Isolated Track
isoTrackAna.setOff=False
isoTrackAna.doIsoAnnulus = True

# recalibrate MET
metAna.recalibrate = 'type1' # 'type1' or False
metAna.old74XMiniAODs = False # get right Raw MET on old 74X MiniAODs



# store all taus by default
genAna.allGenTaus = False
susyScanAna.doLHE = False

# Core Analyzer
ttHCoreEventAna.mhtForBiasedDPhi = "mhtJetXjvec"
ttHCoreEventAna.jetPt = mt2JPt 

##------------------------------------------ 
##  CONTROL VARIABLES
##------------------------------------------ 

from PhysicsTools.Heppy.analyzers.gen.LHEAnalyzer import LHEAnalyzer
LHEAna = LHEAnalyzer.defaultConfig

from PhysicsTools.Heppy.analyzers.gen.TauDecayModeAnalyzer import TauDecayModeAnalyzer
TauDecayAna = TauDecayModeAnalyzer.defaultConfig

from CMGTools.TTHAnalysis.analyzers.ttHMT2Control import ttHMT2Control

ttHMT2Control = cfg.Analyzer(
            ttHMT2Control, name = 'ttHMT2Control',
            jetPt = mt2JPt, 
            )


##------------------------------------------
##  TOPOLOGICAL VARIABLES: minMT, MT2
##------------------------------------------

from CMGTools.TTHAnalysis.analyzers.ttHTopoVarAnalyzer import ttHTopoVarAnalyzer

ttHTopoJetAna = cfg.Analyzer(
            ttHTopoVarAnalyzer, name = 'ttHTopoVarAnalyzer',
            doOnlyDefault = True,
            jetPt = mt2JPt,
            )

from PhysicsTools.Heppy.analyzers.eventtopology.MT2Analyzer import MT2Analyzer

MT2Ana = cfg.Analyzer(
    MT2Analyzer, name = 'MT2Analyzer',
    # metCollection     = "slimmedMETsMuEGClean", 
    metCollection     = "slimmedMETs",
    doOnlyDefault = True,
    jetPt = mt2JPt, 
    collectionPostFix = "",
    )



##------------------------------------------
##  PRODUCER
##------------------------------------------


##  TRIGGERS DEFINITION
from CMGTools.RootTools.samples.triggers_13TeV_Spring16 import triggers_photon75, triggers_photon90, triggers_photon120, triggers_photon75ps 
from CMGTools.RootTools.samples.triggers_13TeV_Spring16 import triggers_photon90ps, triggers_photon120ps, triggers_photon155, triggers_photon165_HE10, triggers_photon175
from CMGTools.RootTools.samples.triggers_13TeV_Spring16 import triggers_doubleele33, triggers_mumu_noniso

from CMGTools.RootTools.samples.triggers_13TeV_Spring16 import triggers_met90_mht90, triggers_metNoMu90_mhtNoMu90, triggers_metNoMu120_mhtNoMu120, triggers_Jet80MET90



triggerFlagsAna.triggerBits = {
#diphoton signal triggers
'DiPhoton30' : ["HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v*"],

'DiPhoton30_2017' : ["HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v*","HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v*"],


# signal triggers 
'PFHT800' : ["HLT_PFHT800_v*"],
'PFHT900' : ["HLT_PFHT900_v*"],
'PFMET170' : ["HLT_PFMET170_NoiseCleaned_v*","HLT_PFMET170_NotCleaned_v*","HLT_PFMET170_HBHECleaned_v*","HLT_PFMET170_JetIdCleaned_v*"],
'PFHT300_PFMET100' : ["HLT_PFHT300_PFMET100_v*"],
'PFHT300_PFMET110' : ["HLT_PFHT300_PFMET110_v*"],
'PFHT350_PFMET100' : ["HLT_PFHT350_PFMET100_NoiseCleaned_v*","HLT_PFHT350_PFMET100_JetIdCleaned_v*","HLT_PFHT350_PFMET100_v*"],
'PFHT350_PFMET120' : ["HLT_PFHT350_PFMET120_NoiseCleaned_v*","HLT_PFHT350_PFMET120_JetIdCleaned_v*"],
'PFJet450' : ["HLT_PFJet450_v*"],
'PFJet500' : ["HLT_PFJet500_v*"],
#
# mono-jet signal triggers
'PFMETNoMu90_PFMHTNoMu90' : ["HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*","HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*","HLT_PFMETNoMu90_PFMHTNoMu90_IDTight_v*"],
'MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90' : ["HLT_MonoCentralPFJet80_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*","HLT_MonoCentralPFJet80_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*",
                                                "HLT_MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90_IDTight_v*"],
#
'PFMETNoMu100_PFMHTNoMu100' : ["HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_v*"],
'PFMETNoMu110_PFMHTNoMu110' : ["HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v*"],
'PFMETNoMu120_PFMHTNoMu120' : ["HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*","HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*","HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v*"],
'PFMET90_PFMHT90'           : ["HLT_PFMET90_PFMHT90_IDTight_v*","HLT_PFMET90_PFMHT90_IDLoose_v*"],
'PFMET100_PFMHT100'         : ["HLT_PFMET100_PFMHT100_IDTight_v*"],
'PFMET110_PFMHT110'         : ["HLT_PFMET110_PFMHT110_IDTight_v*"],
'PFMET120_PFMHT120'         : ["HLT_PFMET120_PFMHT120_IDTight_v*"],
#
# lepton triggers
'SingleMu'     : ["HLT_IsoMu27_v*", "HLT_IsoTkMu27_v*","HLT_IsoMu17_eta2p1_v*","HLT_IsoMu20_v*","HLT_IsoMu20_eta2p1_v*","HLT_IsoTkMu20_v*","HLT_IsoTkMu20_eta2p1_v*","HLT_IsoMu24_v*","HLT_IsoTkMu24_v*"],
'SingleEl'     : ["HLT_Ele32_eta2p1_WPTight_Gsf_v*", "HLT_Ele23_WPLoose_Gsf_v*","HLT_Ele22_eta2p1_WPLoose_Gsf_v*","HLT_Ele23_WP75_Gsf_v*","HLT_Ele22_eta2p1_WP75_Gsf_v*","HLT_Ele25_eta2p1_WPTight_Gsf_v*","HLT_Ele27_eta2p1_WPLoose_Gsf_v*","HLT_Ele27_eta2p1_WPTight_Gsf_v*"],
'DoubleEl'     : ["HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*"],
'DoubleEl33'   : ["HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_MW_v*","HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v*"],
'MuX_Ele12' : ["HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*","HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v*"],
'Mu8_EleX' : ["HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*", "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v*","HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v*"],
'DoubleMu'     : ["HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*", "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v*","HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v*","HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v*"],
'DoubleMu_NonIso'    : ["HLT_Mu40_TkMu11_v*","HLT_Mu30_TkMu11_v*"],
'Mu30_Ele30_NonIso'  : ["HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL_v*"],
'Mu33_Ele33_NonIso'  : ["HLT_Mu33_Ele33_CaloIdL_GsfTrkIdVL_v*"],
'SingleMu_NonIso'    : ["HLT_Mu55_v*", "HLT_Mu50_v*","HLT_TkMu50_v*"],
'SingleEl_NonIso'    : ["HLT_Ele105_CaloIdVT_GsfTrkIdT_v*"],
# for single-photon control region
'Photon120' : ["HLT_Photon120_v*"], 
'Photon165_HE10' : ["HLT_Photon165_HE10_v*"], 
# photon backups
'Photon250_NoHE' : ["HLT_Photon250_NoHE_v*"], 
'ECALHT800' : ["HLT_ECALHT800_v*"], 

# for QCD control region
'PFHT125_Prescale'  : ["HLT_PFHT125_v*"],
'PFHT200_Prescale'  : ["HLT_PFHT200_v*"],
'PFHT300_Prescale'  : ["HLT_PFHT300_v*"],
'PFHT350_Prescale'  : ["HLT_PFHT350_v*"],
'PFHT475_Prescale'  : ["HLT_PFHT475_v*"],
'PFHT600_Prescale'  : ["HLT_PFHT600_v*"],

'DiCentralPFJet70_PFMET120'  : ["HLT_DiCentralPFJet70_PFMET120_NoiseCleaned_v*","HLT_DiCentralPFJet70_PFMET120_JetIdCleaned_v*"], 
'DiCentralPFJet55_PFMET110'  : ["HLT_DiCentralPFJet55_PFMET110_NoiseCleaned_v*","HLT_DiCentralPFJet55_PFMET110_JetIdCleaned_v*"], 

#Francesco's ?? 
'Photon75_R9Id90_HE10_IsoM' : triggers_photon75,
'Photon90_R9Id90_HE10_IsoM' : triggers_photon90,
'Photon120_R9Id90_HE10_IsoM' : triggers_photon120,
'Photon75' : triggers_photon75ps,
'Photon90' : triggers_photon90ps,
'Photon155' : triggers_photon155,
'Photon175' : triggers_photon175,

## monojet triggers
'PFMET90_PFMHT90' : triggers_met90_mht90,
'PFMETNoMu90_PFMHTNoMu90' : triggers_metNoMu90_mhtNoMu90,
'PFMETNoMu120_PFMHTNoMu120' : triggers_metNoMu120_mhtNoMu120,
'MonoCentralPFJet80_PFMETNoMu90_PFMHTNoMu90' : triggers_Jet80MET90,

### ZGamma triggers
'DoubleEle33' : triggers_doubleele33,
'Mu30_TkMu11' : triggers_mumu_noniso,



}

# Get full list of triggers. To be used later to filter events
allTriggers = []
for key,value in triggerFlagsAna.triggerBits.items():
    allTriggers = allTriggers + value
#print "trigger list: %s" % (allTriggers)



##  FILTERS DEFINITION
eventFlagsAna.triggerBits = {
    # recommended filters for 80X
    "HBHENoiseFilter" : [ "Flag_HBHENoiseFilter" ], 
    "HBHENoiseIsoFilter" : [ "Flag_HBHENoiseIsoFilter" ], 
    # "CSCTightHalo2015Filter" : [ "Flag_CSCTightHalo2015Filter" ],
    "EcalDeadCellTriggerPrimitiveFilter" : [ "Flag_EcalDeadCellTriggerPrimitiveFilter" ],
    "goodVertices" : [ "Flag_goodVertices" ],
    "eeBadScFilter" : [ "Flag_eeBadScFilter" ],
    # Halo filter to be used
    #    "globalTightHalo2016Filter" : [ "Flag_globalTightHalo2016Filter" ],    
    #"badMuons" : [ "Flag_badMuons" ],
    #"duplicateMuons" : [ "Flag_duplicateMuons" ],
    #"noBadMuons" : [ "Flag_noBadMuons" ],
    #    "globalSuperTightHalo2016Filter" : ["Flag_globalSuperTightHalo2016Filter"],
    "globalTightHalo2016Filter" : ["Flag_globalTightHalo2016Filter"],
    "badMuons" : [ "Flag_BadPFMuonFilter" ],
    "badChHad" : [ "Flag_BadChargedCandidateFilter" ],
    "eeBadCalibFilter" : [ "Flag_ecalBadCalibFilter" ],
    }


#-------- SEQUENCE

from CMGTools.TTHAnalysis.analyzers.treeProducerSusyFullHad import *
from CMGTools.TTHAnalysis.analyzers.treeProducerMT2forQCDStudies import *
from CMGTools.TTHAnalysis.analyzers.treeProducerMT2forJECstudies import *

treeProducer = cfg.Analyzer(
     AutoFillTreeProducer, name='treeProducerSusyFullHad',
     vectorTree = True,
     saveTLorentzVectors = False,  # can set to True to get also the TLorentzVectors, but trees will be bigger
     PDFWeights = PDFWeights,
     globalVariables = susyFullHad_globalVariables,
     globalObjects = susyFullHad_globalObjects,
     collections = susyFullHad_collections,
     defaultFloatType = 'F',
     treename = 'mt2'
)

susyCoreSequence.insert(susyCoreSequence.index(skimAnalyzer),
                        susyCounter)

### Here we are moving the jet cleaning module so that the JEC corrections are already propagated
### to jets, met, and isoTracks
susyCoreSequence.remove(isoTrackAna)
susyCoreSequence.insert(susyCoreSequence.index(metAna)+1,isoTrackAna)
susyCoreSequence.insert(susyCoreSequence.index(isoTrackAna)+1,jetCleanAna)



sequence = cfg.Sequence(
    susyCoreSequence+[
    LHEAna,
    ttHMT2Control,
    MT2Ana,
    ttHTopoJetAna,
    treeProducer,
    ])


###---- to switch off the compression
#treeProducer.isCompressed = 0





from PhysicsTools.HeppyCore.framework.heppy_loop import getHeppyOption

#-------- HOW TO RUN
# choose 0 for quick validations tests. It doesn't require to load the sample files
# choose 2 for full mc production
# choose 3 for data production
# choose 4 for signal production
test = int(getHeppyOption('test',0))
test = 2 # MC production
#test = 0 # local test on data
isData = False # will be changed accordingly if chosen to run on data
doSpecialSettingsForMECCA = 1 # set to 1 for comparisons with americans
runPreprocessor = False




if test==0:
    from CMGTools.RootTools.samples.ComponentCreator import ComponentCreator
    kreator = ComponentCreator()

    json = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'
    DoubleMuon = kreator.makeDataComponent("DoubleMuon_Run2017C_run299649", "/DoubleMuon/Run2017C-17Nov2017-v1/MINIAOD", "CMS", ".*root", run_range = (299649,299649), triggers = [])
    DoubleMuon.files = [ 'root://eoscms//eos/cms/store/data/Run2017C/DoubleMuon/MINIAOD/17Nov2017-v1/50000/00519DC1-7ED3-E711-96E1-008CFAFBE5E0.root'  ]
    DoubleMuon.json = json
    comp= DoubleMuon

    selectedComponents = [comp]


elif test==1:

    # Uncomment the two following lines to run on a specific event
    #eventSelector.toSelect = [ 84142401 ]
    #sequence = cfg.Sequence([eventSelector] + sequence)

    #isData = True
    #from CMGTools.RootTools.samples.samples_13TeV_DATA2016 import *
    from CMGTools.RootTools.samples.samples_13TeV_RunIISummer16MiniAODv2 import *

    selectedComponents = [DiPhotonJetsBox_MGG80toInf_amcatnlo]

    for comp in selectedComponents:
 
        comp.files = ['root://xrootd.unl.edu//store/mc/RunIISummer16MiniAODv2/DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/120000/12D62993-E7C6-E611-B1A4-002590DE6E3E.root'] 

elif test==2:

    from CMGTools.RootTools.samples.samples_13TeV_RunIISummer16MiniAODv2_QCD import *

    from CMGTools.RootTools.samples.autoAAAconfig import *

    selectedComponents = QCDRelVal

    for comp in selectedComponents:
        comp.splitFactor = 100
        comp.files = comp.files[:]
        comp.fineSplitFactor = 1 

    autoAAA(selectedComponents)


elif test==3:
    # run on data

    isData = True
    from CMGTools.RootTools.samples.samples_13TeV_DATA2017 import *

    dataDir = os.environ['CMSSW_BASE']+"/src/CMGTools/TTHAnalysis/data"
    json=dataDir+'/json/json_PromptReco_Run2017.txt'
    #json=dataDir+'/json/json_DCSONLY.txt'

    
    isForQCD = False


    # --------------- HERE IS THE PART YOU SHOULD PAY ATTENTION TO --------------------------------------------
    #For running on the full list of samples
    if not isForQCD:
        #selectedComponents  = dataSamples_Run2016B_ReReco23Sep_V12
        #selectedComponents  = dataSamples_Run2016B_ReReco23Sep_V3
        #selectedComponents  = dataSamples_Run2016C_ReReco23Sep
        #selectedComponents  = dataSamples_Run2016D_ReReco23Sep
        #selectedComponents  = dataSamples_Run2016E_ReReco23Sep
        #selectedComponents  = dataSamples_Run2016F_ReReco23Sep
        #selectedComponents  = dataSamples_Run2016G_ReReco23Sep
        
        #selectedComponents  = dataSamples_Run2016B_03Feb2017_v2 
        #selectedComponents  = dataSamples_Run2016C_03Feb2017 
        #selectedComponents  = dataSamples_Run2016D_03Feb2017
        #selectedComponents  = dataSamples_Run2016E_03Feb2017
        #selectedComponents  = dataSamples_Run2016F_03Feb2017
        #selectedComponents  = dataSamples_Run2016G_03Feb2017 
        #selectedComponents  = dataSamples_Run2016H_03Feb2017_v2 + dataSamples_Run2016H_03Feb2017_v3

#        selectedComponents  = dataSamples_Run2017_DoubleEG
#        selectedComponents  = [ DoubleEG_Run2017B_PromptReco_v2 ]

        selectedComponents  = dataSamples_Run2017_DoubleEG_reReco
        # selectedComponents  = [DoubleEG_Run2016B_03Feb2017_v2,
        #                        DoubleEG_Run2016C_03Feb2017,
        #                        DoubleEG_Run2016D_03Feb2017,
        #                        DoubleEG_Run2016E_03Feb2017,
        #                        DoubleEG_Run2016F_03Feb2017,
        #                        DoubleEG_Run2016G_03Feb2017,
        #                        DoubleEG_Run2016H_03Feb2017_v2,
        #                        DoubleEG_Run2016H_03Feb2017_v3]



#        selectedComponents  = [DoubleEG_Run2016B_03Feb2017_v2]

#        selectedComponents  = dataSamples_Run2016H_v2 + dataSamples_Run2016H_v3
#        selectedComponents  = dataSamples_Run2016G_23Sep2016
#        selectedComponents  = dataSamples_Run2016F_23Sep2016
#        selectedComponents  = dataSamples_Run2016E_23Sep2016
#        selectedComponents  = dataSamples_Run2016D_23Sep2016
#        selectedComponents  = dataSamples_Run2016C_23Sep2016
#        selectedComponents  = dataSamples_Run2016B_23Sep2016

        #        selectedComponents  = dataSamples_23Sep2016PlusPrompt
        #selectedComponents  = dataSamples_Run2016H_PromptV2 + dataSamples_Run2016H_PromptV3
        #selectedComponents  = dataSamples_Run2016B_ReReco23Sep + dataSamples_Run2016C_ReReco23Sep + dataSamples_Run2016D_ReReco23Sep + dataSamples_Run2016E_ReReco23Sep + dataSamples_Run2016F_ReReco23Sep + dataSamples_Run2016G_ReReco23Sep + dataSamples_Run2016H_PromptV2 + dataSamples_Run2016H_PromptV3
 #   else:
        #selectedComponents  = dataSamples_Run2016B_ReReco23Sep_V12_forQCD
        #selectedComponents  = dataSamples_Run2016B_ReReco23Sep_V3_forQCD
        #selectedComponents  = dataSamples_Run2016C_ReReco23Sep_forQCD
        #selectedComponents  = dataSamples_Run2016D_ReReco23Sep_forQCD
        #selectedComponents  = dataSamples_Run2016E_ReReco23Sep_forQCD
        #selectedComponents  = dataSamples_Run2016F_ReReco23Sep_forQCD
        #selectedComponents  = dataSamples_Run2016G_ReReco23Sep_forQCD
        #selectedComponents  = dataSamples_Run2016H_PromptV2_forQCD + dataSamples_Run2016H_PromptV3_forQCD
        #selectedComponents  = dataSamples_Run2016B_ReReco23Sep_V12_forQCD + dataSamples_Run2016B_ReReco23Sep_V3_forQCD + dataSamples_Run2016C_ReReco23Sep_forQCD + dataSamples_Run2016D_ReReco23Sep_forQCD + dataSamples_Run2016E_ReReco23Sep_forQCD + dataSamples_Run2016F_ReReco23Sep_forQCD + dataSamples_Run2016G_ReReco23Sep_forQCD + dataSamples_Run2016H_PromptV2_forQCD + dataSamples_Run2016H_PromptV3_forQCD

 
    for comp in selectedComponents:
        comp.json=json
        comp.splitFactor = 1000
        comp.files=comp.files[:]
#        comp.files=comp.files[:]
        comp.triggers = allTriggers

    # Here I add the skim to the sequence.
    # It should be uncommented for non _forQCD samples. It should be commented for _forQCD samples
    if not isForQCD:
        sequence.insert(sequence.index(treeProducer), MT2skim)
    

    # Tree configuration for QCD studies
    # It should be commented for non _forQCD samples. It should be uncommented for _forQCD samples
    if isForQCD:
        treeProducer.globalVariables = MT2forQCDStudies_globalVariables
        treeProducer.globalObjects = MT2forQCDStudies_globalObjects
        treeProducer.collections = MT2forQCDStudies_collections


elif test==4:

    from CMGTools.RootTools.samples.samples_13TeV_signals import *

    jetAna.mcGT     = "Spring16_FastSimV1_MC" # jec corrections for FastSim V1### 25
    jetAna.applyL2L3Residual = False # 'Data'
    jetAna.do_mc_match = True
    jetAna.relaxJetId = True
    jetCleanAna.relaxJetId = True

    selectedComponents = [
        SMS_TChiHH_HToGG,
        SMS_TChiHZ_HToGG,
        SMS_TChiWH_HToGG,
        ]




    # test all components (1 thread per component).
    for comp in selectedComponents:
        comp.splitFactor = 1200
        #comp.fineSplitFactor = 4 # to run 4 jobs per file
        #comp.files = comp.files[:1]
        comp.files = comp.files[:]
        # triggers on MC
        #comp.triggers = triggers_HT900 + triggers_HTMET + triggers_photon155 + triggers_1mu_isolow + triggers_MT2_mumu + triggers_MT2_ee + triggers_MT2_mue # to apply trigger skimming


if doSpecialSettingsForMECCA:
    jetAna.doQG = False
    # photonAna.do_randomCone = False
    # Below slow things note: it will in any case try it only on MC, not on data
    # photonAna.do_mc_match = False
    # jetAna.do_mc_match = False
    lepAna.do_mc_match = False
    isoTrackAna.do_mc_match = False
    ###genAna.makeLHEweights = False ### Such option does not exist (anymore)

if isData:
    for comp in samples:
        comp.isMC = False
        comp.isData = True




from PhysicsTools.HeppyCore.framework.services.tfile import TFileService 
output_service = cfg.Service(
      TFileService,
      'outputfile',
      name="outputfile",
      fname='mt2.root',
      option='recreate'
    )


from PhysicsTools.HeppyCore.framework.eventsfwlite import Events
config = cfg.Config( components = selectedComponents,
                     sequence = sequence,
                     services = [output_service],
                     #                     events_class = event_class)
                     events_class = Events)




