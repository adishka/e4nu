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

void UncertaintyBand() {

	// ------------------------------------------------------------------------

	GlobalSettings();

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus;
	std::vector<TString> E;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; 
	std::vector<int> SectorIndex;  std::vector<TString> OutputPlotNames;
	std::vector<TString> Var;

	// ------------------------------------------------------------------------

	nucleus.push_back("4He");
	nucleus.push_back("12C");
	nucleus.push_back("56Fe");

	E.push_back("1_161");
	E.push_back("2_261");	
	E.push_back("4_461");

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");

	SectorIndex.push_back(0);
	SectorIndex.push_back(1);
	SectorIndex.push_back(2);
	SectorIndex.push_back(3);
	SectorIndex.push_back(4);
	SectorIndex.push_back(5);

	Var.push_back("ECal_Slice1");
	Var.push_back("ECal_Slice2");
	Var.push_back("ECal_Slice3");
 
	Var.push_back("EQEReso"); 
	Var.push_back("ECalReso"); 

	Var.push_back("ECal"); 
	Var.push_back("EQE");
	Var.push_back("DeltaPT"); 
	Var.push_back("DeltaAlphaT"); 
	Var.push_back("DeltaPhiT"); 

	// ------------------------------------------------------------------------

	const int NxBCuts = xBCut.size();
	const int NNuclei = nucleus.size();
	const int NEnergies = E.size();
	const int NFSIModels = FSIModel.size();
	const int NVars = Var.size();
	const int NPlots = SectorIndex.size();

	TH1D* Plots[NxBCuts][NNuclei][NEnergies][NFSIModels][NVars][NPlots];
	TFile* Files[NxBCuts][NNuclei][NEnergies][NFSIModels];

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			TString LabelE = " @ E = 4.461 GeV"; double DoubleE = 4.461;
			if ( E[WhichEnergy] == "1_161" ) { LabelE = " @ E = 1.161 GeV"; DoubleE = 1.161; }
			if ( E[WhichEnergy] == "2_261" ) { LabelE = " @ E = 2.261 GeV"; DoubleE = 2.261; }

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				if ( nucleus[WhichNucleus] == "4He" && E[WhichEnergy] == "1_161" ) { continue; }				
				if ( nucleus[WhichNucleus] == "56Fe" && E[WhichEnergy] == "1_161" ) { continue; }

				TString LabelsOfSamples = "^{12}C";
				if ( nucleus[WhichNucleus] == "4He" ) { LabelsOfSamples = "^{4}He"; }
				if ( nucleus[WhichNucleus] == "CH2" ) { LabelsOfSamples = "CH2"; }
				if ( nucleus[WhichNucleus] == "56Fe" ) { LabelsOfSamples = "^{56}Fe"; }

				// Loop over the data set / simulation files

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
					TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
					Files[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel] = TFile::Open(FileName,"update");

					TString UncFileName = "myAcceptanceUncertainties/Unc_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
					TFile* UncFile = TFile::Open(UncFileName,"recreate");

					// Loop over the variable of interest

					for (int WhichVar = 0; WhichVar < NVars; WhichVar ++) {

						TString LabelOfPlots = "(e,e')_{0#pi} E^{QE} [GeV]";

						if (Var[WhichVar] == "ECal_Slice1") { LabelOfPlots = "(e,e'p)_{1p0#pi} P_{T} [GeV/c]"; }
						if (Var[WhichVar] == "ECal_Slice2") { LabelOfPlots = "(e,e'p)_{1p0#pi} P_{T} [GeV/c]"; }
						if (Var[WhichVar] == "ECal_Slice3") { LabelOfPlots = "(e,e'p)_{1p0#pi} P_{T} [GeV/c]"; }

						if (Var[WhichVar] == "ECalReso") { LabelOfPlots = "E^{cal} Feeddown"; }

						if (Var[WhichVar] == "EQEReso") { LabelOfPlots = "E^{QE} Feeddown"; }

						if (Var[WhichVar] == "ECal") { LabelOfPlots = "(e,e'p)_{1p0#pi} E^{Cal} [GeV]"; }
						if (Var[WhichVar] == "DeltaPT") { LabelOfPlots = "(e,e'p)_{1p0#pi} P_{T} [GeV/c]"; }
						if (Var[WhichVar] == "DeltaAlphaT") { LabelOfPlots = "(e,e'p)_{1p0#pi} #delta#alpha_{T} [deg]"; }
						if (Var[WhichVar] == "DeltaPhiT") { LabelOfPlots = "(e,e'p)_{1p0#pi} #delta#phi_{T} [deg]"; }

						TString CanvasName =  Var[WhichVar] + "_" + nucleus[WhichNucleus] + "_" + E[WhichEnergy] + "_" + xBCut[WhichxBCut];
						TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
						PlotCanvas->SetBottomMargin(0.17);
						PlotCanvas->SetLeftMargin(0.17);

						TLegend* leg = leg = new TLegend(0.2,0.7,0.5,0.85);
						leg->SetNColumns(3);

						double max = -99.;
						double min = 1E12;

						std::vector<TH1D*> PlotsForUncBand; PlotsForUncBand.clear();

						// Loop over the plots

						for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

							if ( E[WhichEnergy] == "1_161" && (SectorIndex[WhichPlot] == 2 || SectorIndex[WhichPlot] == 4) ) { continue; }				
							if ( E[WhichEnergy] == "2_261" && (SectorIndex[WhichPlot] == 2 || SectorIndex[WhichPlot] == 3 || SectorIndex[WhichPlot] == 4) )
								{ continue; }				

							// ---------------------------------------------------------------------------------------

							TString PlotName = "h1_" + Var[WhichVar] + "_InSector_" + SectorIndex[WhichPlot];

							Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot] = 
								(TH1D*)Files[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel]->Get(PlotName);

							// --------------------------------------------------------------------------------------

							// Make the plot pretty

							Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->SetLineColor(SectorColors[SectorIndex[WhichPlot]]);
							Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples);
							Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->GetXaxis()->SetTitle(LabelOfPlots);
							PrettyDoubleXSecPlot(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]);

							// ----------------------------------------------------------------------------------

							// Use the universal e4v function that 
							// scales by all the necessary scaling factors
							// divides by the bin width to obtain normalized yields / absolute cross sections
							// uses the relevant binning
							// gets the relevant x axis range
							// If data sample: 
							//                 apply systematics due to rotations et al
							//                 apply acceptance systematics using sector-by -sector uncertainties

							UniversalE4vFunction(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E[WhichEnergy],Var[WhichVar]);

							// ---------------------------------------------------------------------------------------------------

							// Max, min

							double localmax = Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->GetMaximum();
							double localmin = Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->GetMinimum();

							if (localmax > max) { max = localmax; }
							if (localmin < min) { min = localmin; }
							double ExtraHeight = 0.1;
							double PosNegMin = TMath::Min(0.,(1+ExtraHeight)*min);
							Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][0]->GetYaxis()->SetRangeUser( PosNegMin, (1+ExtraHeight)*max );

							// --------------------------------------------------------------------------------------------------

							// Plotting

							if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->SetMarkerStyle(MarkerStyle); 
								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->SetMarkerSize(MarkerSize); 
								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->SetMarkerColor(SectorColors[SectorIndex[WhichPlot]]); 

								gStyle->SetErrorX(0); // Removing the horizontal errors
								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->Draw("e same"); 
								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][0]->Draw("e same"); 

							} else { 

								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]->Draw("C hist same");  // draw them as lines
								Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][0]->Draw("C hist same"); 

							}

							if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
							  {leg->AddEntry(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],ToStringInt(SectorIndex[WhichPlot]+1), "lep");}
							else 
							  { leg->AddEntry(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],ToStringInt(SectorIndex[WhichPlot]+1), "l"); }

							PlotsForUncBand.push_back(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]);

				                        // ---------------------------------------------------------------------------------------------------
				                        // ---------------------------------------------------------------------------------------------------

							TString ext = "";
							if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

							//PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"
							//+ext+nucleus[WhichNucleus]+"_" 
							//+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

							// -----------------------------------------------------------------------------------------------------------------------------------------


						} // End of the loop over the plots

						leg->SetBorderSize(0);
						leg->SetTextFont(FontStyle);
						leg->SetTextSize(TextSize);
						leg->Draw();

						delete PlotCanvas;

						std::vector<double> UncBand = GetUncertaintyBand(PlotsForUncBand);

						// ---------------------------------------------------------------------------------------------------------------------------------------

						// At this point, we have the uncertainty band due to the different sectors
						// Let's apply it on the plot which includes results from all sectors
						// Uncertainty band added in quadrature

						TString NameOfPlot = ""; 

						if ( Var[WhichVar] == "EQE" ) { NameOfPlot = "h_Erec_subtruct_piplpimi_noprot_3pi"; }
						else if ( Var[WhichVar] == "ECal_Slice1" ) { NameOfPlot = "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_1"; }
						else if ( Var[WhichVar] == "ECal_Slice2" ) { NameOfPlot =  "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_2"; }
						else if ( Var[WhichVar] == "ECal_Slice3" ) { NameOfPlot = "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_3"; }
						else if ( Var[WhichVar] == "ECalReso" ) { NameOfPlot = "h_Etot_subtruct_piplpimi_factor_fracfeed"; }
						else if ( Var[WhichVar] == "EQEReso" ) { NameOfPlot = "h_Erec_subtruct_piplpimi_factor_fracfeed"; }
						else if ( Var[WhichVar] == "ECal" ) { NameOfPlot = "epRecoEnergy_slice_0"; }
						else if ( Var[WhichVar] == "DeltaPT" ) { NameOfPlot = "MissMomentum"; }
						else if ( Var[WhichVar] == "DeltaPhiT" ) { NameOfPlot = "DeltaPhiT_Int_0"; }
						else if ( Var[WhichVar] == "DeltaAlphaT" ) { NameOfPlot = "DeltaAlphaT_Int_0"; }
						else { cout << "Come again ? Which combined plot are we talking about ?" << endl; }

						TH1D* Nom = (TH1D*)(Files[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel]->Get(NameOfPlot) );

						TString UncCanvasName = "UncCanvas_" + Var[WhichVar] + "_" + nucleus[WhichNucleus] + "_" + E[WhichEnergy] + "_" + xBCut[WhichxBCut];
						TCanvas* UncCanvas = new TCanvas(UncCanvasName,UncCanvasName,205,34,1024,768);

						// --------------------------------------------------------------------------------------

						// Use the universal e4v function that 
						// scales by all the necessary scaling factors
						// divides by the bin width to obtain normalized yields / absolute cross sections
						// uses the relevant binning
						// gets the relevant x axis range
						// If data sample: 
						//                 apply systematics due to rotations et al
						//                 apply acceptance systematics using sector-by -sector uncertainties

						UniversalE4vFunction(Nom,FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E[WhichEnergy],NameOfPlot);

						ApplySectorSystUnc(Nom,UncBand);

						TH1D* UncBandPlot = VectorToHistSystUnc(Nom, UncBand,Var[WhichVar]);

						// ---------------------------------------------------------------------------------------------------

						// Max, min

						double localmax = Nom->GetMaximum();
						double localmin = Nom->GetMinimum();

						double ExtraHeight = 0.1;
						double PosNegMin = TMath::Min(0.,(1+ExtraHeight)*localmin);
						Nom->GetYaxis()->SetRangeUser( PosNegMin, (1+ExtraHeight)*localmax );

						UncCanvas->cd();

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Nom->SetMarkerStyle(MarkerStyle); 
							Nom->SetMarkerSize(MarkerSize); 
							Nom->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Nom->Draw("e same");

						} else { 

							Nom->Draw("C hist same");  // draw them as lines

						}

						delete UncCanvas;

						UncFile->cd();
						UncBandPlot->Write();
						

					} // End of the loop over the variable of interest

				} // End of the loop over the FSI Models 

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
