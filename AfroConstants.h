#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <TF1.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

	// ------------------------------------------------------------------------------------

	// Constants

	// ------------------------------------------------------------------------------------

	// Dimensions of TPads

	double Xmin = 0.14, Xmax = 1.;
	double Ymax = 1., Ymin = 0.05;
	double Xstep = (Xmax - Xmin) / 3.;
	double Ystep = ( Ymax - Ymin  ) / 2.;
	double space = 0.07;

	// ------------------------------------------------------------------------------------

	const int Ndivisions = 6;
	const int LineWidth = 3;
	const int FontStyle = 132;
	const double TextSize = 0.07;
	const int MarkerStyle = 20;
	const int MarkerSize = 2.;
	const double acc = 3.;

	// ------------------------------------------------------------------------------------

	const TString GlobalPathToFiles = "/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/";		
	const TString version = "v3_0_6/";	
/*	const TString DoubleXSecTitle = "#frac{d^{2}#sigma}{d#Omega dE} [#frac{#mub}{sr GeV nucleus}]";*/
	const TString DoubleXSecTitle = "Normalized Yield";
	const TString DoubleAccCorrXSecTitle = "Cross Section";

	// Conversion factors for extraction of absolute cross sections

	const double ConversionFactorCm2ToMicroBarn = TMath::Power(10.,30.);

	// Uncertainties from Mariana's analysis note

	const double SystUnc1GeV = 0.02; // 2% syst uncertainty at 1.161 GeV
	const double SystUnc2GeV = 0.021; // 2.1% syst uncertainty at 2.261 GeV
	const double SystUnc4GeV = 0.047; // 4.7% syst uncertainty at 4.461 GeV

	// Sector Uncertainties from Afro's study

	const double SectorSystUnc1GeV = 0.06; // 6% syst uncertainty at 1.161 GeV
	const double SectorSystUnc2GeV = 0.06; // 6% syst uncertainty at 2.261 GeV
	const double SectorSystUnc4GeV = 0.06; // 6% syst uncertainty at 4.461 GeV

	// Larry/Axel's suggestion for scaling down the last 2 bins by EnhaceTail

	const double EnhaceTail = 1./1.;

	// Clas dOmega 

//	const double dOmega = 0.02; // sr
	const double dOmega = 0.015; // sr

	// 1e -> 1.6x10^-19 C
	// 1C -> 6.25x10^18 e
	// 1mC -> 6.25x10^15 e
	// Thus the numbers above have to be multiplied by this number to make sure that we refer to electrons and not charge

	double ConversionFactorChargeToElectrons = 6.25*TMath::Power(10.,15.);

	// Avogadro constant: 6x10^23
	// number of atoms in 12 grams of the isotope 12C
	// 1 gr -> 6x10^23 / 12 = 5x10^22 atoms
