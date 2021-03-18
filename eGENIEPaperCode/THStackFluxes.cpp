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

#include "eGENIE_Constants.h"
#include "eGENIE_Functions.cpp"

using namespace std;

void THStackFluxes() {

	// -------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(3);

	int NBreakDown = 4; // leaving COH out for now

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t");

	// -----------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> XLabelOfPlots; 
	std::vector<TString> YLabelOfPlots;  
	std::vector<TString> OutputPlotNames; 

//	nucleus.push_back("CH"); LabelsOfSamples.push_back("CH");
//	nucleus.push_back("CH2"); LabelsOfSamples.push_back("CH2");
	nucleus.push_back("40Ar"); LabelsOfSamples.push_back("^{40}Ar");

	E.push_back("DUNEFlux"); LabelE.push_back("DUNE Near Detector Flux"); YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-38} #frac{cm^{2}}{GeV Ar}#right]");
	E.push_back("FDDUNEOscFlux"); LabelE.push_back("Far Detector DUNE Oscillated Flux"); YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-38} #frac{cm^{2}}{GeV Ar}#right]");

//	E.push_back("BNBFlux"); LabelE.push_back(" BNB Flux"); YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-38} #frac{cm^{2}}{GeV Ar}#right]");
//	E.push_back("NOvAFlux"); LabelE.push_back(" NOvA Flux");  YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-38} #frac{cm^{2}}{GeV CH2}#right]");
//	E.push_back("T2KFlux"); LabelE.push_back(" T2K Flux");  YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-38} #frac{cm^{2}}{GeV CH}#right]");			

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	TString InteractionMode = "CCinclMEC_Q2_0_0";
//	TString InteractionMode = "CCinclMEC_Q2_0_02";
//	TString InteractionMode = "EM+MEC_Q2_0_0";

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	FSIModel.push_back("GTEST19_10b_00_000_"+InteractionMode);FSILabel.push_back("SuSav2");
	FSIModel.push_back("G18_10a_02_11a_"+InteractionMode);FSILabel.push_back("G2018");
	FSIModel.push_back("G18_02a_00_000_"+InteractionMode);FSILabel.push_back("G18_02a");	

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	NameOfPlots.push_back("EvPlot"); XLabelOfPlots.push_back("E_{#nu} [GeV]"); OutputPlotNames.push_back("EvPlot");

	// --------------------------------------------------------------------------------------------------------------------------------	

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// Loop over the nuclei

	for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

		// Loop over the plots

		for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

			TString CanvasName = nucleus[WhichNucleus]+"_"+NameOfPlots[WhichPlot];
