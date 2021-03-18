#include <TFile.h>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaletteAxis.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "eGENIE_Constants.h"

using namespace std;

void NuclearModels_Q0_Q3() {

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);	

	int FontStyle = 132;
	double TextSize = 0.07;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t");

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> Channel; 
	std::vector<TString> XLabelOfPlots; 
	std::vector<TString> YLabelOfPlots;  
	std::vector<TString> Tunes;
	std::vector<TString> TuneLabels;  

	nucleus.push_back("C12"); LabelsOfSamples.push_back("^{12}C");

	E.push_back("1161"); LabelE.push_back(" @ E = 1.161 GeV");

	Tunes.push_back("GTEST19_10b_00_000_CCinclMEC_Q2_0_1"); TuneLabels.push_back("#splitline{#nu SuSav2}{Relativistic MF}");
	Tunes.push_back("G18_10a_02_11a_CCinclMEC_Q2_0_1"); TuneLabels.push_back("#splitline{#nu Nieves}{Local FG}");
	Tunes.push_back("G18_02a_00_000_CCinclMEC_Q2_0_1"); TuneLabels.push_back("#splitline{#nu Lwellyn-Smith}{Relativistic FG}");

	Tunes.push_back("GTEST19_10b_00_000_EM+MEC_Q2_0_1"); TuneLabels.push_back("#splitline{e SuSav2}{Relativistic MF}");
	Tunes.push_back("G18_10a_02_11a_EM+MEC_Q2_0_1"); TuneLabels.push_back("#splitline{e Rosenbluth}{Local FG}");
	Tunes.push_back("G18_02a_00_000_EM+MEC_Q2_0_1"); TuneLabels.push_back("#splitline{e Rosenbluth}{Relativistic FG}");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	NameOfPlots.push_back("QE_Q0_Q3_Plot"); XLabelOfPlots.push_back("q_{3} [GeV/c]"); YLabelOfPlots.push_back("q_{0} [GeV]"); Channel.push_back("QE");
//	NameOfPlots.push_back("MEC_Q0_Q3_Plot"); XLabelOfPlots.push_back("q_{3} [GeV/c]"); YLabelOfPlots.push_back("q_{0} [GeV]"); Channel.push_back("MEC");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NTunes = Tunes.size();
	int NPlots = NameOfPlots.size();

	// Loop over the energies

	for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

		// Loop over the nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TString PlotName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]; 
//				TCanvas* PlotCanvas = new TCanvas(PlotName, PlotName, 205,34,2024,820);
				TCanvas* PlotCanvas = new TCanvas(PlotName, PlotName, 205,34,1424,820);


				TLatex *title = new TLatex(); 
				title->SetNDC();
				title->SetTextFont(FontStyle); 
				title->SetTextColor(kBlack); 
				title->SetTextSize(0.1);
//				TString myTitle = LabelsOfSamples[WhichNucleus] + " " +LabelE[WhichEnergy] + ", " + TuneLabels[WhichTune];
//				title->DrawLatex(0.05,0.3,myTitle); // title / nucleus / energy
				TString myTitle = "QE Scattering";
