#include <TFile.h>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TLatex.h>
#include <TPaletteAxis.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <THStack.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

double TextSize = 0.08;
double FontStyle = 132;

//int DUNEColor = kBlue-9;
//int T2KColor = kOrange-3;
//int NOvAColor = kGreen+1;

int DUNEColor = kBlue-9;
int T2KColor = kOrange+1;
int NOvAColor = kOrange+5;

// -------------------------------------------------------------------------------------------------------------------------------------

void PrettyPlot(TH1D* h, int Color,bool shift) {

	//for (int i = 0; i < 2; i++) { h->Rebin(); }
	h->SetLineColor(Color);
	h->SetLineWidth(3);
	h->Scale(1./h->GetMaximum());

	h->GetXaxis()->SetRangeUser(0.,5.9);
	if (Color == NOvAColor) { h->GetXaxis()->SetRangeUser(0.,4.1);} 
	if (shift) { 
		h->GetXaxis()->SetRangeUser(0.05,5.9); 
		if (Color == NOvAColor) { h->GetXaxis()->SetRangeUser(0.05,4.1);}
	}
	h->GetXaxis()->SetNdivisions(8);
	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetTitleFont(FontStyle);
	h->GetXaxis()->SetLabelFont(FontStyle);
	h->GetXaxis()->SetTitleSize(TextSize);
	h->GetXaxis()->SetLabelSize(TextSize);
	h->GetXaxis()->SetTitleOffset(0.9);
	h->GetXaxis()->SetTickSize(0.02);
	h->GetXaxis()->SetTitle("E_{#nu} [GeV]");

	h->GetYaxis()->SetRangeUser(0.,1.1);
	h->GetYaxis()->SetNdivisions(8);
	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetTitleFont(FontStyle);
	h->GetYaxis()->SetLabelFont(FontStyle);
	h->GetYaxis()->SetTitleSize(TextSize);
	h->GetYaxis()->SetLabelSize(0.);
	h->GetYaxis()->SetTickSize(0.);
	h->GetYaxis()->SetTitleOffset(0.5);
	h->GetYaxis()->SetTitle("#nu Flux [arb.]");

}

// -------------------------------------------------------------------------------------------------------------------------------------

