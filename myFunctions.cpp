#include "TMath.h"
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

// ----------------------------------------------------------------------------------------------------------------

void ApplySystUnc(TH1D* h, TString Energy) {

	double SystUnc = 0;
	if ( Energy == "1_161" ) { SystUnc = SystUnc1GeV; }
	if ( Energy == "2_261" ) { SystUnc = SystUnc2GeV; }
	if ( Energy == "4_461" ) { SystUnc = SystUnc4GeV; }

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
//		double error = h->GetBinError(i);
//		double newerror = error * (1. + systunc);

		double error = h->GetBinError(i);
		double content = h->GetBinContent(i);
		double newerror = TMath::Sqrt( TMath::Power(error,2.) + TMath::Power(SystUnc*content,2.));
		h->SetBinError(i,newerror);

	}

}

// ----------------------------------------------------------------------------------------------------------------

void ApplySectorSystUnc(TH1D* h, TString Energy) {

	double SystUnc = 0;
	if ( Energy == "1_161" ) { SystUnc = SectorSystUnc1GeV; }
	if ( Energy == "2_261" ) { SystUnc = SectorSystUnc2GeV; }
	if ( Energy == "4_461" ) { SystUnc = SectorSystUnc4GeV; }

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
//		double error = h->GetBinError(i);
//		double newerror = error * (1. + systunc);

		double error = h->GetBinError(i);
		double content = h->GetBinContent(i);
		double newerror = TMath::Sqrt( TMath::Power(error,2.) + TMath::Power(SystUnc*content,2.));
		h->SetBinError(i,newerror);

	}

}

// ----------------------------------------------------------------------------------------------------------------

std::vector<double> GetUncertaintyBand(std::vector<TH1D*> h) {

	int NPlots = h.size();

	int NBins = h[0]->GetNbinsX();

	std::vector<double> UncVector; UncVector.clear();

	for (int i = 1; i <= NBins; i++) {  

		std::vector<double> BinVector; BinVector.clear();

		for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

			double content = h[WhichPlot]->GetBinContent(i);
			BinVector.push_back(content);

		} // End of the loop over the plots

		auto min = std::min_element(std::begin(BinVector), std::end(BinVector));

		auto max = std::max_element(std::begin(BinVector), std::end(BinVector));

		double spread = *max - *min;

		UncVector.push_back(0.5*TMath::Abs(spread)); // take half the spread as an uncertainty

	} // End of the loop over the bins

	return UncVector;

}

// ----------------------------------------------------------------------------------------------------------------

void ApplySectorSystUnc(TH1D* h, std::vector<double> sectorsystunc) {

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
//		double error = h->GetBinError(i);
//		double newerror = error * (1. + systunc);

		double error = h->GetBinError(i);
		double sectorerorr = sectorsystunc.at(i-1);
		double newerror = TMath::Sqrt( TMath::Power(error,2.) + TMath::Power(sectorerorr,2.));

		h->SetBinError(i,newerror);

	}

}

// ----------------------------------------------------------------------------------------------------------------

TH1D* VectorToHistSystUnc(TH1D* h, std::vector<double> sectorsystunc, TString name) {

	double NBins = h->GetXaxis()->GetNbins(); 

	TH1D* ClonePlot = (TH1D*)(h->Clone("Unc_"+name));
				
	for (int i = 1; i <= NBins; i++) { 

		double unc = sectorsystunc[i-1];

		ClonePlot->SetBinContent(i,unc);
		ClonePlot->SetBinError(i,0);

	}

	return ClonePlot;

}

// -------------------------------------------------------------------------------------------------------------------------------------

TString ToStringInt(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

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
	h->GetYaxis()->SetTickSize(0.02);
	h->GetYaxis()->SetLabelSize(TextSize);
	h->GetYaxis()->SetTitle(DoubleXSecTitle);
	h->GetYaxis()->SetTitleFont(FontStyle);
	h->GetYaxis()->SetLabelFont(FontStyle);
	h->GetYaxis()->SetTitleOffset(1.05);
	h->GetYaxis()->SetNdivisions(Ndivisions);

	return;	

}

// -------------------------------------------------------------------------------------------------------------------------------------