//				title->DrawLatex(0.14,0.9,myTitle); // title / nucleus / energy

				// ---------------------------------------------------------------------------------------------------------------------------

				double XMinPadOne = 0., XMaxPadOne = 0.37, YMinPadOne = 0.5, YMaxPadOne = 1.;
				double XMinPadTwo = 0.37, XMaxPadTwo = 0.68, YMinPadTwo = 0.5, YMaxPadTwo = YMaxPadOne;
				double XMinPadThree = 0.68, XMaxPadThree = 1., YMinPadThree = 0.5, YMaxPadThree = YMaxPadOne;

				double XMinPadFour = 0., XMaxPadFour = 0.37, YMinPadFour = 0.0, YMaxPadFour = 0.5;
				double XMinPadFive = 0.37, XMaxPadFive = 0.68, YMinPadFive = 0.0, YMaxPadFive = 0.5;
				double XMinPadSix = 0.68, XMaxPadSix = 1., YMinPadSix = 0., YMaxPadSix = 0.5;

				// ---------------------------------------------------------------------------------------------------------------------------

				TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadOne,YMinPadOne,XMaxPadOne,YMaxPadOne, 21); 
				pad1->SetFillColor(kWhite); pad1->Draw();
				TPad* pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadTwo,YMinPadTwo,XMaxPadTwo,YMaxPadTwo,22); 
				pad2->SetFillColor(kWhite); pad2->Draw();
				TPad* pad3 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadThree,YMinPadThree,XMaxPadThree,YMaxPadThree,22); 
				pad3->SetFillColor(kWhite); pad3->Draw(); 
				TPad* pad4 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadFour,YMinPadFour,XMaxPadFour,YMaxPadFour,24); 
				pad4->SetFillColor(kWhite); pad4->Draw();
				TPad* pad5 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadFive,YMinPadFive,XMaxPadFive,YMaxPadFive,24); 
				pad5->SetFillColor(kWhite); pad5->Draw();
				TPad* pad6 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadSix,YMinPadSix,XMaxPadSix,YMaxPadSix,24); 
				pad6->SetFillColor(kWhite); pad6->Draw();

				pad1->SetBottomMargin(0.0);
				pad2->SetBottomMargin(0.0);
				pad3->SetBottomMargin(0.0);

				pad1->SetTopMargin(0.16);
				pad2->SetTopMargin(0.16);
				pad3->SetTopMargin(0.16);

				pad4->SetTopMargin(0.0);
				pad5->SetTopMargin(0.0);
				pad6->SetTopMargin(0.0);

				pad4->SetBottomMargin(0.16);
				pad5->SetBottomMargin(0.16);
				pad6->SetBottomMargin(0.16);

				// ---------------------------------------------------------------------------------------------------------------------------

				for (int WhichTune = 0; WhichTune < NTunes; WhichTune ++) {

					if (WhichTune == 0) 
						{ pad1->cd(); gStyle->SetTitleSize(TextSize,"t"); pad1->SetRightMargin(0.); pad1->SetLeftMargin(0.17); pad1->SetTitle("");}
					else if (WhichTune == 1)  { pad2->cd(); pad2->SetLeftMargin(0.0); pad2->SetRightMargin(0.0); }
					
					else if (WhichTune == 2)  { pad3->cd(); pad3->SetLeftMargin(0.0); pad3->SetRightMargin(0.05); }

					else if (WhichTune == 3)  { pad4->cd(); pad4->SetRightMargin(0.); pad4->SetLeftMargin(0.17); }

					else if (WhichTune == 4)  { pad5->cd(); pad5->SetRightMargin(0.); pad5->SetLeftMargin(0.); }

					else if (WhichTune == 5)  { pad6->cd(); pad6->SetRightMargin(0.05); pad6->SetLeftMargin(0.0); }


					TString PathToFiles = "./myFiles/";
					TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+Tunes[WhichTune]+".root";
					TFile* FileSample = TFile::Open(FileName);

					TH2D* Plots =  (TH2D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) ;

					Plots->GetXaxis()->CenterTitle();
					Plots->GetYaxis()->CenterTitle();

					Plots->SetTitleSize(TextSize,"t");
					gStyle->SetTitleX(.47);

					Plots->GetXaxis()->SetLabelFont(FontStyle);
					Plots->GetXaxis()->SetTitleFont(FontStyle);
					Plots->GetXaxis()->SetLabelSize(TextSize);
					Plots->GetXaxis()->SetTitleSize(TextSize);
					Plots->GetXaxis()->SetTitleOffset(1.);
					Plots->GetXaxis()->SetTitle(XLabelOfPlots[WhichPlot]);
					Plots->GetXaxis()->SetTickSize(0.02);

					Plots->GetYaxis()->SetLabelFont(FontStyle);
					Plots->GetYaxis()->SetTitleFont(FontStyle);

					Plots->GetYaxis()->SetLabelSize(TextSize);

//					if (WhichTune == 1) { 
//						Plots->GetXaxis()->SetLabelSize(TextSize+0.02); 
//						Plots->GetXaxis()->SetLabelOffset(-0.01); 

//						Plots->GetXaxis()->SetTitleSize(TextSize+0.02); 
//						Plots->GetXaxis()->SetTitleOffset(0.78); 
//					}

					Plots->GetYaxis()->SetTitleSize(TextSize);
					Plots->GetYaxis()->SetTitleOffset(1.2);
					Plots->GetYaxis()->SetTitle(YLabelOfPlots[WhichPlot]);

					// --------------------------------------------------------------------------------------------------------------------------

					// Rebinning & Ranges

					Plots->GetXaxis()->SetRangeUser(0.25,1.7);
					Plots->GetYaxis()->SetRangeUser(0.01,1.15);

//					Plots->GetZaxis()->SetRangeUser(1.,Plots->GetMaximum());
					double XMin =-99.,XMax =-99.;
					double YMin =-99.,YMax =-99.;

					// -----------------------------------------------------------------------------------------------------------------------------

//					double ScalingFactor = TMath::Power(10.,6.) / Plots->GetMaximum();
//					Plots->Scale(ScalingFactor);

					Plots->GetZaxis()->SetLabelSize(TextSize);
					Plots->GetZaxis()->SetLabelFont(FontStyle);
//					Plots->GetZaxis()->SetTitle("# Events");
					Plots->GetZaxis()->CenterTitle();
					Plots->GetZaxis()->SetTitleFont(FontStyle);
					Plots->GetZaxis()->SetTitleSize(TextSize);

					Plots->GetXaxis()->SetNdivisions(8);
					Plots->GetYaxis()->SetNdivisions(7);

					Plots->Draw("colt");
					PlotCanvas->Update();

//					if (WhichTune == 0) { 

//						TLatex *titleChannel = new TLatex(); 
//						titleChannel->SetNDC();
//						titleChannel->SetTextFont(FontStyle); 
//						titleChannel->SetTextColor(kBlack); 
//						titleChannel->SetTextSize(TextSize);
//						//titleChannel->DrawLatex(0.2,0.8,Channel[WhichPlot]);

//					}


					TLatex *titleParticle = new TLatex(); 
					titleParticle->SetNDC();
					titleParticle->SetTextFont(FontStyle); 
					titleParticle->SetTextColor(kBlack); 
					titleParticle->SetTextSize(TextSize);
					//if (WhichTune == 1) { titleParticle->SetTextSize(TextSize+0.02); }

					if (WhichTune == 0) { titleParticle->DrawLatex(0.25,0.75,TuneLabels[WhichTune]); }
					else if (WhichTune == 1) { titleParticle->DrawLatex(0.09,0.75,TuneLabels[WhichTune]); /*title->DrawLatex(0.27,0.9,myTitle);*/ }
					else if (WhichTune == 2) { titleParticle->DrawLatex(0.09,0.74,TuneLabels[WhichTune]); }
					else if (WhichTune == 3) { titleParticle->DrawLatex(0.25,0.9,TuneLabels[WhichTune]); }
					else if (WhichTune == 4) { titleParticle->DrawLatex(0.09,0.9,TuneLabels[WhichTune]); }
					else if (WhichTune == 5) { titleParticle->DrawLatex(0.09,0.9,TuneLabels[WhichTune]); }

					// ----------------------------------------------------------------------------------------------------------------

					//delete PlotCanvas;

				} // End of the loop over the FSI Models 

				PlotCanvas->SaveAs("myPlots/NuclearModels_"+PlotName+".pdf");

				//delete PlotCanvas;

			} // End of the loop over the plots

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
