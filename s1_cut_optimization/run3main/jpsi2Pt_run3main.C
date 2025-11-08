// This is a templete for creating scripts to find a cut point of minimum of a variable
// which means this variable will have a varying lower bundary
#include "function_run3main.h"
using namespace std;
using namespace RooFit;
using namespace RooStats;

void jpsi2Pt_run3main()
{	 
	// myset(myStyle, variables);
	// If you want to run without Execute.C, use this to initialize
	
	vector<double> numS, numB, TEM, x_Data, y_Data, eventnum;
	for (double tem_jpsi2Pt = jpsi2Pt_MinOpt; tem_jpsi2Pt < jpsi2Pt_MaxOpt; tem_jpsi2Pt += (jpsi2Pt_MaxOpt - jpsi2Pt_MinOpt) / stepnum)
	{
		jpsi2Pt.setRange(tem_jpsi2Pt, jpsi2Pt_Max);// Set cut as tem, which increase gradually
		RooDataSet *data = RooDataSet::read("result.txt", variables, "Q", "D:/Desktop/SR/code/CutOptimization-run3-2/data/", nullptr);
	if(data->sumEntries() == 0)
		{
			break;
		}
                //Load data read only data from range of optimazed variable;
                // Q is for quiet and D for verbose; 'data/' is data file directory, nullptr by default
                // Each cloumb of the txt file will be read as a variable, accroding to order in variables
                // Cloumb number should match number of variables in 'variables', exceeding lines will be ignored
                // Cloumb with data out of range in 'variables' will also be ignored
                // The first cloumb should be Psi2s Mass and will be used for fitting
                // Multi-files can be used, just substitute 'Data_List' with comma seperated file list
		myresult myroofitresult = fitjpsi1(data);
		
		//For good quality fit, save thier results
		if (myroofitresult.fitquality == 1)
		{
			x_Data.push_back(tem_jpsi2Pt);
			y_Data.push_back(myroofitresult.merit);
			numS.push_back(myroofitresult.mySfromData);
			numB.push_back(myroofitresult.myBfromData);
			eventnum.push_back(data->sumEntries());
			TEM.push_back(myroofitresult.tem);
		}
		delete data;
	}

	//Print results and Draw merit plot
	if (x_Data.size() > 0)
	{
	//	print("tem", TEM);// All good fit cut position
	//	print("numS", numS);// Signal number
	//	print("numB", numB);// Background number
	   	//Draw and print S/sqrt(S+B) as function of cut position
		print_vectors("result/run3main_result/jpsi2Pt","Psi2s_SfromData", x_Data, y_Data, eventnum);
		drawVectors("result/run3main_result/jpsi2Pt", "jpsi2Pt_merit_min", x_Data, y_Data);
		drawVectors("result/run3main_result/jpsi2Pt_mar", "jpsi2Pt_merit_min_mar", x_Data, y_Data, eventnum);
	}
	jpsi2Pt.setRange(jpsi2Pt_Min, jpsi2Pt_Max);// Reset range for next fit
}
