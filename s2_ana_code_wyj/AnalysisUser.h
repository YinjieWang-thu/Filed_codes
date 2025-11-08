#ifndef AnalysisUser_H
#define AnalysisUser_H

#include "TTree.h"
#include "TRandom3.h"
#include <vector>
#include "header.h"

enum class Dataset : UInt_t { kData15, kData16p1, kData16p2, kData16p3, kData17p1, kData17p2, kData18, kMC16a, kMC16d, kMC16e };
enum class Dataset2 : UInt_t { kData15p1, kData15p2, kData16p1, kData16p2, kData16p3, kData16p4, kData16p5, kData17, kData18, kMC16a, kMC16d, kMC16e };
enum class Dataset3 : UInt_t { kData15p1, kData15p2, kData16p1, kData16p2, kData16p3, kData16p4, kData16p5, kData17p1, kData17p2, kData18, kMC16a, kMC16d, kMC16e };

class AnalysisUser : public header {

private:

  TTree* m_tree; //!
  void DefineBranches(TTree* tr);
  TRandom3* rdm;

public:

  int num_eve[18]; //!

  AnalysisUser(std::string inputfiles);
  virtual ~AnalysisUser();

  void initialize(const char* out, int _process, int _cat, int _type);
  float getTriggerWeight( Dataset dataset, UInt_t trigger );
  float getTriggerWeight2( Dataset2 dataset, UInt_t trigger );
  float getTriggerWeight3( Dataset3 dataset, UInt_t trigger );
  void execute();
  void finalize();
  float DR(float eta1, float phi1, float eta2, float phi2);

  int process;
  int cat;
  int type;
  int channel;
  bool pass_trigger;
  float trig_wt;
  bool global_match;
  bool  isReversed;
  float pt_mu1;
  float pt_mu2;

  float mu_rf_m[2]; 
  float mu_rf_pt[2]; 
  float mu_rf_eta[2];
  float mu_rf_phi[2]; 
  float mu_prime_rf_m[2]; 
  float mu_prime_rf_pt[2]; 
  float mu_prime_rf_eta[2]; 
  float mu_prime_rf_phi[2]; 
  float mu_E[2];
  float mu_pt[2];
  float mu_eta[2];
  float mu_phi[2];
  float mu_charge[2];
  float mu_d0[2];
  float mu_z0[2];
  float mu_prime_E[2];
  float mu_prime_pt[2];
  float mu_prime_eta[2];
  float mu_prime_phi[2];
  float mu_prime_charge[2];
  float mu_prime_d0[2];
  float mu_prime_z0[2];
  bool  mu_isMuon[2];
  bool  mu_isMedium[2];
  bool  mu_isLoose[2];
  bool  mu_isVeryLoose[2];
  bool  mu_isLowPt[2];
  bool  mu_isLowPtMVA[2];
  bool  mu_isCombinedMuon[2];
  bool  mu_isInMuonsCont[2];
  bool  mu_passID[2];
  float mu_medium_eff_sf[2];
  float mu_medium_eff_sf_up[2][2];
  float mu_medium_eff_sf_down[2][2];
  float mu_lowptMVA_eff_sf[2];
  float mu_lowptMVA_eff_sf_up[2][2];
  float mu_lowptMVA_eff_sf_down[2][2];
  float mu_loose_eff_sf[2];
  float mu_loose_eff_sf_up[2][2];
  float mu_loose_eff_sf_down[2][2];
  float mu_scale_up[2][2];
  float mu_scale_down[2][2];
  float mu_scale_nominal[2];

// k pi or pi k , [0] for kaon and [1] for pion
  float trk_rf_m[2];
  float trk_rf_pt[2];
  float trk_rf_eta[2];
  float trk_rf_phi[2];
  float trk_m[2];
  float trk_pt[2];
  float trk_eta[2];
  float trk_phi[2];
  float trk_charge[2];
  float trk_d0[2];
  float trk_z0[2];

// k pi pi for D+ and k pi for D0
  float Dtrk_rf_m[3];
  float Dtrk_rf_pt[3];
  float Dtrk_rf_eta[3];
  float Dtrk_rf_phi[3];
  float Dtrk_m[3];
  float Dtrk_pt[3];
  float Dtrk_eta[3];
  float Dtrk_phi[3];
  float Dtrk_charge[3];
  float Dtrk_d0[3];
  float Dtrk_z0[3];

// p or pi from Lambda [0] for proton and [1] for pion
  float Ldtrk_rf_m[2];
  float Ldtrk_rf_pt[2];
  float Ldtrk_rf_eta[2];
  float Ldtrk_rf_phi[2];
  float Ldtrk_m[2];
  float Ldtrk_pt[2];
  float Ldtrk_eta[2];
  float Ldtrk_phi[2];
  float Ldtrk_charge[2];
  float Ldtrk_d0[2];
  float Ldtrk_z0[2];


//Jpsi variables for channel 1 and channel 2
  float jpsi_rf_m;
  float jpsi_rf_pt;
  float jpsi_rf_eta;
  float jpsi_rf_phi;
  float jpsi_rf_y;
  float jpsi_m;
  float jpsi_pt;
  float jpsi_eta;
  float jpsi_phi;
  float jpsi_y;

