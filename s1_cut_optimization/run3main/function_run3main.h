#ifndef FUNCTION_H
#define FUNCTION_H 1
#include <limits.h>
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooBreitWigner.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooAddition.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooProdPdf.h"
#include "RooProduct.h"
#include "RooCBShape.h"
#include "TSystem.h"
#include "RooFitResult.h"

#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAxis.h"

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include "TCanvas.h"
#include "TGraph.h"
#include "var_run3main.h"
// use this order for safet on library loading
using namespace std;
using namespace RooFit;
using namespace RooStats;

// Global variables
TStyle *myStyle = new TStyle("myStyle", "my Style");
RooArgSet variables;

//Class holds results of fit, constructed by function fitData() 
class myresult
{
public:
    double merit;// S/sqrt(S + B)
    double mySfromData;// S
    double myBfromData;// B
    double tem;// Tried position (not used)
    bool fitquality = 0;// fit quality, 1 for good fit and 0 for bad fit
};

//Print all elements in a vector<double> in a line with , spliting and with a title str:
void print(string str, vector<double> vec)
{
    if (vec.size() > 0)
    {
        cout << str << " : ";
        for (long unsigned int j = 0; j < vec.size(); j++)
        {
            cout << vec[j] << ", ";
        }
        cout << endl;
    }
}

void myset(TStyle *myStyle, RooArgSet &variables)
{
    //Set Drawing Style
    myStyle->SetCanvasBorderMode(0);
    myStyle->SetCanvasColor(10);
    myStyle->SetPadBorderMode(0);
    myStyle->SetPadColor(10);
    myStyle->SetPadBottomMargin(0.15);
    myStyle->SetPadLeftMargin(0.15);
    myStyle->SetPaperSize(18, 24);
    myStyle->SetLabelSize(0.04, "XY");
    myStyle->SetLabelOffset(0.01, "Y");
    myStyle->SetTitle("");
    myStyle->SetOptStat(00000);
    myStyle->SetTitleOffset(1, "XY");
    myStyle->SetTitleSize(0.06, "XY");
    gROOT->SetStyle("myStyle");

    //Please add all cut variables here
    //Cut variables are declared in var_run3main.h file
    variables.add(psi2s_mass);
    variables.add(jpsi_mass); 
    variables.add(jpsi_mass1);
    variables.add(MuJpsiRes);
    variables.add(MuonD0);
    variables.add(MuonD02);
    variables.add(MuonD03);
    variables.add(MuonD04);
    variables.add(MuonIso);
    variables.add(MuonIso2);
    variables.add(MuonIso3);
    variables.add(MuonIso4);
    variables.add(Dpipi);
    variables.add(Dpsi2smu);
    variables.add(Dpsi2smu2);
    variables.add(Dpsi2smu3);
    variables.add(Dpsi2smu4);
    variables.add(Dpsi2spi);
    variables.add(Dpsi2spi2);
    variables.add(Dpsi2sjpsi1);
    variables.add(Djpsimu);
    variables.add(Djpsimu2);
    variables.add(XEta);
    variables.add(XPt);
    variables.add(psi2sProb);
    variables.add(psi2sEta);
    variables.add(psi2sPt);
    variables.add(jpsi2Eta);
    variables.add(jpsi1Eta);
    variables.add(jpsi2Pt);
    variables.add(jpsi1Pt);
    variables.add(MuEta);
    variables.add(MuEta2);
    variables.add(MuEta3);
    variables.add(MuEta4);
    variables.add(MuPt);
    variables.add(MuPt2);
    variables.add(MuPt3);
    variables.add(MuPt4);
    variables.add(PiEta);
    variables.add(PiEta2);
    variables.add(PiPt);
    variables.add(PiPt2);
}

