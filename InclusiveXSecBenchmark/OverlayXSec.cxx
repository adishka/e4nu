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

void OverlayXSec() {

	int FontStyle = 132;
	double TextSize = 0.07;
	TGaxis::SetMaxDigits(3);
	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize-0.02,"t");
	gStyle->SetTitleFont(FontStyle,"t");

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	TString TxtName = "../SuSav2_e4nuPaper_PlottingCode/AccCorrXSec/myXSec/InclusiveJLab_XSec.txt";
	ofstream myTxtFile;
	myTxtFile.open(TxtName);
	myTxtFile << std::fixed << std::setprecision(3);
	myTxtFile << "Inclusive JLab Cross Section Ext Data Fig.3;" << endl << endl;
	myTxtFile << "Bin #;Low bin edge; High bin edge;XSec [μbarn/(sr GeV)];XSec error [μbarn/(sr GeV)]" << endl << endl;

	// ---------------------------------------------------------------------------------------------

	TString CanvasName = "DataXSec_Inclusive_Validation";
	TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
				
	PlotCanvas->SetLeftMargin(0.18);
	PlotCanvas->SetBottomMargin(0.17);

	// ---------------------------------------------------------------------------------------------

	// SLAC Data E = 1.299 GeV

	TFile* DataFile = TFile::Open("eQEupdated.root");
	TTree* qent = (TTree*)(DataFile->Get("qent"));
	int n = qent->Draw("v:xsec:xsec_err","Z==6 && A == 12 && E == 1.299 && theta == 37.5","goff");
	TGraphErrors *DataGraph = new TGraphErrors(n,qent->GetV1(),qent->GetV2(),0,qent->GetV3());

//	DataGraph->SetTitle("#theta = 37.5^{o}");
	DataGraph->SetTitle("");

	DataGraph->GetXaxis()->SetTitle("Energy Transfer [GeV]");
	DataGraph->GetXaxis()->CenterTitle();
	DataGraph->GetXaxis()->SetNdivisions(8);
	DataGraph->GetXaxis()->SetLabelFont(FontStyle);
	DataGraph->GetXaxis()->SetLabelSize(TextSize);
	DataGraph->GetXaxis()->SetTitleFont(FontStyle);
	DataGraph->GetXaxis()->SetTitleSize(TextSize);
	DataGraph->GetXaxis()->SetTitleOffset(1.1);
	DataGraph->GetXaxis()->SetLabelOffset(0.015);

	DataGraph->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#OmegadE_{e}} #left[#frac{#mub}{sr GeV ^{12}C}#right]"); // keep in mind that the xsec is in nb, just hiding the 10^3
	DataGraph->GetYaxis()->CenterTitle();
	DataGraph->GetYaxis()->SetNdivisions(7);
	DataGraph->GetYaxis()->SetLabelFont(FontStyle);
	DataGraph->GetYaxis()->SetLabelSize(TextSize);
	DataGraph->GetYaxis()->SetTitleFont(FontStyle);
	DataGraph->GetYaxis()->SetTitleSize(TextSize);
	DataGraph->GetYaxis()->SetTitleOffset(1.1);

	DataGraph->GetXaxis()->SetRangeUser(0.0,0.85);
	DataGraph->GetYaxis()->SetRangeUser(0,7999); // Y axis in nb / sr / GeV

	DataGraph->SetMarkerStyle(20);
	DataGraph->SetMarkerColor(kBlue+1);
	DataGraph->SetLineColor(kBlue+1);
	DataGraph->Draw("AP");

	// ---------------------------------------------------------------------------------------------

	// SLAC Data E = 0.961 GeV

	int nLow = qent->Draw("v:xsec:xsec_err","Z==6 && A == 12 && E == 0.961 && theta == 37.5","goff");
	TGraphErrors *DataGraphLow = new TGraphErrors(nLow,qent->GetV1(),qent->GetV2(),0,qent->GetV3());

	DataGraphLow->SetMarkerStyle(20);
	DataGraphLow->SetMarkerColor(kOrange+7);
	DataGraphLow->SetLineColor(kOrange+7);
	DataGraphLow->Draw("P");

	// ---------------------------------------------------------------------------------------------

	// SuSav2 GENIE Out-Of-The-Box @ E = 1.161 GEV & theta = 37.5 deg

