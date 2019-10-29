// -*- C++ -*-
//
// Package:    GeneratorInterface
// Class:      getXsecInFiducial
// 
//
// Description: Module to analyze Pythia-EvtGen HepMCproducts
//
//
// Original Author:  Roberto Covarelli
//         Created:  April 26, 2007
//

#include <iostream>
#include <fstream>
 
// #include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

// essentials !!!
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
 
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TObjArray.h"
 
#include "FWCore/Framework/interface/MakerMacros.h"

#include "ZZAnalysis/AnalysisStep/test/getXsecInFiducial.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "ZZAnalysis/AnalysisStep/src/kFactors.C"

using namespace edm;
using namespace std;
// using namespace HepMC;
 
getXsecInFiducial::getXsecInFiducial( const ParameterSet& pset )
   : fOutputFileName( pset.getUntrackedParameter<string>("HistOutFile",std::string("HPTRapidity.root")) ),
     theSrc( pset.getUntrackedParameter<string>("theSrc",std::string("source")) ), 
     whichWeight( pset.getUntrackedParameter<int>("whichWeight",-1)),
     isqqZZ( pset.getUntrackedParameter<bool>("isqqZZ",false) ),
     //lookFor( pset.getUntrackedParameter<int>("lookForGenProcID",0) ),
     fOutputFile(0)
{

  lhep_token = consumes< LHEEventProduct >(InputTag(theSrc));
  genp_token = consumes<std::vector<reco::GenParticle> >(InputTag("prunedGenParticles"));
  genp_token2 = consumes<edm::View<reco::Candidate> >(edm::InputTag("prunedGenParticles"));
  genj_token = consumes<std::vector<reco::GenJet> >(InputTag("slimmedGenJets"));
  genInfoToken = consumes<GenEventInfoProduct>(edm::InputTag("generator"));

  std::string fipPath;
  edm::FileInPath ewkFIP("ZZAnalysis/AnalysisStep/data/kfactors/ZZ_EwkCorrections.dat");
  fipPath=ewkFIP.fullPath();
  ewkTable = EwkCorrections::readFile_and_loadEwkTable(fipPath.data());

}

void getXsecInFiducial::beginJob()
{
 
   nevent = 0;
   neventpasslep = 0;
   passlep = 0.;
   passlepgen = 0.;
   passjet = 0.;
   passmz = 0.;
   passmzz = 0.;
   passmjjloose = 0.;
   passall = 0.;

   fOutputFile   = new TFile( fOutputFileName.c_str(), "RECREATE" ) ;
   // fHist2muMass  = new TH1D(  "Hist2muMass", "2-mu inv. mass", 100,  60., 120. ) ;  
   mZ = new TH1D("mZ", "invariant mass of Z", 90, 100., 1000.) ;
   pTZ = new TH1D("pTZ", "pT of Z", 90, 0., 900.) ;
   nJets = new TH1D("nJets", "# of GenJets with pT > 30", 7, -0.5, 6.5) ; 
   pTjet1 = new TH1D("pTjet1", "pT of leading GenJet", 18, 10., 1000.) ;
   pTjet2 = new TH1D("pTjet2", "pT of second leading GenJet", 18, 10., 1000.) ;
   /* pTjet3 = new TH1D("pTjet3", "pT of third leading GenJet", 18, 10., 100.) ;
   		 
   pTZ_lowmass = new TH1D("pTZ_lowmass", "pT of Z boson", 21, 0., 140.) ;
   nJets_lowmass = new TH1D("nJets_lowmass", "# of GenJets with pT > 20", 5, -0.5, 4.5) ; 
   pTjet1_lowmass = new TH1D("pTjet1_lowmass", "pT of leading GenJet", 18, 10., 100.) ;
   pTjet2_lowmass = new TH1D("pTjet2_lowmass", "pT of second leading GenJet", 18, 10., 100.) ;
   pTjet3_lowmass = new TH1D("pTjet3_lowmass", "pT of third leading GenJet", 18, 10., 100.) ;  */
   mZZ = new TH1D("mZZ", "invariant mass of 4l", 90, 100., 1000.) ;
   mZ->Sumw2(); 
   pTZ->Sumw2();
   nJets->Sumw2();
   pTjet1->Sumw2();
   pTjet2->Sumw2();
   /* pTjet3->Sumw2();
   
   pTZ_lowmass->Sumw2();
   nJets_lowmass->Sumw2(); 
   pTjet1_lowmass->Sumw2();
   pTjet2_lowmass->Sumw2();
   pTjet3_lowmass->Sumw2();  */
   mZZ->Sumw2();
   return ;
}
 
