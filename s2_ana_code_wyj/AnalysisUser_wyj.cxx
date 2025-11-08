#include "AnalysisUser.h"
#include "TSystem.h"
#include "TFile.h"
#include "TString.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TTreeFormula.h"
#include <iostream>
#include <random>
#include <stdlib.h>

#define GeV 1000

using namespace std;

AnalysisUser::AnalysisUser(std::string inputfiles) :
  header(inputfiles),
  m_tree(0)
{
  Init();
}

AnalysisUser::~AnalysisUser() {
}

void AnalysisUser::initialize(const char* out, int _process, int _cat, int _type)
{
  process = _process;
  cat = _cat;
  type= _type;

  TFile* f = new TFile(out,"recreate");
  if( !f) {
    printf( "initialize(): Failed to get output file\n");
    return;
  }
  m_tree = new TTree("BPHY25","");
  m_tree->SetDirectory(f);

  DefineBranches(m_tree);
  printf("initialize(): Branches defined\n");

  rdm = new TRandom3();

  for(int i=0; i<(int)(sizeof(num_eve)/sizeof(num_eve[0])); i++) num_eve[i] = 0;
}


//This execute is for process = 1 and cat = 100, which is for Bs->B0+Ks.
void AnalysisUser::execute() {
  num_eve[0]++;
  if(!pass_grl) return;
  if(process!=1)
  {
    cout<<"process is not 1"<<endl;
    return;
  }
  num_eve[1]++; 
  Int_t candidates = TQ_n;
  if(candidates>SIZE) {
    candidates = SIZE;
  }

  Bool_t pass_cut[candidates];
  for(int i=0; i<candidates; i++) {
    pass_cut[i] = false;
     if(TQ_channel[i]==3) continue;//TQ_channel[i]!=1 && TQ_channel[i]!=2
     num_eve[2]++;

     if(!trk3_pass[i] && !trk4_pass[i]) continue;
     num_eve[3]++;
    if(type == 1)
    {
      if(trk3_charge[i]*trk4_charge[i]>0) continue;
    }
    else if(type == 3)
    {
      if(trk3_charge[i]*trk4_charge[i]<0) continue;
    }
    else
    {
      cout<<"type is not 1 or 3"<<endl;
      return;
    }
    if(Ld_type[i]!=3) continue;
    num_eve[4]++;
    
    if(Muon1_pT[i]>4000 && Muon2_pT[i]>4000 && trk5_pT[i]>500 && trk6_pT[i]>500 //&& Muon1_isMedium[i] && Muon2_isMedium[i]
    && trk3_pT[i]>800 && trk4_pT[i]>800 && Muon1_charge[i]*Muon2_charge[i]<0
    && fabs(Muon1_eta[i])<2.5 && fabs(Muon2_eta[i])<2.5 && fabs(trk3_eta[i])<2.5 && fabs(trk4_eta[i])<2.5
    && fabs(trk5_eta[i])<2.5 && fabs(trk6_eta[i])<2.5 && trk3_pass[i] && trk4_pass[i])
    {
      pass_cut[i] = true;
    }

    if(!pass_cut[i]) continue;
    num_eve[5]++;
  }
  int itq=-1;
  float TQptmin = 0;
  for(int j=0; j<candidates; j++)
  {
    if(pass_cut[j] && TQ_pT[j]>TQptmin)
    {
      itq = j;
      TQptmin = TQ_pT[j];
    }
  }

  if(itq == -1){
    return;
  }


  num_eve[6]++;
  
  channel = TQ_channel[itq];
  tq_rf_m = TQ_VTX_mass[itq];
  tq_rf_pt = TQ_pT[itq];
  tq_rf_eta = TQ_eta[itq];
  tq_rf_phi = TQ_phi[itq];
  tq_fitChi2NDF = TQ_fitChi2[itq]/TQ_fitNDF[itq];
  tq_iso = TQ_pT[itq]/TQ_PV_Ref_ptsum[itq];
  tq_pt_sig = TQ_pT[itq]/TQ_pT_error[itq];
  tq_ratio = -999;

  mu_rf_m[0] = JX_RfMuon1_m[itq];
  mu_rf_m[1] = JX_RfMuon2_m[itq];
  mu_rf_pt[0] = JX_RfMuon1_pT[itq];
  mu_rf_pt[1] = JX_RfMuon2_pT[itq];
  mu_rf_eta[0] = JX_RfMuon1_eta[itq];
  mu_rf_eta[1] = JX_RfMuon2_eta[itq];
  mu_rf_phi[0] = JX_RfMuon1_phi[itq];
  mu_rf_phi[1] = JX_RfMuon2_phi[itq];

  mu_E[0] = Muon1_e[itq];
  mu_E[1] = Muon2_e[itq];
  mu_pt[0] = Muon1_pT[itq];
  mu_pt[1] = Muon2_pT[itq];
  mu_eta[0] = Muon1_eta[itq]; 
  mu_eta[1] = Muon2_eta[itq];
  mu_phi[0] = Muon1_phi[itq];
  mu_phi[1] = Muon2_phi[itq];
  mu_charge[0] = Muon1_charge[itq];
  mu_charge[1] = Muon2_charge[itq];
  mu_d0[0] = Muon1_d0[itq];
  mu_d0[1] = Muon2_d0[itq];
  mu_z0[0] = Muon1_z0[itq];
  mu_z0[1] = Muon2_z0[itq];
  mu_isInMuonsCont[0] = 1;
  mu_isInMuonsCont[1] = 1;
  mu_isLoose[0] = Muon1_isLoose[itq];
  mu_isLoose[1] = Muon2_isLoose[itq];
  mu_isMedium[0] = Muon1_isMedium[itq];
  mu_isMedium[1] = Muon2_isMedium[itq];
  mu_isVeryLoose[0] = Muon1_isVeryLoose[itq];
  mu_isVeryLoose[1] = Muon2_isVeryLoose[itq];
  mu_isLowPt[0] = Muon1_isLowPt[itq];
  mu_isLowPt[1] = Muon2_isLowPt[itq];

  if(mu_rf_pt[0]>mu_rf_pt[1])
  {
    mu_prime_rf_m[0] = mu_rf_m[0];
    mu_prime_rf_m[1] = mu_rf_m[1];
    mu_prime_rf_pt[0] = mu_rf_pt[0];
    mu_prime_rf_pt[1] = mu_rf_pt[1];
    mu_prime_rf_eta[0] = mu_rf_eta[0];
    mu_prime_rf_eta[1] = mu_rf_eta[1];
    mu_prime_rf_phi[0] = mu_rf_phi[0];
    mu_prime_rf_phi[1] = mu_rf_phi[1];
  }
  else{
    mu_prime_rf_m[0] = mu_rf_m[1];
    mu_prime_rf_m[1] = mu_rf_m[0];
    mu_prime_rf_pt[0] = mu_rf_pt[1];
    mu_prime_rf_pt[1] = mu_rf_pt[0];
    mu_prime_rf_eta[0] = mu_rf_eta[1];
    mu_prime_rf_eta[1] = mu_rf_eta[0];
    mu_prime_rf_phi[0] = mu_rf_phi[1];
    mu_prime_rf_phi[1] = mu_rf_phi[0];    
  }

  if(mu_pt[0]>mu_pt[1])
  {
    mu_prime_charge[0] = mu_charge[0];
    mu_prime_charge[1] = mu_charge[1];  
    mu_prime_d0[0] = mu_d0[0];
    mu_prime_d0[1] = mu_d0[1];
    mu_prime_z0[0] = mu_z0[0];
    mu_prime_z0[1] = mu_z0[1];  
    mu_prime_E[0] = mu_E[0];
    mu_prime_E[1] = mu_E[1];
    mu_prime_pt[0] = mu_pt[0];
    mu_prime_pt[1] = mu_pt[1];
    mu_prime_eta[0] = mu_eta[0];
    mu_prime_eta[1] = mu_eta[1];
    mu_prime_phi[0] = mu_phi[0];
    mu_prime_phi[1] = mu_phi[1];
  }
  else{
    mu_prime_charge[0] = mu_charge[1];
    mu_prime_charge[1] = mu_charge[0];
    mu_prime_d0[0] = mu_d0[1];
    mu_prime_d0[1] = mu_d0[0];
    mu_prime_z0[0] = mu_z0[1];
    mu_prime_z0[1] = mu_z0[0];
    mu_prime_E[0] = mu_E[1];
    mu_prime_E[1] = mu_E[0];
    mu_prime_pt[0] = mu_pt[1];
    mu_prime_pt[1] = mu_pt[0];
    mu_prime_eta[0] = mu_eta[1];
    mu_prime_eta[1] = mu_eta[0];
    mu_prime_phi[0] = mu_phi[1];
    mu_prime_phi[1] = mu_phi[0];
  }

  if(TQ_channel[itq]==1)
  {
      trk_charge[0] = trk3_charge[itq];
      trk_charge[1] = trk4_charge[itq];
      trk_d0[0] = trk3_d0[itq];
      trk_d0[1] = trk4_d0[itq];
      trk_z0[0] = trk3_z0[itq];
      trk_z0[1] = trk4_z0[itq];
      trk_eta[0] = trk3_eta[itq];
      trk_eta[1] = trk4_eta[itq];
      trk_phi[0] = trk3_phi[itq];
      trk_phi[1] = trk4_phi[itq];
      trk_pt[0] = trk3_pT[itq];
      trk_pt[1] = trk4_pT[itq];
      trk_m[0] = 493.677;
      trk_m[1] = 139.570;
      trk_rf_m[0] = JX_RfTrack3_m[itq];
      trk_rf_m[1] = JX_RfTrack4_m[itq];
      trk_rf_pt[0] = JX_RfTrack3_pT[itq];
      trk_rf_pt[1] = JX_RfTrack4_pT[itq];
      trk_rf_eta[0] = JX_RfTrack3_eta[itq];
      trk_rf_eta[1] = JX_RfTrack4_eta[itq];
      trk_rf_phi[0] = JX_RfTrack3_phi[itq];
      trk_rf_phi[1] = JX_RfTrack4_phi[itq];
  }
  else if(TQ_channel[itq]==2)
  {
      trk_charge[0] = trk4_charge[itq];
      trk_charge[1] = trk3_charge[itq];
      trk_d0[0] = trk4_d0[itq];
      trk_d0[1] = trk3_d0[itq];
      trk_z0[0] = trk4_z0[itq];
      trk_z0[1] = trk3_z0[itq];
      trk_eta[0] = trk4_eta[itq];
      trk_eta[1] = trk3_eta[itq];
      trk_phi[0] = trk4_phi[itq];
      trk_phi[1] = trk3_phi[itq];
      trk_pt[0] = trk4_pT[itq];
      trk_pt[1] = trk3_pT[itq];
      trk_m[0] = 493.677;
      trk_m[1] = 139.570;
      trk_rf_m[0] = JX_RfTrack4_m[itq];
      trk_rf_m[1] = JX_RfTrack3_m[itq];
      trk_rf_pt[0] = JX_RfTrack4_pT[itq];
      trk_rf_pt[1] = JX_RfTrack3_pT[itq];
      trk_rf_eta[0] = JX_RfTrack4_eta[itq];
      trk_rf_eta[1] = JX_RfTrack3_eta[itq];
      trk_rf_phi[0] = JX_RfTrack4_phi[itq];
      trk_rf_phi[1] = JX_RfTrack3_phi[itq];
  }
  else
  {
    cout<<"channel is not 1 or 2"<<endl;
    return;
  }
  if(Ld_type[itq] == 1)
  {
    //3.3版本未给Ldtrk_d0,z0,charge赋值
    Ldtrk_charge[0] = trk5_charge[itq];
    Ldtrk_charge[1] = trk6_charge[itq];
    Ldtrk_d0[0] = trk5_d0[itq];
    Ldtrk_d0[1] = trk6_d0[itq];
    Ldtrk_z0[0] = trk5_z0[itq];
    Ldtrk_z0[1] = trk6_z0[itq];
    Ldtrk_eta[0] = trk5_eta[itq];
    Ldtrk_eta[1] = trk6_eta[itq];
    Ldtrk_phi[0] = trk5_phi[itq];
    Ldtrk_phi[1] = trk6_phi[itq];
    Ldtrk_pt[0] = trk5_pT[itq];
    Ldtrk_pt[1] = trk6_pT[itq];
    Ldtrk_m[0] = 938.272;
    Ldtrk_m[1] = 139.570;
    Ldtrk_rf_m[0] = Ld_RfTrack5_m[itq];
    Ldtrk_rf_m[1] = Ld_RfTrack6_m[itq];
    Ldtrk_rf_pt[0] = Ld_RfTrack5_pT[itq];
    Ldtrk_rf_pt[1] = Ld_RfTrack6_pT[itq];
    Ldtrk_rf_eta[0] = Ld_RfTrack5_eta[itq];
    Ldtrk_rf_eta[1] = Ld_RfTrack6_eta[itq];
    Ldtrk_rf_phi[0] = Ld_RfTrack5_phi[itq];
    Ldtrk_rf_phi[1] = Ld_RfTrack6_phi[itq];

  }
  else if(Ld_type[itq] == 2)
  {
    Ldtrk_charge[0]=trk6_charge[itq];
    Ldtrk_charge[1]=trk5_charge[itq];
    Ldtrk_d0[0]=trk6_d0[itq];
    Ldtrk_d0[1]=trk5_d0[itq];
    Ldtrk_z0[0]=trk6_z0[itq]; 
    Ldtrk_z0[1]=trk5_z0[itq];
    Ldtrk_eta[0]=trk6_eta[itq];
    Ldtrk_eta[1]=trk5_eta[itq];
    Ldtrk_phi[0]=trk6_phi[itq];
    Ldtrk_phi[1]=trk5_phi[itq];
    Ldtrk_pt[0]=trk6_pT[itq];
    Ldtrk_pt[1]=trk5_pT[itq];
    Ldtrk_m[0]=139.570;
    Ldtrk_m[1]=938.272;
    Ldtrk_rf_m[0]=Ld_RfTrack6_m[itq];
    Ldtrk_rf_m[1]=Ld_RfTrack5_m[itq];
    Ldtrk_rf_pt[0]=Ld_RfTrack6_pT[itq];
    Ldtrk_rf_pt[1]=Ld_RfTrack5_pT[itq];
    Ldtrk_rf_eta[0]=Ld_RfTrack6_eta[itq];
    Ldtrk_rf_eta[1]=Ld_RfTrack5_eta[itq];
    Ldtrk_rf_phi[0]=Ld_RfTrack6_phi[itq];
    Ldtrk_rf_phi[1]=Ld_RfTrack5_phi[itq];
  }
  else if(Ld_type[itq] == 3)
  {
    Ldtrk_charge[0] = trk5_charge[itq];
    Ldtrk_charge[1] = trk6_charge[itq];
    Ldtrk_d0[0] = trk5_d0[itq];
    Ldtrk_d0[1] = trk6_d0[itq];
    Ldtrk_z0[0] = trk5_z0[itq];
    Ldtrk_z0[1] = trk6_z0[itq];
    Ldtrk_eta[0] = trk5_eta[itq];
    Ldtrk_eta[1] = trk6_eta[itq];
    Ldtrk_phi[0] = trk5_phi[itq];
    Ldtrk_phi[1] = trk6_phi[itq];
    Ldtrk_pt[0] = trk5_pT[itq];
    Ldtrk_pt[1] = trk6_pT[itq];
    Ldtrk_m[0] = 139.570;
    Ldtrk_m[1] = 139.570;
    Ldtrk_rf_m[0] = Ld_RfTrack5_m[itq];
    Ldtrk_rf_m[1] = Ld_RfTrack6_m[itq];
    Ldtrk_rf_pt[0] = Ld_RfTrack5_pT[itq];
    Ldtrk_rf_pt[1] = Ld_RfTrack6_pT[itq];
    Ldtrk_rf_eta[0] = Ld_RfTrack5_eta[itq];
    Ldtrk_rf_eta[1] = Ld_RfTrack6_eta[itq];
    Ldtrk_rf_phi[0] = Ld_RfTrack5_phi[itq];
    Ldtrk_rf_phi[1] = Ld_RfTrack6_phi[itq];
  }
  else
  {
    cout<<"Ld_type is not 1 or 2 or 3"<<endl;
    return;
  }

  TLorentzVector mu1;
  TLorentzVector mu2;
  TLorentzVector mu1_rf;
  TLorentzVector mu2_rf;
  TLorentzVector jpsi_rf;
  TLorentzVector jpsi;
  TLorentzVector Ldp;
  TLorentzVector Ldpi;
  TLorentzVector Ks;
  TLorentzVector Kstar1;
  TLorentzVector Kstar2;
  TLorentzVector Kstar;
  TLorentzVector b0;
  TLorentzVector tq;

  mu1.SetPtEtaPhiE(Muon1_pT[itq], Muon1_eta[itq], Muon1_phi[itq], Muon1_e[itq]);//105.658
  mu2.SetPtEtaPhiE(Muon2_pT[itq], Muon2_eta[itq], Muon2_phi[itq], Muon2_e[itq]);
  mu1_rf.SetPtEtaPhiM(JX_RfMuon1_pT[itq], JX_RfMuon1_eta[itq], JX_RfMuon1_phi[itq], JX_RfMuon1_m[itq]);
  mu2_rf.SetPtEtaPhiM(JX_RfMuon2_pT[itq], JX_RfMuon2_eta[itq], JX_RfMuon2_phi[itq], JX_RfMuon2_m[itq]);
  jpsi_rf = mu1_rf + mu2_rf;
  jpsi = mu1 + mu2;
 
  Ldp.SetPtEtaPhiM(Ldtrk_pt[0], Ldtrk_eta[0], Ldtrk_phi[0], Ldtrk_m[0]);
  Ldpi.SetPtEtaPhiM(Ldtrk_pt[1], Ldtrk_eta[1], Ldtrk_phi[1], Ldtrk_m[1]);
  Ks=Ldp+Ldpi;

  Kstar1.SetPtEtaPhiM(trk_pt[0], trk_eta[0], trk_phi[0], trk_m[0]);
  Kstar2.SetPtEtaPhiM(trk_pt[1], trk_eta[1], trk_phi[1], trk_m[1]);
  Kstar=Kstar1+Kstar2;

  b0=jpsi+Kstar;

  tq=b0+Ks;

  ld_rf_m = Ld_m[itq];
  ld_rf_pt = Ld_pT[itq];
  ld_rf_eta = Ld_eta[itq];
  ld_rf_phi = Ld_phi[itq];
  ld_fitChi2NDF = Ld_fitChi2[itq]/Ld_fitNDF[itq];
  ld_Lxy = Ld_lxy[itq];
  ld_Lxy_err = Ld_lxyErr[itq];
  ld_Lxy_sig = Ld_lxy[itq]/Ld_lxyErr[itq];
  ld_a0xy = Ld_a0xy[itq];
  ld_a0xy_err = Ld_a0xyErr[itq];
  ld_a0z = Ld_a0z[itq];
  ld_a0z_err = Ld_a0zErr[itq];
  TLorentzVector ld_rf;
  ld_rf.SetPtEtaPhiM(Ld_pT[itq], Ld_eta[itq], Ld_phi[itq], Ld_m[itq]);
  ld_rf_y = ld_rf.Rapidity();
  ld_m = Ks.M();
  ld_pt = Ks.Pt();
  ld_eta = Ks.Eta();
  ld_phi = Ks.Phi();

  jpsi_rf_m = jpsi_rf.M();
  jpsi_rf_pt = jpsi_rf.Pt();
  jpsi_rf_eta = jpsi_rf.Eta();
  jpsi_rf_phi = jpsi_rf.Phi();
  jpsi_rf_y = jpsi_rf.Rapidity();

  jpsi_m = jpsi.M();
  jpsi_pt = jpsi.Pt();
  jpsi_eta = jpsi.Eta();
  jpsi_phi = jpsi.Phi();
  jpsi_y = jpsi.Rapidity();

  jx_rf_m=JX_m[itq];
  jx_rf_pt=JX_pT[itq];
  jx_rf_eta=JX_eta[itq];
  jx_rf_phi=JX_phi[itq];
  jx_fitChi2=JX_fitChi2[itq];
  jx_fitChi2NDF=JX_fitChi2[itq]/JX_fitNDF[itq];
  jx_Lxy=JX_lxy[itq];
  jx_Lxy_err=JX_lxyErr[itq];

  jx_m = b0.M();
  jx_pt = b0.Pt();
  jx_eta = b0.Eta();
  jx_phi = b0.Phi();

  Kst_m = Kstar.M();
  Kst_pt = Kstar.Pt();
  Kst_eta = Kstar.Eta();
  Kst_phi = Kstar.Phi();
  Kst_y = Kstar.Rapidity();

  tq_m = tq.M();
  tq_pt = tq.Pt();
  tq_eta = tq.Eta();
  tq_phi = tq.Phi();
  tq_y = tq.Rapidity();
  
  bool Jpsi_window = false;
  bool Ld_window = false;  
  Ld_window = ((ld_m/GeV> 0.25 && ld_m/GeV< 0.75));
  Jpsi_window = ((jpsi_m/GeV>2.5 && jpsi_m/GeV<3.6));
  
  bool pass_window = Ld_window && Jpsi_window;
  if(!pass_window) return;
  /*
  bool pass_Ccut =0;
  if(
    jx_m > 4979 && jx_m < 5579 && ld_m > 477 && ld_m < 517 
    && jpsi_m > 2800 && jpsi_m < 3400 && Kst_m > 845 && Kst_m < 945
    && tq_fitChi2NDF < 3 && ld_fitChi2NDF < 3 && jx_fitChi2NDF < 3
    && ld_Lxy > 5 && ld_Lxy < 400 && jx_Lxy > 0.3
    && tq_iso > 0.3
  )
  {
    pass_Ccut =1;
  }
  if(!pass_Ccut) return;*/
  m_tree->Fill();
}

