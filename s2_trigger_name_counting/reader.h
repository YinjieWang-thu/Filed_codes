   // Declaration of leaf types
   Int_t           cat;
   UInt_t          run_number;
   ULong64_t       event_number;
   Int_t           lumi_block;
   vector<string>  *HLT_name;
   Float_t         evt_wt;
   Float_t         trig_wt;
   Float_t         pu_wt;
   Float_t         pu_wt_sys_up;
   Float_t         pu_wt_sys_dn;
   Float_t         corr_scaled_mu;
   Bool_t          pass_trigger;
   Int_t           tq_channel;
   Int_t           tq_PV_idx;
   Float_t         tq_rf_m;
   Float_t         tq_rf_fitChi2NDF;
   Float_t         tq_rf_eta;
   Float_t         tq_rf_phi;
   Float_t         tq_rf_pt;
   Float_t         tq_rf_pt_err;
   Float_t         tq_rf_pt_sig;
   Float_t         tq_rf_Lxy;
   Float_t         tq_rf_Lxy_err;
   Float_t         tq_rf_Lxy_sig;
   Float_t         tq_rf_a0xy;
   Float_t         tq_rf_a0xy_err;
   Float_t         tq_rf_z0;
   Float_t         tq_rf_z0_err;
   Float_t         tq_rf_ratio;
   Float_t         tq_m_calc;
   Float_t         jx_fitChi2NDF;
   Float_t         jx_Lxy;
   Float_t         jx_Lxy_err;
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
   Float_t         jx_rev_fitChi2NDF;
   Float_t         jx_rev_Lxy;
   Float_t         jx_rev_Lxy_err;
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
   Float_t         ld_gfitChi2NDF;
   Float_t         ld_gmass;
   Float_t         ld_fitChi2NDF;
   Float_t         ld_Lxy;
   Float_t         ld_Lxy_err;
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
   Float_t         jpsiLd_rf_m;
   Float_t         jpsiLd_rf_pt;
   Float_t         jpsiLd_rf_eta;
   Float_t         jpsiLd_rf_phi;
   Float_t         jpsiLd_rf_y;
   Float_t         jpsiLd_m_calc;
   Float_t         xLd_rf_m;
   Float_t         xLd_rf_pt;
   Float_t         xLd_rf_eta;
   Float_t         xLd_rf_phi;
   Float_t         xLd_rf_y;
   Float_t         mu_rf_m[2];
   Float_t         mu_rf_pt[2];
   Float_t         mu_rf_eta[2];
   Float_t         mu_rf_phi[2];
   Float_t         mu_E[2];
   Float_t         mu_pt_raw[2];
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
   Float_t         trk_rf_m[4];
   Float_t         trk_rf_pt[4];
   Float_t         trk_rf_eta[4];
   Float_t         trk_rf_phi[4];
   Float_t         trk_m[4];
   Float_t         trk_pt[4];
   Float_t         trk_eta[4];
   Float_t         trk_phi[4];
   Int_t           trk_charge[4];
   Float_t         trk_d0[4];
   Float_t         trk_z0[4];
   Float_t         trk_pixeldEdx[4];
   Int_t           trk_nUsedHitsdEdx[4];
   Int_t           trk_nIBLOFsdEdx[4];
   Float_t         pt_mu1;
   Float_t         pt_mu2;
   Float_t         pt_trk1_X;
   Float_t         pt_trk2_X;
   Float_t         pt_K_X;
   Float_t         pt_pi_X;
   Float_t         pt_LRT_trk1;
   Float_t         pt_LRT_trk2;
   Float_t         pt_LRT_p;
   Float_t         pt_LRT_pi;
   Float_t         truth_Bs1_m;
   Float_t         truth_Bs2_m;
   Float_t         truth_mu_m[2];
   Float_t         truth_mu_pt[2];
   Float_t         truth_mu_eta[2];
   Float_t         truth_mu_phi[2];
   Int_t           truth_mu_charge[2];
   Float_t         truth_K_m;
   Float_t         truth_K_pt;
   Float_t         truth_K_eta;
   Float_t         truth_K_phi;
   Int_t           truth_K_charge;
   Float_t         truth_pi1_m;
   Float_t         truth_pi1_pt;
   Float_t         truth_pi1_eta;
   Float_t         truth_pi1_phi;
   Int_t           truth_pi1_charge;
   Float_t         truth_pi_m[2];
   Float_t         truth_pi_pt[2];
   Float_t         truth_pi_eta[2];
   Float_t         truth_pi_phi[2];
   Int_t           truth_pi_charge[2];
   Float_t         truth_p_m;
   Float_t         truth_p_pt;
   Float_t         truth_p_eta;
   Float_t         truth_p_phi;
   Int_t           truth_p_charge;
   Float_t         truth_pi2_m;
   Float_t         truth_pi2_pt;
   Float_t         truth_pi2_eta;
   Float_t         truth_pi2_phi;
   Int_t           truth_pi2_charge;
   Bool_t          match_jpsi;
   Bool_t          match_X;
   Bool_t          match_Ld;
   Bool_t          match_all;

   // List of branches
   TBranch        *b_cat;   //!
   TBranch        *b_run_number;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_lumi_block;
   TBranch        *b_HLT_name;   //!
   TBranch        *b_evt_wt;   //!
   TBranch        *b_trig_wt;   //!
   TBranch        *b_pu_wt;   //!
   TBranch        *b_pu_wt_sys_up;   //!
   TBranch        *b_pu_wt_sys_dn;   //!
   TBranch        *b_corr_scaled_mu;   //!
   TBranch        *b_pass_trigger;   //!
   TBranch        *b_tq_channel;   //!
   TBranch        *b_tq_PV_idx;   //!
   TBranch        *b_tq_rf_m;   //!
   TBranch        *b_tq_rf_fitChi2NDF;   //!
   TBranch        *b_tq_rf_eta;   //!
   TBranch        *b_tq_rf_phi;   //!
   TBranch        *b_tq_rf_pt;   //!
   TBranch        *b_tq_rf_pt_err;   //!
   TBranch        *b_tq_rf_pt_sig;   //!
   TBranch        *b_tq_rf_Lxy;   //!
   TBranch        *b_tq_rf_Lxy_err;   //!
   TBranch        *b_tq_rf_Lxy_sig;   //!
   TBranch        *b_tq_rf_a0xy;   //!
   TBranch        *b_tq_rf_a0xy_err;   //!
   TBranch        *b_tq_rf_z0;   //!
   TBranch        *b_tq_rf_z0_err;   //!
   TBranch        *b_tq_rf_ratio;   //!
   TBranch        *b_tq_m_calc;   //!
   TBranch        *b_jx_fitChi2NDF;   //!
   TBranch        *b_jx_Lxy;   //!
   TBranch        *b_jx_Lxy_err;   //!
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
   TBranch        *b_jx_rev_fitChi2NDF;   //!
   TBranch        *b_jx_rev_Lxy;   //!
   TBranch        *b_jx_rev_Lxy_err;   //!
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
   TBranch        *b_ld_gfitChi2NDF;   //!
   TBranch        *b_ld_gmass;   //!
   TBranch        *b_ld_fitChi2NDF;   //!
   TBranch        *b_ld_Lxy;   //!
   TBranch        *b_ld_Lxy_err;   //!
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
   TBranch        *b_jpsiLd_rf_m;   //!
   TBranch        *b_jpsiLd_rf_pt;   //!
   TBranch        *b_jpsiLd_rf_eta;   //!
   TBranch        *b_jpsiLd_rf_phi;   //!
   TBranch        *b_jpsiLd_rf_y;   //!
   TBranch        *b_jpsiLd_m_calc;   //!
   TBranch        *b_xLd_rf_m;   //!
   TBranch        *b_xLd_rf_pt;   //!
   TBranch        *b_xLd_rf_eta;   //!
   TBranch        *b_xLd_rf_phi;   //!
   TBranch        *b_xLd_rf_y;   //!
   TBranch        *b_mu_rf_m;   //!
   TBranch        *b_mu_rf_pt;   //!
   TBranch        *b_mu_rf_eta;   //!
   TBranch        *b_mu_rf_phi;   //!
   TBranch        *b_mu_E;   //!
   TBranch        *b_mu_pt_raw;   //!
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
   TBranch        *b_trk_pixeldEdx;   //!
   TBranch        *b_trk_nUsedHitsdEdx;   //!
   TBranch        *b_trk_nIBLOFsdEdx;   //!
   TBranch        *b_pt_mu1;   //!
   TBranch        *b_pt_mu2;   //!
   TBranch        *b_pt_trk1_X;   //!
   TBranch        *b_pt_trk2_X;   //!
   TBranch        *b_pt_K_X;   //!
   TBranch        *b_pt_pi_X;   //!
   TBranch        *b_pt_LRT_trk1;   //!
   TBranch        *b_pt_LRT_trk2;   //!
   TBranch        *b_pt_LRT_p;   //!
   TBranch        *b_pt_LRT_pi;   //!
   TBranch        *b_truth_Bs1_m;   //!
   TBranch        *b_truth_Bs2_m;   //!
   TBranch        *b_truth_mu_m;   //!
   TBranch        *b_truth_mu_pt;   //!
   TBranch        *b_truth_mu_eta;   //!
   TBranch        *b_truth_mu_phi;   //!
   TBranch        *b_truth_mu_charge;   //!
   TBranch        *b_truth_K_m;   //!
   TBranch        *b_truth_K_pt;   //!
   TBranch        *b_truth_K_eta;   //!
   TBranch        *b_truth_K_phi;   //!
   TBranch        *b_truth_K_charge;   //!
   TBranch        *b_truth_pi1_m;   //!
   TBranch        *b_truth_pi1_pt;   //!
   TBranch        *b_truth_pi1_eta;   //!
   TBranch        *b_truth_pi1_phi;   //!
   TBranch        *b_truth_pi1_charge;   //!
   TBranch        *b_truth_pi_m;   //!
   TBranch        *b_truth_pi_pt;   //!
   TBranch        *b_truth_pi_eta;   //!
   TBranch        *b_truth_pi_phi;   //!
   TBranch        *b_truth_pi_charge;   //!
   TBranch        *b_truth_p_m;   //!
   TBranch        *b_truth_p_pt;   //!
   TBranch        *b_truth_p_eta;   //!
   TBranch        *b_truth_p_phi;   //!
   TBranch        *b_truth_p_charge;   //!
   TBranch        *b_truth_pi2_m;   //!
   TBranch        *b_truth_pi2_pt;   //!
   TBranch        *b_truth_pi2_eta;   //!
   TBranch        *b_truth_pi2_phi;   //!
   TBranch        *b_truth_pi2_charge;   //!
   TBranch        *b_match_jpsi;   //!
   TBranch        *b_match_X;   //!
   TBranch        *b_match_Ld;   //!
   TBranch        *b_match_all;   //!

