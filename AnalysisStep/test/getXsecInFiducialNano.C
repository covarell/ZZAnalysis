// #include "external_cConstants.h"
#include <TSpline.h>
#include <TString.h>
#include <memory>

void getXsecInFiducialNano(){
  
 	gStyle->SetPalette(1);
	TFile *input_file;
  
        // find available samples  
	int nSamp = 0;  
	TString rootname[1000];

	ifstream parInput("getXsecInFiducialNano.txt");
        
	if (parInput.is_open()) {
	  while ( parInput.good() ) {
	    parInput >> rootname[nSamp]; 
            cout << nSamp << " " <<  rootname[nSamp] << endl; 
	    nSamp++;
	  }
	  parInput.close();
	} 

	//original variable declarations
		
	//new variable declarations
        const int nMaxJets = 50;
        const int nMaxLeps = 5000;
        int nGenJets;
        int nGenDressedLeptons;
	int GenDressedLepton_pdgId[nMaxLeps]; 
	int GenDressedLepton_statusFlags[nMaxLeps]; 
	float GenDressedLepton_pt[nMaxLeps];
	float GenDressedLepton_eta[nMaxLeps];
	float GenDressedLepton_phi[nMaxLeps];
	float GenDressedLepton_mass[nMaxLeps];
	float GenJet_pt[nMaxJets];
	float GenJet_eta[nMaxJets];
	float GenJet_phi[nMaxJets];
	float GenJet_mass[nMaxJets];
 
	int nevent = 0;
	int neventpasslep = 0;
	int passlep = 0.;
	int passlepgen = 0.;
	int passjet = 0.;
	int passmz = 0.;
	int passmzz = 0.;
	int passmjjloose = 0.;
	int passall = 0.;	
	int passall2 = 0.;	
	
	//for loop for different samples
	for(int is = 0; is < nSamp-1; is++){
	  
	  //print cycle
	  std::cout << endl << is << endl;
	  
          TFile* input_file = TFile::Open(rootname[is].Data()); 
	 	  
	  //tchain and add function for multiple input files
	  TChain *tqqzz= new TChain("Events");
	  tqqzz->Add(rootname[is].Data());
          
	  //original brach addresses
	  tqqzz->SetBranchAddress("nGenJet",&nGenJets);
	  /* tqqzz->SetBranchAddress("nGenDressedLepton",&nGenDressedLeptons);
	  tqqzz->SetBranchAddress("GenDressedLepton_pt",GenDressedLepton_pt);
	  tqqzz->SetBranchAddress("GenDressedLepton_pdgId",GenDressedLepton_pdgId);
	  tqqzz->SetBranchAddress("GenDressedLepton_eta",GenDressedLepton_eta);
	  tqqzz->SetBranchAddress("GenDressedLepton_phi",GenDressedLepton_phi);
	  tqqzz->SetBranchAddress("GenDressedLepton_mass",GenDressedLepton_mass);  */
	  tqqzz->SetBranchAddress("nGenPart",&nGenDressedLeptons);
	  tqqzz->SetBranchAddress("GenPart_pt",GenDressedLepton_pt);
	  tqqzz->SetBranchAddress("GenPart_statusFlags",GenDressedLepton_statusFlags);
	  tqqzz->SetBranchAddress("GenPart_pdgId",GenDressedLepton_pdgId);
	  tqqzz->SetBranchAddress("GenPart_eta",GenDressedLepton_eta);
	  tqqzz->SetBranchAddress("GenPart_phi",GenDressedLepton_phi);
	  tqqzz->SetBranchAddress("GenPart_mass",GenDressedLepton_mass);  
	  tqqzz->SetBranchAddress("GenJet_pt",GenJet_pt);
	  tqqzz->SetBranchAddress("GenJet_eta",GenJet_eta);
	  tqqzz->SetBranchAddress("GenJet_phi",GenJet_phi);
	  tqqzz->SetBranchAddress("GenJet_mass",GenJet_mass);
	
	  //new branch addresses
	  	  
	  //loop on entries
	  int enne = tqqzz->GetEntries();
	  
	  for(int i=0;i<enne;i++)
	    {
	    tqqzz->GetEntry(i);
	     
	    //if (whichWeight >= 0) weight *= EvtHandle->weights()[whichWeight].wgt/EvtHandle->originalXWGTUP();
	    nevent++;
  
	    TLorentzVector mu[4];
	    TLorentzVector jet[2];
            int iLep = 0;
            int theLepIndex[4];
	   
	    for(int iMu= 0; iMu < nGenDressedLeptons; iMu++){
              if ((abs(GenDressedLepton_pdgId[iMu]) == 11 || abs(GenDressedLepton_pdgId[iMu]) == 13) && (GenDressedLepton_statusFlags[iMu] >> 7) & 1)  {
		mu[iLep].SetPtEtaPhiM(GenDressedLepton_pt[iMu],GenDressedLepton_eta[iMu],GenDressedLepton_phi[iMu],GenDressedLepton_mass[iMu]);
	        // cout << GenDressedLepton_pt[iMu] << " " << GenDressedLepton_eta[iMu] << " " << GenDressedLepton_phi[iMu] << endl;
		theLepIndex[iLep] = iMu;
		iLep++;
		if (iLep == 4) break;
	      } 
	    }  	          
            // cout << "***" << endl;

            if (iLep < 4) continue;
	    TLorentzVector zzz = mu[0]+mu[1]+mu[2]+mu[3];
	    float mZZ = zzz.M();

	    //do Z1 and Z2
	    float mZ1, mZ2;
	    TLorentzVector z1; 
	    TLorentzVector z2(0.,0.,0.,0.000001);
	    int multiplyAllCharges = GenDressedLepton_pdgId[theLepIndex[0]]*GenDressedLepton_pdgId[theLepIndex[1]]*GenDressedLepton_pdgId[theLepIndex[2]]*GenDressedLepton_pdgId[theLepIndex[3]];  
	    if (multiplyAllCharges != 14641 && multiplyAllCharges != 28561 && multiplyAllCharges != 20449) continue;
   
	    if (multiplyAllCharges == 20449) {       //2e2mu
	      int theEle[2];
	      int iEle = 0;
	      for (int il=0; il < 4; il++) {
		if (abs(GenDressedLepton_pdgId[theLepIndex[il]]) == 11) {theEle[iEle] = il;    iEle++;}
	      }
	      if (iEle != 2) continue;
     
	      z1 = mu[theEle[0]] + mu[theEle[1]];      mZ1 = z1.M();
	      
	      for (int il=0; il < 4; il++) {
		if (theEle[0] != il && theEle[1] != il) z2 += mu[il];
	      }
	      mZ2 = z2.M();
	      
	    } else {                           //4e or 4mu
	      int thePos[2];
	      int iPos = 0;
	      for (int il=0; il < 4; il++) {
		if (GenDressedLepton_pdgId[theLepIndex[il]] > 0) {thePos[iPos] = il;    iPos++;}
	      }
	      if (iPos != 2) continue;
	      
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

            float weight = 1.;

	    if (mu[0].Perp() < 20. || fabs(mu[0].Eta()) > 2.5) continue;
	    if (mu[1].Perp() < 10. || fabs(mu[1].Eta()) > 2.5) continue;
	    if (mu[2].Perp() < 5.  || fabs(mu[2].Eta()) > 2.5) continue;
	    if (mu[3].Perp() < 5.  || fabs(mu[3].Eta()) > 2.5) continue;
	    passlep += weight;
	    passlepgen += weight;  
	    neventpasslep++;

	    int theJet = 0;
	    for(int iJet= 0; iJet < nGenJets; iJet++){
	      if( GenJet_pt[iJet] > 30. && fabs(GenJet_eta[iJet]) < 4.7) {     
		TLorentzVector jet4;
		jet4.SetPtEtaPhiM(GenJet_pt[iJet],GenJet_eta[iJet],GenJet_phi[iJet],GenJet_mass[iJet]);		 
		if (jet4.DeltaR(mu[0]) > 0.4 && jet4.DeltaR(mu[1]) > 0.4 && jet4.DeltaR(mu[2]) > 0.4 && jet4.DeltaR(mu[3]) > 0.4) { 
		  jet[theJet] = jet4;  theJet++;    if (theJet == 2) break;
		}
	      }
	    }
	    
	    if (theJet < 2) continue;     
	    passjet += weight;
	    
	    // cout << multiplyAllCharges << " " << mZ1 << " "  << mZ2 << endl;
	    if (mZ1 < 60 || mZ1 > 120.) continue;
	    if (mZ2 < 60 || mZ2 > 120.) continue;
	    passmz += weight;
	    
	    if (mZZ < 180.) continue;   
	    passmzz += weight;
	    
	    //Deta and mjj
	    z1 = jet[0] + jet[1];
	    if (z1.M() < 100.) continue;
	    passmjjloose += weight;
	    
	    if (fabs(jet[0].Eta() - jet[1].Eta()) < 2.4) continue;
	    if (z1.M() < 400.) continue;
	    
  
	    passall+=weight;
	    if (z1.M() < 1000.) continue;
	    
  
	    passall2+=weight;
   
	    
	  }//file loop  end
          input_file.Close();
	}       
		
	cout << "N_events = " << nevent << "\n";
	cout << "N_events(pass 4l) = " << neventpasslep << "\n";
	cout << "Sum_gen_weights(pass 4l) = " << passlepgen << "\n";
	cout << "Sum_weights(pass 4l) = " << passlep << "\n";
	cout << "Sum_weights(pass 4l+2j) = " << passjet << "\n";
	cout << "Sum_weights(pass 4l+2j+2Z) = " << passmz << "\n";
	cout << "Sum_weights(pass 4l+2j+2Z+mZZ) = " << passmzz << "\n";
	cout << "Sum_weights(pass 4l+2j+2Z+mZZ+mjj100) = " << passmjjloose << "\n";
	cout << "Sum_weights(pass VBS loose) = " << passall << "\n"; 	
	cout << "Sum_weights(pass VBS tight mjj) = " << passall2 << "\n"; 	
}



 
 

