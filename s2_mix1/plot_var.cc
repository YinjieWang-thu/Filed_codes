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

#include "reader.h"
#define NN 26

const Double_t GeV=1000;
const Double_t PI=3.1415926536;
const Float_t BDTG1_lim = -0.4;

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

void plot_var() {
  gStyle->SetOptStat(kFALSE);

  //TMVA Vars
  /*
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
  float weight;

  
  TFile newfile("TMVA.root", "recreate");
  TTree* Signaltree = new TTree("Signaltree","");

  
  Signaltree->Branch("Pt_mu1",&Pt_mu1,"Pt_mu1/F");
  Signaltree->Branch("Pt_mu2",&Pt_mu2,"Pt_mu2/F");
  Signaltree->Branch("Pt_K",&Pt_K,"Pt_K/F");
  Signaltree->Branch("Pt_pi",&Pt_pi,"Pt_pi/F");
  Signaltree->Branch("DR_Kpi",&DR_Kpi,"DR_Kpi/F");
  Signaltree->Branch("Pt_pi1",&Pt_pi1,"Pt_pi1/F");
  Signaltree->Branch("Pt_pi2",&Pt_pi2,"Pt_pi2/F");
  Signaltree->Branch("Pt_B0",&Pt_B0,"Pt_B0/F");
  Signaltree->Branch("Pt_Ks",&Pt_Ks,"Pt_Ks/F");
  Signaltree->Branch("DR_B0Ks",&DR_B0Ks,"DR_B0Ks/F");
  Signaltree->Branch("Pt_tq",&Pt_tq,"Pt_tq/F");
  Signaltree->Branch("M_tq",&M_tq,"M_tq/F");
  Signaltree->Branch("M_jpsi",&M_jpsi,"M_jpsi/F");
  Signaltree->Branch("M_Kpi",&M_Kpi,"M_Kpi/F");
  Signaltree->Branch("M_B0",&M_B0,"M_B0/F");
  Signaltree->Branch("M_Ks",&M_Ks,"M_Ks/F");
  Signaltree->Branch("weight",&weight,"weight/F");

  TTree* Bkgtree = new TTree("Bkgtreee","");
  Bkgtree->Branch("Pt_mu1",&Pt_mu1,"Pt_mu1/F");
  Bkgtree->Branch("Pt_mu2",&Pt_mu2,"Pt_mu2/F");
  Bkgtree->Branch("Pt_K",&Pt_K,"Pt_K/F");
  Bkgtree->Branch("Pt_pi",&Pt_pi,"Pt_pi/F");
  Bkgtree->Branch("DR_Kpi",&DR_Kpi,"DR_Kpi/F");
  Bkgtree->Branch("Pt_pi1",&Pt_pi1,"Pt_pi1/F");
  Bkgtree->Branch("Pt_pi2",&Pt_pi2,"Pt_pi2/F");
  Bkgtree->Branch("Pt_B0",&Pt_B0,"Pt_B0/F");
  Bkgtree->Branch("Pt_Ks",&Pt_Ks,"Pt_Ks/F");
  Bkgtree->Branch("DR_B0Ks",&DR_B0Ks,"DR_B0Ks/F");
  Bkgtree->Branch("Pt_tq",&Pt_tq,"Pt_tq/F");
  Bkgtree->Branch("M_tq",&M_tq,"M_tq/F");
  Bkgtree->Branch("M_jpsi",&M_jpsi,"M_jpsi/F");
  Bkgtree->Branch("M_Kpi",&M_Kpi,"M_Kpi/F");
  Bkgtree->Branch("M_B0",&M_B0,"M_B0/F");
  Bkgtree->Branch("M_Ks",&M_Ks,"M_Ks/F");
  Bkgtree->Branch("weight",&weight,"weight/F");
  */
  

  TChain* ch[4];

  // Bs1
  ch[0] = new TChain("BPHY25");
  ch[0]->Add("../B25TMVA/mc_Bs1_BDT1.root");
  Init(ch[0]);

  // Bs2
  ch[1] = new TChain("BPHY25");
  ch[1]->Add("../B25TMVA/mc_Bs2_BDT1.root");
  Init(ch[1]);

  // data
  ch[2] = new TChain("BPHY25");
  ch[2]->Add("../B25TMVA/data_bdt1.root");
  Init(ch[2]);

  // mixing
  ch[3] = new TChain("BPHY25");
  ch[3]->Add("../B25TMVA/Bphy25mix_BDT1.root");


  ch[3]->SetBranchAddress("tq_rf_m",&tq_rf_m);
  ch[3]->SetBranchAddress("tq_rf_pt",&tq_rf_pt);
  ch[3]->SetBranchAddress("jx_Lxy",&jx_Lxy);
  ch[3]->SetBranchAddress("jx_rf_m",&jx_rf_m);
  ch[3]->SetBranchAddress("jx_rf_pt",&jx_rf_pt);
  ch[3]->SetBranchAddress("jx_rf_eta",&jx_rf_eta);
  ch[3]->SetBranchAddress("jx_rf_phi",&jx_rf_phi);
  ch[3]->SetBranchAddress("jx_m_calc",&jx_m_calc);
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
  ch[3]->SetBranchAddress("trk_rf_m", trk_rf_m);
  ch[3]->SetBranchAddress("trk_rf_pt", trk_rf_pt);
  ch[3]->SetBranchAddress("trk_rf_eta", trk_rf_eta);
  ch[3]->SetBranchAddress("trk_rf_phi", trk_rf_phi);
  ch[3]->SetBranchAddress("BDTG1", &BDTG1);

  char str[100];
  TH1F* h[30][5];
  TH1F* hmix[30];
  TH1F* htot[30];
  TH1F* hratio[30];
  const char* xtitle[] = {"p_{T}^{#mu_{1}} [GeV]",
		    "p_{T}^{#mu_{2}} [GeV]",
		    "p_{T}^{K} [GeV]",
		    "p_{T}^{#pi} [GeV]",
		    "#DeltaR(K,#pi)",
		    "p_{T}^{#pi_{1}}(K_{S}) [GeV]",
		    "p_{T}^{#pi_{2}}(K_{S}) [GeV]",
		    "p_{T}^{B^{0}} [GeV]",
		    "p_{T}^{K_{S}} [GeV]",
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
		    "p_{T}^{K} [GeV]",
		    "p_{T}^{#pi} [GeV]",
		    "#DeltaR(K,#pi)",
		    "m_{B^{0}+K_{S}} [GeV]",
        "BDTG1"
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
    h[4][i] = new TH1F(str,"",20,0,0.8); // dR(K,pi)
    sprintf(str,"h6_%d",i+1);
    h[5][i] = new TH1F(str,"",50,0,10); // pt(pi1)
    sprintf(str,"h7_%d",i+1);
    h[6][i] = new TH1F(str,"",50,0,5); // pt(pi2)
    sprintf(str,"h8_%d",i+1);
    h[7][i] = new TH1F(str,"",50,0,100); // pt(B0)
    sprintf(str,"h9_%d",i+1);
    h[8][i] = new TH1F(str,"",50,0,10); // pt(Ks)
    sprintf(str,"h10_%d",i+1);
    h[9][i] = new TH1F(str,"",40,0,0.4); // dR(Jpsi,Ks)
    sprintf(str,"h11_%d",i+1);
    h[10][i] = new TH1F(str,"",25,0,100); // pt(B0+Ks)
    sprintf(str,"h12_%d",i+1);
    h[11][i] = new TH1F(str,"",75,5.76,5.91); // B0+Ks mass
    sprintf(str,"h13_%d",i+1);
    h[12][i] = new TH1F(str,"",60,2.8,3.4); // Jpsi mass
    sprintf(str,"h14_%d",i+1);
    h[13][i] = new TH1F(str,"",37,0.70,1.07); // K* mass
    sprintf(str,"h15_%d",i+1);
    h[14][i] = new TH1F(str,"",60,5.08,5.48); // B0 mass
    sprintf(str,"h16_%d",i+1);
    h[15][i] = new TH1F(str,"",80,0.4,0.6); // Ks mass
    sprintf(str,"h17_%d",i+1);
    h[16][i] = new TH1F(str,"",76,5,400); // Lxy(Ks)
    sprintf(str,"h18_%d",i+1);
    h[17][i] = new TH1F(str,"",60,0,15); // Lxy(B0)
    sprintf(str,"h19_%d",i+1);
    h[18][i] = new TH1F(str,"",40,0,1); // pt ratio
    sprintf(str,"h20_%d",i+1);
    h[19][i] = new TH1F(str,"",50,-6.5,3.5); // Lxy(B0+Ks)
    sprintf(str,"h21_%d",i+1);
    h[20][i] = new TH1F(str,"",25,0,5.0); // chi2/N
    sprintf(str,"h22_%d",i+1);
    h[21][i] = new TH1F(str,"",50,0,25); // pt(K)
    sprintf(str,"h23_%d",i+1);
    h[22][i] = new TH1F(str,"",30,0,15); // pt(pi)
    sprintf(str,"h24_%d",i+1);
    h[23][i] = new TH1F(str,"",20,0,0.8); // dR(K,pi)
    sprintf(str,"h25_%d",i+1);
    h[24][i] = new TH1F(str,"",75,5.76,5.91); // total tqmass
    sprintf(str,"h26_%d",i+1);
    h[25][i] = new TH1F(str,"",40,-1,1); // BDTG1
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

  Int_t n_NoTruth(0);  
  for(Int_t ich=0; ich<3; ich++) {
    if(!ch[ich]) continue;
    Long64_t nentries = ch[ich]->GetEntries();
    printf("%llu entries to be processed...\n",nentries);
    for(Long64_t entry=0; entry<nentries; entry++) {

      ch[ich]->GetEntry(entry);

      Bool_t isOS = trk_charge[0]*trk_charge[1]<0;

      // baseline selection
      if(jpsi_m/GeV>2.96 && jpsi_m/GeV<3.22
	 && ( (isOS && x_rf_m/GeV>0.84 && x_rf_m/GeV<0.95) || (!isOS && x_rf_m/GeV>0.80 && x_rf_m/GeV<0.99) )
	 && jx_m_calc/GeV>5.180 && jx_m_calc/GeV<5.375 && tq_rf_fitChi2NDF<1.8
	 && ld_m/GeV>0.475 && ld_m/GeV<0.520 && tq_rf_ratio>0.20
	 && jx_Lxy>0.3 && tq_rf_m/GeV<5.91
	 ) {
	int idx(-1);
	if(ich==0) idx = 0; // Bs1
	else if(ich==1) {
	  if(truth_mu_m[0]<=0 || truth_mu_m[1]<=0 || truth_K_m<=0 || truth_pi1_m<=0 || truth_pi_m[0]<=0 || truth_pi_m[1]<=0) {
	    n_NoTruth++;
	    continue;
	  }

	  TLorentzVector v; TLorentzVector tmp;
	  tmp.SetPtEtaPhiM(truth_mu_pt[0],truth_mu_eta[0],truth_mu_phi[0],truth_mu_m[0]); v += tmp;
	  tmp.SetPtEtaPhiM(truth_mu_pt[1],truth_mu_eta[1],truth_mu_phi[1],truth_mu_m[1]); v += tmp;
	  tmp.SetPtEtaPhiM(truth_K_pt,truth_K_eta,truth_K_phi,truth_K_m);                 v += tmp;
	  tmp.SetPtEtaPhiM(truth_pi1_pt,truth_pi1_eta,truth_pi1_phi,truth_pi1_m);         v += tmp;
	  tmp.SetPtEtaPhiM(truth_pi_pt[0],truth_pi_eta[0],truth_pi_phi[0],truth_pi_m[0]); v += tmp;
	  tmp.SetPtEtaPhiM(truth_pi_pt[1],truth_pi_eta[1],truth_pi_phi[1],truth_pi_m[1]); v += tmp;
	  if(v.M()/GeV<5.83) idx = 1; // Bs2 low peak
	  else idx = 2; // Bs2 high peak
	}
	else if(ich==2) {
	  if(isOS) idx = 3;
	}
	else continue;

	TLorentzVector tmpK; TLorentzVector tmpPi;
	tmpK.SetPtEtaPhiM(trk_rf_pt[0],trk_rf_eta[0],trk_rf_phi[0],trk_rf_m[0]);
	tmpPi.SetPtEtaPhiM(trk_rf_pt[1],trk_rf_eta[1],trk_rf_phi[1],trk_rf_m[1]);
	TLorentzVector tmpJpsi; TLorentzVector tmpKs;
	tmpJpsi.SetPtEtaPhiM(jx_rf_pt,jx_rf_eta,jx_rf_phi,jx_rf_m);
	tmpKs.SetPtEtaPhiM(ld_rf_pt,ld_rf_eta,ld_rf_phi,ld_rf_m);

	// further cuts
	if( idx<=3 && isOS
	    && (tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
	    //&& !(tq_rf_m/GeV<5.80)
	    ) {
	  Float_t wt = 1;

	  if(idx<=2) { // Bs2 high peak signal
	    wt *= 0.90;

	    Float_t tmp = pt_mu2/GeV;
	    if(tmp>9) tmp = 9;
	    wt *= 7.76806-4.10701*tmp+0.742646*pow(tmp,2)-0.0409049*pow(tmp,3);

	    tmp = pt_K_X/GeV;
	    if(tmp>10) tmp = 10;
	    wt *= 2.45196-0.520279*tmp+0.0497799*pow(tmp,2)-0.00156806*pow(tmp,3);
	    
	    tmp = tmpK.DeltaR(tmpPi);
	    if(tmp>0.3) tmp = 0.3;
	    wt *= 0.562446+4.69604*tmp-9.3218*pow(tmp,2);

	    tmp = tq_rf_pt/GeV;
	    if(tmp<15) tmp = 15; if(tmp>80) tmp = 80;
	    wt *= 1.03478+0.0453435*tmp-0.0014999*pow(tmp,2)+1.10796e-05*pow(tmp,3);
	  }

	  h[0][idx]->Fill(pt_mu1/GeV,wt); // idx = 1,2,3
	  h[1][idx]->Fill(pt_mu2/GeV,wt);
	  h[2][idx]->Fill(pt_K_X/GeV,wt);
	  h[3][idx]->Fill(pt_pi_X/GeV,wt);
	  h[4][idx]->Fill(tmpK.DeltaR(tmpPi),wt);
	  h[5][idx]->Fill(pt_LRT_trk1/GeV,wt);
	  h[6][idx]->Fill(pt_LRT_trk2/GeV,wt);
	  h[7][idx]->Fill(jx_rf_pt/GeV,wt);
	  h[8][idx]->Fill(ld_rf_pt/GeV,wt);
	  h[9][idx]->Fill(tmpJpsi.DeltaR(tmpKs),wt);
	  h[10][idx]->Fill(tq_rf_pt/GeV,wt);
	  h[11][idx]->Fill(tq_rf_m/GeV,wt);
	  h[12][idx]->Fill(jpsi_m/GeV,wt);
	  h[13][idx]->Fill(x_rf_m/GeV,wt);
	  h[14][idx]->Fill(jx_m_calc/GeV,wt);	  
	  h[15][idx]->Fill(ld_m/GeV,wt);
	  h[16][idx]->Fill(ld_Lxy,wt);
	  h[17][idx]->Fill(jx_Lxy,wt);
	  h[18][idx]->Fill(tq_rf_ratio,wt);
	  h[19][idx]->Fill(tq_rf_Lxy,wt);
	  h[20][idx]->Fill(tq_rf_fitChi2NDF,wt);
	  h[21][idx]->Fill(pt_K_X/GeV,wt);
	  h[22][idx]->Fill(pt_pi_X/GeV,wt);
	  h[23][idx]->Fill(tmpK.DeltaR(tmpPi),wt);
    h[25][idx]->Fill(BDTG1,wt);
    /*
    if(idx == 2
    ){
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
      weight = wt * 0.0116;//not comfirm
      Signaltree->Fill();
    }
    */

	}

  	// further cuts
	if( idx<=3 && isOS
    && BDTG1 > BDTG1_lim
	    ) {
	  Float_t wt = 1;

	  if(idx<=2) { // Bs2 high peak signal
	    wt *= 0.90;

	    Float_t tmp = pt_mu2/GeV;
	    if(tmp>9) tmp = 9;
	    wt *= 7.76806-4.10701*tmp+0.742646*pow(tmp,2)-0.0409049*pow(tmp,3);

	    tmp = pt_K_X/GeV;
	    if(tmp>10) tmp = 10;
	    wt *= 2.45196-0.520279*tmp+0.0497799*pow(tmp,2)-0.00156806*pow(tmp,3);
	    
	    tmp = tmpK.DeltaR(tmpPi);
	    if(tmp>0.3) tmp = 0.3;
	    wt *= 0.562446+4.69604*tmp-9.3218*pow(tmp,2);

	    tmp = tq_rf_pt/GeV;
	    if(tmp<15) tmp = 15; if(tmp>80) tmp = 80;
	    wt *= 1.03478+0.0453435*tmp-0.0014999*pow(tmp,2)+1.10796e-05*pow(tmp,3);
	  }

    h[24][idx]->Fill(tq_rf_m/GeV,wt);
	}


	if( idx==3 && isOS
	    && !(tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
	    && !(tq_rf_m/GeV<5.80)
	    ) {
	  idx += 1; // TQ mass sideband
	  Float_t wt = 0.16;

	  h[0][idx]->Fill(pt_mu1/GeV,wt);//idx = 4
	  h[1][idx]->Fill(pt_mu2/GeV,wt);
	  h[2][idx]->Fill(pt_K_X/GeV,wt);
	  h[3][idx]->Fill(pt_pi_X/GeV,wt);
	  h[4][idx]->Fill(tmpK.DeltaR(tmpPi),wt);
	  h[5][idx]->Fill(pt_LRT_trk1/GeV,wt);
	  h[6][idx]->Fill(pt_LRT_trk2/GeV,wt);
	  h[7][idx]->Fill(jx_rf_pt/GeV,wt);
	  h[8][idx]->Fill(ld_rf_pt/GeV,wt);
	  h[9][idx]->Fill(tmpJpsi.DeltaR(tmpKs),wt);
	  h[10][idx]->Fill(tq_rf_pt/GeV,wt);
	  h[11][idx]->Fill(tq_rf_m/GeV,wt);
	  h[12][idx]->Fill(jpsi_m/GeV,wt);
	  h[13][idx]->Fill(x_rf_m/GeV,wt);
	  h[14][idx]->Fill(jx_m_calc/GeV,wt);	  
	  h[15][idx]->Fill(ld_m/GeV,wt);
	  h[16][idx]->Fill(ld_Lxy,wt);
	  h[17][idx]->Fill(jx_Lxy,wt);
	  h[18][idx]->Fill(tq_rf_ratio,wt);
	  h[19][idx]->Fill(tq_rf_Lxy,wt);
	  h[20][idx]->Fill(tq_rf_fitChi2NDF,wt);
	  h[21][idx]->Fill(pt_K_X/GeV,wt);
	  h[22][idx]->Fill(pt_pi_X/GeV,wt);
	  h[23][idx]->Fill(tmpK.DeltaR(tmpPi),wt);
    h[25][idx]->Fill(BDTG1,wt);
	}


      }
    }
  }
  printf(" %d events with NoTruth\n",n_NoTruth);

  Long64_t nentries = ch[3]->GetEntries();
  printf("%llu entries to be processed...\n",nentries);
  for(Long64_t entry=0; entry<nentries; entry++) {

    ch[3]->GetEntry(entry);

    TLorentzVector tmpK; TLorentzVector tmpPi;
    tmpK.SetPtEtaPhiM(trk_rf_pt[0],trk_rf_eta[0],trk_rf_phi[0],trk_rf_m[0]);
    tmpPi.SetPtEtaPhiM(trk_rf_pt[1],trk_rf_eta[1],trk_rf_phi[1],trk_rf_m[1]);
    TLorentzVector tmpJpsi; TLorentzVector tmpKs;
    tmpJpsi.SetPtEtaPhiM(jx_rf_pt,jx_rf_eta,jx_rf_phi,jx_rf_m);
    tmpKs.SetPtEtaPhiM(ld_rf_pt,ld_rf_eta,ld_rf_phi,ld_rf_m);

    if(true
       && (tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
       //&& !(tq_rf_m/GeV<5.80)
      ) {
      Float_t wt = 0.065;

      Float_t tmp = jx_rf_pt/GeV;
      if(tmp<12) tmp = 12; if(tmp>70) tmp = 70;
      wt *= 3.38248-0.176722*tmp+0.00428258*pow(tmp,2)-3.21723e-05*pow(tmp,3);

      tmp = ld_rf_pt/GeV;
      if(tmp<0.8) tmp = 0.8; if(tmp>7) tmp = 7;
      wt *= 0.685533-0.332305*tmp+0.159484*pow(tmp,2)+0.00508318*pow(tmp,3);

      tmp = tmpJpsi.DeltaR(tmpKs);
      if(tmp>0.3) tmp = 0.3;
      wt *= 2.0065-17.4898*tmp+91.7427*pow(tmp,2)-173.585*pow(tmp,3);

      tmp = pt_LRT_trk2/GeV;
      if(tmp<1) wt *= 1.88842-2.07924*tmp+1.22875*pow(tmp,2);

      tmp = pt_K_X/GeV;
      if(tmp>7) tmp = 7;
      wt *= 1.77323-0.520244*tmp+0.0845369*pow(tmp,2)-0.00442852*pow(tmp,3);

      tmp = pt_pi_X/GeV;
      if(tmp>7) tmp = 7;
      wt *= 1.67228-0.570894*tmp+0.112904*pow(tmp,2)-0.00700197*pow(tmp,3);

      tmp = pt_mu1/GeV;
      if(tmp>50) tmp = 50;
      if(tmp<20) wt *= 0.548378+0.034195*tmp+2.00334e-05*pow(tmp,2);
      else wt *= 1.38268+0.00326933*tmp;

      hmix[0]->Fill(pt_mu1/GeV,wt);
      hmix[1]->Fill(pt_mu2/GeV,wt);
      hmix[2]->Fill(pt_K_X/GeV,wt);
      hmix[3]->Fill(pt_pi_X/GeV,wt);
      hmix[4]->Fill(tmpK.DeltaR(tmpPi),wt);
      hmix[5]->Fill(pt_LRT_trk1/GeV,wt);
      hmix[6]->Fill(pt_LRT_trk2/GeV,wt);
      hmix[7]->Fill(jx_rf_pt/GeV,wt);
      hmix[8]->Fill(ld_rf_pt/GeV,wt);
      hmix[9]->Fill(tmpJpsi.DeltaR(tmpKs),wt);
      hmix[10]->Fill(tq_rf_pt/GeV,wt);
      hmix[11]->Fill(tq_rf_m/GeV,wt);
      hmix[12]->Fill(jpsi_m/GeV,wt);
      hmix[13]->Fill(x_rf_m/GeV,wt);
      hmix[14]->Fill(jx_m_calc/GeV,wt);     
      hmix[15]->Fill(ld_m/GeV,wt);
      hmix[25]->Fill(BDTG1,wt);

      /*
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
      weight = wt;
      Bkgtree->Fill();
        */
      
    }

    if(true && BDTG1 > BDTG1_lim
       //&& !(tq_rf_m/GeV<5.80)
      ) {
      Float_t wt = 0.065;

      Float_t tmp = jx_rf_pt/GeV;
      if(tmp<12) tmp = 12; if(tmp>70) tmp = 70;
      wt *= 3.38248-0.176722*tmp+0.00428258*pow(tmp,2)-3.21723e-05*pow(tmp,3);

      tmp = ld_rf_pt/GeV;
      if(tmp<0.8) tmp = 0.8; if(tmp>7) tmp = 7;
      wt *= 0.685533-0.332305*tmp+0.159484*pow(tmp,2)+0.00508318*pow(tmp,3);

      tmp = tmpJpsi.DeltaR(tmpKs);
      if(tmp>0.3) tmp = 0.3;
      wt *= 2.0065-17.4898*tmp+91.7427*pow(tmp,2)-173.585*pow(tmp,3);

      tmp = pt_LRT_trk2/GeV;
      if(tmp<1) wt *= 1.88842-2.07924*tmp+1.22875*pow(tmp,2);

      tmp = pt_K_X/GeV;
      if(tmp>7) tmp = 7;
      wt *= 1.77323-0.520244*tmp+0.0845369*pow(tmp,2)-0.00442852*pow(tmp,3);

      tmp = pt_pi_X/GeV;
      if(tmp>7) tmp = 7;
      wt *= 1.67228-0.570894*tmp+0.112904*pow(tmp,2)-0.00700197*pow(tmp,3);

      tmp = pt_mu1/GeV;
      if(tmp>50) tmp = 50;
      if(tmp<20) wt *= 0.548378+0.034195*tmp+2.00334e-05*pow(tmp,2);
      else wt *= 1.38268+0.00326933*tmp;
      hmix[24]->Fill(tq_rf_m/GeV,wt);
    }
  }

  for(Int_t idx=0; idx<5; idx++) {
    h[13][idx]->SetMinimum(0);
    h[15][idx]->GetXaxis()->SetNdivisions(509);
  }

  for(Int_t i=0; i<NN; i++) {    
    h[i][2]->Scale(0.0116);//signal nomarlization

    // if(i>=0 && i<=15) {
    //   h[i][3]->Add(hmix[i],-1);
    // }

    htot[i]->Add(h[i][2]);
    if(i>=0 && i<=15 || i >= 24) {
      htot[i]->Add(hmix[i]);
    }
    else {
      htot[i]->Add(h[i][4]);
    }

    SetMax(h[i][3],htot[i],1.3);
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
  //for(Int_t i=0; i<=15; i++) {
  for(Int_t i=24; i<NN; i++) {
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

    htot[i]->SetLineColor(kRed);//htot[i] = h[i][2]+ h[i][4] or hmix[i]
    htot[i]->SetLineWidth(3);
    htot[i]->Draw("same hist");
    
    if(i>=0 && i<=15  || i>=24) {
      hmix[i]->SetLineColor(kBlue);
      hmix[i]->Draw("same hist");
    }
    else {
      h[i][4]->SetLineColor(kBlue);
      h[i][4]->Draw("same hist");//4 for sideband , hmix for mixing
    }

    h[i][2]->SetLineColor(6);//2 for signal(Bs2 high peak)
    h[i][2]->SetLineStyle(5);
    h[i][2]->Draw("same hist");

    if(i==11) lg2->Draw("same");
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

    TH1F* hh = nullptr;
    for(Int_t j=1; j<=hratio[i]->GetNbinsX(); j++) {
      hh = htot[i];
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

     sprintf(str,"out/out2/c%d.png",i+1);
     c[i]->SaveAs(str);
  }
  /*
  newfile.Write();
  newfile.Close();*/
}
