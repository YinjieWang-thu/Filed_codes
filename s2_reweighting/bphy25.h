//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 13 17:40:00 2025 by ROOT version 6.32.04
// from TTree BPHY25/
// found on file: BPHY25_B0Ks_SS_OS.root
//////////////////////////////////////////////////////////

#ifndef bphy25_h
#define bphy25_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class bphy25 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           cat;
   UInt_t          run_number;
   ULong64_t       event_number;
   Int_t           lumi_block;
   Float_t         evt_wt;
   Float_t         trig_wt;
   Float_t         pu_wt;
   Float_t         pu_wt_sys_up;
   Float_t         pu_wt_sys_dn;
   Float_t         corr_scaled_mu;
   Bool_t          pass_trigger;
   Int_t           tq_channel;
   Float_t         tq_m;
   Float_t         tq_fitChi2NDF;
   Float_t         tq_eta;
   Float_t         tq_phi;
   Float_t         tq_pt;
   Float_t         tq_pt_err;
   Float_t         tq_pt_sig;
   Float_t         tq_Lxy;
   Float_t         tq_Lxy_err;
   Float_t         tq_Lxy_sig;
   Int_t           tq_PV_idx;
   Float_t         tq_a0xy;
   Float_t         tq_a0xy_err;
   Float_t         tq_z0;
   Float_t         tq_z0_err;
   Float_t         tq_ratio;
   Float_t         tq_m_calc;
   Float_t         jx_fitChi2NDF;
   Float_t         jx_Lxy;
   Float_t         jx_rf_m;
   Float_t         jx_rf_pt;
   Float_t         jx_rf_eta;
   Float_t         jx_rf_phi;
   Float_t         jx_rf_y;
   Float_t         jx_m_calc;
   Float_t         jx_m;
   Float_t         jx_pt;
   Float_t         jx_eta;
   Float_t         jx_phi;
   Float_t         jx_y;
   Float_t         jx_ratio;
   Float_t         jpsi_rf_m;
   Float_t         jpsi_rf_pt;
   Float_t         jpsi_rf_eta;
   Float_t         jpsi_rf_phi;
   Float_t         jpsi_rf_y;
   Float_t         jpsi_m;
   Float_t         jpsi_pt;
   Float_t         jpsi_eta;
   Float_t         jpsi_phi;
   Float_t         jpsi_y;
   Float_t         x_rf_m;
   Float_t         x_rf_pt;
   Float_t         x_rf_eta;
   Float_t         x_rf_phi;
   Float_t         x_rf_y;
   Float_t         x_m;
   Float_t         x_pt;
   Float_t         x_eta;
   Float_t         x_phi;
   Float_t         x_y;
   Int_t           ld_type;
   Float_t         ld_fitChi2NDF;
   Float_t         ld_Lxy;
   Float_t         ld_gfitChi2NDF;
   Float_t         ld_gmass;
   Float_t         ld_rf_m;
   Float_t         ld_rf_pt;
   Float_t         ld_rf_eta;
   Float_t         ld_rf_phi;
   Float_t         ld_rf_y;
   Float_t         ld_m;
   Float_t         ld_pt;
   Float_t         ld_eta;
   Float_t         ld_phi;
   Float_t         ld_y;
   Float_t         jpsiLd_m;
   Float_t         jpsiLd_pt;
   Float_t         jpsiLd_eta;
   Float_t         jpsiLd_phi;
   Float_t         jpsiLd_y;
   Float_t         xLd_m;
   Float_t         xLd_pt;
   Float_t         xLd_eta;
   Float_t         xLd_phi;
   Float_t         xLd_y;
   Float_t         d_Lxy;
   Float_t         d_Lxy_err;
   Float_t         d_a0xy;
   Float_t         d_a0xy_err;
   Float_t         d_a0z;
   Float_t         d_a0z_err;
   Float_t         Dpm_rf_m;
   Float_t         Dpm_rf_pt;
   Float_t         Dpm_rf_eta;
   Float_t         Dpm_rf_phi;
   Float_t         Dpm_rf_y;
   Float_t         D0_rf_m;
   Float_t         D0_rf_pt;
   Float_t         D0_rf_eta;
   Float_t         D0_rf_phi;
   Float_t         D0_rf_y;
   Float_t         Dst_rf_m;
   Float_t         Dst_rf_pt;
   Float_t         Dst_rf_eta;
   Float_t         Dst_rf_phi;
   Float_t         Dst_rf_y;
   Float_t         Dpm_m;
   Float_t         Dpm_pt;
   Float_t         Dpm_eta;
   Float_t         Dpm_phi;
   Float_t         Dpm_y;
   Float_t         D0_m;
   Float_t         D0_pt;
   Float_t         D0_eta;
   Float_t         D0_phi;
   Float_t         D0_y;
   Float_t         Dst_m;
   Float_t         Dst_pt;
   Float_t         Dst_eta;
   Float_t         Dst_phi;
   Float_t         Dst_y;
   Float_t         Dst_m_calc;
   Float_t         mu_rf_m[2];
   Float_t         mu_rf_pt[2];
   Float_t         mu_rf_eta[2];
   Float_t         mu_rf_phi[2];
   Float_t         mu_E[2];
   Float_t         mu_pt[2];
   Float_t         mu_eta[2];
   Float_t         mu_phi[2];
   Float_t         mu_charge[2];
   Float_t         mu_d0[2];
   Float_t         mu_z0[2];
   Bool_t          mu_isMuon[2];
   Bool_t          mu_isMedium[2];
   Bool_t          mu_isLoose[2];
   Bool_t          mu_isVeryLoose[2];
   Bool_t          mu_isLowPt[2];
   Bool_t          mu_isCombinedMuon[2];
   Bool_t          mu_isInMuonsCont[2];
   Bool_t          mu_passID[2];
   Float_t         mu_medium_eff_sf[2];
   Float_t         mu_medium_eff_sf_up[2][4];
   Float_t         mu_medium_eff_sf_down[2][4];
   Float_t         mu_lowpt_eff_sf[2];
   Float_t         mu_lowpt_eff_sf_up[2][4];
   Float_t         mu_lowpt_eff_sf_down[2][4];
   Float_t         mu_loose_eff_sf[2];
   Float_t         mu_loose_eff_sf_up[2][4];
   Float_t         mu_loose_eff_sf_down[2][4];
   Float_t         mu_scale_up[2][6];
   Float_t         mu_scale_down[2][6];
   Float_t         mu_scale_nominal[2];
   Float_t         trk_rf_m[7];
   Float_t         trk_rf_pt[7];
   Float_t         trk_rf_eta[7];
   Float_t         trk_rf_phi[7];
   Float_t         trk_m[7];
   Float_t         trk_pt[7];
   Float_t         trk_eta[7];
   Float_t         trk_phi[7];
   Float_t         trk_charge[7];
   Float_t         trk_d0[7];
   Float_t         trk_z0[7];
   Float_t         pt_mu1;
   Float_t         pt_mu2;
   Float_t         pt_trk1;
   Float_t         pt_trk2;
   Float_t         pt_LRT_trk1;
   Float_t         pt_LRT_trk2;
   Float_t         pt_K;
   Float_t         eta_K;
   Float_t         phi_K;
   Float_t         pt_pi;
   Float_t         eta_pi;
   Float_t         phi_pi;
   Float_t         pt_p_Ld;
   Float_t         pt_pi_Ld;
   Float_t         pt_pi1_D;
   Float_t         pt_pi2_D;
   Int_t           truth_n;
   Int_t           truth_pdgId[1];   //[truth_n]
   Int_t           truth_motherID[1];   //[truth_n]
   Double_t        truth_mass[1];   //[truth_n]
   Double_t        truth_pT[1];   //[truth_n]
   Double_t        truth_eta[1];   //[truth_n]
   Double_t        truth_phi[1];   //[truth_n]

   // List of branches
   TBranch        *b_cat;   //!
   TBranch        *b_run_number;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_lumi_block;   //!
   TBranch        *b_evt_wt;   //!
   TBranch        *b_trig_wt;   //!
   TBranch        *b_pu_wt;   //!
   TBranch        *b_pu_wt_sys_up;   //!
   TBranch        *b_pu_wt_sys_dn;   //!
   TBranch        *b_corr_scaled_mu;   //!
   TBranch        *b_pass_trigger;   //!
   TBranch        *b_tq_channel;   //!
   TBranch        *b_tq_m;   //!
   TBranch        *b_tq_fitChi2NDF;   //!
   TBranch        *b_tq_eta;   //!
   TBranch        *b_tq_phi;   //!
   TBranch        *b_tq_pt;   //!
   TBranch        *b_tq_pt_err;   //!
   TBranch        *b_tq_pt_sig;   //!
   TBranch        *b_tq_Lxy;   //!
   TBranch        *b_tq_Lxy_err;   //!
   TBranch        *b_tq_Lxy_sig;   //!
   TBranch        *b_tq_PV_idx;   //!
   TBranch        *b_tq_a0xy;   //!
   TBranch        *b_tq_a0xy_err;   //!
   TBranch        *b_tq_z0;   //!
   TBranch        *b_tq_z0_err;   //!
   TBranch        *b_tq_ratio;   //!
   TBranch        *b_tq_m_calc;   //!
   TBranch        *b_jx_fitChi2NDF;   //!
   TBranch        *b_jx_Lxy;   //!
   TBranch        *b_jx_rf_m;   //!
   TBranch        *b_jx_rf_pt;   //!
   TBranch        *b_jx_rf_eta;   //!
   TBranch        *b_jx_rf_phi;   //!
   TBranch        *b_jx_rf_y;   //!
   TBranch        *b_jx_m_calc;   //!
   TBranch        *b_jx_m;   //!
   TBranch        *b_jx_pt;   //!
   TBranch        *b_jx_eta;   //!
   TBranch        *b_jx_phi;   //!
   TBranch        *b_jx_y;   //!
   TBranch        *b_jx_ratio;   //!
   TBranch        *b_jpsi_rf_m;   //!
   TBranch        *b_jpsi_rf_pt;   //!
   TBranch        *b_jpsi_rf_eta;   //!
   TBranch        *b_jpsi_rf_phi;   //!
   TBranch        *b_jpsi_rf_y;   //!
   TBranch        *b_jpsi_m;   //!
   TBranch        *b_jpsi_pt;   //!
   TBranch        *b_jpsi_eta;   //!
   TBranch        *b_jpsi_phi;   //!
   TBranch        *b_jpsi_y;   //!
   TBranch        *b_x_rf_m;   //!
   TBranch        *b_x_rf_pt;   //!
   TBranch        *b_x_rf_eta;   //!
   TBranch        *b_x_rf_phi;   //!
   TBranch        *b_x_rf_y;   //!
   TBranch        *b_x_m;   //!
   TBranch        *b_x_pt;   //!
   TBranch        *b_x_eta;   //!
   TBranch        *b_x_phi;   //!
   TBranch        *b_x_y;   //!
   TBranch        *b_ld_type;   //!
   TBranch        *b_ld_fitChi2NDF;   //!
   TBranch        *b_ld_Lxy;   //!
   TBranch        *b_ld_gfitChi2NDF;   //!
   TBranch        *b_ld_gmass;   //!
   TBranch        *b_ld_rf_m;   //!
   TBranch        *b_ld_rf_pt;   //!
   TBranch        *b_ld_rf_eta;   //!
   TBranch        *b_ld_rf_phi;   //!
   TBranch        *b_ld_rf_y;   //!
   TBranch        *b_ld_m;   //!
   TBranch        *b_ld_pt;   //!
   TBranch        *b_ld_eta;   //!
   TBranch        *b_ld_phi;   //!
   TBranch        *b_ld_y;   //!
   TBranch        *b_jpsiLd_m;   //!
   TBranch        *b_jpsiLd_pt;   //!
   TBranch        *b_jpsiLd_eta;   //!
   TBranch        *b_jpsiLd_phi;   //!
   TBranch        *b_jpsiLd_y;   //!
   TBranch        *b_xLd_m;   //!
   TBranch        *b_xLd_pt;   //!
   TBranch        *b_xLd_eta;   //!
   TBranch        *b_xLd_phi;   //!
   TBranch        *b_xLd_y;   //!
   TBranch        *b_d_Lxy;   //!
   TBranch        *b_d_Lxy_err;   //!
   TBranch        *b_d_a0xy;   //!
   TBranch        *b_d_a0xy_err;   //!
   TBranch        *b_d_a0z;   //!
   TBranch        *b_d_a0z_err;   //!
   TBranch        *b_Dpm_rf_m;   //!
   TBranch        *b_Dpm_rf_pt;   //!
   TBranch        *b_Dpm_rf_eta;   //!
   TBranch        *b_Dpm_rf_phi;   //!
   TBranch        *b_Dpm_rf_y;   //!
   TBranch        *b_D0_rf_m;   //!
   TBranch        *b_D0_rf_pt;   //!
   TBranch        *b_D0_rf_eta;   //!
   TBranch        *b_D0_rf_phi;   //!
   TBranch        *b_D0_rf_y;   //!
   TBranch        *b_Dst_rf_m;   //!
   TBranch        *b_Dst_rf_pt;   //!
   TBranch        *b_Dst_rf_eta;   //!
   TBranch        *b_Dst_rf_phi;   //!
   TBranch        *b_Dst_rf_y;   //!
   TBranch        *b_Dpm_m;   //!
   TBranch        *b_Dpm_pt;   //!
   TBranch        *b_Dpm_eta;   //!
   TBranch        *b_Dpm_phi;   //!
   TBranch        *b_Dpm_y;   //!
   TBranch        *b_D0_m;   //!
   TBranch        *b_D0_pt;   //!
   TBranch        *b_D0_eta;   //!
   TBranch        *b_D0_phi;   //!
   TBranch        *b_D0_y;   //!
   TBranch        *b_Dst_m;   //!
   TBranch        *b_Dst_pt;   //!
   TBranch        *b_Dst_eta;   //!
   TBranch        *b_Dst_phi;   //!
   TBranch        *b_Dst_y;   //!
   TBranch        *b_Dst_m_calc;   //!
   TBranch        *b_mu_rf_m;   //!
   TBranch        *b_mu_rf_pt;   //!
   TBranch        *b_mu_rf_eta;   //!
   TBranch        *b_mu_rf_phi;   //!
   TBranch        *b_mu_E;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_d0;   //!
   TBranch        *b_mu_z0;   //!
   TBranch        *b_mu_isMuon;   //!
   TBranch        *b_mu_isMedium;   //!
   TBranch        *b_mu_isLoose;   //!
   TBranch        *b_mu_isVeryLoose;   //!
   TBranch        *b_mu_isLowPt;   //!
   TBranch        *b_mu_isCombinedMuon;   //!
   TBranch        *b_mu_isInMuonsCont;   //!
   TBranch        *b_mu_passID;   //!
   TBranch        *b_mu_medium_eff_sf;   //!
   TBranch        *b_mu_medium_eff_sf_up;   //!
   TBranch        *b_mu_medium_eff_sf_down;   //!
   TBranch        *b_mu_lowpt_eff_sf;   //!
   TBranch        *b_mu_lowpt_eff_sf_up;   //!
   TBranch        *b_mu_lowpt_eff_sf_down;   //!
   TBranch        *b_mu_loose_eff_sf;   //!
   TBranch        *b_mu_loose_eff_sf_up;   //!
   TBranch        *b_mu_loose_eff_sf_down;   //!
   TBranch        *b_mu_scale_up;   //!
   TBranch        *b_mu_scale_down;   //!
   TBranch        *b_mu_scale_nominal;   //!
   TBranch        *b_trk_rf_m;   //!
   TBranch        *b_trk_rf_pt;   //!
   TBranch        *b_trk_rf_eta;   //!
   TBranch        *b_trk_rf_phi;   //!
   TBranch        *b_trk_m;   //!
   TBranch        *b_trk_pt;   //!
   TBranch        *b_trk_eta;   //!
   TBranch        *b_trk_phi;   //!
   TBranch        *b_trk_charge;   //!
   TBranch        *b_trk_d0;   //!
   TBranch        *b_trk_z0;   //!
   TBranch        *b_pt_mu1;   //!
   TBranch        *b_pt_mu2;   //!
   TBranch        *b_pt_trk1;   //!
   TBranch        *b_pt_trk2;   //!
   TBranch        *b_pt_LRT_trk1;   //!
   TBranch        *b_pt_LRT_trk2;   //!
   TBranch        *b_pt_K;   //!
   TBranch        *b_eta_K;   //!
   TBranch        *b_phi_K;   //!
   TBranch        *b_pt_pi;   //!
   TBranch        *b_eta_pi;   //!
   TBranch        *b_phi_pi;   //!
   TBranch        *b_pt_p_Ld;   //!
   TBranch        *b_pt_pi_Ld;   //!
   TBranch        *b_pt_pi1_D;   //!
   TBranch        *b_pt_pi2_D;   //!
   TBranch        *b_truth_n;   //!
   TBranch        *b_truth_pdgId;   //!
   TBranch        *b_truth_motherID;   //!
   TBranch        *b_truth_mass;   //!
   TBranch        *b_truth_pT;   //!
   TBranch        *b_truth_eta;   //!
   TBranch        *b_truth_phi;   //!

   bphy25(TTree *tree=0);
   virtual ~bphy25();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString outputname);
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef bphy25_cxx
bphy25::bphy25(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("BPHY25_B0Ks_SS_OS.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("BPHY25_B0Ks_SS_OS.root");
      }
      f->GetObject("BPHY25",tree);

   }
   Init(tree);
}

