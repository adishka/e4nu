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

void CombinedSectorDoubleRatio(TString Ereco) {

	// ------------------------------------------------------------------------

	GlobalSettings();

	TString E = "4_461";
	double Energy = 4.461;
	TString xBCut = "NoxBCut";
	TString LabelE = " @ E = 4.461 GeV";

	// ------------------------------------------------------------------------

	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> SectorLabel;  

	std::vector<TString> nucleus{"4He","12C","56Fe"};

//	FSIModel.push_back("Pinned_Data_Final_SixSectors"); FSILabel.push_back("Pinned Data");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_SixSectors"); FSILabel.push_back("SuSav2");
////	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_SixSectors"); FSILabel.push_back("G2018");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");

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
	int NNuclei = nucleus.size();

	TFile* Files[NFSIModels][NNuclei];
	TH1D* Plots[NFSIModels][NNuclei][NPlots];

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the Data / SuSav2 / G2018 files

	for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

		// ---------------------------------------------------------------------------------------

		TString CanvasName =  FSILabel[WhichFSIModel]+"_"+E+"_"+xBCut + "_" + Ereco;
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

		// Loop over the 3 nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
			Files[WhichFSIModel][WhichNucleus] = TFile::Open(FileName);

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				// ------------------------------------------------------------------------------------------------------------------

				if ( !(string(FSIModel[WhichFSIModel]).find("SixSectors") != std::string::npos) ) {

					if (Energy == 1.161 && (SectorLabel[WhichPlot] == "3rd" || SectorLabel[WhichPlot] == "5th") ) { continue; }
					if (Energy == 2.261 && (SectorLabel[WhichPlot] == "3rd" || SectorLabel[WhichPlot] == "4th" || SectorLabel[WhichPlot] == "5th") ) { continue; }

				}

				// ------------------------------------------------------------------------------------------------------------------

				// Grab the relevant plot

				Plots[WhichFSIModel][WhichNucleus][WhichPlot] = (TH1D*)( Files[WhichFSIModel][WhichNucleus]->Get( NameOfPlots+ToStringInt(WhichPlot) ) );

				// -------------------------------------------------------------------------------------------------------------------

				// Make the plot pretty

				PrettyDoubleXSecPlot(Plots[WhichFSIModel][WhichNucleus][WhichPlot]);
				Plots[WhichFSIModel][WhichNucleus][WhichPlot]->SetLineColor(SectorColors[WhichPlot]);
				Plots[WhichFSIModel][WhichNucleus][WhichPlot]->SetTitle(FSILabel[WhichFSIModel] + " " + LabelE);
				Plots[WhichFSIModel][WhichNucleus][WhichPlot]->GetXaxis()->SetTitle(LabelOfPlots);

				// --------------------------------------------------------------------------------------

				// Use the universal e4v function that 
				// scales by all the necessary scaling factors
				// divides by the bin width to obtain normalized yields / absolute cross sections
				// uses the relevant binning
				// gets the relevant x axis range
				// If data sample: 
				//                 apply systematics due to rotations et al
				//                 apply acceptance systematics using sector-by -sector uncertainties

				for (int i = 0; i < 2; i++) { Plots[WhichFSIModel][WhichNucleus][WhichPlot]->Rebin(); }

				UniversalE4vFunction(Plots[WhichFSIModel][WhichNucleus][WhichPlot],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E,Ereco);

				Plots[WhichFSIModel][WhichNucleus][WhichPlot]->GetXaxis()->SetNdivisions(7);

				// ---------------------------------------------------------------------------------------------------

				// Max, min

				double localmax = Plots[WhichFSIModel][WhichNucleus][WhichPlot]->GetMaximum();
				double localmin = Plots[WhichFSIModel][WhichNucleus][WhichPlot]->GetMinimum();

				if (localmax > max) { max = localmax; }
				if (localmin < min) { min = localmin; }
				double ExtraHeight = 0.1;
				double PosNegMin = TMath::Min(0.,min);
				Plots[WhichFSIModel][WhichNucleus][0]->GetYaxis()->SetRangeUser( (1+ExtraHeight)*PosNegMin, (1+ExtraHeight)*max );

				// --------------------------------------------------------------------------------------------------

				ApplyRange(Plots[WhichFSIModel][WhichNucleus][WhichPlot],Energy,Ereco);

				if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

					if (WhichNucleus == NNuclei-1) {

						Plots[WhichFSIModel][WhichNucleus][WhichPlot]->SetMarkerStyle(MarkerStyle); 
						Plots[WhichFSIModel][WhichNucleus][WhichPlot]->SetMarkerSize(MarkerSize); 
						Plots[WhichFSIModel][WhichNucleus][WhichPlot]->SetMarkerColor(SectorColors[WhichPlot]); 

						gStyle->SetErrorX(0); // Removing the horizontal errors
						Plots[WhichFSIModel][WhichNucleus][WhichPlot]->Draw("e same"); 
						Plots[WhichFSIModel][WhichNucleus][0]->Draw("e same"); 
						leg->AddEntry(Plots[WhichFSIModel][WhichNucleus][WhichPlot],SectorLabel[WhichPlot], "lep");

					} else {

						Plots[WhichFSIModel][0][WhichPlot]->Add(Plots[WhichFSIModel][WhichNucleus][WhichPlot]);

					}

				} else { 

					if (WhichNucleus == NNuclei-1) {

						Plots[WhichFSIModel][WhichNucleus][WhichPlot]->Draw("C hist same");  // draw them as lines
						Plots[WhichFSIModel][WhichNucleus][0]->Draw("C hist same"); 
						leg->AddEntry(Plots[WhichFSIModel][WhichNucleus][WhichPlot],SectorLabel[WhichPlot], "l");

					} else {

						Plots[WhichFSIModel][0][WhichPlot]->Add(Plots[WhichFSIModel][WhichNucleus][WhichPlot]);

					}

				}

				// ---------------------------------------------------------------------------------------------------
				// --------------------------------------------------------------------------------------------------

			} // End of the loop over the plots

		} // End of the loop over the 3 nuclei

		// -----------------------------------------------------------------------------------------------------------------------------------------

		leg->SetBorderSize(0);
		leg->SetTextFont(FontStyle);
		leg->SetTextSize(TextSize);
		leg->Draw();

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TString ext = "";
		if ( xBCut == "xBCut" ) { ext = "xB_"; } 

