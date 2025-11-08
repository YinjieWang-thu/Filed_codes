#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;

void sidebindKstar()
{
    TFile *out = new TFile("fit.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1");
    RooRealVar x("x","x",5.75,6);
    RooRealVar Ks("K*mass","K*mass",0.68,1.08);

    RooRealVar mean("mean","mean",0.892,-1,1);
    mean.setConstant(kTRUE);
    RooRealVar width("width","width",1,0.0001,1);
    RooRealVar sigma("sigma","sigma",1,0.0001,0.05);
    RooAbsPdf * SigPdf=new RooVoigtian("MeanPdf","MeanPdf",Ks,mean,width,sigma);

    RooRealVar *Bkg_a1  = new RooRealVar("bkg_{a1}", "background a1", 0, -1, 1);
    RooRealVar *Bkg_a2  = new RooRealVar("bkg_{a2}", "background a2", 0, -1, 1);
    RooAbsPdf  *BkgPdf  = new RooChebychev("BkgPdf","background", Ks, RooArgList(*Bkg_a1,*Bkg_a2));

    RooRealVar *nsig = new RooRealVar("N_{sig}","nsig",800,0,3000);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",6000,1000,8000);
    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf,*BkgPdf),RooArgList(*nsig,*nbkgd));


    RooDataSet *data = RooDataSet::read("data/tq_Kstar_noKstarcut.txt",RooArgSet(x, Ks),"Q");
    RooPlot* frame = Ks.frame(Title("Kstar_mass"));
    data->plotOn(frame,Binning(50));//
    pdf->fitTo(*data,Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    pdf->plotOn(frame);
    pdf->plotOn(frame, Components("BkgPdf"), LineStyle(kDashed));
    pdf->plotOn(frame, Components("MeanPdf"), LineColor(kRed));
    frame->Draw();
    cout<<"Mean of Gaus: "<< mean.getVal()<<endl;
    cout<<"Width of Gaus: "<< width.getVal()<<endl;
    cout<<"Sigma of Gaus: "<< sigma.getVal()<<endl;
    cout<<"s: "<< nsig->getVal()<<endl;
    cout<<"g: "<< nbkgd->getVal()<<endl;

}