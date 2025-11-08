#define bphy25_cxx
#include "bphy25.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include "TRandom.h"
#include <vector>
#include <algorithm> // for std::swap
#include <iostream>
/*
   virtual void     Loop(TString outputname);
   virtual void     LoopCut(TString outputname);
   virtual void     LoopSeq(TString outputname);
   virtual void     LoopSwapKs(TString outputname);
   virtual void     LoopConditionalSwapKs(TString outputname, float mass_limit);
*/
#define GeV 1000

using namespace std;

void bphy25::Loop(TString outputname)
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   ofstream data;
   data.open((outputname+".txt").Data(), ios::out|ios::app);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
 
      if(
         jx_m > 4979 && jx_m < 5579 && ld_m > 477 && ld_m < 517 
         && jpsi_m > 2800 && jpsi_m < 3400 && x_m > 845 && x_m < 945
         && tq_rf_fitChi2NDF < 3 && ld_fitChi2NDF < 3 && jx_fitChi2NDF < 3
         && ld_Lxy > 5 && ld_Lxy < 400 && jx_Lxy > 0.3
         && tq_rf_ratio > 0.3 && tq_rf_m < 6000
      )
      {
         char* line = new char[8192];
         sprintf(line, "%.8f",tq_rf_m/1000);
         data<<line<<endl;
         
      }
   }

   data.close();
}

void bphy25::LoopCut(TString outputname)
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *myoutput = new TFile(outputname + ".root", "Recreate");



   TH1F* ld_mass=new TH1F("ld_mass","ld_mass", 50, 240, 760);
   TH1F* tq_mass=new TH1F("tq_mass","tq_mass", 60, 5.76, 5.91);
   TH1F* jpsi_mass=new TH1F("jpsi_mass","jpsi_mass", 50, 2400, 3700);
   TH1F* x_mass=new TH1F("x_mass","x_mass", 50, 800, 1000);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(   jx_m_calc / GeV > 5.08 && jx_m_calc / GeV < 5.48 &&
            //ld_m / GeV > 0.477 && ld_m / GeV < 0.517 &&
            jpsi_m / GeV > 2.6 && jpsi_m / GeV < 3.5 &&
            tq_rf_m / GeV < 5.91 && pt_K_X /GeV >1.0 &&
            x_rf_m / GeV > 0.68 && x_rf_m / GeV < 1.07 &&
            tq_rf_fitChi2NDF < 5 && //ld_fitChi2NDF < 3.0 && jx_fitChi2NDF < 3.0 &&
            //ld_Lxy > 5 && ld_Lxy < 400 &&
            jx_Lxy > 0.3 && //tq_rf_ratio > 0.3 &&
            trk_charge[0]*trk_charge[1]<0

            && tq_rf_fitChi2NDF<2.0

            && tq_rf_ratio>0.25

            && jpsi_m/GeV>2.95 && jpsi_m/GeV<3.22

            && x_rf_m/GeV>0.83 && x_rf_m/GeV<0.96

            && ld_m/GeV>0.475 && ld_m/GeV<0.52
         )
      {
         ld_mass -> Fill(ld_m);
         tq_mass -> Fill(tq_rf_m/1000);
         jpsi_mass -> Fill(jpsi_m);
         x_mass -> Fill(x_m);
         
      }
      if (Cut(ientry) < 0) continue;
   }
   myoutput->Write();
}

