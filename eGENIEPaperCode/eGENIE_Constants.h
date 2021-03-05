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

	const std::vector<int> Colors{kBlue-5,kYellow+1,kOrange+7,kRed+1,kGreen+1};

/*	const std::vector<int> AlternativeColors{kGreen+1,kBlue-5,kViolet+7,kYellow+1};*/
/*	const std::vector<int> AlternativeColors{kGreen+2,kRed+1,kViolet+7,kYellow+1};*/
/*	const std::vector<int> AlternativeColors{kBlue-2,kGreen-2,kOrange+7,kRed+1};*/
/*	const std::vector<int> AlternativeColors{kBlue-2,kCyan-2,kYellow+1,kRed+1};*/
/*	const std::vector<int> AlternativeColors{kBlue-2,kCyan-2,kYellow+1,kRed+1};*/
/*	const std::vector<int> AlternativeColors{kGreen+3,kYellow+1,kBlue-8,kGreen+2};*/
	const std::vector<int> AlternativeColors{kRed+1,kYellow+1,kOrange+7,kRed-2};

	std::vector<TString> ProcessLabel = {"QE","MEC","RES","DIS","COH"}; 

	//  ------------------------------------------------------------------------------

	// 10^{-38} cm^2 / nucleus

	static std::map<TString,double> GENIEXSec =
	{

		// xsecs [10^-38 cm^2]

		// ------------------------------------------------------------

		// master

		{ "12C_1161_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 6.1253517e+09}, 
		{ "12C_1161_G18_10a_02_11a_EM+MEC_Q2_0_0", 5.3850504e+09},
		{ "12C_1161_G18_02a_00_000_EM+MEC_Q2_0_0", 5.8473812e+09},               
		{ "12C_1161_G00_00a_00_000_EM+MEC_Q2_0_0", 5.3420997e+09},

		{ "12C_1161_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 14.649157},
		{ "12C_1161_G18_10a_02_11a_CCinclMEC_Q2_0_0", 11.993989},
		{ "12C_1161_G18_02a_00_000_CCinclMEC_Q2_0_0", 13.802811},
		{ "12C_1161_G00_00a_00_000_CCinclMEC_Q2_0_0", 13.957122},

		// 12C 1.161 GeV, Q2 > 0.1

		{ "12C_1161_GTEST19_10b_00_000_EM+MEC_Q2_0_1", 1.2874608e+09},            
		{ "12C_1161_G18_10a_02_11a_EM+MEC_Q2_0_1", 1.1661458e+09},                
		{ "12C_1161_G18_02a_00_000_EM+MEC_Q2_0_1", 1.1661458e+09},
		{ "12C_1161_G00_00a_00_000_EM+MEC_Q2_0_1", 1.0616364e+09},     

		{ "12C_1161_GTEST19_10b_00_000_CCinclMEC_Q2_0_1", 0}, 	      // waiting on grid
		{ "12C_1161_G18_10a_02_11a_CCinclMEC_Q2_0_1", 0.},	      // waiting on grid
		{ "12C_1161_G18_02a_00_000_CCinclMEC_Q2_0_1", 0.},	      // waiting on grid
		{ "12C_1161_G00_00a_00_000_CCinclMEC_Q2_0_1", 12.247493},

		// ------------------------------------------------------------

		// DUNE Flux

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 2.21805e+10},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 1.97228e+10},
		{ "40Ar_DUNEFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 1.98551e+10},
		{ "40Ar_DUNEFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 1.78926e+10},

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 86.4405},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 77.842 },
		{ "40Ar_DUNEFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 83.3917},
		{ "40Ar_DUNEFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 81.3907},

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 85.687},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 77.3762},
		{ "40Ar_DUNEFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 82.7183},
		{ "40Ar_DUNEFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 80.4881},

		// ------------------------------------------------------------

		// BNB Flux

		{ "40Ar_BNBFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 1.54007e+10},
		{ "40Ar_BNBFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 1.35655e+10},
		{ "40Ar_BNBFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 1.40324e+10},		
		{ "40Ar_BNBFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 1.30232e+10},

		{ "40Ar_BNBFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 31.9663},
		{ "40Ar_BNBFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 27.1438},
		{ "40Ar_BNBFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 30.3686},
		{ "40Ar_BNBFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 32.4126},

		{ "40Ar_BNBFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 31.5627},
		{ "40Ar_BNBFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 26.8509},
		{ "40Ar_BNBFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 30.0045},
		{ "40Ar_BNBFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 31.8372},

		// ------------------------------------------------------------

		// NOvA Flux

		{ "12C_NOvAFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},		// NOT to be produced
		{ "12C_NOvAFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5.79231e+09},
		{ "12C_NOvAFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5.79231e+09},
		{ "12C_NOvAFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5.57273e+09},

		{ "12C_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 22.3282},
		{ "12C_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 19.3882},
		{ "12C_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 21.4453},
		{ "12C_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 20.8681},

		{ "12C_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 22.121},
		{ "12C_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 19.2408},
		{ "12C_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 21.2753},
		{ "12C_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 20.638},

		// ------------------------------------------------------------

		{ "1H_NOvAFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},         // NOT to be produced
		{ "1H_NOvAFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 1.11298e+09},
		{ "1H_NOvAFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 1.09925e+09},
		{ "1H_NOvAFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 1.05024e+09},

		{ "1H_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 1.13718},
		{ "1H_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 0.967012},
		{ "1H_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 1.13718},
		{ "1H_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 1.04123},

		{ "1H_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 1.12637},
		{ "1H_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 0.957537},
		{ "1H_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 1.12637},
		{ "1H_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 1.02785},

		// ------------------------------------------------------------

		// T2K Flux

		{ "12C_T2KFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},		// NOT to be produced
		{ "12C_T2KFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 4.28079e+09},
		{ "12C_T2KFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 4.72064e+09},
		{ "12C_T2KFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 4.45459e+09},

		{ "12C_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 9.24185},
		{ "12C_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 7.60092},
		{ "12C_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 8.92865},
		{ "12C_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 9.27586},

		{ "12C_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 9.12783},
		{ "12C_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 7.52929},
		{ "12C_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 8.83686},
		{ "12C_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 9.12773},

		// ------------------------------------------------------------

		{ "1H_T2KFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0.},		// NOT to be produced
		{ "1H_T2KFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 9.64483e+08},
		{ "1H_T2KFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 9.62602e+08},
		{ "1H_T2KFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 9.39704e+08},

		{ "1H_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 0.331849},
		{ "1H_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 0.281795},
		{ "1H_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 0.331849},
		{ "1H_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 0.307004},

		{ "1H_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 0.328665},
		{ "1H_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 0.279013},
		{ "1H_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 0.328665},
		{ "1H_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 0.302881},


	};

	static std::map<TString,double> GENIEEvents =
	{
		{ "40Ar_BNBFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 4500000},
		{ "40Ar_BNBFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5000000},
		{ "40Ar_BNBFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5000000},
		{ "40Ar_BNBFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "40Ar_BNBFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 3800000},
		{ "40Ar_BNBFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 2400000},
		{ "40Ar_BNBFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 5000000},
		{ "40Ar_BNBFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 14900000},

		{ "40Ar_BNBFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 5000000},
		{ "40Ar_BNBFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 4900000},
		{ "40Ar_BNBFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 5000000},
		{ "40Ar_BNBFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 4800000},	

		// ------------------------------------------------------------

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 4600000},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5100000},
		{ "40Ar_DUNEFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5000000},
		{ "40Ar_DUNEFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 5000000},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 5000000},
		{ "40Ar_DUNEFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 5000000},
		{ "40Ar_DUNEFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 9900000},

		{ "40Ar_DUNEFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 3800000},
		{ "40Ar_DUNEFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 4800000},
		{ "40Ar_DUNEFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 5000000},
		{ "40Ar_DUNEFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 3800000},     

		// ------------------------------------------------------------		   

		{ "CH_T2KFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0},         		// NOT to be produced
		{ "CH_T2KFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5000000},
		{ "CH_T2KFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 4900000},
		{ "CH_T2KFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "CH_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 4900000},     
		{ "CH_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 4900000},
		{ "CH_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 4900000},
		{ "CH_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 4900000},

		{ "CH_T2KFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 5000000},     
		{ "CH_T2KFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 4900000},
		{ "CH_T2KFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 5000000},
		{ "CH_T2KFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 5000000}, 

		// ------------------------------------------------------------		          	

		{ "CH2_NOvAFlux_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 0},           		// NOT to be produced
		{ "CH2_NOvAFlux_G18_10a_02_11a_EM+MEC_Q2_0_0", 5000000},
		{ "CH2_NOvAFlux_G18_02a_00_000_EM+MEC_Q2_0_0", 5000000},
		{ "CH2_NOvAFlux_G00_00a_00_000_EM+MEC_Q2_0_0", 5000000},

		{ "CH2_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 5000000},      		 
		{ "CH2_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_0", 5000000},
		{ "CH2_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_0", 5000000},
		{ "CH2_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_0", 5000000}, 

		{ "CH2_NOvAFlux_GTEST19_10b_00_000_CCinclMEC_Q2_0_02", 5000000},	 
		{ "CH2_NOvAFlux_G18_10a_02_11a_CCinclMEC_Q2_0_02", 5000000},
		{ "CH2_NOvAFlux_G18_02a_00_000_CCinclMEC_Q2_0_02", 4900000},
		{ "CH2_NOvAFlux_G00_00a_00_000_CCinclMEC_Q2_0_02", 5300000},  

		// ------------------------------------------------------------		                 		  

		{ "C12_1161_GTEST19_10b_00_000_CCinclMEC_Q2_0_0", 10000000},    
		{ "C12_1161_G18_10a_02_11a_CCinclMEC_Q2_0_0", 10000000},    
		{ "C12_1161_G18_02a_00_000_CCinclMEC_Q2_0_0", 10000000}, 
		{ "C12_1161_G00_00a_00_000_CCinclMEC_Q2_0_0", 9800000},

		{ "C12_1161_GTEST19_10b_00_000_CCinclMEC_Q2_0_1_NoFSI", 10000000},    
		{ "C12_1161_G18_10a_02_11a_CCinclMEC_Q2_0_1_NoFSI", 10000000},    
		{ "C12_1161_G18_02a_00_000_CCinclMEC_Q2_0_1_NoFSI", 10000000}, 
		{ "C12_1161_G00_00a_00_000_CCinclMEC_Q2_0_1_NoFSI", 10000000},

		// ------------------------------------------------------------		   

		{ "C12_1161_GTEST19_10b_00_000_EM+MEC_Q2_0_0", 9900000},    
		{ "C12_1161_G18_10a_02_11a_EM+MEC_Q2_0_0", 9600000},    
		{ "C12_1161_G18_02a_00_000_EM+MEC_Q2_0_0", 9900000}, 
		{ "C12_1161_G00_00a_00_000_EM+MEC_Q2_0_0", 20000000},

		{ "C12_1161_GTEST19_10b_00_000_EM+MEC_Q2_0_1_NoFSI", 9900000},    
		{ "C12_1161_G18_10a_02_11a_EM+MEC_Q2_0_1_NoFSI", 10000000},    
		{ "C12_1161_G18_02a_00_000_EM+MEC_Q2_0_1_NoFSI", 20000000}, 
		{ "C12_1161_G00_00a_00_000_EM+MEC_Q2_0_1_NoFSI", 10000000},       

	};

//  ------------------------------------------------------------------------------

#endif
