#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <TMVA/Reader.h>
#include "reader.h"

using namespace std;
const Double_t GeV=1000;

// newly defined variables
Float_t score1;
Float_t score2;

Float_t dR_mumu;
Float_t dR_Kpi;
Float_t dR_JpsiKst;
Float_t dR_pipi;
Float_t dR_B0Ks;

TMVA::Reader* reader1_testOdd;
TMVA::Reader* reader1_testEven;
TMVA::Reader* reader2_testOdd;
TMVA::Reader* reader2_testEven;

void reduce(const char* infile = "../Bphy25_ntuple/channel34_0/data24_BphysDelayed.root", const char* outfile = "data24_red.root", bool massCut=true)
{
   TChain* oldtree = new TChain("BPHY25");
   oldtree->Add(infile);
   Init(oldtree);
   std::cout<<oldtree->GetEntries()<<std::endl;

   ULong64_t nentries = oldtree->GetEntries();

   reader1_testOdd = new TMVA::Reader("!Color:!Silent");
   reader1_testOdd->AddVariable("ld_Lxy", &ld_Lxy);
   reader1_testOdd->AddVariable("jx_Lxy", &jx_Lxy);
   reader1_testOdd->AddVariable("tq_rf_ratio", &tq_rf_ratio);
   reader1_testOdd->AddVariable("tq_rf_Lxy", &tq_rf_Lxy);
   reader1_testOdd->AddVariable("tq_rf_fitChi2NDF", &tq_rf_fitChi2NDF);
   reader1_testOdd->BookMVA("BDTG", "../mix/BDT1/weights_testOdd/TMVAClassification_BDTG.weights.xml");

   reader1_testEven = new TMVA::Reader("!Color:!Silent");
   reader1_testEven->AddVariable("ld_Lxy", &ld_Lxy);
   reader1_testEven->AddVariable("jx_Lxy", &jx_Lxy);
   reader1_testEven->AddVariable("tq_rf_ratio", &tq_rf_ratio);
   reader1_testEven->AddVariable("tq_rf_Lxy", &tq_rf_Lxy);
   reader1_testEven->AddVariable("tq_rf_fitChi2NDF", &tq_rf_fitChi2NDF);
   reader1_testEven->BookMVA("BDTG", "../mix/BDT1/weights_testEven/TMVAClassification_BDTG.weights.xml");

    //beg
            

   reader2_testOdd = new TMVA::Reader("!Color:!Silent");
   reader2_testOdd->AddVariable("pt_K_X", &pt_K_X);
   reader2_testOdd->AddVariable("pt_pi_X", &pt_pi_X);
   reader2_testOdd->AddVariable("dR_Kpi", &dR_Kpi);
   reader2_testOdd->AddVariable("dR_JpsiKst", &dR_JpsiKst);
   reader2_testOdd->AddVariable("pt_LRT_trk1", &pt_LRT_trk1);
   reader2_testOdd->AddVariable("pt_LRT_trk2", &pt_LRT_trk2);
   reader2_testOdd->AddVariable("jx_rf_pt", &jx_rf_pt);
   reader2_testOdd->AddVariable("ld_rf_pt", &ld_rf_pt);
   reader2_testOdd->AddVariable("dR_pipi", &dR_pipi);
   reader2_testOdd->AddVariable("tq_rf_pt", &tq_rf_pt);
   reader2_testOdd->AddVariable("x_rf_m", &x_rf_m);
   reader2_testOdd->BookMVA("BDTG", "../plot3b/BDT2/weights_testOdd/TMVAClassification_BDTG.weights.xml");

   reader2_testEven = new TMVA::Reader("!Color:!Silent");
   reader2_testEven->AddVariable("pt_K_X", &pt_K_X);
   reader2_testEven->AddVariable("pt_pi_X", &pt_pi_X);
   reader2_testEven->AddVariable("dR_Kpi", &dR_Kpi);
   reader2_testEven->AddVariable("dR_JpsiKst", &dR_JpsiKst);
   reader2_testEven->AddVariable("pt_LRT_trk1", &pt_LRT_trk1);
   reader2_testEven->AddVariable("pt_LRT_trk2", &pt_LRT_trk2);
   reader2_testEven->AddVariable("jx_rf_pt", &jx_rf_pt);
   reader2_testEven->AddVariable("ld_rf_pt", &ld_rf_pt);
   reader2_testEven->AddVariable("dR_pipi", &dR_pipi);
   reader2_testEven->AddVariable("tq_rf_pt", &tq_rf_pt);
   reader2_testEven->AddVariable("x_rf_m", &x_rf_m);
   reader2_testEven->BookMVA("BDTG", "../plot3b/BDT2/weights_testEven/TMVAClassification_BDTG.weights.xml");


    //end

   // Create a new file + a clone of old tree in new file
   TFile newfile(outfile, "recreate");
   TTree* newtree = oldtree->CloneTree(0);

   for (ULong64_t entry=0; entry<nentries; entry++) {
     oldtree->GetEntry(entry);

     // pre-selection
     if(jpsi_m/GeV>2.96 && jpsi_m/GeV<3.22 && x_rf_m/GeV>0.84 && x_rf_m/GeV<0.95
	&& jx_m_calc/GeV>5.180 && jx_m_calc/GeV<5.375 && tq_rf_fitChi2NDF<1.8
	&& ld_m/GeV>0.475 && ld_m/GeV<0.520 && tq_rf_ratio>0.20
	&& jx_Lxy>0.3
	&& trk_charge[0]*trk_charge[1]<0
	&& tq_rf_m/GeV > 5.832 && tq_rf_m/GeV < 5.848
	) {


       if(event_number%2 == 1) score1 = reader1_testOdd->EvaluateMVA("BDTG");
       else                    score1 = reader1_testEven->EvaluateMVA("BDTG");

       
       //baseline selection
       if(score1 > -0.4 ) {
	 //
        TLorentzVector tmpMu1; TLorentzVector tmpMu2;
      tmpMu1.SetPtEtaPhiM(mu_rf_pt[0],mu_rf_eta[0],mu_rf_phi[0],mu_rf_m[0]);
      tmpMu2.SetPtEtaPhiM(mu_rf_pt[1],mu_rf_eta[1],mu_rf_phi[1],mu_rf_m[1]);
      TLorentzVector tmpK; TLorentzVector tmpPi;
      tmpK.SetPtEtaPhiM(trk_rf_pt[0],trk_rf_eta[0],trk_rf_phi[0],trk_rf_m[0]);
      tmpPi.SetPtEtaPhiM(trk_rf_pt[1],trk_rf_eta[1],trk_rf_phi[1],trk_rf_m[1]);
      TLorentzVector tmpJpsi; TLorentzVector tmpKst;
      tmpJpsi.SetPtEtaPhiM(jpsi_rf_pt,jpsi_rf_eta,jpsi_rf_phi,jpsi_rf_m);
      tmpKst = tmpK+tmpPi;
      TLorentzVector tmpPi1; TLorentzVector tmpPi2;
      tmpPi1.SetPtEtaPhiM(trk_rf_pt[2],trk_rf_eta[2],trk_rf_phi[2],trk_rf_m[2]);
      tmpPi2.SetPtEtaPhiM(trk_rf_pt[3],trk_rf_eta[3],trk_rf_phi[3],trk_rf_m[3]);
      TLorentzVector tmpJX; TLorentzVector tmpKs;
      tmpJX.SetPtEtaPhiM(jx_rf_pt,jx_rf_eta,jx_rf_phi,jx_rf_m);
      tmpKs.SetPtEtaPhiM(ld_rf_pt,ld_rf_eta,ld_rf_phi,ld_rf_m);

      dR_mumu = tmpMu1.DeltaR(tmpMu2);
      dR_Kpi = tmpK.DeltaR(tmpPi);
      dR_JpsiKst = tmpJpsi.DeltaR(tmpKst);
      dR_pipi = tmpPi1.DeltaR(tmpPi2);
      dR_B0Ks = tmpJX.DeltaR(tmpKs);

           if(event_number%2 == 1) score2 = reader2_testOdd->EvaluateMVA("BDTG");
           else                    score2 = reader2_testEven->EvaluateMVA("BDTG");

   if(score2 > -0.5) newtree->Fill();
   
       }
     }
     if((entry+1)%100000==0) printf(" %llu entries processed...\n",entry+1);
   }
   std::cout<<newtree->GetEntries()<<std::endl;
   newfile.Write();
}