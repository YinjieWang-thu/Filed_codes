#ifndef VAR_HH
#define VAR_HH 1
int stepnum = 25; // how many points to plot

// Mass range of psi2s_mass, which is final mass target
// float psi2s_mass_Min = 3.68, psi2s_mass_Max = 3.70;// Mass peak range
   float psi2s_mass_Min = 3.60, psi2s_mass_Max = 3.80;
   float jpsi_mass_Min = 2.8, jpsi_mass_Max = 3.4;


// Set all cut variables
// RooReaVar("name", "title", min, max) (primary value is the mid point of the range)

// Variable definations here
RooRealVar psi2s_mass("psi2s_mass", "M(#mu#mu#pi#pi)-M(#mu#mu)+3.0969 GeV", psi2s_mass_Min, psi2s_mass_Max);
RooRealVar jpsi_mass("jpsi_mass", "M(#mu#mu) GeV", jpsi_mass_Min, jpsi_mass_Max);
RooRealVar jpsi_mass1("jpsi_mass1", "M(#mu1#mu2) GeV", jpsi_mass_Min, jpsi_mass_Max);// only used in 2D fit, if use 1D, please delete this line
#endif
const double MuJpsiRes_Min = 1;
const double MuJpsiRes_Max = 5;
const double MuJpsiRes_MaxOpt = 5;
const double MuJpsiRes_MinOpt = 0;
RooRealVar MuJpsiRes("MuJpsiRes", "MuJpsiRes", MuJpsiRes_Min, MuJpsiRes_Max);

const double MuonD0_Min = 0;
const double MuonD0_Max = 0.0787;
const double MuonD0_MaxOpt = 0.1;
const double MuonD0_MinOpt = 0;
RooRealVar MuonD0("MuonD0", "MuonD0", MuonD0_Min, MuonD0_Max);
RooRealVar MuonD02("MuonD02", "MuonD02", MuonD0_Min, MuonD0_Max);
RooRealVar MuonD03("MuonD03", "MuonD03", MuonD0_Min, MuonD0_Max);
RooRealVar MuonD04("MuonD04", "MuonD04", MuonD0_Min, MuonD0_Max);

const double MuonIso_Min = 0;
const double MuonIso_Max = 14.52;
const double MuonIso_MaxOpt = 16;
const double MuonIso_MinOpt = 13;
RooRealVar MuonIso("MuonIso", "MuonIso", MuonIso_Min, MuonIso_Max);
RooRealVar MuonIso2("MuonIso2", "MuonIso2", MuonIso_Min, MuonIso_Max);
RooRealVar MuonIso3("MuonIso3", "MuonIso3", MuonIso_Min, MuonIso_Max);
RooRealVar MuonIso4("MuonIso4", "MuonIso4", MuonIso_Min, MuonIso_Max);

const double Dpipi_Min = 0.21625;
const double Dpipi_Max = 0.7;
const double Dpipi_MaxOpt = 0.2;
const double Dpipi_MinOpt = 0.7;
RooRealVar Dpipi("Dpipi", "Dpipi", Dpipi_Min, Dpipi_Max);

const double Dpsi2smu_Min = 0;
const double Dpsi2smu_Max = 0.808;//conf
const double Dpsi2smu_MaxOpt = 1;
const double Dpsi2smu_MinOpt = 0.8;
RooRealVar Dpsi2smu("Dpsi2smu", "Dpsi2smu", Dpsi2smu_Min, Dpsi2smu_Max);
RooRealVar Dpsi2smu2("Dpsi2smu2", "Dpsi2smu2", Dpsi2smu_Min, Dpsi2smu_Max);
RooRealVar Dpsi2smu3("Dpsi2smu3", "Dpsi2smu3", 0, 40);
RooRealVar Dpsi2smu4("Dpsi2smu4", "Dpsi2smu4", 0, 40);

const double Dpsi2spi_Min = 0;
const double Dpsi2spi_Max = 0.6;//0.6
const double Dpsi2spi_MaxOpt = 0;
const double Dpsi2spi_MinOpt = 0.6;
RooRealVar Dpsi2spi("Dpsi2spi", "Dpsi2spi", Dpsi2spi_Min, Dpsi2spi_Max);
RooRealVar Dpsi2spi2("Dpsi2spi2", "Dpsi2spi2", Dpsi2spi_Min, Dpsi2spi_Max);

const double Dpsi2sjpsi1_Min = 0;//0
const double Dpsi2sjpsi1_Max = 0.066;//0.125
const double Dpsi2sjpsi1_MaxOpt = 0.15;
const double Dpsi2sjpsi1_MinOpt = 0;
RooRealVar Dpsi2sjpsi1("Dpsi2sjpsi1", "Dpsi2sjpsi1", Dpsi2sjpsi1_Min, Dpsi2sjpsi1_Max);

const double Djpsimu_Min = 0;
const double Djpsimu_Max = 1;
const double Djpsimu_MaxOpt = 1;
const double Djpsimu_MinOpt = 0;
RooRealVar Djpsimu("Djpsimu", "Djpsimu", Djpsimu_Min, Djpsimu_Max);
RooRealVar Djpsimu2("Djpsimu2", "Djpsimu2", Djpsimu_Min, Djpsimu_Max);

const double XEta_Min = 0;
const double XEta_Max = 4;
const double XEta_MaxOpt = 4;
const double XEta_MinOpt = 0;
RooRealVar XEta("XEta", "XEta", XEta_Min, XEta_Max);