//	TFile* GenieBoxFile = TFile::Open("GenieOutOfTheBox_12C_DoubleDiff_E_1_161GeV_theta_37_5.root");
//	TH1D* GenieBoxPlot = (TH1D*)GenieBoxFile->Get("v_distribution");

	TFile* GenieBoxFile = TFile::Open("GenieOutOfTheBox_12C_DoubleDiff_E_1_161GeV_theta_37_5_FineBin.root");
	TGraph* GenieBoxPlot = (TGraph*)GenieBoxFile->Get("Simulation");

	GenieBoxPlot->SetLineColor(kGreen+2);
	GenieBoxPlot->SetLineWidth(2);

	GenieBoxPlot->Draw("c same");

	// ---------------------------------------------------------------------------------------------

	// G2018 GENIE Out-Of-The-Box @ E = 1.161 GEV & theta = 37.5 deg

	TFile* G2018_GenieBoxFile = TFile::Open("G2018_GenieOutOfTheBox_12C_DoubleDiff_E_1_161GeV_theta_37_5_FineBin.root");
	TGraph* G2018_GenieBoxPlot = (TGraph*)G2018_GenieBoxFile->Get("Simulation");
//	G2018_GenieBoxPlot->Rebin();
//	G2018_GenieBoxPlot->Scale(0.5);

	G2018_GenieBoxPlot->SetLineColor(kGreen+2);
	G2018_GenieBoxPlot->SetLineStyle(kDashed);
	G2018_GenieBoxPlot->SetLineWidth(2);

//	G2018_GenieBoxPlot->Draw("c same"); 

	// ---------------------------------------------------------------------------------------------

	// SuSav2 GENIE Out-Of-The-Box @ E = 1.299 GEV & theta = 37.5 deg

	TFile* GenieBoxFile1299 = TFile::Open("C12_E_1_299_theta_37_5.root");

	TGraph* GenieBoxPlot1299 = (TGraph*)GenieBoxFile1299->Get("Simulation");

