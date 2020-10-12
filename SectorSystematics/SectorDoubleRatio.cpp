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
#include <vector>
#include <map>
#include <utility>

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

// To run the code

// root -l
// .L SectorDoubleRatio.cpp
// SectorDoubleRatio("12C",4461,"ECal")

// ----------------------------------------------------------------------------------------------------------------

void SectorDoubleRatio(TString Nucleus = "12C", double Energy = 4.461, TString Ereco = "ECal", TString xBCut = "NoxBCut") {

	// ------------------------------------------------------------------------

	// Available options for input parameters

	// Nucleus = {"12C","4He","56Fe","CH2"}
	// Energy = {1.161,2.261,4.461}
	// Ereco = {"ECal","EQE","Omega"}
	// xBCut = {"NoxBCut","xBCut"}

	// ------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	// ------------------------------------------------------------------------

	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> SectorLabel;  

	TString LabelsOfSamples = "^{12}C";
	if (Nucleus == "4He") { LabelsOfSamples = "^{4}He"; }
	if (Nucleus == "CH2") { LabelsOfSamples = "CH2"; }
	if (Nucleus == "56Fe") { LabelsOfSamples = "^{56}Fe"; }

	TString E = "4_461", LabelE = " @ E = 4.461 GeV";
	if (Energy == 2.261) { E = "2_261"; LabelE = " @ E = 2.261 GeV"; }
	if (Energy == 1.161) { E = "1_161"; LabelE = " @ E = 1.161 GeV"; }

	FSIModel.push_back("Pinned_Data_Final_SixSectors"); FSILabel.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM_SixSectors"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_SixSectors"); FSILabel.push_back("G2018");

	SectorLabel.push_back("1st");
	SectorLabel.push_back("2nd");
	SectorLabel.push_back("3rd");
	SectorLabel.push_back("4th");
	SectorLabel.push_back("5th");
	SectorLabel.push_back("6th");

	TString NameOfPlots = "h1_"+Ereco+"_InSector_", LabelOfPlots = "(e,e'p)_{1p0#pi} E^{Cal} [GeV]", OutputPlotNames = Ereco+"_InSector";
	if (Ereco == "EQE") { LabelOfPlots = "(e,e')_{0#pi} E^{QE} [GeV]"; }
	if (Ereco == "Omega") { NameOfPlots = "h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_"; LabelOfPlots = "Energy Transfer [GeV]"; }

	const int NFSIModels = FSIModel.size();
	const int NPlots = SectorLabel.size();

	TFile* Files[NFSIModels];
	TH1D* Plots[NFSIModels][NPlots];

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the Data / SuSav2 / G2018 files

	for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

		// ---------------------------------------------------------------------------------------

		TString CanvasName =  FSILabel[WhichFSIModel]+Nucleus+"_"+E+"_"+xBCut + "_" + Ereco;
		TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

		PlotCanvas->SetBottomMargin(0.17);
		PlotCanvas->SetLeftMargin(0.17);

		TLegend* leg = leg = new TLegend(0.2,0.7,0.5,0.85);
		leg->SetNColumns(3);

		// ---------------------------------------------------------------------------------------

		double max = -99.;
		double min = 1E12;

		TString PathToFiles = "../../myFiles/"+ E + "/"+FSIModel[WhichFSIModel]+"/"+xBCut+"/";
		TString FileName = PathToFiles+Nucleus+"_"+E+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
		Files[WhichFSIModel] = TFile::Open(FileName);

		// Loop over the plots

		for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

			// ------------------------------------------------------------------------------------------------------------------

			// Grab the relevant plot

			Plots[WhichFSIModel][WhichPlot] = (TH1D*)( Files[WhichFSIModel]->Get( NameOfPlots+ToStringInt(WhichPlot) ) );

			// -------------------------------------------------------------------------------------------------------------------

			// Make the plot pretty

			Plots[WhichFSIModel][WhichPlot]->SetLineColor(SectorColors[WhichPlot]);
			Plots[WhichFSIModel][WhichPlot]->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples+LabelE);
			Plots[WhichFSIModel][WhichPlot]->GetXaxis()->SetTitle(LabelOfPlots);
			PrettyDoubleXSecPlot(Plots[WhichFSIModel][WhichPlot]);

			// --------------------------------------------------------------------------------------

			// Scale to obtain absolute double differential cross sections 
			// Use charge, density and length for data samples
			// Use total number of events in genie sample and relevant genie cross sections for simulation

			AbsoluteXSecScaling(Plots[WhichFSIModel][WhichPlot],FSILabel[WhichFSIModel],Nucleus,E); 

			// -----------------------------------------------------------------------------------

			// Division by bin width, function defined in myFunctions.C
			// Accounting for the fact that the bin width might not be constant

			ReweightPlots(Plots[WhichFSIModel][WhichPlot]);

			// --------------------------------------------------------------------------------------

			// Rebining & ranges

			BinningAndRange(Plots[WhichFSIModel][WhichPlot],Energy,Ereco);

			// ----------------------------------------------------------------------------------

			// Apply Systematic Uncertainties on Data Points
			// using numbers obtained from Mariana's thesis

			if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { ApplySystUnc(Plots[WhichFSIModel][WhichPlot], Energy); }

			// ---------------------------------------------------------------------------------------------------

			// Max, min

			double localmax = Plots[WhichFSIModel][WhichPlot]->GetMaximum();
			double localmin = Plots[WhichFSIModel][WhichPlot]->GetMinimum();

			if (localmax > max) { max = localmax; }
			if (localmin < min) { min = localmin; }
			double ExtraHeight = 0.1;
			double PosNegMin = TMath::Min(0.,min);
			Plots[WhichFSIModel][0]->GetYaxis()->SetRangeUser( (1+ExtraHeight)*PosNegMin, (1+ExtraHeight)*max );

			// --------------------------------------------------------------------------------------------------

			if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

				Plots[WhichFSIModel][WhichPlot]->SetMarkerStyle(MarkerStyle); 
				Plots[WhichFSIModel][WhichPlot]->SetMarkerSize(MarkerSize); 
				Plots[WhichFSIModel][WhichPlot]->SetMarkerColor(SectorColors[WhichPlot]); 

				gStyle->SetErrorX(0); // Removing the horizontal errors
				Plots[WhichFSIModel][WhichPlot]->Draw("e same"); 
				Plots[WhichFSIModel][0]->Draw("e same"); 

			} else { 

				Plots[WhichFSIModel][WhichPlot]->Draw("C hist same");  // draw them as lines
				Plots[WhichFSIModel][0]->Draw("C hist same"); 

			}

			if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
				{ leg->AddEntry(Plots[WhichFSIModel][WhichPlot],SectorLabel[WhichPlot], "lep");}
			else { leg->AddEntry(Plots[WhichFSIModel][WhichPlot],SectorLabel[WhichPlot], "l"); }
			

			// ---------------------------------------------------------------------------------------------------
			// --------------------------------------------------------------------------------------------------


		} // End of the loop over the plots

		// -----------------------------------------------------------------------------------------------------------------------------------------

		leg->SetBorderSize(0);
		leg->SetTextFont(FontStyle);
		leg->SetTextSize(TextSize);
		leg->Draw();

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TString ext = "";
		if ( xBCut == "xBCut" ) { ext = "xB_"; } 