//Print with title str : and , spliting; Print all elements; Print maximum in vec2 and
//elements in vec1 with the same index, format is Max = vec1_same_index : maximun vec2
void print_vectors(string str, vector<double> vec1, vector<double> vec2)
{
    if (vec1.size() > 0 && vec2.size() > 0)
    {
        double max_vec2 = vec2[0];
        double cor_vec1 = vec1[0];
        cout << str << " : " << endl;
        for (int j = 0; j < vec1.size(); j++)
        {
            cout << vec1[j] << ", ";
        }
        cout << endl;
        for (int j = 0; j < vec2.size(); j++)
        {
            cout << vec2[j] << ", ";
            if (vec2[j] > max_vec2)
            {
                max_vec2 = vec2[j];
                cor_vec1 = vec1[j];
            }
        }
        cout << endl
             << str << "Max = " << cor_vec1 << " : " << max_vec2 << endl;
    }
}
// Override version for saving a file with name fileName.txt
void print_vectors(const char* fileName, string str, vector<double> vec1, vector<double> vec2)
{
    std::ofstream file;
    std::string text = fileName;
    text = text + ".txt";
    file.open(text.c_str(), std::ios::out);
    if (vec1.size() > 0 && vec2.size() > 0)
    {
        double max_vec2 = vec2[0];
        double cor_vec1 = vec1[0];
        file << str << " : " << endl;
        for (int j = 0; j < vec1.size(); j++)
        {
            file << vec1[j] << ", ";
        }
        file << endl;
        for (int j = 0; j < vec2.size(); j++)
        {
            file << vec2[j] << ", ";
            if (vec2[j] > max_vec2)
            {
                max_vec2 = vec2[j];
                cor_vec1 = vec1[j];
            }
        }
        file << endl
             << str << "Max = " << cor_vec1 << " : " << max_vec2 << endl;
    }
}
// Override version with eventnumber output
void print_vectors(const char* fileName, string str, vector<double> vec1, vector<double> vec2,  vector<double> eventnum)
{
    std::ofstream file;
    std::string text = fileName;
    text = text + ".txt";
    file.open(text.c_str(), std::ios::out);
    if (vec1.size() > 0 && vec2.size() > 0)
    {
        double max_vec2 = vec2[0];
        double cor_vec1 = vec1[0];
        double cor_event = eventnum[0];
        file << str << " : " << endl;
        for (int j = 0; j < vec1.size(); j++)
        {
            file << vec1[j] << ", ";
        }
        file << endl;
        for (int j = 0; j < vec2.size(); j++)
        {
            file << vec2[j] << ", ";
            if (vec2[j] > max_vec2)
            {
                max_vec2 = vec2[j];
                cor_vec1 = vec1[j];
                cor_event = eventnum[j];
            }
        }
        file << endl;
        for (int j = 0; j < eventnum.size(); j++)
        {
            file << eventnum[j] << ", ";
        }
        double finalacceptance = cor_event/eventnum[0];
        file << endl
             << str << "Max = " << cor_vec1 << " : " << max_vec2 << " : " <<  cor_event << " : " << finalacceptance << endl;
    }
}
//Draw a plot use vecotr x as x_data and y as y_data, the x axis title is str
void drawVectors(const char *str, vector<double> x, vector<double> y)
{
    TCanvas *canvas = new TCanvas("c1", "my graph", 200, 10, 700, 500);
    TGraph *gr = new TGraph(x.size(), &x[0], &y[0]);//Load graph from vector x and y, note that they must have the same dimension
    gr->SetTitle("Figure of Merit");
    gr->GetXaxis()->SetTitle(str);
    gr->GetYaxis()->SetTitle("Merit");
    gr->Draw("AL");//A: Draw axis; L: Draw ployline to make a plot
    gr->SetLineWidth(7);
}
// Override version for saving a file in fileName.png
void drawVectors(const char *fileName, const char *str, vector<double> x, vector<double> y)
{
    TCanvas *canvas = new TCanvas("c1", "my graph", 200, 10, 700, 500);
    TGraph *gr = new TGraph(x.size(), &x[0], &y[0]);//Load graph from vector x and y, note that they must have the same dimension
    std::string tempStr = "Figure of Merit";
    tempStr = tempStr + fileName;
    gr->SetTitle(tempStr.c_str());
    gr->GetXaxis()->SetTitle(str);
    gr->GetYaxis()->SetTitle("Merit");
    gr->Draw("AL");//A: Draw axis; L: Draw ployline to make a plot
    gr->SetLineWidth(7);
    tempStr = fileName;
    tempStr = tempStr + ".png"; 
    canvas->SaveAs(tempStr.c_str());
}
// Override version for getting acceptance, rejection and merit in range(0,1) in a same pic.
void drawVectors(const char *fileName, const char *str, vector<double> x, vector<double> y, vector<double> eventnum)
{
    double meritmax = y[0];
    double meritmin = y[0];
    for (int j = 0; j < y.size(); j++)
        {
            if (y[j] > meritmax)
            {
                meritmax = y[j];
            }
            if (y[j] < meritmin)
            {
                meritmin = y[j];
            }
        }
    for (int j = 0; j < y.size(); j++)
    {
        y[j] = (y[j] - meritmin)/(meritmax - meritmin);
    }
    TCanvas *canvas = new TCanvas("c1", "my graph", 200, 10, 700, 500);
    TGraph *gr1 = new TGraph(x.size(), &x[0], &y[0]);//Load graph from vector x and y, note that they must have the same dimension
    vector<double> acceptance;
    vector<double> rejection;
    for (int j = 0; j < eventnum.size(); j++)
    {
        acceptance.push_back(eventnum[j]/eventnum[0]);
        rejection.push_back(1-(eventnum[j]/eventnum[0]));
    }
    std::string tempStr = "Figure of Merit";
    tempStr = tempStr + fileName;
    gr1->SetTitle(tempStr.c_str());
    gr1->GetXaxis()->SetTitle(str);
    gr1->GetYaxis()->SetTitle("Merit");
    gr1->Draw("AL");//A: Draw axis; L: Draw ployline to make a plot
    gr1->SetLineWidth(7);
    TGraph *gr2 = new TGraph(x.size(), &x[0], &acceptance[0]);
    TGraph *gr3 = new TGraph(x.size(), &x[0], &rejection[0]);
    gr2->SetLineColor(kRed);
    gr3->SetLineColor(kBlue);
    gr2->Draw("L*");
    gr3->Draw("L*");
    tempStr = fileName;
    tempStr = tempStr + ".png"; 
    canvas->SaveAs(tempStr.c_str());
}
//Do a fit and calculate merit
myresult fitData(RooDataSet *data, bool isDraw = false)
{
    //Set signal and background PDF and paramiters
    //signal: double cristal ball by certain fraction
    //background: 2th order Chebychev for Jpsi and 3th order Chebychev for Psi2s
   
    // signal config
    double meanCB;
    if(isDraw)
    {
	    meanCB = 3.68619e+00;
    }else
    {
	    meanCB = 3.872e+00; // For spacial fit when drawing result
    }

    RooRealVar meanCB1_psi2s("meanCB1_psi2s", "meanCB1_psi2s", 3.68619e+00, psi2s_mass_Min, psi2s_mass_Max);
    RooRealVar sigmaCB1_psi2s("sigmaCB1_psi2s", "sigmaCB1_psi2s", 9.59592e-03, 0., 0.01);
    RooRealVar nCB1_psi2s("nCB1_psi2s", "nCB1_psi2s", 1.99999e+01);
    RooRealVar alphaCB1_psi2s("alphaCB1_psi2s", "alphaCB1_psi2s", 1.99999e+00);
    RooCBShape CB1_psi2s("CB1_psi2s", "CB1_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB1_psi2s, alphaCB1_psi2s, nCB1_psi2s);

    RooRealVar sigmaCB2_psi2s("sigmaCB2_psi2s", "sigmaCB2_psi2s", 5.28500e-03, 0, 0.01);
    RooRealVar nCB2_psi2s("nCB2_psi2s", "nCB2_psi2s", 7.38216e-01);
    RooRealVar alphaCB2_psi2s("alphaCB2_psi2s", "alphaCB2_psi2s", 5.35155e+00);
    RooCBShape CB2_psi2s("CB2_psi2s", "CB2_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB2_psi2s, alphaCB2_psi2s, nCB2_psi2s);

    RooRealVar fracCB1_psi2s("fracCB1_psi2s", "fracCB1_psi2s", 5.14370e-01);
    RooAddPdf psi2s_double_CB_Fcn("psi2s_double_CB_Fcn", "psi2s_double_CB_Fcn",
                                  RooArgList(CB1_psi2s, CB2_psi2s), fracCB1_psi2s);

    // background config
    RooRealVar c1_bkg_psi2s("c1_bkg_psi2s", "c1_bkg_psi2s", 1.35819e-01, -0.8, 0.8);
    RooRealVar c2_bkg_psi2s("c2_bkg_psi2s", "c2_bkg_psi2s", -4.91313e-02, -0.6, 0.6);
    RooRealVar c3_bkg_psi2s("c3_bkg_psi2s", "c3_bkg_psi2s", 5.91313e-02, -0.07, 0.07);
    RooChebychev bkg_psi2s_Fcn("bkg_psi2s_Fcn", "bkg_psi2s_Fcn", psi2s_mass, RooArgList(c1_bkg_psi2s, c2_bkg_psi2s, c3_bkg_psi2s));

    // Fraction of psi2s and bkg, also total event numbers of each
    RooRealVar n_psi2s("n_psi2s", "n_psi2s", 0, 0, 100000);
    RooRealVar n_bkg_psi2s("n_bkg_psi2s", "n_bkg_psi2s", 1000, 0, 100000);

    RooAddPdf totalPdf("totalPdf", "totalPdf", RooArgList(psi2s_double_CB_Fcn, bkg_psi2s_Fcn), RooArgList(n_psi2s, n_bkg_psi2s));

    //Make mass of Psi2s constant
    if(!isDraw)
    {
    // sigmaCB1_jpsi.setConstant(kTRUE);
    sigmaCB1_psi2s.setConstant(kTRUE);
    // sigmaCB2_jpsi.setConstant(kTRUE);
    sigmaCB2_psi2s.setConstant(kTRUE);
    	meanCB1_psi2s.setConstant(kTRUE);
    }

    double tem = 1.35819e-01;
    double Data_edm;
    int Data_status, Data_covQual;
    RooFitResult *fitRes;
    unsigned int ii = 0;
    while (true)
    {
        c1_bkg_psi2s.setVal(tem);
        fitRes = totalPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));//Fit total PDF
        Data_edm = fitRes->edm();
        Data_status = fitRes->status();
        Data_covQual = fitRes->covQual();
	ii = ii + 1;
        if ((Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3) || ii >= 100)
        {
            break;
        }
        tem += 0.0001;
    }

    // double x1min = 3.6861 - 0.01 * 3; // psi2s mean massErr 10 MeV, 3 mass window
    // double x1max = 3.6861 + 0.01 * 3;
    // double x2min = 3.0969 - 0.03 * 3; // jpsi mean massErr 30 MeV, 3 mass window
    // double x2max = 3.0969 + 0.03 * 3;
    double x1min = psi2s_mass_Min; // psi2s mean massErr 10 MeV, 3 mass window
    double x1max = psi2s_mass_Max;
    psi2s_mass.setRange("massPeak", x1min, x1max);

    // only consider events under psi2s mass peak

    double areabkglimit = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("massPeak"))->getVal(); 
    double areasiglimit = psi2s_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("massPeak"))->getVal();

    double areabkgtotal = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal();
    double areasigtotal = psi2s_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal(); 

    // Compute fraction of events under range of the mass peak, that is the fanal S/B is the result under the peak
    double fraclimitbkg = areabkglimit / areabkgtotal;
    double fraclimitsig = areasiglimit / areasigtotal;

    cout << "fraclimitbkg: " << fraclimitbkg << endl;
    cout << "fraclimitsig: " << fraclimitsig << endl;

    // getntotal
    double nbkgTotal = n_bkg_psi2s.getVal();
    double nsigTotal = n_psi2s.getVal();

    cout << "nbkgTotal: " << nbkgTotal << endl;
    cout << "nsigTotal:" << nsigTotal << endl;

    // getnlimit
    double nbkglimit = nbkgTotal * fraclimitbkg;
    double nsiglimit = nsigTotal * fraclimitsig;

    cout << "nbkglimit:" << nbkglimit << endl;
    cout << "nsiglimit:" << nsiglimit << endl;

    double myBfromData = nbkglimit;
    double mySfromData = nsiglimit;

    cout << "mySfromData = " << mySfromData << endl;
    cout << "myBfromData = " << myBfromData << endl;

    cout << "Data_edm = " << Data_edm << endl;
    cout << "Data_status = " << Data_status << endl;
    cout << "Data_covQual = " << Data_covQual << endl;
    myresult myroofitresult;
    myroofitresult.merit = mySfromData / sqrt(myBfromData + mySfromData);
    myroofitresult.myBfromData = myBfromData;
    myroofitresult.mySfromData = mySfromData;
    myroofitresult.tem = tem;
    if (Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3)
    {
        myroofitresult.fitquality = 1;
    }
    // Draw a graph if isDraw is true
    if(isDraw)
    {
        TCanvas *Resultc = new TCanvas("Resultc", "Resultc", 1);
    	RooPlot *myframe = psi2s_mass.frame();
    	data->plotOn(myframe);
    	totalPdf.plotOn(myframe,Components(bkg_psi2s_Fcn) ,LineStyle(kDashed),LineColor(kBlue)); 
        totalPdf.plotOn(myframe,Components(psi2s_double_CB_Fcn) ,LineColor(kRed)); 
        totalPdf.plotOn(myframe,LineColor(kBlue)); 
    	myframe->Draw();
        Resultc->SaveAs("result/fitdata.png");
    }
    ii = 0;
    return myroofitresult;
}


