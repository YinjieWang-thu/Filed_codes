#define bphy25_cxx
#include "bphy25.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void bphy25::Loop(TString outputname)
{
//   In a ROOT session, you can do:
//      root> .L bphy25.C
//      root> bphy25 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   ofstream data;
   data.open((outputname+".txt").Data(), ios::out|ios::app);
   TFile *out = new TFile("os_hist.root", "RECREATE");
   TH1F* hist=new TH1F("tqmass","tqmass",50,0,20);
   TH1F* hist2=new TH1F("tqmass2","tqmass2",50,0,20);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(
         jx_m > 4979 && jx_m < 5579 && ld_m > 477 && ld_m < 517 
         && jpsi_m > 2800 && jpsi_m < 3400 //&& x_m > 845 && x_m < 945
         && tq_fitChi2NDF < 3 && ld_fitChi2NDF < 3 && jx_fitChi2NDF < 3
         && ld_Lxy > 5 && ld_Lxy < 400 && jx_Lxy > 0.3
         && tq_ratio > 0.3 
         && tq_m < 6000
         && trk_charge[0]*trk_charge[1]<0
      )
      {
         char* line = new char[8192];
         double Deta = eta_K - eta_pi;
         double Dphi = phi_K - phi_pi;
         double DR = sqrt(Deta*Deta+Dphi*Dphi);
         sprintf(line, "%.8f %.8f %.8f %.5f %.8f", tq_m/1000, x_rf_m/1000, pt_K/1000, pt_pi/1000, DR);
         data<<line<<endl;
      }

   }
   data.close();
   out->Write();
}
