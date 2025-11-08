#include "BDTApp.C"

//delete previous file and edit BDTApp.C before using！

void AppExe()
{
    BDTApp("mc_Bs1.root", "mc_Bs1_BDT1.root");
    BDTApp("mc_Bs2.root", "mc_Bs2_BDT1.root");
    BDTApp("data.root", "data_BDT1.root");
    BDTApp("Bphy25mix.root", "Bphy25mix_BDT1.root");
}