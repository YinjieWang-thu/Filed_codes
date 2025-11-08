#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;


void draw()
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

    //利用sideband得到的本底
    RooRealVar Bkg_a5("Bkg_a5", "background a5", 0.298217, 0.15, 10);
    RooFormulaVar x_shifted3("x_shifted3", "mass_B0Ks+Bkg_a5-x", RooArgSet(mass_B0Ks, Bkg_a5, x));
    RooRealVar Bkg_a6("Bkg_a6", "background a6", 0.25, 0, 1);
    RooAbsPdf  *BkgPdf3  = new RooArgusBG("BkgPdf3","backgroun3d", x_shifted3, Bkg_a5, Bkg_a6);

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
    RooDataSet *data2 = RooDataSet::read("data/1_100_1_mix.txt",RooArgSet(x),"Q");//mixing cut过的事例集
    RooDataSet *data3 = RooDataSet::read("data/tqKs_noKsw.txt",RooArgSet(x, Ks),"Q");//没有K*cut的数据集

    //定义横坐标
    RooPlot* frame = x.frame(Title("m_{B0Ks}"));

    //画信号
    data->plotOn(frame, MarkerStyle(20), Name("data"));
    pdf->fitTo(*data, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    pdf->plotOn(frame, Name("datafit"));
    pdf->plotOn(frame, Components("BkgPdf"), LineStyle(kDashed), LineWidth(1), Name("bkgfit"));
    pdf->plotOn(frame, Components("SigPdf1,SigPdf2,SigPdf3"), LineColor(kRed), LineWidth(1), Name("sigfit"));

    //画mixing
    //double sf1 = data->sumEntries()/data2->sumEntries();//scale factor
    double sf1 = nbkgd->getVal()/data2->sumEntries();
    data2->plotOn(frame, MarkerStyle(4), LineColor(12), MarkerColor(12), Rescale(sf1), Name("data2"));
    BkgPdf2->fitTo(*data2, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf2->plotOn(frame, LineColor(12),Normalization(sf1), LineWidth(2), Name("mixfit"));
    
    //构建sideband数据集
    Ks.setRange("left",0.6,0.795);
    Ks.setRange("right",0.98,1.05);
    RooDataSet *data4 =(RooDataSet*) data3->reduce(CutRange("left"));
    RooDataSet *data5 =(RooDataSet*) data3->reduce(CutRange("right"));
    data4->append(*data5);

    //画sideband
    //double sf2 = data->sumEntries()/data4->sumEntries();//scale factor
    double sf2 = nbkgd->getVal()/data4->sumEntries();
    data4->plotOn(frame, MarkerStyle(26), LineColor(38), MarkerColor(38), Rescale(sf2), Name("data4"));
    BkgPdf3->fitTo(*data4, Save(kTRUE), Warnings(-1), PrintEvalErrors(-1));
    BkgPdf3->plotOn(frame, LineColor(38),Normalization(sf2), LineWidth(2), Name("sbfit"));

    //画
    frame->Draw();

    //图例
    TLegend *leg = new TLegend(0.11, 0.5, 0.4, 0.89);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);

    TGraph* dataPoints = (TGraph*)frame->findObject("data");
    if (dataPoints) {
        dataPoints->SetMarkerSize(1.3);
        leg->AddEntry(dataPoints, " Data points", "pe");
    }
    TGraph* dataPoints2 = (TGraph*)frame->findObject("data2");
    if (dataPoints2) {
        dataPoints2->SetMarkerSize(1.3);
        leg->AddEntry(dataPoints2, " Event mixing points", "pe");
    }
    TGraph* dataPoints4 = (TGraph*)frame->findObject("data4");
    if (dataPoints4) {
        dataPoints4->SetMarkerSize(1.3);
        leg->AddEntry(dataPoints4, " K* sideband points", "pe");
    }
    TGraph* datafit = (TGraph*)frame->findObject("datafit");
    if (datafit) {
        datafit->SetMarkerSize(1.3);
        leg->AddEntry(datafit, " Fit of data", "l");
    }
    TGraph* sigfit = (TGraph*)frame->findObject("sigfit");
    if (sigfit) {
        sigfit->SetMarkerSize(1.3);
        leg->AddEntry(sigfit, " Signal of data fit", "l");
    }
    TGraph* bkgfit = (TGraph*)frame->findObject("bkgfit");
    if (bkgfit) {
        bkgfit->SetMarkerSize(1.3);
        leg->AddEntry(bkgfit, " Background of data fit", "l");
    }
    TGraph* mixfit = (TGraph*)frame->findObject("mixfit");
    if (mixfit) {
        mixfit->SetMarkerSize(1.3);
        leg->AddEntry(mixfit, " Fit of event mixing", "l");
    }
    TGraph* sbfit = (TGraph*)frame->findObject("sbfit");
    if (sbfit) {
        sbfit->SetMarkerSize(1.3);
        leg->AddEntry(sbfit, " Fit of K* sideband", "l");
    }
    leg->Draw("same");
    c1->Update();
    c1->SaveAs("resultpics/ress.png");
    c1->SaveAs("resultpics/ress.pdf");
    out->Write();



    
    cout<<"Bkg_par: "<<Bkg_a1.getVal()<<" / "<<Bkg_a2.getVal()<<endl;
    cout<<"mixBkg_par: "<<Bkg_a3.getVal()<<" / "<<Bkg_a4.getVal()<<endl;
    cout<<"sb_par: "<<Bkg_a5.getVal()<<" / "<<Bkg_a6.getVal()<<endl;
}