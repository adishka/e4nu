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

using namespace std;

void eGENIE_Q0_Q3() {

	gStyle->SetOptStat(0);	

	int Ndivisions = 4;
	int FontStyle = 132;
	double TextSize = 0.07;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	TString Tune = "GTEST19_10b_00_000"; TString TuneLabel = "SuSav2";
//	TString Tune = "G18_10a_02_11a"; TString TuneLabel = "G2018";
//	TString Tune = "G00_00a_00_000"; TString TuneLabel = "G2000";

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t");

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> Interaction;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> Channel; 
	std::vector<TString> XLabelOfPlots; 
	std::vector<TString> YLabelOfPlots;  

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He");
	nucleus.push_back("C12"); LabelsOfSamples.push_back("^{12}C");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

	E.push_back("1161"); LabelE.push_back(" @ E = 1.161 GeV");
//	E.push_back("2261"); LabelE.push_back(" @ E = 2.261 GeV");
//	E.push_back("4461"); LabelE.push_back(" @ E = 4.461 GeV");

	Interaction.push_back("CCinclMEC_Q2_0_1"); FSILabel.push_back("#nu");
	Interaction.push_back("EM+MEC_Q2_0_1"); FSILabel.push_back("e");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

//	NameOfPlots.push_back("QE_Q0_Q3_Plot"); XLabelOfPlots.push_back("q_{3} [GeV/c]"); YLabelOfPlots.push_back("q_{0} [GeV]"); Channel.push_back("QE");
	NameOfPlots.push_back("MEC_Q0_Q3_Plot"); XLabelOfPlots.push_back("q_{3} [GeV/c]"); YLabelOfPlots.push_back("q_{0} [GeV]"); Channel.push_back("MEC");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NInteractions = Interaction.size();
	int NPlots = NameOfPlots.size();

	// Loop over the energies

	for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

		// Loop over the nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TString PlotName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]; 
				TCanvas* PlotCanvas = new TCanvas(PlotName, PlotName, 205,34,2024,768);

				// ---------------------------------------------------------------------------------------------------------------------------

				// Dimensions of TPads (pad2 will be deleted at the very end for the Ereco plots)

				double XMinPadOne = 0., XMaxPadOne = 0.5, YMinPadOne = 0., YMaxPadOne = 1.;
				double XMinPadTwo = 0.5, XMaxPadTwo = 1., YMinPadTwo = 0., YMaxPadTwo = YMaxPadOne;
				double XMinPadThree = 0.5, XMaxPadThree = 0.53, YMinPadThree = 0.07, YMaxPadThree = 0.17;
				double XMinPadFour = 0.3, XMaxPadFour = 0.85, YMinPadFour = 0.91, YMaxPadFour = 1.;

				// ---------------------------------------------------------------------------------------------------------------------------

				TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadOne,YMinPadOne,XMaxPadOne,YMaxPadOne, 21); 
				pad1->SetFillColor(kWhite); pad1->Draw();
				TPad* pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadTwo,YMinPadTwo,XMaxPadTwo,YMaxPadTwo,22); 
				pad2->SetFillColor(kWhite); pad2->Draw(); 
				TPad* pad4 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadFour,YMinPadFour,XMaxPadFour,YMaxPadFour,24); 
				pad4->SetFillColor(kWhite); pad4->Draw();
				pad1->SetBottomMargin(0.16);
				pad2->SetBottomMargin(0.16);

				pad4->cd();
				TLatex *title = new TLatex(); 
				title->SetNDC();
				title->SetTextFont(FontStyle); 
				title->SetTextColor(kBlack); 
				title->SetTextSize(0.8);
				TString myTitle = LabelsOfSamples[WhichNucleus] + " " +LabelE[WhichEnergy] + ", " + TuneLabel;
//				title->DrawLatex(0.05,0.3,myTitle); // title / nucleus / energy

				// ---------------------------------------------------------------------------------------------------------------------------

				for (int WhichInteraction = 0; WhichInteraction < NInteractions; WhichInteraction ++) {

					if (WhichInteraction == 0) { 

						pad1->cd(); gStyle->SetTitleSize(TextSize,"t"); pad1->SetRightMargin(0.); pad1->SetLeftMargin(0.15); 

					} else { pad2->cd(); pad2->SetLeftMargin(0.0); pad2->SetRightMargin(0.15); }

					TString PathToFiles = "./myFiles/";
					TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+Tune+"_"+Interaction[WhichInteraction]+".root";
					TFile* FileSample = TFile::Open(FileName);

					TH2D* Plots =  (TH2D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) ;

					Plots->GetXaxis()->CenterTitle();
					Plots->GetYaxis()->CenterTitle();

					Plots->SetTitleSize(TextSize,"t");
					if (FSILabel[WhichInteraction] == "Data") { gStyle->SetTitleX(.54); }
					else { gStyle->SetTitleX(.47); }

					Plots->GetXaxis()->SetLabelFont(FontStyle);
					Plots->GetXaxis()->SetTitleFont(FontStyle);
					Plots->GetXaxis()->SetLabelSize(TextSize);
					Plots->GetXaxis()->SetTitleSize(TextSize);
					Plots->GetXaxis()->SetTitleOffset(1.);
					Plots->GetXaxis()->SetTitle(XLabelOfPlots[WhichPlot]);

					Plots->GetYaxis()->SetLabelFont(FontStyle);
					Plots->GetYaxis()->SetTitleFont(FontStyle);
					Plots->GetYaxis()->SetLabelSize(TextSize);
					Plots->GetYaxis()->SetTitleSize(TextSize);
					Plots->GetYaxis()->SetTitleOffset(1.);
					Plots->GetYaxis()->SetTitle(YLabelOfPlots[WhichPlot]);

					// --------------------------------------------------------------------------------------------------------------------------

					// Rebinning & Ranges

					Plots->GetXaxis()->SetRangeUser(0.25,1.7);
					Plots->GetYaxis()->SetRangeUser(-0.05,1.15);

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

					if (WhichInteraction == 0) { 

						TLatex *titleChannel = new TLatex(); 
						titleChannel->SetNDC();
						titleChannel->SetTextFont(FontStyle); 
						titleChannel->SetTextColor(kBlack); 
						titleChannel->SetTextSize(TextSize);
						titleChannel->DrawLatex(0.2,0.8,Channel[WhichPlot]);

					}


					TLatex *titleParticle = new TLatex(); 
					titleParticle->SetNDC();
					titleParticle->SetTextFont(FontStyle); 
					titleParticle->SetTextColor(kBlack); 
					titleParticle->SetTextSize(TextSize);
					titleParticle->DrawLatex(0.85-0.15*WhichInteraction,0.8,FSILabel[WhichInteraction]);

					// ----------------------------------------------------------------------------------------------------------------

					//delete PlotCanvas;

				} // End of the loop over the FSI Models 

				PlotCanvas->SaveAs("myPlots/"+PlotName+".pdf");

				//delete PlotCanvas;

			} // End of the loop over the plots

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