//		PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut+"/"+version+"ThreeNuclei/"+E+"/"+ext+"ThreeNuclei_"+E+"_" +OutputPlotNames+".pdf");

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

			TString RatioCanvasName = "Ratio_"+FSILabel[WhichFSIModel]+"_"+E+"_"+xBCut + Ereco; 
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

			// ------------------------------------------------------------------------------------------------------------------

			if ( !(string(FSIModel[WhichFSIModel]).find("SixSectors") != std::string::npos) ) {

				if (Energy == 1.161 && (SectorLabel[WhichPlot] == "3rd" || SectorLabel[WhichPlot] == "5th") ) { continue; }
				if (Energy == 2.261 && (SectorLabel[WhichPlot] == "3rd" || SectorLabel[WhichPlot] == "4th" || SectorLabel[WhichPlot] == "5th") ) { continue; }

			}

			// ------------------------------------------------------------------------------------------------------------------

				RatioPlots[WhichFSIModel-1][WhichPlot] = (TH1D*)( Plots[0][NNuclei-1][WhichPlot]->Clone() );
				RatioPlots[WhichFSIModel-1][WhichPlot]->Divide(Plots[WhichFSIModel][NNuclei-1][WhichPlot]);

				RatioPlots[WhichFSIModel-1][WhichPlot]->GetYaxis()->SetTitle("Ratio");

				RatioPlots[WhichFSIModel-1][WhichPlot]->SetTitle(FSILabel[0] + "/" + FSILabel[WhichFSIModel] + " " +LabelE);

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

			TString DoubleRatioCanvasName = "DoubleRatio_"+FSILabel[WhichFSIModel]+"_"+E+"_"+xBCut + Ereco; 

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

			TFile* f = new TFile("myFiles/"+RatioCanvasName+".root","recreate");

			// Loop over the 6 sector plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot++) {

			// ------------------------------------------------------------------------------------------------------------------

			if ( !(string(FSIModel[WhichFSIModel]).find("SixSectors") != std::string::npos) ) {

				if (Energy == 1.161 && (SectorLabel[WhichPlot] == "3rd" || SectorLabel[WhichPlot] == "5th") ) { continue; }
				if (Energy == 2.261 && (SectorLabel[WhichPlot] == "3rd" || SectorLabel[WhichPlot] == "4th" || SectorLabel[WhichPlot] == "5th") ) { continue; }

			}

			// ------------------------------------------------------------------------------------------------------------------

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot] = (TH1D*)( RatioPlots[WhichFSIModel-1][WhichPlot]->Clone() );
				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->Divide( RatioPlots[WhichFSIModel-1][0]);

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->GetYaxis()->SetTitle("Double Ratio To 1st Sector");

				DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->SetTitle(FSILabel[0] + "/" + FSILabel[WhichFSIModel] + " " + LabelE);

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

f->cd();
DoubleRatioPlots[WhichFSIModel-1][WhichPlot]->Write();

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
				// subtract the variance expected from the statsitical uncertainties Sqrt([Sum[(x_i - x_bar)^2] - Sum[(error_i)^2]/5)	

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

			TString RMSCanvasName = "RMS_"+FSILabel[WhichFSIModel]+"_"+E+"_"+xBCut + Ereco; 
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

			WeightedGraph->SetTitle(FSILabel[WhichFSIModel] + " " + LabelE);

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

			TString PercErrRMSCanvasName = "PercErrRMS_"+FSILabel[WhichFSIModel]+"_"+E+"_"+xBCut + Ereco; 
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

			PercErrWeightedGraph->SetTitle(FSILabel[WhichFSIModel] + " " + LabelE);

			ApplyRange(PercErrWeightedGraph,E,Ereco);
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
