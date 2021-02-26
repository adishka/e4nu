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
	TGaxis::SetMaxDigits(3);

	const std::vector<int> LocalDataSetColors{1,610,410,kRed+2,kBlue};
	double split = 0.1;

	TString Label = "SuSav2";
	//TString Label = "hA2018_Final";

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus; 
	std::vector<TString> JustNucleus;
	std::vector<TString> E; 
	std::vector<double> DoubleE;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> LegendLabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames;

	// ------------------------------------------------------------------------

	nucleus.push_back("4He"); JustNucleus.push_back("He");
//	nucleus.push_back("12C"); JustNucleus.push_back("C");
//	nucleus.push_back("56Fe"); JustNucleus.push_back("Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.157 GeV"); DoubleE.push_back(1.161);	
	E.push_back("2_261"); LabelE.push_back(" @ E = 2.257 GeV"); DoubleE.push_back(2.261);	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.457 GeV"); DoubleE.push_back(4.461);	

	xBCut.push_back("NoxBCut");

	NameOfPlots.push_back("DeltaPhiT_Int_0"); LabelOfPlots.push_back("#delta#phi_{T} [deg]"); OutputPlotNames.push_back("DeltaPhiT");
	NameOfPlots.push_back("DeltaAlphaT_Int_0"); LabelOfPlots.push_back("#delta#alpha_{T} [deg]"); OutputPlotNames.push_back("DeltaAlphaT");
	NameOfPlots.push_back("MissMomentum"); LabelOfPlots.push_back("P_{T} [GeV/c]"); OutputPlotNames.push_back("MissMomentum");
	NameOfPlots.push_back("epRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{cal} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");
////	NameOfPlots.push_back("eRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e')_{1p0#pi} E^{QE} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");
	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); OutputPlotNames.push_back("eRecoEnergy_slice_0");
////	NameOfPlots.push_back("h1_EQE_FullyInclusive"); LabelOfPlots.push_back("(e,e') E^{QE} [GeV]");  OutputPlotNames.push_back("FullyInclusiveeRecoEnergy_slice_0");

	// 0th plot is CV
	// 1st plot is true 1p0pi with smearing (S) / fiducials (F) / acceptance maps (A) / resolution (R) / thresholds (T)
	// 2nd plot is true 1p0pi without radiation, without smearing (S) / fiducials (F) / acceptance maps (A) / resolution (R) but with thresholds (T)

