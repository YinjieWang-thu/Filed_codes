#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"

#include <vector>
#include <iostream>
#include <string>
#include "function_run3main.h"

#define Names std::vector<std::string>

void PrintCurrentCut()
{
        std::ofstream file;
        std::string text = "result/cutvalues.txt";
        file.open(text.c_str(), std::ios::out);
        file << "Cut Ranges: "<<endl;
        file << MuJpsiRes_MinOpt << " < " << "MuJpsiRes" << " < " <<  MuJpsiRes_MaxOpt << endl;
        file << MuonD0_MinOpt << " < " << "MuonD0" << " < " <<  MuonD0_MaxOpt << endl;
        file << MuonIso_MinOpt << " < " << "MuonIso" << " < " <<  MuonIso_MaxOpt << endl;
        file << Dpipi_MinOpt << " < " << "Dpipi" << " < " <<  Dpipi_MaxOpt << endl;
        file << Dpsi2smu_MinOpt << " < " << "Dpsi2smu" << " < " <<  Dpsi2smu_MaxOpt << endl;
       file << Dpsi2spi_MinOpt << " < " << "Dpsi2spi" << " < " <<  Dpsi2spi_MaxOpt << endl;
        file << Dpsi2sjpsi1_MinOpt << " < " << "Dpsi2sjpsi1" << " < " <<  Dpsi2sjpsi1_MaxOpt << endl;
        file << Djpsimu_MinOpt << " < " << "Djpsimu" << " < " <<  Djpsimu_MaxOpt << endl;
        file << XEta_MinOpt << " < " << "XEta" << " < " <<  XEta_MaxOpt << endl;
        file << XPt_MinOpt << " < " << "XPt" << " < " <<  XPt_MaxOpt << endl;
        file << psi2sProb_MinOpt << " < " << "psi2sProb" << " < " <<  psi2sProb_MaxOpt << endl;
        file << psi2sEta_MinOpt << " < " << "psi2sEta" << " < " <<  psi2sEta_MaxOpt << endl;
        file << psi2sPt_MinOpt << " < " << "psi2sPt" << " < " <<  psi2sPt_MaxOpt << endl;
        file << jpsi2Eta_MinOpt << " < " << "jpsi2Eta" << " < " <<  jpsi2Eta_MaxOpt << endl;
        file << jpsi1Eta_MinOpt << " < " << "jpsi1Eta" << " < " <<  jpsi1Eta_MaxOpt << endl;
        file << jpsi2Pt_MinOpt << " < " << "jpsi2Pt" << " < " <<  jpsi2Pt_MaxOpt << endl;
        file << jpsi1Pt_MinOpt << " < " << "jpsi1Pt" << " < " <<  jpsi1Pt_MaxOpt << endl;
        file << MuEta_MinOpt << " < " << "MuEta" << " < " <<  MuEta_MaxOpt << endl;
        file << MuPt_MinOpt << " < " << "MuPt" << " < " <<  MuPt_MaxOpt << endl;
        file << PiEta_MinOpt << " < " << "PiEta" << " < " <<  PiEta_MaxOpt << endl;
        file << PiPt_MinOpt << " < " << "PiPt" << " < " <<  PiPt_MaxOpt << endl;
        //CUTRANGE
        file << endl;
        file << endl;
        file << "Draw Ranges: "<<endl;
        file << MuJpsiRes_Min << " < " << "MuJpsiRes" << " < " <<  MuJpsiRes_Max << endl;
        file << MuonD0_Min << " < " << "MuonD0" << " < " <<  MuonD0_Max << endl;
        file << MuonIso_Min << " < " << "MuonIso" << " < " <<  MuonIso_Max << endl;
        file << Dpipi_Min << " < " << "Dpipi" << " < " <<  Dpipi_Max << endl;
        file << Dpsi2smu_Min << " < " << "Dpsi2smu" << " < " <<  Dpsi2smu_Max << endl;
        file << Dpsi2spi_Min << " < " << "Dpsi2spi" << " < " <<  Dpsi2spi_Max << endl;
       file << Dpsi2sjpsi1_Min << " < " << "Dpsi2sjpsi1" << " < " <<  Dpsi2sjpsi1_Max << endl;
        file << Djpsimu_Min << " < " << "Djpsimu" << " < " <<  Djpsimu_Max << endl;
        file << XEta_Min << " < " << "XEta" << " < " <<  XEta_Max << endl;
        file << XPt_Min << " < " << "XPt" << " < " <<  XPt_Max << endl;
        file << psi2sProb_Min << " < " << "psi2sProb" << " < " <<  psi2sProb_Max << endl;
        file << psi2sEta_Min << " < " << "psi2sEta" << " < " <<  psi2sEta_Max << endl;
        file << psi2sPt_Min << " < " << "psi2sPt" << " < " <<  psi2sPt_Max << endl;
        file << jpsi2Eta_Min << " < " << "jpsi2Eta" << " < " <<  jpsi2Eta_Max << endl;
        file << jpsi1Eta_Min << " < " << "jpsi1Eta" << " < " <<  jpsi1Eta_Max << endl;
        file << jpsi2Pt_Min << " < " << "jpsi2Pt" << " < " <<  jpsi2Pt_Max << endl;
        file << jpsi1Pt_Min << " < " << "jpsi1Pt" << " < " <<  jpsi1Pt_Max << endl;
        file << MuEta_Min << " < " << "MuEta" << " < " <<  MuEta_Max << endl;
        file << MuPt_Min << " < " << "MuPt" << " < " <<  MuPt_Max << endl;
       file << PiEta_Min << " < " << "PiEta" << " < " <<  PiEta_Max << endl;
        file << PiPt_Min << " < " << "PiPt" << " < " <<  PiPt_Max << endl;
       //DRAWRANGE
        file << endl;
        file.close();
}

void Execute_run3main()
{
        int status = system("bash initialization.sh");
        if(status != 0)
        {
                cout<<"Initialization Failed!"<<endl;
                return;
        }
	myset(myStyle, variables);

	Names * name = new Names();
	//Register file names here
        name->push_back("MuonD0_run3main.C");
        name->push_back("MuonIso_run3main.C");
        name->push_back("Dpipi_run3main.C");
        name->push_back("Dpsi2smu_run3main.C");
        name->push_back("Dpsi2spi_run3main.C");
        name->push_back("Dpsi2sjpsi1_run3main.C");
        name->push_back("Djpsismu_run3main.C");
        name->push_back("XEta_run3main.C");
        name->push_back("XPt_run3main.C");
        name->push_back("psi2sProb_run3main.C");
        name->push_back("psi2sEta_run3main.C");
        name->push_back("psi2sPt_run3main.C");
        name->push_back("jpsi2Eta_run3main.C");
        name->push_back("jpsi1Eta_run3main.C");
        name->push_back("jpsi2Pt_run3main.C");
        name->push_back("jpsi1Pt_run3main.C");
        name->push_back("MuEta_run3main.C");
        name->push_back("MuPt_run3main.C");
        name->push_back("PiEta_run3main.C");
        name->push_back("PiPt_run3main.C");
	unsigned int num = name->size();
	std::string cmd;
        
	for(unsigned int i = 0; i < num; i++)
	{
		std::cout<<"I am processing "<<name->at(i)<<std::endl;
		std::cout<<"This is "<<i + 1<<" out of "<<num<<std::endl;
                cmd = ".x " + name->at(i);
                std::cout<<cmd.c_str()<<std::endl;
                gROOT->ProcessLine(cmd.c_str());
	}
        PrintCurrentCut();
}