//This function will fit both Psi2S and X3872 peak and maintain the distance of these two peak as a constant.
myresult fitData2peak(RooDataSet *data, bool isDraw = false)
{
    double distance = 3.872-3.68619;
    RooRealVar dist("dist", "dist", distance, 0.15, 0.25);
    dist.setConstant(kTRUE);

    //psi2S peak sig
    RooRealVar meanCB1_psi2s("meanCB1_psi2s", "meanCB1_psi2s", 3.68619e+00, psi2s_mass_Min, psi2s_mass_Max);
    RooRealVar sigmaCB1_psi2s("sigmaCB1_psi2s", "sigmaCB1_psi2s", 9.59592e-03, 0., 0.01);
    RooRealVar nCB1_psi2s("nCB1_psi2s", "nCB1_psi2s", 1.99999e+01);
    RooRealVar alphaCB1_psi2s("alphaCB1_psi2s", "alphaCB1_psi2s", 1.99999e+00);
    RooCBShape CB1_psi2s("CB1_psi2s", "CB1_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB1_psi2s, alphaCB1_psi2s, nCB1_psi2s);

    RooRealVar sigmaCB2_psi2s("sigmaCB2_psi2s", "sigmaCB2_psi2s", 5.28500e-03, 0, 0.01);
    RooRealVar nCB2_psi2s("nCB2_psi2s", "nCB2_psi2s", 7.38216e-01);
    RooRealVar alphaCB2_psi2s("alphaCB2_psi2s", "alphaCB2_psi2s", 5.35155e+00);
    RooCBShape CB2_psi2s("CB2_psi2s", "CB2_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB2_psi2s, alphaCB2_psi2s, nCB2_psi2s);

    RooRealVar fracCB1_psi2s("fracCB1_psi2s", "fracCB1_psi2s", 5.14370e-01);
    RooAddPdf psi2s_double_CB_Fcn("psi2s_double_CB_Fcn", "psi2s_double_CB_Fcn",
                                  RooArgList(CB1_psi2s, CB2_psi2s), fracCB1_psi2s);
    //X3872 peak sig
    RooFormulaVar meanCB1_X("meanCB1_X", "meanCB1_psi2s+dist", RooArgList(meanCB1_psi2s,dist));
    
    RooRealVar sigmaCB1_X("sigmaCB1_X", "sigmaCB1_X", 9.59592e-03, 0., 0.01);
    RooRealVar nCB1_X("nCB1_X", "nCB1_X", 1.99999e+01);
    RooRealVar alphaCB1_X("alphaCB1_X", "alphaCB1_X", 1.99999e+00);
    RooCBShape CB1_X("CB1_X", "CB1_X", psi2s_mass,
                         meanCB1_X, sigmaCB1_X, alphaCB1_X, nCB1_X);

    RooRealVar sigmaCB2_X("sigmaCB2_X", "sigmaCB2_X", 5.28500e-03, 0, 0.01);
    RooRealVar nCB2_X("nCB2_X", "nCB2_X", 7.38216e-01);
    RooRealVar alphaCB2_X("alphaCB2_X", "alphaCB2_X", 5.35155e+00);
    RooCBShape CB2_X("CB2_X", "CB2_Xs", psi2s_mass,
                         meanCB1_X, sigmaCB2_X, alphaCB2_X, nCB2_X);

    RooRealVar fracCB1_X("fracCB1_X", "fracCB1_X", 5.14370e-01);
    RooAddPdf X_double_CB_Fcn("X_double_CB_Fcn", "X_double_CB_Fcn",
                                  RooArgList(CB1_X, CB2_X), fracCB1_X);


    // background config
    RooRealVar c1_bkg_psi2s("c1_bkg_psi2s", "c1_bkg_psi2s", 1.35819e-01, -0.8, 0.8);
    RooRealVar c2_bkg_psi2s("c2_bkg_psi2s", "c2_bkg_psi2s", -4.91313e-02, -0.6, 0.6);
    RooRealVar c3_bkg_psi2s("c3_bkg_psi2s", "c3_bkg_psi2s", 5.91313e-02, -0.07, 0.07);
    RooChebychev bkg_psi2s_Fcn("bkg_psi2s_Fcn", "bkg_psi2s_Fcn", psi2s_mass, RooArgList(c1_bkg_psi2s, c2_bkg_psi2s, c3_bkg_psi2s));

    // Fraction of sig and bkg, also total event numbers of each
    RooRealVar n_sig_psi2s("n_sig_psi2s", "n_sig_psi2s", 10, 0, 100000);
    RooRealVar n_sig_X("n_sig_X", "n_sig_X", 10, 0, 100000);
    RooRealVar n_bkg("n_bkg", "n_bkg", 1000, 0, 100000);

    RooAddPdf totalPdf("totalPdf", "totalPdf", RooArgList(psi2s_double_CB_Fcn, X_double_CB_Fcn, bkg_psi2s_Fcn), RooArgList(n_sig_psi2s, n_sig_X, n_bkg));

    double tem = 1.35819e-01;
    double Data_edm;
    int Data_status, Data_covQual;
    RooFitResult *fitRes;
    unsigned int ii = 0;
    while (true)
    {
        c1_bkg_psi2s.setVal(tem);
        fitRes = totalPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));//Fit total PDF
        Data_edm = fitRes->edm();
        Data_status = fitRes->status();
        Data_covQual = fitRes->covQual();
	ii = ii + 1;
        if ((Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3) || ii >= 100)
        {
            break;
        }
        tem += 0.0001;
    }

    double x1min = 3.84; // psi2s mean massErr 10 MeV, 3 mass window
    double x1max = 3.90;
    psi2s_mass.setRange("X_massPeak", x1min, x1max);

    // only consider events under psi2s mass peak

    double areabkglimit = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("X_massPeak"))->getVal(); 
    double areasiglimit = X_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("X_massPeak"))->getVal();

    double areabkgtotal = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal();
    double areasigtotal = X_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal(); 

    // Compute fraction of events under range of the mass peak, that is the fanal S/B is the result under the peak
    double fraclimitbkg = areabkglimit / areabkgtotal;
    double fraclimitsig = areasiglimit / areasigtotal;

    cout << "fraclimitbkg: " << fraclimitbkg << endl;
    cout << "fraclimitsig: " << fraclimitsig << endl;

    // getntotal
    double nbkgTotal = n_bkg.getVal();
    double nsigTotal = n_sig_X.getVal();

    cout << "nbkgTotal: " << nbkgTotal << endl;
    cout << "nsigTotal:" << nsigTotal << endl;

    // getnlimit
    double nbkglimit = nbkgTotal * fraclimitbkg;
    double nsiglimit = nsigTotal * fraclimitsig;

    cout << "nbkglimit:" << nbkglimit << endl;
    cout << "nsiglimit:" << nsiglimit << endl;

    double myBfromData = nbkglimit;
    double mySfromData = nsiglimit;

    cout << "mySfromData = " << mySfromData << endl;
    cout << "myBfromData = " << myBfromData << endl;

    cout << "Data_edm = " << Data_edm << endl;
    cout << "Data_status = " << Data_status << endl;
    cout << "Data_covQual = " << Data_covQual << endl;
    myresult myroofitresult;
    myroofitresult.merit = mySfromData / sqrt(myBfromData + mySfromData);
    myroofitresult.myBfromData = myBfromData;
    myroofitresult.mySfromData = mySfromData;
    myroofitresult.tem = tem;

    double bkgn=n_bkg.getVal();
    double psi2Sn=n_sig_psi2s.getVal();
    double Xn=n_sig_X.getVal();
    double psi2smasscenter=meanCB1_psi2s.getVal();
    double Xmasscenter=meanCB1_X.getVal();
    cout<<"Psi2S Mass Center at: "<<psi2smasscenter<<"; X3872 Mass Center at: "<<Xmasscenter<<endl;
    cout<<"Background number: "<<bkgn<<"; Psi2S number: "<<psi2Sn<<"; X3872 number: "<<Xn<<endl;
    if(isDraw)
    {
        TCanvas *Resultc = new TCanvas("Resultc", "Resultc", 1);
    	RooPlot *myframe = psi2s_mass.frame();
    	data->plotOn(myframe);
    	totalPdf.plotOn(myframe,Components(bkg_psi2s_Fcn) ,LineStyle(kDashed),LineColor(kBlue)); 
        totalPdf.plotOn(myframe,Components(psi2s_double_CB_Fcn) ,LineColor(kRed)); 
        totalPdf.plotOn(myframe,Components(X_double_CB_Fcn) ,LineColor(kGreen));
        totalPdf.plotOn(myframe,LineColor(kBlue)); 
    	myframe->Draw();
        Resultc->SaveAs("result/fitdata2peak.png");
    }
    return myroofitresult;
}


