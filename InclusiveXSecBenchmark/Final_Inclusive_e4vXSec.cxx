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

void Final_Inclusive_e4vXSec() {

	int FontStyle = 132;
	double TextSize = 0.07;
	TGaxis::SetMaxDigits(3);

	gStyle->SetTitleSize(TextSize-0.02,"t");
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);	

	// ---------------------------------------------------------------------------------------------

	TString CanvasName = "DataXSec_Inclusive_Validation";
	TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
				
	PlotCanvas->SetLeftMargin(0.15);
	PlotCanvas->SetBottomMargin(0.17);

	// ---------------------------------------------------------------------------------------------

	// Corrected Data e4vFinal_Inclusive_e4vXSec

	TFile* CorrectedDatae4vFile = TFile::Open("e4v_C12_E_1_161_theta_37_5.root");

	TH1D* CorrectedDatae4vPlot = (TH1D*)CorrectedDatae4vFile->Get("Correctede4vData"); // already extracted xsec in e4vXSecRatio.cxx solid angle for 24 < phi < 36 && 36 < theta < 39 

	CorrectedDatae4vPlot->SetTitle("(e,e') ^{12}C 1.161 GeV, #theta = 37.5^{o}");

	CorrectedDatae4vPlot->GetXaxis()->SetTitle("Energy Transfer [GeV]");
	CorrectedDatae4vPlot->GetXaxis()->CenterTitle();
	CorrectedDatae4vPlot->GetXaxis()->SetNdivisions(8);
	CorrectedDatae4vPlot->GetXaxis()->SetLabelFont(FontStyle);
	CorrectedDatae4vPlot->GetXaxis()->SetLabelSize(TextSize);
	CorrectedDatae4vPlot->GetXaxis()->SetTitleFont(FontStyle);
	CorrectedDatae4vPlot->GetXaxis()->SetTitleSize(TextSize);
	CorrectedDatae4vPlot->GetXaxis()->SetTitleOffset(1.1);
	CorrectedDatae4vPlot->GetXaxis()->SetLabelOffset(0.015);

	CorrectedDatae4vPlot->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#OmegadE_{e}} [#frac{#mub}{sr GeV}]");
	CorrectedDatae4vPlot->GetYaxis()->CenterTitle();
	CorrectedDatae4vPlot->GetYaxis()->SetNdivisions(7);
	CorrectedDatae4vPlot->GetYaxis()->SetLabelFont(FontStyle);
	CorrectedDatae4vPlot->GetYaxis()->SetLabelSize(TextSize);
	CorrectedDatae4vPlot->GetYaxis()->SetTitleFont(FontStyle);
	CorrectedDatae4vPlot->GetYaxis()->SetTitleSize(TextSize);
	CorrectedDatae4vPlot->GetYaxis()->SetTitleOffset(0.88);

	CorrectedDatae4vPlot->GetXaxis()->SetRangeUser(0.08,0.72);
	CorrectedDatae4vPlot->GetYaxis()->SetRangeUser(0,4.2); // Y axis in nb / sr / GeV

	CorrectedDatae4vPlot->SetLineColor(kBlack);
	CorrectedDatae4vPlot->SetMarkerColor(kBlack);
	CorrectedDatae4vPlot->SetMarkerStyle(20);
	CorrectedDatae4vPlot->Scale(0.001);// Conversion from nb to ub
	CorrectedDatae4vPlot->Draw("e1x0 same");

	// ---------------------------------------------------------------------------------------------

	// SuSav2 GENIE Out-Of-The-Box @ E = 1.161 GEV & theta = 37.5 deg

	TFile* GenieBoxFile = TFile::Open("GenieOutOfTheBox_12C_DoubleDiff_E_1_161GeV_theta_37_5_FineBin.root");
	TGraph* GenieBoxPlot = (TGraph*)GenieBoxFile->Get("Simulation");
	TGraph* QEGenieBoxPlot = (TGraph*)GenieBoxFile->Get("SimulationQE");
	TGraph* MECGenieBoxPlot = (TGraph*)GenieBoxFile->Get("SimulationMEC");
	TGraph* RESGenieBoxPlot = (TGraph*)GenieBoxFile->Get("SimulationRES");
	TGraph* DISGenieBoxPlot = (TGraph*)GenieBoxFile->Get("SimulationDIS");

	GenieBoxPlot->SetLineColor(kBlack);
	GenieBoxPlot->SetLineWidth(2);

	QEGenieBoxPlot->SetLineColor(BreakDownColors[0]);
	QEGenieBoxPlot->SetLineWidth(2);

	MECGenieBoxPlot->SetLineColor(BreakDownColors[1]);
	MECGenieBoxPlot->SetLineWidth(2);

	RESGenieBoxPlot->SetLineColor(BreakDownColors[2]);
	RESGenieBoxPlot->SetLineWidth(2);

	DISGenieBoxPlot->SetLineColor(BreakDownColors[3]);
	DISGenieBoxPlot->SetLineWidth(2);

	double constant = TMath::Power(10.,-3.);
	for (int i=0;i<GenieBoxPlot->GetN();i++) { 

		GenieBoxPlot->GetY()[i] *= constant; 
		QEGenieBoxPlot->GetY()[i] *= constant; 
		MECGenieBoxPlot->GetY()[i] *= constant; 
		RESGenieBoxPlot->GetY()[i] *= constant; 
		DISGenieBoxPlot->GetY()[i] *= constant; 

	} // Conversion from nb to ub

	GenieBoxPlot->Draw("c same");
	QEGenieBoxPlot->Draw("c same");
	MECGenieBoxPlot->Draw("c same");
	RESGenieBoxPlot->Draw("c same");
	DISGenieBoxPlot->Draw("c same");

	// ---------------------------------------------------------------------------------------------

	// G2018 GENIE Out-Of-The-Box @ E = 1.161 GEV & theta = 37.5 deg

	TFile* G2018_GenieBoxFile = TFile::Open("G2018_GenieOutOfTheBox_12C_DoubleDiff_E_1_161GeV_theta_37_5_FineBin.root");
	TGraph* G2018_GenieBoxPlot = (TGraph*)G2018_GenieBoxFile->Get("Simulation");

	G2018_GenieBoxPlot->SetLineColor(kBlack);
	G2018_GenieBoxPlot->SetLineStyle(kDashed);
	G2018_GenieBoxPlot->SetLineWidth(2);
	
	for (int i=0;i<G2018_GenieBoxPlot->GetN();i++) G2018_GenieBoxPlot->GetY()[i] *= constant; // Conversion from nb to ub

	G2018_GenieBoxPlot->Draw("c same");

	// ---------------------------------------------------------------------------------------------

	TString PlotName = "h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0";

	// ---------------------------------------------------------------------------------------------

	// Uncorrected Data e4v

	TFile* Datae4vFile = TFile::Open("/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/1_161/Pinned_Data_Final_XSec/NoxBCut/12C_1_161_Pinned_Data_Final_XSec_Plots_FSI_em.root");

	TH1D* Datae4vPlot = (TH1D*)Datae4vFile->Get(PlotName);
	UniversalE4vFunction(Datae4vPlot,"Pinned Data","12C","1_161",PlotName);

	Datae4vPlot->SetLineColor(kBlack);
	Datae4vPlot->SetMarkerColor(kBlack);
	Datae4vPlot->SetMarkerStyle(20);

	Datae4vPlot->Scale(1./0.0067); // sr: solid angle for 24 < phi < 36 && 36 < theta < 39 
	//Datae4vPlot->Scale(1000); // Conversion from ub to nb
	Datae4vPlot->SetMarkerStyle(4);
	//Datae4vPlot->Draw("e1x0 same");

	// ---------------------------------------------------------------------------------------------

	TLatex latexData;
	latexData.SetTextFont(FontStyle);
	latexData.SetTextSize(0.07);
	latexData.SetTextColor(kBlack);
	latexData.DrawLatexNDC(0.2,0.69,"Data");

	TLatex latexG2018;
	latexG2018.SetTextFont(FontStyle);
	latexG2018.SetTextSize(0.07);
	latexG2018.SetTextColor(kBlack);
	latexG2018.DrawLatexNDC(0.29,0.41,"#it{G2018}");

	TLatex latexSuSav2;
	latexSuSav2.SetTextFont(FontStyle);
	latexSuSav2.SetTextSize(0.07);
	latexSuSav2.SetTextColor(kBlack);
	latexSuSav2.DrawLatexNDC(0.72,0.84,"SuSav2");

	TLatex latexSuSav2QE;
	latexSuSav2QE.SetTextFont(FontStyle);
	latexSuSav2QE.SetTextSize(0.07);
	latexSuSav2QE.SetTextColor(BreakDownColors[0]);
	latexSuSav2QE.DrawLatexNDC(0.35,0.55,"QE");

	TLatex latexSuSav2MEC;
	latexSuSav2MEC.SetTextFont(FontStyle);
	latexSuSav2MEC.SetTextSize(0.07);
	latexSuSav2MEC.SetTextColor(BreakDownColors[1]);
	latexSuSav2MEC.DrawLatexNDC(0.36,0.29,"MEC");

	TLatex latexSuSav2RES;
	latexSuSav2RES.SetTextFont(FontStyle);
	latexSuSav2RES.SetTextSize(0.07);
	latexSuSav2RES.SetTextColor(BreakDownColors[2]);
	latexSuSav2RES.DrawLatexNDC(0.6,0.45,"RES");

	TLatex latexSuSav2DIS;
	latexSuSav2DIS.SetTextFont(FontStyle);
	latexSuSav2DIS.SetTextSize(0.07);
	latexSuSav2DIS.SetTextColor(BreakDownColors[3]);
	latexSuSav2DIS.DrawLatexNDC(0.7,0.28,"DIS");

	// ---------------------------------------------------------------------------------------------

	PlotCanvas->SaveAs("e4v_DataXSec_Inclusive_Validation.pdf");

} // End of the program