void PrettyGraph(TGraph* h) {

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
	h->GetYaxis()->SetTickSize(0.02);
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

	// ----------------------------------------------------------------------------------------------------------------------------------------

	// Data sets

	if (Sample == "Data") { 

		SF = 1. / ( IntegratedCharge[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus] ) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Data_FilterRuns") { 

		SF = 1. / (IntegratedCharge_FilterRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Data_NewFilterRuns") { 

		SF = 1. / (IntegratedCharge_NewFilterRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "GoodRunList_Data") { 

		SF = 1. / (IntegratedCharge_GoodRunList_AllRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "LowCurrent_GoodRunList_Data") { 

		SF = 1. / (IntegratedCharge_GoodRunList_LowCurrentRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;


	}

	if (Sample == "HighCurrent_GoodRunList_Data") { 

		SF = 1. / (IntegratedCharge_GoodRunList_HighCurrentRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Pinned Data" || Sample == "Pinned Data No Rotations") { 

		SF = 1. / (IntegratedCharge_PinnedFiles[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Mikhail Data") { 

		SF = 1. / (IntegratedCharge_MikhailFiles[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	// Simulation sets

	if (Sample == "SuSav2" || Sample == "SuSav2_NoAccMaps" ) { 

				SF = (SuSav2GenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (SuSav2NumberEvents[std::make_pair(Nucleus, E)] *\
					dOmega) ) ;

	}

	if (Sample == "G2018") { 

		SF = ( G2018GenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (G2018NumberEvents[std::make_pair(Nucleus, E)] *\
					dOmega) );

	}	

	h->Scale(SF);

}

// -------------------------------------------------------------------------------------------------------------------------------------

void AbsoluteXSec2DScaling(TH2D* h, TString Sample, TString Nucleus, TString E) {  

	double SF = 1.;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	// Data sets

	if (Sample == "Data") { 

		SF = 1. / ( IntegratedCharge[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus] ) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Data_FilterRuns") { 

		SF = 1. / (IntegratedCharge_FilterRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Data_NewFilterRuns") { 

		SF = 1. / (IntegratedCharge_NewFilterRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "GoodRunList_Data") { 

		SF = 1. / (IntegratedCharge_GoodRunList_AllRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "LowCurrent_GoodRunList_Data") { 

		SF = 1. / (IntegratedCharge_GoodRunList_LowCurrentRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;


	}

	if (Sample == "HighCurrent_GoodRunList_Data") { 

		SF = 1. / (IntegratedCharge_GoodRunList_HighCurrentRuns[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Pinned Data" || Sample == "Pinned Data No Rotations") { 

		SF = 1. / (IntegratedCharge_PinnedFiles[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	if (Sample == "Mikhail Data") { 

		SF = 1. / (IntegratedCharge_MikhailFiles[std::make_pair(Nucleus, E)] *\
						    TargetLength[std::make_pair(Nucleus, E)] *\
						    TargetDensity[std::make_pair(Nucleus, E)] *\
						    OverallUnitConversionFactor / MassNumber[Nucleus]) * ConversionFactorCm2ToMicroBarn / dOmega;

	}

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	// Simulation sets

	if (Sample == "SuSav2" || Sample == "SuSav2_NoAccMaps" ) { 

				SF = (SuSav2GenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (SuSav2NumberEvents[std::make_pair(Nucleus, E)] *\
					dOmega) ) ;

	}

	if (Sample == "G2018") { 

		SF = ( G2018GenieXSec[std::make_pair(Nucleus, E)] * TMath::Power(10.,-38.) *\
					ConversionFactorCm2ToMicroBarn / (G2018NumberEvents[std::make_pair(Nucleus, E)] *\
					dOmega) );

	}	

	h->Scale(SF);

}

// -------------------------------------------------------------------------------------------------------------------------------------

void ApplyRebinning(TH1D* h, TString Energy, TString PlotVar) {

	// -----------------------------------------------------------------------------------------------------------------------------

	if (string(PlotVar).find("Omega") != std::string::npos) {

		if (Energy == "1_161") { for (int i = 0; i < 5; i++) { h->Rebin(); } }
		if (Energy == "2_261") { for (int i = 0; i < 5; i++) { h->Rebin(); } }
		if (Energy == "4.461") { for (int i = 0; i < 6; i++) { h->Rebin(); } }

	} else if (string(PlotVar).find("EcalReso") != std::string::npos || string(PlotVar).find("ECalReso") != std::string::npos || string(PlotVar).find("h_Etot_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

	} else if (string(PlotVar).find("EQEReso") != std::string::npos || string(PlotVar).find("h_Erec_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

	} else if (string(PlotVar).find("EQE") != std::string::npos || string(PlotVar).find("eReco") != std::string::npos || string(PlotVar).find("Erec") != std::string::npos) {

	} else if (string(PlotVar).find("cal") != std::string::npos || string(PlotVar).find("Cal") != std::string::npos || string(PlotVar).find("epReco") != std::string::npos || string(PlotVar).find("Etot") != std::string::npos || string(PlotVar).find("E_tot") != std::string::npos) {

	} else if (string(PlotVar).find("PT") != std::string::npos || string(PlotVar).find("MissMomentum") != std::string::npos) {

		for (int i = 0; i < 2; i++) { h->Rebin();} 

	} else if (string(PlotVar).find("DeltaAlphaT") != std::string::npos ) {

		for (int i = 0; i < 1; i++) { h->Rebin();} 

	} else if (string(PlotVar).find("DeltaPhiT") != std::string::npos ) {

		for (int i = 0; i < 1; i++) { h->Rebin();} 

	} else if (string(PlotVar).find("Wvar") != std::string::npos || string(PlotVar).find("W_") != std::string::npos ) {

		for (int i = 0; i < 1; i++) { h->Rebin();} 

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

	} else if (string(PlotVar).find("EcalReso") != std::string::npos || string(PlotVar).find("ECalReso") != std::string::npos || string(PlotVar).find("h_Etot_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(-0.81,0.07);

	} else if (string(PlotVar).find("EQEReso") != std::string::npos || string(PlotVar).find("h_Erec_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(-0.85,0.2);

	} else if (string(PlotVar).find("EQE") != std::string::npos || string(PlotVar).find("eReco") != std::string::npos || string(PlotVar).find("Erec") != std::string::npos) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.47,1.4); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.7,2.6); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(2.,5.); }

	} else if (string(PlotVar).find("Etot") != std::string::npos || string(PlotVar).find("Cal") != std::string::npos || string(PlotVar).find("cal") != std::string::npos || string(PlotVar).find("epReco") != std::string::npos || string(PlotVar).find("E_tot") != std::string::npos) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.57,1.23); }
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

// -----------------------------------------------------------------------------------------------------------------------------

void ApplyRange(TGraph* h, TString Energy, TString PlotVar) {

	// -----------------------------------------------------------------------------------------------------------------------------

	if (string(PlotVar).find("Omega") != std::string::npos) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.,0.7); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.,1.5); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(0.5,3.); }

	} else if (string(PlotVar).find("EcalReso") != std::string::npos || string(PlotVar).find("ECalReso") != std::string::npos || string(PlotVar).find("h_Etot_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(-0.81,0.07);

	} else if (string(PlotVar).find("EQEReso") != std::string::npos || string(PlotVar).find("h_Erec_subtruct_piplpimi_factor_fracfeed") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(-0.85,0.2);

	} else if (string(PlotVar).find("EQE") != std::string::npos || string(PlotVar).find("eReco") != std::string::npos || string(PlotVar).find("Erec") != std::string::npos) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.47,1.4); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.7,2.6); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(2.,5.); }

	} else if (string(PlotVar).find("Etot") != std::string::npos || string(PlotVar).find("ECal") != std::string::npos || string(PlotVar).find("Ecal") != std::string::npos || string(PlotVar).find("epReco") != std::string::npos ) {

		if (Energy == "1_161") { h->GetXaxis()->SetRangeUser(0.57,1.19); }
		if (Energy == "2_261") { h->GetXaxis()->SetRangeUser(0.67,2.4); }
		if (Energy == "4_461") { h->GetXaxis()->SetRangeUser(1.5,4.6); }

	} else if (string(PlotVar).find("PT") != std::string::npos || string(PlotVar).find("MissMomentum") != std::string::npos) {

	} else if (string(PlotVar).find("DeltaAlphaT") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(10,180);

	} else if (string(PlotVar).find("DeltaPhiT") != std::string::npos ) {

	} else if (string(PlotVar).find("Wvar") != std::string::npos ) {

		h->GetXaxis()->SetRangeUser(0.6,1.5);

	}


	else { cout << "Aaaaaaaaaaaah ! How do I set the range for this plot ?" << endl; }

	return;	

}

// -------------------------------------------------------------------------------------------------------------------------------------

void UniversalE4vFunction(TH1D* h, TString DataSetLabel, TString nucleus, TString E, TString name) {

	// Scale to obtain absolute double differential cross sections 
	// Use charge, density and length for data samples
	// Use total number of events in genie sample and relevant genie cross sections for simulation

	AbsoluteXSecScaling(h,DataSetLabel,nucleus,E);

	// Division by the bin width

	ReweightPlots(h);

	// Rebin if necessary

	ApplyRebinning(h,E,name);

	// Use relevant ranges
			
	ApplyRange(h,E,name);

	// if data sample: 

	// 	apply systematics due to rotations et al

	if (string(DataSetLabel).find("Data") != std::string::npos) { ApplySystUnc(h, E); }

	// 	apply acceptance systematics using sector-by -sector uncertainties

	if (string(DataSetLabel).find("Data") != std::string::npos) { ApplySectorSystUnc(h, E); }
	
}

// -------------------------------------------------------------------------------------------------------------------------------------

TH1D* AcceptanceCorrection(TH1D* h, TString ScaleToDataSet, TString nucleus, TString E, TString name, TString xBCut) {

	std::vector<TH1D*> Plots; Plots.clear();

	std::vector<TString> FSIModel; FSIModel.clear();

	FSIModel.push_back(ScaleToDataSet+"_RadCorr_LFGM");
//	FSIModel.push_back(ScaleToDataSet+"_RadCorr_LFGM_Truth_WithFidAcc");
	FSIModel.push_back(ScaleToDataSet+"_RadCorr_LFGM_Truth_WithoutFidAcc");
	int NFSIModels = FSIModel.size();

	for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

		// --------------------------------------------------------------------------------------

		TString PathToFiles = GlobalPathToFiles + E + "/" + FSIModel[WhichFSIModel] + "/" + xBCut + "/";
		TString FileName = PathToFiles + nucleus +"_" + E + "_" + FSIModel[WhichFSIModel] + "_Plots_FSI_em.root";
		TFile* FileSample = TFile::Open(FileName);

		Plots.push_back( (TH1D*)( FileSample->Get(name) ) );

		UniversalE4vFunction(Plots[WhichFSIModel],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus,E,name);

		// --------------------------------------------------------------------------------------

	}

	// --------------------------------------------------------------------------------------	

	TH1D* OverallClone = (TH1D*)h->Clone();	

	int NBins = OverallClone->GetXaxis()->GetNbins();

	for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {

		double AccCorr = Plots[0]->GetBinContent(WhichBin + 1) / Plots[1]->GetBinContent(WhichBin + 1);

		double NewBinContent = 1.;
		double NewBinError = 0.;		

		if (Plots[1]->GetBinContent(WhichBin + 1) <= 0) { 

			NewBinContent = 0.;
			NewBinError = 0.;

		} else {

			NewBinContent = h->GetBinContent(WhichBin + 1) / AccCorr;
			NewBinError = h->GetBinError(WhichBin + 1) / AccCorr;

		}

		OverallClone->SetBinContent(WhichBin + 1, NewBinContent);
		OverallClone->SetBinError(WhichBin + 1, NewBinError);

	}

	// --------------------------------------------------------------------------------------	

	return OverallClone;

}

// -------------------------------------------------------------------------------------------------------------------------------------

void UniversalE4v2DFunction(TH2D* h, TString DataSetLabel, TString nucleus, TString E, TString name) {

	// Scale to obtain absolute double differential cross sections 
	// Use charge, density and length for data samples
	// Use total number of events in genie sample and relevant genie cross sections for simulation

	AbsoluteXSec2DScaling(h,DataSetLabel,nucleus,E);

	// Division by the bin width

//	ReweightPlots(h);

//	// Rebin is necessary

//	ApplyRebinning(h,E,name);

//	// Use relevant ranges
//			
//	ApplyRange(h,E,name);

//	// if data sample: 
//	//                 apply systematics due to rotations et al

//	if (string(DataSetLabel).find("Data") != std::string::npos) { ApplySystUnc(h, E); }

//	//                 apply acceptance systematics using sector-by -sector uncertainties

//	if (string(DataSetLabel).find("Data") != std::string::npos) { ApplySectorSystUnc(h, E); }
}


// -------------------------------------------------------------------------------------------------------------------------------------

double computeMean(std::vector<double> numbers,std::vector<double> weights = {}) {

	if(numbers.empty()) return 0;

	int NBins = (int)(numbers.size());

	if (numbers.size() != weights.size()) { 

		weights.resize( NBins );

		for (int bin = 0; bin < NBins; bin ++) {

			weights[bin] = 1.;

		}

	}

	double total = 0;
	double sumweights = 0;

	for (int number = 0; number < NBins; number ++) {

		total += numbers[number] * weights[number];
		sumweights += weights[number];
	}

	if (sumweights == 0) { return 0.; }

	double average = total / sumweights;

	return average;
}

// -------------------------------------------------------------------------------------------------------------------------------------

double computeStd(double mean, std::vector<double> numbers,std::vector<double> weights = {}) {

	if(numbers.empty()) return 0;

	int NBins = (int)(numbers.size());

	if (numbers.size() != weights.size()) { 

		weights.resize( NBins );

		for (int bin = 0; bin < NBins; bin ++) {

			weights[bin] = 1.;

		}

	}

	double DiffToMean = 0;
	double sumweights = 0;
	int M = 0; // Non zero weights

	for (int number = 0; number < NBins; number ++) {

		DiffToMean += weights[number]*(numbers[number] - mean)*(numbers[number] - mean);
		sumweights += weights[number];
		if (weights[number] != 0) { M++; }

	}

	if (sumweights == 0) { return 0.; }

	return sqrt(DiffToMean / ( (double)(M-1)/(double)(M) * sumweights) );
}

// -------------------------------------------------------------------------------------------------------------------------------------

double SumSqDiffInBin(std::vector<double> numbers, double mean = 0) {

	if(numbers.empty()) return 0;

	int NBins = (int)(numbers.size());

	double sum = 0;

	for (int number = 0; number < NBins; number ++) {

		sum += TMath::Power(numbers[number] - mean,2.);

	}

	return sum;

}

// -------------------------------------------------------------------------------------------------------------------------------------

double Chi2(TH1D* h1,TH1D* h2, int LowBin = -1, int HighBin = -1) {

	int NBinsX = h1->GetXaxis()->GetNbins();

	double chi2 = 0;
	
	if (LowBin == -1) { LowBin = 0; }
	if (HighBin == -1) { HighBin = NBinsX; }	

	for (int WhichXBin = LowBin; WhichXBin < HighBin; WhichXBin++) {

		double h1Entry = h1->GetBinContent(WhichXBin+1);
		double h1Error = h1->GetBinError(WhichXBin+1);
		double h2Entry = h2->GetBinContent(WhichXBin+1);
		double h2Error = h2->GetBinError(WhichXBin+1);

		double num = TMath::Power(h1Entry - h2Entry,2.);
		double den = TMath::Power(h1Error,2.) + TMath::Power(h2Error,2.);
		if (den != 0) { chi2 += (num / den); }

	}

	return chi2;

}

// -------------------------------------------------------------------------------------------------------------------------------------

TPad* CreateTPad(int WhichEnergy, int WhichNucleus, double Energy, TString nucleus, TString name, TCanvas* PlotCanvas) {

	double XMinPad = Xmin + WhichEnergy * Xstep, XMaxPad = Xmin + ( WhichEnergy + 1) * Xstep;
	if (Energy == 1.161 ) { XMinPad = XMinPad - 0.05; }
	double YMinPad = Ymax - ( WhichNucleus + 1) * Ystep, YMaxPad = Ymax - WhichNucleus * Ystep;

	TPad* pad = new TPad(); 

	if (nucleus == "12C") 
	{ pad = new TPad(name,name,XMinPad,YMinPad,XMaxPad,YMaxPad, 21); }
	else { 
		if (Energy == 2.261) 
			{ pad = new TPad(name,name,XMinPad-0.031,YMinPad+space,XMaxPad,YMaxPad+space, 21); }
		else { pad = new TPad(name,name,XMinPad,YMinPad+space,XMaxPad,YMaxPad+space, 21); }
	}

	pad->SetFillColor(kWhite); 
	PlotCanvas->cd();
	pad->Draw();
	pad->cd();

	pad->SetBottomMargin(0.15);

	pad->SetTopMargin(0.0);
	if (nucleus == "12C") { pad->SetTopMargin(0.01); }

	pad->SetRightMargin(0.0);
	if (Energy == 4.461 ) { pad->SetRightMargin(0.01); }

	pad->SetLeftMargin(0.);
	if (Energy == 1.161 ) { pad->SetLeftMargin(0.13); }
	if (Energy == 2.261 && nucleus == "56Fe") { pad->SetLeftMargin(0.1); }	

	return pad;

}

// -------------------------------------------------------------------------------------------------------------------------------------
