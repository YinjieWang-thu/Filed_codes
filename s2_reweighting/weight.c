#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;

#define BIN 50

int GetBinnumber(double x, int bin, double lmin, double lmax)
{
    return (int)((x-lmin)/(lmax-lmin)*bin);
}

void DrawHist(TCanvas* c1, RooDataSet* os_data, RooDataSet* ss_data)
{
    
    c1->Divide(3,1);
    //Creating histograms with dataset(with weight) and legend
    gStyle->SetOptStat(kFALSE);
    const char* oslabel = "os data";
    const char* sslabel = "ss weighted";
    double lx1 = 0.58;
    double ly1 = 0.8;
    double lx2 = 0.89;
    double ly2 = 0.89;
    RooArgSet* obs = (RooArgSet*)ss_data->get();

    RooRealVar* K_pt = (RooRealVar*)obs->find("K_pt");
    TH1* K_pt_hist_os = os_data->createHistogram("__oshist",*K_pt,Binning(BIN, 0, 20));
    TH1* K_pt_hist_ss = ss_data->createHistogram("__sshist",*K_pt,Binning(BIN, 0, 20));
    double scale = K_pt_hist_os->Integral()/K_pt_hist_ss->Integral();
    K_pt_hist_ss->Scale(scale);
    TLegend *leg1 = new TLegend(lx1, ly1, lx2, ly2);
    leg1->SetBorderSize(1);
    leg1->SetTextSize(0.04);
    c1->cd(3);
    K_pt_hist_ss->SetLineColor(kBlue);
    K_pt_hist_ss->SetTitle("p_{T}^{K} distribution");
    K_pt_hist_ss->Draw("HIST"); 
    K_pt_hist_os->SetLineWidth(2);
    K_pt_hist_os->SetLineColor(kRed);
    K_pt_hist_os->Draw("HIST SAME");
    K_pt_hist_ss->Draw("HIST SAME");
    leg1->AddEntry(K_pt_hist_os,oslabel,"l");
    leg1->AddEntry(K_pt_hist_ss,sslabel,"l");
    leg1->Draw();

    RooRealVar* pi_pt = (RooRealVar*)obs->find("pi_pt");
    TH1* pi_pt_hist_os = os_data->createHistogram("__oshist",*pi_pt,Binning(BIN, 0, 20));
    TH1* pi_pt_hist_ss = ss_data->createHistogram("__sshist",*pi_pt,Binning(BIN, 0, 20));
    scale = pi_pt_hist_os->Integral()/pi_pt_hist_ss->Integral();
    pi_pt_hist_ss->Scale(scale);
    TLegend *leg2 = new TLegend(lx1, ly1, lx2, ly2);
    leg2->SetBorderSize(1);
    leg2->SetTextSize(0.04);
    c1->cd(2);
    pi_pt_hist_ss->SetLineColor(kBlue);
    pi_pt_hist_ss->SetTitle("p_{T}^{#pi} distribution");
    pi_pt_hist_ss->Draw("HIST"); 
    pi_pt_hist_os->SetLineWidth(2);
    pi_pt_hist_os->SetLineColor(kRed);
    pi_pt_hist_os->Draw("HIST SAME");
    pi_pt_hist_ss->Draw("HIST SAME");
    leg2->AddEntry(pi_pt_hist_os,oslabel,"l");
    leg2->AddEntry(pi_pt_hist_ss,sslabel,"l");
    leg2->Draw();

    RooRealVar* DR = (RooRealVar*)obs->find("DR");
    TH1* DR_hist_os = os_data->createHistogram("__oshist",*DR,Binning(BIN, 0, 2));
    TH1* DR_hist_ss = ss_data->createHistogram("__sshist",*DR,Binning(BIN, 0, 2));
    scale = DR_hist_os->Integral()/DR_hist_ss->Integral();
    DR_hist_ss->Scale(scale);
    TLegend *leg3 = new TLegend(lx1, ly1, lx2, ly2);
    leg3->SetBorderSize(1);
    leg3->SetTextSize(0.04);
    c1->cd(1);
    DR_hist_ss->SetLineColor(kBlue);
    DR_hist_os->SetTitle("#DeltaR distribution");
    DR_hist_os->SetLineWidth(2);
    DR_hist_os->SetLineColor(kRed);
    DR_hist_os->Draw("HIST");
    DR_hist_ss->Draw("HIST SAME"); 
    leg3->AddEntry(DR_hist_os,oslabel,"l");
    leg3->AddEntry(DR_hist_ss,sslabel,"l");
    leg3->Draw();

}

