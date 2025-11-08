#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    	 float psi2s_mass;
         float jpsi_mass;
		 float jpsi_mass1;
         int MuJpsiRes; 
		 float MuonD0; 
		 float MuonD02; 
		 float MuonD03; 
		 float MuonD04; 
		 float MuonIso; 
		 float MuonIso2; 
		 float MuonIso3; 
		 float MuonIso4; 
		 float Dpipi; 
		 float Dpsi2smu; 
		 float Dpsi2smu2; 
		 float Dpsi2smu3; 
		 float Dpsi2smu4; 
		 float Dpsi2spi; 
		 float Dpsi2spi2; 
		 float Dpsi2sjpsi1; 
		 float Djpsimu; 
		 float Djpsimu2; 
		 float XEta; 
		 float XPt; 
		 float psi2sProb; 
		 float psi2sEta; 
		 float psi2sPt; 
		 float jpsi2Eta; 
		 float jpsi1Eta; 
		 float jpsi2Pt; 
		 float jpsi1Pt; 
		 float MuEta; 
		 float MuEta2; 
		 float MuEta3; 
		 float MuEta4; 
		 float MuPt; 
		 float MuPt2; 
		 float MuPt3; 
		 float MuPt4; 
		 float PiEta; 
		 float PiEta2; 
		 float PiPt; 
		 float PiPt2; 
    ifstream data;
    fstream file("data/result.txt", ios::out|ios::app);
    data.open("data/data.txt", ios::in);
    string temp;

    if(!data.is_open())
    {
        cout << "input open failed" << endl;
    }
    if(!file.is_open())
    {
        cout << "output open failed" << endl;
    }
    int i=0;
    while(getline(data,temp))
    {
        i++;
        sscanf(temp.c_str(),
        "%f %f %f %d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
         &psi2s_mass,
         &jpsi_mass,
		 &jpsi_mass1,
         &MuJpsiRes, 
		 &MuonD0, 
		 &MuonD02, 
		 &MuonD03, 
		 &MuonD04, 
		 &MuonIso, 
		 &MuonIso2, 
		 &MuonIso3, 
		 &MuonIso4, 
		 &Dpipi, 
		 &Dpsi2smu, 
		 &Dpsi2smu2, 
		 &Dpsi2smu3, 
		 &Dpsi2smu4, 
		 &Dpsi2spi, 
		 &Dpsi2spi2, 
		 &Dpsi2sjpsi1, 
		 &Djpsimu, 
		 &Djpsimu2, 
		 &XEta, 
		 &XPt, 
		 &psi2sProb, 
		 &psi2sEta, 
		 &psi2sPt, 
		 &jpsi2Eta, 
		 &jpsi1Eta, 
		 &jpsi2Pt, 
		 &jpsi1Pt, 
		 &MuEta, 
		 &MuEta2, 
		 &MuEta3, 
		 &MuEta4, 
		 &MuPt, 
		 &MuPt2, 
		 &MuPt3, 
		 &MuPt4, 
		 &PiEta, 
		 &PiEta2, 
		 &PiPt, 
		 &PiPt2);
        if(psi2s_mass > 3.6 && psi2s_mass < 3.95 &&
        jpsi_mass > 2.8 && jpsi_mass < 3.4 &&
		jpsi_mass1 > 2.8 && jpsi_mass1 < 3.4 &&
         MuJpsiRes >= 0 && MuJpsiRes <= 5 &&
		 MuonD0 >= 0 && MuonD0 < 0.1 &&
		 MuonD02 >= 0 && MuonD02 < 0.1 &&
		 MuonD03 >= 0 && MuonD03 < 0.1 &&
		 MuonD04 >= 0 && MuonD04 < 0.1 &&
		 MuonIso >= 0 && MuonIso < 15 &&
		 MuonIso2 >= 0 && MuonIso2 < 15 &&
		 MuonIso3 >= 0 && MuonIso3 < 15 &&
		 MuonIso4 >= 0 && MuonIso4 < 15 &&
		 Dpipi >= 0 && Dpipi < 0.7 &&
		 Dpsi2smu >= 0 && Dpsi2smu <= 1 &&
		 Dpsi2smu2 >= 0 && Dpsi2smu2 <= 1 &&
		 Dpsi2spi >= 0 && Dpsi2spi < 0.6 &&
		 Dpsi2spi2 >= 0 && Dpsi2spi2 < 0.6 &&
		 Dpsi2sjpsi1 >= 0 && Dpsi2sjpsi1 < 0.15 &&
		 Djpsimu >= 0 && Djpsimu <= 1 &&
		 Djpsimu2 >= 0 && Djpsimu2 <= 1 &&
		 XEta >= 0 && XEta < 4 &&
		 XPt >= 0 && XPt < 30 &&
		 psi2sProb >= 0 && psi2sProb <= 1 &&
		 psi2sEta >= 0 && psi2sEta < 2.2 &&
		 psi2sPt >= 4 && psi2sPt < 30 &&
		 jpsi2Eta >= 0 && jpsi2Eta < 2.2 &&
		 jpsi1Eta >= 0 && jpsi1Eta < 2.2 &&
		 jpsi2Pt >= 0 && jpsi2Pt < 20 &&
		 jpsi1Pt >= 0 && jpsi1Pt < 20 &&
		 MuEta >= 0 && MuEta < 2.5 &&
		 MuEta2 >= 0 && MuEta2 < 2.5 &&
		 MuEta3 >= 0 && MuEta3 < 2.5 &&
		 MuEta4 >= 0 && MuEta4 < 2.5 &&
		 MuPt > 2 && MuPt < 15 &&
		 MuPt2 > 2 && MuPt2 < 15 &&
		 MuPt3 > 2 && MuPt3 < 15 &&
		 MuPt4 > 2 && MuPt4 < 15 &&
		 PiEta >= 0 && PiEta < 3 &&
		 PiEta2 >= 0 && PiEta2 < 3 &&
		 PiPt > 0.5 && PiPt < 3 &&
		 PiPt2 > 0.5 && PiPt2 < 3 
        )
        {
        file << temp.c_str() << endl;
        }

    }
    return 0;
}