bphy25::~bphy25()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t bphy25::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t bphy25::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void bphy25::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("cat", &cat, &b_cat);
   fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
   fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
   fChain->SetBranchAddress("lumi_block", &lumi_block, &b_lumi_block);
   fChain->SetBranchAddress("evt_wt", &evt_wt, &b_evt_wt);
   fChain->SetBranchAddress("trig_wt", &trig_wt, &b_trig_wt);
   fChain->SetBranchAddress("pu_wt", &pu_wt, &b_pu_wt);
   fChain->SetBranchAddress("pu_wt_sys_up", &pu_wt_sys_up, &b_pu_wt_sys_up);
   fChain->SetBranchAddress("pu_wt_sys_dn", &pu_wt_sys_dn, &b_pu_wt_sys_dn);
   fChain->SetBranchAddress("corr_scaled_mu", &corr_scaled_mu, &b_corr_scaled_mu);
   fChain->SetBranchAddress("pass_trigger", &pass_trigger, &b_pass_trigger);
   fChain->SetBranchAddress("tq_channel", &tq_channel, &b_tq_channel);
   fChain->SetBranchAddress("tq_m", &tq_m, &b_tq_m);
   fChain->SetBranchAddress("tq_fitChi2NDF", &tq_fitChi2NDF, &b_tq_fitChi2NDF);
   fChain->SetBranchAddress("tq_eta", &tq_eta, &b_tq_eta);
   fChain->SetBranchAddress("tq_phi", &tq_phi, &b_tq_phi);
   fChain->SetBranchAddress("tq_pt", &tq_pt, &b_tq_pt);
   fChain->SetBranchAddress("tq_pt_err", &tq_pt_err, &b_tq_pt_err);
   fChain->SetBranchAddress("tq_pt_sig", &tq_pt_sig, &b_tq_pt_sig);
   fChain->SetBranchAddress("tq_Lxy", &tq_Lxy, &b_tq_Lxy);
   fChain->SetBranchAddress("tq_Lxy_err", &tq_Lxy_err, &b_tq_Lxy_err);
   fChain->SetBranchAddress("tq_Lxy_sig", &tq_Lxy_sig, &b_tq_Lxy_sig);
   fChain->SetBranchAddress("tq_PV_idx", &tq_PV_idx, &b_tq_PV_idx);
   fChain->SetBranchAddress("tq_a0xy", &tq_a0xy, &b_tq_a0xy);
   fChain->SetBranchAddress("tq_a0xy_err", &tq_a0xy_err, &b_tq_a0xy_err);
   fChain->SetBranchAddress("tq_z0", &tq_z0, &b_tq_z0);
   fChain->SetBranchAddress("tq_z0_err", &tq_z0_err, &b_tq_z0_err);
   fChain->SetBranchAddress("tq_ratio", &tq_ratio, &b_tq_ratio);
   fChain->SetBranchAddress("tq_m_calc", &tq_m_calc, &b_tq_m_calc);
   fChain->SetBranchAddress("jx_fitChi2NDF", &jx_fitChi2NDF, &b_jx_fitChi2NDF);
   fChain->SetBranchAddress("jx_Lxy", &jx_Lxy, &b_jx_Lxy);
   fChain->SetBranchAddress("jx_rf_m", &jx_rf_m, &b_jx_rf_m);
   fChain->SetBranchAddress("jx_rf_pt", &jx_rf_pt, &b_jx_rf_pt);
   fChain->SetBranchAddress("jx_rf_eta", &jx_rf_eta, &b_jx_rf_eta);
   fChain->SetBranchAddress("jx_rf_phi", &jx_rf_phi, &b_jx_rf_phi);
   fChain->SetBranchAddress("jx_rf_y", &jx_rf_y, &b_jx_rf_y);
   fChain->SetBranchAddress("jx_m_calc", &jx_m_calc, &b_jx_m_calc);
   fChain->SetBranchAddress("jx_m", &jx_m, &b_jx_m);
   fChain->SetBranchAddress("jx_pt", &jx_pt, &b_jx_pt);
   fChain->SetBranchAddress("jx_eta", &jx_eta, &b_jx_eta);
   fChain->SetBranchAddress("jx_phi", &jx_phi, &b_jx_phi);
   fChain->SetBranchAddress("jx_y", &jx_y, &b_jx_y);
   fChain->SetBranchAddress("jx_ratio", &jx_ratio, &b_jx_ratio);
   fChain->SetBranchAddress("jpsi_rf_m", &jpsi_rf_m, &b_jpsi_rf_m);
   fChain->SetBranchAddress("jpsi_rf_pt", &jpsi_rf_pt, &b_jpsi_rf_pt);
   fChain->SetBranchAddress("jpsi_rf_eta", &jpsi_rf_eta, &b_jpsi_rf_eta);
   fChain->SetBranchAddress("jpsi_rf_phi", &jpsi_rf_phi, &b_jpsi_rf_phi);
   fChain->SetBranchAddress("jpsi_rf_y", &jpsi_rf_y, &b_jpsi_rf_y);
   fChain->SetBranchAddress("jpsi_m", &jpsi_m, &b_jpsi_m);
   fChain->SetBranchAddress("jpsi_pt", &jpsi_pt, &b_jpsi_pt);
   fChain->SetBranchAddress("jpsi_eta", &jpsi_eta, &b_jpsi_eta);
   fChain->SetBranchAddress("jpsi_phi", &jpsi_phi, &b_jpsi_phi);
   fChain->SetBranchAddress("jpsi_y", &jpsi_y, &b_jpsi_y);
   fChain->SetBranchAddress("x_rf_m", &x_rf_m, &b_x_rf_m);
   fChain->SetBranchAddress("x_rf_pt", &x_rf_pt, &b_x_rf_pt);
   fChain->SetBranchAddress("x_rf_eta", &x_rf_eta, &b_x_rf_eta);
   fChain->SetBranchAddress("x_rf_phi", &x_rf_phi, &b_x_rf_phi);
   fChain->SetBranchAddress("x_rf_y", &x_rf_y, &b_x_rf_y);
   fChain->SetBranchAddress("x_m", &x_m, &b_x_m);
   fChain->SetBranchAddress("x_pt", &x_pt, &b_x_pt);
   fChain->SetBranchAddress("x_eta", &x_eta, &b_x_eta);
   fChain->SetBranchAddress("x_phi", &x_phi, &b_x_phi);
   fChain->SetBranchAddress("x_y", &x_y, &b_x_y);
   fChain->SetBranchAddress("ld_type", &ld_type, &b_ld_type);
   fChain->SetBranchAddress("ld_fitChi2NDF", &ld_fitChi2NDF, &b_ld_fitChi2NDF);
   fChain->SetBranchAddress("ld_Lxy", &ld_Lxy, &b_ld_Lxy);
   fChain->SetBranchAddress("ld_gfitChi2NDF", &ld_gfitChi2NDF, &b_ld_gfitChi2NDF);
   fChain->SetBranchAddress("ld_gmass", &ld_gmass, &b_ld_gmass);
   fChain->SetBranchAddress("ld_rf_m", &ld_rf_m, &b_ld_rf_m);
   fChain->SetBranchAddress("ld_rf_pt", &ld_rf_pt, &b_ld_rf_pt);
   fChain->SetBranchAddress("ld_rf_eta", &ld_rf_eta, &b_ld_rf_eta);
   fChain->SetBranchAddress("ld_rf_phi", &ld_rf_phi, &b_ld_rf_phi);
   fChain->SetBranchAddress("ld_rf_y", &ld_rf_y, &b_ld_rf_y);
   fChain->SetBranchAddress("ld_m", &ld_m, &b_ld_m);
   fChain->SetBranchAddress("ld_pt", &ld_pt, &b_ld_pt);
   fChain->SetBranchAddress("ld_eta", &ld_eta, &b_ld_eta);
   fChain->SetBranchAddress("ld_phi", &ld_phi, &b_ld_phi);
   fChain->SetBranchAddress("ld_y", &ld_y, &b_ld_y);
   fChain->SetBranchAddress("jpsiLd_m", &jpsiLd_m, &b_jpsiLd_m);
   fChain->SetBranchAddress("jpsiLd_pt", &jpsiLd_pt, &b_jpsiLd_pt);
   fChain->SetBranchAddress("jpsiLd_eta", &jpsiLd_eta, &b_jpsiLd_eta);
   fChain->SetBranchAddress("jpsiLd_phi", &jpsiLd_phi, &b_jpsiLd_phi);
   fChain->SetBranchAddress("jpsiLd_y", &jpsiLd_y, &b_jpsiLd_y);
   fChain->SetBranchAddress("xLd_m", &xLd_m, &b_xLd_m);
   fChain->SetBranchAddress("xLd_pt", &xLd_pt, &b_xLd_pt);
   fChain->SetBranchAddress("xLd_eta", &xLd_eta, &b_xLd_eta);
   fChain->SetBranchAddress("xLd_phi", &xLd_phi, &b_xLd_phi);
   fChain->SetBranchAddress("xLd_y", &xLd_y, &b_xLd_y);
   fChain->SetBranchAddress("d_Lxy", &d_Lxy, &b_d_Lxy);
   fChain->SetBranchAddress("d_Lxy_err", &d_Lxy_err, &b_d_Lxy_err);
   fChain->SetBranchAddress("d_a0xy", &d_a0xy, &b_d_a0xy);
   fChain->SetBranchAddress("d_a0xy_err", &d_a0xy_err, &b_d_a0xy_err);
   fChain->SetBranchAddress("d_a0z", &d_a0z, &b_d_a0z);
   fChain->SetBranchAddress("d_a0z_err", &d_a0z_err, &b_d_a0z_err);
   fChain->SetBranchAddress("Dpm_rf_m", &Dpm_rf_m, &b_Dpm_rf_m);
   fChain->SetBranchAddress("Dpm_rf_pt", &Dpm_rf_pt, &b_Dpm_rf_pt);
   fChain->SetBranchAddress("Dpm_rf_eta", &Dpm_rf_eta, &b_Dpm_rf_eta);
   fChain->SetBranchAddress("Dpm_rf_phi", &Dpm_rf_phi, &b_Dpm_rf_phi);
   fChain->SetBranchAddress("Dpm_rf_y", &Dpm_rf_y, &b_Dpm_rf_y);
   fChain->SetBranchAddress("D0_rf_m", &D0_rf_m, &b_D0_rf_m);
   fChain->SetBranchAddress("D0_rf_pt", &D0_rf_pt, &b_D0_rf_pt);
   fChain->SetBranchAddress("D0_rf_eta", &D0_rf_eta, &b_D0_rf_eta);
   fChain->SetBranchAddress("D0_rf_phi", &D0_rf_phi, &b_D0_rf_phi);
   fChain->SetBranchAddress("D0_rf_y", &D0_rf_y, &b_D0_rf_y);
   fChain->SetBranchAddress("Dst_rf_m", &Dst_rf_m, &b_Dst_rf_m);
   fChain->SetBranchAddress("Dst_rf_pt", &Dst_rf_pt, &b_Dst_rf_pt);
   fChain->SetBranchAddress("Dst_rf_eta", &Dst_rf_eta, &b_Dst_rf_eta);
   fChain->SetBranchAddress("Dst_rf_phi", &Dst_rf_phi, &b_Dst_rf_phi);
   fChain->SetBranchAddress("Dst_rf_y", &Dst_rf_y, &b_Dst_rf_y);
   fChain->SetBranchAddress("Dpm_m", &Dpm_m, &b_Dpm_m);
   fChain->SetBranchAddress("Dpm_pt", &Dpm_pt, &b_Dpm_pt);
   fChain->SetBranchAddress("Dpm_eta", &Dpm_eta, &b_Dpm_eta);
   fChain->SetBranchAddress("Dpm_phi", &Dpm_phi, &b_Dpm_phi);
   fChain->SetBranchAddress("Dpm_y", &Dpm_y, &b_Dpm_y);
   fChain->SetBranchAddress("D0_m", &D0_m, &b_D0_m);
   fChain->SetBranchAddress("D0_pt", &D0_pt, &b_D0_pt);
   fChain->SetBranchAddress("D0_eta", &D0_eta, &b_D0_eta);
   fChain->SetBranchAddress("D0_phi", &D0_phi, &b_D0_phi);
   fChain->SetBranchAddress("D0_y", &D0_y, &b_D0_y);
   fChain->SetBranchAddress("Dst_m", &Dst_m, &b_Dst_m);
   fChain->SetBranchAddress("Dst_pt", &Dst_pt, &b_Dst_pt);
   fChain->SetBranchAddress("Dst_eta", &Dst_eta, &b_Dst_eta);
   fChain->SetBranchAddress("Dst_phi", &Dst_phi, &b_Dst_phi);
   fChain->SetBranchAddress("Dst_y", &Dst_y, &b_Dst_y);
   fChain->SetBranchAddress("Dst_m_calc", &Dst_m_calc, &b_Dst_m_calc);
   fChain->SetBranchAddress("mu_rf_m", mu_rf_m, &b_mu_rf_m);
   fChain->SetBranchAddress("mu_rf_pt", mu_rf_pt, &b_mu_rf_pt);
   fChain->SetBranchAddress("mu_rf_eta", mu_rf_eta, &b_mu_rf_eta);
   fChain->SetBranchAddress("mu_rf_phi", mu_rf_phi, &b_mu_rf_phi);
   fChain->SetBranchAddress("mu_E", mu_E, &b_mu_E);
   fChain->SetBranchAddress("mu_pt", mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_charge", mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_d0", mu_d0, &b_mu_d0);
   fChain->SetBranchAddress("mu_z0", mu_z0, &b_mu_z0);
   fChain->SetBranchAddress("mu_isMuon", mu_isMuon, &b_mu_isMuon);
   fChain->SetBranchAddress("mu_isMedium", mu_isMedium, &b_mu_isMedium);
   fChain->SetBranchAddress("mu_isLoose", mu_isLoose, &b_mu_isLoose);
   fChain->SetBranchAddress("mu_isVeryLoose", mu_isVeryLoose, &b_mu_isVeryLoose);
   fChain->SetBranchAddress("mu_isLowPt", mu_isLowPt, &b_mu_isLowPt);
   fChain->SetBranchAddress("mu_isCombinedMuon", mu_isCombinedMuon, &b_mu_isCombinedMuon);
   fChain->SetBranchAddress("mu_isInMuonsCont", mu_isInMuonsCont, &b_mu_isInMuonsCont);
   fChain->SetBranchAddress("mu_passID", mu_passID, &b_mu_passID);
   fChain->SetBranchAddress("mu_medium_eff_sf", mu_medium_eff_sf, &b_mu_medium_eff_sf);
   fChain->SetBranchAddress("mu_medium_eff_sf_up", mu_medium_eff_sf_up, &b_mu_medium_eff_sf_up);
   fChain->SetBranchAddress("mu_medium_eff_sf_down", mu_medium_eff_sf_down, &b_mu_medium_eff_sf_down);
   fChain->SetBranchAddress("mu_lowpt_eff_sf", mu_lowpt_eff_sf, &b_mu_lowpt_eff_sf);
   fChain->SetBranchAddress("mu_lowpt_eff_sf_up", mu_lowpt_eff_sf_up, &b_mu_lowpt_eff_sf_up);
   fChain->SetBranchAddress("mu_lowpt_eff_sf_down", mu_lowpt_eff_sf_down, &b_mu_lowpt_eff_sf_down);
   fChain->SetBranchAddress("mu_loose_eff_sf", mu_loose_eff_sf, &b_mu_loose_eff_sf);
   fChain->SetBranchAddress("mu_loose_eff_sf_up", mu_loose_eff_sf_up, &b_mu_loose_eff_sf_up);
   fChain->SetBranchAddress("mu_loose_eff_sf_down", mu_loose_eff_sf_down, &b_mu_loose_eff_sf_down);
   fChain->SetBranchAddress("mu_scale_up", mu_scale_up, &b_mu_scale_up);
   fChain->SetBranchAddress("mu_scale_down", mu_scale_down, &b_mu_scale_down);
   fChain->SetBranchAddress("mu_scale_nominal", mu_scale_nominal, &b_mu_scale_nominal);
   fChain->SetBranchAddress("trk_rf_m", trk_rf_m, &b_trk_rf_m);
   fChain->SetBranchAddress("trk_rf_pt", trk_rf_pt, &b_trk_rf_pt);
   fChain->SetBranchAddress("trk_rf_eta", trk_rf_eta, &b_trk_rf_eta);
   fChain->SetBranchAddress("trk_rf_phi", trk_rf_phi, &b_trk_rf_phi);
   fChain->SetBranchAddress("trk_m", trk_m, &b_trk_m);
   fChain->SetBranchAddress("trk_pt", trk_pt, &b_trk_pt);
   fChain->SetBranchAddress("trk_eta", trk_eta, &b_trk_eta);
   fChain->SetBranchAddress("trk_phi", trk_phi, &b_trk_phi);
   fChain->SetBranchAddress("trk_charge", trk_charge, &b_trk_charge);
   fChain->SetBranchAddress("trk_d0", trk_d0, &b_trk_d0);
   fChain->SetBranchAddress("trk_z0", trk_z0, &b_trk_z0);
   fChain->SetBranchAddress("pt_mu1", &pt_mu1, &b_pt_mu1);
   fChain->SetBranchAddress("pt_mu2", &pt_mu2, &b_pt_mu2);
   fChain->SetBranchAddress("pt_trk1", &pt_trk1, &b_pt_trk1);
   fChain->SetBranchAddress("pt_trk2", &pt_trk2, &b_pt_trk2);
   fChain->SetBranchAddress("pt_LRT_trk1", &pt_LRT_trk1, &b_pt_LRT_trk1);
   fChain->SetBranchAddress("pt_LRT_trk2", &pt_LRT_trk2, &b_pt_LRT_trk2);
   fChain->SetBranchAddress("pt_K", &pt_K, &b_pt_K);
   fChain->SetBranchAddress("eta_K", &eta_K, &b_eta_K);
   fChain->SetBranchAddress("phi_K", &phi_K, &b_phi_K);
   fChain->SetBranchAddress("pt_pi", &pt_pi, &b_pt_pi);
   fChain->SetBranchAddress("eta_pi", &eta_pi, &b_eta_pi);
   fChain->SetBranchAddress("phi_pi", &phi_pi, &b_phi_pi);
   fChain->SetBranchAddress("pt_p_Ld", &pt_p_Ld, &b_pt_p_Ld);
   fChain->SetBranchAddress("pt_pi_Ld", &pt_pi_Ld, &b_pt_pi_Ld);
   fChain->SetBranchAddress("pt_pi1_D", &pt_pi1_D, &b_pt_pi1_D);
   fChain->SetBranchAddress("pt_pi2_D", &pt_pi2_D, &b_pt_pi2_D);
   fChain->SetBranchAddress("truth_n", &truth_n, &b_truth_n);
   fChain->SetBranchAddress("truth_pdgId", &truth_pdgId, &b_truth_pdgId);
   fChain->SetBranchAddress("truth_motherID", &truth_motherID, &b_truth_motherID);
   fChain->SetBranchAddress("truth_mass", &truth_mass, &b_truth_mass);
   fChain->SetBranchAddress("truth_pT", &truth_pT, &b_truth_pT);
   fChain->SetBranchAddress("truth_eta", &truth_eta, &b_truth_eta);
   fChain->SetBranchAddress("truth_phi", &truth_phi, &b_truth_phi);
   Notify();
}

bool bphy25::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void bphy25::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t bphy25::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef bphy25_cxx
