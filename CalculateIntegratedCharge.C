#define CalculateIntegratedCharge_cxx
#include "CalculateIntegratedCharge.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void CalculateIntegratedCharge::Loop() {

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	double IntegratedCharge = 0;
	double RunCharge = -1;

	double Q_U_Min = 99;
	double Q_U_Max = -1;
	double Lifetime = -1;

	double Events = 0;
	double SumLifetime = 0;

//	TProfile* IntCharge = new TProfile("Charge","Charge",fChain->GetEntries(),0,fChain->GetEntries());

	// ---------------------------------------------------------------------------------------------------------------------------------	

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);	 nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		// ---------------------------------------------------------------------------------------------------------------------

		if (jentry%1000 == 0) {std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/fChain->GetEntries()*100. << " %"<< std::endl;}

		// ------------------------------------------------------------------------------------------------------------------------

		// apapadop Nov 2 2020: Watch out !!!
		// new sampples cooked by Mikhail
		// the helicity branches and the runnb one have been deactivated

//		double fTorusCurrent = 0;

//		if((runnb>18283 && runnb<18289) || (runnb>18300 && runnb<18304) || (runnb>18317 && runnb<18329)) fTorusCurrent=750; //setting appropriate torrus magnet current
//		else if ((runnb>18293 && runnb<18301) || (runnb>18305 && runnb<18317) || (runnb>18328 && runnb<18336))  fTorusCurrent=1500;
//		else fTorusCurrent=2250;

		//if (fbeam_en == "1161" && fTorusCurrent > 760) { continue; }                                                              
                //if (fbeam_en == "1161" && fTorusCurrent < 760) { continue; }

//		IntCharge->Fill(jentry,q_u*t_l);

		// -------------------------------------------------------------------------------

		// first click

		if (jentry == 0) { 

			Q_U_Min = q_u; 
			Lifetime = t_l;
			RunCharge = q_u;

		}

		// next click

		if (RunCharge != q_u) {

			Q_U_Max = q_u; 
			IntegratedCharge += (Q_U_Max - Q_U_Min)*Lifetime; // in μC to be added only once per run
			RunCharge = q_u;

			Q_U_Min = q_u; 
			Lifetime = t_l;
		}

		// -------------------------------------------------------------------------------

//		if (RunCharge != q_u) {

//			IntegratedCharge += q_u*t_l; // in μC to be added only once per run
//			RunCharge = q_u;
//		}

		// -------------------------------------------------------------------------------

//		if (q_u < Q_U_Min) { Q_U_Min = q_u; }
//		if (q_u > Q_U_Max) { Q_U_Max = q_u; }

//		Events ++;
//		SumLifetime += t_l;


	} // End of the loop over the events

	// ---------------------------------------------------------------------------------------------------------------------------------

//	double AverageLifetime = SumLifetime / Events;

//	cout << endl << "AverageLifetime = " << AverageLifetime << endl; 
//	cout << "Q_U_Min = " << Q_U_Min << endl;
//	cout << "Q_U_Max = " << Q_U_Max << endl;

//	double IntCharge = (Q_U_Max - Q_U_Min)*AverageLifetime ;
//	cout << "IntCharge = " << IntCharge << endl;

	cout << "IntegratedCharge = " << IntegratedCharge << endl;

}