void AnalysisUser::finalize()
{
  const char* name_eve[6] = {
		"entries",
		"process",
		"channel",
		"trkpass",
		"charge",
		"cut"
	  };
	  printf(">>> Event:\n");
	  for(Int_t i=0;i<6;i++){
		printf("%s: %d\n",name_eve[i],num_eve[i]);
	  }
  m_tree->AutoSave();
}

void AnalysisUser::DefineBranches(TTree * tr) {
  tr->Branch("process",&process,"process/I");
  tr->Branch("channel",&channel,"channel/I");
  tr->Branch("cat",&cat,"cat/I");
  tr->Branch("run_number"  , &run_number);
  tr->Branch("event_number", &event_number);
  tr->Branch("lumi_block", &lumi_block);
  tr->Branch("evt_wt", &evt_wt);
  tr->Branch("trig_wt", &trig_wt);
  tr->Branch("global_match", &global_match);
  tr->Branch("pu_wt", &pu_wt);
  tr->Branch("pu_wt_sys_up", &pu_wt_sys_up);
  tr->Branch("pu_wt_sys_dn", &pu_wt_sys_dn);
  tr->Branch("corr_scaled_mu", &corr_scaled_mu);
  tr->Branch("TQ_n", &TQ_n, "TQ_n/I");
  tr->Branch("pass_trigger", &pass_trigger);

  tr->Branch("tq_m",&tq_m,"tq_m/F");
  tr->Branch("tq_fitChi2NDF",&tq_fitChi2NDF,"tq_fitChi2NDF/F");
  tr->Branch("tq_iso",&tq_iso,"tq_iso/F");
  tr->Branch("tq_eta",&tq_eta,"tq_eta/F");
  tr->Branch("tq_phi",&tq_phi,"tq_phi/F");
  tr->Branch("tq_pt",&tq_pt,"tq_pt/F");
  tr->Branch("tq_pt_err",&tq_pt_err,"tq_pt_err/F");
  tr->Branch("tq_pt_sig",&tq_pt_sig,"tq_pt_sig/F");
  tr->Branch("tq_Lxy",&tq_Lxy,"tq_Lxy/F");
  tr->Branch("tq_Lxy_err",&tq_Lxy_err,"tq_Lxy_err/F");
  tr->Branch("tq_Lxy_sig",&tq_Lxy_sig,"tq_Lxy_sig/F");
  tr->Branch("tq_PV_idx",&tq_PV_idx,"tq_PV_idx/I");
  tr->Branch("tq_a0xy",&tq_a0xy,"tq_a0xy/F");
  tr->Branch("tq_a0xy_err",&tq_a0xy_err,"tq_a0xy_err/F");
  tr->Branch("tq_z0",&tq_z0,"tq_z0/F");
  tr->Branch("tq_z0_err",&tq_z0_err,"tq_z0_err/F");
  tr->Branch("tq_ratio",&tq_ratio,"tq_ratio/F");
  tr->Branch("tq_rf_m",&tq_rf_m,"tq_rf_m/F");
  tr->Branch("tq_rf_pt",&tq_rf_pt,"tq_rf_pt/F");
  tr->Branch("tq_rf_eta",&tq_rf_eta,"tq_rf_eta/F");
  tr->Branch("tq_rf_phi",&tq_rf_phi,"tq_rf_phi/F");
  
  tr->Branch("jpsi_rf_m",&jpsi_rf_m,"jpsi_rf_m/F");
  tr->Branch("jpsi_rf_pt",&jpsi_rf_pt,"jpsi_rf_pt/F");
  tr->Branch("jpsi_rf_eta",&jpsi_rf_eta,"jpsi_rf_eta/F");
  tr->Branch("jpsi_rf_phi",&jpsi_rf_phi,"jpsi_rf_phi/F");
  tr->Branch("jpsi_rf_y",&jpsi_rf_y,"jpsi_rf_y/F");
  tr->Branch("jpsi_m",&jpsi_m,"jpsi_m/F");
  tr->Branch("jpsi_pt",&jpsi_pt,"jpsi_pt/F");
  tr->Branch("jpsi_eta",&jpsi_eta,"jpsi_eta/F");
  tr->Branch("jpsi_phi",&jpsi_phi,"jpsi_phi/F");
  tr->Branch("jpsi_y",&jpsi_y,"jpsi_y/F");

  tr->Branch("ld_m",&ld_m,"ld_m/F");
  tr->Branch("ld_fitChi2NDF",&ld_fitChi2NDF,"ld_fitChi2NDF/F");
  tr->Branch("ld_eta",&ld_eta,"ld_eta/F");
  tr->Branch("ld_phi",&ld_phi,"ld_phi/F");
  tr->Branch("ld_pt",&ld_pt,"ld_pt/F");
  tr->Branch("ld_y",&ld_y,"ld_y/F");
  tr->Branch("ld_pt_err",&ld_pt_err,"ld_pt_err/F");
  tr->Branch("ld_Lxy",&ld_Lxy,"ld_Lxy/F");
  tr->Branch("ld_Lxy_err",&ld_Lxy_err,"ld_Lxy_err/F");
  tr->Branch("ld_Lxy_sig",&ld_Lxy_sig,"ld_Lxy_sig/F");
  tr->Branch("ld_a0xy",&ld_a0xy,"ld_a0xy/F");
  tr->Branch("ld_a0xy_err",&ld_a0xy_err,"ld_a0xy_err/F");
  tr->Branch("ld_a0z",&ld_a0z,"ld_a0z/F");
  tr->Branch("ld_a0z_err",&ld_a0z_err,"ld_a0z_err/F");
  tr->Branch("ld_rf_m",&ld_rf_m,"ld_rf_m/F");
  tr->Branch("ld_rf_pt",&ld_rf_pt,"ld_rf_pt/F");
  tr->Branch("ld_rf_eta",&ld_rf_eta,"ld_rf_eta/F");
  tr->Branch("ld_rf_phi",&ld_rf_phi,"ld_rf_phi/F");
  tr->Branch("ld_rf_y",&ld_rf_y,"ld_rf_y/F");
  tr->Branch("Kst_m",&Kst_m,"Kst_m/F");
  tr->Branch("Kst_pt",&Kst_pt,"Kst_pt/F");  
  tr->Branch("Kst_eta",&Kst_eta,"Kst_eta/F");  
  tr->Branch("Kst_phi",&Kst_phi,"Kst_phi/F");  
  tr->Branch("Kst_y",&Kst_y,"Kst_y/F");  
  tr->Branch("mu_rf_m",mu_rf_m,"mu_rf_m[2]/F");
  tr->Branch("mu_rf_pt",mu_rf_pt,"mu_rf_pt[2]/F");
  tr->Branch("mu_rf_eta",mu_rf_eta,"mu_rf_eta[2]/F");
  tr->Branch("mu_rf_phi",mu_rf_phi,"mu_rf_phi[2]/F");
  tr->Branch("mu_E",mu_E,"mu_E[2]/F");
  tr->Branch("mu_pt",mu_pt,"mu_pt[2]/F");
  tr->Branch("mu_eta",mu_eta,"mu_eta[2]/F");
  tr->Branch("mu_phi",mu_phi,"mu_phi[2]/F");
  tr->Branch("mu_charge",mu_charge,"mu_charge[2]/F");
  tr->Branch("mu_d0",mu_d0,"mu_d0[2]/F");
  tr->Branch("mu_z0",mu_z0,"mu_z0[2]/F");
  tr->Branch("mu_prime_rf_m",mu_prime_rf_m,"mu_prime_rf_m[2]/F");
  tr->Branch("mu_prime_rf_pt",mu_prime_rf_pt,"mu_prime_rf_pt[2]/F");
  tr->Branch("mu_prime_rf_eta",mu_prime_rf_eta,"mu_prime_rf_eta[2]/F");
  tr->Branch("mu_prime_rf_phi",mu_prime_rf_phi,"mu_prime_rf_phi[2]/F");
  tr->Branch("mu_prime_E",mu_prime_E,"mu_prime_E[2]/F");
  tr->Branch("mu_prime_pt",mu_prime_pt,"mu_prime_pt[2]/F");
  tr->Branch("mu_prime_eta",mu_prime_eta,"mu_prime_eta[2]/F");
  tr->Branch("mu_prime_phi",mu_prime_phi,"mu_prime_phi[2]/F");
  tr->Branch("mu_prime_charge",mu_prime_charge,"mu_prime_charge[2]/F");
  tr->Branch("mu_prime_d0",mu_prime_d0,"mu_prime_d0[2]/F");
  tr->Branch("mu_prime_z0",mu_prime_z0,"mu_prime_z0[2]/F");
  tr->Branch("mu_isMuon",mu_isMuon,"mu_isMuon[2]/O");
  tr->Branch("mu_isMedium",mu_isMedium,"mu_isMedium[2]/O");
  tr->Branch("mu_isLoose",mu_isLoose,"mu_isLoose[2]/O");
  tr->Branch("mu_isVeryLoose",mu_isVeryLoose,"mu_isVeryLoose[2]/O");
  tr->Branch("mu_isLowPt",mu_isLowPt,"mu_isLowPt[2]/O");
  tr->Branch("mu_isLowPtMVA",mu_isLowPtMVA,"mu_isLowPtMVA[2]/O");
  tr->Branch("mu_isCombinedMuon",mu_isCombinedMuon,"mu_isCombinedMuon[2]/O");
  tr->Branch("mu_isInMuonsCont",mu_isInMuonsCont,"mu_isInMuonsCont[2]/O");
  // tr->Branch("mu_passID",mu_passID,"mu_passID[2]/O");
  tr->Branch("mu_medium_eff_sf",mu_medium_eff_sf,"mu_medium_eff_sf[2]/F");
  tr->Branch("mu_medium_eff_sf_up",mu_medium_eff_sf_up,"mu_medium_eff_sf_up[2][2]/F");
  tr->Branch("mu_medium_eff_sf_down",mu_medium_eff_sf_down,"mu_medium_eff_sf_down[2][2]/F");
  tr->Branch("mu_lowptMVA_eff_sf",mu_lowptMVA_eff_sf,"mu_lowptMVA_eff_sf[2]/F");
  tr->Branch("mu_lowptMVA_eff_sf_up",mu_lowptMVA_eff_sf_up,"mu_lowptMVA_eff_sf_up[2][2]/F");
  tr->Branch("mu_lowptMVA_eff_sf_down",mu_lowptMVA_eff_sf_down,"mu_lowptMVA_eff_sf_down[2][2]/F");
  tr->Branch("mu_loose_eff_sf",mu_loose_eff_sf,"mu_loose_eff_sf[2]/F");
  tr->Branch("mu_loose_eff_sf_up",mu_loose_eff_sf_up,"mu_loose_eff_sf_up[2][2]/F");
  tr->Branch("mu_loose_eff_sf_down",mu_loose_eff_sf_down,"mu_loose_eff_sf_down[2][2]/F");
  tr->Branch("mu_scale_up",mu_scale_up,"mu_scale_up[2][2]/F");
  tr->Branch("mu_scale_down",mu_scale_down,"mu_scale_down[2][2]/F");
  tr->Branch("mu_scale_nominal",mu_scale_up,"mu_scale_nominal[2]/F");
  tr->Branch("trk_rf_m",trk_rf_m,"trk_rf_m[2]/F");
  tr->Branch("trk_rf_pt",trk_rf_pt,"trk_rf_pt[2]/F");
  tr->Branch("trk_rf_eta",trk_rf_eta,"trk_rf_eta[2]/F");
  tr->Branch("trk_rf_phi",trk_rf_phi,"trk_rf_phi[2]/F");
  tr->Branch("trk_m",trk_m,"trk_m[2]/F");
  tr->Branch("trk_pt",trk_pt,"trk_pt[2]/F");
  tr->Branch("trk_eta",trk_eta,"trk_eta[2]/F");
  tr->Branch("trk_phi",trk_phi,"trk_phi[2]/F");
  tr->Branch("trk_charge",trk_charge,"trk_charge[2]/F");
  tr->Branch("trk_d0",trk_d0,"trk_d0[2]/F");
  tr->Branch("trk_z0",trk_z0,"trk_z0[2]/F");
  tr->Branch("Ldtrk_rf_m",Ldtrk_rf_m,"Ldtrk_rf_m[2]/F");
  tr->Branch("Ldtrk_rf_pt",Ldtrk_rf_pt,"Ldtrk_rf_pt[2]/F");
  tr->Branch("Ldtrk_rf_eta",Ldtrk_rf_eta,"Ldtrk_rf_eta[2]/F");
  tr->Branch("Ldtrk_rf_phi",Ldtrk_rf_phi,"Ldtrk_rf_phi[2]/F");
  tr->Branch("Ldtrk_m",Ldtrk_m,"Ldtrk_m[2]/F");
  tr->Branch("Ldtrk_pt",Ldtrk_pt,"Ldtrk_pt[2]/F");
  tr->Branch("Ldtrk_eta",Ldtrk_eta,"Ldtrk_eta[2]/F");
  tr->Branch("Ldtrk_phi",Ldtrk_phi,"Ldtrk_phi[2]/F");
  tr->Branch("Ldtrk_charge",Ldtrk_charge,"Ldtrk_charge[2]/F");
  tr->Branch("Ldtrk_d0",Ldtrk_d0,"Ldtrk_d0[2]/F");
  tr->Branch("Ldtrk_z0",Ldtrk_z0,"Ldtrk_z0[2]/F");
  tr->Branch("jx_rf_m",&jx_rf_m,"jx_rf_m/F");
  tr->Branch("jx_rf_pt",&jx_rf_pt,"jx_rf_pt/F");
  tr->Branch("jx_rf_eta",&jx_rf_eta,"jx_rf_eta/F");
  tr->Branch("jx_rf_phi",&jx_rf_phi,"jx_rf_phi/F");
  tr->Branch("jx_rf_y",&jx_rf_y,"jx_rf_y/F");
  tr->Branch("jx_m",&jx_m,"jx_m/F");
  tr->Branch("jx_pt",&jx_pt,"jx_pt/F");
  tr->Branch("jx_eta",&jx_eta,"jx_eta/F");
  tr->Branch("jx_phi",&jx_phi,"jx_phi/F");
  tr->Branch("jx_y",&jx_y,"jx_y/F");
  tr->Branch("jx_fitChi2",&jx_fitChi2,"jx_fitChi2/F");
  tr->Branch("jx_fitChi2NDF",&jx_fitChi2NDF,"jx_fitChi2NDF/F");
  tr->Branch("jx_Lxy",&jx_Lxy,"jx_Lxy/F");
  tr->Branch("jx_Lxy_err",&jx_Lxy_err,"jx_Lxy_err/F");    
  tr->Branch("truth_n",&truth_n,"truth_n/I");
  tr->Branch("truth_pdgId",truth_pdgId,"truth_pdgId[truth_n]/I");
  tr->Branch("truth_motherID",truth_motherID,"truth_motherID[truth_n]/I");
  tr->Branch("truth_mass",truth_mass,"truth_mass[truth_n]/D");
  tr->Branch("truth_pT",truth_pT,"truth_pT[truth_n]/D");
  tr->Branch("truth_eta",truth_eta,"truth_eta[truth_n]/D");
  tr->Branch("truth_phi",truth_phi,"truth_phi[truth_n]/D");
  tr->Branch("match", match,"match[TQ_n]/I");


}


