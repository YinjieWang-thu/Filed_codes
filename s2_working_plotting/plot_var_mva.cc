#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TMinuit.h"
#include "THStack.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLorentzVector.h"
#include "TLine.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TArrow.h"
#include <TMVA/Reader.h>
#include "reader.h"
#define NN 26

const Double_t GeV=1000;
const Double_t PI=3.1415926536;

void SetMax(TH1* h1, TH1* h2, Double_t scale=1.0) {
  h1->SetMaximum(scale*TMath::Max(h1->GetMaximum(),h2->GetMaximum()));
  h2->SetMaximum(scale*TMath::Max(h1->GetMaximum(),h2->GetMaximum()));
}

float DR(float eta1, float phi1, float eta2, float phi2) {
  float dphi = fabs(phi1-phi2);
  if(dphi>M_PI) dphi = 2*M_PI-dphi;
  float deta = fabs(eta1-eta2);
  return sqrt(dphi*dphi+deta*deta);
}

// newly defined variables
Float_t dR_mumu;
Float_t dR_Kpi;
Float_t dR_JpsiKst;
Float_t dR_pipi;
Float_t dR_B0Ks;
Float_t score2;

// config variable
Bool_t subtractBkg = 0;

TMVA::Reader* reader2_testOdd;
TMVA::Reader* reader2_testEven;

