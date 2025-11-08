#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
using namespace std;
using namespace RooFit;

void test()
{
    TCanvas *c1 = new TCanvas("c1","c1");
    // Observable 
RooRealVar t("t","t",-10,30) ; 
// Theoretical model 
RooRealVar ml("ml","mean landau",5.782,-20,20) ; 
RooRealVar sl("sl","sigma landau",0.0004,0.1,10) ; 
RooGaussian landau("lx","lx",t,ml,sl) ; 
// Detector response function 
RooRealVar mg("mg","mg",0) ; 
RooRealVar sg("sg","sg",0.5,0.1,10) ; 
RooGaussian gauss("gauss","gauss",t,mg,sg) ; 
t.setBins(10000,"cache") ;
// Construct convolution 
RooFFTConvPdf lxg("lxg","landau (X) gauss",t,landau,gauss) ;

// Sample 1000 events in x from gxlx 
RooDataSet* data = lxg.generate(t,10000) ; 
// Fit gxlx to data 
lxg.fitTo(*data) ; 
// Plot data, fitted p.d.f 
RooPlot* frame = t.frame(Title("landau (x) gauss convolution")) ; 
data->plotOn(frame) ; 
lxg.plotOn(frame) ; 
landau.plotOn(frame,LineStyle(kDashed)) ;
frame->Draw();
cout<<ml.getVal()<<endl;
}