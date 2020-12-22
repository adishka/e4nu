#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TGaxis.h>
#include <TROOT.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "../AfroConstants.h"
#include "../myFunctions.cpp"

//TString ToString(double num) {

//	std::ostringstream start;
//	start << num;
//	string start1 = start.str();
//	return start1;
//}

void e4vXSecRatio() {

	TH1D::SetDefaultSumw2();

	int FontStyle = 132;
	double TextSize = 0.07;
	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");
//	TGaxis::SetExponentOffset(-0.05, 0., "y");

	gStyle->SetTitleSize(TextSize-0.02,"t");
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);	

	// ---------------------------------------------------------------------------------------------

	TString CanvasName = "e4vXSec";
	TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
				
	PlotCanvas->SetLeftMargin(0.18);
	PlotCanvas->SetBottomMargin(0.17);

	PlotCanvas->SetGridx();
	PlotCanvas->SetGridy();

	// ---------------------------------------------------------------------------------------------

	TString PlotName = "h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0";

	// ---------------------------------------------------------------------------------------------

	// Data e4v

	TFile* Datae4vFile = TFile::Open("/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/1_161/Pinned_Data_Final_XSec/NoxBCut/12C_1_161_Pinned_Data_Final_XSec_Plots_FSI_em.root");

	TH1D* Datae4vPlot = (TH1D*)Datae4vFile->Get(PlotName);
	UniversalE4vFunction(Datae4vPlot,"Pinned Data","12C","1_161",PlotName);

	Datae4vPlot->SetTitle("(e,e') ^{12}C, #theta = 37.5^{o}");

	Datae4vPlot->GetXaxis()->SetTitle("Energy Transfer [GeV]");
	Datae4vPlot->GetXaxis()->CenterTitle();
	Datae4vPlot->GetXaxis()->SetNdivisions(9);
	Datae4vPlot->GetXaxis()->SetLabelFont(FontStyle);
	Datae4vPlot->GetXaxis()->SetLabelSize(TextSize);
	Datae4vPlot->GetXaxis()->SetTitleFont(FontStyle);
	Datae4vPlot->GetXaxis()->SetTitleSize(TextSize);
	Datae4vPlot->GetXaxis()->SetTitleOffset(1.1);
	Datae4vPlot->GetXaxis()->SetLabelOffset(0.015);

	Datae4vPlot->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#OmegadE_{e}} [#frac{nb}{sr GeV}]");
	Datae4vPlot->GetYaxis()->CenterTitle();
	Datae4vPlot->GetYaxis()->SetNdivisions(7);
	Datae4vPlot->GetYaxis()->SetLabelFont(FontStyle);
	Datae4vPlot->GetYaxis()->SetLabelSize(TextSize);
	Datae4vPlot->GetYaxis()->SetTitleFont(FontStyle);
	Datae4vPlot->GetYaxis()->SetTitleSize(TextSize);
	Datae4vPlot->GetYaxis()->SetTitleOffset(1.1);

	Datae4vPlot->GetXaxis()->SetRangeUser(0.0,0.85);
	Datae4vPlot->GetYaxis()->SetRangeUser(0,4500); // Y axis in nb / sr / GeV

	Datae4vPlot->SetLineColor(kGreen+2);
	Datae4vPlot->SetMarkerColor(kGreen+2);
	Datae4vPlot->SetMarkerStyle(20);

	Datae4vPlot->Scale(1./0.0067); // sr: solid angle for 24 < phi < 36 && 36 < theta < 39 
	Datae4vPlot->Scale(1000); // Conversion from ub to nb
	Datae4vPlot->Draw("e1x0 same");

//TH1D* AccCorrDatae4vPlot = AcceptanceCorrection(Datae4vPlot,"SuSav2","12C","1_161",PlotName,"NoxBCut","_XSec");
//AccCorrDatae4vPlot->Draw("e1x0 same");

	// ---------------------------------------------------------------------------------------------

	// SuSav2 GENIE Out-Of-The-Box @ E = 1.161 GEV & theta = 37.5 deg

	TFile* GenieBoxFile = TFile::Open("GenieOutOfTheBox_12C_DoubleDiff_E_1_161GeV_theta_37_5.root");

	TH1D* GenieBoxPlot = (TH1D*)GenieBoxFile->Get("v_distribution");

	GenieBoxPlot->SetLineColor(kGreen+2);
	GenieBoxPlot->SetLineWidth(2);

	GenieBoxPlot->Draw("c hist same");

	TF1 *myfunc = new TF1("myfunc","pol10",0.05,0.8);
	GenieBoxPlot->Fit(myfunc);
	myfunc->Draw("same");

	// ---------------------------------------------------------------------------------------------
