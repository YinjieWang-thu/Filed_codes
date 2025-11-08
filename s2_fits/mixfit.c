#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;


void mixfit()
{


    TFile *out = new TFile("fit.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1",1000,700);
    //c1->Divide(2,1);
    RooRealVar x("x","x",5.75,5.9);
    RooRealVar Ks("Ks","Ks",0.845,0.945);//Kstar mass window cut, don't forget if disable this cut in plot

    RooRealVar mean1("mean1","mean1",5.782981,5.78,5.79);
    RooRealVar sigma1("sigma1","sigma1",0.002,0.0001,0.01);//  sigma = Gamma / 2.3548 fix 0.0004/2.3548
    RooAbsPdf * SigPdf1=new RooGaussian("SigPdf1","SigPdf1",x,mean1,sigma1);

    RooRealVar mean2("mean2","mean2",5.794571,5.79,5.797);
    RooRealVar sigma2("sigma2","sigma2",0.002,0.0001,0.01);
    RooAbsPdf * SigPdf2=new RooGaussian("SigPdf2","SigPdf2",x,mean2,sigma2);

    RooRealVar mean3("mean3","mean3",5.839751,5.83,5.85);
    RooRealVar sigma23("sigma23","sigma23",0.0021/2.3548,0.0001,0.01);

    RooRealVar sigma3("sigma3","sigma3",0.002,0.0001,0.01);
    RooAbsPdf * SigPdf3=new RooGaussian("SigPdf3","SigPdf3",x,mean3,sigma3);

    RooRealVar mass_B0Ks("mass_B0Ks", "mass_B0Ks", 5.7773, 5.77, 5.78);
    RooRealVar Bkg_a1("Bkg_a1", "background a1", 0.298217, 0.15, 10);//Bkg_a1最小值小于x_max - mass_B0Ks时会报错(积分会炸)
    mass_B0Ks.setConstant(kTRUE);
    RooFormulaVar x_shifted("x_shifted", "mass_B0Ks+Bkg_a1-x", RooArgSet(mass_B0Ks, Bkg_a1, x));
    RooRealVar Bkg_a2("Bkg_a2", "background a2", 0.25, 0, 10);
    //RooAbsPdf  *BkgPdf  = new RooChebychev("BkgPdf","background", x,RooArgList(Bkg_a1,Bkg_a2));
    RooAbsPdf  *BkgPdf  = new RooArgusBG("BkgPdf","background", x_shifted, Bkg_a1, Bkg_a2);

    RooRealVar Bkg_a3("Bkg_a3", "background a3", 0.298217, 0.15, 10);//Bkg_a1最小值小于x_max - mass_B0Ks时会报错(积分会炸)
    RooFormulaVar x_shifted2("x_shifted2", "mass_B0Ks+Bkg_a3-x", RooArgSet(mass_B0Ks, Bkg_a3, x));
    RooRealVar Bkg_a4("Bkg_a4", "background a4", 0.25, 0, 10);
    //RooAbsPdf  *BkgPdf  = new RooChebychev("BkgPdf","background", x,RooArgList(Bkg_a1,Bkg_a2));
    RooAbsPdf  *BkgPdf2  = new RooArgusBG("BkgPdf2","backgroun2d", x_shifted2, Bkg_a3, Bkg_a4);

    RooRealVar *nsig1 = new RooRealVar("N_{sig1}","nsig1",12,0,100);
    RooRealVar *nsig2 = new RooRealVar("N_{sig2}","nsig2",5,0,100);
    RooRealVar *nsig3 = new RooRealVar("N_{sig3}","nsig3",86,0,200);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",1200,0,6000);


    mean1.setConstant(kTRUE);
    mean2.setConstant(kTRUE);
    mean3.setConstant(kTRUE);

    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf1,*SigPdf2,*SigPdf3,*BkgPdf),RooArgList(*nsig1,*nsig2,*nsig3,*nbkgd));
    
    //RooDataSet* toyMC_data = pdf->generate(x,10000) ; 
    RooDataSet *data = RooDataSet::read("data/B0Ksmass.txt",RooArgSet(x),"Q");
    RooDataSet *data2 = RooDataSet::read("data/1_100_1_mix.txt",RooArgSet(x),"Q");


    RooPlot* frame = x.frame(Title("B0Ks_data"));
    //RooPlot* frame2 = x.frame(Title("event_mixing"));

    //data->plotOn(frame, MarkerStyle(20));
    data->plotOn(frame, MarkerStyle(20), Rescale(4038/1339));
    
    
    pdf->fitTo(*data, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf2->fitTo(*data2, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    

    data2->plotOn(frame, MarkerStyle(4), LineColor(12), MarkerColor(12));
    BkgPdf2->plotOn(frame, LineColor(12));
    pdf->plotOn(frame);
    pdf->plotOn(frame, Components("BkgPdf"), LineStyle(kDashed));
    pdf->plotOn(frame, Components("SigPdf1,SigPdf2,SigPdf3"), LineColor(kRed));
    //c1->cd(1);
    frame->Draw();
    //c1->cd(2);
    //frame2->Draw();
    c1->SaveAs("resultpics/roofit.png");
    out->Write();

    cout<<"peak1: "<<mean1.getVal()<<" / "<<sigma1.getVal()<<" / "<<nsig1->getVal()<<endl;
    cout<<"peak2: "<<mean2.getVal()<<" / "<<sigma2.getVal()<<" / "<<nsig2->getVal()<<endl;
    cout<<"peak3: "<<mean3.getVal()<<" / "<<sigma3.getVal()<<" / "<<nsig3->getVal()<<endl;
    cout<<"Bkg_par: "<<Bkg_a1.getVal()<<" / "<<Bkg_a2.getVal()<<" / "<<nbkgd->getVal()<<endl;
    cout<<"mixBkg_par: "<<Bkg_a3.getVal()<<" / "<<Bkg_a4.getVal()<<" / "<<endl;

}