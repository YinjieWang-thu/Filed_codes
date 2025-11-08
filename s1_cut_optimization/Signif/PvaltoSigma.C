#include "TMath.h"
#include "RooStats/RooStatsUtils.h"
using namespace std;
void PvaltoSigma() {
        //-10873.5 -2554.78
        //-3304.91 -1336.29
        //-10870.6 -10873.9(sig)
        //-6246.4 -6247.41(sig)
    Double_t ln_l1 = -7701.04;
    Double_t ln_l2 = -7703.34;// ln_l is log likelyhood, that is log(PI(pi))
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
    // confidence level: wheni zero hyposis(no signal) is correct, how possible it is to give chi2 or larger one, the smaller confidence level, the better the hyposis(signal exits)
    //
    // significance: a value to evaluate cl above by converting it to a normal distribution, no obvious static meaning, just providing 3-sigma or 5-sigma principle
}