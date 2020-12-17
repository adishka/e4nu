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

void PrettyGraph(TGraph* g, int color,TString Interaction) {

	int FontStyle = 132;
	double TextSize = 0.05;

	g->SetTitle("");

	g->GetXaxis()->SetTitle("E_{#nu} [GeV]");
	g->GetXaxis()->CenterTitle();
	g->GetXaxis()->SetRangeUser(0,3.);
	g->GetXaxis()->SetNdivisions(7);
	g->GetXaxis()->SetLabelSize(TextSize);
	g->GetXaxis()->SetTitleSize(TextSize);
	g->GetXaxis()->SetLabelFont(FontStyle);
	g->GetXaxis()->SetTitleFont(FontStyle);

	g->GetYaxis()->SetTitle("#sigma_{"+Interaction+"} [10^{-38} #frac{cm^{2}}{nucleus}]");
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
	g->SetLineWidth(3);

//	g->Draw("ap same");
//	if (color == kBlack) { g->Draw("al same"); }
//	else { g->Draw("l same"); }

	if (color == kBlack) { g->Draw("ac same"); }
	else { g->Draw("c same"); }

}

// ------------------------------------------------------------------------------------------------------------------------------------------------------

void XSecOverlay() {

	int A = 12; TString Element = "C";

	TString Q2Thres = "0_1";

	int FontStyle = 132;
	double TextSize = 0.05;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------
	//                                    CCQE (Nieves, SuSav2, LW)
	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TString CCQEPlotCanvasName = "CCQECanvas";
	TCanvas* CCQEPlotCanvas = new TCanvas(CCQEPlotCanvasName,CCQEPlotCanvasName,205,34,1024,768);
	CCQEPlotCanvas->SetBottomMargin(0.11);
	CCQEPlotCanvas->SetLeftMargin(0.14);

	TLegend* legCCQE = new TLegend(0.5,0.4,0.7,0.7);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* CCQEG2018File = TFile::Open("myXSec/xsec_carbon12_spline_CCQE_G18_10a_02_11a_Q2_"+Q2Thres+".root");
	TDirectory* CCQEG2018Dir = (TDirectory*)(CCQEG2018File->Get("nu_mu_C12"));
	TGraph* CCQEG2018 = (TGraph*)(CCQEG2018Dir->Get("tot_cc"));
	PrettyGraph(CCQEG2018,kBlack,"CCQE");

	TLegendEntry* legCCQEG2018 = legCCQE->AddEntry(CCQEG2018,"Nieves","");
	legCCQEG2018->SetTextColor(kBlack);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* CCQESuSav2File = TFile::Open("myXSec/xsec_carbon12_spline_CCQE_GTEST19_10b_00_000_Q2_"+Q2Thres+".root");
	TDirectory* CCQESuSav2Dir = (TDirectory*)(CCQESuSav2File->Get("nu_mu_C12"));
	TGraph* CCQESuSav2 = (TGraph*)(CCQESuSav2Dir->Get("tot_cc"));
	PrettyGraph(CCQESuSav2,610,"CCQE");

	TLegendEntry* legCCQESuSav2 = legCCQE->AddEntry(CCQESuSav2,"SuSav2","");
	legCCQESuSav2->SetTextColor(610);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	// G2000 = G00_00a_00_000

	TFile* CCQEG2000File = TFile::Open("myXSec/xsec_carbon12_spline_CCQE_G00_00a_00_000_Q2_"+Q2Thres+".root");
	TDirectory* CCQEG2000Dir = (TDirectory*)(CCQEG2000File->Get("nu_mu_C12"));
	TGraph* CCQEG2000 = (TGraph*)(CCQEG2000Dir->Get("tot_cc"));
	PrettyGraph(CCQEG2000,410,"CCQE");

	TLegendEntry* legCCQEG2000 = legCCQE->AddEntry(CCQEG2000,"LS","");
	legCCQEG2000->SetTextColor(410);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	legCCQE->SetBorderSize(0);
	legCCQE->SetTextSize(TextSize);
	legCCQE->SetTextFont(FontStyle);
	legCCQE->Draw();

	delete CCQEPlotCanvas;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------
	//                                    CCMEC (Nieves, SuSav2, Empirical)
	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TString CCMECPlotCanvasName = "CCMECCanvas";
	TCanvas* CCMECPlotCanvas = new TCanvas(CCMECPlotCanvasName,CCMECPlotCanvasName,205,34,1024,768);
	CCMECPlotCanvas->SetBottomMargin(0.11);
	CCMECPlotCanvas->SetLeftMargin(0.14);

	TLegend* legCCMEC = new TLegend(0.5,0.2,0.7,0.5);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* CCMECG2018File = TFile::Open("myXSec/xsec_carbon12_spline_CCMEC_G18_10a_02_11a_Q2_"+Q2Thres+".root");
	TDirectory* CCMECG2018Dir = (TDirectory*)(CCMECG2018File->Get("nu_mu_C12"));
	TGraph* CCMECG2018 = (TGraph*)(CCMECG2018Dir->Get("tot_cc"));
	CCMECG2018->GetYaxis()->SetRangeUser(0,2.3);
	PrettyGraph(CCMECG2018,kBlack,"CCMEC");

	TLegendEntry* legCCMECG2018 = legCCMEC->AddEntry(CCMECG2018,"Nieves","");
	legCCMECG2018->SetTextColor(kBlack);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* CCMECSuSav2File = TFile::Open("myXSec/xsec_carbon12_spline_CCMEC_GTEST19_10b_00_000_Q2_"+Q2Thres+".root");
	TDirectory* CCMECSuSav2Dir = (TDirectory*)(CCMECSuSav2File->Get("nu_mu_C12"));
	TGraph* CCMECSuSav2 = (TGraph*)(CCMECSuSav2Dir->Get("tot_cc"));
	PrettyGraph(CCMECSuSav2,610,"CCMEC");

	TLegendEntry* legCCMECSuSav2 = legCCMEC->AddEntry(CCMECSuSav2,"SuSav2","");
	legCCMECSuSav2->SetTextColor(610);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	// G2000 = G00_00a_00_000

	TFile* CCMECG2000File = TFile::Open("myXSec/xsec_carbon12_spline_CCMEC_G00_00a_00_000_Q2_"+Q2Thres+".root");
	TDirectory* CCMECG2000Dir = (TDirectory*)(CCMECG2000File->Get("nu_mu_C12"));
	TGraph* CCMECG2000 = (TGraph*)(CCMECG2000Dir->Get("tot_cc"));
	CCMECG2000->GetYaxis()->SetRangeUser(0,2.3);
	PrettyGraph(CCMECG2000,410,"CCMEC");

	TLegendEntry* legCCMECG2000 = legCCMEC->AddEntry(CCMECG2000,"Empirical","");
	legCCMECG2000->SetTextColor(410);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	legCCMEC->SetBorderSize(0);
	legCCMEC->SetTextSize(TextSize);
	legCCMEC->SetTextFont(FontStyle);
	legCCMEC->Draw();

	//delete CCMECPlotCanvas;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------
	//                                    EMQE (SuSav2, Rosenbluth)
	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TString EMQEPlotCanvasName = "EMQECanvas";
	TCanvas* EMQEPlotCanvas = new TCanvas(EMQEPlotCanvasName,EMQEPlotCanvasName,205,34,1024,768);
	EMQEPlotCanvas->SetBottomMargin(0.11);
	EMQEPlotCanvas->SetLeftMargin(0.14);

	TLegend* legEMQE = new TLegend(0.5,0.2,0.7,0.5);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* EMQEG2018File = TFile::Open("myXSec/xsec_carbon12_spline_EMQE_G18_10a_02_11a_Q2_"+Q2Thres+".root");
	TDirectory* EMQEG2018Dir = (TDirectory*)(EMQEG2018File->Get("e-_C12"));
	TGraph* EMQEG2018 = (TGraph*)(EMQEG2018Dir->Get("tot_em"));
	PrettyGraph(EMQEG2018,kBlack,"EMQE");

	TLegendEntry* legEMQEG2018 = legEMQE->AddEntry(EMQEG2018,"Rosenbluth","");
	legEMQEG2018->SetTextColor(kBlack);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* EMQESuSav2File = TFile::Open("myXSec/xsec_carbon12_spline_EMQE_GTEST19_10b_00_000_Q2_"+Q2Thres+".root");
	TDirectory* EMQESuSav2Dir = (TDirectory*)(EMQESuSav2File->Get("e-_C12"));
	TGraph* EMQESuSav2 = (TGraph*)(EMQESuSav2Dir->Get("tot_em"));
	PrettyGraph(EMQESuSav2,610,"EMQE");

	TLegendEntry* legEMQESuSav2 = legEMQE->AddEntry(EMQESuSav2,"SuSav2","");
	legEMQESuSav2->SetTextColor(610);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	legEMQE->SetBorderSize(0);
	legEMQE->SetTextSize(TextSize);
	legEMQE->SetTextFont(FontStyle);
	legEMQE->Draw();

	delete EMQEPlotCanvas;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------
	//                                    EMMEC (SuSav2, Empirical)
	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TString EMMECPlotCanvasName = "EMMECCanvas";
	TCanvas* EMMECPlotCanvas = new TCanvas(EMMECPlotCanvasName,EMMECPlotCanvasName,205,34,1024,768);
	EMMECPlotCanvas->SetBottomMargin(0.11);
	EMMECPlotCanvas->SetLeftMargin(0.14);

	TLegend* legEMMEC = new TLegend(0.5,0.2,0.7,0.5);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* EMMECG2018File = TFile::Open("myXSec/xsec_carbon12_spline_EMMEC_G18_10a_02_11a_Q2_"+Q2Thres+".root");
	TDirectory* EMMECG2018Dir = (TDirectory*)(EMMECG2018File->Get("e-_C12"));
	TGraph* EMMECG2018 = (TGraph*)(EMMECG2018Dir->Get("tot_em"));
	EMMECG2018->GetYaxis()->SetRangeUser(0,190000000);
	PrettyGraph(EMMECG2018,kBlack,"EMMEC");

	TLegendEntry* legEMMECG2018 = legEMMEC->AddEntry(EMMECG2018,"Empirical","");
	legEMMECG2018->SetTextColor(kBlack);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	TFile* EMMECSuSav2File = TFile::Open("myXSec/xsec_carbon12_spline_EMMEC_GTEST19_10b_00_000_Q2_"+Q2Thres+".root");
	TDirectory* EMMECSuSav2Dir = (TDirectory*)(EMMECSuSav2File->Get("e-_C12"));
	TGraph* EMMECSuSav2 = (TGraph*)(EMMECSuSav2Dir->Get("tot_em"));
	PrettyGraph(EMMECSuSav2,610,"EMMEC");

	TLegendEntry* legEMMECSuSav2 = legEMMEC->AddEntry(EMMECSuSav2,"SuSav2","");
	legEMMECSuSav2->SetTextColor(610);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	legEMMEC->SetBorderSize(0);
	legEMMEC->SetTextSize(TextSize);
	legEMMEC->SetTextFont(FontStyle);
	legEMMEC->Draw();

	delete EMMECPlotCanvas;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program
