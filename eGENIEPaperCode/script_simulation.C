{

	gROOT->ProcessLine(".L treeProducer_simulation.cpp+");

	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"EM+MEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"GTEST19_10b_00_000\",\"CCinclMEC\").Loop()");

	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"EM+MEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"1161\",\"G18_10a_02_11a\",\"CCinclMEC\").Loop()");

	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"uBFlux\",\"G18_10a_02_11a\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"uBFlux\",\"G18_02a_00_000\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"uBFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\").Loop()");
	
	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_10a_02_11a\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"G18_02a_00_000\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"40Ar\",\"DUNEFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\").Loop()");
	
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"NovaFlux\",\"G18_10a_02_11a\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"NovaFlux\",\"G18_02a_00_000\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"NovaFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\").Loop()");
	
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"T2KFlux\",\"G18_10a_02_11a\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"T2KFlux\",\"G18_02a_00_000\",\"CCinclMEC\").Loop()");
	gROOT->ProcessLine("treeProducer_simulation(\"C12\",\"T2KFlux\",\"GTEST19_10b_00_000\",\"CCinclMEC\").Loop()");				

	gROOT->ProcessLine(".q");

};