myresult fitData2D(RooDataSet *data, bool isDraw = false)
{
    RooRealVar meanCB1_psi2s("meanCB1_psi2s", "meanCB1_psi2s", 3.68619e+00, 3.682, 3.688);
    RooRealVar sigmaCB1_psi2s("sigmaCB1_psi2s", "sigmaCB1_psi2s", 9.59592e-03, 0., 0.01);
    RooRealVar nCB1_psi2s("nCB1_psi2s", "nCB1_psi2s", 1.99999e+01);
    RooRealVar alphaCB1_psi2s("alphaCB1_psi2s", "alphaCB1_psi2s", 1.99999e+00);
    RooCBShape CB1_psi2s("CB1_psi2s", "CB1_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB1_psi2s, alphaCB1_psi2s, nCB1_psi2s);

    RooRealVar sigmaCB2_psi2s("sigmaCB2_psi2s", "sigmaCB2_psi2s", 5.28500e-03, 0, 0.01);
    RooRealVar nCB2_psi2s("nCB2_psi2s", "nCB2_psi2s", 7.38216e-01);
    RooRealVar alphaCB2_psi2s("alphaCB2_psi2s", "alphaCB2_psi2s", 5.35155e+00);
    RooCBShape CB2_psi2s("CB2_psi2s", "CB2_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB2_psi2s, alphaCB2_psi2s, nCB2_psi2s);

    RooRealVar fracCB1_psi2s("fracCB1_psi2s", "fracCB1_psi2s", 5.14370e-01);
    RooAddPdf psi2s_double_CB_Fcn("psi2s_double_CB_Fcn", "psi2s_double_CB_Fcn",
                                  RooArgList(CB1_psi2s, CB2_psi2s), fracCB1_psi2s);

    RooRealVar meanCB1_jpsi("meanCB1_jpsi", "meanCB1_jpsi", 3.09603065e+00, 3.05, 3.12);
    RooRealVar sigmaCB1_jpsi("sigmaCB1_jpsi", "sigmaCB1_jpsi", 3.03477e-02, 0., 0.1);
    RooRealVar nCB1_jpsi("nCB1_jpsi", "nCB1_jpsi", 9.99947e+00);
    RooRealVar alphaCB1_jpsi("alphaCB1_jpsi", "alphaCB1_jpsi", 1.40029e+00);
    RooCBShape CB1_jpsi("CB1_jpsi", "CB1_jpsi", jpsi_mass,
                        meanCB1_jpsi, sigmaCB1_jpsi, alphaCB1_jpsi, nCB1_jpsi);

    RooRealVar sigmaCB2_jpsi("sigmaCB2_jpsi", "sigmaCB2_jpsi", 6.89897e-02, 0., 0.1);
    RooRealVar nCB2_jpsi("nCB2_jpsi", "nCB2_jpsi", 3.75249e+00 /*,0,10*/);
    RooRealVar alphaCB2_jpsi("alphaCB2_jpsi", "alphaCB2_jpsi", -4.41544e+00 /*,-5,5*/);
    RooCBShape CB2_jpsi("CB2_jpsi", "CB2_jpsi", jpsi_mass,
                        meanCB1_jpsi, sigmaCB2_jpsi, alphaCB2_jpsi, nCB2_jpsi);

    RooRealVar fracCB1_jpsi("fracCB1_jpsi", "fracCB1_jpsi", 5.59735e-01);
    RooAddPdf jpsi_double_CB_Fcn("jpsi_double_CB_Fcn", "jpsi_double_CB_Fcn",
                                 RooArgList(CB1_jpsi, CB2_jpsi), fracCB1_jpsi);

    RooRealVar c1_bkg_psi2s("c1_bkg_psi2s", "c1_bkg_psi2s", 1.35819e-01, -0.8, 0.8);
    RooRealVar c2_bkg_psi2s("c2_bkg_psi2s", "c2_bkg_psi2s", -4.91313e-02, -0.6, 0.6);
    RooRealVar c3_bkg_psi2s("c3_bkg_psi2s", "c3_bkg_psi2s", 5.91313e-02, -0.07, 0.07);
    RooChebychev bkg_psi2s_Fcn("bkg_psi2s_Fcn", "bkg_psi2s_Fcn", psi2s_mass, RooArgList(c1_bkg_psi2s, c2_bkg_psi2s, c3_bkg_psi2s));

    RooRealVar c1_bkg_jpsi("c1_bkg_jpsi", "c1_bkg_jpsi", -1.59346e-01, -1, 1);
    RooRealVar c2_bkg_jpsi("c2_bkg_jpsi", "c2_bkg_jpsi", 1.16489e-01, -0.5, 0.5);
    RooChebychev bkg_jpsi_Fcn("bkg_jpsi_Fcn", "bkg_jpsi_Fcn", jpsi_mass, RooArgList(c1_bkg_jpsi, c2_bkg_jpsi));

    // two dimension pdf
    RooProdPdf psi2s_jpsi_Pdf("psi2s_jpsi_Pdf", "psi2s_jpsi_Pdf", psi2s_double_CB_Fcn, jpsi_double_CB_Fcn);
    RooProdPdf psi2s_bkg2_Pdf("psi2s_bkg2_Pdf", "psi2s_bkg2_Pdf", psi2s_double_CB_Fcn, bkg_jpsi_Fcn);
    RooProdPdf bkg1_jpsi_Pdf("bkg1_jpsi_Pdf", "bkg1_jpsi_Pdf", bkg_psi2s_Fcn, jpsi_double_CB_Fcn);
    RooProdPdf bkg1_bkg2_Pdf("bkg1_bkg2_Pdf", "bkg1_bkg2_Pdf", bkg_psi2s_Fcn, bkg_jpsi_Fcn);

    RooRealVar n_psi2s_jpsi("n_psi2s_jpsi", "n_psi2s_jpsi", 0, 0, 1000000);
    RooRealVar n_psi2s_bkg2("n_psi2s_bkg2", "n_psi2s_bkg2", 0, 0, 1000000);
    RooRealVar n_bkg1_jpsi("n_bkg1_jpsi", "n_bkg1_jpsi", 20000, 0, 1000000);
    RooRealVar n_bkg1_bkg2("n_bkg1_bkg2", "n_bkg1_bkg2", 20000, 0, 1000000);

    RooAddPdf totalPdf("totalPdf", "totalPdf",
                       RooArgList(psi2s_jpsi_Pdf, psi2s_bkg2_Pdf, bkg1_jpsi_Pdf, bkg1_bkg2_Pdf),
                       RooArgList(n_psi2s_jpsi, n_psi2s_bkg2, n_bkg1_jpsi, n_bkg1_bkg2));

    sigmaCB1_jpsi.setConstant(kTRUE);
    sigmaCB1_psi2s.setConstant(kTRUE);
    sigmaCB2_jpsi.setConstant(kTRUE);
    sigmaCB2_psi2s.setConstant(kTRUE);
    meanCB1_psi2s.setConstant(kTRUE);

    double tem = 1.35819e-01;
    double Data_edm;
    int Data_status, Data_covQual;
    RooFitResult *fitRes;
    unsigned int ii = 0;
    while (true)
    {
        
        c1_bkg_psi2s.setVal(tem);
        fitRes = totalPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));
        Data_edm = fitRes->edm();
        Data_status = fitRes->status();
        Data_covQual = fitRes->covQual();
        if ((Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3) || ii > 100)
        {
            break;
        }
        tem += 0.0001;
	ii++;
    }

    // double x1min = 3.6861 - 0.01 * 3; // psi2s mean massErr 10 MeV, 3 mass window
    // double x1max = 3.6861 + 0.01 * 3;
    // double x2min = 3.0969 - 0.03 * 3; // jpsi mean massErr 30 MeV, 3 mass window
    // double x2max = 3.0969 + 0.03 * 3;
    double x1min = psi2s_mass_Min; // psi2s mean massErr 10 MeV, 3 mass window
    double x1max = psi2s_mass_Max;
    double x2min = jpsi_mass_Min; // jpsi mean massErr 30 MeV, 3 mass window
    double x2max = jpsi_mass_Max;
    psi2s_mass.setRange("signal1", x1min, x1max);
    jpsi_mass.setRange("signal2", x2min, x2max);
    double areabkg1limit = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("signal1"))->getVal();
    double areabkg2limit = bkg_jpsi_Fcn.createIntegral(RooArgSet(jpsi_mass), Range("signal2"))->getVal();
    double areapsi2slimit = psi2s_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("signal1"))->getVal();
    double areajpsilimit = jpsi_double_CB_Fcn.createIntegral(RooArgSet(jpsi_mass), Range("signal2"))->getVal();

    double areabkg1total = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal();
    double areabkg2total = bkg_jpsi_Fcn.createIntegral(RooArgSet(jpsi_mass))->getVal();
    double areapsi2stotal = psi2s_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal();
    double areajpsitotal = jpsi_double_CB_Fcn.createIntegral(RooArgSet(jpsi_mass))->getVal();

    double fraclimitbkg1 = areabkg1limit / areabkg1total;
    double fraclimitbkg2 = areabkg2limit / areabkg2total;
    double fraclimitpsi2s = areapsi2slimit / areapsi2stotal;
    double fraclimitjpsi = areajpsilimit / areajpsitotal;
    double fraclimitbkg1jpsi = fraclimitbkg1 * fraclimitjpsi;
    double fraclimitpsi2sbkg2 = fraclimitpsi2s * fraclimitbkg2;
    double fraclimitbkg1bkg2 = fraclimitbkg1 * fraclimitbkg2;

   cout << "fraclimitbkg1jpsi:" << fraclimitbkg1jpsi << endl;
   cout << "fraclimitpsi2sbkg2:" << fraclimitpsi2sbkg2 << endl;
   cout << "fraclimitbkg1bkg2:" << fraclimitbkg1bkg2 << endl;
   cout << "fraclimitbkg1:" << fraclimitbkg1 << endl;
   cout << "fraclimitbkg2:" << fraclimitbkg2 << endl;
   cout << "fraclimitpsi2s:" << fraclimitpsi2s << endl;
   cout << "fraclimitjpsi:" << fraclimitjpsi << endl;

    // getntotal
    double nbkg1jpsiTotal = n_bkg1_jpsi.getVal();
    double npsi2sbkg2Total = n_psi2s_bkg2.getVal();
    double nbkg1bkg2Total = n_bkg1_bkg2.getVal();

   cout << "nbkg1jpsiTotal:" << nbkg1jpsiTotal << endl;
   cout << "npsi2sbkg2Total:" << npsi2sbkg2Total << endl;
   cout << "nbkg1bkg2Total:" << nbkg1bkg2Total << endl;

    // getnlimit
    double nbkg1jpsilimit = nbkg1jpsiTotal * fraclimitbkg1jpsi;
    double npsi2sbkg2limit = npsi2sbkg2Total * fraclimitpsi2sbkg2;
    double nbkg1bkg2limit = nbkg1bkg2Total * fraclimitbkg1bkg2;

   cout << "nbkg1jpsilimit:" << nbkg1jpsilimit << endl;
   cout << "npsi2sbkg2limit:" << npsi2sbkg2limit << endl;
   cout << "nbkg1bkg2limit:" << nbkg1bkg2limit << endl;

    double Ncomall = nbkg1jpsilimit + npsi2sbkg2limit + nbkg1bkg2limit;
    cout << "Ncomall(3 num bkg) after 3 sigma=" << Ncomall << endl;

    psi2s_mass.setRange("signal", x1min, x1max);
    jpsi_mass.setRange("signal", x2min, x2max);
    double areapsi2sjpsilimit = psi2s_jpsi_Pdf.createIntegral(RooArgSet(psi2s_mass, jpsi_mass), Range("signal"))->getVal();
    double areapsi2sjpsitotal = psi2s_jpsi_Pdf.createIntegral(RooArgSet(psi2s_mass, jpsi_mass))->getVal();
    double fraclimitpsi2sjpsi = areapsi2sjpsilimit / areapsi2sjpsitotal;
    double npsi2sjpsiTotal = n_psi2s_jpsi.getVal();
    double npsi2sjpsilimit = npsi2sjpsiTotal * fraclimitpsi2sjpsi;
    double myBfromData = Ncomall;
    double mySfromData = npsi2sjpsilimit;

    cout << "mySfromData = " << mySfromData << endl;
    cout << "npsi2sjpsiTotal=" << npsi2sjpsiTotal << endl;
    cout << "myBfromData = " << myBfromData << endl;

    cout << "Data_edm = " << Data_edm << endl;
    cout << "Data_status = " << Data_status << endl;
    cout << "Data_covQual = " << Data_covQual << endl;
    myresult myroofitresult;
    myroofitresult.merit = mySfromData / sqrt(myBfromData + mySfromData);
    myroofitresult.myBfromData = myBfromData;
    myroofitresult.mySfromData = mySfromData;
    myroofitresult.tem = tem;
    if (Data_edm < 0.1 && Data_status == 0 && Data_covQual == 3)
    {
        myroofitresult.fitquality = 1;
    }
    

    
    if(isDraw)
    {
        TCanvas *Resultc = new TCanvas("Resultc", "Resultc", 1500, 600);
        Resultc->Divide(2,1);
    	RooPlot* myframe = psi2s_mass.frame();
        Resultc->cd(1);
    	data->plotOn(myframe);
    	totalPdf.plotOn(myframe, LineColor(kBlack));
        totalPdf.plotOn(myframe, Components("psi2s_jpsi_Pdf, psi2s_jpsi_Pdf"), LineColor(kRed));
        myframe->Draw();
        Resultc->cd(2);
        RooPlot* myframe2 = jpsi_mass.frame();
        data->plotOn(myframe2);
        totalPdf.plotOn(myframe2, LineColor(kBlack));
        totalPdf.plotOn(myframe2, Components("psi2s_jpsi_Pdf, psi2s_jpsi_Pdf"), LineColor(kRed));
    	myframe2->Draw();
        Resultc->SaveAs("result/fitdata2D.png");

    }
    ii = 0;

    return myroofitresult;
}


