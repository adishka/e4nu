#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>

#include <iostream>
#include <vector>

#include <iostream>
#include <map>
#include <utility>

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

// Accounting for the fact that the bin width is not constant

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

void ApplySystUnc(TH1D* h, double systunc) {

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
		double error = h->GetBinError(i);
		double newerror = error * (1. + systunc);
		h->SetBinError(i,newerror);

	}

}

// ----------------------------------------------------------------------------------------------------------------

void HydrogenComparisons() {

	// ------------------------------------------------------------------------

	SetOffsetAndSize();
	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	int Ndivisions = 4;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.08;
	double acc = 3.;
	
	TString version = "v3_0_6/";

	// From Mariana's analysis note

	double SystUnc1GeV = 0.02; // 2% syst uncertainty at 1.161 GeV
	double SystUnc2GeV = 0.021; // 2.1% syst uncertainty at 2.261 GeV
	double SystUnc4GeV = 0.047; // 4.7% syst uncertainty at 4.461 GeV

	// ------------------------------------------------------------------------

	// Larry/Axel's suggestion for scaling the last 2 bins by EnhaceTail
	double EnhaceTail = 1./3.;

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;  std::vector<int> BreakDownColors;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He"); JustNucleus.push_back("He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");
	nucleus.push_back("CH2"); LabelsOfSamples.push_back("CH2"); JustNucleus.push_back("CH2");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");  JustNucleus.push_back("Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV"); DoubleE.push_back(1.161);
	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");  DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");
 
//	Colors.push_back(kBlack); Colors.push_back(kRed); Colors.push_back(kBlue); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);
	Colors.push_back(kBlack); Colors.push_back(610); Colors.push_back(410); Colors.push_back(kMagenta); Colors.push_back(kGreen+3); Colors.push_back(kBlue);  Colors.push_back(610);

//	Style.push_back(9); Style.push_back(3); Style.push_back(7); Style.push_back(5);
//	Style.push_back(9); Style.push_back(9); Style.push_back(9); Style.push_back(9); // fancy dashed lines 
	Style.push_back(1); Style.push_back(kDashed); Style.push_back(1); Style.push_back(1);

	BreakDownColors.push_back(kBlue); BreakDownColors.push_back(kCyan); BreakDownColors.push_back(kGreen); BreakDownColors.push_back(kMagenta);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");

//	FSIModel.push_back("Data_Final"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("hA2018_Final_NoRadCorr_LFGM"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");  DirNames.push_back("G2018");
//	FSIModel.push_back("SuSav2_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2 NoRad");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("SuSav2");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_NoAccMaps"); FSILabel.push_back("SuSav2_NoAccMaps");  DirNames.push_back("SuSav2_NoAccMaps");

//	FSIModel.push_back("SuSav2_02_11a_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("Data_Final_FilterRuns"); FSILabel.push_back("Data_FilterRuns"); DirNames.push_back("Data_FilterRuns");
//	FSIModel.push_back("Data_Final_NewFilterRuns"); FSILabel.push_back("Data_NewFilterRuns"); DirNames.push_back("Data_NewFilterRuns");

//	FSIModel.push_back("GoodRunList_Data_Final"); FSILabel.push_back("GoodRunList_Data"); DirNames.push_back("GRL Data");
//	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");
//	FSIModel.push_back("LowCurrent_GoodRunList_Data_Final"); FSILabel.push_back("LowCurrent_GoodRunList_Data"); DirNames.push_back("LC GRL Data");
//	FSIModel.push_back("HighCurrent_GoodRunList_Data_Final"); FSILabel.push_back("HighCurrent_GoodRunList_Data"); DirNames.push_back("HC GRL Data");

