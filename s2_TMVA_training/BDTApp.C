#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "reader_mix.h"//use reader_mix.h or reader.h

using namespace TMVA;

const Double_t GeV=1000;
const Double_t PI=3.1415926536;

void BDTApp(const char* infile="mc_Bs1.root", const char* outfile="mc_Bs1_BDT1.root")
{
    TMVA::Tools::Instance();

    TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

    float Pt_mu1;
    float Pt_mu2;
    float Pt_K;
    float Pt_pi;
    float DR_Kpi;
    float Pt_pi1;
    float Pt_pi2;
    float Pt_B0;
    float Pt_Ks;
    float DR_B0Ks;
    float Pt_tq;
    float M_tq;
    float M_jpsi;
    float M_Kpi;
    float M_B0;
    float M_Ks;
    reader->AddVariable("Pt_mu1", &Pt_mu1);
    reader->AddVariable("Pt_mu2", &Pt_mu2);
    reader->AddVariable("Pt_K", &Pt_K);
    reader->AddVariable("Pt_pi", &Pt_pi);
    reader->AddVariable("DR_Kpi", &DR_Kpi);
    reader->AddVariable("Pt_pi1", &Pt_pi1);
    reader->AddVariable("Pt_pi2", &Pt_pi2);
    reader->AddVariable("Pt_B0", &Pt_B0);
    reader->AddVariable("Pt_Ks", &Pt_Ks);
    reader->AddVariable("DR_B0Ks", &DR_B0Ks);
    reader->AddVariable("Pt_tq", &Pt_tq);
    //reader->AddVariable("M_tq", &M_tq);
    reader->AddVariable("M_jpsi", &M_jpsi);
    reader->AddVariable("M_Kpi", &M_Kpi);
    reader->AddVariable("M_B0", &M_B0);
    reader->AddVariable("M_Ks", &M_Ks);

    reader->BookMVA("BDTG","dataset3/weights/BphyBDT1_BDTG.weights.xml");

    TChain* chain = new TChain("BPHY25");
    chain->Add(infile);

    Init(chain);
    TFile newfile(outfile, "recreate");
    TTree* newtree = chain->CloneTree(0);
    float BDTG1(0);
    newtree->Branch("BDTG1",&BDTG1,"BDTG1/F");
    std::cout << "--- Processing: " << chain->GetEntries() << " events" << std::endl;

    for (Long64_t ievt=0; ievt<chain->GetEntries();ievt++) {

        if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

        chain->GetEntry(ievt);

        TLorentzVector tmpK; TLorentzVector tmpPi;
	    tmpK.SetPtEtaPhiM(trk_rf_pt[0],trk_rf_eta[0],trk_rf_phi[0],trk_rf_m[0]);
	    tmpPi.SetPtEtaPhiM(trk_rf_pt[1],trk_rf_eta[1],trk_rf_phi[1],trk_rf_m[1]);
	    TLorentzVector tmpJpsi; TLorentzVector tmpKs;
	    tmpJpsi.SetPtEtaPhiM(jx_rf_pt,jx_rf_eta,jx_rf_phi,jx_rf_m);
	    tmpKs.SetPtEtaPhiM(ld_rf_pt,ld_rf_eta,ld_rf_phi,ld_rf_m);

        Pt_mu1 = pt_mu1/GeV;
        Pt_mu2 = pt_mu2/GeV;
        Pt_K = pt_K_X/GeV;
        Pt_pi = pt_pi_X/GeV;
        DR_Kpi = tmpK.DeltaR(tmpPi);
        Pt_pi1 = pt_LRT_trk1/GeV;
        Pt_pi2 = pt_LRT_trk2/GeV;
        Pt_B0 = jx_rf_pt/GeV;
        Pt_Ks = ld_rf_pt/GeV;
        DR_B0Ks = tmpJpsi.DeltaR(tmpKs);
        Pt_tq = tq_rf_pt/GeV;
        M_tq = tq_rf_m/GeV;
        M_jpsi = jpsi_m/GeV;
        M_Kpi = x_rf_m/GeV;
        M_B0 = jx_m_calc/GeV;
        M_Ks = ld_m/GeV;

        BDTG1 = reader->EvaluateMVA("BDTG");

        newtree->Fill();
    }
    newfile.Write();

}