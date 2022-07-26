#include "TMath.h"
#include <TProfile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGaxis.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

#include "AfroConstants.h"

using namespace std;

// -------------------------------------------------------------------------------------------------------------------------------------

void GlobalSettings() {

	TGaxis::SetMaxDigits(5);

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);	

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

}

// -------------------------------------------------------------------------------------------------------------------------------------

void ReweightPlots(TH1D* h) {

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
		double content = h->GetBinContent(i);
		double error = h->GetBinError(i);
		double width = h->GetBinWidth(i);
		double newcontent = content / width;
		double newerror = error / width;				
		h->SetBinContent(i,newcontent);
		h->SetBinError(i,newerror);

	}

}

// -------------------------------------------------------------------------------------------------------------------------------------

void PrettyDoubleXSecPlot(TH1D* h) {

	// ----------------------------------------------------------------------------------------------------------------

	h->SetLineWidth(LineWidth);

	// ----------------------------------------------------------------------------------------------------------------

	// X-axis

	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetLabelFont(FontStyle);
	h->GetXaxis()->SetTitleFont(FontStyle);
	h->GetXaxis()->SetLabelSize(TextSize);
	h->GetXaxis()->SetTitleSize(TextSize);
	h->GetXaxis()->SetTitleOffset(1.05);
	h->GetXaxis()->SetNdivisions(Ndivisions);

	// ----------------------------------------------------------------------------------------------------------------

	// Y-axis

	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetTitleSize(TextSize); 
	//h->GetYaxis()->SetTickSize(0.02);
	h->GetYaxis()->SetLabelSize(TextSize);
	h->GetYaxis()->SetTitle(DoubleXSecTitle);
	h->GetYaxis()->SetTitleFont(FontStyle);
	h->GetYaxis()->SetLabelFont(FontStyle);
	h->GetYaxis()->SetTitleOffset(1.05);
	h->GetYaxis()->SetNdivisions(Ndivisions);

	return;	

}

// -------------------------------------------------------------------------------------------------------------------------------------

void AbsoluteXSecScaling(TH1D* h, TString Sample, TString Nucleus, TString E) {  

	double SF = 1.;

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	if (Sample == "SuSav2 NoRad") { 

				SF = (SuSav2GenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (NoRadSuSav2NumberEvents[std::make_pair(Nucleus, E)] ) ) ;

	}

	else if (Sample == "G2018 NoRad") { 

				SF = (G2018GenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (NoRadG2018NumberEvents[std::make_pair(Nucleus, E)] ) ) ;

	}

	else if (Sample == "Fortran SF NoRad") { 

				SF = (FortranSFGenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (NoRadFortranSFNumberEvents[std::make_pair(Nucleus, E)] ) ) ;

	}

	else {

		std::cout << "Craaaaaaaaaaaaaaap !!!!!!!!! What is the SF in AbsoluteXSecScaling for " << h->GetName() << " in " << Sample << "???????????????" << std::endl;

	}		

	h->Scale(SF);

}

// -------------------------------------------------------------------------------------------------------------------------------------

