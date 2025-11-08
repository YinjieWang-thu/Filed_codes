#include "function_run3main.h"
using namespace std;
using namespace RooFit;
using namespace RooStats;
void DrawCut_run3main()
{
	myset(myStyle, variables);
	psi2s_mass.setRange(3.6, 3.95);
		RooDataSet *data = RooDataSet::read("result.txt", variables, "Q", "D:/Desktop/SR/code/CutOptimization-run3-2/data/", nullptr);
	fitData2D2peak(data, true); 
	fitjpsi1(data, true);
	psi2s_mass.setRange(psi2s_mass_Min, psi2s_mass_Max);
}