void plot_var_mva() {
  TChain* ch[4] = {nullptr, nullptr, nullptr, nullptr};

  // Bs1
  ch[0] = new TChain("BPHY25");
  ch[0]->Add("../mix/ntuple/mc20a_Bs1_802750_baseline.root");
  ch[0]->Add("../mix/ntuple/mc20a_Bs1_802751_baseline.root");
  ch[0]->Add("../mix/ntuple/mc20d_Bs1_802750_baseline.root");
  ch[0]->Add("../mix/ntuple/mc20d_Bs1_802751_baseline.root");
  ch[0]->Add("../mix/ntuple/mc20e_Bs1_802750_baseline.root");
  ch[0]->Add("../mix/ntuple/mc20e_Bs1_802751_baseline.root");
  ch[0]->Add("../mix/ntuple/mc23a_Bs1_802750_baseline.root");
  ch[0]->Add("../mix/ntuple/mc23a_Bs1_802751_baseline.root");
  ch[0]->Add("../mix/ntuple/mc23d_Bs1_802750_baseline.root");
  ch[0]->Add("../mix/ntuple/mc23d_Bs1_802751_baseline.root");
  ch[0]->Add("../mix/ntuple/mc23e_Bs1_802750_baseline.root");
  ch[0]->Add("../mix/ntuple/mc23e_Bs1_802751_baseline.root");
  Init(ch[0]);

  // Bs2
  ch[1] = new TChain("BPHY25");
  ch[1]->Add("../mix/ntuple/mc20a_Bs2_802395_baseline.root");
  ch[1]->Add("../mix/ntuple/mc20a_Bs2_802396_baseline.root");
  ch[1]->Add("../mix/ntuple/mc20d_Bs2_802395_baseline.root");
  ch[1]->Add("../mix/ntuple/mc20d_Bs2_802396_baseline.root");
  ch[1]->Add("../mix/ntuple/mc20e_Bs2_802395_baseline.root");
  ch[1]->Add("../mix/ntuple/mc20e_Bs2_802396_baseline.root");
  ch[1]->Add("../mix/ntuple/mc23a_Bs2_802395_baseline.root");
  ch[1]->Add("../mix/ntuple/mc23a_Bs2_802396_baseline.root");
  ch[1]->Add("../mix/ntuple/mc23d_Bs2_802395_baseline.root");
  ch[1]->Add("../mix/ntuple/mc23d_Bs2_802396_baseline.root");
  ch[1]->Add("../mix/ntuple/mc23e_Bs2_802395_baseline.root");
  ch[1]->Add("../mix/ntuple/mc23e_Bs2_802396_baseline.root");
  Init(ch[1]);

  // data
  ch[2] = new TChain("BPHY25");
  ch[2]->Add("../mix/ntuple/data15_Main_baseline.root");
  ch[2]->Add("../mix/ntuple/data16_All_baseline.root");
  ch[2]->Add("../mix/ntuple/data17_All_baseline.root");
  ch[2]->Add("../mix/ntuple/data18_All_baseline.root");
  ch[2]->Add("../mix/ntuple/data22_BphysDelayed_baseline.root");
  ch[2]->Add("../mix/ntuple/data23_BphysDelayed_baseline.root");
  ch[2]->Add("../mix/ntuple/data24_BphysDelayed_baseline.root");
  Init(ch[2]);

  // mixing
  ch[3] = new TChain("BPHY25");
  ch[3]->Add("../mix/ntuple/data15_Main_mix.root");
  ch[3]->Add("../mix/ntuple/data16_All_mix.root");
  ch[3]->Add("../mix/ntuple/data17_All_mix.root");
  ch[3]->Add("../mix/ntuple/data18_All_mix.root");
  ch[3]->Add("../mix/ntuple/data22_BphysDelayed_mix.root");
  ch[3]->Add("../mix/ntuple/data23_BphysDelayed_mix.root");
  ch[3]->Add("../mix/ntuple/data24_BphysDelayed_mix.root");

  ch[3]->SetBranchAddress("event_number",&event_number);
  ch[3]->SetBranchAddress("tq_rf_m",&tq_rf_m);
  ch[3]->SetBranchAddress("tq_rf_pt",&tq_rf_pt);
  ch[3]->SetBranchAddress("jx_Lxy",&jx_Lxy);
  ch[3]->SetBranchAddress("jx_rf_m",&jx_rf_m);
  ch[3]->SetBranchAddress("jx_rf_pt",&jx_rf_pt);
  ch[3]->SetBranchAddress("jx_rf_eta",&jx_rf_eta);
  ch[3]->SetBranchAddress("jx_rf_phi",&jx_rf_phi);
  ch[3]->SetBranchAddress("jx_m_calc",&jx_m_calc);
  ch[3]->SetBranchAddress("jpsi_rf_m",&jpsi_rf_m);
  ch[3]->SetBranchAddress("jpsi_rf_pt",&jpsi_rf_pt);
  ch[3]->SetBranchAddress("jpsi_rf_eta",&jpsi_rf_eta);
  ch[3]->SetBranchAddress("jpsi_rf_phi",&jpsi_rf_phi);
  ch[3]->SetBranchAddress("jpsi_m",&jpsi_m);
  ch[3]->SetBranchAddress("x_rf_m",&x_rf_m);
  ch[3]->SetBranchAddress("ld_Lxy",&ld_Lxy);
  ch[3]->SetBranchAddress("ld_rf_m",&ld_rf_m);
  ch[3]->SetBranchAddress("ld_rf_pt",&ld_rf_pt);
  ch[3]->SetBranchAddress("ld_rf_eta",&ld_rf_eta);
  ch[3]->SetBranchAddress("ld_rf_phi",&ld_rf_phi);
  ch[3]->SetBranchAddress("ld_m",&ld_m);
  ch[3]->SetBranchAddress("pt_mu1",&pt_mu1);
  ch[3]->SetBranchAddress("pt_mu2",&pt_mu2);
  ch[3]->SetBranchAddress("pt_K_X",&pt_K_X);
  ch[3]->SetBranchAddress("pt_pi_X",&pt_pi_X);
  ch[3]->SetBranchAddress("pt_LRT_trk1",&pt_LRT_trk1);
  ch[3]->SetBranchAddress("pt_LRT_trk2",&pt_LRT_trk2);
  ch[3]->SetBranchAddress("mu_rf_m", mu_rf_m);
  ch[3]->SetBranchAddress("mu_rf_pt", mu_rf_pt);
  ch[3]->SetBranchAddress("mu_rf_eta", mu_rf_eta);
  ch[3]->SetBranchAddress("mu_rf_phi", mu_rf_phi);
  ch[3]->SetBranchAddress("trk_rf_m", trk_rf_m);
  ch[3]->SetBranchAddress("trk_rf_pt", trk_rf_pt);
  ch[3]->SetBranchAddress("trk_rf_eta", trk_rf_eta);
  ch[3]->SetBranchAddress("trk_rf_phi", trk_rf_phi);

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
  reader2_testOdd->BookMVA("BDTG", "BDT2/weights_testOdd/TMVAClassification_BDTG.weights.xml");

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
  reader2_testEven->BookMVA("BDTG", "BDT2/weights_testEven/TMVAClassification_BDTG.weights.xml");

  char str[100];
  TH1F* h[30][5];
  TH1F* hmix[30];
  TH1F* htot[30];
  TH1F* hratio[30];
  const char* xtitle[] = {"p_{T}^{#mu_{1}} [GeV]",
		    "p_{T}^{#mu_{2}} [GeV]",
		    "p_{T}^{K} [GeV]",
		    "p_{T}^{#pi} [GeV]",
		    "#DeltaR(#mu,#mu)",
		    "#DeltaR(K,#pi)",
		    "#DeltaR(J/#psi,K^{*})",
		    "p_{T}^{#pi_{1}}(K_{S}) [GeV]",
		    "p_{T}^{#pi_{2}}(K_{S}) [GeV]",
		    "p_{T}^{B^{0}} [GeV]",
		    "p_{T}^{K_{S}} [GeV]",
		    "#DeltaR(#pi,#pi)",
		    "#DeltaR(B^{0},K_{S})",
		    "p_{T}^{B^{0}+K_{S}} [GeV]",
		    "m_{B^{0}+K_{S}} [GeV]",
		    "m_{J/#psi} [GeV]",
		    "m_{K#pi} [GeV]",
		    "m_{B^{0}} [GeV]",
		    "m_{K_{S}} [GeV]",
		    "L_{xy}^{K_{S}} [mm]",
		    "L_{xy}^{B^{0}} [mm]",
		    "p_{T}^{B^{0}+K_{S}}/#Sigmap_{T}^{PV}",
		    "L_{xy}^{B^{0}+K_{S}} [mm]",
                    "#chi^{2}/N",
		    "BDTG2",
		    "m_{B^{0}+K_{S}} [GeV]"
  };
  for(Int_t i=0; i<5; i++) {
    sprintf(str,"h1_%d",i+1);
    h[0][i] = new TH1F(str,"",30,0,60); // pt(mu1)
    sprintf(str,"h2_%d",i+1);
    h[1][i] = new TH1F(str,"",30,0,30); // pt(mu2)
    sprintf(str,"h3_%d",i+1);
    h[2][i] = new TH1F(str,"",30,0,15); // pt(K)
    sprintf(str,"h4_%d",i+1);
    h[3][i] = new TH1F(str,"",30,0,15); // pt(pi)
    sprintf(str,"h5_%d",i+1);
    h[4][i] = new TH1F(str,"",20,0,1.0); // dR(mu,mu)
    sprintf(str,"h6_%d",i+1);
    h[5][i] = new TH1F(str,"",20,0,1.0); // dR(K,pi)
    sprintf(str,"h7_%d",i+1);
    h[6][i] = new TH1F(str,"",20,0,1); // dR(Jpsi,Kstar)
    sprintf(str,"h8_%d",i+1);
    h[7][i] = new TH1F(str,"",50,0,10); // pt(pi1)
    sprintf(str,"h9_%d",i+1);
    h[8][i] = new TH1F(str,"",50,0,5); // pt(pi2)
    sprintf(str,"h10_%d",i+1);
    h[9][i] = new TH1F(str,"",50,0,100); // pt(B0)
    sprintf(str,"h11_%d",i+1);
    h[10][i] = new TH1F(str,"",50,0,10); // pt(Ks)
    sprintf(str,"h12_%d",i+1);
    h[11][i] = new TH1F(str,"",30,0,1.2); // dR(pi,pi)
    sprintf(str,"h13_%d",i+1);
    h[12][i] = new TH1F(str,"",40,0,0.4); // dR(B0,Ks)
    sprintf(str,"h14_%d",i+1);
    h[13][i] = new TH1F(str,"",25,0,100); // pt(B0+Ks)
    sprintf(str,"h15_%d",i+1);
    h[14][i] = new TH1F(str,"",75,5.76,5.91); // B0+Ks mass
    sprintf(str,"h16_%d",i+1);
    h[15][i] = new TH1F(str,"",60,2.8,3.4); // Jpsi mass
    sprintf(str,"h17_%d",i+1);
    h[16][i] = new TH1F(str,"",37,0.70,1.07); // K* mass
    sprintf(str,"h18_%d",i+1);
    h[17][i] = new TH1F(str,"",60,5.08,5.48); // B0 mass
    sprintf(str,"h19_%d",i+1);
    h[18][i] = new TH1F(str,"",80,0.4,0.6); // Ks mass
    sprintf(str,"h20_%d",i+1);
    h[19][i] = new TH1F(str,"",76,5,400); // Lxy(Ks)
    sprintf(str,"h21_%d",i+1);
    h[20][i] = new TH1F(str,"",60,0,15); // Lxy(B0)
    sprintf(str,"h22_%d",i+1);
    h[21][i] = new TH1F(str,"",40,0,1); // pt ratio
    sprintf(str,"h23_%d",i+1);
    h[22][i] = new TH1F(str,"",50,-6.5,3.5); // Lxy(B0+Ks)
    sprintf(str,"h24_%d",i+1);
    h[23][i] = new TH1F(str,"",25,0,5.0); // chi2/N
    sprintf(str,"h25_%d",i+1);
    h[24][i] = new TH1F(str,"",40,-1,1); // BDT score
    sprintf(str,"h26_%d",i+1);
    h[25][i] = new TH1F(str,"",70,5.76,5.90); // B0+Ks mass
  }
  for(Int_t i=0; i<NN; i++) {
    for(Int_t j=0; j<5; j++) h[i][j]->Sumw2(true);
    sprintf(str,"hratio%d",i+1);
    hratio[i] = new TH1F(str,"",h[i][0]->GetNbinsX(),h[i][0]->GetXaxis()->GetXmin(),h[i][0]->GetXaxis()->GetXmax());
    sprintf(str,"hmix%d",i+1);
    hmix[i] = new TH1F(str,"",h[i][0]->GetNbinsX(),h[i][0]->GetXaxis()->GetXmin(),h[i][0]->GetXaxis()->GetXmax());
    hmix[i]->Sumw2(true);
    sprintf(str,"htot%d",i+1);
    htot[i] = new TH1F(str,"",h[i][0]->GetNbinsX(),h[i][0]->GetXaxis()->GetXmin(),h[i][0]->GetXaxis()->GetXmax());
    htot[i]->Sumw2(true);
  }

  for(Int_t ich=0; ich<3; ich++) {
    if(!ch[ich]) continue;
    Long64_t nentries = ch[ich]->GetEntries();
    printf("%llu entries to be processed...\n",nentries);
    for(Long64_t entry=0; entry<nentries; entry++) {

      ch[ich]->GetEntry(entry);

      int idx(-1);
      if(ich==0) idx = 0; // Bs1
      else if(ich==1) {
	if(tq_rf_m/GeV<5.815) idx = 1; // Bs2 low peak
	else idx = 2; // Bs2 high peak
      }
      else if(ich==2) {
	idx = 3;
      }
      else continue;

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

      Float_t wt = 1;

      if(idx<=2) { // Bs2 high peak signal
	if(idx==0)      wt *= 0.00125;
	else if(idx==1) wt *= 0.0105;
	else if(idx==2) wt *= 0.77;

	Float_t tmp = pt_mu2/GeV;
	if(tmp>15) tmp = 15;
	if(tmp<6) wt *= 0.108234+0.102635*tmp;
	else wt *= 5.11551-0.961954*tmp+0.0770815*pow(tmp,2)-0.00203477*pow(tmp,3);

	tmp = pt_K_X/GeV;
	if(tmp>7) tmp = 7;
	wt *= 4.15108-2.11688*tmp+0.446349*pow(tmp,2)-0.0303387*pow(tmp,3);

	tmp = tq_rf_pt/GeV;
	if(tmp<15) tmp = 15; if(tmp>85) tmp = 85;
	wt *= 0.976235+0.0393772*tmp-0.00103122*pow(tmp,2)+6.28236e-06*pow(tmp,3);

	tmp = tq_rf_ratio;
	if(tmp<0.2) tmp = 0.2; if(tmp>0.7) tmp = 0.7;
	wt *= 1.52702+6.38684*tmp-23.9037*pow(tmp,2)+17.2831*pow(tmp,3);

	tmp = tq_rf_fitChi2NDF;
	if(tmp>1.8) tmp = 1.8;
	wt *= 0.572951+0.42142*tmp;

	tmp = dR_B0Ks;
	if(tmp<0.05) wt *= 2.88144-105.055*tmp+1886.1*pow(tmp,2)-10725.7*pow(tmp,3);
      }

      // mass region cuts
      if( idx<=3
	  && (tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
	  ) {
	h[0][idx]->Fill(pt_mu1/GeV,wt);
	h[1][idx]->Fill(pt_mu2/GeV,wt);
	h[2][idx]->Fill(pt_K_X/GeV,wt);
	h[3][idx]->Fill(pt_pi_X/GeV,wt);
	h[4][idx]->Fill(dR_mumu,wt);
	h[5][idx]->Fill(dR_Kpi,wt);
	h[6][idx]->Fill(dR_JpsiKst,wt);
	h[7][idx]->Fill(pt_LRT_trk1/GeV,wt);
	h[8][idx]->Fill(pt_LRT_trk2/GeV,wt);
	h[9][idx]->Fill(jx_rf_pt/GeV,wt);
	h[10][idx]->Fill(ld_rf_pt/GeV,wt);
	h[11][idx]->Fill(dR_pipi,wt);
	h[12][idx]->Fill(dR_B0Ks,wt);
	h[13][idx]->Fill(tq_rf_pt/GeV,wt);
	h[14][idx]->Fill(tq_rf_m/GeV,wt);
	h[15][idx]->Fill(jpsi_m/GeV,wt);
	h[16][idx]->Fill(x_rf_m/GeV,wt);
	h[17][idx]->Fill(jx_m_calc/GeV,wt);	  
	h[18][idx]->Fill(ld_m/GeV,wt);
	h[19][idx]->Fill(ld_Lxy,wt);
	h[20][idx]->Fill(jx_Lxy,wt);
	h[21][idx]->Fill(tq_rf_ratio,wt);
	h[22][idx]->Fill(tq_rf_Lxy,wt);
	h[23][idx]->Fill(tq_rf_fitChi2NDF,wt);
      }

      if(event_number%2 == 1) score2 = reader2_testOdd->EvaluateMVA("BDTG");
      else                    score2 = reader2_testEven->EvaluateMVA("BDTG");
      if(tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848) {
	h[24][idx]->Fill(score2,wt);
      }
      if(score2 > -0.5) {
	h[25][idx]->Fill(tq_rf_m/GeV,wt);
      }

      if( idx==3
	  && !(tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
	  && !(tq_rf_m/GeV<5.80)
	  ) {
	idx = 4; // TQ mass sideband
	wt = 0.185;

	h[19][idx]->Fill(ld_Lxy,wt);
	h[20][idx]->Fill(jx_Lxy,wt);
	h[21][idx]->Fill(tq_rf_ratio,wt);
	h[22][idx]->Fill(tq_rf_Lxy,wt);
	h[23][idx]->Fill(tq_rf_fitChi2NDF,wt);
      }
    }
  }

  Long64_t nentries = ch[3]->GetEntries();
  printf("%llu entries to be processed...\n",nentries);
  for(Long64_t entry=0; entry<nentries; entry++) {

    ch[3]->GetEntry(entry);

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

    Float_t wt = 1;

    // right sideband
    if( (tq_rf_m/GeV>5.848 && tq_rf_m/GeV<=5.90)
	|| (tq_rf_m/GeV>5.832 && tq_rf_m/GeV<=5.848)
	//|| (tq_rf_m/GeV>5.80 && tq_rf_m/GeV<=5.848)
	) {
      wt *= 0.0257;

      Float_t tmp = pt_mu1/GeV;
      if(tmp>20) wt *= 1.21736;

      tmp = pt_K_X/GeV;
      if(tmp>10) tmp = 10;
      wt *= 2.10336-0.63087*tmp+0.0970254*pow(tmp,2)-0.00491499*pow(tmp,3);

      tmp = pt_pi_X/GeV;
      if(tmp>10) tmp = 10;
      wt *= 1.67968-0.478205*tmp+0.0878225*pow(tmp,2)-0.00482538*pow(tmp,3);

      tmp = pt_LRT_trk1/GeV;
      if(tmp>6) tmp = 6;
      wt *= 0.344943-0.0563506*tmp+0.258667*pow(tmp,2)-0.0147922*pow(tmp,3);

      tmp = pt_LRT_trk2/GeV;
      if(tmp>3) tmp = 3;
      wt *= 0.946227-0.336697*tmp+0.533454*pow(tmp,2)-0.0899269*pow(tmp,3);

      tmp = dR_B0Ks;
      if(tmp<0.1) wt *= 0.915283+19.5524*tmp-378.3*pow(tmp,2)+1875.97*pow(tmp,3);
    }
    // left sideband
    else if( (tq_rf_m/GeV>5.80 && tq_rf_m/GeV<=5.832)
	     || (tq_rf_m/GeV<=5.80)
	     ) {
      wt *= 0.0245;

      Float_t tmp = pt_mu1/GeV;
      if(tmp>20) wt *= 1.21736;

      tmp = pt_K_X/GeV;
      if(tmp>10) tmp = 10;
      wt *= 2.83179-1.02762*tmp+0.148442*pow(tmp,2)-0.00675105*pow(tmp,3);

      tmp = pt_pi_X/GeV;
      if(tmp>8) tmp =8;
      wt *= 2.02288-0.812198*tmp+0.170114*pow(tmp,2)-0.0108782*pow(tmp,3);

      tmp = pt_LRT_trk1/GeV;
      if(tmp>6) tmp = 6;
      wt *= 0.344943-0.0563506*tmp+0.258667*pow(tmp,2)-0.0147922*pow(tmp,3);

      tmp = pt_LRT_trk2/GeV;
      if(tmp>2.5) tmp = 2.5;
      wt *= 1.71598-2.36231*tmp+2.03162*pow(tmp,2)-0.408492*pow(tmp,3);

      tmp = dR_B0Ks;
      if(tmp<0.1) wt *= 0.915283+19.5524*tmp-378.3*pow(tmp,2)+1875.97*pow(tmp,3);
    }

    if(true
       && (tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
      ) {
      hmix[0]->Fill(pt_mu1/GeV,wt);
      hmix[1]->Fill(pt_mu2/GeV,wt);
      hmix[2]->Fill(pt_K_X/GeV,wt);
      hmix[3]->Fill(pt_pi_X/GeV,wt);
      hmix[4]->Fill(dR_mumu,wt);
      hmix[5]->Fill(dR_Kpi,wt);
      hmix[6]->Fill(dR_JpsiKst,wt);
      hmix[7]->Fill(pt_LRT_trk1/GeV,wt);
      hmix[8]->Fill(pt_LRT_trk2/GeV,wt);
      hmix[9]->Fill(jx_rf_pt/GeV,wt);
      hmix[10]->Fill(ld_rf_pt/GeV,wt);
      hmix[11]->Fill(dR_pipi,wt);
      hmix[12]->Fill(dR_B0Ks,wt);
      hmix[13]->Fill(tq_rf_pt/GeV,wt);
      hmix[14]->Fill(tq_rf_m/GeV,wt);
      hmix[15]->Fill(jpsi_m/GeV,wt);
      hmix[16]->Fill(x_rf_m/GeV,wt);
      hmix[17]->Fill(jx_m_calc/GeV,wt);
      hmix[18]->Fill(ld_m/GeV,wt);
    }

    if(event_number%2 == 1) score2 = reader2_testOdd->EvaluateMVA("BDTG");
    else                    score2 = reader2_testEven->EvaluateMVA("BDTG");
    if(tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848) {
      hmix[24]->Fill(score2,wt);
    }
    if(score2 > -0.5) {
      hmix[25]->Fill(tq_rf_m/GeV,wt);
    }
  }

  for(Int_t idx=0; idx<5; idx++) {
    h[16][idx]->SetMinimum(0);
    h[18][idx]->GetXaxis()->SetNdivisions(509);
  }

  for(Int_t i=0; i<NN; i++) {    
    h[i][2]->Scale(0.0116);

    if(subtractBkg) {
      if((i>=0 && i<=18) || i==24 || i==25) {
	h[i][3]->Add(hmix[i],-1);
      }
      else {
	h[i][3]->Add(h[i][4],-1);
      }
    }
    else {
      if((i>=0 && i<=18) || i==24 || i==25) {
	htot[i]->Add(hmix[i]);
      }
      else {
	htot[i]->Add(h[i][4]);
      }
    }

    htot[i]->Add(h[i][2]);

    if(i==25) {
      htot[i]->Add(h[i][1]);
      htot[i]->Add(h[i][0]);
    }

    if(i==24) SetMax(h[i][3],htot[i],1.8);
    else SetMax(h[i][3],htot[i],1.3);
  }

  TH1D* dummy1 = new TH1D("dummy1","",1,0,1); dummy1->SetLineColor(kRed); dummy1->SetLineWidth(3);
  TH1D* dummy2 = new TH1D("dummy2","",1,0,1); dummy2->SetLineColor(kBlue); dummy2->SetLineWidth(1);
  TH1D* dummy3 = new TH1D("dummy4","",1,0,1); dummy3->SetLineColor(6); dummy3->SetLineStyle(5);
  TH1D* dummy4 = new TH1D("dummy5","",1,0,1); dummy4->SetMarkerSize(0.7);
  TLegend* lg1 = new TLegend(0.65,0.58,0.89,0.89,"");
  lg1->AddEntry(dummy1,"Sig.+Bkg.","L");
  lg1->AddEntry(dummy2,"Background","L");
  lg1->AddEntry(dummy3,"Signal","L");
  lg1->AddEntry(dummy4,"Data","LEP");
  lg1->SetBorderSize(0);
  lg1->SetMargin(0.25);
  lg1->SetFillColor(kWhite);

  TLegend* lg2 = new TLegend(0.16,0.58,0.40,0.89,"");
  lg2->AddEntry(dummy1,"Sig.+Bkg.","L");
  lg2->AddEntry(dummy2,"Background","L");
  lg2->AddEntry(dummy3,"Signal","L");
  lg2->AddEntry(dummy4,"Data","LEP");
  lg2->SetBorderSize(0);
  lg2->SetMargin(0.25);
  lg2->SetFillColor(kWhite);

  TCanvas* c[30];
  TPad* padhigh[30];
  TPad* padlow[30];
  //for(Int_t i=0; i<=18; i++) {
  for(Int_t i=0; i<NN; i++) {
    sprintf(str,"c%d",i+1);
    c[i] = new TCanvas(str,str,600,600);

    sprintf(str,"padhigh%d",i+1);
    padhigh[i] = new TPad(str,str,0,0.3,1,1);
    padhigh[i]->Draw();
    padhigh[i]->cd();
    padhigh[i]->SetGrid(0,0);
    padhigh[i]->SetBottomMargin(0.0);

    //h[i][3]->SetXTitle(xtitle[i]);
    h[i][3]->SetMinimum(1e-3);
    h[i][3]->SetLineColor(kBlack);
    h[i][3]->SetMarkerStyle(8);
    h[i][3]->SetMarkerSize(0.7);
    h[i][3]->Draw("E1");

    htot[i]->SetLineColor(kRed);
    htot[i]->SetLineWidth(3);
    htot[i]->Draw("same hist");

    if(!subtractBkg) {
      if((i>=0 && i<=18) || i==24 || i==25) {
	hmix[i]->SetLineColor(kBlue);
	hmix[i]->Draw("same hist");
      }
      else {
	h[i][4]->SetLineColor(kBlue);
	h[i][4]->Draw("same hist");
      }
    }

    h[i][2]->SetLineColor(6);
    h[i][2]->SetLineStyle(5);
    h[i][2]->Draw("same hist");

    if(i==25) {
      h[i][1]->SetLineColor(6);
      h[i][1]->SetLineStyle(5);
      h[i][1]->Draw("same hist");
      h[i][0]->SetLineColor(6);
      h[i][0]->SetLineStyle(5);
      h[i][0]->Draw("same hist");
    }

    if(i==14 || i==22 || i==24 || i==25) lg2->Draw("same");
    else lg1->Draw("same");

    c[i]->cd();
    sprintf(str,"padlow%d",i+1);
    padlow[i] = new TPad(str,str,0,0,1,0.3);
    padlow[i]->SetFillStyle(4000);
    padlow[i]->SetGrid(1,1);
    padlow[i]->SetTopMargin(0.0);
    padlow[i]->SetBottomMargin(0.35);
    padlow[i]->Draw();
    padlow[i]->cd();

    TH1F* hh = htot[i];
    for(Int_t j=1; j<=hratio[i]->GetNbinsX(); j++) {
      Float_t tmp1 = h[i][3]->GetBinContent(j)>0 ? h[i][3]->GetBinError(j)/h[i][3]->GetBinContent(j) : 0;
      Float_t tmp2 = hh->GetBinContent(j)>0 ? hh->GetBinError(j)/hh->GetBinContent(j) : 0;
      Float_t tmp = hh->GetBinContent(j)>0 ? h[i][3]->GetBinContent(j)/hh->GetBinContent(j) : 0;
      hratio[i]->SetBinContent(j,tmp);
      hratio[i]->SetBinError(j,tmp*sqrt(pow(tmp1,2)+pow(tmp2,2)));
    }

    hratio[i]->GetXaxis()->SetLabelFont(42);
    hratio[i]->GetXaxis()->SetLabelSize(0.12); 
    hratio[i]->GetXaxis()->SetLabelOffset(0.02); 
    hratio[i]->GetXaxis()->SetTitleOffset(1.0);
    hratio[i]->GetXaxis()->SetTitleSize(0.15); 
    hratio[i]->GetYaxis()->SetLabelFont(42);
    hratio[i]->GetYaxis()->SetLabelSize(0.12); 
    hratio[i]->GetYaxis()->SetTitleOffset(0.45);
    hratio[i]->GetYaxis()->SetTitleSize(0.12); 
    hratio[i]->SetMarkerStyle(8);
    hratio[i]->SetMarkerSize(0.6);
    hratio[i]->SetMaximum(2.0-1e-3);
    hratio[i]->SetMinimum(0.0+1e-3);
    hratio[i]->GetYaxis()->SetNdivisions(509);
    hratio[i]->GetYaxis()->SetTitle("Ratio");
    hratio[i]->GetYaxis()->CenterTitle();
    hratio[i]->GetXaxis()->SetTitle(xtitle[i]);
    hratio[i]->Draw("EX0");

     sprintf(str,"./plot/selcut/c%d.png",i+1);
     c[i]->SaveAs(str);
  }
}
