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

void RadiationCorrections() {

	// ------------------------------------------------------------------------

	GlobalSettings();
	TGaxis::SetMaxDigits(3);

	const std::vector<int> LocalDataSetColors{1,610,410,kRed+2,kBlue};
	double split = 0.1;

	TString Label = "SuSav2";
	//TString Label = "hA2018_Final"; // NOT to be used, G2018 is problematic with radiation

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

//	nucleus.push_back("4He"); JustNucleus.push_back("He");
//	nucleus.push_back("12C"); JustNucleus.push_back("C");
	nucleus.push_back("56Fe"); JustNucleus.push_back("Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.157 GeV"); DoubleE.push_back(1.161);	
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.257 GeV"); DoubleE.push_back(2.261);	
	E.push_back("4_461"); LabelE.push_back(" @ E = 4.457 GeV"); DoubleE.push_back(4.461);	

	xBCut.push_back("NoxBCut");

	NameOfPlots.push_back("DeltaPhiT_Int_0"); LabelOfPlots.push_back("#delta#phi_{T} [deg]"); OutputPlotNames.push_back("DeltaPhiT");
	NameOfPlots.push_back("DeltaAlphaT_Int_0"); LabelOfPlots.push_back("#delta#alpha_{T} [deg]"); OutputPlotNames.push_back("DeltaAlphaT");
	NameOfPlots.push_back("MissMomentum"); LabelOfPlots.push_back("P_{T} [GeV/c]"); OutputPlotNames.push_back("MissMomentum");
	NameOfPlots.push_back("epRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{cal} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");
////	NameOfPlots.push_back("eRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e')_{1p0#pi} E^{QE} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");
	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); OutputPlotNames.push_back("eRecoEnergy_slice_0");
////	NameOfPlots.push_back("h1_EQE_FullyInclusive"); LabelOfPlots.push_back("(e,e') E^{QE} [GeV]");  OutputPlotNames.push_back("FullyInclusiveeRecoEnergy_slice_0");

	// 0th plot is Rad_UpdatedSchwinger SuSav2
	// 1st plot is NoRad SuSav2

//	FSIModel.push_back(Label+"_RadCorr_LFGM_XSec"); FSILabel.push_back("Reco");

	if (Label == "SuSav2") {

		FSIModel.push_back(Label+"_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"); FSILabel.push_back("Rad"); LegendLabel.push_back("Rad");
		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithFidAcc"); FSILabel.push_back("NoRad"); LegendLabel.push_back("NoRad");

	} else {

		// Not to be used
		// G2018 Rad is problematic

		FSIModel.push_back(Label+"_RadCorr_LFGM_Truth_WithFidAcc_UpdatedSchwinger"); FSILabel.push_back("Rad");  LegendLabel.push_back("Rad");
		FSIModel.push_back(Label+"_NoRadCorr_LFGM_Truth_WithFidAcc"); FSILabel.push_back("NoRad"); LegendLabel.push_back("NoRad");

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

				TFile* StoreEfficiencyFile = TFile::Open("myFiles/Efficiency_"+Label+"_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+xBCut[WhichxBCut]+".root","recreate");

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					TString PlotCanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* PlotCanvas = new TCanvas(PlotCanvasName,PlotCanvasName,205,34,1024,768);

					PlotCanvas->SetLeftMargin(0.15);
					PlotCanvas->SetBottomMargin(0.19);
					//PlotCanvas->SetLogy();

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					TLegend* legGenie = new TLegend(0.3,0.9,0.9,0.99);					
					legGenie->SetNColumns(3);

					// ---------------------------------------------------------------------------------------

					// Special treatment for the QE energy reconstruction

					if (NameOfPlots[WhichPlot] == "h_Erec_subtruct_piplpimi_noprot_3pi") {

						FSIModel[0] = Label+"_RadCorr_LFGM_Truth0pi_WithFidAcc_UpdatedSchwinger";
						FSIModel[1] = Label+"_NoRadCorr_LFGM_Truth0pi_WithFidAcc";

					}

					double max = -99.;
					double min = 1E12;
					double height = 1.05;

					// Loop over the FSI Models

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

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						Plots[WhichFSIModel]->GetYaxis()->SetRangeUser(0.0,height*max);

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
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 
						
							if (FSILabel[WhichFSIModel] =="G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
//							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							Plots[WhichFSIModel]->Draw("e hist same");  // draw them as lines

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

					// Radiation correction factor

					TString RadiationCorrPlotCanvasName = "RadiationCorr_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* RadiationCorrPlotCanvas = new TCanvas(RadiationCorrPlotCanvasName,RadiationCorrPlotCanvasName,205,34,1024,768);

					RadiationCorrPlotCanvas->SetLeftMargin(0.15);
					RadiationCorrPlotCanvas->SetBottomMargin(0.17);	

					TH1D* RadiationClone = (TH1D*)Plots[1]->Clone(); // 1: NoRad 1p0pi	
					RadiationClone->Divide(Plots[0]); // 0: Rad 1p0pi UpdatedSchwinger				

					RadiationCorrPlotCanvas->cd();

					RadiationClone->SetTitle("Radiation Correction");
					RadiationClone->GetYaxis()->SetRangeUser( 0.5,1.5);
					RadiationClone->GetYaxis()->SetTitle("NoRad / Rad");

					RadiationClone->Draw();
					//delete RadiationCorrPlotCanvas;

					// ------------------------------------------------------------------------------

					StoreEfficiencyFile->cd();
					RadiationClone->Write(Label+"_"+"RadiationCorrection_"+NameOfPlots[WhichPlot]);

					// ------------------------------------------------------------------------------

				} // End of the loop over the plots

				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