//			TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,2624,768);
			TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1400,768);

			// ---------------------------------------------------------------------------------------------------------------------------

			TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.06,0.5,0.38,1.,21); pad1->SetFillColor(kWhite); pad1->Draw();
			TPad* pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.38,0.5,0.69,1,22); pad2->SetFillColor(kWhite); pad2->Draw();
			TPad* pad3 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.69,0.5,1.,1,22); pad3->SetFillColor(kWhite); pad3->Draw();

			TPad* pad4 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.06,0.,0.38,0.5,21); pad4->SetFillColor(kWhite); pad4->Draw();
			TPad* pad5 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.38,0.,0.69,0.5,22); pad5->SetFillColor(kWhite); pad5->Draw();
			TPad* pad6 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.69,0.,1.,0.5,22); pad6->SetFillColor(kWhite); pad6->Draw();
					
			pad1->SetTopMargin(0.18); pad1->SetBottomMargin(0.);
			pad2->SetTopMargin(0.18); pad2->SetBottomMargin(0.);
			pad3->SetTopMargin(0.18); pad3->SetBottomMargin(0.);

			pad4->SetBottomMargin(0.18); pad4->SetTopMargin(0.);
			pad5->SetBottomMargin(0.18); pad5->SetTopMargin(0.);
			pad6->SetBottomMargin(0.18); pad6->SetTopMargin(0.);	

			// --------------------------------------------------------------------------------------------------

			// Loop over the energies

			for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					if (WhichFSIModel == 0 && WhichEnergy == 0) 
						{ pad1->cd(); gStyle->SetTitleSize(TextSize,"t"); pad1->SetRightMargin(0.); pad1->SetLeftMargin(0.1); pad1->SetTitle("");}
					if (WhichFSIModel == 1 && WhichEnergy == 0)  { pad2->cd(); pad2->SetLeftMargin(0.0); pad2->SetRightMargin(0.0); }
					
					if (WhichFSIModel == 2 && WhichEnergy == 0)  { pad3->cd(); pad3->SetLeftMargin(0.0); pad3->SetRightMargin(0.04); }

					if (WhichFSIModel == 0 && WhichEnergy == 1) 
						{ pad4->cd(); gStyle->SetTitleSize(TextSize,"t"); pad4->SetRightMargin(0.); pad4->SetLeftMargin(0.1); pad3->SetTitle("");}
					if (WhichFSIModel == 1 && WhichEnergy == 1)  { pad5->cd(); pad5->SetLeftMargin(0.0); pad5->SetRightMargin(0.0); }
					
					if (WhichFSIModel == 2 && WhichEnergy == 1)  { pad6->cd(); pad6->SetLeftMargin(0.0); pad6->SetRightMargin(0.04); }

					THStack* THStacks = new THStack(NameOfPlots[WhichPlot]+"_"+FSIModel[WhichFSIModel]+"_"+E[WhichEnergy],"");

					TString PathToFiles = "myFiles/";
					TFile* FileSample = TFile::Open(PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+".root");

					TH1D* Plots[NBreakDown];
					TH1D* Total = nullptr;

					for (int WhichInteraction = 0; WhichInteraction < NBreakDown; WhichInteraction++) {

						Plots[WhichInteraction] =  (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]+"_Interaction_"+ToStringInt(WhichInteraction) ) ) ;	
						if (WhichInteraction == 0) { Total = (TH1D*)Plots[0]->Clone(); }
						else { Total->Add(Plots[WhichInteraction]); }	

					}

					double Weight = XSecNorm(nucleus[WhichNucleus],E[WhichEnergy],FSIModel[WhichFSIModel]);
					//std::cout << "XSec Weight = " << Weight << std::endl;
					Reweight(Total,Weight);
					
					TLegend* leg = new TLegend(0.71,0.53,0.95,0.8);
					if (WhichFSIModel == 1 && WhichEnergy == 0) { leg = new TLegend(0.67,0.53,0.91,0.8); }
					if (WhichFSIModel == 2 && WhichEnergy == 0) { leg = new TLegend(0.65,0.53,0.91,0.8); }
					if (WhichFSIModel == 0 && WhichEnergy == 1) { leg = new TLegend(0.71,0.71,0.95,0.98); }
					if (WhichFSIModel == 1 && WhichEnergy == 1) { leg = new TLegend(0.67,0.71,0.91,0.98); }
					if (WhichFSIModel == 2 && WhichEnergy == 1) { leg = new TLegend(0.65,0.71,0.91,0.98); }
					leg->SetNColumns(1);
					leg->SetMargin(0.);

					TLegend* legFrac = new TLegend(0.83,0.53,1.,0.8);
					if (WhichFSIModel == 1 && WhichEnergy == 0) { legFrac = new TLegend(0.8,0.53,0.96,0.8); }
					if (WhichFSIModel == 2 && WhichEnergy == 0) { legFrac = new TLegend(0.78,0.53,0.95,0.8); }
					if (WhichFSIModel == 0 && WhichEnergy == 1) { legFrac = new TLegend(0.83,0.71,0.95,0.98); }
					if (WhichFSIModel == 1 && WhichEnergy == 1) { legFrac = new TLegend(0.79,0.71,0.91,0.98); }
					if (WhichFSIModel == 2 && WhichEnergy == 1) { legFrac = new TLegend(0.77,0.71,0.91,0.98); }
					legFrac->SetNColumns(1);
					legFrac->SetMargin(0.);

					for (int WhichInteraction = 0; WhichInteraction < NBreakDown; WhichInteraction++) {

						Reweight(Plots[WhichInteraction],Weight);

						Plots[WhichInteraction]->GetXaxis()->CenterTitle();
						Plots[WhichInteraction]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichInteraction]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichInteraction]->GetXaxis()->SetLabelSize(TextSize);

						if (string(FSIModel[WhichFSIModel]).find("G18_10a_02_11a") != std::string::npos) { Plots[WhichInteraction]->GetXaxis()->SetTitleSize(TextSize); }
						else { Plots[WhichInteraction]->GetXaxis()->SetTitleSize(0); }

						Plots[WhichInteraction]->GetXaxis()->SetTitleOffset(1.);
						Plots[WhichInteraction]->GetXaxis()->SetTitle(XLabelOfPlots[WhichPlot]);
						Plots[WhichInteraction]->GetXaxis()->SetNdivisions(6);
						Plots[WhichInteraction]->GetXaxis()->SetTickSize(0.01);

						Plots[WhichInteraction]->GetYaxis()->CenterTitle();
						Plots[WhichInteraction]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichInteraction]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichInteraction]->GetYaxis()->SetLabelSize(TextSize);
						Plots[WhichInteraction]->GetYaxis()->SetLabelOffset(0.01);
						Plots[WhichInteraction]->GetYaxis()->SetTitleSize(TextSize);
						//Plots[WhichInteraction]->GetYaxis()->SetTitleOffset(1.35);
						//Plots[WhichInteraction]->GetYaxis()->SetTitle(YLabelOfPlots[WhichEnergy]);
						Plots[WhichInteraction]->GetYaxis()->SetNdivisions(5);
						Plots[WhichInteraction]->GetYaxis()->SetTickSize(0.02);