//	FSIModel.push_back("Data_Final_NoChargedPions"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_NoChargedPions"); FSILabel.push_back("G2018");  DirNames.push_back("hA2018_Truth_RadCorr");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_NoChargedPions"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("hA2018_Final_NoRadCorr"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hA2018_Truth_NoRadCorr"); FSILabel.push_back("Genie (Truth)");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hN2018_Final_NoRadCorr_LFGM"); FSILabel.push_back("Genie hN2018");  DirNames.push_back("hN2018_Truth_NoRadCorr");
//	FSIModel.push_back("hN2018_Final_RadCorr_LFGM"); FSILabel.push_back("Genie hN2018");  DirNames.push_back("hN2018_Truth_NoRadCorr");



	NameOfPlots.push_back("h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0"); LabelOfPlots.push_back("1st Sector Energy Transfer [GeV]"); OutputPlotNames.push_back("h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0");



	std::vector<TH1D*> Plots;
	std::vector<TH1D*> Plots_Clones;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	TString RecoCalorimetry = "(e,e'p)";
	TString FSI = "FSI";

	std::vector<TString> GenieFSILabel; GenieFSILabel.clear();
	GenieFSILabel.push_back("QE"); GenieFSILabel.push_back("MEC"); GenieFSILabel.push_back("RES"); GenieFSILabel.push_back("DIS");

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// cm^2 to μbarn
	double ConversionFactorCm2ToMicroBarn = TMath::Power(10.,30.);

	// 1e -> 1.6x10^-19 C
	// 1C -> 6.25x10^18 e
	// 1mC -> 6.25x10^15 e
	// Thus the numbers above have to be multiplied by this number to make sure that we refer to electrons and not charge
	double ConversionFactorChargeToElectrons = 6.25*TMath::Power(10.,15.);

	// Avogadro constant: 6x10^23
	// number of atoms in 12 grams of the isotope 12C
	// 1 gr -> 6x10^23 / 12 = 5x10^22 atoms
