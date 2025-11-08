#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"

#include "bphy25.C"

#include <vector>
#include <iostream>
#include <string>

void execute()
{
	TChain *chain = new TChain("BPHY25","");
	chain->Add("BPHY25_B0Ks_SS_OS.root");
	bphy25 a(chain);
	a.Loop("output/os_nnn");
        //Delete all things to save memory
	a.~bphy25();
	delete chain;
    gROOT->ProcessLine(".q");
}