void Fluxes() {

	// -------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(3);

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t");

	// --------------------------------------------------------------------------------------------------------------------------------	

	TString CanvasName = "LB_FluxCanvas";
//	TString CanvasName = "ND_FluxCanvas";

	TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1600,768);

	// ---------------------------------------------------------------------------------------------------------------------------

	TFile* DUNEFile = TFile::Open("/home/afroditi/Dropbox/PhD/myCode/21th_assignment_CalibratedProducts/CodeRootFiles/uboonecode_v08/myGenieAnalysis/myFluxes/LBNF_TDRFlux_Nov19.root");
	TH1D* DUNEND = (TH1D*)( ( (TH2D*)DUNEFile->Get("ND_293kA_nu_numu") )->ProjectionX("",1,2,"") );
	TH1D* DUNEUnosc = (TH1D*)(DUNEFile->Get("FD_nu_numu"));
	TH1D* DUNEOsc = (TH1D*)(DUNEFile->Get("FD_nu_numu_osc"));

	TFile* T2KFile = TFile::Open("t2kflux_2016_plus250kA.root");
	TH1D* T2KND = (TH1D*)(T2KFile->Get("enu_nd280_numu"));
	TH1D* T2KUnosc = (TH1D*)(T2KFile->Get("enu_sk_numu"));
	TH1D* T2KOsc = (TH1D*)(T2KFile->Get("enu_sk_numu_osc_trial"));

	TFile* NOvAFile = TFile::Open("FHC_Flux_NOvA_ND_2017.root");
	TH1D* NOvAND = (TH1D*)(NOvAFile->Get("flux_numu"));
	TH1D* NOvAUnosc = (TH1D*)(NOvAFile->Get("flux_numu_FD"));
	TH1D* NOvAOsc = (TH1D*)(NOvAFile->Get("flux_numu_FD_osc_trial"));

	// ---------------------------------------------------------------------------------------------------------------------------

	TPad* pad1 = new TPad("Unosc","Unosc",0,0,0.5,1., 21); 
	pad1->SetFillColor(kWhite); 
	pad1->SetBottomMargin(0.15);
	pad1->SetRightMargin(0.);
	pad1->Draw();

	TPad* pad2 = new TPad("Osc","Osc",0.5,0,1.,1,22); 
	pad2->SetFillColor(kWhite); 
	pad2->Draw(); 
	pad2->SetBottomMargin(0.15);
	pad2->SetLeftMargin(0.);

	// --------------------------------------------------------------------------------------------------

	PrettyPlot(DUNEND,DUNEColor,false);
	PrettyPlot(T2KND,T2KColor,false);
	PrettyPlot(NOvAND,NOvAColor,false);

	PrettyPlot(DUNEUnosc,DUNEColor,false);
	PrettyPlot(T2KUnosc,T2KColor,false);
	PrettyPlot(NOvAUnosc,NOvAColor,false);

	PrettyPlot(DUNEOsc,DUNEColor,true);
	PrettyPlot(T2KOsc,T2KColor,true);
	PrettyPlot(NOvAOsc,NOvAColor,true);
							
	// --------------------------------------------------------------------------------------------------

	TLine* lineLow = new TLine(1.161,0,1.161,1.1);
	lineLow->SetLineColor(kBlack);
	lineLow->SetLineStyle(kDashed);

	TLine* lineMid = new TLine(2.261,0,2.261,1.1);
	lineMid->SetLineColor(kBlack);
	lineMid->SetLineStyle(kDashed);

	TLine* lineHigh = new TLine(4.461,0,4.461,1.1);
	lineHigh->SetLineColor(kBlack);
	lineHigh->SetLineStyle(kDashed);
	
	// --------------------------------------------------------------------------------------------------

	// Pad 1: Unoscillated spectra

	PlotCanvas->cd();
	pad1->cd();

	if (CanvasName == "LB_FluxCanvas") {

		DUNEUnosc->Draw("c hist same");
		T2KUnosc->Draw("c hist same");
		NOvAUnosc->Draw("c hist same");

	}

	if (CanvasName == "ND_FluxCanvas") {

		DUNEND->Draw("c hist same");
		T2KND->Draw("c hist same");
		NOvAND->Draw("c hist same");

	}

	lineLow->Draw();
	lineMid->Draw();
	lineHigh->Draw();

	// --------------------------------------------------------------------------------------------------

	// Pad 2: Oscillated spectra

	PlotCanvas->cd();
	pad2->cd();

	if (CanvasName == "LB_FluxCanvas") {

		DUNEOsc->Draw("c hist same");
		T2KOsc->Draw("c hist same");
		NOvAOsc->Draw("c hist same");

	}

	if (CanvasName == "ND_FluxCanvas") {

		PrettyPlot(DUNEUnosc,DUNEColor,true);

		DUNEUnosc->Draw("c hist same");
		T2KUnosc->Draw("c hist same");
		NOvAUnosc->Draw("c hist same");

	}

	lineLow->Draw();
	lineMid->Draw();
	lineHigh->Draw();

	// --------------------------------------------------------------------------------------------------

	TLatex *DUNE = new TLatex(); 
	DUNE->SetTextFont(FontStyle); 
	DUNE->SetTextColor(DUNEColor); 
	DUNE->SetTextSize(TextSize);
	DUNE->DrawLatexNDC(0.45,0.82,"DUNE");

	TLatex *T2K = new TLatex(); 
	T2K->SetTextFont(FontStyle); 
	T2K->SetTextColor(T2KColor); 
	T2K->SetTextSize(TextSize);
	T2K->DrawLatexNDC(0.45,0.75,"T2K");

	TLatex *NOvA = new TLatex(); 
	NOvA->SetTextFont(FontStyle); 
	NOvA->SetTextColor(NOvAColor); 
	NOvA->SetTextSize(TextSize);
	NOvA->DrawLatexNDC(0.45,0.68,"NOvA");

	PlotCanvas->SaveAs(CanvasName+".pdf");
	delete PlotCanvas;

	// --------------------------------------------------------------------------------------------------

	// Individual canvases // Unosc spectrum

	TString CanvasNameUnosc = "Unosc_LB_FluxCanvas";
	TCanvas* PlotCanvasUnosc = new TCanvas(CanvasNameUnosc,CanvasNameUnosc,205,34,1000,768);
	PlotCanvasUnosc->cd();
	PlotCanvasUnosc->SetBottomMargin(0.15);

	if (CanvasName == "LB_FluxCanvas") {

		DUNEUnosc->Draw("c hist same");
		T2KUnosc->Draw("c hist same");
		NOvAUnosc->Draw("c hist same");

	}

	if (CanvasName == "ND_FluxCanvas") {

		DUNEND->Draw("c hist same");
		T2KND->Draw("c hist same");
		NOvAND->Draw("c hist same");

	}

	lineLow->Draw();
	lineMid->Draw();
	lineHigh->Draw();

	TLatex *Letter = new TLatex(); 
	Letter->SetTextFont(FontStyle); 
	Letter->SetTextColor(kBlack); 
	Letter->SetTextSize(TextSize);
	Letter->DrawLatexNDC(0.8,0.83,"(a)");

