#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TString.h>
#include <TColor.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

// ------------------------------------------------------------------------------------------------------------------------------------------------------

TString ToString(double num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------

void PrettyGraph(TGraph* g, int color) {

	int FontStyle = 132;
	double TextSize = 0.05;

	g->SetTitle("");

	g->GetXaxis()->SetTitle("E_{#nu} [GeV]");
	g->GetXaxis()->CenterTitle();
	g->GetXaxis()->SetRangeUser(0,3);
	g->GetXaxis()->SetNdivisions(7);
	g->GetXaxis()->SetLabelSize(TextSize);
	g->GetXaxis()->SetTitleSize(TextSize);
	g->GetXaxis()->SetLabelFont(FontStyle);
	g->GetXaxis()->SetTitleFont(FontStyle);

	g->GetYaxis()->SetTitle("#sigma [10^{-38} #frac{cm^{2}}{nucleus}]");
	g->GetYaxis()->CenterTitle();
	g->GetYaxis()->SetNdivisions(7);
	g->GetYaxis()->SetLabelSize(TextSize);
	g->GetYaxis()->SetTitleSize(TextSize);
	g->GetYaxis()->SetLabelFont(FontStyle);
	g->GetYaxis()->SetTitleFont(FontStyle);

	g->SetMarkerStyle(20);
	g->SetMarkerSize(2.);
	g->SetMarkerColor(color);
	g->SetLineColor(color);

	g->Draw("ap same");

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------

void XSecToyModel() {

	int A = 12; TString Element = "C";

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TString CCQEPlotCanvasName = "CCQECanvas";
	TCanvas* CCQEPlotCanvas = new TCanvas(CCQEPlotCanvasName,CCQEPlotCanvasName,205,34,1024,768);
	CCQEPlotCanvas->SetBottomMargin(0.11);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* CCQEG2018File = TFile::Open("myXSec/xsec_carbon12_spline_CCQE_G18_10a_02_11a_Q2_0_1.root");
	TDirectory* CCQEG2018Dir = (TDirectory*)(CCQEG2018File->Get("nu_mu_C12"));
	TGraph* CCQEG2018 = (TGraph*)(CCQEG2018Dir->Get("tot_cc"));

	PrettyGraph(CCQEG2018,kBlack);



/*
	// General

	std::vector<TString> FileNames;
	std::vector<TString> LegendNames;

	TString study = "XSec_"+Interaction+Channel+"_"+Element+ToString(A); TString CurrentTitle = Interaction+Channel+" ^{"+ToString(A)+"}"+Element; 
	TString DirName = IncomingParticle+"_"+Element+ToString(A);

	FileNames.push_back("xsec_"+Element+ToString(A)+"_"+Interaction+Channel+"_master");
	FileNames.push_back("xsec_"+Element+ToString(A)+"_"+Interaction+Channel+"_devel_namespace");

	LegendNames.push_back("master");
	LegendNames.push_back("devel_namespace");

	TString PathToSamples = "myXSec/";
	TCanvas* canEvents = new TCanvas("canEvents","canEvents",205,34,1024,768);

	TLegend* leg = new TLegend(0.55,0.3,0.7,0.5);
	leg->SetTextFont(132);
	leg->SetTextSize(0.05);
	leg->SetBorderSize(0);
	leg->SetNColumns(1);

	TLatex* CurrentLatexTitle = new TLatex(0.35,0.93,CurrentTitle);
	CurrentLatexTitle->SetNDC(kTRUE);
	CurrentLatexTitle->SetTextFont(132);
	CurrentLatexTitle->SetTextSize(0.07);

	std::vector<int> Colors; Colors.push_back(kRed); Colors.push_back(kBlack); Colors.push_back(kBlue); Colors.push_back(kMagenta);

	int SizeColors = Colors.size();
	int SizeFileNames = FileNames.size();
	int SizeLegendNames = LegendNames.size();

	std::vector<TFile*> Files;
	std::vector<TDirectory*> TDirs;
	std::vector<TGraph*> Graphs;

	if ( SizeFileNames == SizeLegendNames && SizeColors >= SizeFileNames) {

		for (int WhichSample = 0; WhichSample < SizeFileNames; WhichSample++) {

			Files.push_back(TFile::Open(PathToSamples+FileNames[WhichSample]+".root"));
			TDirs.push_back( (TDirectory*)(Files[WhichSample]->Get(DirName)));
			Graphs.push_back((TGraph*)TDirs[WhichSample]->Get(XSecName));
			Graphs[WhichSample]->SetLineWidth(3);

			Graphs[WhichSample]->GetXaxis()->SetTitleOffset(0.85);
			Graphs[WhichSample]->GetXaxis()->SetTitleSize(0.05);
			Graphs[WhichSample]->GetXaxis()->SetTitleFont(132);
//			Graphs[WhichSample]->GetXaxis()->SetRangeUser(RangeMin,RangeMax);
			Graphs[WhichSample]->GetXaxis()->SetLimits(RangeMin,RangeMax);
			Graphs[WhichSample]->GetXaxis()->SetTitle(quantity);
			Graphs[WhichSample]->GetXaxis()->CenterTitle();

			Graphs[WhichSample]->GetYaxis()->SetTitleSize(0.05);
			Graphs[WhichSample]->GetYaxis()->SetTitleOffset(0.9);
			Graphs[WhichSample]->GetYaxis()->SetTitleFont(132);
			Graphs[WhichSample]->GetYaxis()->SetTitle("#sigma (10^{-38} cm^{2})");
			Graphs[WhichSample]->GetYaxis()->SetRangeUser(YMin,YMax);
//			Graphs[WhichSample]->GetYaxis()->SetLimits(YMin,YMax);
			Graphs[WhichSample]->GetYaxis()->CenterTitle();

			Graphs[WhichSample]->SetLineColor(Colors[WhichSample]);
			Graphs[WhichSample]->SetTitle("");
			leg->AddEntry(Graphs[WhichSample],LegendNames[WhichSample],"l");

			canEvents->cd();	
			if (WhichSample == 0) { Graphs[WhichSample]->Draw("APL"); }
			else { Graphs[WhichSample]->Draw("CP"); }


		}

	} else { cout << "Inconsistent files - legends size" << std::endl; }

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	// Draw legend & save

	leg->Draw();
	CurrentLatexTitle->Draw();
*/

//	canEvents->SaveAs("./myPlots/eps/SmoothSplines_"+study+".eps");
//	canEvents->SaveAs("./myPlots/pdf/SmoothSplines_"+study+".pdf");

} // End of the program