//	GenieBoxPlot1299->SetLineColor(kBlack);
	GenieBoxPlot1299->SetLineColor(kBlue+1);
	GenieBoxPlot1299->SetLineWidth(2);

	GenieBoxPlot1299->Draw("c same");

	// ---------------------------------------------------------------------------------------------

	// SuSav2 GENIE Out-Of-The-Box @ E = 0.961 GEV & theta = 37.5 deg

	TFile* GenieBoxFile0961 = TFile::Open("C12_E_0_961_theta_37_5.root");

	TGraph* GenieBoxPlot0961 = (TGraph*)GenieBoxFile0961->Get("Simulation");

	GenieBoxPlot0961->SetLineColor(kOrange+7);
	GenieBoxPlot0961->SetLineWidth(2);

	GenieBoxPlot0961->Draw("c same");

	// ---------------------------------------------------------------------------------------------

	TString PlotName = "h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0";

	// ---------------------------------------------------------------------------------------------

	// SuSav2 e4v // Sanity check

	TFile* GenieFile = TFile::Open("/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/1_161/SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc_XSec/NoxBCut/12C_1_161_SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc_XSec_Plots_FSI_em.root");

	TH1D* GeniePlot = (TH1D*)GenieFile->Get(PlotName);
	GeniePlot->Rebin();
	UniversalE4vFunction(GeniePlot,"SuSav2 NoRad","12C","1_161",PlotName);

	GeniePlot->SetLineColor(kBlue+1);
	GeniePlot->SetLineWidth(2);

	GeniePlot->Scale(1./0.00667); // sr -> solid angle for 36 < theta < 39 & 24 < phi < 36 
	GeniePlot->Scale(1000); // Conversion from ub to nb
	//GeniePlot->Draw("c hist same");

	// ---------------------------------------------------------------------------------------------

	// G2018 e4v // Sanity check

	TFile* G2018GenieFile = TFile::Open("/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/1_161/hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc_XSec/NoxBCut/12C_1_161_hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc_XSec_Plots_FSI_em.root");

	TH1D* G2018GeniePlot = (TH1D*)G2018GenieFile->Get(PlotName);
	G2018GeniePlot->Rebin();
	UniversalE4vFunction(G2018GeniePlot,"G2018 NoRad","12C","1_161",PlotName);

	G2018GeniePlot->SetLineColor(kMagenta);
	G2018GeniePlot->SetLineWidth(2);

	G2018GeniePlot->Scale(1./0.00667); // sr -> solid angle for 36 < theta < 39 & 24 < phi < 36 
	G2018GeniePlot->Scale(1000); // Conversion from ub to nb
	//G2018GeniePlot->Draw("c hist same");

	// ---------------------------------------------------------------------------------------------

	// Uncorrected Data e4v

	TFile* Datae4vFile = TFile::Open("/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/myFiles/1_161/Pinned_Data_Final_XSec/NoxBCut/12C_1_161_Pinned_Data_Final_XSec_Plots_FSI_em.root");

	TH1D* Datae4vPlot = (TH1D*)Datae4vFile->Get(PlotName);
	UniversalE4vFunction(Datae4vPlot,"Pinned Data","12C","1_161",PlotName);

	Datae4vPlot->SetLineColor(kGreen+2);
	Datae4vPlot->SetMarkerColor(kGreen+2);
	Datae4vPlot->SetMarkerStyle(20);

	Datae4vPlot->Scale(1./0.0067); // sr: solid angle for 24 < phi < 36 && 36 < theta < 39 
	Datae4vPlot->Scale(1000); // Conversion from ub to nb
	Datae4vPlot->SetMarkerStyle(4);
	//Datae4vPlot->Draw("e1x0 same");

	// ---------------------------------------------------------------------------------------------

	// Corrected Data e4v

	TFile* CorrectedDatae4vFile = TFile::Open("e4v_C12_E_1_161_theta_37_5.root");

	TH1D* CorrectedDatae4vPlot = (TH1D*)CorrectedDatae4vFile->Get("Correctede4vData"); // already extracted xsec in e4vXSecRatio.cxx solid angle for 24 < phi < 36 && 36 < theta < 39 

	CorrectedDatae4vPlot->SetLineColor(kGreen+2);
	CorrectedDatae4vPlot->SetMarkerColor(kGreen+2);
	CorrectedDatae4vPlot->SetMarkerStyle(20);
	CorrectedDatae4vPlot->SetMarkerSize(1.);
	CorrectedDatae4vPlot->SetLineWidth(1);
	CorrectedDatae4vPlot->Draw("e1x0 same");

	// ---------------------------------------------------------------------------------------------

	// Nature Data Release

	int nbins = CorrectedDatae4vPlot->GetXaxis()->GetNbins();

	int counter = 0;

	for (int i = 0; i < nbins; i++) {

		double BinContent = CorrectedDatae4vPlot->GetBinContent(i+1) / 1000.; // nb to μb conversion
		double BinError = CorrectedDatae4vPlot->GetBinError(i+1) / 1000.; // nb to μb conversion
		double BinLowEdge = CorrectedDatae4vPlot->GetBinLowEdge(i+1);			
		double BinWidth = CorrectedDatae4vPlot->GetBinWidth(i+1);
		double PreviousBinWidth = CorrectedDatae4vPlot->GetBinWidth(i);
		double BinHighEdge = BinLowEdge + BinWidth;

		if (BinLowEdge > 0.07 && BinLowEdge < 0.73) {
			myTxtFile << counter+1 << ";" << BinLowEdge << ";" << BinHighEdge << ";" << BinContent << ";" << BinError << endl;
			counter++;
		}

	}

	myTxtFile << endl;

	// ---------------------------------------------------------------------------------------------

//	// Data e4v High Torus 1500

//	TFile* HighDatae4vFile = TFile::Open("HighTorus_12C_1_161_Pinned_Data_Final_XSec_Plots_FSI_em.root");

//	TH1D* HighDatae4vPlot = (TH1D*)HighDatae4vFile->Get(PlotName);
//	UniversalE4vFunction(HighDatae4vPlot,"Pinned Data","12C","1_161",PlotName);

//	HighDatae4vPlot->SetLineColor(kMagenta);
//	HighDatae4vPlot->SetMarkerColor(kMagenta);
//	HighDatae4vPlot->SetMarkerStyle(20);

//	double HighTorusC12IntCharge = 0.105; // mC

//	// using the correct 1500 integrated charge instead of the 750 one for the normalization
//	HighDatae4vPlot->Scale(IntegratedCharge_PinnedFiles[std::make_pair("12C","1_161")] / HighTorusC12IntCharge);