void DrawHistKs(TCanvas* c1, RooDataSet* os_data, RooDataSet* ss_data)
{
    
    //Creating histograms with dataset(with weight) and legend
    gStyle->SetOptStat(kFALSE);
    const char* oslabel = "os data";
    const char* sslabel = "ss weighted";
    double lx1 = 0.58;
    double ly1 = 0.8;
    double lx2 = 0.89;
    double ly2 = 0.89;
    RooArgSet* obs = (RooArgSet*)ss_data->get();

    RooRealVar* Kst_m = (RooRealVar*)obs->find("Kst_mass");
    TH1* K_st_hist_os = os_data->createHistogram("_oshist",*Kst_m,Binning(BIN, 0, 3));
    TH1* K_st_hist_ss = ss_data->createHistogram("_sshist",*Kst_m,Binning(BIN, 0, 3));
    double scale = K_st_hist_os->Integral()/K_st_hist_ss->Integral();
    K_st_hist_ss->Scale(scale);
    TLegend *leg1 = new TLegend(lx1, ly1, lx2, ly2);
    leg1->SetBorderSize(1);
    leg1->SetTextSize(0.04);
    c1->cd(3);
    K_st_hist_ss->SetLineColor(kBlue);
    K_st_hist_ss->SetTitle("p_{T}^{K} distribution");
    K_st_hist_ss->Draw("HIST"); 
    K_st_hist_os->SetLineWidth(2);
    K_st_hist_os->SetLineColor(kRed);
    K_st_hist_os->Draw("HIST SAME");
    K_st_hist_ss->Draw("HIST SAME");
    leg1->AddEntry(K_st_hist_os,oslabel,"l");
    leg1->AddEntry(K_st_hist_ss,sslabel,"l");
    leg1->Draw();

}

RooDataSet* AddWeight(RooDataSet* os_data, RooDataSet* ss_data, const char* VarName, int bin, double lmin, double lmax)
{

    vector<double> w1;
    RooArgSet* obs = (RooArgSet*)ss_data->get();

    RooRealVar* Var = (RooRealVar*)obs->find(VarName);
    if(!Var) cout<<"Wrong weight var name:"<<VarName<<endl,exit(0);
    TH1* hist_os = os_data->createHistogram("oshist",*Var,Binning(bin, lmin, lmax));
    TH1* hist_ss = ss_data->createHistogram("sshist",*Var,Binning(bin, lmin, lmax));
    double scale = hist_os->Integral()/hist_ss->Integral();
    hist_ss->Scale(scale);

    for(int j=1; j<=BIN; ++j)
    {
        if(hist_ss->GetBinContent(j)==0)
        {
            w1.push_back(1);
        }
        else
        {
            w1.push_back(hist_os->GetBinContent(j)/hist_ss->GetBinContent(j));
        }
    }

    RooDataSet* weighted_ss_data = new RooDataSet(
        ss_data->GetName(),
        ss_data->GetTitle(),
        *obs,
        RooFit::WeightVar() 
    );

    for (int i=0; i < ss_data->numEntries(); ++i) {
        const RooArgSet* eventVars = ss_data->get(i);
        double currentWeight = ss_data->weight(); 
        double newWeight;
        if(Var->getVal()>lmax || Var->getVal()<lmin){
            newWeight = currentWeight;
        }
        else{
            int nbin = GetBinnumber(Var->getVal(), bin, lmin, lmax);
            newWeight = currentWeight * w1[nbin];
        }

        weighted_ss_data->add(*eventVars, newWeight);
    }

    return weighted_ss_data;
}

