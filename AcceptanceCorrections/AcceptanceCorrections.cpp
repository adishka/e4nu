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

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

void AcceptanceCorrections() {

	// ------------------------------------------------------------------------

	GlobalSettings();
	const std::vector<int> LocalDataSetColors{1,610,410,kRed+2,kBlue};
	double split = 0.1;

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus; 
	std::vector<TString> JustNucleus;
	std::vector<TString> E; 
	std::vector<double> DoubleE;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames;

	// ------------------------------------------------------------------------

	nucleus.push_back("12C"); JustNucleus.push_back("C");

	E.push_back("1_161"); LabelE.push_back(" @ E = 1.157 GeV"); DoubleE.push_back(1.161);	
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.257 GeV"); DoubleE.push_back(2.261);	

	xBCut.push_back("NoxBCut");

	// 0th plot is CV
	// 1st plot is true 1p0pi with smearing (S) / fiducials (F) / acceptance maps (A) / resolution (R) / thresholds (T)
	// 2nd plot is true 1p0pi without smearing (S) / fiducials (F) / acceptance maps (A) / resolution (R) but with thresholds (T)

	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_SixSectors"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("SuSav2_RadCorr_LFGM_Truth_WithFidAcc"); FSILabel.push_back("True 1p0pi W/");
	FSIModel.push_back("SuSav2_RadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("True 1p0pi W/O");

//	NameOfPlots.push_back("MissMomentum"); LabelOfPlots.push_back("P_{T} [GeV/c]"); OutputPlotNames.push_back("MissMomentum");
	NameOfPlots.push_back("epRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{cal} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");
//	NameOfPlots.push_back("eRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{cal} [GeV]"); OutputPlotNames.push_back("eRecoEnergy_slice_0");
//	NameOfPlots.push_back("h1_EQE_FullyInclusive"); LabelOfPlots.push_back("(e,e') E^{QE} [GeV]");  OutputPlotNames.push_back("FullyInclusiveeRecoEnergy_slice_0");

	// ------------------------------------------------------------------------

	std::vector<TH1D*> Plots;
	std::vector<TH1D*> BreakDownPlots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				// Loop over the plots

				double max = -99.;
				double min = 1E12;
				double height = 1.05;

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					TString PlotCanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* PlotCanvas = new TCanvas(PlotCanvasName,PlotCanvasName,205,34,1024,768);

					PlotCanvas->SetLeftMargin(0.15);
					PlotCanvas->SetBottomMargin(0.15);

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					TLegend* legGenie = new TLegend(0.1,0.9,0.9,0.99);					
					legGenie->SetNColumns(3);

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(LocalDataSetColors[WhichFSIModel]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);
						Plots[WhichFSIModel]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]);

						// ----------------------------------------------------------------------------------

						// Use the universal e4v function that 
						// scales by all the necessary scaling factors
						// divides by the bin width to obtain normalized yields / absolute cross sections
						// uses the relevant binning
						// gets the relevant x axis range
						// If data sample: 
						//                 apply systematics due to rotations et al
						//                 apply acceptance systematics using sector-by -sector uncertainties

						UniversalE4vFunction(Plots[WhichFSIModel],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot]);

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();
						Plots[0]->GetXaxis()->SetTitle(XLabel);

						// --------------------------------------------------------------------------------------------------

						// Drawing The Plots

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 
						
							if (FSILabel[WhichFSIModel] =="G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines

							if (string(FSILabel[0]).find("Data") != std::string::npos) { Plots[0]->Draw("e same"); } 

						}

						legGenie->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel]);

					} // End of the loop over the FSI Models 

					// -----------------------------------------------------------------------------------

					legGenie->SetBorderSize(0);
					legGenie->SetTextFont(FontStyle);

					PlotCanvas->cd();
					legGenie->Draw(); 

					// ---------------------------------------------------------------------------------------------------

					// Let's take the ratios to account for

					// 1st ratio: Correct for bkg subtraction
					// 2nd ratio: Correct for proton & electron acceptance
					// 3rd ratio: Overall correction factor

					// ---------------------------------------------------------------------------------------------------

					// 1st ratio: Correct for bkg subtraction

					TString BkgCorrPlotCanvasName = "BkgCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* BkgCorrPlotCanvas = new TCanvas(BkgCorrPlotCanvasName,BkgCorrPlotCanvasName,205,34,1024,768);

					BkgCorrPlotCanvas->SetLeftMargin(0.15);
					BkgCorrPlotCanvas->SetBottomMargin(0.15);	

					TH1D* RecoClone = (TH1D*)Plots[0]->Clone();	
					RecoClone->Divide(Plots[1]);			

					BkgCorrPlotCanvas->cd();

					RecoClone->SetTitle("Background Correction");

					RecoClone->GetYaxis()->SetRangeUser( 0,1 );
					RecoClone->GetYaxis()->SetTitle("Reco / True 1p0pi W/" );

					RecoClone->Draw();

					// ---------------------------------------------------------------------------------------------------

					// 2nd ratio: Correct for proton & electron acceptance

					TString ThresCorrPlotCanvasName = "ThresCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* ThresCorrPlotCanvas = new TCanvas(ThresCorrPlotCanvasName,ThresCorrPlotCanvasName,205,34,1024,768);

					ThresCorrPlotCanvas->SetLeftMargin(0.15);
					ThresCorrPlotCanvas->SetBottomMargin(0.15);	

					TH1D* TrueClone = (TH1D*)Plots[1]->Clone();	
					TrueClone->Divide(Plots[2]);			

					ThresCorrPlotCanvas->cd();

					TrueClone->SetTitle("Threshold Correction");
					TrueClone->GetYaxis()->SetRangeUser( 0,1 );
					TrueClone->GetYaxis()->SetTitle("True 1p0pi W/ / True 1p0pi W/O" );

					TrueClone->Draw();

					// ---------------------------------------------------------------------------------------------------

					// 3rd ratio: Overall correction factor

					TString OverallCorrPlotCanvasName = "OverallCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* OverallCorrPlotCanvas = new TCanvas(OverallCorrPlotCanvasName,OverallCorrPlotCanvasName,205,34,1024,768);

					OverallCorrPlotCanvas->SetLeftMargin(0.15);
					OverallCorrPlotCanvas->SetBottomMargin(0.15);	

					TH1D* OverallClone = (TH1D*)Plots[0]->Clone();	
					OverallClone->Divide(Plots[2]);			

					OverallCorrPlotCanvas->cd();

					OverallClone->SetTitle("Acceptance Correction");
					OverallClone->GetYaxis()->SetRangeUser( 0,1 );
					OverallClone->GetYaxis()->SetTitle("Reco / True 1p0pi W/O" );

					OverallClone->Draw();

					// ------------------------------------------------------------------------------


				} // End of the loop over the plots

				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
