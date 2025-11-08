#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;


void fit()
{
    TFile *out = new TFile("fit.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1");
    RooRealVar x("x","x",5.75,5.9);
    RooRealVar Ks("Ks","Ks",0.845,0.945);//Kstar mass window cut, don't forget if disable this cut in plot

    RooRealVar mean1("mean1","mean1",5.782981,5.78,5.79);
    RooRealVar sigma1("sigma1","sigma1",0.0001,0.0001,1);
    RooRealVar width1("width1","width1",0.0001,0.0001,1);
    RooAbsPdf * SigPdf1=new RooVoigtian("SigPdf1","SigPdf1",x,mean1,width1,sigma1);

    RooRealVar mean2("mean2","mean2",5.794571,5.79,5.797);
    RooRealVar sigma2("sigma2","sigma2",0.0001,0.0001,1);
    RooRealVar width2("width2","width2",0.0001,0.0001,1);
    RooAbsPdf * SigPdf2=new RooVoigtian("SigPdf2","SigPdf2",x,mean2,width2,sigma2);

    RooRealVar mean3("mean3","mean3",5.839751,5.83,5.85);
    RooRealVar sigma3("sigma3","sigma3",0.0001,0.0001,1);
    RooRealVar width3("width3","width3",0.0001,0.0001,1);
    RooAbsPdf * SigPdf3=new RooVoigtian("SigPdf3","SigPdf3",x,mean3,width3,sigma3);

    RooRealVar mass_B0Ks("mass_B0Ks", "mass_B0Ks", 5.7773, 5.77, 5.78);
    RooRealVar Bkg_a1("Bkg_a1", "background a1", 0.298217, 0.15, 1);//Bkg_a1最小值小于x_max - mass_B0Ks时会报错(积分会炸)
    mass_B0Ks.setConstant(kTRUE);
    RooFormulaVar x_shifted("x_shifted", "mass_B0Ks+Bkg_a1-x", RooArgSet(mass_B0Ks, Bkg_a1, x));
    RooRealVar Bkg_a2("Bkg_a2", "background a2", 0.25, 0, 10);
    //RooAbsPdf  *BkgPdf  = new RooChebychev("BkgPdf","background", x,RooArgList(Bkg_a1,Bkg_a2));
    RooAbsPdf  *BkgPdf  = new RooArgusBG("BkgPdf","background", x_shifted, Bkg_a1, Bkg_a2);

    RooRealVar *nsig1 = new RooRealVar("N_{sig1}","nsig1",50,0,5000);
    RooRealVar *nsig2 = new RooRealVar("N_{sig2}","nsig2",10,0,5000);
    RooRealVar *nsig3 = new RooRealVar("N_{sig3}","nsig3",700,0,5000);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",14000,0,20000);

    if(1){
    mean1.setConstant(kTRUE);
    mean2.setConstant(kTRUE);
    mean3.setConstant(kTRUE);}

    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf1,*SigPdf2,*SigPdf3,*BkgPdf),RooArgList(*nsig1,*nsig2,*nsig3,*nbkgd));
    
    //RooDataSet* toyMC_data = pdf->generate(x,10000) ; 
    RooDataSet *data = RooDataSet::read("data/tq_data.txt",RooArgSet(x),"Q");


    RooPlot* frame = x.frame(Title("m_{B^{0}K_{s}}"));
    data->plotOn(frame,Binning(50));
    pdf->fitTo(*data, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    pdf->plotOn(frame, Components("SigPdf1,SigPdf2,SigPdf3"), LineColor(kRed));
    pdf->plotOn(frame);
    pdf->plotOn(frame, Components("BkgPdf"), LineStyle(kDashed));

    frame->Draw();
    c1->SaveAs("roofit.png");
    out->Write();

    cout<<"peak1: "<<mean1.getVal()<<" / "<<sigma1.getVal()<<" / "<<width1.getVal()<<" / "<<nsig1->getVal()<<endl;
    cout<<"peak2: "<<mean2.getVal()<<" / "<<sigma2.getVal()<<" / "<<width2.getVal()<<" / "<<nsig2->getVal()<<endl;
    cout<<"peak3: "<<mean3.getVal()<<" / "<<sigma3.getVal()<<" / "<<width3.getVal()<<" / "<<nsig3->getVal()<<endl;
    cout<<"Bkg_par: "<<Bkg_a1.getVal()<<" / "<<Bkg_a2.getVal()<<" / "<<nbkgd->getVal()<<endl;

}