//						int color = Colors[WhichInteraction];
						int color = AlternativeColors[WhichInteraction];

						Plots[WhichInteraction]->SetLineColor(color);
						Plots[WhichInteraction]->SetFillColor(color);

						//Plots[WhichInteraction]->SetFillStyle(3004);
						Plots[WhichInteraction]->SetLineWidth(1);

						double MinX = 0.25, MaxX = 9.;
						double MinY = 0.001, MaxY = 31.;
						
						if (E[WhichEnergy] == "DUNEFlux") { 
							MinX = 0.3,MaxX = 5.3; 
							MaxY = 36;
							if (string(FSIModel[WhichFSIModel]).find("EM+MEC") != std::string::npos) { MaxY = 3.E8; }
						}
						if (E[WhichEnergy] == "FDDUNEOscFlux") { 
							MinX = 0.3; MaxX = 5.3; MaxY = 63.;
//							MinX = 0.3; MaxX = 2.5; MaxY = 66.;
//							MinX = 2.7; MaxX = 5.3; MaxY = 29.;

							if (string(FSIModel[WhichFSIModel]).find("EM+MEC") != std::string::npos) { MaxX = 6.E8; }
						}

						Plots[WhichInteraction]->GetXaxis()->SetRangeUser(MinX,MaxX);
						Plots[WhichInteraction]->GetYaxis()->SetRangeUser(MinY,MaxY);
						Total->GetXaxis()->SetRangeUser(MinX,MaxX);
						Total->GetYaxis()->SetRangeUser(MinY,MaxY);

						Plots[WhichInteraction]->Draw("hist same");
						THStacks->Add(Plots[WhichInteraction],"hist");
						THStacks->Draw("hist same");		

					} // End of the loop over the interactions

					// Now let's fill in the legend

					for (int WhichInteraction = NBreakDown-1; WhichInteraction >=0; WhichInteraction--) {

						int color = AlternativeColors[WhichInteraction];

						TString LegEntry = ProcessLabel[WhichInteraction];
						TLegendEntry* lEntry = leg->AddEntry(Plots[WhichInteraction],LegEntry, "");
						lEntry->SetTextColor(color);

						TString LegEntryFrac = "(" + ToStringInt(int(100.*Plots[WhichInteraction]->Integral()/Total->Integral())) + "%)";
						TLegendEntry* lEntryFrac = legFrac->AddEntry(Plots[WhichInteraction],LegEntryFrac, "");
						lEntryFrac->SetTextColor(color);

					}

					// -------------------------------------------------------------------------------------------

					// Rebinning & Ranges

					// -------------------------------------------------------------------------------------------------------
					
					leg->SetBorderSize(0);
					leg->SetTextFont(FontStyle);
					leg->SetTextSize(TextSize-0.01);
					leg->Draw();

					legFrac->SetBorderSize(0);
					legFrac->SetTextFont(FontStyle);
					legFrac->SetTextSize(TextSize-0.01);
					legFrac->Draw(); 

					TLatex *sample = new TLatex(); 
					sample->SetTextFont(FontStyle); 
					sample->SetTextColor(kBlack); 
					sample->SetTextSize(TextSize);

					if (WhichEnergy == 0) {

						if (WhichFSIModel == 0) { sample->DrawLatexNDC(0.15,0.75,FSILabel[WhichFSIModel]); }
						else if (WhichFSIModel == 1) { sample->DrawLatexNDC(0.05,0.75,FSILabel[WhichFSIModel]); }
						else if (WhichFSIModel == 2) { sample->DrawLatexNDC(0.05,0.75,FSILabel[WhichFSIModel]); }

					}
					
