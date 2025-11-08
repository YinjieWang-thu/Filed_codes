#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;

void roo()
{
    //TFile *out = new TFile("ROOTFitbinned0.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1"); 
    TRandom3 r;
    TH1F* h2=new TH1F("h2","Histogram 2",100,-5,5);
    TH1F* h3=new TH1F("h3","Histogram 3",100,-5,5);
    for(int i=1;i<=1000;i++)
    {
        TH1F* h1=new TH1F("h1","Histogram 1",100,-5,5);
        for(double x=-4.98;x<=5;x+=0.02)
        {
            for(int j=1;j<=x*x;++j)
            {
                h1->Fill(x);
            }
        }
        h1->Fill(r.Gaus(0,1));
        h1->Fit("gaus");
        TF1 *f1 = h1->GetFunction("gaus");
        h2->Fill(f1->GetParameter(1));
        h3->Fill((f1->GetParameter(2)-1));
        cout<<(f1->GetParameter(2))<<endl;
        h1->Scale(0);
    }
    h2->SetLineColor(kRed);
    h3->SetLineColor(kBlue);
    h2->Draw();
    h3->Draw("same");
    h2->Fit("gaus");
    TF1*f2=h2->GetFunction("gaus");
    f2->Draw("same");
    c1->SaveAs("ROOTFitbinned.png");
    cout<<"mean of Mean Dist. is "<<(f2->GetParameter(1))<<" sigma is "<<(f2->GetParameter(2))<<endl;
    out->Write();
}