myresult fitData2D2peak(RooDataSet *data, bool isDraw = false)
{

    double distance = 3.872-3.68619;
    RooRealVar dist("dist", "dist", distance, 0.15, 0.25);
    dist.setConstant(kTRUE);

    //psi2s peak
    RooRealVar meanCB1_psi2s("meanCB1_psi2s", "meanCB1_psi2s", 3.68619e+00, 3.682, 3.688);
    RooRealVar sigmaCB1_psi2s("sigmaCB1_psi2s", "sigmaCB1_psi2s", 9.59592e-03, 0., 0.01);
    RooRealVar nCB1_psi2s("nCB1_psi2s", "nCB1_psi2s", 1.99999e+01);
    RooRealVar alphaCB1_psi2s("alphaCB1_psi2s", "alphaCB1_psi2s", 1.99999e+00);
    RooCBShape CB1_psi2s("CB1_psi2s", "CB1_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB1_psi2s, alphaCB1_psi2s, nCB1_psi2s);

    RooRealVar sigmaCB2_psi2s("sigmaCB2_psi2s", "sigmaCB2_psi2s", 5.28500e-03, 0, 0.01);
    RooRealVar nCB2_psi2s("nCB2_psi2s", "nCB2_psi2s", 7.38216e-01);
    RooRealVar alphaCB2_psi2s("alphaCB2_psi2s", "alphaCB2_psi2s", 5.35155e+00);
    RooCBShape CB2_psi2s("CB2_psi2s", "CB2_psi2s", psi2s_mass,
                         meanCB1_psi2s, sigmaCB2_psi2s, alphaCB2_psi2s, nCB2_psi2s);

    RooRealVar fracCB1_psi2s("fracCB1_psi2s", "fracCB1_psi2s", 5.14370e-01);
    RooAddPdf psi2s_double_CB_Fcn("psi2s_double_CB_Fcn", "psi2s_double_CB_Fcn",
                                  RooArgList(CB1_psi2s, CB2_psi2s), fracCB1_psi2s);

    RooRealVar meanCB1_jpsi("meanCB1_jpsi", "meanCB1_jpsi", 3.09603065e+00, 3.05, 3.12);
    RooRealVar sigmaCB1_jpsi("sigmaCB1_jpsi", "sigmaCB1_jpsi", 3.03477e-02, 0., 0.1);
    RooRealVar nCB1_jpsi("nCB1_jpsi", "nCB1_jpsi", 9.99947e+00);
    RooRealVar alphaCB1_jpsi("alphaCB1_jpsi", "alphaCB1_jpsi", 1.40029e+00);
    RooCBShape CB1_jpsi("CB1_jpsi", "CB1_jpsi", jpsi_mass,
                        meanCB1_jpsi, sigmaCB1_jpsi, alphaCB1_jpsi, nCB1_jpsi);

    RooRealVar sigmaCB2_jpsi("sigmaCB2_jpsi", "sigmaCB2_jpsi", 6.89897e-02, 0., 0.1);
    RooRealVar nCB2_jpsi("nCB2_jpsi", "nCB2_jpsi", 3.75249e+00 /*,0,10*/);
    RooRealVar alphaCB2_jpsi("alphaCB2_jpsi", "alphaCB2_jpsi", -4.41544e+00 /*,-5,5*/);
    RooCBShape CB2_jpsi("CB2_jpsi", "CB2_jpsi", jpsi_mass,
                        meanCB1_jpsi, sigmaCB2_jpsi, alphaCB2_jpsi, nCB2_jpsi);

    RooRealVar fracCB1_jpsi("fracCB1_jpsi", "fracCB1_jpsi", 5.59735e-01);
    RooAddPdf jpsi_double_CB_Fcn("jpsi_double_CB_Fcn", "jpsi_double_CB_Fcn",
                                 RooArgList(CB1_jpsi, CB2_jpsi), fracCB1_jpsi);

    //bkg pdf

    RooRealVar c1_bkg_psi2s("c1_bkg_psi2s", "c1_bkg_psi2s", 1.35819e-01, -0.8, 0.8);
    RooRealVar c2_bkg_psi2s("c2_bkg_psi2s", "c2_bkg_psi2s", -4.91313e-02, -0.6, 0.6);
    RooRealVar c3_bkg_psi2s("c3_bkg_psi2s", "c3_bkg_psi2s", 5.91313e-02, -0.07, 0.07);
    RooChebychev bkg_psi2s_Fcn("bkg_psi2s_Fcn", "bkg_psi2s_Fcn", psi2s_mass, RooArgList(c1_bkg_psi2s, c2_bkg_psi2s, c3_bkg_psi2s));

    RooRealVar c1_bkg_jpsi("c1_bkg_jpsi", "c1_bkg_jpsi", -1.59346e-01, -1, 1);
    RooRealVar c2_bkg_jpsi("c2_bkg_jpsi", "c2_bkg_jpsi", 1.16489e-01, -0.5, 0.5);
    RooChebychev bkg_jpsi_Fcn("bkg_jpsi_Fcn", "bkg_jpsi_Fcn", jpsi_mass, RooArgList(c1_bkg_jpsi, c2_bkg_jpsi));

    //X3872 peak sig
    RooFormulaVar meanCB1_X_psi2s("meanCB1_X_psi2s", "meanCB1_psi2s+dist", RooArgList(meanCB1_psi2s,dist));
    RooRealVar sigmaCB1_X_psi2s("sigmaCB1_X_psi2s", "sigmaCB1_X_psi2s", 9.59592e-03, 0., 0.01);
    RooRealVar nCB1_X_psi2s("nCB1_X_psi2s", "nCB1_X_psi2s", 1.99999e+01);
    RooRealVar alphaCB1_X_psi2s("alphaCB1_X_psi2s", "alphaCB1_X_psi2s", 1.99999e+00);
    RooCBShape CB1_X_psi2s("CB1_X_psi2s", "CB1_X_psi2s", psi2s_mass,
                         meanCB1_X_psi2s, sigmaCB1_X_psi2s, alphaCB1_X_psi2s, nCB1_X_psi2s);

    RooRealVar sigmaCB2_X_psi2s("sigmaCB2_X_psi2s", "sigmaCB2_X_psi2s", 5.28500e-03, 0, 0.01);
    RooRealVar nCB2_X_psi2s("nCB2_X_psi2s", "nCB2_X_psi2s", 7.38216e-01);
    RooRealVar alphaCB2_X_psi2s("alphaCB2_X_psi2s", "alphaCB2_X_psi2s", 5.35155e+00);
    RooCBShape CB2_X_psi2s("CB2_X_psi2s", "CB2_X_psi2s", psi2s_mass,
                         meanCB1_X_psi2s, sigmaCB2_X_psi2s, alphaCB2_X_psi2s, nCB2_X_psi2s);

    RooRealVar fracCB1_X_psi2s("fracCB1_X_psi2s", "fracCB1_X_psi2s", 5.14370e-01);
    RooAddPdf X_double_CB_Fcn_psi2s("X_double_CB_Fcn_psi2s", "X_double_CB_Fcn_psi2s",
                                  RooArgList(CB1_X_psi2s, CB2_X_psi2s), fracCB1_X_psi2s);

    // two dimension pdf
    RooProdPdf psi2s_jpsi_Pdf("psi2s_jpsi_Pdf", "psi2s_jpsi_Pdf", psi2s_double_CB_Fcn, jpsi_double_CB_Fcn);
    RooProdPdf psi2s_bkg2_Pdf("psi2s_bkg2_Pdf", "psi2s_bkg2_Pdf", psi2s_double_CB_Fcn, bkg_jpsi_Fcn);
    RooProdPdf X_jpsi_Pdf("X_jpsi_Pdf", "X_jpsi_Pdf", X_double_CB_Fcn_psi2s, jpsi_double_CB_Fcn);
    RooProdPdf X_bkg2_Pdf("X_bkg2_Pdf", "X_bkg2_Pdf", X_double_CB_Fcn_psi2s, bkg_jpsi_Fcn);
    RooProdPdf bkg1_jpsi_Pdf("bkg1_jpsi_Pdf", "bkg1_jpsi_Pdf", bkg_psi2s_Fcn, jpsi_double_CB_Fcn);
    RooProdPdf bkg1_bkg2_Pdf("bkg1_bkg2_Pdf", "bkg1_bkg2_Pdf", bkg_psi2s_Fcn, bkg_jpsi_Fcn);

    RooRealVar n_psi2s_jpsi("n_psi2s_jpsi", "n_psi2s_jpsi", 0, 0, 20000);
    RooRealVar n_psi2s_bkg2("n_psi2s_bkg2", "n_psi2s_bkg2", 0, 0, 20000);
    RooRealVar n_X_jpsi("n_X_jpsi", "n_X_jpsi", 0, 0, 20000);
    RooRealVar n_X_bkg2("n_X_bkg2", "n_X_bkg2", 0, 0, 20000);
    RooRealVar n_bkg1_jpsi("n_bkg1_jpsi", "n_bkg1_jpsi", 20000, 0, 200000);
    RooRealVar n_bkg1_bkg2("n_bkg1_bkg2", "n_bkg1_bkg2", 20000, 0, 200000);

    RooAddPdf totalPdf("totalPdf", "totalPdf",
                       RooArgList(psi2s_jpsi_Pdf, psi2s_bkg2_Pdf, X_jpsi_Pdf, X_bkg2_Pdf, bkg1_jpsi_Pdf, bkg1_bkg2_Pdf),
                       RooArgList(n_psi2s_jpsi, n_psi2s_bkg2, n_X_jpsi, n_X_bkg2, n_bkg1_jpsi, n_bkg1_bkg2));


/*
    sigmaCB1_jpsi.setConstant(kTRUE);
    sigmaCB1_psi2s.setConstant(kTRUE);
    sigmaCB2_jpsi.setConstant(kTRUE);
    sigmaCB2_psi2s.setConstant(kTRUE);
    sigmaCB1_X_psi2s.setConstant(kTRUE);
    sigmaCB2_X_psi2s.setConstant(kTRUE);
*/
    //meanCB1_psi2s.setConstant(kTRUE);

    double tem = 1.35819e-01;
    double Data_edm;
    int Data_status, Data_covQual;
    RooFitResult *fitRes;
    unsigned int ii = 0;
    while (true)
    {
        c1_bkg_psi2s.setVal(tem);
        fitRes = totalPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));
        Data_edm = fitRes->edm();
        Data_status = fitRes->status();
        Data_covQual = fitRes->covQual();
        if ((Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3) || ii > 10)
        {
            break;
        }
        tem += 0.0001;
	ii++;
    }

    double mean_X = meanCB1_X_psi2s.getVal();
    cout << "mean_X:" << mean_X <<endl;

    // double x1min = 3.6861 - 0.01 * 3; // psi2s mean massErr 10 MeV, 3 mass window
    // double x1max = 3.6861 + 0.01 * 3;
    // double x2min = 3.0969 - 0.03 * 3; // jpsi mean massErr 30 MeV, 3 mass window
    // double x2max = 3.0969 + 0.03 * 3;
    double x1min = psi2s_mass_Min; // psi2s mean massErr 10 MeV, 3 mass window
    double x1max = psi2s_mass_Max;
    double x2min = jpsi_mass_Min; // jpsi mean massErr 30 MeV, 3 mass window
    double x2max = jpsi_mass_Max;
    psi2s_mass.setRange("signal1", x1min, x1max);
    jpsi_mass.setRange("signal2", x2min, x2max);
    double areabkg1limit = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("signal1"))->getVal();
    double areabkg2limit = bkg_jpsi_Fcn.createIntegral(RooArgSet(jpsi_mass), Range("signal2"))->getVal();
    double areapsi2slimit = psi2s_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass), Range("signal1"))->getVal();
    double areajpsilimit = jpsi_double_CB_Fcn.createIntegral(RooArgSet(jpsi_mass), Range("signal2"))->getVal();

    double areabkg1total = bkg_psi2s_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal();
    double areabkg2total = bkg_jpsi_Fcn.createIntegral(RooArgSet(jpsi_mass))->getVal();
    double areapsi2stotal = psi2s_double_CB_Fcn.createIntegral(RooArgSet(psi2s_mass))->getVal();
    double areajpsitotal = jpsi_double_CB_Fcn.createIntegral(RooArgSet(jpsi_mass))->getVal();

    double fraclimitbkg1 = areabkg1limit / areabkg1total;
    double fraclimitbkg2 = areabkg2limit / areabkg2total;
    double fraclimitpsi2s = areapsi2slimit / areapsi2stotal;
    double fraclimitjpsi = areajpsilimit / areajpsitotal;
    double fraclimitbkg1jpsi = fraclimitbkg1 * fraclimitjpsi;
    double fraclimitpsi2sbkg2 = fraclimitpsi2s * fraclimitbkg2;
    double fraclimitbkg1bkg2 = fraclimitbkg1 * fraclimitbkg2;

   cout << "fraclimitbkg1jpsi:" << fraclimitbkg1jpsi << endl;
   cout << "fraclimitpsi2sbkg2:" << fraclimitpsi2sbkg2 << endl;
   cout << "fraclimitbkg1bkg2:" << fraclimitbkg1bkg2 << endl;
   cout << "fraclimitbkg1:" << fraclimitbkg1 << endl;
   cout << "fraclimitbkg2:" << fraclimitbkg2 << endl;
   cout << "fraclimitpsi2s:" << fraclimitpsi2s << endl;
   cout << "fraclimitjpsi:" << fraclimitjpsi << endl;

    // getntotal
    double nbkg1jpsiTotal = n_bkg1_jpsi.getVal();
    double npsi2sbkg2Total = n_psi2s_bkg2.getVal();
    double nbkg1bkg2Total = n_bkg1_bkg2.getVal();
    double nXjpsiTotal = n_X_jpsi.getVal();

   cout << "nbkg1jpsiTotal:" << nbkg1jpsiTotal << endl;
   cout << "npsi2sbkg2Total:" << npsi2sbkg2Total << endl;
   cout << "nbkg1bkg2Total:" << nbkg1bkg2Total << endl;
   cout << "nXjpsiTotal:" << nXjpsiTotal << endl;

    // getnlimit
    double nbkg1jpsilimit = nbkg1jpsiTotal * fraclimitbkg1jpsi;
    double npsi2sbkg2limit = npsi2sbkg2Total * fraclimitpsi2sbkg2;
    double nbkg1bkg2limit = nbkg1bkg2Total * fraclimitbkg1bkg2;

   cout << "nbkg1jpsilimit:" << nbkg1jpsilimit << endl;
   cout << "npsi2sbkg2limit:" << npsi2sbkg2limit << endl;
   cout << "nbkg1bkg2limit:" << nbkg1bkg2limit << endl;

    double Ncomall = nbkg1jpsilimit + npsi2sbkg2limit + nbkg1bkg2limit;
    cout << "Ncomall(3 num bkg) after 3 sigma=" << Ncomall << endl;

    psi2s_mass.setRange("signal", x1min, x1max);
    jpsi_mass.setRange("signal", x2min, x2max);
    double areapsi2sjpsilimit = psi2s_jpsi_Pdf.createIntegral(RooArgSet(psi2s_mass, jpsi_mass), Range("signal"))->getVal();
    double areapsi2sjpsitotal = psi2s_jpsi_Pdf.createIntegral(RooArgSet(psi2s_mass, jpsi_mass))->getVal();
    double fraclimitpsi2sjpsi = areapsi2sjpsilimit / areapsi2sjpsitotal;
    double npsi2sjpsiTotal = n_psi2s_jpsi.getVal();
    double npsi2sjpsilimit = npsi2sjpsiTotal * fraclimitpsi2sjpsi;
    double myBfromData = Ncomall;
    double mySfromData = npsi2sjpsilimit;

    cout << "mySfromData = " << mySfromData << endl;
    cout << "myBfromData = " << myBfromData << endl;

    cout << "Data_edm = " << Data_edm << endl;
    cout << "Data_status = " << Data_status << endl;
    cout << "Data_covQual = " << Data_covQual << endl;
    myresult myroofitresult;
    myroofitresult.merit = mySfromData / sqrt(myBfromData + mySfromData);
    myroofitresult.myBfromData = myBfromData;
    myroofitresult.mySfromData = mySfromData;
    myroofitresult.tem = tem;
    if (Data_edm < 0.1 && Data_status == 0 && Data_covQual == 3)
    {
        myroofitresult.fitquality = 1;
    }

    if(isDraw)
    {
        TCanvas *Resultc = new TCanvas("Resultc", "Resultc", 1500, 600);
        Resultc->Divide(2,1);
    	RooPlot* myframe = psi2s_mass.frame();
        
        Resultc->cd(1);
    	data->plotOn(myframe);
    	totalPdf.plotOn(myframe, LineColor(kBlack));
        totalPdf.plotOn(myframe, Components("psi2s_jpsi_Pdf"), LineColor(kRed));
        totalPdf.plotOn(myframe, Components("X_jpsi_Pdf"), LineColor(kBlue));
        myframe->Draw();
        Resultc->cd(2);
        RooPlot* myframe2 = jpsi_mass.frame();
        data->plotOn(myframe2);
        totalPdf.plotOn(myframe2, LineColor(kBlack));
        totalPdf.plotOn(myframe2, Components("psi2s_jpsi_Pdf, psi2s_jpsi_Pdf"), LineColor(kRed));
        totalPdf.plotOn(myframe2, Components("X_jpsi_Pdf"), LineColor(kBlue));
    	myframe2->Draw();
        Resultc->SaveAs("result/fitdata2D2peak.png");
    }
    ii = 0;

    return myroofitresult;
}

