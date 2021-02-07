#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>

#include <iostream>
#include <vector>

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

void FractionalContribution() {

	// ------------------------------------------------------------------------

	GlobalSettings();

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut;
	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots;
	std::vector<TString> NameOfSubPlots;
	std::vector<int> Colors;

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV");
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV");	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");
 
	Colors.push_back(kBlack); Colors.push_back(610); Colors.push_back(kBlack); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);

	FSIModel.push_back("SuSav2"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("hA2018_Final"); FSILabel.push_back("G2018");

//	NameOfPlots.push_back("Reco_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("TrueWithFid_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("True_eRecoEnergy_slice_0");

//	NameOfPlots.push_back("BkgCorrection_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("FidCorrection_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("AccCorrection_eRecoEnergy_slice_0");

//	NameOfPlots.push_back("Reco_epRecoEnergy_slice_0");
//	NameOfPlots.push_back("TrueWithFid_epRecoEnergy_slice_0");
//	NameOfPlots.push_back("True_epRecoEnergy_slice_0");

	NameOfPlots.push_back("AccCorrection_epRecoEnergy_slice_0");

	// ------------------------------------------------------------------------

	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// ------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				// Loop over the plots

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					TCanvas* PlotCanvas = new TCanvas(nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
									 nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
									 205,34,1024,768);
				
					PlotCanvas->SetLeftMargin(0.15);
					PlotCanvas->SetBottomMargin(0.17);	
					PlotCanvas->SetGridx();	
					PlotCanvas->SetGridy();	

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					TLegend* leg = new TLegend(0.2,0.7,0.5,0.89);
					leg->SetNColumns(1);

					double max = -99.;
					double min = 1E12;

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString FileName = "myFiles/Efficiency_"+FSIModel[WhichFSIModel]+"_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+xBCut[WhichxBCut]+".root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(FSIModel[WhichFSIModel]+"_"+NameOfPlots[WhichPlot]) ) );

//						Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);

//						// ---------------------------------------------------------------------------------------------------

//						TLegendEntry* l1 = leg->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel], "l");
//						l1->SetTextColor(Colors[WhichFSIModel]);

//						// ---------------------------------------------------------------------------------------------------

//						// Max, min, title & # divisions

//						double localmax = Plots[WhichFSIModel]->GetMaximum();
//						if (localmax > max) { max = localmax; }
//						double height = 1.1;
//						Plots[0]->SetMaximum(height*max);

//		                                // --------------------------------------------------------------------------------------------------

////						Plots[WhichFSIModel]->Draw("C hist same");
////						Plots[0]->Draw("C hist same");

//						Plots[WhichFSIModel]->Draw("e  same");
////						Plots[0]->Draw("e  same");

		                                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

//					leg->SetBorderSize(0);
//					leg->SetTextFont(FontStyle);
//					leg->SetTextSize(TextSize);
//					leg->Draw();

					TH1D* clone = (TH1D*)(Plots[0]->Clone());
					clone->Add(Plots[1],-1);
					clone->Divide(Plots[0]);
					clone->Scale(100.);

					clone->GetYaxis()->SetTitle("Fractional Contribution (%)");
//					clone->GetYaxis()->SetRangeUser(-20,20);
					clone->GetYaxis()->SetRangeUser(-100,100);

					clone->GetXaxis()->SetNdivisions(8);
					clone->GetYaxis()->SetNdivisions(10);

					clone->Draw("e same");

					// -----------------------------------------------------------------------------------------------------------------------------------------

//					TString ext = "";
//					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

//					PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
//						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+WhatModelsAreIncluded+".pdf");

					//delete PlotCanvas;

					// -----------------------------------------------------------------------------------------------------------------------------------------

				} // End of the loop over the plots

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