//	FSIModel.push_back(Label+"_RadCorr_LFGM_XSec"); FSILabel.push_back("Reco");

	if (Label == "SuSav2") {

//		FSIModel.push_back(Label+"_RadCorr_LFGM"); FSILabel.push_back("Reco");
//		FSIModel.push_back(Label+"_RadCorr_LFGM_Truth_WithFidAcc"); FSILabel.push_back("TrueWithFid");

//		FSIModel.push_back(Label+"_RadCorr_LFGM_UpdatedSchwinger"); FSILabel.push_back("Reco");
//		FSIModel.push_back(Label+"_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"); FSILabel.push_back("TrueWithFid");
//		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithoutFidAcc_Offset"); FSILabel.push_back("True");

		FSIModel.push_back(Label+"_NoRadCorr_LFGM"); FSILabel.push_back("Reco"); LegendLabel.push_back("e4v Reco");
		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithFidAcc"); FSILabel.push_back("TrueWithFid"); LegendLabel.push_back("1p0#pi Reco");
		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithoutFidAcc_Smearing"); FSILabel.push_back("True"); LegendLabel.push_back("1p0#pi True");

	} else {

//		FSIModel.push_back(Label+"_RadCorr_LFGM_Offset"); FSILabel.push_back("Reco");
//		FSIModel.push_back(Label+"_RadCorr_LFGM_Truth_WithFidAcc_Offset"); FSILabel.push_back("TrueWithFid");
////		FSIModel.push_back(Label+"_RadCorr_LFGM_UpdatedSchwinger_Offset"); FSILabel.push_back("Reco");
////		FSIModel.push_back(Label+"_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger_Offset"); FSILabel.push_back("TrueWithFid");
//		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithoutFidAcc_Offset"); FSILabel.push_back("True");

		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Offset"); FSILabel.push_back("Reco"); LegendLabel.push_back("e4v Reco");
		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithFidAcc_Offset"); FSILabel.push_back("TrueWithFid"); LegendLabel.push_back("1p0#pi Reco");
		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithoutFidAcc_Smearing_Offset"); FSILabel.push_back("True"); LegendLabel.push_back("1p0#pi True");

	}

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

				double height = 1.05;

				TFile* StoreEfficiencyFile = TFile::Open("myFiles/Efficiency_"+Label+"_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+xBCut[WhichxBCut]+".root","recreate");

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					//if (NameOfPlots[WhichPlot] == "h_Erec_subtruct_piplpimi_noprot_3pi" && !(nucleus[WhichNucleus] == "12C" && E[WhichEnergy] == "1_161") ) 
					//	{ continue; }

					TString PlotCanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* PlotCanvas = new TCanvas(PlotCanvasName,PlotCanvasName,205,34,1024,768);

					PlotCanvas->SetLeftMargin(0.15);
					PlotCanvas->SetBottomMargin(0.19);

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					TLegend* legGenie = new TLegend(0.2,0.9,0.9,0.99);					
					legGenie->SetNColumns(3);

					// ---------------------------------------------------------------------------------------

					// Special treatment for the QE energy reconstruction

					if (NameOfPlots[WhichPlot] == "h_Erec_subtruct_piplpimi_noprot_3pi") {

						FSIModel[0] = Label+"_NoRadCorr_LFGM"; 
						FSIModel[1] = Label+"_NoRadCorr_LFGM_Truth0pi_WithFidAcc";
						FSIModel[2] = Label+"_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc_Smearing";


					}

					// Loop over the FSI Models

					double max = -99.;
					double min = 1E12;

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = GlobalPathToFiles + E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
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

//if ( E[WhichEnergy] == "1_161") { Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.8,1.22); }

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						//Plots[WhichFSIModel]->GetYaxis()->SetRangeUser(0.,height*max);
//						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();
						Plots[WhichFSIModel]->GetXaxis()->SetTitle(XLabel);
						Plots[0]->GetXaxis()->SetTitle(XLabel);

						// --------------------------------------------------------------------------------------------------

						StoreEfficiencyFile->cd();
						Plots[WhichFSIModel]->Write(Label+"_"+FSILabel[WhichFSIModel]+"_"+NameOfPlots[WhichPlot]);

						// --------------------------------------------------------------------------------------------------

						// Drawing The Plots

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 
						
							if (FSILabel[WhichFSIModel] =="G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
//							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							Plots[WhichFSIModel]->Draw("e hist same");  // draw them as histos

							Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);
							Plots[0]->Draw("e hist same");

						}

						legGenie->AddEntry(Plots[WhichFSIModel],LegendLabel[WhichFSIModel]);

					} // End of the loop over the FSI Models 

					//delete PlotCanvas;

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
					// 4th ratio: Inverse overall correction factor

					// ---------------------------------------------------------------------------------------------------

					// 1st ratio: Correct for bkg subtraction

					TString BkgCorrPlotCanvasName = "BkgCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* BkgCorrPlotCanvas = new TCanvas(BkgCorrPlotCanvasName,BkgCorrPlotCanvasName,205,34,1024,768);

					BkgCorrPlotCanvas->SetLeftMargin(0.15);
					BkgCorrPlotCanvas->SetBottomMargin(0.17);	

					TH1D* RecoClone = (TH1D*)Plots[0]->Clone();	
					RecoClone->Divide(Plots[1]);			

					BkgCorrPlotCanvas->cd();

					RecoClone->SetTitle("Background Correction");

					RecoClone->GetYaxis()->SetRangeUser( 0.8,1.5 );
					RecoClone->GetYaxis()->SetTitle("Reco / True 1p0pi W/" );

					RecoClone->Draw();
					delete BkgCorrPlotCanvas;

					// ---------------------------------------------------------------------------------------------------

					// 2nd ratio: Correct for proton & electron acceptance

					TString ThresCorrPlotCanvasName = "ThresCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* ThresCorrPlotCanvas = new TCanvas(ThresCorrPlotCanvasName,ThresCorrPlotCanvasName,205,34,1024,768);

					ThresCorrPlotCanvas->SetLeftMargin(0.15);
					ThresCorrPlotCanvas->SetBottomMargin(0.17);	

					TH1D* TrueClone = (TH1D*)Plots[1]->Clone();	
					TrueClone->Divide(Plots[2]);			

					ThresCorrPlotCanvas->cd();

					TrueClone->SetTitle("Truth Ratios");
					TrueClone->GetYaxis()->SetRangeUser( 0.,1. );
					TrueClone->GetYaxis()->SetTitle("True 1p0pi W/ / True 1p0pi W/O" );

					TrueClone->Draw();
					delete ThresCorrPlotCanvas;

					// ---------------------------------------------------------------------------------------------------

					// 3rd ratio: Overall correction factor

					TString OverallCorrPlotCanvasName = "OverallCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* OverallCorrPlotCanvas = new TCanvas(OverallCorrPlotCanvasName,OverallCorrPlotCanvasName,205,34,1024,768);

					OverallCorrPlotCanvas->SetLeftMargin(0.15);
					OverallCorrPlotCanvas->SetBottomMargin(0.17);	