const double XPt_Min = 0;//conf
const double XPt_Max = 30;
const double XPt_MaxOpt = 10;
const double XPt_MinOpt = 0;
RooRealVar XPt("XPt", "XPt", XPt_Min, XPt_Max);

const double psi2sProb_Min = 0;//conf
const double psi2sProb_Max = 1;
const double psi2sProb_MaxOpt = 0.1;
const double psi2sProb_MinOpt = 0;
RooRealVar psi2sProb("psi2sProb", "psi2sProb", psi2sProb_Min, psi2sProb_Max);

const double psi2sEta_Min = 0;
const double psi2sEta_Max = 2.2;//2.2
const double psi2sEta_MaxOpt = 2.2;
const double psi2sEta_MinOpt = 0;
RooRealVar psi2sEta("psi2sEta", "psi2sEta", psi2sEta_Min, psi2sEta_Max);

const double psi2sPt_Min = 8.16;//conf
const double psi2sPt_Max = 30;
const double psi2sPt_MaxOpt = 20;
const double psi2sPt_MinOpt = 4;
RooRealVar psi2sPt("psi2sPt", "psi2sPt", psi2sPt_Min, psi2sPt_Max);

const double jpsi2Eta_Min = 0;
const double jpsi2Eta_Max = 1.92;//2.02
const double jpsi2Eta_MaxOpt = 2.2;
const double jpsi2Eta_MinOpt = 1.2;
RooRealVar jpsi2Eta("jpsi2Eta", "jpsi2Eta", jpsi2Eta_Min, jpsi2Eta_Max);

const double jpsi1Eta_Min = 0;
const double jpsi1Eta_Max = 2.2;//conf
const double jpsi1Eta_MaxOpt = 2.2;
const double jpsi1Eta_MinOpt = 1.2;
RooRealVar jpsi1Eta("jpsi1Eta", "jpsi1Eta", jpsi1Eta_Min, jpsi1Eta_Max);

const double jpsi2Pt_Min = 2.8;
const double jpsi2Pt_Max = 20;
const double jpsi2Pt_MaxOpt = 20;
const double jpsi2Pt_MinOpt = 0;
RooRealVar jpsi2Pt("jpsi2Pt", "jpsi2Pt", jpsi2Pt_Min, jpsi2Pt_Max);

const double jpsi1Pt_Min = 6;
const double jpsi1Pt_Max = 20;
const double jpsi1Pt_MaxOpt = 20;
const double jpsi1Pt_MinOpt = 0;
RooRealVar jpsi1Pt("jpsi1Pt", "jpsi1Pt", jpsi1Pt_Min, jpsi1Pt_Max);

const double MuEta_Min = 0;
const double MuEta_Max = 2.5;//2.5
const double MuEta_MaxOpt = 2.5;
const double MuEta_MinOpt = 1;
RooRealVar MuEta("MuEta", "MuEta", MuEta_Min, MuEta_Max);
RooRealVar MuEta2("MuEta2", "MuEta2", MuEta_Min, MuEta_Max);
RooRealVar MuEta3("MuEta3", "MuEta3", MuEta_Min, MuEta_Max);
RooRealVar MuEta4("MuEta4", "MuEta4", MuEta_Min, MuEta_Max);

const double MuPt_Min = 2;//2
const double MuPt_Max = 15;
const double MuPt_MaxOpt = 4;
const double MuPt_MinOpt = 2;
RooRealVar MuPt("MuPt", "MuPt", MuPt_Min, MuPt_Max);
RooRealVar MuPt2("MuPt2", "MuPt2", MuPt_Min, MuPt_Max);
RooRealVar MuPt3("MuPt3", "MuPt3", MuPt_Min, MuPt_Max);
RooRealVar MuPt4("MuPt4", "MuPt4", MuPt_Min, MuPt_Max);

const double PiEta_Min = 0;
const double PiEta_Max = 2.4;//3
const double PiEta_MaxOpt = 3;
const double PiEta_MinOpt = 1;
RooRealVar PiEta("PiEta", "PiEta", PiEta_Min, PiEta_Max);
RooRealVar PiEta2("PiEta2", "PiEta2", PiEta_Min, PiEta_Max);

const double PiPt_Min = 0.5;//0.5
const double PiPt_Max = 3;
const double PiPt_MaxOpt = 0.6;
const double PiPt_MinOpt = 0.5;
RooRealVar PiPt("PiPt", "PiPt", PiPt_Min, PiPt_Max);
RooRealVar PiPt2("PiPt2", "PiPt2", PiPt_Min, PiPt_Max);

/*
1 < MuJpsiRes < 5
0 < MuonD0 < 0.787
0 < MuonIso < 13.83
0.21625 < Dpipi < 0.7
0 < Dpsi2smu < 0.9
0 < Dpsi2spi < 0.6
0 < Dpsi2sjpsi1 < 0.15
0 < Djpsimu < 1
0 < XEta < 4
0 < XPt < 30
0 < psi2sProb < 1
0 < psi2sEta < 2.2
4 < psi2sPt < 30
0 < jpsi2Eta < 2.2
0 < jpsi1Eta < 2.2
0 < jpsi2Pt < 20
0 < jpsi1Pt < 20
0 < MuEta < 2.5
2 < MuPt < 15
0 < PiEta < 3
0.5 < PiPt < 3
*/