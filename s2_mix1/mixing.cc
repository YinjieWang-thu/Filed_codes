#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include "reader.h"

using namespace std;
const Double_t GeV=1000;

ULong64_t Min(ULong64_t n1, ULong64_t n2) {
  if(n1<=n2) return n1;
  else return n2;
}

void reduce(const char* infile, const char* outfile)
{
   TChain* oldtree = new TChain("BPHY25");
   oldtree->Add(infile);
   Init(oldtree);
   std::cout<<oldtree->GetEntries()<<std::endl;

   ULong64_t nentries = oldtree->GetEntries();

   // Create a new file + a clone of old tree in new file
   TFile newfile(outfile, "recreate");
   TTree* newtree = oldtree->CloneTree(0);

   for (ULong64_t entry=0; entry<nentries; entry++) {
     oldtree->GetEntry(entry);

     if(jpsi_m/GeV>2.96 && jpsi_m/GeV<3.22 && x_rf_m/GeV>0.84 && x_rf_m/GeV<0.95
	&& jx_m_calc/GeV>5.180 && jx_m_calc/GeV<5.375 && tq_rf_fitChi2NDF<1.8
	&& ld_m/GeV>0.475 && ld_m/GeV<0.520 && tq_rf_ratio>0.20
	&& jx_Lxy>0.3
	&& trk_charge[0]*trk_charge[1]<0) {
       newtree->Fill();
     }
     if((entry+1)%100000==0) printf(" %llu entries processed...\n",entry+1);
   }
   std::cout<<newtree->GetEntries()<<std::endl;
   newfile.Write();
}