void bphy25::LoopSeq(TString outputname)
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *myoutput = new TFile(outputname + ".root", "Recreate");


   TH1F* tq_mass_cut0=new TH1F("tq_mass_cut0","tq_mass_cut0", 50, 5300, 6000);
   TH1F* tq_mass_cut1=new TH1F("tq_mass_cut1","tq_mass_cut1", 50, 5300, 6000);
   TH1F* tq_mass_cut2=new TH1F("tq_mass_cut2","tq_mass_cut2", 50, 5300, 6000);
   TH1F* tq_mass_cut3=new TH1F("tq_mass_cut3","tq_mass_cut3", 50, 5300, 6000);
   TH1F* tq_mass_cut4=new TH1F("tq_mass_cut4","tq_mass_cut4", 50, 5300, 6000);
   TH1F* tq_mass_cut5=new TH1F("tq_mass_cut5","tq_mass_cut5", 50, 5300, 6000);
   TH1F* tq_mass_cut6=new TH1F("tq_mass_cut6","tq_mass_cut6", 50, 5300, 6000);
   TH1F* tq_mass_cut7=new TH1F("tq_mass_cut7","tq_mass_cut7", 50, 5300, 6000);
   TH1F* tq_mass_cut8=new TH1F("tq_mass_cut8","tq_mass_cut8", 50, 5300, 6000);
   TH1F* tq_mass_cut9=new TH1F("tq_mass_cut9","tq_mass_cut9", 50, 5300, 6000);
   TH1F* tq_mass_cut10=new TH1F("tq_mass_cut10","tq_mass_cut10", 50, 5300, 6000);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      tq_mass_cut0 -> Fill(tq_rf_m);
      if(jx_m > 4979 && jx_m < 5579)
      {
         tq_mass_cut1 -> Fill(tq_rf_m);
         if(ld_m > 477 && ld_m < 517)
         {
            tq_mass_cut2 -> Fill(tq_rf_m);
            if(jpsi_m > 2800 && jpsi_m < 3400)
            {
               tq_mass_cut3 -> Fill(tq_rf_m);
               if(x_m > 845 && x_m < 945)
               {
                  tq_mass_cut4 -> Fill(tq_rf_m);
                  if(tq_rf_fitChi2NDF < 3 )
                  {
                     tq_mass_cut5 -> Fill(tq_rf_m);
                     if(ld_fitChi2NDF < 3)
                     {
                        tq_mass_cut6 -> Fill(tq_rf_m);
                        if(jx_fitChi2NDF < 3)
                        {
                           tq_mass_cut7 -> Fill(tq_rf_m);
                           if(ld_Lxy > 5 && ld_Lxy < 400)
                           {
                              tq_mass_cut8 -> Fill(tq_rf_m);
                              if(jx_Lxy > 0.3)
                              {
                                 tq_mass_cut9 -> Fill(tq_rf_m);
                                 if(tq_rf_ratio > 0.3)
                                 {
                                    tq_mass_cut10 -> Fill(tq_rf_m);
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
      
      

   }
   myoutput->Write();
}

void bphy25::LoopSwapKs(TString outputname)
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   ofstream data;
   data.open((outputname+".txt").Data(), ios::out|ios::app);

   Long64_t nbytes = 0, nb = 0;
   int seq = 0;
   TLorentzVector Ks1;
   TLorentzVector Ks2;
   TLorentzVector B01;
   TLorentzVector B02;
   TLorentzVector tq_mix_1;
   TLorentzVector tq_mix_2;
   TFile *myoutput = new TFile(outputname + ".root", "Recreate");
   TH1F* tq_mass=new TH1F("tq_mass","tq_mass", 50, 5.7, 6);
   TH1F* tq_mass2=new TH1F("tq_mass2","tq_mass2", 50, 5, 9.7);
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(
         
         jx_m > 4979 && jx_m < 5579 && ld_m > 477 && ld_m < 517 
         && jpsi_m > 2800 && jpsi_m < 3400 && x_m > 845 && x_m < 945
         && tq_rf_fitChi2NDF < 3 && ld_fitChi2NDF < 3 && jx_fitChi2NDF < 3
         && ld_Lxy > 5 && ld_Lxy < 400 && jx_Lxy > 0.3
         && tq_rf_ratio > 0.3
      )
      {
         if(seq == 0)
         {
            B01.SetPtEtaPhiM(jx_rf_pt, jx_rf_eta, jx_rf_phi, jx_rf_m);
            Ks1.SetPtEtaPhiM(ld_rf_pt, ld_rf_eta, ld_rf_phi, ld_rf_m);
         }

         if(seq == 1)
         {
            B02.SetPtEtaPhiM(jx_rf_pt, jx_rf_eta, jx_rf_phi, jx_rf_m);
            Ks2.SetPtEtaPhiM(ld_rf_pt, ld_rf_eta, ld_rf_phi, ld_rf_m);
            tq_mix_1 = B01 + Ks1;
            tq_mix_2 = B02 + Ks2;
            float mass1 = tq_mix_1.M()/1000;
            float mass2 = tq_mix_2.M()/1000;
            char* line = new char[8192];
            sprintf(line, "%.8f", mass1);
            data<<line<<endl;
            sprintf(line, "%.8f", mass2);
            data<<line<<endl;
            seq = -1;
            tq_mass->Fill(mass1);
            tq_mass->Fill(mass2);
            tq_mass2->Fill(mass1);
            tq_mass2->Fill(mass2);
         }
         seq+=1;
      }
   }
   myoutput->Write();
   data.close();
}

void bphy25::LoopConditionalSwapKs(TString outputname, float mass_limit)//use cut input
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   //Long64_t nentries = 20;//预设输入最大事例数
   ofstream data;
   data.open((outputname+".txt").Data(), ios::out|ios::app);

   Long64_t nbytes = 0, nb = 0;
   int success_pair = 0;
   int in_range = 0;
   int block = 1000;
   int pair_min = 0;
   int pair_max = block-1;
   vector<int> used_entry;
   TLorentzVector Ks;
   TLorentzVector B0;
   TLorentzVector tq_mix;

   //每一次运行使用Fisher-Yates算法得到一个随机排列，在每一个block中用来实现随机顺序的配对
   /*
   int n = block;
   vector<int> permutation(n);
   for(int i = 0; i < n; ++i) {
      permutation[i] = i;
   }
   for(int i = n - 1; i > 0; --i) {
      int j = gRandom->Integer(i + 1);
      swap(permutation[i], permutation[j]);
   }
   */

   TFile *myoutput = new TFile(outputname + ".root", "Recreate");
   TH1F* tq_mass=new TH1F("tq_mass","tq_mass", 50, 5.7, 6);
   TH1F* tq_mass2=new TH1F("tq_mass2","tq_mass2", 50, 5, mass_limit);

   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if(jentry % 100 == 0)
      {
         cout<<"processing "<<jentry<<" out of "<<nentries<<", valid pairs: "<<success_pair<<endl;
      }
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      B0.SetPtEtaPhiM(jx_rf_pt, jx_rf_eta, jx_rf_phi, jx_rf_m);
      //cout<<"pairing entry "<<jentry<<", event number: "<<event_number<<endl;

      if(jentry%block == 0)
      {
         pair_min = jentry;
         pair_max = jentry+block;
         used_entry.clear();
         cout<<"reset pair range: "<<pair_min<<" to "<<pair_max<<endl;
      }
      for (Long64_t kentry=pair_min; kentry<pair_max;kentry++)
      {
         //Long64_t kentry = permutation[ientry-pair_min];//得到随机匹配的输入
         Long64_t fentry = LoadTree(kentry);
         if (fentry < 0) break;
         nb = fChain->GetEntry(kentry);   nbytes += nb;

         //cout<<"  trying entry "<<kentry<<", event number: "<<event_number<<" : ";
         if(kentry == jentry)
         {
            //cout<<"same event, pass."<<endl;
            continue;
         }

         bool used_ent = 0;
         for(int lentry : used_entry)
         {
            if(kentry == lentry)
            {
               used_ent = 1;
               break;
            }
         }
         if(used_ent)
         {
            //cout<<"used event, pass."<<endl;
            continue;
         }

         Ks.SetPtEtaPhiM(ld_rf_pt, ld_rf_eta, ld_rf_phi, ld_rf_m);

         tq_mix = B0 + Ks;
         float mass = tq_mix.M()/1000;
         if(mass>mass_limit)
         {
            //cout<<"tq mass is "<< mass <<", too large, pass."<<endl;
            continue;
         }
         else{
            tq_mass->Fill(mass);
            tq_mass2->Fill(mass);
            used_entry.push_back(kentry);
            //cout<<"  trying entry "<<kentry<<", event number: "<<event_number<<" : ";
            //cout<<"tq mass is"<< mass <<", valid pair."<<endl;
            char* line = new char[8192];
            sprintf(line, "%.8f", mass);
            data<<line<<endl;
            success_pair ++;
            if(mass<5.9) in_range++;
            break;
         }
      }

      

   }
   cout<<"total valid pair: "<<success_pair<<endl;
   cout<<"total pair mass<5.9: "<<in_range<<endl;
   myoutput->Write();
   data.close();
}