void getXsecInFiducial::analyze( const Event& e, const EventSetup& )
{

   edm::Handle< LHEEventProduct > EvtHandle ;
   e.getByToken( lhep_token , EvtHandle ) ;

   float weight = EvtHandle->hepeup().XWGTUP;
   if (!isqqZZ) weight = 1.;
   if (whichWeight >= 0) weight *= EvtHandle->weights()[whichWeight].wgt/EvtHandle->originalXWGTUP();
   nevent++;
  
   edm::Handle<std::vector<reco::GenParticle> > genParticles;
   e.getByToken(genp_token, genParticles);
   edm::Handle<edm::View<reco::Candidate> > genParticles2;
   e.getByToken(genp_token2, genParticles2);
   TLorentzVector mu[4];
   TLorentzVector jet[2];
   TLorentzVector gamma;
   int iMu = 0;
   int iJet = 0;
   reco::GenParticleCollection* genLepGood = new reco::GenParticleCollection();
   reco::GenParticleCollection* genLepSorted = new reco::GenParticleCollection();

   edm::Handle<reco::GenJetCollection> jetsgen;
   e.getByToken(genj_token, jetsgen);
   // const reco::GenJetCollection genJets = jetsgen.product();
   reco::GenJetCollection* genJetsSorted = new reco::GenJetCollection();

   edm::Handle<GenEventInfoProduct> genInfo;
   e.getByToken(genInfoToken, genInfo);
   GenEventInfoProduct genInfoP = *(genInfo.product());

   for(std::vector<reco::GenParticle>::const_iterator genParticle=genParticles->begin(); genParticle!=genParticles->end(); ++genParticle){
     // last in the collection
     if( genParticle->status()==1 && (abs(genParticle->pdgId())==11 || abs(genParticle->pdgId())==13)) 
       genLepSorted->push_back(*genParticle); 
   }

   if (genLepSorted->size() < 4) return;
   std::sort(genLepSorted->begin(), genLepSorted->end(), pTComparator_);

   for(std::vector<reco::GenParticle>::const_iterator genParticle=genLepSorted->begin(); genParticle!=genLepSorted->end(); ++genParticle){
     mu[iMu].SetPxPyPzE(genParticle->px(),genParticle->py(),
			genParticle->pz(),genParticle->energy());
     for(std::vector<reco::GenParticle>::const_iterator genParticle2=genParticles->begin(); genParticle2!=genParticles->end(); ++genParticle2){
       if( genParticle2->status()==1 && genParticle2->pdgId()==22) {
	 gamma.SetPxPyPzE(genParticle2->px(),genParticle2->py(),
			  genParticle2->pz(),genParticle2->energy());
	 if (gamma.DeltaR(mu[iMu]) < 0.1) mu[iMu].SetPxPyPzE(genParticle->px()+genParticle2->px(),genParticle->py()+genParticle2->py(),
							     genParticle->pz()+genParticle2->pz(),genParticle->energy()+genParticle2->energy());
       }
     }
     genLepGood->push_back(*genParticle); 
     iMu++;
     if (iMu == 4) break;
     
   } 

   TLorentzVector zzz = mu[0]+mu[1]+mu[2]+mu[3];
   float mZZ = zzz.M();

   //do Z1 and Z2
   float mZ1, mZ2;
   TLorentzVector z1; 
   TLorentzVector z2(0.,0.,0.,0.000001);
   int multiplyAllCharges = genLepSorted->at(0).pdgId()*genLepSorted->at(1).pdgId()*genLepSorted->at(2).pdgId()*genLepSorted->at(3).pdgId();  
   if (multiplyAllCharges != 14641 && multiplyAllCharges != 28561 && multiplyAllCharges != 20449) return;
   
   if (multiplyAllCharges == 20449) {       //2e2mu
     int theEle[2];
     int iEle = 0;
     for (int il=0; il < 4; il++) {
       if (abs(genLepGood->at(il).pdgId()) == 11) {theEle[iEle] = il;    iEle++;}
     }
     if (iEle != 2) return;
     
     z1 = mu[theEle[0]] + mu[theEle[1]];      mZ1 = z1.M();

     for (int il=0; il < 4; il++) {
       if (theEle[0] != il && theEle[1] != il) z2 += mu[il];
     }
     mZ2 = z2.M();

   } else {                           //4e or 4mu
     int thePos[2];
     int iPos = 0;
     for (int il=0; il < 4; il++) {
       if (genLepGood->at(il).pdgId() > 0) {thePos[iPos] = il;    iPos++;}
     }
     if (iPos != 2) return;
     
     int theNeg[2];
     iPos = 0;
     for (int il=0; il < 4; il++) {
       if (thePos[0] != il && thePos[1] != il) {theNeg[iPos] = il;    iPos++;}
     }
     
     mZ1 = 99999.;
     z1 = mu[thePos[0]] + mu[theNeg[0]];
     if (fabs(z1.M() - 91.12) < fabs(mZ1 - 91.12)) {
       mZ1 = z1.M();   z2 = mu[thePos[1]] + mu[theNeg[1]];  mZ2 = z2.M();
     }
     z1 = mu[thePos[0]] + mu[theNeg[1]];
     if (fabs(z1.M() - 91.12) < fabs(mZ1 - 91.12)) {
       mZ1 = z1.M();   z2 = mu[thePos[0]] + mu[theNeg[1]];  mZ2 = z2.M();
     }
     z1 = mu[thePos[1]] + mu[theNeg[0]];
     if (fabs(z1.M() - 91.12) < fabs(mZ1 - 91.12)) {
       mZ1 = z1.M();    z2 = mu[thePos[1]] + mu[theNeg[0]];   mZ2 = z2.M();
     }
     z1 = mu[thePos[1]] + mu[theNeg[1]];
     if (fabs(z1.M() - 91.12) < fabs(mZ1 - 91.12)) {
       mZ1 = z1.M();   z2 = mu[thePos[0]] + mu[theNeg[0]];   mZ2 = z2.M();
     }
   }

   float genweight = weight;

   if (isqqZZ){           // apply mZZ dependent k-factors 
     bool sameflavor=(genLepGood->at(0).pdgId()*genLepGood->at(1).pdgId() == genLepGood->at(2).pdgId()*genLepGood->at(3).pdgId());
     float KFactor_QCD_qqZZ = kfactor_qqZZ_qcd_M(mZZ, (sameflavor) ? 1 : 2, 2) / kfactor_qqZZ_qcd_M(mZZ, (sameflavor) ? 1 : 2, 1);
     
     // Calculate NLO EWK K factors for qqZZ    
     float KFactor_EW_qqZZ = EwkCorrections::getEwkCorrections(genParticles2, ewkTable, genInfoP, z1, z2);
     weight *= KFactor_QCD_qqZZ*KFactor_EW_qqZZ;
   }
   
   if (mu[0].Perp() < 20. || fabs(mu[0].Eta()) > 2.5) return;
   if (mu[1].Perp() < 10. || fabs(mu[1].Eta()) > 2.5) return;
   if (mu[2].Perp() < 5.  || fabs(mu[2].Eta()) > 2.5) return;
   if (mu[3].Perp() < 5.  || fabs(mu[3].Eta()) > 2.5) return;
   passlep += weight;
   passlepgen += genweight;  
   neventpasslep++;

   for(reco::GenJetCollection::const_iterator genJet=jetsgen->begin(); genJet!=jetsgen->end(); ++genJet){
     if( genJet->pt() > 30. && fabs(genJet->eta()) < 4.7) {     
       TLorentzVector jet4;
       jet4.SetPxPyPzE(genJet->px(),genJet->py(),
		       genJet->pz(),genJet->energy());
       if (jet4.DeltaR(mu[0]) > 0.4 && jet4.DeltaR(mu[1]) > 0.4 && jet4.DeltaR(mu[2]) > 0.4 && jet4.DeltaR(mu[3]) > 0.4) { 
	 genJetsSorted->push_back(*genJet); 
	 
       }
     }
   }

   if (genJetsSorted->size() < 2) return;     
   passjet += weight;
     
   std::sort(genJetsSorted->begin(), genJetsSorted->end(), pTComparatorJ_);

   for(reco::GenJetCollection::const_iterator genJet=genJetsSorted->begin(); genJet!=genJetsSorted->end(); ++genJet){
     jet[iJet].SetPxPyPzE(genJet->px(),genJet->py(),
			  genJet->pz(),genJet->energy());
     iJet++;
     if (iJet == 2) break;
   }
     
   // cout << multiplyAllCharges << " " << mZ1 << " "  << mZ2 << endl;
   if (mZ1 < 60 || mZ1 > 120.) return;
   if (mZ2 < 60 || mZ2 > 120.) return;
   passmz += weight;
   
   if (mZZ < 180.) return;   
   passmzz += weight;

   //Deta and mjj
   z1 = jet[0] + jet[1];
   if (z1.M() < 100.) return;
   passmjjloose += weight;
   
   if (fabs(genJetsSorted->at(0).eta() - genJetsSorted->at(1).eta()) < 2.4) return;
   if (z1.M() < 400.) return;
   
   passall+=weight;

   return ;   
}

