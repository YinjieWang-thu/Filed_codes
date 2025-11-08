/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides examples for the training and testing of the
/// TMVA classifiers.
///
/// As input data is used a toy-MC sample consisting of four Gaussian-distributed
/// and linearly correlated input variables.
/// The methods to be used can be switched on and off by means of booleans, or
/// via the prompt command, for example:
///
///     root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)
///
/// (note that the backslashes are mandatory)
/// If no method given, a default set of classifiers is used.
/// The output file "TMVA.root" can be analysed with the use of dedicated
/// macros (simply say: root -l <macro.C>), which can be conveniently
/// invoked through a GUI that will appear at the end of the run of this macro.
/// Launch the GUI via the command:
///
///     root -l ./TMVAGui.C
///
/// You can also compile and run the example with the following commands
///
///     make
///     ./TMVAClassification <Methods>
///
/// where: `<Methods> = "method1 method2"` are the TMVA classifier names
/// example:
///
///     ./TMVAClassification Fisher LikelihoodPCA BDT
///
/// If no method given, a default set is of classifiers is used
///
/// - Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Root Macro: TMVAClassification
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker


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

#define NVAR 5

int TMVAClassification1( bool testOdd = false )
{
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc

   // Methods to be processed can be given as an argument; use format:
   //
   //     mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // Boosted Decision Trees
   Use["BDTG"]            = 1; // uses Gradient Boost

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Here the preparation phase begins

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TFile *input(0);
   TString fname = "./inputfile1.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;

   // Register the training and test trees

   TTree *signalTree     = (TTree*)input->Get("BPHY25_sig");
   TTree *background     = (TTree*)input->Get("BPHY25_bkg");

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA1.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("BDT1");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   /* dataloader->AddVariable( "myvar1 := var1+var2", 'F' ); */
   /* dataloader->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' ); */
   /* dataloader->AddVariable( "var3",                "Variable 3", "units", 'F' ); */
   /* dataloader->AddVariable( "var4",                "Variable 4", "units", 'F' ); */

   dataloader->AddVariable("ld_Lxy","","mm",'F');
   dataloader->AddVariable("jx_Lxy","","mm",'F');
   dataloader->AddVariable("tq_rf_ratio","","",'F');
   dataloader->AddVariable("tq_rf_Lxy","","mm",'F');
   dataloader->AddVariable("tq_rf_fitChi2NDF","","",'F');

   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   /* dataloader->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' ); */
   /* dataloader->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' ); */

   std::vector<Double_t> vars(NVAR);
   Float_t treevars[NVAR], weight;
   ULong64_t event_number;
   signalTree->SetBranchAddress( "weight", &weight );
   signalTree->SetBranchAddress( "event_number", &event_number );
   signalTree->SetBranchAddress( "ld_Lxy", &(treevars[0]) );
   signalTree->SetBranchAddress( "jx_Lxy", &(treevars[1]) );
   signalTree->SetBranchAddress( "tq_rf_ratio", &(treevars[2]) );
   signalTree->SetBranchAddress( "tq_rf_Lxy", &(treevars[3]) );
   signalTree->SetBranchAddress( "tq_rf_fitChi2NDF", &(treevars[4]) );

   for (UInt_t i=0; i<signalTree->GetEntries(); i++) {
     signalTree->GetEntry(i);
     for (UInt_t ivar=0; ivar<NVAR; ivar++) vars[ivar] = treevars[ivar];
     if(testOdd) {
       if(event_number%2==0) dataloader->AddSignalTrainingEvent( vars, weight );
       else                  dataloader->AddSignalTestEvent    ( vars, weight );
     }
     else {
       if(event_number%2==1) dataloader->AddSignalTrainingEvent( vars, weight );
       else                  dataloader->AddSignalTestEvent    ( vars, weight );
     }
   }

   background->SetBranchAddress( "weight", &weight );
   background->SetBranchAddress( "event_number", &event_number );
   background->SetBranchAddress( "ld_Lxy", &(treevars[0]) );
   background->SetBranchAddress( "jx_Lxy", &(treevars[1]) );
   background->SetBranchAddress( "tq_rf_ratio", &(treevars[2]) );
   background->SetBranchAddress( "tq_rf_Lxy", &(treevars[3]) );
   background->SetBranchAddress( "tq_rf_fitChi2NDF", &(treevars[4]) );

   for (UInt_t i=0; i<background->GetEntries(); i++) {
     background->GetEntry(i);
     for (UInt_t ivar=0; ivar<NVAR; ivar++) vars[ivar] = treevars[ivar];
     if(testOdd) {
       if(event_number%2==0) dataloader->AddBackgroundTrainingEvent( vars, weight );
       else                  dataloader->AddBackgroundTestEvent    ( vars, weight );
     }
     else {
       if(event_number%2==1) dataloader->AddBackgroundTrainingEvent( vars, weight );
       else                  dataloader->AddBackgroundTestEvent    ( vars, weight );
     }
   }

   dataloader->PrepareTrainingAndTestTree( "", "", "NormMode=NumEvents:!V" );

   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=500:MinNodeSize=7%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=18:MaxDepth=3" );

   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}
