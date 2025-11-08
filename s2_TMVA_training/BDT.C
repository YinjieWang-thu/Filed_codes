#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

void BDT()
{
    TMVA::Tools::Instance();

    TString fname = "data/TMVA.root";
    TFile *input = TFile::Open(fname);

    TTree *signalTree = (TTree*)input->Get("Signaltree");
    TTree *background = (TTree*)input->Get("Bkgtreee");//wrong name but just do it

    TString outfileName( "TMVAC3.root" );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

    TMVA::Factory *factory = new TMVA::Factory( "BphyBDT1", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset3");

    //vars
    /*
    Signaltree->Branch("Pt_mu1",&Pt_mu1,"Pt_mu1/F");
    Signaltree->Branch("Pt_mu2",&Pt_mu2,"Pt_mu2/F");
    Signaltree->Branch("Pt_K",&Pt_K,"Pt_K/F");
    Signaltree->Branch("Pt_pi",&Pt_pi,"Pt_pi/F");
    Signaltree->Branch("DR_Kpi",&DR_Kpi,"DR_Kpi/F");
    Signaltree->Branch("Pt_pi1",&Pt_pi1,"Pt_pi1/F");
    Signaltree->Branch("Pt_pi2",&Pt_pi2,"Pt_pi2/F");
    Signaltree->Branch("Pt_B0",&Pt_B0,"Pt_B0/F");
    Signaltree->Branch("Pt_Ks",&Pt_Ks,"Pt_Ks/F");
    Signaltree->Branch("DR_B0Ks",&DR_B0Ks,"DR_B0Ks/F");
    Signaltree->Branch("Pt_tq",&Pt_tq,"Pt_tq/F");
    Signaltree->Branch("M_tq",&M_tq,"M_tq/F");
    Signaltree->Branch("M_jpsi",&M_jpsi,"M_jpsi/F");
    Signaltree->Branch("M_Kpi",&M_Kpi,"M_Kpi/F");
    Signaltree->Branch("M_B0",&M_B0,"M_B0/F");
    Signaltree->Branch("M_Ks",&M_Ks,"M_Ks/F");
    */

    dataloader->AddVariable( "Pt_mu1","Pt_mu1", "units", 'F' );
    dataloader->AddVariable( "Pt_mu2","Pt_mu2", "units", 'F' );
    dataloader->AddVariable( "Pt_K","Pt_K", "units", 'F' );
    dataloader->AddVariable( "Pt_pi","Pt_pi", "units", 'F' );
    dataloader->AddVariable( "DR_Kpi","DR_Kpi", "units", 'F' );
    dataloader->AddVariable( "Pt_pi1","Pt_pi1", "units", 'F' );
    dataloader->AddVariable( "Pt_pi2","Pt_pi2", "units", 'F' );
    dataloader->AddVariable( "Pt_B0","Pt_B0", "units", 'F' );
    dataloader->AddVariable( "Pt_Ks","Pt_Ks", "units", 'F' );
    dataloader->AddVariable( "DR_B0Ks","DR_B0Ks", "DR_B0Ks", 'F' );
    dataloader->AddVariable( "Pt_tq","Pt_tq", "units", 'F' );
    //dataloader->AddVariable( "M_tq","M_tq", "units", 'F' );
    dataloader->AddVariable( "M_jpsi","M_jpsi", "units", 'F' );
    dataloader->AddVariable( "M_Kpi","M_Kpi", "units", 'F' );
    dataloader->AddVariable( "M_B0","M_B0", "units", 'F' );
    dataloader->AddVariable( "M_Ks","M_Ks", "units", 'F' );

    Double_t signalWeight     = 1.0;
    Double_t backgroundWeight = 1.0;

    dataloader->AddSignalTree    ( signalTree,     signalWeight );
    dataloader->AddBackgroundTree( background, backgroundWeight );

    dataloader->SetSignalWeightExpression("weight");
    dataloader->SetBackgroundWeightExpression("weight");

    TCut mycuts = "";;
    TCut mycutb = "";

    dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=random:!V:nTrain_Signal=0:nTrain_Background=0:nTest_Signal=0:nTest_Background=0" );

    factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=500:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
    outputFile->Close();
    delete factory;
    delete dataloader;
    if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );
}