//		PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut+"/"+version+Nucleus+"/"+E+"/"+ext+Nucleus+"_"+E+"_" +OutputPlotNames+".pdf");

//		delete PlotCanvas;


	} // End of the loop over the FSI Models 

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Ratio & double ratio study

	if (NFSIModels > 1) {

		TH1D* RatioPlots[NFSIModels-1][NPlots];
		TH1D* DoubleRatioPlots[NFSIModels-1][NPlots];

		// First sample will be data
		// Loop over simulation files

		for (int WhichFSIModel = 1; WhichFSIModel < NFSIModels; WhichFSIModel++) {

			// Ratio studies

			TString RatioCanvasName = "Ratio_"+FSILabel[WhichFSIModel]+Nucleus+"_"+E+"_"+xBCut + Ereco; 
			TCanvas* RatioPlotCanvas = new TCanvas(RatioCanvasName,RatioCanvasName,205,34,1024,768);

			RatioPlotCanvas->SetBottomMargin(0.17);
			RatioPlotCanvas->SetLeftMargin(0.17);

			TLegend* Ratioleg = new TLegend(0.2,0.7,0.5,0.85);
			Ratioleg->SetNColumns(3);

			double Ratiomax = -99.;
			double Ratiomin = 1E12;

			// Loop over the 6 sector plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot++) {

				RatioPlots[WhichFSIModel-1][WhichPlot] = (TH1D*)( Plots[0][WhichPlot]->Clone() );
				RatioPlots[WhichFSIModel-1][WhichPlot]->Divide(Plots[WhichFSIModel][WhichPlot]);

				RatioPlots[WhichFSIModel-1][WhichPlot]->GetYaxis()->SetTitle("Ratio");

				RatioPlots[WhichFSIModel-1][WhichPlot]->SetTitle(FSILabel[0] + "/" + FSILabel[WhichFSIModel] + ", " + LabelsOfSamples+LabelE);

				// ---------------------------------------------------------------------------------------------------

				// Max, min

				double localRatiomax = RatioPlots[WhichFSIModel-1][WhichPlot]->GetMaximum();
				double localRatiomin = RatioPlots[WhichFSIModel-1][WhichPlot]->GetMinimum();

				if (localRatiomax > Ratiomax) { Ratiomax = localRatiomax; }
				if (localRatiomin < Ratiomin) { Ratiomin = localRatiomin; }
				double RatioExtraHeight = 0.1;
				double RatioPosNegMin = TMath::Min(-0.5,Ratiomin);
				double RatioPosNegMax = TMath::Min(4.,Ratiomax);
				RatioPlots[0][0]->GetYaxis()->SetRangeUser( (1+RatioExtraHeight)*RatioPosNegMin, (1+RatioExtraHeight)*RatioPosNegMax );

				// ---------------------------------------------------------------------------------------------------

				RatioPlotCanvas->cd();
				RatioPlots[WhichFSIModel-1][WhichPlot]->Draw("e same");
				RatioPlots[0][WhichPlot]->Draw("e same");

				Ratioleg->AddEntry(RatioPlots[WhichFSIModel-1][WhichPlot],SectorLabel[WhichPlot], "lep");

			} // End of the loop over the 6 sector plots

			Ratioleg->SetBorderSize(0);
			Ratioleg->SetTextFont(FontStyle);
			Ratioleg->SetTextSize(TextSize);
			Ratioleg->Draw();

//			delete RatioPlotCanvas;

			// -----------------------------------------------------------------------------------------------------------------------------------------

			// Double ratio studies
			// Ratio with respect to sector 1 ratio

			TString DoubleRatioCanvasName = "DoubleRatio_"+FSILabel[WhichFSIModel]+Nucleus+"_"+E+"_"+xBCut + Ereco; 

			TCanvas* DoubleRatioPlotCanvas = new TCanvas(DoubleRatioCanvasName,DoubleRatioCanvasName,205,34,1024,768);

			DoubleRatioPlotCanvas->SetBottomMargin(0.17);
			DoubleRatioPlotCanvas->SetLeftMargin(0.17);

			TLegend* DoubleRatioleg = new TLegend(0.2,0.7,0.5,0.85);
			DoubleRatioleg->SetNColumns(3);

			double DoubleRatiomax = -99.;
			double DoubleRatiomin = 1E12;

			std::vector< std::vector<double> > CVInBin; CVInBin.clear();
			int NBins = RatioPlots[0][0]->GetXaxis()->GetNbins();
			CVInBin.resize(NBins);

			// Loop over the 6 sector plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot++) {

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot] = (TH1D*)( RatioPlots[WhichFSIModel-1][WhichPlot]->Clone() );
				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->Divide( RatioPlots[WhichFSIModel-1][0]);

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetYaxis()->SetTitle("Double Ratio To 1st Sector");

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->SetTitle(FSILabel[0] + "/" + FSILabel[WhichFSIModel] + ", " + LabelsOfSamples+LabelE);

				// ---------------------------------------------------------------------------------------------------

				for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
	
					CVInBin[WhichBin].push_back(DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetBinContent(WhichBin+1) );

				}

				// ---------------------------------------------------------------------------------------------------

				// Max, min

				double localDoubleRatiomax = DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetMaximum();
				double localDoubleRatiomin = DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetMinimum();

				if (localDoubleRatiomax > DoubleRatiomax) { DoubleRatiomax = localDoubleRatiomax; }
				if (localDoubleRatiomin < DoubleRatiomin) { DoubleRatiomin = localDoubleRatiomin; }
				double DoubleRatioExtraHeight = 0.1;
				double DoubleRatioPosNegMin = TMath::Min(-0.5,DoubleRatiomin);
				double DoubleRatioPosNegMax = TMath::Min(3.,DoubleRatiomax);
				DoubleRatioPlots[0][0]->GetYaxis()->SetRangeUser( (1+DoubleRatioExtraHeight)*DoubleRatioPosNegMin, (1+DoubleRatioExtraHeight)*DoubleRatioPosNegMax );

				// ---------------------------------------------------------------------------------------------------

				DoubleRatioPlotCanvas->cd();
				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->Draw("e same");
				DoubleRatioPlots[0][WhichPlot]->Draw("e same");

				DoubleRatioleg->AddEntry(DoubleRatioPlots[WhichFSIModel-1][WhichPlot],SectorLabel[WhichPlot], "lep");

			} // End of the loop over the 6 sector plots

			DoubleRatioleg->SetBorderSize(0);
			DoubleRatioleg->SetTextFont(FontStyle);
			DoubleRatioleg->SetTextSize(TextSize);
			DoubleRatioleg->Draw();

			for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {

				std::vector<double> ArrayInsBin = CVInBin[WhichBin];

				double mean = computeMean(ArrayInsBin); 
				double std = computeStd(mean,ArrayInsBin); 										

			}

//			delete DoubleRatioPlotCanvas;

			// ---------------------------------------------------------------------------------------------------

			// Now on a bin-by-bin basis, we want to calculate the RMS 



		} // End of the loop over the simulation sets

	} // End of the case where we have more than one samples
	  // Aka we have carried out the ratio & double ratio study

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program
