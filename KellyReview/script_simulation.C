{

	gROOT->ProcessLine(".L treeProducer_simulation.cpp+");

	gROOT->ProcessLine("treeProducer_simulation(\"16O\",\"2442\",\"GTEST19_10b_00_000\",\"EM+MEC\").Loop()");			

	gROOT->ProcessLine(".q");

};