  float d_rf_m;
  float d_rf_pt;
  float d_rf_eta;
  float d_rf_phi;
  float d_rf_y;
  float d_m;
  float d_pt;
  float d_eta;
  float d_phi;
  float d_y;
  float d_Lxy;

  float jx_rf_m;
  float jx_rf_pt;
  float jx_rf_eta;
  float jx_rf_phi;
  float jx_rf_y;
  float jx_m;
  float jx_pt;
  float jx_eta;
  float jx_phi;
  float jx_y;
  float jx_fitChi2;
  float jx_fitChi2NDF;
  float jx_Lxy;
  float jx_Lxy_err;

  float Kst_m;
  float Kst_pt;
  float Kst_eta;
  float Kst_phi;
  float Kst_y;
  float etac_m;
  float etac_pt;
  float etac_eta;
  float etac_phi;
  float etac_y;

  float JpsiLd_m;
  float JpsiLd_pt;
  float JpsiLd_eta;
  float JpsiLd_phi;
  float JpsiLd_y;
  float JpsiTrk_m;
  float JpsiTrk_pt;
  float JpsiTrk_eta;
  float JpsiTrk_phi;
  float JpsiTrk_y;
  float LdTrk_m;
  float LdTrk_pt;
  float LdTrk_eta;
  float LdTrk_phi;
  float LdTrk_y;

  float ld_rf_m;
  float ld_rf_pt;
  float ld_rf_eta;
  float ld_rf_phi;
  float ld_rf_y;
  float ld_fitChi2;
  int   ld_fitNDF;   
  float ld_fitChi2NDF;

  float ld_m;
  float ld_pt;
  float ld_eta;
  float ld_phi;
  float ld_y;

  float ld_pt_err;
  float ld_Lxy;
  float ld_Lxy_err;
  float ld_Lxy_sig;
  float ld_a0xy;
  float ld_a0xy_err;
  float ld_a0z;
  float ld_a0z_err;


  // calculated from jpsi_rf_XXX and refitted track
  float tq_rf_m;
  float tq_rf_pt;
  float tq_rf_eta;
  float tq_rf_phi;

  // calculated from Muon1 Muon2 (Muon3 Muon4) and trk1 to trk6
  float tq_m;
  float tq_fitChi2NDF;
  float tq_iso;
  float tq_eta;
  float tq_phi;
  float tq_pt;
  float tq_y;
  float tq_pt_err;
  float tq_pt_sig;
  float tq_Lxy;
  float tq_Lxy_err;
  float tq_Lxy_sig;
  int   tq_PV_idx;
  float tq_a0xy;
  float tq_a0xy_err;
  float tq_z0;
  float tq_z0_err;
  float tq_ratio;


  Int_t match[SIZE]; //[TQ_n]
};

#endif
