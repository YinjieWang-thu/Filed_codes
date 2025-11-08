#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TChain.h"
#include "TString.h"
#include "TRegexp.h"
#include "AnalysisUser_wyj.cxx"
#include "header.cxx"
using namespace std;

void execute()
{
	Int_t process = 1;
	Int_t cat = 100;
	Int_t type = 3;

	//Configurations
	std::string framelist = "input.txt";
	std::string inputdir = "input/";
	std::string outputdir = "out2/";

	ifstream list(framelist.c_str(), ios::in);
    if(!list.is_open())
    {
        cout << "No File or Open Error!" << endl;
	}
	std::string data;
	vector<string> inputFiles;
	while(getline(list, data))
	{
		inputFiles.push_back(data);
	}
	list.close();

	for(int i=0; i<inputFiles.size(); i++)
	{
		AnalysisUser a(inputdir + inputFiles[i]);
		cout << "Processing " << inputFiles[i] << endl;
		std::string outputFile = outputdir+inputFiles[i];
		a.initialize(outputFile.c_str(), process, cat, type);
  		Long64_t nEntries = a.GetEntries();
  		printf("%ld entries to be processed\n",(long int)nEntries);
  		for(Long64_t i=0; i<nEntries; i++) {
  	  	a.GetEntry(i);
    	a.execute();
   		 if((i+1)%100000==0) printf("%ld entries processed...\n",(long int)(i+1));
  		}
		a.finalize();
	}
	gROOT->ProcessLine(".q");
	return;
}