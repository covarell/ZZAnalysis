import FWCore.ParameterSet.Config as cms

process = cms.Process("ANALYSIS")

# import of standard configurations
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500000)
)

# Input source
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(
        ## qqZZ
        #'/store/mc/RunIISummer16MiniAODv2/ZZTo4L_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/80000/C2B18861-06D6-E611-9665-00259048B754.root'
        '/store/mc/RunIISummer16MiniAODv2/ZZTo4L_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/80000/706445E5-FBD5-E611-B167-002481DE485A.root'

        # ggZZ
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_0.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_1.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_10.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_100.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_101.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_102.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_103.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_104.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_105.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_106.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_107.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_109.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_11.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_111.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_112.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_113.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_114.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_115.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_116.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_117.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_118.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_119.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_12.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_120.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_121.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_122.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_123.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_125.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_126.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_127.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_129.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_13.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_130.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_131.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_132.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_133.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_134.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_135.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_136.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_137.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_138.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_139.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_14.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_140.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_141.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_142.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_143.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_144.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_145.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_146.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_147.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_148.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_15.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_150.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_151.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_152.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_154.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_155.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_156.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_157.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_158.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_159.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_16.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_160.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_161.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_162.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_163.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_164.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_165.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_167.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_168.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_169.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_17.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_170.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_171.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_172.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_173.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_174.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_175.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_176.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_177.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_178.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_179.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_180.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_181.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_182.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_183.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_184.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_185.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_186.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_187.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_188.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_189.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_19.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_190.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_191.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_192.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_193.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_194.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_195.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_196.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_197.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_198.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_199.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_2.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_20.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_200.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_201.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_202.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_203.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_204.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_205.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_206.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_207.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_208.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_209.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_21.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_210.root',
        #'/store/user/covarell/ggzz1jet/ggzz1jet_13TeV_211.root',
        
        
        ## VBS
        #'/store/mc/RunIISummer16MiniAODv2/ZZJJTo4L_EWK_13TeV-madgraph-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/EC71A8A9-19C1-E611-9614-0CC47A78A4A0.root',
        #'/store/mc/RunIISummer16MiniAODv2/ZZJJTo4L_EWK_13TeV-madgraph-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/DA10788F-ECC4-E611-8457-44A842CFD674.root',
      
    )
)

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')

process.Test = cms.EDAnalyzer("getXsecInFiducial",
    HistOutFile = cms.untracked.string('testplots.root'),
    theSrc = cms.untracked.string('externalLHEProducer'),
    whichWeight = cms.untracked.int32(-1),
    isqqZZ = cms.untracked.bool(True),
  #  lookForGenProcID = cms.untracked.int32(0) # 24 = ZH, 26 = WH, 121,122 = ttH                         
)

process.p1 = cms.Path(process.Test)

