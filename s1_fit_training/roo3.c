#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;

void roo3()
{
    TFile *out = new TFile("RooFitUnBinnedFit100.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1"); 
    RooFitResult *fitRes;
    TH1F* h2=new TH1F("h2","RooFit_UnbinnedFit",100,-5,5);
    TH1F* h3=new TH1F("h3","Histogram 3",100,-5,5);
    TRandom3 r;
    
    RooRealVar x("x","x",-5,5);
    RooRealVar mean("mean","mean",0,-1,1);
    RooRealVar sigma("sigma","sigma",1,0.001,5);
    RooAbsPdf * SigPdf=new RooGaussian("MeanPdf","MeanPdf",x,mean,sigma);

    RooRealVar *Bkg_a1  = new RooRealVar("bkg_{a1}", "background a1", 0, -1, 1);
    RooRealVar *Bkg_a2  = new RooRealVar("bkg_{a2}", "background a2", 0, -1, 1);
    RooAbsPdf  *BkgPdf  = new RooChebychev("BkgPdf","background", x, RooArgList(*Bkg_a1,*Bkg_a2));

    RooRealVar *nsig = new RooRealVar("N_{sig}","nsig",10,0,100000);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",10,0,100000);
    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf,*BkgPdf),RooArgList(*nsig,*nbkgd));

    for(int i=1;i<=1000;i++)
    {
        TTree* tree=new TTree("Histdata","Histdata");
        Double_t xdata;
        tree->Branch("x",&xdata,"x/D");
        for(double a=-4.98;a<=5.02;a+=0.02)
        {
            for(int j=1;j<=-0.05*(a+5)*(a-30)+2;++j)
            {
                xdata=a;
                tree->Fill();
            }
        }
        for(int k=1;k<=100000;++k) {xdata=r.Gaus(0,1);
        tree->Fill();}
        RooDataSet data("data","data",RooArgSet(x),Import(*tree));
        
       // RooPlot* frame = x.frame(Title("Fit hsum in RooFit"));
        //data.plotOn(frame);

        pdf->fitTo(data,Save(kTRUE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));
       // pdf->plotOn(frame);
        //frame->Draw();
        h2->Fill(mean.getVal()/mean.getError());
        h3->Fill((sigma.getVal()-1)/sigma.getError());
        tree->~TTree();
    }
    h2->SetLineColor(kRed);
    h3->SetLineColor(kBlue);
    h2->Draw();
    h2->Fit("gaus");
    TF1*f2=h2->GetFunction("gaus");
    f2->Draw("same");
    h3->Draw("same");
    h3->Fit("gaus");
    TF1*f3=h3->GetFunction("gaus");
    f3->SetLineColor(kBlue);
    f3->Draw("same");
    c1->SaveAs("RooFitUnbinnedFit.png");
    cout<<"mean of Mean Dist. is "<<(f2->GetParameter(1))<<" sigma is "<<(f2->GetParameter(2))<<endl;
    cout<<"mean of sigma Dist. is "<<(f3->GetParameter(1))<<" sigma is "<<(f3->GetParameter(2))<<endl;
    out->Write();
}
//0.327089 sigma is 0.762565