//	HighDatae4vPlot->Scale(1./0.0067); // sr: solid angle for 24 < phi < 36 && 36 < theta < 39 
//	HighDatae4vPlot->Scale(1000); // Conversion from ub to nb
//	HighDatae4vPlot->Draw("e1x0 same");


	// ---------------------------------------------------------------------------------------------
//	// ---------------------------------------------------------------------------------------------

//	TLegend* leg = new TLegend(0.35,0.65,0.4,0.89);
//	leg->SetNColumns(1);

//	leg->AddEntry(DataGraph,"SLAC/Sealock Data E_{e} = 1.299 GeV","lep");

//	TLegendEntry* lDataLow = leg->AddEntry(DataGraphLow,"SLAC/Sealock Data E_{e} = 0.961 GeV", "lep");
//	lDataLow->SetTextColor(kRed+1);

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

	leg->AddEntry(DataGraph,"1.299 GeV","");

	TLegendEntry* lDataLow = leg->AddEntry(DataGraphLow,"0.961 GeV", "");
	lDataLow->SetTextColor(kOrange+7);

//	TLegendEntry* lGenie = leg->AddEntry(GeniePlot,"e4v GENIE E_{e} = 1.161 GeV, 24^{o} < #phi_{e'} < 36^{o}", "l");
//	lGenie->SetTextColor(kBlue);

//	TLegendEntry* lGenieBox = leg->AddEntry(GenieBoxPlot,"GENIE E_{e} = 1.161 GeV", "l");
//	lGenieBox->SetTextColor(kGreen+2);

	TLegendEntry* lDatae4v = leg->AddEntry(Datae4vPlot,"1.161 GeV", "");
	lDatae4v->SetTextColor(kGreen+2);

//	TLegendEntry* lHighTorusDatae4v = leg->AddEntry(HighDatae4vPlot,"1.161 GeV", "");
//	lHighTorusDatae4v->SetTextColor(kMagenta);

	leg->SetBorderSize(0);
	leg->SetTextFont(FontStyle);
	leg->SetTextSize(TextSize-0.01);
//	leg->Draw();

	// ---------------------------------------------------------------------------------------------

	TLatex* Latex1299 = new TLatex();
	Latex1299->SetTextFont(FontStyle);
	Latex1299->SetTextSize(TextSize-0.01);
//	Latex1299->SetTextColor(kBlack);
	Latex1299->SetTextColor(kBlue+1);
	Latex1299->DrawLatexNDC(0.5,0.22,"SLAC 1.299 GeV");

	// ---------------------------------------------------------------------------------------------

	TLatex* Latex0961 = new TLatex();
	Latex0961->SetTextFont(FontStyle);
	Latex0961->SetTextSize(TextSize-0.01);
	Latex0961->SetTextColor(kOrange+7);
	Latex0961->DrawLatexNDC(0.32,0.80,"SLAC 0.961 GeV");

	// ---------------------------------------------------------------------------------------------

	TLatex* Latex1161 = new TLatex();
	Latex1161->SetTextFont(FontStyle);
	Latex1161->SetTextSize(TextSize-0.01);
	Latex1161->SetTextColor(kGreen+2);
	Latex1161->SetTextAlign(12);  //centered
	Latex1161->DrawLatexNDC(0.7,0.57,"#splitline{JLab}{1.159 GeV}");

	// ---------------------------------------------------------------------------------------------

	// Scattering angle

	TLatex* LatexAngle = new TLatex();
	LatexAngle->SetTextFont(FontStyle);
	LatexAngle->SetTextSize(TextSize-0.01);
	LatexAngle->SetTextColor(kBlack);
	LatexAngle->SetTextAlign(12);  //centered
	LatexAngle->DrawLatexNDC(0.73,0.86,"#theta = 37.5^{o}");

	// ---------------------------------------------------------------------------------------------

	PlotCanvas->SaveAs("DataXSec_Inclusive_Validation.pdf");
	PlotCanvas->SaveAs("DataXSec_Inclusive_Validation.eps");

	TFile* f = new TFile("DataXSec_Inclusive_Validation.root","recreate");
	gStyle->SetOptStat(0);	
	TGaxis::SetMaxDigits(3);
	TGaxis::SetExponentOffset(-0.1, 1., "y");
	PlotCanvas->Write();

} // End of the program
