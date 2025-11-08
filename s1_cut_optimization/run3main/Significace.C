#include "function_run3main.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
#include "RooStats/RooStatsUtils.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

void Significace()
{
        myset(myStyle, variables);
	psi2s_mass.setRange(3.85, 3.95);
	RooDataSet *data = RooDataSet::read("result.txt", variables, "Q", "D:/Desktop/SR/code/CutOptimization-run3-2/data/", nullptr);
	RooRealVar meanSig("meanSig","meanSig", 3.872e+00, 3.871, 3.873);
        RooRealVar sigmaSig("sigmaSig", "sigmaSig", 0.000001, 0.000001, 0.001);

        RooGaussian sigPdf("sigPdf", "sigPdf", psi2s_mass, meanSig, sigmaSig);
        RooRealVar c1_bkg("c1_bkg_psi2s", "c1_bkg_psi2s", 1.35819e-01, -0.8, 0.8);
        RooRealVar c2_bkg("c2_bkg_psi2s", "c2_bkg_psi2s", -4.91313e-02, -0.6, 0.6);
        RooRealVar c3_bkg("c3_bkg_psi2s", "c3_bkg_psi2s", 5.91313e-02, -0.07, 0.07);
        RooChebychev chbPdf("chbPdf", "chbPdf", psi2s_mass, RooArgList(c1_bkg, c2_bkg, c3_bkg));
        RooRealVar norm("norm", "norm", 9000);// Do remember modify this. It's total entry num
        RooExtendPdf bkgPdf("bkgPdf", "bkgPdf", chbPdf, norm);
        RooRealVar n_sig("n_sig", "n_sig", 0, 0, 100000);
        RooRealVar n_bkg("n_bkg", "n_bkg", 1000, 0, 100000);
        RooAddPdf totalPdf("totalPdf", "totalPdf", RooArgList(sigPdf, bkgPdf), RooArgList(n_sig, n_bkg));
        //meanSig.setConstant(kTRUE);
        double tem = 1.35819e-01; 
        double Data_edm;
        int Data_status, Data_covQual;
        RooFitResult *fitRes;
        unsigned int ii = 0;
        bool isBkg =1;
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
       
                bkgPdf.plotOn(myframe, LineColor(kBlue));
                //leg->AddEntry(bkgPdf,"background","L");
                cout<<"Here is H_0 "<<endl;
                cout<<"NLL is "<< bkgPdf.createNLL(*data)->getVal()<<std::endl;
                // data
                totalPdf.plotOn(myframe,Components(bkgPdf) ,LineStyle(kDashed),LineColor(kRed)); 
                totalPdf.plotOn(myframe,Components(sigPdf) ,LineColor(kRed));
                totalPdf.plotOn(myframe,LineColor(kRed));
                myframe->Draw();
                //leg->AddEntry(bkgPdf,"background","L");
                //leg->AddEntry(sigPdf,"signal","L");
                //leg->AddEntry("totalPdf","total PDF","L");
                cout<<"Here is H_1 "<<endl;
                // totalPdf.createNLL(*data, Range("peak"))->plotOn(myframe);
                cout<<"NLL is "<<totalPdf.createNLL(*data)->getVal()<<std::endl;
                Double_t ln_l1 = bkgPdf.createNLL(*data)->getVal();
                Double_t ln_l2 = totalPdf.createNLL(*data)->getVal();
    Double_t delta_ln_l = fabs(ln_l1 - ln_l2);// delta_ln_l is log likelyhood ratio that is ll of alternative hyposis over that of zero hyposis, the larger, the more possible signal exists
    Int_t ndf = 4;
    Double_t chi2 = 2 * delta_ln_l;// chi2 is simply twice delta_ln_l
    Double_t pval = TMath::Prob(chi2, ndf);// returns upper tail cdf of chi2 distribution
                                           // from chi2->inf and number of freedom is ndf
    Double_t significance = RooStats::PValueToSignificance(pval/2.0);// returns inverse of
    // upper tail cdf of a gaussian distribution with mu=0 and sigma=1, this means possiblity
    // of a normal distribution out side sigificance range(-int->-s and s->inf) is pval
    //cout << "delta lnL = " << delta_ln_l << endl;
    cout << "number of degree of freedom = " << ndf << endl;
    cout << "confidence level = " << pval << endl;
    cout << "significance = " << significance << endl;
        
//      leg->Draw();
}