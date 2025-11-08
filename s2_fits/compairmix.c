#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;


void compairmix()
{
    //一个无情的输出文件
    TFile *out = new TFile("fit.root", "RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1",1000,700);

    //坐标轴，包括了B0Ks和sideband的K*横坐标
    RooRealVar x("x","x",5.75,5.9);
    RooRealVar Ks("Ks","Ks",0.5,1.3);// stands for Kstar
    
    //第一个信号
    RooRealVar mean1("mean1","mean1",5.782981,5.78,5.79);
    RooRealVar sigma1("sigma1","sigma1",0.002,0.0001,0.01);
    RooAbsPdf * SigPdf1=new RooGaussian("SigPdf1","SigPdf1",x,mean1,sigma1);

    //第二个信号
    RooRealVar mean2("mean2","mean2",5.794571,5.79,5.797);
    RooRealVar sigma2("sigma2","sigma2",0.002,0.0001,0.01);
    RooAbsPdf * SigPdf2=new RooGaussian("SigPdf2","SigPdf2",x,mean2,sigma2);

    //第三个信号
    RooRealVar mean3("mean3","mean3",5.839751,5.83,5.85);
    RooRealVar sigma3("sigma3","sigma3",0.002,0.0001,0.01);
    RooAbsPdf * SigPdf3=new RooGaussian("SigPdf3","SigPdf3",x,mean3,sigma3);

    //信号的本底
    RooRealVar mass_B0Ks("mass_B0Ks", "mass_B0Ks", 5.7773, 5.77, 5.78);
    RooRealVar Bkg_a1("Bkg_a1", "background a1", 0.298217, 0.15, 10);
    mass_B0Ks.setConstant(kTRUE);
    RooFormulaVar x_shifted("x_shifted", "mass_B0Ks+Bkg_a1-x", RooArgSet(mass_B0Ks, Bkg_a1, x));
    RooRealVar Bkg_a2("Bkg_a2", "background a2", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf  = new RooArgusBG("BkgPdf","background", x_shifted, Bkg_a1, Bkg_a2);
    
    //利用mixing得到的本底

    RooRealVar Bkg_a3("Bkg_a3", "background a3", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted2("x_shifted2", "mass_B0Ks+Bkg_a3-x", RooArgSet(mass_B0Ks, Bkg_a3, x));
    RooRealVar Bkg_a4("Bkg_a4", "background a4", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf2  = new RooArgusBG("BkgPdf2","backgroun2d", x_shifted2, Bkg_a3, Bkg_a4);

    //利用mixing得到的本底
    RooRealVar Bkg_a5("Bkg_a5", "background a5", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted3("x_shifted3", "mass_B0Ks+Bkg_a5-x", RooArgSet(mass_B0Ks, Bkg_a5, x));
    RooRealVar Bkg_a6("Bkg_a6", "background a6", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf3  = new RooArgusBG("BkgPdf3","backgroun3d", x_shifted3, Bkg_a5, Bkg_a6);

    //利用mixing得到的本底
    RooRealVar Bkg_a7("Bkg_a7", "background a7", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted4("x_shifted4", "mass_B0Ks+Bkg_a7-x", RooArgSet(mass_B0Ks, Bkg_a7, x));
    RooRealVar Bkg_a8("Bkg_a4", "background a8", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf4  = new RooArgusBG("BkgPdf4","backgroun4d", x_shifted4, Bkg_a7, Bkg_a8);

    //利用mixing得到的本底
    RooRealVar Bkg_a9("Bkg_a9", "background a9", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted5("x_shifted5", "mass_B0Ks+Bkg_a9-x", RooArgSet(mass_B0Ks, Bkg_a9, x));
    RooRealVar Bkg_a10("Bkg_a10", "background a10", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf5  = new RooArgusBG("BkgPdf5","backgroun5d", x_shifted5, Bkg_a9, Bkg_a10);

    //利用mixing得到的本底
    RooRealVar Bkg_a11("Bkg_a11", "background a11", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted6("x_shifted6", "mass_B0Ks+Bkg_a11-x", RooArgSet(mass_B0Ks, Bkg_a11, x));
    RooRealVar Bkg_a12("Bkg_a12", "background a12", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf6 = new RooArgusBG("BkgPdf6","backgroun6d", x_shifted6, Bkg_a11, Bkg_a12);

    //利用mixing得到的本底
    RooRealVar Bkg_a13("Bkg_a13", "background a13", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted7("x_shifted7", "mass_B0Ks+Bkg_a13-x", RooArgSet(mass_B0Ks, Bkg_a13, x));
    RooRealVar Bkg_a14("Bkg_a14", "background a14", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf7  = new RooArgusBG("BkgPdf7","backgroun7d", x_shifted7, Bkg_a13, Bkg_a14);

    //利用mixing得到的本底
    RooRealVar Bkg_a15("Bkg_a15", "background a15", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted8("x_shifted8", "mass_B0Ks+Bkg_a15-x", RooArgSet(mass_B0Ks, Bkg_a15, x));
    RooRealVar Bkg_a16("Bkg_a16", "background a16", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf8  = new RooArgusBG("BkgPdf8","backgroun8d", x_shifted8, Bkg_a15, Bkg_a16);

    
    //拟合事例的系数
    RooRealVar *nsig1 = new RooRealVar("N_{sig1}","nsig1",12,0,100);
    RooRealVar *nsig2 = new RooRealVar("N_{sig2}","nsig2",5,0,100);
    RooRealVar *nsig3 = new RooRealVar("N_{sig3}","nsig3",86,0,200);
    RooRealVar *nbkgd = new RooRealVar("N_{bkg}","nbkgd",1200,0,6000);

    //拟合选项：固定信号的中心
    mean1.setConstant(kTRUE);
    mean2.setConstant(kTRUE);
    mean3.setConstant(kTRUE);

    //定义信号pdf
    RooAbsPdf  *pdf   = new RooAddPdf("pdf","total signal+background pdf",RooArgList(*SigPdf1,*SigPdf2,*SigPdf3,*BkgPdf),RooArgList(*nsig1,*nsig2,*nsig3,*nbkgd));
    
    //读数据
    RooDataSet *data = RooDataSet::read("data/B0Ksmass.txt",RooArgSet(x),"Q");//事例的数据集
    RooDataSet *data1 = RooDataSet::read("data/1_100_1_mix.txt",RooArgSet(x),"Q");//mixing cut过的事例集
    RooDataSet *data2 = RooDataSet::read("data/mix_lim65.txt",RooArgSet(x),"Q");
    RooDataSet *data3 = RooDataSet::read("data/mix_lim7.txt",RooArgSet(x),"Q");
    RooDataSet *data4 = RooDataSet::read("data/mix_lim75.txt",RooArgSet(x),"Q");
    RooDataSet *data5 = RooDataSet::read("data/mix_lim8.txt",RooArgSet(x),"Q");
    RooDataSet *data6 = RooDataSet::read("data/mix_lim85.txt",RooArgSet(x),"Q");
    RooDataSet *data7 = RooDataSet::read("data/1_100_1_mix9.txt",RooArgSet(x),"Q");

    //定义横坐标
    RooPlot* frame = x.frame(Title("m_{B0Ks}"));

    //画信号
    
    //data->plotOn(frame, MarkerStyle(20), Name("data"));
    pdf->fitTo(*data, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    pdf->plotOn(frame, LineColor(1), Normalization(1), Name("datafit"));
    pdf->plotOn(frame, LineColor(1), Normalization(1), Components("BkgPdf"), LineStyle(kDashed), LineWidth(2), Name("bkgfit"));
    //pdf->plotOn(frame, Components("SigPdf1,SigPdf2,SigPdf3"), LineColor(kRed), LineWidth(1), Name("sigfit"));*/

    //画mixing
    //double sf1 = data->sumEntries()/data2->sumEntries();//scale factor
    double sf1 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
    //data2->plotOn(frame, MarkerStyle(4), LineColor(41), MarkerColor(41), Rescale(sf1), Name("data1"));
    BkgPdf2->fitTo(*data1, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf2->plotOn(frame, LineColor(kRed),Normalization(sf1), LineWidth(2), Name("mixfit1"));

    double sf2 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
    //data2->plotOn(frame, MarkerStyle(4), LineColor(42), MarkerColor(42), Rescale(sf2), Name("data2"));
    BkgPdf3->fitTo(*data2, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf3->plotOn(frame, LineColor(kOrange),Normalization(sf2), LineWidth(2), Name("mixfit2"));

    double sf3 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
    //data2->plotOn(frame, MarkerStyle(4), LineColor(43), MarkerColor(43), Rescale(sf3), Name("data3"));
    BkgPdf4->fitTo(*data3, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf4->plotOn(frame, LineColor(kYellow),Normalization(sf3), LineWidth(2), Name("mixfit3"));

    double sf4 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
    //data2->plotOn(frame, MarkerStyle(4), LineColor(44), MarkerColor(44), Rescale(sf4), Name("data4"));
    BkgPdf5->fitTo(*data4, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf5->plotOn(frame, LineColor(kGreen),Normalization(sf4), LineWidth(2), Name("mixfit4"));

    double sf5 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
    //data2->plotOn(frame, MarkerStyle(4), LineColor(45), MarkerColor(45), Rescale(sf5), Name("data5"));
    BkgPdf6->fitTo(*data5, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf6->plotOn(frame, LineColor(kCyan),Normalization(sf5), LineWidth(2), Name("mixfit5"));

    double sf6 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
   // data2->plotOn(frame, MarkerStyle(4), LineColor(46), MarkerColor(46), Rescale(sf6), Name("data6"));
    BkgPdf7->fitTo(*data6, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf7->plotOn(frame, LineColor(kBlue),Normalization(sf6), LineWidth(2), Name("mixfit6"));

    double sf7 = nbkgd->getVal()/data->sumEntries();//nbkgd->getVal()/data2->sumEntries();
    //data2->plotOn(frame, MarkerStyle(4), LineColor(47), MarkerColor(47), Rescale(sf7), Name("data7"));
    BkgPdf8->fitTo(*data7, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf8->plotOn(frame, LineColor(kViolet),Normalization(sf7), LineWidth(2), Name("mixfit7"));
    


    //画
    frame->Draw();

    //图例
    
    TLegend *leg = new TLegend(0.11, 0.5, 0.4, 0.89);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);
    
    
    TGraph* datafit = (TGraph*)frame->findObject("datafit");
    if (datafit) {
        datafit->SetMarkerSize(1.3);
        leg->AddEntry(datafit, " Fit of data", "l");
    }
    TGraph* bkgfit = (TGraph*)frame->findObject("bkgfit");
    if (bkgfit) {
        bkgfit->SetMarkerSize(1.3);
        leg->AddEntry(bkgfit, " Background of data fit", "l");
    }
    TGraph* mixfit1 = (TGraph*)frame->findObject("mixfit1");
    if (mixfit1) {
        mixfit1->SetMarkerSize(1.3);
        leg->AddEntry(mixfit1, "mixing mass_max=6", "l");
    }
    TGraph* mixfit2 = (TGraph*)frame->findObject("mixfit2");
    if (mixfit2) {
        mixfit2->SetMarkerSize(1.3);
        leg->AddEntry(mixfit2, "mixing mass_max=6.5", "l");
    }
    TGraph* mixfit3 = (TGraph*)frame->findObject("mixfit3");
    if (mixfit3) {
        mixfit3->SetMarkerSize(1.3);
        leg->AddEntry(mixfit3, "mixing mass_max=7", "l");
    }
    TGraph* mixfit4 = (TGraph*)frame->findObject("mixfit4");
    if (mixfit4) {
        mixfit4->SetMarkerSize(1.3);
        leg->AddEntry(mixfit4, "mixing mass_max=7.5", "l");
    }
    TGraph* mixfit5 = (TGraph*)frame->findObject("mixfit5");
    if (mixfit5) {
        mixfit5->SetMarkerSize(1.3);
        leg->AddEntry(mixfit5, "mixing mass_max=8", "l");
    }
    TGraph* mixfit6 = (TGraph*)frame->findObject("mixfit6");
    if (mixfit6) {
        mixfit6->SetMarkerSize(1.3);
        leg->AddEntry(mixfit6, "mixing mass_max=8.5", "l");
    }
    TGraph* mixfit7 = (TGraph*)frame->findObject("mixfit7");
    if (mixfit7) {
        mixfit7->SetMarkerSize(1.3);
        leg->AddEntry(mixfit7, "mixing mass_max=9", "l");
    }
        
    leg->Draw("same");
    c1->Update();
    c1->SaveAs("resultpics/mixcom.png");
    out->Write();



}