//	// ---------------------------------------------------------------------------------------------

//	TLegend* leg = new TLegend(0.35,0.65,0.4,0.89);
//	leg->SetNColumns(1);

////	TLegendEntry* lGenie = leg->AddEntry(GeniePlot,"e4v GENIE E_{e} = 1.161 GeV, 24^{o} < #phi_{e'} < 36^{o}", "l");
////	lGenie->SetTextColor(kBlue);

//	TLegendEntry* lGenieBox = leg->AddEntry(GenieBoxPlot,"GENIE E_{e} = 1.161 GeV", "l");
//	lGenieBox->SetTextColor(kGreen+2);

//	TLegendEntry* lDatae4v = leg->AddEntry(Datae4vPlot,"e4v CLAS Data E_{e} = 1.161 GeV, 24^{o} < #phi_{e'} < 36^{o}", "lep");
//	lDatae4v->SetTextColor(kGreen+2);

//	leg->SetBorderSize(0);
//	leg->SetTextFont(FontStyle);
//	leg->SetTextSize(TextSize-0.03);
//	leg->Draw();

	// ---------------------------------------------------------------------------------------------

	TLegend* leg = new TLegend(0.3,0.75,0.85,0.89);
	leg->SetNColumns(3);

	TLegendEntry* lDatae4v = leg->AddEntry(Datae4vPlot,"1.161 GeV", "");
	lDatae4v->SetTextColor(kGreen+2);

	leg->SetBorderSize(0);
	leg->SetTextFont(FontStyle);
	leg->SetTextSize(TextSize-0.01);
//	leg->Draw();

	// ---------------------------------------------------------------------------------------------

	TLatex* Latex1161 = new TLatex();
	Latex1161->SetTextFont(FontStyle);
	Latex1161->SetTextSize(TextSize-0.01);
	Latex1161->SetTextColor(kGreen+2);
	Latex1161->SetTextAlign(12);  // centered
	Latex1161->DrawLatexNDC(0.7,0.52,"#splitline{e4#nu 36^{o}-39^{o}}{1.161 GeV}");

	// ---------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------

	// Ratio Data / GENIE

	// ---------------------------------------------------------------------------------------------

	TString RatioCanvasName = "e4vXSecRatio";
	TCanvas* RatioPlotCanvas = new TCanvas(RatioCanvasName,RatioCanvasName,205,34,1024,768);
				
	RatioPlotCanvas->SetLeftMargin(0.18);
	RatioPlotCanvas->SetBottomMargin(0.17);

	RatioPlotCanvas->SetGridx();
	RatioPlotCanvas->SetGridy();

	int NBins = Datae4vPlot->GetXaxis()->GetNbins();
	TH1D* DataClone = (TH1D*)(Datae4vPlot->Clone("DataClone"));

	for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {

		double DataBinCenter = Datae4vPlot->GetBinCenter(WhichBin+1);
		double DataBinEntry = Datae4vPlot->GetBinContent(WhichBin+1);
		double DataBinError = Datae4vPlot->GetBinError(WhichBin+1);

		int GENIEBin = GenieBoxPlot->FindBin(DataBinCenter);
		double GENIEBinEntry = GenieBoxPlot->GetBinContent(GENIEBin);
		double GENIEBinError = GenieBoxPlot->GetBinError(GENIEBin);

		double NewEntry = 0.;
		double NewError = 0.;

		if (GENIEBinEntry > 0 && DataBinEntry > 0) { 

			NewEntry = DataBinEntry / GENIEBinEntry;
			NewError = NewEntry * TMath::Sqrt( TMath::Power(DataBinError/DataBinEntry,2.) + TMath::Power(GENIEBinError/GENIEBinEntry,2.) ); 

		}

		DataClone->SetBinContent(WhichBin+1,NewEntry);
		DataClone->SetBinError(WhichBin+1,NewError);

	}

	DataClone->GetXaxis()->SetNdivisions(9);
	DataClone->GetYaxis()->SetNdivisions(8);

	DataClone->GetYaxis()->SetRangeUser(0.75,1.45);
	DataClone->GetYaxis()->SetTitle("Data / GENIE");
	DataClone->Draw("e1x0");

	delete RatioPlotCanvas;

	// ---------------------------------------------------------------------------------------------

} // End of the program
