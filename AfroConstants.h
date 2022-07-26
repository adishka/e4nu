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

	const int FontStyle = 132;
	const double TextSize = 0.07;
	const int Ndivisions = 6;
	const int LineWidth = 3;	

	// ------------------------------------------------------------------------------------

	const TString GlobalPathToFiles = "/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/";		
	const TString DoubleXSecTitle = "Normalized Yield";

	// Conversion factors for extraction of absolute cross sections

	const double ConversionFactorCm2ToMicroBarn = TMath::Power(10.,30.);

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

	// FSI Models to Labels

	static std::map<TString,TString> FSIModelsToLabels =
	{

		// ------------------------------------------------------------------------------------------------------

		{ "SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc", "SuSav2 NoRad" },
		{ "SuSav2_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc", "SuSav2 NoRad" },

		// ------------------------------------------------------------------------------------------------------

		{ "hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc", "G2018 NoRad" },
		{ "hA2018_Final_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc", "G2018 NoRad" },
		
		// ------------------------------------------------------------------------------------------------------

		{ "Fortran_SF_NoRadCorr_LFGM_Truth_WithoutFidAcc", "Fortran SF NoRad" },		

		// ------------------------------------------------------------------------------------------------------



	};
	
	//--------------------------------//

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

		{ std::make_pair("4He", "2_261"),  20000000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"),  17700000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"),  19800000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"),  174600000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"),  164300000 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 167000000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 190600000 } // Q2 > 0.8
	};

	//--------------------------------//

	// G2018 GENIE spline xsec // 10^{-38} cm^2

	static std::map<std::pair<TString,TString>,double> G2018GenieXSec =
	{
		{ std::make_pair("1H", "1_161"),  1.4515324e+08 }, // Q2 > 0.1
		{ std::make_pair("1H", "2_261"),  20943873. }, // Q2 > 0.4
		{ std::make_pair("1H", "4_461"),  8521094.7 }, // Q2 > 0.8
		{ std::make_pair("4He", "2_261"), 6.55943e+07 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 2.73355e+07 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"),  1.10931e+09 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 1.96812e+08 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 8.20065e+07 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"),9.02272e+08  }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 3.8295048e+08 } // Q2 > 0.8
	};

	// No Rad G2018 GENIE number events 

	static std::map<std::pair<TString,TString>,double> NoRadG2018NumberEvents =
	{

		{ std::make_pair("4He", "2_261"),  69000000 }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"),  70400000 }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"),  43900000 }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"),  53200000 }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"),  67900000 }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 69600000 }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 81100000 } // Q2 > 0.8

	};
	
	//--------------------------------//	
	
	// Fortran SF GENIE spline xsec // 10^{-38} cm^2

	static std::map<std::pair<TString,TString>,double> FortranSFGenieXSec =
	{
		{ std::make_pair("1H", "1_161"),  0. }, // Q2 > 0.1
		{ std::make_pair("1H", "2_261"),  0. }, // Q2 > 0.4
		{ std::make_pair("1H", "4_461"),  0. }, // Q2 > 0.8
		{ std::make_pair("4He", "2_261"), 0. }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"), 0. }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"), 3.17e9  }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"), 0. }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"), 0. }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"),0. }, // Q > 0.4
		{ std::make_pair("56Fe", "4_461"),0. } // Q2 > 0.8
	};

	// No Rad Fortran SF GENIE number events 

	static std::map<std::pair<TString,TString>,double> NoRadFortranSFNumberEvents =
	{

		{ std::make_pair("4He", "2_261"),  0. }, // Q2 > 0.4
		{ std::make_pair("4He", "4_461"),  0. }, // Q2 > 0.8
		{ std::make_pair("12C", "1_161"),  300000. }, // Q2 > 0.1
		{ std::make_pair("12C", "2_261"),  0. }, // Q2 > 0.4
		{ std::make_pair("12C", "4_461"),  0. }, // Q2 > 0.8
		{ std::make_pair("56Fe", "2_261"), 0. }, // Q2 > 0.4
		{ std::make_pair("56Fe", "4_461"), 0. } // Q2 > 0.8

	};	
	
	//  ------------------------------------------------------------------------------	

	const std::vector<int> DataSetColors{1,1,1,1,1};

	//  ------------------------------------------------------------------------------

	// XSec labels

	TString XSecEcalLabel = "#frac{d#sigma}{dE_{cal}} #left[#frac{#mub}{GeV}#right]";
	TString XSecEQELabel = "#frac{d#sigma}{dE_{QE}} #left[#frac{#mub}{GeV}#right]";

	TString ResoXSecEcalLabel = "#frac{d#sigma}{dE_{cal}^{Feed}} #left[#mub#right]";
	TString ResoXSecEQELabel = "#frac{d#sigma}{dE_{QE}^{Feed}} #left[#mub#right]";

	//  ------------------------------------------------------------------------------


#endif
