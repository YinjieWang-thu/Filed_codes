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
	chain->Add("../BPhy25_ntuple/data/data.root");//../BPhy25_ntuple/data/*.roo
	bphy25 a(chain);
	a.LoopCut("output/out_os");
        //Delete all things to save memory
	a.~bphy25();
	delete chain;
    gROOT->ProcessLine(".q");
}


//sop:
//check input
//check function
//check output
//execute