//					if (WhichFSIModel == 1) {
//					
//						TLatex *flux = new TLatex(); 
//						flux->SetTextFont(FontStyle); 
//						flux->SetTextColor(kBlack); 
//						flux->SetTextSize(TextSize);
//						if (E[WhichEnergy] == "FDDUNEOscFlux") { flux->DrawLatexNDC(0.,0.92,LabelE[WhichEnergy]); }
//						if (E[WhichEnergy] == "DUNEFlux") { flux->DrawLatexNDC(0.11,0.92,LabelE[WhichEnergy]); }
//					
//					}

					gPad->RedrawAxis();

					//delete PlotCanvas;

				} // End of the loop over the FSI Models 

					PlotCanvas->cd();
					TPad* padTitle = new TPad("padTitle","padTitle",0.,0.,0.05,1., 21); 
					padTitle->SetFillColor(kWhite); 
					padTitle->Draw();
					padTitle->cd();

					TLatex latexYTitle;
					latexYTitle.SetTextFont(FontStyle);
					latexYTitle.SetTextSize(6*TextSize);
					latexYTitle.SetTextColor(kBlack);
					latexYTitle.SetTextAngle(90);
					latexYTitle.DrawLatexNDC(0.65,0.35,YLabelOfPlots[WhichEnergy]);

				PlotCanvas->cd();
				TPad* pad7 = new TPad("Title","Title",0.,0.92,01,1,21); 
				pad7->SetFillColor(kWhite); 
				pad7->Draw();
				pad7->cd();

				TLatex *flux = new TLatex(); 
				flux->SetTextFont(FontStyle); 
				flux->SetTextColor(kBlack); 
				flux->SetTextSize(14*TextSize);
//				if (E[WhichEnergy] == "FDDUNEOscFlux") { flux->DrawLatexNDC(0.365,0.2,LabelE[WhichEnergy]); }
//				if (E[WhichEnergy] == "DUNEFlux") { flux->DrawLatexNDC(0.41,0.2,LabelE[WhichEnergy]); }

				//delete PlotCanvas;

			} // End of the loop over the energies

			PlotCanvas->SaveAs("myPlots/DUNEPanel_"+InteractionMode+".pdf");

		} // End of the loop over the plots

	} // End of the loop over the nuclei

} // End of the program
