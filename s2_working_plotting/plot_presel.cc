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

#include "../plot3b/reader.h"
#define NN 13

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
Float_t weight;
Float_t dR_B0Ks;

// config variable
Bool_t subtractBkg = 0;

void plot_presel() {
  TChain* ch[2];

  // Bs2
  ch[0] = new TChain("BPHY25");
  ch[0]->Add("../BPhy25_ntuple/mc/mc20a_Bs2_802395.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc20a_Bs2_802396.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc20d_Bs2_802395.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc20d_Bs2_802396.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc20e_Bs2_802395.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc20e_Bs2_802396.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc23a_Bs2_802395.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc23a_Bs2_802396.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc23d_Bs2_802395.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc23d_Bs2_802396.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc23e_Bs2_802395.root");
  ch[0]->Add("../BPhy25_ntuple/mc/mc23e_Bs2_802396.root");
  Init(ch[0]);

  // data
  ch[1] = new TChain("BPHY25");
  ch[1]->Add("data_reduced.root");
  Init(ch[1]);

  // output tree for BDT
  TTree* newtree_sig = new TTree("BPHY25_sig","");
  newtree_sig->Branch("weight",&weight,"weight/F");
  newtree_sig->Branch("event_number",&event_number,"event_number/l");
  newtree_sig->Branch("ld_Lxy",&ld_Lxy,"ld_Lxy/F");
  newtree_sig->Branch("jx_Lxy",&jx_Lxy,"jx_Lxy/F");
  newtree_sig->Branch("tq_rf_ratio",&tq_rf_ratio,"tq_rf_ratio/F");
  newtree_sig->Branch("tq_rf_Lxy",&tq_rf_Lxy,"tq_rf_Lxy/F");
  newtree_sig->Branch("tq_rf_fitChi2NDF",&tq_rf_fitChi2NDF,"tq_rf_fitChi2NDF/F");

  TTree* newtree_bkg = new TTree("BPHY25_bkg","");
  newtree_bkg->Branch("weight",&weight,"weight/F");
  newtree_bkg->Branch("event_number",&event_number,"event_number/l");
  newtree_bkg->Branch("ld_Lxy",&ld_Lxy,"ld_Lxy/F");
  newtree_bkg->Branch("jx_Lxy",&jx_Lxy,"jx_Lxy/F");
  newtree_bkg->Branch("tq_rf_ratio",&tq_rf_ratio,"tq_rf_ratio/F");
  newtree_bkg->Branch("tq_rf_Lxy",&tq_rf_Lxy,"tq_rf_Lxy/F");
  newtree_bkg->Branch("tq_rf_fitChi2NDF",&tq_rf_fitChi2NDF,"tq_rf_fitChi2NDF/F");

  char str[100];
  TH1F* h[30][5];
  TH1F* hmix[30];
  TH1F* htot[30];
  TH1F* hratio[30];
  const char* xtitle[] = {
		    "L_{xy}^{K_{S}} [mm]",
		    "L_{xy}^{B^{0}} [mm]",
		    "p_{T}^{B^{0}+K_{S}}/#Sigmap_{T}^{PV}",
		    "L_{xy}^{B^{0}+K_{S}} [mm]",
                    "#chi^{2}/N",
		    "p_{T}^{#mu_{1}} [GeV]",
		    "p_{T}^{#mu_{2}} [GeV]",
		    "p_{T}^{K} [GeV]",
		    "p_{T}^{#pi} [GeV]",
		    "p_{T}^{#pi_{1}}(K_{S}) [GeV]",
		    "p_{T}^{#pi_{2}}(K_{S}) [GeV]",
		    "p_{T}^{B^{0}+K_{S}} [GeV]",
		    "#DeltaR(B^{0},K_{S})"
  };
  for(Int_t i=0; i<5; i++) {
    sprintf(str,"h1_%d",i+1);
    h[0][i] = new TH1F(str,"",76,5,400); // Lxy(Ks)
    sprintf(str,"h2_%d",i+1);
    h[1][i] = new TH1F(str,"",60,0,15); // Lxy(B0)
    sprintf(str,"h3_%d",i+1);
    h[2][i] = new TH1F(str,"",40,0,1); // pt ratio
    sprintf(str,"h4_%d",i+1);
    h[3][i] = new TH1F(str,"",50,-6.5,3.5); // Lxy(B0+Ks)
    sprintf(str,"h5_%d",i+1);
    h[4][i] = new TH1F(str,"",25,0,5.0); // chi2/N
    sprintf(str,"h6_%d",i+1);
    h[5][i] = new TH1F(str,"",30,0,60); // pt(mu1)
    sprintf(str,"h7_%d",i+1);
    h[6][i] = new TH1F(str,"",30,0,30); // pt(mu2)
    sprintf(str,"h8_%d",i+1);
    h[7][i] = new TH1F(str,"",30,0,15); // pt(K)
    sprintf(str,"h9_%d",i+1);
    h[8][i] = new TH1F(str,"",30,0,15); // pt(pi)
    sprintf(str,"h10_%d",i+1);
    h[9][i] = new TH1F(str,"",50,0,10); // pt(pi1)
    sprintf(str,"h11_%d",i+1);
    h[10][i] = new TH1F(str,"",50,0,5); // pt(pi2)
    sprintf(str,"h12_%d",i+1);
    h[11][i] = new TH1F(str,"",25,0,100); // pt(B0+Ks)
    sprintf(str,"h13_%d",i+1);
    h[12][i] = new TH1F(str,"",40,0,0.4); // dR(B0,Ks)
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

  for(Int_t ich=0; ich<2; ich++) {
    if(!ch[ich]) continue;
    Long64_t nentries = ch[ich]->GetEntries();
    printf("%llu entries to be processed...\n",nentries);
    for(Long64_t entry=0; entry<nentries; entry++) {

      ch[ich]->GetEntry(entry);

      Bool_t isOS = trk_charge[0]*trk_charge[1]<0;

      // pre-selection
      if(jpsi_m/GeV>2.96 && jpsi_m/GeV<3.22
	 && isOS && x_rf_m/GeV>0.84 && x_rf_m/GeV<0.95
	 && jx_m_calc/GeV>5.180 && jx_m_calc/GeV<5.375 && tq_rf_fitChi2NDF<1.8
	 && ld_m/GeV>0.475 && ld_m/GeV<0.520 && tq_rf_ratio>0.20
	 && jx_Lxy>0.3 && tq_rf_m/GeV<5.90
	 ) {
	int idx(-1);
	if(ich==0) {
	  if(tq_rf_m/GeV<5.815) idx = 1; // Bs2 low peak
	  else idx = 2; // Bs2 high peak
	}
	else if(ich==1) {
	  idx = 3;
	}
	else continue;

	TLorentzVector tmpJX; TLorentzVector tmpKs;
	tmpJX.SetPtEtaPhiM(jx_rf_pt,jx_rf_eta,jx_rf_phi,jx_rf_m);
	tmpKs.SetPtEtaPhiM(ld_rf_pt,ld_rf_eta,ld_rf_phi,ld_rf_m);

	dR_B0Ks = tmpJX.DeltaR(tmpKs);

	// mass region cuts
	if( idx<=3
	    && (tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
	    ) {
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

	  h[0][idx]->Fill(ld_Lxy,wt);
	  h[1][idx]->Fill(jx_Lxy,wt);
	  h[2][idx]->Fill(tq_rf_ratio,wt);
	  h[3][idx]->Fill(tq_rf_Lxy,wt);
	  h[4][idx]->Fill(tq_rf_fitChi2NDF,wt);
	  h[5][idx]->Fill(pt_mu1/GeV,wt);
	  h[6][idx]->Fill(pt_mu2/GeV,wt);
	  h[7][idx]->Fill(pt_K_X/GeV,wt);
	  h[8][idx]->Fill(pt_pi_X/GeV,wt);
	  h[9][idx]->Fill(pt_LRT_trk1/GeV,wt);
	  h[10][idx]->Fill(pt_LRT_trk2/GeV,wt);
	  h[11][idx]->Fill(tq_rf_pt/GeV,wt);
	  h[12][idx]->Fill(dR_B0Ks,wt);

	  if(idx==2) {
	    weight = wt;
	    newtree_sig->Fill();
	  }
	}

	if( idx==3
	    && !(tq_rf_m/GeV>5.832 && tq_rf_m/GeV<5.848)
	    && !(tq_rf_m/GeV<5.80)
	    ) {
	  idx = 4; // TQ mass sideband
	  Float_t wt = 0.185;

	  h[0][idx]->Fill(ld_Lxy,wt);
	  h[1][idx]->Fill(jx_Lxy,wt);
	  h[2][idx]->Fill(tq_rf_ratio,wt);
	  h[3][idx]->Fill(tq_rf_Lxy,wt);
	  h[4][idx]->Fill(tq_rf_fitChi2NDF,wt);
	  h[5][idx]->Fill(pt_mu1/GeV,wt);
	  h[6][idx]->Fill(pt_mu2/GeV,wt);
	  h[7][idx]->Fill(pt_K_X/GeV,wt);
	  h[8][idx]->Fill(pt_pi_X/GeV,wt);
	  h[9][idx]->Fill(pt_LRT_trk1/GeV,wt);
	  h[10][idx]->Fill(pt_LRT_trk2/GeV,wt);
	  h[11][idx]->Fill(tq_rf_pt/GeV,wt);
	  h[12][idx]->Fill(dR_B0Ks,wt);

	  weight = wt;
	  newtree_bkg->Fill();
	}
      }
    }
  }

  for(Int_t i=0; i<NN; i++) {    
    h[i][2]->Scale(0.0116);

    if(subtractBkg) h[i][3]->Add(h[i][4],-1);
    else htot[i]->Add(h[i][4]);

    htot[i]->Add(h[i][2]);

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
      h[i][4]->SetLineColor(kBlue);
      h[i][4]->Draw("same hist");
      h[i][2]->SetLineColor(6);
      h[i][2]->SetLineStyle(5);
      h[i][2]->Draw("same hist");
    }

    if(i==3) lg2->Draw("same");
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

    for(Int_t j=1; j<=hratio[i]->GetNbinsX(); j++) {
      Float_t tmp1 = h[i][3]->GetBinContent(j)>0 ? h[i][3]->GetBinError(j)/h[i][3]->GetBinContent(j) : 0;
      Float_t tmp2 = htot[i]->GetBinContent(j)>0 ? htot[i]->GetBinError(j)/htot[i]->GetBinContent(j) : 0;
      Float_t tmp = htot[i]->GetBinContent(j)>0 ? h[i][3]->GetBinContent(j)/htot[i]->GetBinContent(j) : 0;
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

     sprintf(str,"./plot/presel/c%d.png",i+1);
     c[i]->SaveAs(str);
  }

  TFile newfile("inputfile1.root", "recreate");
  newtree_sig->Write();
  newtree_bkg->Write();
}
