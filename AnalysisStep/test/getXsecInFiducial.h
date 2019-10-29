#ifndef getXsecInFiducial_H
#define getXsecInFiducial_H

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "CommonTools/Utils/interface/PtComparator.h"
#include "DataFormats/JetReco/interface/GenJet.h"

#include "ZZAnalysis/AnalysisStep/interface/EwkCorrections.h"

// forward declarations
class TFile;
class TH1D;

class getXsecInFiducial : public edm::EDAnalyzer
{

   public:
   
      //
      explicit getXsecInFiducial( const edm::ParameterSet& ) ;
      virtual ~getXsecInFiducial() {} // no need to delete ROOT stuff
                               // as it'll be deleted upon closing TFile
      
      virtual void analyze( const edm::Event&, const edm::EventSetup& ) ;
      virtual void beginJob() ;
      virtual void endJob() ;

   private:
   
     //
     std::string fOutputFileName ;
     std::string theSrc ;
     int         whichWeight;
     bool        isqqZZ;
     TFile*      fOutputFile ;
     
     // int         lookFor;

     TH1D*       mZ;
     TH1D*       pTZ ;	   
     TH1D*       nJets ;
     TH1D*       pTjet1 ;
     TH1D*       pTjet2 ;
     /* TH1D*       pTjet3 ;
     TH1D*       pTZ_lowmass ;	   
     TH1D*       nJets_lowmass ;
     TH1D*       pTjet1_lowmass ;
     TH1D*       pTjet2_lowmass ;  */
     TH1D*       mZZ ;
    
     GreaterByPt<reco::GenJet> pTComparatorJ_;
     GreaterByPt<reco::GenParticle> pTComparator_;
     int         nevent, neventpasslep;
     float       passlepgen, passlep, passjet, passmz, passmzz, passmjjloose, passall ;
     edm::EDGetTokenT< LHEEventProduct > lhep_token;
     edm::EDGetTokenT<std::vector<reco::GenParticle> > genp_token;
     edm::EDGetTokenT<edm::View<reco::Candidate> > genp_token2;
     edm::EDGetTokenT<std::vector<reco::GenJet> > genj_token;
     edm::EDGetTokenT<GenEventInfoProduct> genInfoToken;

     std::vector<std::vector<float> > ewkTable;
   
};

#endif