void Init(TTree *tree)
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
   TTree* fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("cat", &cat, &b_cat);
   fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
   fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
   fChain->SetBranchAddress("lumi_block", &lumi_block, &b_lumi_block);
   fChain->SetBranchAddress("HLT_name", &HLT_name, &b_HLT_name);
   fChain->SetBranchAddress("evt_wt", &evt_wt, &b_evt_wt);
   fChain->SetBranchAddress("trig_wt", &trig_wt, &b_trig_wt);
   fChain->SetBranchAddress("pu_wt", &pu_wt, &b_pu_wt);
   fChain->SetBranchAddress("pu_wt_sys_up", &pu_wt_sys_up, &b_pu_wt_sys_up);
   fChain->SetBranchAddress("pu_wt_sys_dn", &pu_wt_sys_dn, &b_pu_wt_sys_dn);
   fChain->SetBranchAddress("corr_scaled_mu", &corr_scaled_mu, &b_corr_scaled_mu);
   fChain->SetBranchAddress("pass_trigger", &pass_trigger, &b_pass_trigger);
   fChain->SetBranchAddress("tq_channel", &tq_channel, &b_tq_channel);
   fChain->SetBranchAddress("tq_PV_idx", &tq_PV_idx, &b_tq_PV_idx);
   fChain->SetBranchAddress("tq_rf_m", &tq_rf_m, &b_tq_rf_m);
   fChain->SetBranchAddress("tq_rf_fitChi2NDF", &tq_rf_fitChi2NDF, &b_tq_rf_fitChi2NDF);
   fChain->SetBranchAddress("tq_rf_eta", &tq_rf_eta, &b_tq_rf_eta);
   fChain->SetBranchAddress("tq_rf_phi", &tq_rf_phi, &b_tq_rf_phi);
   fChain->SetBranchAddress("tq_rf_pt", &tq_rf_pt, &b_tq_rf_pt);
   fChain->SetBranchAddress("tq_rf_pt_err", &tq_rf_pt_err, &b_tq_rf_pt_err);
   fChain->SetBranchAddress("tq_rf_pt_sig", &tq_rf_pt_sig, &b_tq_rf_pt_sig);
   fChain->SetBranchAddress("tq_rf_Lxy", &tq_rf_Lxy, &b_tq_rf_Lxy);
   fChain->SetBranchAddress("tq_rf_Lxy_err", &tq_rf_Lxy_err, &b_tq_rf_Lxy_err);
   fChain->SetBranchAddress("tq_rf_Lxy_sig", &tq_rf_Lxy_sig, &b_tq_rf_Lxy_sig);
   fChain->SetBranchAddress("tq_rf_a0xy", &tq_rf_a0xy, &b_tq_rf_a0xy);
   fChain->SetBranchAddress("tq_rf_a0xy_err", &tq_rf_a0xy_err, &b_tq_rf_a0xy_err);
   fChain->SetBranchAddress("tq_rf_z0", &tq_rf_z0, &b_tq_rf_z0);
   fChain->SetBranchAddress("tq_rf_z0_err", &tq_rf_z0_err, &b_tq_rf_z0_err);
   fChain->SetBranchAddress("tq_rf_ratio", &tq_rf_ratio, &b_tq_rf_ratio);
   fChain->SetBranchAddress("tq_m_calc", &tq_m_calc, &b_tq_m_calc);
   fChain->SetBranchAddress("jx_fitChi2NDF", &jx_fitChi2NDF, &b_jx_fitChi2NDF);
   fChain->SetBranchAddress("jx_Lxy", &jx_Lxy, &b_jx_Lxy);
   fChain->SetBranchAddress("jx_Lxy_err", &jx_Lxy_err, &b_jx_Lxy_err);
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
   fChain->SetBranchAddress("jx_rev_fitChi2NDF", &jx_rev_fitChi2NDF, &b_jx_rev_fitChi2NDF);
   fChain->SetBranchAddress("jx_rev_Lxy", &jx_rev_Lxy, &b_jx_rev_Lxy);
   fChain->SetBranchAddress("jx_rev_Lxy_err", &jx_rev_Lxy_err, &b_jx_rev_Lxy_err);
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
   fChain->SetBranchAddress("ld_gfitChi2NDF", &ld_gfitChi2NDF, &b_ld_gfitChi2NDF);
   fChain->SetBranchAddress("ld_gmass", &ld_gmass, &b_ld_gmass);
   fChain->SetBranchAddress("ld_fitChi2NDF", &ld_fitChi2NDF, &b_ld_fitChi2NDF);
   fChain->SetBranchAddress("ld_Lxy", &ld_Lxy, &b_ld_Lxy);
   fChain->SetBranchAddress("ld_Lxy_err", &ld_Lxy_err, &b_ld_Lxy_err);
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
   fChain->SetBranchAddress("jpsiLd_rf_m", &jpsiLd_rf_m, &b_jpsiLd_rf_m);
   fChain->SetBranchAddress("jpsiLd_rf_pt", &jpsiLd_rf_pt, &b_jpsiLd_rf_pt);
   fChain->SetBranchAddress("jpsiLd_rf_eta", &jpsiLd_rf_eta, &b_jpsiLd_rf_eta);
   fChain->SetBranchAddress("jpsiLd_rf_phi", &jpsiLd_rf_phi, &b_jpsiLd_rf_phi);
   fChain->SetBranchAddress("jpsiLd_rf_y", &jpsiLd_rf_y, &b_jpsiLd_rf_y);
   fChain->SetBranchAddress("jpsiLd_m_calc", &jpsiLd_m_calc, &b_jpsiLd_m_calc);
   fChain->SetBranchAddress("xLd_rf_m", &xLd_rf_m, &b_xLd_rf_m);
   fChain->SetBranchAddress("xLd_rf_pt", &xLd_rf_pt, &b_xLd_rf_pt);
   fChain->SetBranchAddress("xLd_rf_eta", &xLd_rf_eta, &b_xLd_rf_eta);
   fChain->SetBranchAddress("xLd_rf_phi", &xLd_rf_phi, &b_xLd_rf_phi);
   fChain->SetBranchAddress("xLd_rf_y", &xLd_rf_y, &b_xLd_rf_y);
   fChain->SetBranchAddress("mu_rf_m", mu_rf_m, &b_mu_rf_m);
   fChain->SetBranchAddress("mu_rf_pt", mu_rf_pt, &b_mu_rf_pt);
   fChain->SetBranchAddress("mu_rf_eta", mu_rf_eta, &b_mu_rf_eta);
   fChain->SetBranchAddress("mu_rf_phi", mu_rf_phi, &b_mu_rf_phi);
   fChain->SetBranchAddress("mu_E", mu_E, &b_mu_E);
   fChain->SetBranchAddress("mu_pt_raw", mu_pt_raw, &b_mu_pt_raw);
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
   fChain->SetBranchAddress("trk_pixeldEdx", trk_pixeldEdx, &b_trk_pixeldEdx);
   fChain->SetBranchAddress("trk_nUsedHitsdEdx", trk_nUsedHitsdEdx, &b_trk_nUsedHitsdEdx);
   fChain->SetBranchAddress("trk_nIBLOFsdEdx", trk_nIBLOFsdEdx, &b_trk_nIBLOFsdEdx);
   fChain->SetBranchAddress("pt_mu1", &pt_mu1, &b_pt_mu1);
   fChain->SetBranchAddress("pt_mu2", &pt_mu2, &b_pt_mu2);
   fChain->SetBranchAddress("pt_trk1_X", &pt_trk1_X, &b_pt_trk1_X);
   fChain->SetBranchAddress("pt_trk2_X", &pt_trk2_X, &b_pt_trk2_X);
   fChain->SetBranchAddress("pt_K_X", &pt_K_X, &b_pt_K_X);
   fChain->SetBranchAddress("pt_pi_X", &pt_pi_X, &b_pt_pi_X);
   fChain->SetBranchAddress("pt_LRT_trk1", &pt_LRT_trk1, &b_pt_LRT_trk1);
   fChain->SetBranchAddress("pt_LRT_trk2", &pt_LRT_trk2, &b_pt_LRT_trk2);
   fChain->SetBranchAddress("pt_LRT_p", &pt_LRT_p, &b_pt_LRT_p);
   fChain->SetBranchAddress("pt_LRT_pi", &pt_LRT_pi, &b_pt_LRT_pi);
   fChain->SetBranchAddress("truth_Bs1_m", &truth_Bs1_m, &b_truth_Bs1_m);
   fChain->SetBranchAddress("truth_Bs2_m", &truth_Bs2_m, &b_truth_Bs2_m);
   fChain->SetBranchAddress("truth_mu_m", truth_mu_m, &b_truth_mu_m);
   fChain->SetBranchAddress("truth_mu_pt", truth_mu_pt, &b_truth_mu_pt);
   fChain->SetBranchAddress("truth_mu_eta", truth_mu_eta, &b_truth_mu_eta);
   fChain->SetBranchAddress("truth_mu_phi", truth_mu_phi, &b_truth_mu_phi);
   fChain->SetBranchAddress("truth_mu_charge", truth_mu_charge, &b_truth_mu_charge);
   fChain->SetBranchAddress("truth_K_m", &truth_K_m, &b_truth_K_m);
   fChain->SetBranchAddress("truth_K_pt", &truth_K_pt, &b_truth_K_pt);
   fChain->SetBranchAddress("truth_K_eta", &truth_K_eta, &b_truth_K_eta);
   fChain->SetBranchAddress("truth_K_phi", &truth_K_phi, &b_truth_K_phi);
   fChain->SetBranchAddress("truth_K_charge", &truth_K_charge, &b_truth_K_charge);
   fChain->SetBranchAddress("truth_pi1_m", &truth_pi1_m, &b_truth_pi1_m);
   fChain->SetBranchAddress("truth_pi1_pt", &truth_pi1_pt, &b_truth_pi1_pt);
   fChain->SetBranchAddress("truth_pi1_eta", &truth_pi1_eta, &b_truth_pi1_eta);
   fChain->SetBranchAddress("truth_pi1_phi", &truth_pi1_phi, &b_truth_pi1_phi);
   fChain->SetBranchAddress("truth_pi1_charge", &truth_pi1_charge, &b_truth_pi1_charge);
   fChain->SetBranchAddress("truth_pi_m", truth_pi_m, &b_truth_pi_m);
   fChain->SetBranchAddress("truth_pi_pt", truth_pi_pt, &b_truth_pi_pt);
   fChain->SetBranchAddress("truth_pi_eta", truth_pi_eta, &b_truth_pi_eta);
   fChain->SetBranchAddress("truth_pi_phi", truth_pi_phi, &b_truth_pi_phi);
   fChain->SetBranchAddress("truth_pi_charge", truth_pi_charge, &b_truth_pi_charge);
   fChain->SetBranchAddress("truth_p_m", &truth_p_m, &b_truth_p_m);
   fChain->SetBranchAddress("truth_p_pt", &truth_p_pt, &b_truth_p_pt);
   fChain->SetBranchAddress("truth_p_eta", &truth_p_eta, &b_truth_p_eta);
   fChain->SetBranchAddress("truth_p_phi", &truth_p_phi, &b_truth_p_phi);
   fChain->SetBranchAddress("truth_p_charge", &truth_p_charge, &b_truth_p_charge);
   fChain->SetBranchAddress("truth_pi2_m", &truth_pi2_m, &b_truth_pi2_m);
   fChain->SetBranchAddress("truth_pi2_pt", &truth_pi2_pt, &b_truth_pi2_pt);
   fChain->SetBranchAddress("truth_pi2_eta", &truth_pi2_eta, &b_truth_pi2_eta);
   fChain->SetBranchAddress("truth_pi2_phi", &truth_pi2_phi, &b_truth_pi2_phi);
   fChain->SetBranchAddress("truth_pi2_charge", &truth_pi2_charge, &b_truth_pi2_charge);
   fChain->SetBranchAddress("match_jpsi", &match_jpsi, &b_match_jpsi);
   fChain->SetBranchAddress("match_X", &match_X, &b_match_X);
   fChain->SetBranchAddress("match_Ld", &match_Ld, &b_match_Ld);
   fChain->SetBranchAddress("match_all", &match_all, &b_match_all);
}