void ApplyRebinning(TH1D* h, TString Energy, TString PlotVar) {

	// -----------------------------------------------------------------------------------------------------------------------------

	if (string(PlotVar).find("Omega_FullyInclusive") != std::string::npos) {

		if (Energy == "1_161") { for (int i = 0; i < 5; i++) { h->Rebin(); } }

	} else if (string(PlotVar).find("Omega") != std::string::npos) {

		if (Energy == "1_161") { for (int i = 0; i < 5; i++) { h->Rebin(); } }
		if (Energy == "2_261") { for (int i = 0; i < 5; i++) { h->Rebin(); } }
		if (Energy == "4.461") { for (int i = 0; i < 6; i++) { h->Rebin(); } }

	} else if (string(PlotVar).find("EcalReso") != std::string::npos || string(PlotVar).find("ECalReso") != std::string::npos || string(PlotVar).find("h_Etot_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

	} else if (
		string(PlotVar).find("T2KEQEReso") != std::string::npos
	) {

		for (int i = 0; i < 2; i++) { h->Rebin();}

	} else if (
		string(PlotVar).find("EQEReso") != std::string::npos || 
		string(PlotVar).find("h_Erec_subtruct_piplpimi_factor_fracfeed") != std::string::npos ||
		string(PlotVar).find("h_Erec_subtruct_piplpimi_noprot_frac_feed") != std::string::npos

	) {

	} else if (string(PlotVar).find("EQE") != std::string::npos || string(PlotVar).find("eReco") != std::string::npos || string(PlotVar).find("Erec") != std::string::npos) {

	} else if (string(PlotVar).find("cal") != std::string::npos || string(PlotVar).find("Cal") != std::string::npos || string(PlotVar).find("epReco") != std::string::npos || string(PlotVar).find("Etot") != std::string::npos || string(PlotVar).find("E_tot") != std::string::npos) {

	} else if (string(PlotVar).find("PT") != std::string::npos || string(PlotVar).find("MissMomentum") != std::string::npos) {

		for (int i = 0; i < 2; i++) { h->Rebin();} 

	} else if (string(PlotVar).find("DeltaAlphaT") != std::string::npos ) {

		for (int i = 0; i < 1; i++) { h->Rebin();} 

	} else if (string(PlotVar).find("DeltaPhiT") != std::string::npos ) {

		for (int i = 0; i < 1; i++) { h->Rebin();} 

	} else if (string(PlotVar).find("Wvar") != std::string::npos || string(PlotVar).find("W_") != std::string::npos ) {

		for (int i = 0; i < 2; i++) { h->Rebin();} 

	}

	else { cout << "Aaaaaaaaaaaah ! How do I rebin this plot ?" << endl; }

	return;	

}

// -------------------------------------------------------------------------------------------------------------------------------------

void ApplyRange(TH1D* h, TString Energy, TString PlotVar) {

	// -----------------------------------------------------------------------------------------------------------------------------

	if (string(PlotVar).find("Omega") != std::string::npos) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.,0.7); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.,1.5); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(0.5,3.); }

	} else if (
		string(PlotVar).find("EcalReso") != std::string::npos || string(PlotVar).find("ECalReso") != std::string::npos || 
		string(PlotVar).find("h_Etot_subtruct_piplpimi_factor_fracfeed") != std::string::npos ||
		string(PlotVar).find("h1_Ecal_Reso") != std::string::npos ||
		string(PlotVar).find("h_Etot_subtruct_piplpimi_2p1pi_1p0pi_fracfeed") != std::string::npos

	) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(-0.7,0.06); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(-0.7,0.06); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(-0.7,0.03); }

	} else if (
		string(PlotVar).find("T2KEQEReso") != std::string::npos
		) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(-0.75,0.39); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(-0.69,0.21); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(-0.75,0.21); }


	} else if (
		string(PlotVar).find("EQEReso") != std::string::npos || 
		string(PlotVar).find("h_Erec_subtruct_piplpimi_factor_fracfeed") != std::string::npos ||
		string(PlotVar).find("h_Erec_subtruct_piplpimi_factor_fracfeed") != std::string::npos ||
		string(PlotVar).find("h_Erec_subtruct_piplpimi_noprot_frac_feed") != std::string::npos
		) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(-0.75,0.21); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(-0.69,0.21); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(-0.75,0.21); }

	} else if (string(PlotVar).find("EQE") != std::string::npos || string(PlotVar).find("eReco") != std::string::npos || string(PlotVar).find("Erec") != std::string::npos) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.47,1.4); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.7,2.6); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(1.9,5.2); }

	} else if (string(PlotVar).find("Etot") != std::string::npos || string(PlotVar).find("Cal") != std::string::npos || string(PlotVar).find("cal") != std::string::npos || string(PlotVar).find("epReco") != std::string::npos || string(PlotVar).find("E_tot") != std::string::npos || string(PlotVar).find("h1_Ecal_SuperFine") != std::string::npos) {

//		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.57,1.23); } // default, but now in the Ecal 6-pannel, we need to expand the range for smaller box 
		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.5,1.23); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.67,2.4); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(1.5,4.6); }

	} else if (string(PlotVar).find("PT") != std::string::npos || string(PlotVar).find("MissMomentum") != std::string::npos) {

	} else if (string(PlotVar).find("DeltaAlphaT") != std::string::npos ) {

	} else if (string(PlotVar).find("DeltaPhiT") != std::string::npos ) {

	} else if (string(PlotVar).find("Wvar") != std::string::npos || string(PlotVar).find("W_") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(0.6,1.5);

	}


	else { cout << "Aaaaaaaaaaaah ! How do I set the range for this plot ?" << endl; }

	return;	

}

// -------------------------------------------------------------------------------------------------------------------------------------

void UniversalE4vFunction(TH1D* h, TString DataSetLabel, TString nucleus, TString E, TString name) {

	// Scale by GENIE cross section/total number of events
	AbsoluteXSecScaling(h,DataSetLabel,nucleus,E);

	// e4v binning
	ApplyRebinning(h,E,name);

	// Bin width division
	ReweightPlots(h);

	// Relevant X-range ranges
	ApplyRange(h,E,name);
	
}