void weight()
{
    //Output files
    TFile *out = new TFile("fit.root", "RECREATE");
    TCanvas *c2 = new TCanvas("c2","c2",2200,700);
    
    c2->Divide(2,1);
    //Variables from txt files
    RooRealVar tq_mass("tq_mass","tq_mass",5,6);
    RooRealVar Kst_mass("Kst_mass","Kst_mass",0.6,2.2);
    RooRealVar K_pt("K_pt","K_pt",0,200);
    RooRealVar pi_pt("pi_pt","pi_pt",0,200);
    RooRealVar DR("DR","Delta R",0,15);
    RooRealVar w("w","w",-10,10);

    //Read data and write to RooFit dataset
    RooDataSet *os_data = RooDataSet::read("output/os_nnn.txt",RooArgSet(tq_mass,Kst_mass,K_pt,pi_pt,DR),"Q");
    RooDataSet *ss_data = RooDataSet::read("output/ss_norf.txt",RooArgSet(tq_mass,Kst_mass,K_pt,pi_pt,DR),"Q");

    //first fit and plot
    tq_mass.setRange("_fit",5.75,6);
    Kst_mass.setRange("fit",0.68,1.08);
    RooDataSet *_os_fit =(RooDataSet*) os_data->reduce(CutRange("_fit"));
    RooDataSet *_ss_fit =(RooDataSet*) ss_data->reduce(CutRange("_fit"));
    RooDataSet *os_fit =(RooDataSet*) _os_fit->reduce(CutRange("fit"));
    RooDataSet *ss_fit =(RooDataSet*) _ss_fit->reduce(CutRange("fit"));
    
    Kst_mass.setRange(0.68,1.08);
    RooRealVar mean("mean","mean",0.892,-1,1);
    mean.setConstant(kTRUE);
    RooRealVar width("width","width",1,0.00001,1);
    RooRealVar sigma("sigma","sigma",1,0.00001,1);
    RooAbsPdf * SigPdf=new RooVoigtian("MeanPdf","MeanPdf",Kst_mass,mean,width,sigma);

    RooRealVar *Bkg_a1  = new RooRealVar("bkg_{a1}", "background a1", 0, -1, 1);
    RooRealVar *Bkg_a2  = new RooRealVar("bkg_{a2}", "background a2", 0, -1, 1);
    RooAbsPdf  *BkgPdf  = new RooChebychev("BkgPdf","background", Kst_mass, RooArgList(*Bkg_a1,*Bkg_a2));

    RooRealVar *nsig = new RooRealVar("N_{sig}","nsig",800,0,3000);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",6000,1000,8000);
    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf,*BkgPdf),RooArgList(*nsig,*nbkgd));

    RooPlot* frame1 = Kst_mass.frame(Title("m_{K*}, ss data"));
    RooPlot* frame2 = Kst_mass.frame(Title("m_{K*}, ss weighted"));
    
    pdf->fitTo(*os_fit,Range(0.68,1.08),Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    double sf1 = os_fit->sumEntries()/ss_fit->sumEntries();
    ss_fit->plotOn(frame1,Binning(50),Name("ss_fit_1"));
    pdf->plotOn(frame1, LineStyle(kDashed),Name("os_data_1"));
    pdf->plotOn(frame1, Components("BkgPdf"),Name("os_bkg_1"));
    c2->cd(1);
    frame1->Draw();

    TLegend *legf1 = new TLegend(0.11, 0.75, 0.47, 0.89);
    legf1->SetBorderSize(1);
    legf1->SetTextSize(0.03);
    TGraph* os_data_1 = (TGraph*)frame1->findObject("os_data_1");
    if (os_data_1) {
        legf1->AddEntry(os_data_1, "Total fit of os data", "l");
    }
    TGraph* os_bkg_1 = (TGraph*)frame1->findObject("os_bkg_1");
    if (os_bkg_1) {
        legf1->AddEntry(os_bkg_1, "Background fit of os data", "l");
    }
    TGraph* ss_fit_1 = (TGraph*)frame1->findObject("ss_fit_1");
    if (ss_fit_1) {
        legf1->AddEntry(ss_fit_1, "Unweighted ss data", "pe");
    }
    legf1->Draw("SAME");
    
    ss_data = AddWeight(os_data, ss_data, "DR", BIN, 0, 2);
    ss_data = AddWeight(os_data, ss_data, "pi_pt", BIN, 0, 20);
    ss_data = AddWeight(os_data, ss_data, "K_pt", BIN, 0, 20);

    ss_data = AddWeight(os_data, ss_data, "DR", BIN, 0, 2);
    ss_data = AddWeight(os_data, ss_data, "pi_pt", BIN, 0, 20);
    ss_data = AddWeight(os_data, ss_data, "K_pt", BIN, 0, 20);

    ss_data = AddWeight(os_data, ss_data, "DR", BIN, 0, 2);
    ss_data = AddWeight(os_data, ss_data, "pi_pt", BIN, 0, 20);
    ss_data = AddWeight(os_data, ss_data, "K_pt", BIN, 0, 20);

    
    RooDataSet *_ss_rw =(RooDataSet*) ss_data->reduce(CutRange("_fit"));
    RooDataSet *ss_rw =(RooDataSet*) _ss_rw->reduce(CutRange("fit"));
    double sf2 = nbkgd->getVal()/ss_rw->sumEntries();
    ss_rw->plotOn(frame2,Binning(50),Name("ss_fit_2"));//,Normalization(sf2)
    pdf->plotOn(frame2, LineStyle(kDashed),Name("os_data_2"));
    pdf->plotOn(frame2, Components("BkgPdf"),Name("os_bkg_2"));
    c2->cd(2);
    frame2->Draw();

    TLegend *legf2 = new TLegend(0.11, 0.75, 0.47, 0.89);
    legf2->SetBorderSize(1);
    legf2->SetTextSize(0.03);
    TGraph* os_data_2 = (TGraph*)frame2->findObject("os_data_2");
    if (os_data_2) {
        legf2->AddEntry(os_data_2, "Total fit of os data", "l");
    }
    TGraph* os_bkg_2 = (TGraph*)frame2->findObject("os_bkg_2");
    if (os_bkg_2) {
        legf2->AddEntry(os_bkg_2, "Background fit of os data", "l");
    }
    TGraph* ss_fit_2 = (TGraph*)frame2->findObject("ss_fit_2");
    if (ss_fit_2) {
        legf2->AddEntry(ss_fit_2, "Weighted ss data", "pe");
    }
    legf2->Draw("SAME");
    c2->SaveAs("reweight/rwfit_9.png");
    
    TCanvas *c1 = new TCanvas("c1","c1",800,600);//2400
    DrawHistKs(c1,os_data,ss_data);
    c1->SaveAs("reweight/t1.png");

    
    out->Write();
}