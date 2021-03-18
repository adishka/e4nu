{

	gROOT->ProcessLine(".L treeProducer_simulation.cpp+");
/*

	// 100M events
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"Default\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10b_02_11a\",\"Default\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10a_00_000\",\"Default\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"Default\",\"Q2_0_1\").Loop()");

	// 10M events
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_1\").Loop()");

	// 100M events
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"EM\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10b_02_11a\",\"EM\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10a_00_000\",\"EM\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"EM\",\"Q2_0_1\").Loop()");

	// 10M events
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G00_00a_00_000\",\"EM+MEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_02a_00_000\",\"EM+MEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"EM+MEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10b_02_11a\",\"EM+MEC\",\"Q2_0_1\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"EM+MEC\",\"Q2_0_1\").Loop()");

	// NoFSI

	// 100M events
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"Default\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10b_02_11a\",\"Default\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10a_00_000\",\"Default\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"Default\",\"Q2_0_1_NoFSI\").Loop()");

	// 10M
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_1_NoFSI\").Loop()");

	// 100M
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"EM\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10b_02_11a\",\"EM\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10a_00_000\",\"EM\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"EM\",\"Q2_0_1_NoFSI\").Loop()");

	// 10M
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G00_00a_00_000\",\"EM+MEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_02a_00_000\",\"EM+MEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"EM+MEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10b_02_11a\",\"EM+MEC\",\"Q2_0_1_NoFSI\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"EM+MEC\",\"Q2_0_1_NoFSI\").Loop()");
*/
	// -------------------------------------------------------------------------------------------------------------------------

//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");

//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");

//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G00_00a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G18_02a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"G18_10a_02_11a\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"BNBFlux\",\"GTEST19_10b_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");

	// -------------------------------------------------------------------------------------------------------------------------

//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");

//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");

//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G00_00a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_02a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_10a_02_11a\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"GTEST19_10b_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");

//      gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"FDDUNEOscFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"FDDUNEOscFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"FDDUNEOscFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"FDDUNEOscFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");

	// -------------------------------------------------------------------------------------------------------------------------

//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");	
//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");

//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");	
//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");

//      gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G00_00a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G18_02a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"CH2\",\"NOvAFlux\",\"G18_10a_02_11a\",\"EM+MEC\",\"Q2_0_0\").Loop()");

	// -------------------------------------------------------------------------------------------------------------------------

//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");	
//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_0\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_0\").Loop()");

//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G00_00a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");	
//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G18_02a_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G18_10a_02_11a\",\"CCinclMEC\",\"Q2_0_02\").Loop()");
//	gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"Q2_0_02\").Loop()");

//      gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G00_00a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G18_02a_00_000\",\"EM+MEC\",\"Q2_0_0\").Loop()");
//      gROOT->ProcessLine("treeProducer_simulation(\"CH\",\"T2KFlux\",\"G18_10a_02_11a\",\"EM+MEC\",\"Q2_0_0\").Loop()");

	// -------------------------------------------------------------------------------------------------------------------------			

	gROOT->ProcessLine(".q");

};
