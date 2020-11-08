{

	gROOT->ProcessLine(".L VertexRange.cpp+");

	gROOT->ProcessLine("VertexRange(\"CH2\",\"1161\",\"1500\")");

	gROOT->ProcessLine("VertexRange(\"C12\",\"1161\",\"750\")");
	gROOT->ProcessLine("VertexRange(\"C12\",\"1161\",\"1500\")");
	gROOT->ProcessLine("VertexRange(\"C12\",\"2261\",\"2250\")");
	gROOT->ProcessLine("VertexRange(\"C12\",\"4461\",\"2250\")");

	gROOT->ProcessLine("VertexRange(\"56Fe\",\"2261\",\"2250\")");
	gROOT->ProcessLine("VertexRange(\"56Fe\",\"4461\",\"2250\")");

//	gROOT->ProcessLine("VertexRange(\"4He\",\"2261\",\"2250\")");
//	gROOT->ProcessLine("VertexRange(\"4He\",\"4461\",\"2250\")");

};