//					TH1D* OverallClone = (TH1D*)Plots[0]->Clone(); // e4v reco machinery
					TH1D* OverallClone = (TH1D*)Plots[1]->Clone(); // true 1p0pi, with fiducials & acceptance maps	
					OverallClone->Divide(Plots[2]);

					OverallCorrPlotCanvas->cd();

					OverallClone->SetTitle("Acceptance Correction");
					OverallClone->GetYaxis()->SetRangeUser( 0.,1. );
					OverallClone->GetYaxis()->SetTitle("Reco / True 1p0pi W/O" );

					OverallClone->Draw();
					delete OverallCorrPlotCanvas;

					// ---------------------------------------------------------------------------------------------------

					// 4th ratio: Inverse InverseOverall correction factor

					TString InverseOverallCorrPlotCanvasName = "InverseOverallCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* InverseOverallCorrPlotCanvas = new TCanvas(InverseOverallCorrPlotCanvasName,InverseOverallCorrPlotCanvasName,205,34,1024,768);

					InverseOverallCorrPlotCanvas->SetLeftMargin(0.15);
					InverseOverallCorrPlotCanvas->SetBottomMargin(0.17);	

					TH1D* InverseOverallClone = (TH1D*)Plots[2]->Clone();	
					//InverseOverallClone->Divide(Plots[0]); // e4v reco machinery			
					InverseOverallClone->Divide(Plots[1]); // true 1p0pi, with fiducials & acceptance maps				

					InverseOverallCorrPlotCanvas->cd();

					InverseOverallClone->SetTitle("Inverse Acceptance Correction");
					InverseOverallClone->GetYaxis()->SetRangeUser( 0.,10. );
					InverseOverallClone->GetYaxis()->SetTitle("True 1p0pi W/O / Reco" );

					InverseOverallClone->Draw();
					//delete InverseOverallCorrPlotCanvas;

					// ------------------------------------------------------------------------------

					StoreEfficiencyFile->cd();
					RecoClone->Write(Label+"_"+"BkgCorrection_"+NameOfPlots[WhichPlot]);
					TrueClone->Write(Label+"_"+"FidCorrection_"+NameOfPlots[WhichPlot]);
					OverallClone->Write(Label+"_"+"AccCorrection_"+NameOfPlots[WhichPlot]);
					InverseOverallClone->Write(Label+"_"+"InverseAccCorrection_"+NameOfPlots[WhichPlot]);

					// ------------------------------------------------------------------------------

				} // End of the loop over the plots

				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