myresult fitjpsi1(RooDataSet *data, bool isDraw = false)
{
    RooRealVar meanCB1_jpsi("meanCB1_jpsi", "meanCB1_jpsi", 3.09603065e+00, 3.05, 3.12);
    RooRealVar sigmaCB1_jpsi("sigmaCB1_jpsi", "sigmaCB1_jpsi", 3.03477e-02, 0., 0.1);
    RooRealVar nCB1_jpsi("nCB1_jpsi", "nCB1_jpsi", 9.99947e+00);
    RooRealVar alphaCB1_jpsi("alphaCB1_jpsi", "alphaCB1_jpsi", 1.40029e+00);
    RooCBShape CB1_jpsi("CB1_jpsi", "CB1_jpsi", jpsi_mass1,
                        meanCB1_jpsi, sigmaCB1_jpsi, alphaCB1_jpsi, nCB1_jpsi);

    RooRealVar sigmaCB2_jpsi("sigmaCB2_jpsi", "sigmaCB2_jpsi", 6.89897e-02, 0., 0.1);
    RooRealVar nCB2_jpsi("nCB2_jpsi", "nCB2_jpsi", 3.75249e+00 /*,0,10*/);
    RooRealVar alphaCB2_jpsi("alphaCB2_jpsi", "alphaCB2_jpsi", -4.41544e+00 /*,-5,5*/);
    RooCBShape CB2_jpsi("CB2_jpsi", "CB2_jpsi", jpsi_mass1,
                        meanCB1_jpsi, sigmaCB2_jpsi, alphaCB2_jpsi, nCB2_jpsi);

    RooRealVar fracCB1_jpsi("fracCB1_jpsi", "fracCB1_jpsi", 5.59735e-01);
    RooAddPdf jpsi_double_CB_Fcn("jpsi_double_CB_Fcn", "jpsi_double_CB_Fcn",
                                 RooArgList(CB1_jpsi, CB2_jpsi), fracCB1_jpsi);

    RooRealVar c1_bkg_jpsi("c1_bkg_jpsi", "c1_bkg_jpsi", 1.35819e-01, -0.8, 0.8);
    RooRealVar c2_bkg_jpsi("c2_bkg_jpsi", "c2_bkg_jpsi", -4.91313e-02, -0.6, 0.6);
    RooRealVar c3_bkg_jpsi("c3_bkg_jpsi", "c3_bkg_jpsi", 5.91313e-02, -0.07, 0.07);
    RooChebychev bkg_jpsi_Fcn("bkg_jpsi_Fcn", "bkg_jpsi_Fcn", jpsi_mass1, RooArgList(c1_bkg_jpsi, c2_bkg_jpsi, c3_bkg_jpsi));


    RooRealVar n_jpsi("n_jpsi", "n_jpsi", 0, 0, 100000);
    RooRealVar n_bkg_jpsi("n_bkg_jpsi", "n_bkg_jpsi", 1000, 0, 100000);

    RooAddPdf totalPdf("totalPdf", "totalPdf", RooArgList(jpsi_double_CB_Fcn, bkg_jpsi_Fcn), RooArgList(n_jpsi, n_bkg_jpsi));

        double tem = 1.35819e-01;
    double Data_edm;
    int Data_status, Data_covQual;
    RooFitResult *fitRes;
    unsigned int ii = 0;
    while (true)
    {
        c1_bkg_jpsi.setVal(tem);
        fitRes = totalPdf.fitTo(*data, Hesse(kTRUE), Strategy(2), NumCPU(8), Save(kTRUE), Minos(kFALSE), PrintLevel(-1), Warnings(-1), PrintEvalErrors(-1));//Fit total PDF
        Data_edm = fitRes->edm();
        Data_status = fitRes->status();
        Data_covQual = fitRes->covQual();
	ii = ii + 1;
        if ((Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3) || ii >= 100)
        {
            break;
        }
        tem += 0.0001;
    }

    // double x1min = 3.6861 - 0.01 * 3; // psi2s mean massErr 10 MeV, 3 mass window
    // double x1max = 3.6861 + 0.01 * 3;
    // double x2min = 3.0969 - 0.03 * 3; // jpsi mean massErr 30 MeV, 3 mass window
    // double x2max = 3.0969 + 0.03 * 3;
    double x1min = jpsi_mass_Min; // psi2s mean massErr 10 MeV, 3 mass window
    double x1max = jpsi_mass_Max;
    jpsi_mass1.setRange("massPeak", x1min, x1max);

    // only consider events under psi2s mass peak

    double areabkglimit = bkg_jpsi_Fcn.createIntegral(RooArgSet(jpsi_mass), Range("massPeak"))->getVal(); 
    double areasiglimit = jpsi_double_CB_Fcn.createIntegral(RooArgSet(jpsi_mass), Range("massPeak"))->getVal();

    double areabkgtotal = bkg_jpsi_Fcn.createIntegral(RooArgSet(jpsi_mass))->getVal();
    double areasigtotal = jpsi_double_CB_Fcn.createIntegral(RooArgSet(jpsi_mass))->getVal(); 

    // Compute fraction of events under range of the mass peak, that is the fanal S/B is the result under the peak
    double fraclimitbkg = areabkglimit / areabkgtotal;
    double fraclimitsig = areasiglimit / areasigtotal;

    cout << "fraclimitbkg: " << fraclimitbkg << endl;
    cout << "fraclimitsig: " << fraclimitsig << endl;

    // getntotal
    double nbkgTotal = n_bkg_jpsi.getVal();
    double nsigTotal = n_jpsi.getVal();

    cout << "nbkgTotal: " << nbkgTotal << endl;
    cout << "nsigTotal:" << nsigTotal << endl;

    // getnlimit
    double nbkglimit = nbkgTotal * fraclimitbkg;
    double nsiglimit = nsigTotal * fraclimitsig;

    cout << "nbkglimit:" << nbkglimit << endl;
    cout << "nsiglimit:" << nsiglimit << endl;

    double myBfromData = nbkglimit;
    double mySfromData = nsiglimit;

    cout << "mySfromData = " << mySfromData << endl;
    cout << "myBfromData = " << myBfromData << endl;

    cout << "Data_edm = " << Data_edm << endl;
    cout << "Data_status = " << Data_status << endl;
    cout << "Data_covQual = " << Data_covQual << endl;
    myresult myroofitresult;
    myroofitresult.merit = mySfromData / sqrt(myBfromData + mySfromData);
    myroofitresult.myBfromData = myBfromData;
    myroofitresult.mySfromData = mySfromData;
    myroofitresult.tem = tem;
    if (Data_edm < 0.01 && Data_status == 0 && Data_covQual == 3)
    {
        myroofitresult.fitquality = 1;
    }
    // Draw a graph if isDraw is true
    if(isDraw)
    {
        TCanvas *Resultc = new TCanvas("Resultc", "Resultc", 1);
    	RooPlot *myframe = jpsi_mass1.frame();
    	data->plotOn(myframe);
    	totalPdf.plotOn(myframe,Components(bkg_jpsi_Fcn) ,LineStyle(kDashed),LineColor(kBlue)); 
        totalPdf.plotOn(myframe,Components(jpsi_double_CB_Fcn) ,LineColor(kRed)); 
        totalPdf.plotOn(myframe,LineColor(kBlue)); 
    	myframe->Draw();
        Resultc->SaveAs("result/fitjpsi1.png");
    }
    ii = 0;
    return myroofitresult;
}


#endif
