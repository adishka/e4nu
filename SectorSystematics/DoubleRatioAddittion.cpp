#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>
#include <TGraph.h>

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

void DoubleRatioAddittion() {

	TH1D::SetDefaultSumw2();

	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	// ------------------------------------------------------------------------

	TString FilePath = "myFiles/";
	int Sectors = 6;

	// ------------------------------------------------------------------------

	std::vector<TFile*> Files;

	// ------------------------------------------------------------------------

	std::vector<TString> nucleus{"4He","12C","56Fe"};
	int NNuclei = nucleus.size();

	// ------------------------------------------------------------------------

	std::vector<std::vector<TH1D*> > Plots;
	Plots.resize(NNuclei);	

	// ------------------------------------------------------------------------

	for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus++) {

		Files.push_back(TFile::Open(FilePath+"Ratio_SuSav2"+nucleus[WhichNucleus]+"_4_461_NoxBCutECal.root"));

		// Loop over the 6 sector double ratios

		for (int WhichSector = 0; WhichSector < Sectors; WhichSector++) {

			TH1D* LocalPlot = (TH1D*)Files[WhichNucleus]->Get("h1_ECal_InSector_"+ToStringInt(WhichSector));
			Plots[WhichNucleus].push_back(LocalPlot);

		}

	}

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	TString DoubleRatioCanvasName = "CombinedDoubleRatio_ECal"; 

	TCanvas* DoubleRatioPlotCanvas = new TCanvas(DoubleRatioCanvasName,DoubleRatioCanvasName,205,34,1024,768);

	DoubleRatioPlotCanvas->SetGridx();
	DoubleRatioPlotCanvas->SetGridy();

	DoubleRatioPlotCanvas->SetBottomMargin(0.17);
	DoubleRatioPlotCanvas->SetLeftMargin(0.17);

	TLegend* DoubleRatioleg = new TLegend(0.2,0.7,0.5,0.85);
	DoubleRatioleg->SetNColumns(3);
	DoubleRatioleg->SetFillStyle(0);	

	// Loop over the 6 sector double ratios

	for (int WhichSector = 0; WhichSector < Sectors; WhichSector++) {
			
		TH1D* Clone = nullptr;

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus++) {

			if (WhichNucleus == 0) { Clone = (TH1D*)(Plots[WhichNucleus][WhichSector]->Clone()); }
			else { Clone->Add(Plots[WhichNucleus][WhichSector]); }

		}

		int NRebin = 2;
		for (int i = 0; i < NRebin; i++) { Clone->Rebin(); }

		DoubleRatioleg->AddEntry(Clone,ToStringInt(WhichSector+1),"p");
		Clone->SetTitle("Pinned Data/SuSav2 @ 4.461 GeV");
		Clone->Scale(1./(double)(NNuclei)/(double)(NRebin+1));
		DoubleRatioPlotCanvas->cd();
		Clone->GetYaxis()->SetRangeUser(0,2);
		Clone->Draw("ex0 same");

	}

	DoubleRatioleg->SetBorderSize(0);
	DoubleRatioleg->SetTextFont(FontStyle);
	DoubleRatioleg->SetTextSize(TextSize);
	DoubleRatioleg->Draw();

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program