void getXsecInFiducial::endJob()
{
  TObjArray Hlist(0);
  Hlist.Add(mZ);
  Hlist.Add(pTZ);	   
  Hlist.Add(nJets) ;
  Hlist.Add(pTjet1);
  Hlist.Add(pTjet2); 
  // Hlist.Add(pTjet3) ;
  /* Hlist.Add(pTZ_lowmass);	   
  Hlist.Add(nJets_lowmass) ;
  Hlist.Add(pTjet1_lowmass);
  Hlist.Add(pTjet2_lowmass); 
  Hlist.Add(pTjet3_lowmass) ; */
  Hlist.Add(mZZ);
  fOutputFile->cd() ;
  Hlist.Write() ;
  fOutputFile->Close() ;
  cout << "N_events = " << nevent << "\n";
  cout << "N_events(pass 4l) = " << neventpasslep << "\n";
  cout << "Sum_gen_weights(pass 4l) = " << passlepgen << "\n";
  cout << "Sum_weights(pass 4l) = " << passlep << "\n";
  cout << "Sum_weights(pass 4l+2j) = " << passjet << "\n";
  cout << "Sum_weights(pass 4l+2j+2Z) = " << passmz << "\n";
  cout << "Sum_weights(pass 4l+2j+2Z+mZZ) = " << passmzz << "\n";
  cout << "Sum_weights(pass 4l+2j+2Z+mZZ+mjj100) = " << passmjjloose << "\n";
  cout << "Sum_weights(pass all) = " << passall << "\n"; 
  return ;
}
 
DEFINE_FWK_MODULE(getXsecInFiducial);
