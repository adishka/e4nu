{

	gROOT->ProcessLine(".L treeProducer_simulation.cpp+");

	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"EM+MEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"CCinclMEC\").Loop()");

	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"EM+MEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"CCinclMEC\").Loop()");

	gROOT->ProcessLine(".q");

};