//	double ConversionFactorGramToAtoms = 5*TMath::Power(10.,22);
	double AvogadroNumber = 6*TMath::Power(10.,23);
	double OverallUnitConversionFactor = ConversionFactorChargeToElectrons * AvogadroNumber;

	
	// Clas dOmega 

	double dOmega = 0.01; // sr

	// Mass Numbers
	std::map<TString,double> MassNumber =
	{
		{ "4He", 4 },
		{ "12C", 12 },
		{ "CH2", 14 },
		{ "56Fe", 56 }
	};

	// mC // Regular files
	std::map<std::pair<TString,TString>,double> IntegratedCharge =
	{
		{ std::make_pair("4He", "2_261"), 1.08 },
		{ std::make_pair("4He", "4_461"), 0.87 },
//		{ std::make_pair("12C", "1_161"), 0.19 },
		{ std::make_pair("12C", "1_161"), 0.079 },
		{ std::make_pair("12C", "2_261"), 1.79 },
		{ std::make_pair("12C", "4_461"), 2.14 },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0.34168 },
		{ std::make_pair("CH2", "4_461"), 0.188218873 },
		{ std::make_pair("56Fe", "2_261"), 0.22 },
		{ std::make_pair("56Fe", "4_461"), 0.29 }
	};

	// mC // Good run list all runs // pinned files by Stuart F
	std::map<std::pair<TString,TString>,double> IntegratedCharge_PinnedFiles =
	{
		{ std::make_pair("4He", "2_261"), 1.16584 },
		{ std::make_pair("4He", "4_461"), 0.97884 },
		{ std::make_pair("12C", "1_161"), 0.079 },
		{ std::make_pair("12C", "2_261"), 2.83649 },
//		{ std::make_pair("12C", "2_261"), 0.007609864 },
		{ std::make_pair("12C", "4_461"), 2.31146 },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0.34168 },
		{ std::make_pair("CH2", "4_461"), 0.188218873 },
		{ std::make_pair("56Fe", "2_261"), 0.217238 },
		{ std::make_pair("56Fe", "4_461"), 0.308581 }
	};

	// mC // Filtered runs
	std::map<std::pair<TString,TString>,double> IntegratedCharge_FilterRuns =
	{
		{ std::make_pair("4He", "2_261"), 0.024727582 },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.05392387 },
		{ std::make_pair("12C", "2_261"), 0.060684561 },
		{ std::make_pair("12C", "4_461"), 0.099557913 },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0.34168 },
		{ std::make_pair("CH2", "4_461"), 0.188218873 },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0.089507691 }
	};

	// mC // New Filtered runs
	std::map<std::pair<TString,TString>,double> IntegratedCharge_NewFilterRuns =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.070707652 },
		{ std::make_pair("12C", "2_261"), 0. },
		{ std::make_pair("12C", "4_461"), 0. },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0.34168 },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0. }
	};

	// mC // Good run list all runs
	std::map<std::pair<TString,TString>,double> IntegratedCharge_GoodRunList_AllRuns =
	{
		{ std::make_pair("4He", "2_261"), 1.16584 },
		{ std::make_pair("4He", "4_461"), 0.97884 },
		{ std::make_pair("12C", "1_161"), 0.18432 },
//		{ std::make_pair("12C", "2_261"), 2.8682265 },
		{ std::make_pair("12C", "2_261"), 0.007609864 },
		{ std::make_pair("12C", "4_461"), 2.31146 },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0.34168 },
		{ std::make_pair("CH2", "4_461"), 0.188218873 },
		{ std::make_pair("56Fe", "2_261"), 0.217238 },
		{ std::make_pair("56Fe", "4_461"), 0.308581 }
	};

	// mC // Good run list low current runs
	std::map<std::pair<TString,TString>,double> IntegratedCharge_GoodRunList_LowCurrentRuns =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.079 },
		{ std::make_pair("12C", "2_261"), 0. },
		{ std::make_pair("12C", "4_461"), 0. },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0. },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0. }
	};

	// mC // Good run list high current runs
	std::map<std::pair<TString,TString>,double> IntegratedCharge_GoodRunList_HighCurrentRuns =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.105 },
		{ std::make_pair("12C", "2_261"), 0. },
		{ std::make_pair("12C", "4_461"), 0. },
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0. },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0. }
	};

	// cm
	std::map<std::pair<TString,TString>,double> TargetLength =
	{
		{ std::make_pair("4He", "2_261"), 4.3 }, // 3.72-4.99 // taking the average
		{ std::make_pair("4He", "4_461"), 4.3 }, // 3.72-4.99 // taking the average
		{ std::make_pair("12C", "1_161"), 0.1 },
		{ std::make_pair("12C", "2_261"), 0.1 },
		{ std::make_pair("12C", "4_461"), 0.1 },
//		{ std::make_pair("CH2", "1_161"), 0.07 },
		{ std::make_pair("CH2", "2_261"), 0.07 },
		{ std::make_pair("CH2", "4_461"), 0.07 },
		{ std::make_pair("56Fe", "2_261"), 0.015 },
		{ std::make_pair("56Fe", "4_461"), 0.015 }
	};

	// g/cm^2
	std::map<std::pair<TString,TString>,double> TargetDensity =
	{
		{ std::make_pair("4He", "2_261"), 0.125 },
		{ std::make_pair("4He", "4_461"), 0.125 },
		{ std::make_pair("12C", "1_161"), 1.786 },
		{ std::make_pair("12C", "2_261"), 1.786 },
		{ std::make_pair("12C", "4_461"), 1.786 },
//		{ std::make_pair("CH2", "1_161"), 1.392 },
		{ std::make_pair("CH2", "2_261"), 1.392 },
		{ std::make_pair("CH2", "4_461"), 1.392 },
		{ std::make_pair("56Fe", "2_261"), 7.872 },
		{ std::make_pair("56Fe", "4_461"), 7.872 }
	};

	// SuSav2 GENIE spline xsec // 10^{-38} cm^2
	std::map<std::pair<TString,TString>,double> SuSav2GenieXSec =
	{
		{ std::make_pair("4He", "2_261"), 8.30934e+07 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 3.01721e+07 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 1.28967e+09 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 2.1024e+08 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 8.36795e+07 }, // Q2 > 0.8
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0. },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 9.66272e+08 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 3.84607e+08 } // Q2 > 0.8
	};

	// SuSav2 GENIE number events 
	std::map<std::pair<TString,TString>,double> SuSav2NumberEvents =
	{
		{ std::make_pair("4He", "2_261"), 19800000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 20000000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 39700000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 201300000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 179600000 }, // Q2 > 0.8
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0. },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 152800000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 130800000 } // Q2 > 0.8
	};

	// G2018 GENIE spline xsec // cm^2
	std::map<std::pair<TString,TString>,double> G2018GenieXSec =
	{
		{ std::make_pair("4He", "2_261"), 6.55943e+07 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 2.73355e+07 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"),  1.10931e+09 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 1.96812e+08 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 8.20065e+07 }, // Q2 > 0.8
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0. },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"),9.02272e+08  }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 3.76765e+08 } // Q2 > 0.8
	};

	// G2018 GENIE number events 
	std::map<std::pair<TString,TString>,double> G2018NumberEvents =
	{
		{ std::make_pair("4He", "2_261"), 20000000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 9000000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 50000000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 227100000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 150100000 }, // Q2 > 0.8
//		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0. },
		{ std::make_pair("CH2", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 50000000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 150100000 } // Q2 > 0.8
	};

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TCanvas* PlotCanvas = new TCanvas(E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
								 E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
								 205,34,1024,768);

				PlotCanvas->SetBottomMargin(0.2);
				PlotCanvas->SetLeftMargin(0.17);

				// ---------------------------------------------------------------------------------------

				TLegend* leg = leg = new TLegend(0.2,0.73,0.53,0.87);

				leg->SetNColumns(1);

				double max = -99.;
				double min = 1E12;

				double DataIntegral = 1.;
				double SuSav2Integral = 1.;
				double G2018Integral = 1.;

				// Loop over the FSI Models

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					// Loop over the nuclei

					Plots.clear();

					for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

						TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						Plots[WhichNucleus]->SetLineColor(Colors[WhichNucleus]);
						CenterAxisTitle(Plots[WhichNucleus]);

						// --------------------------------------------------------------------------------------

						// X-axis label

						Plots[WhichNucleus]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichNucleus]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichNucleus]->GetXaxis()->SetLabelSize(TextSize);
						Plots[WhichNucleus]->GetXaxis()->SetTitleSize(TextSize);
						Plots[WhichNucleus]->GetXaxis()->SetTitleOffset(1.05);

						// X-axis Title

						Plots[WhichNucleus]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]);

						// Y-axis Title/Tick Size

						Plots[WhichNucleus]->GetYaxis()->SetTitleSize(TextSize-0.01); 
						Plots[WhichNucleus]->GetYaxis()->SetTickSize(0.02);
						Plots[WhichNucleus]->GetYaxis()->SetLabelSize(TextSize);
						//Plots[WhichNucleus]->GetYaxis()->SetTitle("Weighted Events / (GeV mC cm)");
						Plots[WhichNucleus]->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [#frac{#mub}{sr GeV nucleus}]");

						// --------------------------------------------------------------------------------------

						Plots[WhichNucleus]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichNucleus]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichNucleus]->GetYaxis()->SetTitleOffset(1.1); 

						Plots[WhichNucleus]->SetLineWidth(LineWidth);

						// --------------------------------------------------------------------------------------

						// Scaling Factor
						// Scale to data integral after dividing by integrated charge & length

						double ScalingFactor = 1.;
						double ScaleBy = 1.;

