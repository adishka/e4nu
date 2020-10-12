#include "TMath.h"
#include <TH1D.h>
#include <TH2D.h>

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

void ApplySystUnc(TH1D* h, double Energy) {

	double SystUnc = 0;
	if ( Energy == 1.161 ) { SystUnc = SystUnc1GeV; }
	if ( Energy == 2.261 ) { SystUnc = SystUnc2GeV; }
	if ( Energy == 4.461 ) { SystUnc = SystUnc4GeV; }

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

std::vector<double> GetUncertaintyBand(TH1D* h[], int NPlots) {

	double NBins = h[0]->GetNbinsX();

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

		UncVector.push_back(0.5*spread); // take half the spread as an uncertainty

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

	if (Sample == "Pinned Data") { 

		SF = 1. / (IntegratedCharge_PinnedFiles[std::make_pair(Nucleus, E)] *\
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

void BinningAndRange(TH1D* h, double Energy, TString PlotVar) {

	// -----------------------------------------------------------------------------------------------------------------------------

	if (string(PlotVar).find("Omega") != std::string::npos) {

		if (Energy == 1.161) { for (int i = 0; i < 5; i++) { h->Rebin(); } h->GetXaxis()->SetRangeUser(0.,0.7); }
		if (Energy == 2.261) { for (int i = 0; i < 5; i++) { h->Rebin(); } h->GetXaxis()->SetRangeUser(0.,1.5); }
		if (Energy == 4.461) { for (int i = 0; i < 6; i++) { h->Rebin(); } h->GetXaxis()->SetRangeUser(0.5,3.); }

	} else if (string(PlotVar).find("EQE") != std::string::npos || string(PlotVar).find("ECal") != std::string::npos) {

		if (Energy == 1.161) { h->GetXaxis()->SetRangeUser(0.4,1.7); }
		if (Energy == 2.261) { h->GetXaxis()->SetRangeUser(0.6,3.); }
		if (Energy == 4.461) { h->GetXaxis()->SetRangeUser(1.5,6.); }

	} else { cout << "Aaaaaaaaaaaah ! How do I rebin this plot ?" << endl; }

	return;	

}

// -------------------------------------------------------------------------------------------------------------------------------------

double computeMean(std::vector<double> numbers) {

	if(numbers.empty()) return 0;

	double total = 0;
	for (int number = 0; number < (int)(numbers.size()); number ++) {
		total += numbers[number];
	}

	double average = total / numbers.size();
	return average;
}

// -------------------------------------------------------------------------------------------------------------------------------------

double computeStd(double mean, std::vector<double> numbers) {

	float result = 0;
	for (int number = 0; number < (int)(numbers.size()); number ++) {
		result += (numbers[number] - mean)*(numbers[number] - mean);
	}

	return sqrt(result / (numbers.size() - 1));
}

// -------------------------------------------------------------------------------------------------------------------------------------
