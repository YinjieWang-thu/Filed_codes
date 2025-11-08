#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;


void sb_fit()
{
    bool IsSplitLR = 0;

    TFile *out = new TFile("fit.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1",1500,600);

    if(IsSplitLR) c1->Divide(2,1);

    RooRealVar x("x","x",5.75,5.9);
    RooRealVar Ks("Ks","Ks",0.5,1.3);// stands for Kstar

    RooRealVar mean3("mean3","mean3",5.839751,5.83,5.85);
    mean3.setConstant(kTRUE);
    RooRealVar sigma3("sigma3","sigma3",0.005,0.001,0.04);
    RooAbsPdf * SigPdf3=new RooGaussian("SigPdf3","SigPdf3",x,mean3,sigma3);

    RooRealVar mass_B0Ks("mass_B0Ks", "mass_B0Ks", 5.7773, 5.77, 5.78);
    RooRealVar Bkg_a1("Bkg_a1", "background a1", 0.3, 0.15, 1);
    mass_B0Ks.setConstant(kTRUE);
    RooFormulaVar x_shifted("x_shifted", "mass_B0Ks+Bkg_a1-x", RooArgSet(mass_B0Ks, Bkg_a1, x));
    RooRealVar Bkg_a2("Bkg_a2", "background a2", 1, 0, 10);
    RooAbsPdf  *BkgPdf  = new RooArgusBG("BkgPdf","background", x_shifted, Bkg_a1, Bkg_a2);

    RooRealVar *nsig3 = new RooRealVar("N_{sig3}","nsig3",50,0,2000);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",1200,0,6000);


    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf3,*BkgPdf),RooArgList(*nsig3,*nbkgd));
    
    //RooDataSet* toyMC_data = pdf->generate(x,10000) ; 
    RooDataSet *data = RooDataSet::read("data/tqKs_noKsw.txt",RooArgSet(x, Ks),"Q");
    
    //1
    Ks.setRange("left",0.6,0.795);
    Ks.setRange("right",0.98,1.05);
    //3(ss)
    //Ks.setRange("left",0.6,0.82);
    //Ks.setRange("right",0.98,1.05);

    RooDataSet *data1 =(RooDataSet*) data->reduce(CutRange("left"));
    RooDataSet *data2 =(RooDataSet*) data->reduce(CutRange("right"));
    cout<<"left events:"<<data1->sumEntries()<<endl;
    cout<<"right events:"<<data2->sumEntries()<<endl;
    if(!IsSplitLR) data1->append(*data2);

    
    RooPlot* frame1 = x.frame(Title("B0Ks:Kstar_sideband"));
    RooPlot* frame2 = x.frame(Title("B0Ks:Kstar_Rsideband"));

    

    if(IsSplitLR)  c1->cd(1);
    data1->plotOn(frame1);
    pdf->fitTo(*data1, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    pdf->plotOn(frame1, Components("SigPdf3"), LineColor(kRed));
    pdf->plotOn(frame1);
    pdf->plotOn(frame1, Components("BkgPdf"), LineStyle(kDashed));
    frame1->Draw();
    if(!IsSplitLR) cout<<"total events:"<<data1->sumEntries()<<endl;
    cout<<"peak3: "<<mean3.getVal()<<" / "<<sigma3.getVal()<<" / "<<nsig3->getVal()<<endl;
    cout<<"Bkg_par: "<<Bkg_a1.getVal()<<" / "<<Bkg_a2.getVal()<<" / "<<nbkgd->getVal()<<endl;

    if(IsSplitLR) 
    {
        c1->cd(2);
        data2->plotOn(frame2);
        pdf->fitTo(*data2, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
        pdf->plotOn(frame2, Components("SigPdf3"), LineColor(kRed));
        pdf->plotOn(frame2);
        pdf->plotOn(frame2, Components("BkgPdf"), LineStyle(kDashed));
        frame2->Draw();
        cout<<"left events:"<<data1->sumEntries()<<endl;
        cout<<"right events:"<<data2->sumEntries()<<endl;
        cout<<"peak3: "<<mean3.getVal()<<" / "<<sigma3.getVal()<<" / "<<nsig3->getVal()<<endl;
        cout<<"Bkg_par: "<<Bkg_a1.getVal()<<" / "<<Bkg_a2.getVal()<<" / "<<nbkgd->getVal()<<endl;
    }
    c1->SaveAs("resultpics/sb_fit.png");
    out->Write();
}