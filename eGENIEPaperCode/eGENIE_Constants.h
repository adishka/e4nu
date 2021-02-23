#ifndef EGENIE_CONSTANTS_H
#define EGENIE_CONSTANTS_H

#include <TF1.h>
#include <TString.h>
#include <TStyle.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

// ------------------------------------------------------------------------------------

	int Ndivisions = 4;
	int FontStyle = 132;
	double TextSize = 0.08;

//	int NBreakDown = 5;
	int NBreakDown = 4; // leaving COH out for now

	const std::vector<int> Colors{kBlue-5,kYellow+1,kOrange+7,kRed+1,kBlue};

	std::vector<TString> ProcessLabel = {"QE","MEC","RES","DIS","COH"}; 

//  ------------------------------------------------------------------------------

	// 10^{-38} cm^2 / nucleus

	static std::map<TString,double> GENIEXSec =
	{
		{ "40Ar_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},
		{ "40Ar_G18_10a_02_11a_EM+MEC_Q2_0_0", 0.},
		{ "40Ar_G18_02a_00_000_EM+MEC_Q2_0_0", 0.},
		{ "40Ar_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},
		{ "40Ar_G18_10a_02_11a_EM+MEC_Q2_0_0", 0.},
		{ "40Ar_G18_02a_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH2_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH2_G18_10a_02_11a_EM+MEC_Q2_0_0", 0.},
		{ "CH2_G18_02a_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH_G18_10a_02_11a_EM+MEC_Q2_0_0", 0.},
		{ "CH_G18_02a_00_000_EM+MEC_Q2_0_0", 0.},
	};

	static std::map<TString,double> GENIEEvents =
	{
		{ "BNB_GTEST19_10b_00_000", 0},
		{ "BNB_G18_10a_02_11a", 0},
		{ "BNB_G18_02a_00_000", 0},
		{ "DUNE_GTEST19_10b_00_000", 0},
		{ "DUNE_G18_10a_02_11a", 0},
		{ "DUNE_G18_02a_00_000", 0},
		{ "NOvA_GTEST19_10b_00_000", 0},
		{ "NOvA_G18_10a_02_11a", 0},
		{ "NOvA_G18_02a_00_000", 0},
		{ "T2K_GTEST19_10b_00_000", 0},
		{ "T2K_G18_10a_02_11a", 0},
		{ "T2K_G18_02a_00_000", 0},
	};

//  ------------------------------------------------------------------------------

#endif
