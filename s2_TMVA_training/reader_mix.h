//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 15 12:00:59 2025 by ROOT version 6.32.04
// from TTree BPHY25/
// found on file: data15_Main_mix.root
//////////////////////////////////////////////////////////

#ifndef reader_mix_h
#define reader_mix_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.


   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         tq_rf_m;
   Float_t         tq_rf_pt;
   Float_t         jx_Lxy;
   Float_t         jx_rf_m;
   Float_t         jx_rf_pt;
   Float_t         jx_rf_eta;
   Float_t         jx_rf_phi;
   Float_t         jx_m_calc;
   Float_t         jpsi_m;
   Float_t         x_rf_m;
   Float_t         ld_Lxy;
   Float_t         ld_rf_m;
   Float_t         ld_rf_pt;
   Float_t         ld_rf_eta;
   Float_t         ld_rf_phi;
   Float_t         ld_m;
   Float_t         pt_mu1;
   Float_t         pt_mu2;
   Float_t         pt_K_X;
   Float_t         pt_pi_X;
   Float_t         pt_LRT_trk1;
   Float_t         pt_LRT_trk2;
   Float_t         trk_rf_m[4];
   Float_t         trk_rf_pt[4];
   Float_t         trk_rf_eta[4];
   Float_t         trk_rf_phi[4];

   // List of branches
   TBranch        *b_tq_rf_m;   //!
   TBranch        *b_tq_rf_pt;   //!
   TBranch        *b_jx_Lxy;   //!
   TBranch        *b_jx_rf_m;   //!
   TBranch        *b_jx_rf_pt;   //!
   TBranch        *b_jx_rf_eta;   //!
   TBranch        *b_jx_rf_phi;   //!
   TBranch        *b_jx_m_calc;   //!
   TBranch        *b_jpsi_m;   //!
   TBranch        *b_x_rf_m;   //!
   TBranch        *b_ld_Lxy;   //!
   TBranch        *b_ld_rf_m;   //!
   TBranch        *b_ld_rf_pt;   //!
   TBranch        *b_ld_rf_eta;   //!
   TBranch        *b_ld_rf_phi;   //!
   TBranch        *b_ld_m;   //!
   TBranch        *b_pt_mu1;   //!
   TBranch        *b_pt_mu2;   //!
   TBranch        *b_pt_K_X;   //!
   TBranch        *b_pt_pi_X;   //!
   TBranch        *b_pt_LRT_trk1;   //!
   TBranch        *b_pt_LRT_trk2;   //!
   TBranch        *b_trk_rf_m;   //!
   TBranch        *b_trk_rf_pt;   //!
   TBranch        *b_trk_rf_eta;   //!
   TBranch        *b_trk_rf_phi;   //!


   Int_t    Cut(Long64_t entry);
   Int_t    GetEntry(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void     Init(TTree *tree);
   bool     Notify();
   void     Show(Long64_t entry = -1);




Int_t GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t LoadTree(Long64_t entry)
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
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("tq_rf_m", &tq_rf_m, &b_tq_rf_m);
   fChain->SetBranchAddress("tq_rf_pt", &tq_rf_pt, &b_tq_rf_pt);
   fChain->SetBranchAddress("jx_Lxy", &jx_Lxy, &b_jx_Lxy);
   fChain->SetBranchAddress("jx_rf_m", &jx_rf_m, &b_jx_rf_m);
   fChain->SetBranchAddress("jx_rf_pt", &jx_rf_pt, &b_jx_rf_pt);
   fChain->SetBranchAddress("jx_rf_eta", &jx_rf_eta, &b_jx_rf_eta);
   fChain->SetBranchAddress("jx_rf_phi", &jx_rf_phi, &b_jx_rf_phi);
   fChain->SetBranchAddress("jx_m_calc", &jx_m_calc, &b_jx_m_calc);
   fChain->SetBranchAddress("jpsi_m", &jpsi_m, &b_jpsi_m);
   fChain->SetBranchAddress("x_rf_m", &x_rf_m, &b_x_rf_m);
   fChain->SetBranchAddress("ld_Lxy", &ld_Lxy, &b_ld_Lxy);
   fChain->SetBranchAddress("ld_rf_m", &ld_rf_m, &b_ld_rf_m);
   fChain->SetBranchAddress("ld_rf_pt", &ld_rf_pt, &b_ld_rf_pt);
   fChain->SetBranchAddress("ld_rf_eta", &ld_rf_eta, &b_ld_rf_eta);
   fChain->SetBranchAddress("ld_rf_phi", &ld_rf_phi, &b_ld_rf_phi);
   fChain->SetBranchAddress("ld_m", &ld_m, &b_ld_m);
   fChain->SetBranchAddress("pt_mu1", &pt_mu1, &b_pt_mu1);
   fChain->SetBranchAddress("pt_mu2", &pt_mu2, &b_pt_mu2);
   fChain->SetBranchAddress("pt_K_X", &pt_K_X, &b_pt_K_X);
   fChain->SetBranchAddress("pt_pi_X", &pt_pi_X, &b_pt_pi_X);
   fChain->SetBranchAddress("pt_LRT_trk1", &pt_LRT_trk1, &b_pt_LRT_trk1);
   fChain->SetBranchAddress("pt_LRT_trk2", &pt_LRT_trk2, &b_pt_LRT_trk2);
   fChain->SetBranchAddress("trk_rf_m", trk_rf_m, &b_trk_rf_m);
   fChain->SetBranchAddress("trk_rf_pt", trk_rf_pt, &b_trk_rf_pt);
   fChain->SetBranchAddress("trk_rf_eta", trk_rf_eta, &b_trk_rf_eta);
   fChain->SetBranchAddress("trk_rf_phi", trk_rf_phi, &b_trk_rf_phi);
   Notify();
}

bool Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif 
