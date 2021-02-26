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
		{ "40Ar_G00_00a_00_000_EM+MEC_Q2_0_0", 0.},

		{ "40Ar_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 0.},
		{ "40Ar_G18_10a_02_11a_CCinclMEC_Q2_0_0", 0.},
		{ "40Ar_G18_02a_00_000_CCinclMEC_Q2_0_0", 0.},
		{ "40Ar_G00_00a_00_000_CCinclMEC_Q2_0_0", 0.},

		{ "CH2_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH2_G18_10a_02_11a_EM+MEC_Q2_0_0", 0.},
		{ "CH2_G18_02a_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH2_G00_00a_00_000_EM+MEC_Q2_0_0", 0.},

		{ "CH2_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 0.},
		{ "CH2_G18_10a_02_11a_CCinclMEC_Q2_0_0", 0.},
		{ "CH2_G18_02a_00_000_CCinclMEC_Q2_0_0", 0.},
		{ "CH2_G00_00a_00_000_CCinclMEC_Q2_0_0", 0.},

		{ "CH_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH_G18_10a_02_11a_EM+MEC_Q2_0_0", 0.},
		{ "CH_G18_02a_00_000_EM+MEC_Q2_0_0", 0.},
		{ "CH_G00_00a_00_000_EM+MEC_Q2_0_0", 0.},

		{ "CH_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 0.},
		{ "CH_G18_10a_02_11a_CCinclMEC_Q2_0_0", 0.},
		{ "CH_G18_02a_00_000_CCinclMEC_Q2_0_0", 0.},
		{ "CH_G00_00a_00_000_CCinclMEC_Q2_0_0", 0.},

	};

	static std::map<TString,double> GENIEEvents =
	{
		{ "40Ar_BNBFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 4500000},
		{ "40Ar_BNBFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5000000},
		{ "40Ar_BNBFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5000000},
		{ "40Ar_BNBFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "40Ar_BNBFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 3800000},
		{ "40Ar_BNBFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 2400000},
		{ "40Ar_BNBFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 4000000},
		{ "40Ar_BNBFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 0},			// producing C/H splines

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 4600000},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5100000},
		{ "40Ar_DUNEFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5000000},
		{ "40Ar_DUNEFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 3400000},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 4000000},
		{ "40Ar_DUNEFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 4000000},
		{ "40Ar_DUNEFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 0},         		// producing C/H splines

		{ "CH2_NOvAFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0},         		// talk to marco roda
		{ "CH2_NOvAFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5000000},
		{ "CH2_NOvAFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5000000},
		{ "CH2_NOvAFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "CH2_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 4000000},     
		{ "CH2_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 4000000},
		{ "CH2_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 4000000},
		{ "CH2_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 0},        		// producing C/H splines

		{ "CH_T2KFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0},           		// talk to marco roda
		{ "CH_T2KFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5000000},
		{ "CH_T2KFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 4900000},
		{ "CH_T2KFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "CH_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 0},      		 // talk to marco roda
		{ "CH_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 4000000},
		{ "CH_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 4000000},
		{ "CH_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 0},                		  // producing C/H splines

		{ "C12_1161_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 10000000},    
		{ "C12_1161_G18_10a_02_11a_CCinclMEC_Q2_0_0", 10000000},    
		{ "C12_1161_G18_02a_00_000_CCinclMEC_Q2_0_0", 10000000}, 
		{ "C12_1161_G00_00a_00_000_CCinclMEC_Q2_0_0", 0},

		{ "C12_1161_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0},    
		{ "C12_1161_G18_10a_02_11a_EM+MEC_Q2_0_0", 0},    
		{ "C12_1161_G18_02a_00_000_EM+MEC_Q2_0_0", 0}, 
		{ "C12_1161_G00_00a_00_000_EM+MEC_Q2_0_0", 0},

		{ "C12_1161_GTEST19_10b_00_000_CCinclMEC_Q2_0_1_NoFSI", 10000000},    
		{ "C12_1161_G18_10a_02_11a_CCinclMEC_Q2_0_1_NoFSI", 10000000},    
		{ "C12_1161_G18_02a_00_000_CCinclMEC_Q2_0_1_NoFSI", 10000000}, 
		{ "C12_1161_G00_00a_00_000_CCinclMEC_Q2_0_1_NoFSI", 0},

		{ "C12_1161_GTEST19_10b_00_000_EM+MEC_Q2_0_1_NoFSI", 0},    
		{ "C12_1161_G18_10a_02_11a_EM+MEC_Q2_0_1_NoFSI", 0},    
		{ "C12_1161_G18_02a_00_000_EM+MEC_Q2_0_1_NoFSI", 0}, 
		{ "C12_1161_G00_00a_00_000_EM+MEC_Q2_0_1_NoFSI", 0},       

	};

//  ------------------------------------------------------------------------------

#endif
