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
#include <TGraph.h>

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
		leg->SetFillStyle(0);

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

			ApplyRebinning(Plots[WhichFSIModel][WhichPlot],Energy,Ereco);

			Plots[WhichFSIModel][WhichPlot]->GetXaxis()->SetNdivisions(7);

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

			ApplyRange(Plots[WhichFSIModel][WhichPlot],Energy,Ereco);

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

		//delete PlotCanvas;


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

			RatioPlotCanvas->SetGridx();
			RatioPlotCanvas->SetGridy();

			TLegend* Ratioleg = new TLegend(0.2,0.7,0.5,0.85);
			Ratioleg->SetNColumns(3);
			Ratioleg->SetFillStyle(0);

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
				double RatioPosNegMin = TMath::Min(0.,Ratiomin);
				double RatioPosNegMax = TMath::Min(2.,Ratiomax);
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

			//delete RatioPlotCanvas;

			// -----------------------------------------------------------------------------------------------------------------------------------------

			// Double ratio studies
			// Ratio with respect to sector 1 ratio

			TString DoubleRatioCanvasName = "DoubleRatio_"+FSILabel[WhichFSIModel]+Nucleus+"_"+E+"_"+xBCut + Ereco; 

			TCanvas* DoubleRatioPlotCanvas = new TCanvas(DoubleRatioCanvasName,DoubleRatioCanvasName,205,34,1024,768);

			DoubleRatioPlotCanvas->SetGridx();
			DoubleRatioPlotCanvas->SetGridy();

			DoubleRatioPlotCanvas->SetBottomMargin(0.17);
			DoubleRatioPlotCanvas->SetLeftMargin(0.17);

			TLegend* DoubleRatioleg = new TLegend(0.2,0.7,0.5,0.85);
			DoubleRatioleg->SetNColumns(3);
			DoubleRatioleg->SetFillStyle(0);

			double DoubleRatiomax = -99.;
			double DoubleRatiomin = 1E12;

			std::vector< std::vector<double> > CVInBin; CVInBin.clear();
			std::vector< std::vector<double> > InverseErrorSqInBin; InverseErrorSqInBin.clear();
			std::vector< std::vector<double> > ErrorInBin; ErrorInBin.clear();
			int NBins = RatioPlots[0][0]->GetXaxis()->GetNbins();
			CVInBin.resize(NBins);
			InverseErrorSqInBin.resize(NBins);
			ErrorInBin.resize(NBins);

			// Loop over the 6 sector plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot++) {

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot] = (TH1D*)( RatioPlots[WhichFSIModel-1][WhichPlot]->Clone() );
				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->Divide( RatioPlots[WhichFSIModel-1][0]);

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetYaxis()->SetTitle("Double Ratio To 1st Sector");

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->SetTitle(FSILabel[0] + "/" + FSILabel[WhichFSIModel] + ", " + LabelsOfSamples+LabelE);

				// ---------------------------------------------------------------------------------------------------

				for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {
	
					CVInBin[WhichBin].push_back(DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetBinContent(WhichBin+1) );
					InverseErrorSqInBin[WhichBin].push_back(1. / TMath::Power(DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetBinError(WhichBin+1),2.) );
					ErrorInBin[WhichBin].push_back( DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetBinError(WhichBin+1) );

				}

				// ---------------------------------------------------------------------------------------------------

				// Max, min

				double localDoubleRatiomax = DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetMaximum();
				double localDoubleRatiomin = DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetMinimum();

				if (localDoubleRatiomax > DoubleRatiomax) { DoubleRatiomax = localDoubleRatiomax; }
				if (localDoubleRatiomin < DoubleRatiomin) { DoubleRatiomin = localDoubleRatiomin; }
				double DoubleRatioExtraHeight = 0.1;
				double DoubleRatioPosNegMin = TMath::Min(0.,DoubleRatiomin);
				double DoubleRatioPosNegMax = TMath::Min(2.,DoubleRatiomax);
				DoubleRatioPlots[0][0]->GetYaxis()->SetRangeUser( DoubleRatioPosNegMin, DoubleRatioPosNegMax );

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

			// ---------------------------------------------------------------------------------------------------

			// Now on a bin-by-bin basis, we want to calculate the RMS 

			//delete DoubleRatioPlotCanvas;

			double XaxisEntries[NBins];
			double WeightedStd[NBins];
			double UnweightedStd[NBins];
			double UnweightedDiff[NBins];

			double WeightedStdPercErr[NBins];
			double UnweightedStdPercErr[NBins];
			double UnweightedDiffPercErr[NBins];

			for (int WhichBin = 0; WhichBin < NBins; WhichBin++) {

				std::vector<double> ArrayCVInBin = CVInBin[WhichBin];
				std::vector<double> ArrayInverseErrorSqInBin = InverseErrorSqInBin[WhichBin];
				std::vector<double> ArrayErrorInBin = ErrorInBin[WhichBin];

				// error weighted std
				double mean = computeMean(ArrayCVInBin,ArrayInverseErrorSqInBin); 
				double std = computeStd(mean,ArrayCVInBin,ArrayInverseErrorSqInBin); 
				//cout << "Bin Center = " << DoubleRatioPlots[0][0]->GetBinCenter(WhichBin+1) << " mean = " << mean << " std = " << std << endl;

				// Larry
				// We can calculate an unweighted variance from our six values and then 
				// subtract the variance expected from the statsitical uncertainties [Sum[(x_i - x_bar)^2] - Sum[(error_i)^2]	

				double unweightedmean = computeMean(ArrayCVInBin); 
				double unweightedstd = computeStd(unweightedmean,ArrayCVInBin); 
				double sumstatsqerr = SumSqDiffInBin(ArrayErrorInBin);
				double sumCVsqerr = SumSqDiffInBin(ArrayCVInBin,unweightedmean);
				double diff = sumCVsqerr - sumstatsqerr;
				//cout << "Bin Center = " << DoubleRatioPlots[0][0]->GetBinCenter(WhichBin+1) << " diff = " << diff << endl;

				XaxisEntries[WhichBin] = DoubleRatioPlots[0][0]->GetBinCenter(WhichBin+1);
				WeightedStd[WhichBin] = std;
				UnweightedStd[WhichBin] = unweightedstd;
				UnweightedDiff[WhichBin] = TMath::Sqrt( TMath::Abs(diff)/(double)(NPlots-1) );

				if (mean != 0) {
				
					WeightedStdPercErr[WhichBin] = std / mean * 100.;

				} else {

					WeightedStdPercErr[WhichBin] = -99.;

				}

				if (unweightedmean != 0) {

					UnweightedStdPercErr[WhichBin] = unweightedstd / unweightedmean * 100.;
					UnweightedDiffPercErr[WhichBin] = UnweightedDiff[WhichBin] / unweightedmean * 100.;

				} else {

					UnweightedStdPercErr[WhichBin] = -99.;
					UnweightedDiffPercErr[WhichBin] = -99.;					

				}

			}

			TString RMSCanvasName = "RMS_"+FSILabel[WhichFSIModel]+Nucleus+"_"+E+"_"+xBCut + Ereco; 
			TCanvas* RMSCanvas = new TCanvas(RMSCanvasName,RMSCanvasName,205,34,1024,768);

			RMSCanvas->SetBottomMargin(0.17);
			RMSCanvas->SetLeftMargin(0.17);

			RMSCanvas->SetGridx();
			RMSCanvas->SetGridy();

			TLegend* RMSleg = new TLegend(0.2,0.7,0.5,0.85);
			RMSleg->SetNColumns(1);
			RMSleg->SetFillStyle(0);

			// ----------------------------------------------------------------		

			TGraph* WeightedGraph = new TGraph(NBins,XaxisEntries,WeightedStd);

			PrettyGraph(WeightedGraph);

			WeightedGraph->SetLineColor(kBlack);
			WeightedGraph->SetMarkerColor(kBlack);
			WeightedGraph->SetMarkerStyle(20);
			WeightedGraph->SetMarkerSize(2.);

			WeightedGraph->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples+LabelE);

			WeightedGraph->GetXaxis()->SetTitle(LabelOfPlots);
			WeightedGraph->GetYaxis()->SetRangeUser(0,2.5);
			WeightedGraph->GetYaxis()->SetTitle();
			WeightedGraph->Draw("AP");

			RMSleg->AddEntry(WeightedGraph,"Weighted Std");

			// ----------------------------------------------------------------

			TGraph* UnweightedStdGraph = new TGraph(NBins,XaxisEntries,UnweightedStd);

			PrettyGraph(UnweightedStdGraph);

			UnweightedStdGraph->SetLineColor(kRed);
			UnweightedStdGraph->SetMarkerColor(kRed);
			UnweightedStdGraph->SetMarkerStyle(20);
			UnweightedStdGraph->SetMarkerSize(2.);
			UnweightedStdGraph->GetYaxis()->SetTitle();
			UnweightedStdGraph->Draw("P");

			RMSleg->AddEntry(UnweightedStdGraph,"Unweighted Std");

			// ----------------------------------------------------------------

			TGraph* UnweightedDiffGraph = new TGraph(NBins,XaxisEntries,UnweightedDiff);

			PrettyGraph(UnweightedDiffGraph);

			UnweightedDiffGraph->SetLineColor(kBlue);
			UnweightedDiffGraph->SetMarkerColor(kBlue);
			UnweightedDiffGraph->SetMarkerStyle(20);
			UnweightedDiffGraph->SetMarkerSize(2.);
			UnweightedDiffGraph->GetYaxis()->SetTitle();
			UnweightedDiffGraph->Draw("P");

			RMSleg->AddEntry(UnweightedDiffGraph,"Unweighted Diff");

			// ----------------------------------------------------------------

			RMSleg->SetTextFont(FontStyle);
			RMSleg->SetTextSize(TextSize);
			RMSleg->SetBorderSize(0);
			RMSleg->Draw();

			delete RMSCanvas;

			// ----------------------------------------------------------------
			// ----------------------------------------------------------------

			// Percentage Error

			TString PercErrRMSCanvasName = "PercErrRMS_"+FSILabel[WhichFSIModel]+Nucleus+"_"+E+"_"+xBCut + Ereco; 
			TCanvas* PercErrRMSCanvas = new TCanvas(PercErrRMSCanvasName,PercErrRMSCanvasName,205,34,1024,768);

			PercErrRMSCanvas->SetBottomMargin(0.17);
			PercErrRMSCanvas->SetLeftMargin(0.17);
			PercErrRMSCanvas->SetGridx();
			PercErrRMSCanvas->SetGridy();

			TLegend* PercErrRMSleg = new TLegend(0.2,0.65,0.5,0.85);
			PercErrRMSleg->SetNColumns(1);
			PercErrRMSleg->SetFillStyle(0);

			// ----------------------------------------------------------------		

			TGraph* PercErrWeightedGraph = new TGraph(NBins,XaxisEntries,WeightedStdPercErr);

			PrettyGraph(PercErrWeightedGraph);

			PercErrWeightedGraph->SetLineColor(kBlack);
			PercErrWeightedGraph->SetMarkerColor(kBlack);
			PercErrWeightedGraph->SetMarkerStyle(20);
			PercErrWeightedGraph->SetMarkerSize(2.);

			PercErrWeightedGraph->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples+LabelE);

			ApplyRange(PercErrWeightedGraph,Energy,Ereco);
			PercErrWeightedGraph->GetXaxis()->SetTitle(LabelOfPlots);
			PercErrWeightedGraph->GetYaxis()->SetRangeUser(0.,35);
			PercErrWeightedGraph->GetYaxis()->SetTitle("Percentage Error");
			PercErrWeightedGraph->GetYaxis()->SetNdivisions(10);
			PercErrWeightedGraph->Draw("AP");

			PercErrRMSleg->AddEntry(WeightedGraph,"Weighted Std");

			// ----------------------------------------------------------------

			TGraph* PercErrUnweightedStdGraph = new TGraph(NBins,XaxisEntries,UnweightedStdPercErr);

			PrettyGraph(PercErrUnweightedStdGraph);

			PercErrUnweightedStdGraph->SetLineColor(kRed);
			PercErrUnweightedStdGraph->SetMarkerColor(kRed);
			PercErrUnweightedStdGraph->SetMarkerStyle(20);
			PercErrUnweightedStdGraph->SetMarkerSize(2.);
			PercErrUnweightedStdGraph->GetYaxis()->SetTitle();
			PercErrUnweightedStdGraph->Draw("P");

			PercErrRMSleg->AddEntry(PercErrUnweightedStdGraph,"Unweighted Std");

			// ----------------------------------------------------------------

			TGraph* PercErrUnweightedDiffGraph = new TGraph(NBins,XaxisEntries,UnweightedDiffPercErr);

			PrettyGraph(PercErrUnweightedDiffGraph);

			PercErrUnweightedDiffGraph->SetLineColor(kBlue);
			PercErrUnweightedDiffGraph->SetMarkerColor(kBlue);
			PercErrUnweightedDiffGraph->SetMarkerStyle(20);
			PercErrUnweightedDiffGraph->SetMarkerSize(2.);
			PercErrUnweightedDiffGraph->GetYaxis()->SetTitle();
			PercErrUnweightedDiffGraph->Draw("P");

			PercErrRMSleg->AddEntry(PercErrUnweightedDiffGraph,"Unweighted Diff");

			// ----------------------------------------------------------------

			PercErrRMSleg->SetTextFont(FontStyle);
			PercErrRMSleg->SetTextSize(TextSize);
			PercErrRMSleg->SetBorderSize(0);
			PercErrRMSleg->Draw();

			//delete PercErrRMSCanvas;

		} // End of the loop over the simulation sets

	} // End of the case where we have more than one samples
	  // Aka we have carried out the ratio & double ratio study

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program
