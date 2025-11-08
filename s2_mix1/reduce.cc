#include "TROOT.h"
#include "TObject.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <vector>
#include <utility>
#include <iostream>

#include "reader.h"

using namespace std;
const Double_t GeV=1000;

void reduce(const char* infile="data.root", const char* outfile="data_reduced.root")
{
   TChain* oldtree = new TChain("BPHY25");
   oldtree->Add(infile);
   Init(oldtree);
   std::cout<<oldtree->GetEntries()<<std::endl;

   ULong64_t nentries = oldtree->GetEntries();

   // Create a new file + a clone of old tree in new file
   TFile newfile(outfile, "recreate");
   TTree* newtree = oldtree->CloneTree(0);

   for (ULong64_t entry=0; entry<nentries; entry++) {
     oldtree->GetEntry(entry);

     if(jpsi_m/GeV>2.95 && jpsi_m/GeV<3.22 && x_rf_m/GeV>0.84 && x_rf_m/GeV<0.95
	&& jx_m_calc/GeV>5.08 && jx_m_calc/GeV<5.48 && tq_rf_fitChi2NDF<2.0
	&& ld_m/GeV>0.475 && ld_m/GeV<0.520 && tq_rf_ratio>0.15
	&& jx_Lxy>0.2 && pt_K_X/GeV>1.0
	&& trk_charge[0]*trk_charge[1]<0) {
       newtree->Fill();
     }
     if((entry+1)%100000==0) printf(" %llu entries processed...\n",entry+1);
   }
   std::cout<<newtree->GetEntries()<<std::endl;
   newfile.Write();
}