int MinBin = 0;
int MaxBin = Plots[WhichNucleus]->GetXaxis()->GetNbins()+1;

//if ( OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_0") {

//	double perc = 0.05;
//	if (DoubleE[WhichEnergy] == 1.161) { perc = 0.1; }
//	double LowE = (1-perc)*DoubleE[WhichEnergy];
//	double HighE = (1+perc)*DoubleE[WhichEnergy];


	// 1.1 GeV

//	double LowE = 0.;
//	double HighE = 0.24;

	// 2.2 GeV
//	double LowE = 0.;
//	double HighE = 0.4;

	// 4.4 GeV

//	double LowE = 0.;
//	double HighE = 1.2;


//	MinBin = Plots[WhichNucleus]->FindBin(LowE);
//	MaxBin = Plots[WhichNucleus]->FindBin(HighE);

//}

//						if (DoubleE[WhichEnergy] == 1.161) {} 
//							{ for (int i = 0; i < 4; i++) { Plots[WhichNucleus]->Rebin(); Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.4,1.7); } }

//						if ( DoubleE[WhichEnergy] == 2.261) 
//							{ for (int i = 0; i < 4; i++) { Plots[WhichNucleus]->Rebin(); Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.4,3.); } }

//						if ( DoubleE[WhichEnergy] == 4.461) 
//							{ for (int i = 0; i < 4; i++) { Plots[WhichNucleus]->Rebin(); Plots[WhichNucleus]->GetXaxis()->SetRangeUser(1.5,6.); } }

						if (FSILabel[WhichFSIModel] == "Data") { 

							ScaleBy = 1. / ( IntegratedCharge[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]] ) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);

							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "Data_FilterRuns") { 

							ScaleBy = 1. / (IntegratedCharge_FilterRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "Data_NewFilterRuns") { 

							ScaleBy = 1. / (IntegratedCharge_NewFilterRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "GoodRunList_Data") { 

							ScaleBy = 1. / (IntegratedCharge_GoodRunList_AllRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "LowCurrent_GoodRunList_Data") { 

							ScaleBy = 1. / (IntegratedCharge_GoodRunList_LowCurrentRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}


						if (FSILabel[WhichFSIModel] == "HighCurrent_GoodRunList_Data") { 

							ScaleBy = 1. / (IntegratedCharge_GoodRunList_HighCurrentRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "Pinned Data") { 

							ScaleBy = 1. / (IntegratedCharge_PinnedFiles[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichNucleus]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						// -------------------------------------------------------------------------------------------------------------------------------------------------

						if (FSILabel[WhichFSIModel] == "SuSav2" || FSILabel[WhichFSIModel] == "SuSav2_NoAccMaps" ) { 

							ScalingFactor = (SuSav2GenieXSec[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] * TMath::Power(10.,-38.) *\
								ConversionFactorCm2ToMicroBarn / (SuSav2NumberEvents[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
								dOmega) ) ;

							Plots[WhichNucleus]->Scale(ScalingFactor);
							ScaleBy = ScalingFactor;
							SuSav2Integral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "G2018") { 

							ScalingFactor = ( G2018GenieXSec[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] * TMath::Power(10.,-38.) *\
								ConversionFactorCm2ToMicroBarn / (G2018NumberEvents[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
								dOmega) );

							Plots[WhichNucleus]->Scale(ScalingFactor);
							ScaleBy = ScalingFactor;
							G2018Integral =  Plots[WhichNucleus]->Integral(MinBin,MaxBin);
						}

						cout << FSILabel[WhichFSIModel] << " scaling factor = " << ScaleBy << endl;

//						double ScalingFactor = DataIntegral / Plots[WhichNucleus]->Integral();

//						if (FSILabel[WhichFSIModel] == "SuSav2") { ScalingFactor = DataIntegral / SuSav2Integral; }
//						if (FSILabel[WhichFSIModel] == "G2018") { ScalingFactor = DataIntegral / G2018Integral; }

//						double ScalingFactorIntegral = DataIntegral / Plots[WhichNucleus]->Integral();

//						if (FSILabel[WhichFSIModel] == "SuSav2") { ScalingFactorIntegral = DataIntegral / SuSav2Integral; }
//						if (FSILabel[WhichFSIModel] == "G2018") { ScalingFactorIntegral = DataIntegral / G2018Integral; }

//if (FSILabel[WhichFSIModel] == "SuSav2" || FSILabel[WhichFSIModel] == "G2018") {
//cout << "ScalingFactorIntegral = " << ScalingFactorIntegral<< endl;
//}

//						Plots[WhichNucleus]->Scale(ScalingFactor);

						// -----------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						ReweightPlots(Plots[WhichNucleus]);

						// --------------------------------------------------------------------------------------

						// Rebining & ranges


						if (string(NameOfPlots[WhichPlot]).find("Omega_FullyInclusive") != std::string::npos) {

							if (DoubleE[WhichEnergy] == 1.161)  
								{ for (int i = 0; i < 5; i++) { Plots[WhichNucleus]->Rebin(); } Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.,0.7);  }

							if ( DoubleE[WhichEnergy] == 2.261) 
								{ for (int i = 0; i < 5; i++) { Plots[WhichNucleus]->Rebin(); } Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.,1.5); }

							if ( DoubleE[WhichEnergy] == 4.461) 
								{ for (int i = 0; i < 6; i++) { Plots[WhichNucleus]->Rebin(); } Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.5,3.); }

						} else {

							if (DoubleE[WhichEnergy] == 1.161)  
								{ /*for (int i = 0; i < 5; i++) { Plots[WhichNucleus]->Rebin(); }*/ Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.4,1.7); }

							if ( DoubleE[WhichEnergy] == 2.261) 
								{ /*for (int i = 0; i < 5; i++) { Plots[WhichNucleus]->Rebin(); }*/ Plots[WhichNucleus]->GetXaxis()->SetRangeUser(0.6,3.); }

							if ( DoubleE[WhichEnergy] == 4.461) 
								{ /*for (int i = 0; i < 6; i++) { Plots[WhichNucleus]->Rebin(); }*/ Plots[WhichNucleus]->GetXaxis()->SetRangeUser(1.5,6.); }

						}

						// ----------------------------------------------------------------------------------

						// Apply Systematic Uncertainties on Data Points

						double SystUnc = 0;
						if ( DoubleE[WhichEnergy] == 1.161 ) { SystUnc = SystUnc1GeV; }
						if ( DoubleE[WhichEnergy] == 2.261 ) { SystUnc = SystUnc2GeV; }
						if ( DoubleE[WhichEnergy] == 4.461 ) { SystUnc = SystUnc4GeV; }

						if (FSILabel[WhichFSIModel] == "Data") { ApplySystUnc(Plots[WhichNucleus], SystUnc); }

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichNucleus]->GetMaximum();

						if (localmax > max) { max = localmax; }
						double height = 1.05;
						if ( xBCut[WhichxBCut] == "xBCut" ) { height = 1.1; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						TString XLabel = Plots[WhichNucleus]->GetXaxis()->GetTitle();
						Plots[0]->GetXaxis()->SetTitle(XLabel);

						Plots[WhichNucleus]->GetXaxis()->SetNdivisions(Ndivisions);
						Plots[WhichNucleus]->GetYaxis()->SetNdivisions(Ndivisions);
//Plots[WhichNucleus]->Divide(Plots[0]);
						// --------------------------------------------------------------------------------------------------

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichNucleus]->SetMarkerStyle(20); 
							Plots[WhichNucleus]->SetMarkerSize(2.); 
							Plots[WhichNucleus]->SetMarkerColor(Colors[WhichNucleus]); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichNucleus]->Draw("e same"); 

						} else { 

//							Plots[WhichNucleus]->Draw("hist same"); // draw them as histos
							Plots[WhichNucleus]->SetLineStyle(Style[WhichFSIModel]); 
							Plots[WhichNucleus]->Draw("C hist same");  // draw them as lines
							Plots[0]->Draw("e same"); 

//							if (FSILabel[WhichFSIModel] == "G2018") {
//							
//								TLatex* latex = new TLatex();
//								latex->SetTextFont(FontStyle);
//								latex->SetTextSize(TextSize);
//								latex->DrawLatexNDC(0.17,0.6,"SF G2018 = "+ToString(round(ScalingFactor*TMath::Power(10,8.),acc)));

//							}

//							if (FSILabel[WhichFSIModel] == "SuSav2") {
//							
//								TLatex* latex = new TLatex();
//								latex->SetTextFont(FontStyle);
//								latex->SetTextSize(TextSize);
//								latex->DrawLatexNDC(0.17,0.5,"SF SuSav2 = "+ToString(round(ScalingFactor*TMath::Power(10,8.),acc)));

//							}

						}

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
							{ leg->AddEntry(Plots[WhichNucleus],LabelsOfSamples[WhichNucleus], "lep");}
						else { leg->AddEntry(Plots[WhichNucleus],LabelsOfSamples[WhichNucleus], "l"); }
				

		                                // ---------------------------------------------------------------------------------------------------
		                                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

					leg->SetBorderSize(0);
					leg->SetTextFont(FontStyle);
					leg->SetTextSize(TextSize);
					leg->Draw(); // Just data + e.g. susav2

					// -----------------------------------------------------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

//					PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
//						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

					//delete PlotCanvas;

					// -----------------------------------------------------------------------------------------------------------------------------------------

				} // End of the loop over the nuclei

			} // End of the loop over the plots

			TCanvas* DiffCanvas = new TCanvas("DiffCanvas","DiffCanvas",205,34,1024,768);
			DiffCanvas->SetBottomMargin(0.2);
			DiffCanvas->SetLeftMargin(0.17);
			
			TH1D* Clone = (TH1D*)Plots[0]->Clone("Clone");
			Clone->Add(Plots[1],-1);
			Clone->Scale(0.5);
			DiffCanvas->cd();
			Clone->Draw();


//				TCanvas* RatioCanvas = new TCanvas("Ratio","Ratio",205,34,1024,768);

//				for (int i = 2; i < NFSIModels-1; i++) {

//					Plots[i+1]->Divide(Plots[0]);
//					Plots[i+1]->Draw("e same");

//				}

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