//	DUNE->DrawLatexNDC(0.65,0.82,"DUNE");
//	T2K->DrawLatexNDC(0.65,0.75,"T2K");
//	NOvA->DrawLatexNDC(0.65,0.68,"NOvA");

	PlotCanvasUnosc->SaveAs(CanvasNameUnosc+".pdf");
	PlotCanvasUnosc->SaveAs(CanvasNameUnosc+".eps");

	// --------------------------------------------------------------------------------------------------

	// Individual canvases // Osc spectrum

	TString CanvasNameOsc = "Osc_LB_FluxCanvas";
	TCanvas* PlotCanvasOsc = new TCanvas(CanvasNameOsc,CanvasNameOsc,205,34,1000,768);
	PlotCanvasOsc->cd();
	PlotCanvasOsc->SetBottomMargin(0.15);

	if (CanvasName == "LB_FluxCanvas") {

		DUNEOsc->Draw("c hist same");
		T2KOsc->Draw("c hist same");
		NOvAOsc->Draw("c hist same");

	}

	if (CanvasName == "ND_FluxCanvas") {

		PrettyPlot(DUNEUnosc,DUNEColor,true);

		DUNEUnosc->Draw("c hist same");
		T2KUnosc->Draw("c hist same");
		NOvAUnosc->Draw("c hist same");

	}

	lineLow->Draw();
	lineMid->Draw();
	lineHigh->Draw();

	DUNE->DrawLatexNDC(0.45,0.82,"DUNE");
	T2K->DrawLatexNDC(0.45,0.75,"T2K");
	NOvA->DrawLatexNDC(0.45,0.68,"NOvA");

	TLatex *LetterB = new TLatex(); 
	LetterB->SetTextFont(FontStyle); 
	LetterB->SetTextColor(kBlack); 
	LetterB->SetTextSize(TextSize);
	LetterB->DrawLatexNDC(0.8,0.83,"(b)");

	PlotCanvasOsc->SaveAs(CanvasNameOsc+".pdf");
	PlotCanvasOsc->SaveAs(CanvasNameOsc+".eps");

	// --------------------------------------------------------------------------------------------------

	TCanvas *ctot = new TCanvas("ctot","",2000,768);
	ctot->cd();

	TPad* left = new TPad("left","left",0.,0.,0.5,1.,21);
	left->SetFillColor(kWhite); 
	left->Draw();
	left->cd();

	PlotCanvasUnosc->DrawClonePad();

	ctot->cd();
	TPad* right = new TPad("right","right",0.5,0.,1.,1.,21);
	right->SetFillColor(kWhite); 
	right->Draw();
	right->cd();

	PlotCanvasOsc->DrawClonePad();

	ctot->SaveAs("Merged_FigExtData1.pdf");
	ctot->SaveAs("Merged_FigExtData1.eps");

	// --------------------------------------------------------------------------------------------------

} // End of the program
