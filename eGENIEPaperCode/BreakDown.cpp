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

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "eGENIE_Constants.h"
#include "eGENIE_Functions.cpp"

using namespace std;

// ----------------------------------------------------------------------------------------------------------------

void BreakDown(TString Nucleus, TString Energy, TString Tune, TString Interaction,TString PlotName) {

	// -----------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TH1D::SetDefaultSumw2();

	// ------------------------------------------------------------------------

	TString TuneLabel = "SuSav2";
	if (Tune == "G18_10a_02_11a") { TuneLabel = "G2018"; }
	if (Tune == "G00_00a_00_000") { TuneLabel = "G2000"; }
	if (Tune == "G00_00a_00_000") { TuneLabel = "G18_02a"; }

	// ------------------------------------------------------------------------

	TString FileName = "myFiles/"+Nucleus+"_"+Energy+"_"+Tune+"_"+Interaction+".root";
	TFile* FileSample = TFile::Open(FileName);

	// ------------------------------------------------------------------------

	int NInteractions = ProcessLabel.size(); // QE, MEC, RES, DIS, COH
	TH1D* Plots[NInteractions];

	// ------------------------------------------------------------------------

	TString canName = Nucleus+"_"+Energy+"_"+Tune+"_"+Interaction+PlotName;
	TCanvas* can = new TCanvas(canName,canName,205,34,1024,768);
	can->cd();	
	//can->SetBottomMargin(0.15);
	//can->SetLeftMargin(0.15);

	// ------------------------------------------------------------------------

	TLegend* leg = new TLegend(0.4,0.6,0.75,0.85);

	// ------------------------------------------------------------------------

	TH1D* FullPlot = (TH1D*)(FileSample->Get(PlotName));
	PrettyPlot(FullPlot,kBlack);
	leg->AddEntry(FullPlot,"Total " + TuneLabel + " " + Interaction,"l");

	// ------------------------------------------------------------------------

	for (int WhichInteraction = 0; WhichInteraction < NInteractions; WhichInteraction++) {

		Plots[WhichInteraction] = (TH1D*)(FileSample->Get(PlotName+"_BreakDown_"+ToStringInt(WhichInteraction)));
		PrettyPlot(Plots[WhichInteraction],Colors[WhichInteraction]);
		leg->AddEntry(Plots[WhichInteraction],ProcessLabel[WhichInteraction],"l");
		

	}

	
	// ------------------------------------------------------------------------

	leg->SetTextSize(0.04);
	leg->SetTextFont(FontStyle);
	leg->SetBorderSize(0);
	leg->Draw();

	// ------------------------------------------------------------------------

} // End of the program
