#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;

void b0fit()
{
    TFile *out = new TFile("b0fit.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1");
    RooRealVar x("x","x",5.75,5.9);
    RooRealVar Ks("Ks","Ks",0.5,1.3);
    RooRealVar B0("B0","B0",4.979,5.579);
    RooDataSet *data = RooDataSet::read("data/tqKsb0_sideband_ss.txt",RooArgSet(x, Ks, B0),"Q");
    RooPlot* frame = B0.frame(Title("B0_mass:sideband,ss"));
    data->plotOn(frame);
    RooRealVar mean1("mean1","mean1",5.28,4.979,5.579);
    RooRealVar sigma1("sigma1","sigma1",0.5,0,3);
    RooAbsPdf * SigPdf1=new RooGaussian("SigPdf1","SigPdf1",B0,mean1,sigma1);
    SigPdf1->fitTo(*data, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    SigPdf1->plotOn(frame);
    frame->Draw();
}