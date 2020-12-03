{

	gROOT->ProcessLine(".L BreakDown.cpp+");

	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"MissMomentumPlot\")");
	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"GTEST19_10b_00_000\",\"EM+MEC\",\"MissMomentumPlot\")");

	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"G18_10a_02_11a\",\"CCinclMEC\",\"MissMomentumPlot\")");
	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"G18_10a_02_11a\",\"EM+MEC\",\"MissMomentumPlot\")");

	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"GTEST19_10b_00_000\",\"CCinclMEC\",\"MissMomentumPlot_OneProton\")");
	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"GTEST19_10b_00_000\",\"EM+MEC\",\"MissMomentumPlot_OneProton\")");

	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"G18_10a_02_11a\",\"CCinclMEC\",\"MissMomentumPlot_OneProton\")");
	gROOT->ProcessLine("BreakDown(\"C12\", \"1161\",\"G18_10a_02_11a\",\"EM+MEC\",\"MissMomentumPlot_OneProton\")");

//	gROOT->ProcessLine(".q");

};