void mixing(const char* infile, const char* outfile)
{
   TChain* oldtree = new TChain("BPHY25");
   oldtree->Add(infile);
   Init(oldtree);
   std::cout<<oldtree->GetEntries()<<std::endl;

   ULong64_t nentries = oldtree->GetEntries();

   // Create a new file + a clone of old tree in new file
   TFile newfile(outfile, "recreate");
   TTree* newtree = new TTree("BPHY25","");

   newtree->Branch("tq_rf_m",&tq_rf_m,"tq_rf_m/F");
   newtree->Branch("tq_rf_pt",&tq_rf_pt,"tq_rf_pt/F");
   newtree->Branch("jx_Lxy",&jx_Lxy,"jx_Lxy/F");
   newtree->Branch("jx_rf_m",&jx_rf_m,"jx_rf_m/F");
   newtree->Branch("jx_rf_pt",&jx_rf_pt,"jx_rf_pt/F");
   newtree->Branch("jx_rf_eta",&jx_rf_eta,"jx_rf_eta/F");
   newtree->Branch("jx_rf_phi",&jx_rf_phi,"jx_rf_phi/F");
   newtree->Branch("jx_m_calc",&jx_m_calc,"jx_m_calc/F");
   newtree->Branch("jpsi_m",&jpsi_m,"jpsi_m/F");
   newtree->Branch("x_rf_m",&x_rf_m,"x_rf_m/F");
   newtree->Branch("ld_Lxy",&ld_Lxy,"ld_Lxy/F");
   newtree->Branch("ld_rf_m",&ld_rf_m,"ld_rf_m/F");
   newtree->Branch("ld_rf_pt",&ld_rf_pt,"ld_rf_pt/F");
   newtree->Branch("ld_rf_eta",&ld_rf_eta,"ld_rf_eta/F");
   newtree->Branch("ld_rf_phi",&ld_rf_phi,"ld_rf_phi/F");
   newtree->Branch("ld_m",&ld_m,"ld_m/F");
   newtree->Branch("pt_mu1",&pt_mu1,"pt_mu1/F");
   newtree->Branch("pt_mu2",&pt_mu2,"pt_mu2/F");
   newtree->Branch("pt_K_X",&pt_K_X,"pt_K_X/F");
   newtree->Branch("pt_pi_X",&pt_pi_X,"pt_pi_X/F");
   newtree->Branch("pt_LRT_trk1",&pt_LRT_trk1,"pt_LRT_trk1/F");
   newtree->Branch("pt_LRT_trk2",&pt_LRT_trk2,"pt_LRT_trk2/F");
   newtree->Branch("trk_rf_m",trk_rf_m,"trk_rf_m[4]/F");
   newtree->Branch("trk_rf_pt",trk_rf_pt,"trk_rf_pt[4]/F");
   newtree->Branch("trk_rf_eta",trk_rf_eta,"trk_rf_eta[4]/F");
   newtree->Branch("trk_rf_phi",trk_rf_phi,"trk_rf_phi[4]/F");

   Int_t interval = 100;
   std::vector<ULong64_t> list_of_used_entries;

   for (ULong64_t entry=0; entry<nentries-1; entry++) {
     std::vector<ULong64_t>::iterator iter = std::find(list_of_used_entries.begin(),list_of_used_entries.end(),entry);
     if(iter != list_of_used_entries.end()) {
       list_of_used_entries.erase(iter);
       continue;
     }

     oldtree->GetEntry(entry);

     float _tq_rf_m = tq_rf_m;
     float _tq_rf_pt = tq_rf_pt;
     float _jx_Lxy = jx_Lxy;
     float _jx_rf_m = jx_rf_m;
     float _jx_rf_pt = jx_rf_pt;
     float _jx_rf_eta = jx_rf_eta;
     float _jx_rf_phi = jx_rf_phi;
     float _jx_m_calc = jx_m_calc;
     float _jpsi_m = jpsi_m;
     float _x_rf_m = x_rf_m;
     float _ld_Lxy = ld_Lxy;
     float _ld_rf_m = ld_rf_m;
     float _ld_rf_pt = ld_rf_pt;
     float _ld_rf_eta = ld_rf_eta;
     float _ld_rf_phi = ld_rf_phi;
     float _ld_m = ld_m;
     float _pt_mu1 = pt_mu1;
     float _pt_mu2 = pt_mu2;
     float _pt_K_X = pt_K_X;
     float _pt_pi_X = pt_pi_X;
     float _pt_LRT_trk1 = pt_LRT_trk1;
     float _pt_LRT_trk2 = pt_LRT_trk2;
     float _trk_rf_m[4];
     float _trk_rf_pt[4];
     float _trk_rf_eta[4];
     float _trk_rf_phi[4];
     for(int i=0; i<4; i++) {
       _trk_rf_m[i] = trk_rf_m[i];
       _trk_rf_pt[i] = trk_rf_pt[i];
       _trk_rf_eta[i] = trk_rf_eta[i];
       _trk_rf_phi[i] = trk_rf_phi[i];
     }

     TLorentzVector v1; TLorentzVector v2;
     v1.SetPtEtaPhiM(_jx_rf_pt,_jx_rf_eta,_jx_rf_phi,_jx_rf_m);
     v2.SetPtEtaPhiM(_ld_rf_pt,_ld_rf_eta,_ld_rf_phi,_ld_rf_m);

     for (ULong64_t entry2=entry+1; entry2<Min(entry+interval+1,nentries); entry2++) {
       std::vector<ULong64_t>::iterator iter = std::find(list_of_used_entries.begin(),list_of_used_entries.end(),entry2);
       if(iter != list_of_used_entries.end()) continue;

       oldtree->GetEntry(entry2);

       TLorentzVector v3; TLorentzVector v4;
       v3.SetPtEtaPhiM(jx_rf_pt,jx_rf_eta,jx_rf_phi,jx_rf_m);
       v4.SetPtEtaPhiM(ld_rf_pt,ld_rf_eta,ld_rf_phi,ld_rf_m);

       Double_t mass14 = (v1+v4).M();
       Double_t mass23 = (v2+v3).M();

       Bool_t success = false;
       if(mass14/GeV<5.91) {
	 tq_rf_m = mass14;
	 tq_rf_pt = (v1+v4).Pt();
	 jx_Lxy = _jx_Lxy;
	 jx_rf_m = _jx_rf_m;
	 jx_rf_pt = _jx_rf_pt;
	 jx_rf_eta = _jx_rf_eta;
	 jx_rf_phi = _jx_rf_phi;
	 jx_m_calc = _jx_m_calc;
	 jpsi_m = _jpsi_m;
	 x_rf_m = _x_rf_m;
	 pt_mu1 = _pt_mu1;
	 pt_mu2 = _pt_mu2;
	 pt_K_X = _pt_K_X;
	 pt_pi_X = _pt_pi_X;
	 for(int i=0; i<=1; i++) {
	   trk_rf_m[i] = _trk_rf_m[i];
	   trk_rf_pt[i] = _trk_rf_pt[i];
	   trk_rf_eta[i] = _trk_rf_eta[i];
	   trk_rf_phi[i] = _trk_rf_phi[i];
	 }

	 newtree->Fill();
	 success = true;
       }
       if(mass23/GeV<5.91) {
	 if(success) oldtree->GetEntry(entry2);

	 tq_rf_m = mass23;
	 tq_rf_pt = (v2+v3).Pt();
	 ld_Lxy = _ld_Lxy;
	 ld_rf_m = _ld_rf_m;
	 ld_rf_pt = _ld_rf_pt;
	 ld_rf_eta = _ld_rf_eta;
	 ld_rf_phi = _ld_rf_phi;
	 ld_m = _ld_m;
	 pt_LRT_trk1 = _pt_LRT_trk1;
	 pt_LRT_trk2 = _pt_LRT_trk2;
	 for(int i=2; i<=3; i++) {
	   trk_rf_m[i] = _trk_rf_m[i];
	   trk_rf_pt[i] = _trk_rf_pt[i];
	   trk_rf_eta[i] = _trk_rf_eta[i];
	   trk_rf_phi[i] = _trk_rf_phi[i];
	 }

	 newtree->Fill();
	 success = true;
       }

       if(success) {
	 list_of_used_entries.push_back(entry2);
	 break;
       }
     }

     if((entry+1)%100000==0) printf(" %llu entries processed...\n",entry+1);
   }
   std::cout<<newtree->GetEntries()<<std::endl;
   //newtree->Print();
   newfile.Write();
}
