#include "TCanvas.h"
#include "TGraph.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

void Significace()
{
        RooRealVar psi2s_mass("psi2s_mass", "M(#mu#mu#pi#pi)-M(#mu#mu)+3.0969 GeV", 3.8, 3.95);
        RooArgSet variables;
        variables.add(psi2s_mass);
        psi2s_mass.setRange("fullRange", 3.85, 3.95);
        RooDataSet *data = RooDataSet::read("data.txt", variables, "Q", "D:/Desktop/SR/code/CutOptimization-run3-2/data/", nullptr);
        RooRealVar meanSig("meanSig","meanSig", 3.872e+00, 3.85, 3.95);
        RooRealVar sigmaSig("sigmaSig", "sigmaSig", 0.01, 0.0001, 100);
        sigmaSig.setConstant(kTRUE);
        RooGaussian sigPdf("sigPdf", "sigPdf", psi2s_mass, meanSig, sigmaSig);
        RooRealVar c1_bkg("c1_bkg_psi2s", "c1_bkg_psi2s", 1.35819e-01, -0.8, 0.8);
        RooRealVar c2_bkg("c2_bkg_psi2s", "c2_bkg_psi2s", -4.91313e-02, -0.6, 0.6);
        RooRealVar c3_bkg("c3_bkg_psi2s", "c3_bkg_psi2s", 5.91313e-02, -0.07, 0.07);
        RooChebychev chbPdf("chbPdf", "chbPdf", psi2s_mass, RooArgList(c1_bkg, c2_bkg, c3_bkg));
        RooRealVar norm("norm", "norm", 820);// Do remember modify this. It's total entry num
        RooExtendPdf bkgPdf("bkgPdf", "bkgPdf", chbPdf, norm);
        RooRealVar n_sig("n_sig", "n_sig", 0, 0, 100000);
        RooRealVar n_bkg("n_bkg", "n_bkg", 1000, 0, 100000);
        RooAddPdf totalPdf("totalPdf", "totalPdf", RooArgList(sigPdf, bkgPdf), RooArgList(n_sig, n_bkg));

        double tem = 1.35819e-01; 
        double Data_edm;
        int Data_status, Data_covQual;
        RooFitResult *fitRes;
        unsigned int ii = 0;
        bool isBkg = false;
        while (true)
        {
                c1_bkg.setVal(tem);
                OwningPtr<RooFitResult> fitRes;
                if(isBkg)
                {
                        fitRes = bkgPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));//Fit total PDF
                }else{
                        fitRes = totalPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(0), Warnings(-1), PrintEvalErrors(2));//Fit total PDF
                }
                Data_edm = fitRes->edm();
                Data_status = fitRes->status();
                Data_covQual = fitRes->covQual();
                ii = ii + 1;
                if ((Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3) || ii >= 1000)
                {
                        break;
                }
 }
        RooPlot *myframe = psi2s_mass.frame();
        data->plotOn(myframe);
        psi2s_mass.setRange("peak", 3.85, 3.9);
        // auto leg = new TLegend(3.9,27.5,3.94,32.5);
        // leg->AddEntry(data,"data points","P");
        if(isBkg)
        {
                bkgPdf.plotOn(myframe, LineColor(kRed));
                //leg->AddEntry(bkgPdf,"background","L");
                cout<<"Here is H_0 "<<endl;
                cout<<"NLL is "<< bkgPdf.createNLL(*data)->getVal()<<std::endl;
        }else
        {
                // data
                totalPdf.plotOn(myframe, LineColor(kRed));
                sigPdf.plotOn(myframe, LineColor(kBlue));
                bkgPdf.plotOn(myframe, LineColor(kBlack));
                //leg->AddEntry(bkgPdf,"background","L");
                //leg->AddEntry(sigPdf,"signal","L");
                //leg->AddEntry("totalPdf","total PDF","L");
                cout<<"Here is H_1 "<<endl;
                // totalPdf.createNLL(*data, Range("peak"))->plotOn(myframe);
                cout<<"NLL is "<<totalPdf.createNLL(*data)->getVal()<<std::endl;
        }
        myframe->Draw();
//      leg->Draw();
}