//	double ConversionFactorGramToAtoms = 5*TMath::Power(10.,22);
	double AvogadroNumber = 6.02*TMath::Power(10.,23);
	double OverallUnitConversionFactor = ConversionFactorChargeToElectrons * AvogadroNumber;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// Maps 

	// Plot names to plot labels

	static std::map<TString,TString> PlotNamesToLabels =
	{
		{ "DeltaAlphaT", "(e,e'p)_{1p0#pi} #delta#alpha_{T} [deg]" },
		{ "DeltaPhiT", "(e,e'p)_{1p0#pi} #delta#phi_{T} [deg]" },
		{ "ECalReso", "E^{cal} Feeddown" },
		{ "EQEReso", "E^{QE} Feeddown" },
		{ "ECal", "(e,e'p)_{1p0#pi} E^{Cal} [GeV]" },
		{ "DeltaPT", "(e,e'p)_{1p0#pi} P_{T} [GeV/c]" }
	};

	// FSI Models to Labels

	static std::map<TString,TString> FSIModelsToLabels =
	{
		{ "MikhailCook_Data", "Mikhail Data" },
		{ "Pinned_Data_Final", "Pinned Data" },
		{ "Pinned_Data_NewFiducials_SixSectors", "Pinned Data" },
		{ "SuSav2_RadCorr_LFGM", "SuSav2" },
		{ "SuSav2_NoRadCorr_LFGM", "SuSav2 NoRad" },
		{ "SuSav2_RadCorr_LFGM_Truth_WithFidAcc", "SuSav2" },
		{ "SuSav2_RadCorr_LFGM_Truth_WithoutFidAcc", "SuSav2" },
		{ "SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc", "SuSav2 NoRad" },
		{ "SuSav2_RadCorr_LFGM_Truth_WithoutFidAcc_NoThetaCut", "SuSav2" },
		{ "SuSav2_RadCorr_LFGM_Truth0pi_WithFidAcc", "SuSav2" },
		{ "SuSav2_RadCorr_LFGM_Truth0pi_WithoutFidAcc", "SuSav2" },
		{ "hA2018_Final_RadCorr_LFGM", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Offset", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth_WithFidAcc", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth_WithFidAcc_Offset", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth_WithoutFidAcc", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth_WithoutFidAcc_NoThetaCut", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth_WithoutFidAcc_Offset", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth0pi_WithFidAcc", "G2018" },
		{ "hA2018_Final_RadCorr_LFGM_Truth0pi_WithoutFidAcc", "G2018" },
		{ "Pinned_Data_Final_SixSectors", "Pinned Data" },
		{ "SuSav2_RadCorr_LFGM_SixSectors", "SuSav2" },
		{ "hA2018_Final_RadCorr_LFGM_SixSectors", "G2018" },
	};

	// Mass Numbers

	static std::map<TString,double> MassNumber =
	{
		{ "1H", 1 },
		{ "4He", 4 },
		{ "12C", 12 },
		{ "CH2", 14 },
		{ "56Fe", 56 }
	};

	// mC // Regular files // Data_Final

	static std::map<std::pair<TString,TString>,double> IntegratedCharge =
	{
		{ std::make_pair("4He", "2_261"), 1.08 },
		{ std::make_pair("4He", "4_461"), 0.87 },
//		{ std::make_pair("12C", "1_161"), 0.19 },
		{ std::make_pair("12C", "1_161"), 0.079 },
		{ std::make_pair("12C", "2_261"), 1.79 },
		{ std::make_pair("12C", "4_461"), 2.14 },
		{ std::make_pair("56Fe", "2_261"), 0.22 },
		{ std::make_pair("56Fe", "4_461"), 0.29 }
	};

	// mC // Good run list all runs // Mikhail cook pass3

	static std::map<std::pair<TString,TString>,double> IntegratedCharge_MikhailFiles =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0. },
		{ std::make_pair("12C", "2_261"), 2.47238 },
		{ std::make_pair("12C", "4_461"), 2.06258 },
		{ std::make_pair("CH2", "1_161"), 0. },
		{ std::make_pair("CH2", "2_261"), 0.31532 },
		{ std::make_pair("CH2", "4_461"), 0.17789 },
		{ std::make_pair("56Fe", "2_261"), 0.20595 },
		{ std::make_pair("56Fe", "4_461"), 0.24576 }
	};

	// mC // Good run list all runs // pinned files by Stuart F

	static std::map<std::pair<TString,TString>,double> IntegratedCharge_PinnedFiles =
	{
		{ std::make_pair("4He", "2_261"), 1.16584 },
		{ std::make_pair("4He", "4_461"), 0.97884 },
		{ std::make_pair("12C", "1_161"), 0.079 },
//		{ std::make_pair("CH2", "1_161"), 0.070707652 },

//		{ std::make_pair("CH2", "1_161"), 0.0794 },
		{ std::make_pair("CH2", "1_161"), 0.068 }, // L.W. Dec 17 2020

		{ std::make_pair("12C", "2_261"), 2.83649 },
//		{ std::make_pair("12C", "2_261"), 0.007609864 },
		{ std::make_pair("12C", "4_461"), 2.31146 },
		{ std::make_pair("56Fe", "2_261"), 0.217238 },
		{ std::make_pair("56Fe", "4_461"), 0.308581 }
	};

	// mC // Filtered runs

	static std::map<std::pair<TString,TString>,double> IntegratedCharge_FilterRuns =
	{
		{ std::make_pair("4He", "2_261"), 0.024727582 },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.05392387 },
		{ std::make_pair("12C", "2_261"), 0.060684561 },
		{ std::make_pair("12C", "4_461"), 0.099557913 },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0.089507691 }
	};

	// mC // New Filtered runs

	static std::map<std::pair<TString,TString>,double> IntegratedCharge_NewFilterRuns =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.070707652 },
		{ std::make_pair("12C", "2_261"), 0. },
		{ std::make_pair("12C", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0. }
	};

	// mC // Good run list all runs
	static std::map<std::pair<TString,TString>,double> IntegratedCharge_GoodRunList_AllRuns =
	{
		{ std::make_pair("4He", "2_261"), 1.16584 },
		{ std::make_pair("4He", "4_461"), 0.97884 },
		{ std::make_pair("12C", "1_161"), 0.18432 },
//		{ std::make_pair("12C", "2_261"), 2.8682265 },
		{ std::make_pair("12C", "2_261"), 0.007609864 },
		{ std::make_pair("12C", "4_461"), 2.31146 },
		{ std::make_pair("56Fe", "2_261"), 0.217238 },
		{ std::make_pair("56Fe", "4_461"), 0.308581 }
	};

	// mC // Good run list low current runs

	static std::map<std::pair<TString,TString>,double> IntegratedCharge_GoodRunList_LowCurrentRuns =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.079 },
		{ std::make_pair("12C", "2_261"), 0. },
		{ std::make_pair("12C", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0. }
	};

	// mC // Good run list high current runs

	static std::map<std::pair<TString,TString>,double> IntegratedCharge_GoodRunList_HighCurrentRuns =
	{
		{ std::make_pair("4He", "2_261"), 0. },
		{ std::make_pair("4He", "4_461"), 0. },
		{ std::make_pair("12C", "1_161"), 0.105 },
		{ std::make_pair("12C", "2_261"), 0. },
		{ std::make_pair("12C", "4_461"), 0. },
		{ std::make_pair("56Fe", "2_261"), 0. },
		{ std::make_pair("56Fe", "4_461"), 0. }
	};

	// cm

	static std::map<std::pair<TString,TString>,double> TargetLength =
	{
		{ std::make_pair("4He", "2_261"), 4.3 }, // 3.72-4.99 // taking the average
		{ std::make_pair("4He", "4_461"), 4.3 }, // 3.72-4.99 // taking the average
		{ std::make_pair("CH2", "1_161"), 0.07 },
		{ std::make_pair("12C", "1_161"), 0.1 },
		{ std::make_pair("12C", "2_261"), 0.1 },
		{ std::make_pair("12C", "4_461"), 0.1 },
		{ std::make_pair("56Fe", "2_261"), 0.015 },
		{ std::make_pair("56Fe", "4_461"), 0.015 }
	};

	// g/cm^3

	static std::map<std::pair<TString,TString>,double> TargetDensity =
	{
		{ std::make_pair("4He", "2_261"), 0.125 },
		{ std::make_pair("4He", "4_461"), 0.125 },
		{ std::make_pair("CH2", "1_161"), 1.392 },
		{ std::make_pair("12C", "1_161"), 1.786 },
		{ std::make_pair("12C", "2_261"), 1.786 },
		{ std::make_pair("12C", "4_461"), 1.786 },
		{ std::make_pair("56Fe", "2_261"), 7.872 },
		{ std::make_pair("56Fe", "4_461"), 7.872 }
	};

	// SuSav2 GENIE spline xsec // 10^{-38} cm^2

	static std::map<std::pair<TString,TString>,double> SuSav2GenieXSec =
	{
		{ std::make_pair("4He", "2_261"), 8.30934e+07 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 3.01721e+07 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 1.28967e+09 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 2.1024e+08 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 8.36795e+07 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 9.66272e+08 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 3.84607e+08 } // Q2 > 0.8
	};

	// No Rad SuSav2 GENIE number events 

	static std::map<std::pair<TString,TString>,double> NoRadSuSav2NumberEvents =
	{
		{ std::make_pair("4He", "2_261"), 20000000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 17700000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 19800000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 174600000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 164300000 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 167000000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 141000000 } // Q2 > 0.8
	};

	// Rad SuSav2 GENIE number events 

	static std::map<std::pair<TString,TString>,double> SuSav2NumberEvents =
	{
		{ std::make_pair("4He", "2_261"), 19800000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 20000000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 39700000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 201300000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 179600000 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 152800000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 130800000 } // Q2 > 0.8
	};

	// G2018 GENIE spline xsec // 10^{-38} cm^2

	static std::map<std::pair<TString,TString>,double> G2018GenieXSec =
	{
		{ std::make_pair("1H", "1_161"),  1.4515324e+08 }, // Q2 > 0.1
		//(double) 1.1038574e+09 // Q2 > 0.02
		{ std::make_pair("1H", "2_261"),  20943873. }, // Q2 > 0.4
		{ std::make_pair("1H", "4_461"),  8521094.7 }, // Q2 > 0.8
		{ std::make_pair("4He", "2_261"), 6.55943e+07 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 2.73355e+07 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"),  1.10931e+09 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 1.96812e+08 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 8.20065e+07 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"),9.02272e+08  }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 3.76765e+08 } // Q2 > 0.8
	};

	// G2018 GENIE number events 

	static std::map<std::pair<TString,TString>,double> G2018NumberEvents =
	{
		{ std::make_pair("1H", "1_161"), 3000000 }, // Q2 > 0.1
		{ std::make_pair("4He", "2_261"), 20000000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 9000000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 50000000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 227100000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 150100000 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 50000000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 150100000 } // Q2 > 0.8

	};

	//  ------------------------------------------------------------------------------

	const std::vector<int> BreakDownColors{kBlue,429,410,610};
	const std::vector<int> SectorColors{kBlack,610,410,kRed+1,kGreen+3,kBlue};
	const std::vector<int> Style{1,1,kDashed,1,1};
	const std::vector<TString> GenieFSILabel{"QE","MEC","RES","DIS"};
	const std::vector<int> DataSetColors{1,1,1,1,1};

	//  ------------------------------------------------------------------------------


#endif
