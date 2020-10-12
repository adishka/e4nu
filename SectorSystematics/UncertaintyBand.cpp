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

	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus;
	std::vector<TString> E;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; 
	std::vector<int> SectorIndex;  std::vector<TString> OutputPlotNames;
	std::vector<TString> Var;

	// ------------------------------------------------------------------------

//	nucleus.push_back("4He");
	nucleus.push_back("12C");
//	nucleus.push_back("56Fe");

//	E.push_back("1_161");
//	E.push_back("2_261");	
	E.push_back("4_461");

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");

	SectorIndex.push_back(0);
	SectorIndex.push_back(1);
	SectorIndex.push_back(5);

	Var.push_back("ECal"); 
//	Var.push_back("EQE");

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

				TString LabelsOfSamples = "^{12}C";
				if ( nucleus[WhichNucleus] == "4He" ) { LabelsOfSamples = "^{4}He"; }
				if ( nucleus[WhichNucleus] == "CH2" ) { LabelsOfSamples = "CH2"; }
				if ( nucleus[WhichNucleus] == "56Fe" ) { LabelsOfSamples = "^{56}Fe"; }

				// Loop over the data set / simulation files

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
					TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
					Files[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel] = TFile::Open(FileName);

					// Loop over the variable of interest

					for (int WhichVar = 0; WhichVar < NVars; WhichVar ++) {

						TString LabelOfPlots = "(e,e')_{0#pi} E^{QE} [GeV]";
						if (Var[WhichVar] == "ECal") { LabelOfPlots = "(e,e'p)_{1p0#pi} E^{Cal} [GeV]"; }

						TString CanvasName =  Var[WhichVar] + "_" + nucleus[WhichNucleus] + "_" + E[WhichEnergy] + "_" + xBCut[WhichxBCut];

						TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

						PlotCanvas->SetBottomMargin(0.17);
						PlotCanvas->SetLeftMargin(0.17);

						TLegend* leg = leg = new TLegend(0.17,0.7,0.5,0.85);
						leg->SetNColumns(3);

						double max = -99.;
						double min = 1E12;

						// Loop over the plots

						for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

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

							// --------------------------------------------------------------------------------------

							// Scale to obtain absolute double differential cross sections 
							// Use charge, density and length for data samples
							// Use total number of events in genie sample and relevant genie cross sections for simulation

							AbsoluteXSecScaling(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],
								FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]); 

							// -----------------------------------------------------------------------------------

							// Division by bin width, function defined in myFunctions.C
							// Accounting for the fact that the bin width might not be constant

							ReweightPlots(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot]);

							// --------------------------------------------------------------------------------------

							// Rebining & ranges

							BinningAndRange(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],DoubleE,Var[WhichVar]);

							// ----------------------------------------------------------------------------------

							// Apply Systematic Uncertainties on Data Points
							// using numbers obtained from Mariana's thesis

							if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
								{ ApplySystUnc(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot], DoubleE); }

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
							  {leg->AddEntry(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],ToStringInt(SectorIndex[WhichPlot]), "lep");}
							else 
							  { leg->AddEntry(Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot],ToStringInt(SectorIndex[WhichPlot]), "l"); }


				                        // ---------------------------------------------------------------------------------------------------
				                        // ---------------------------------------------------------------------------------------------------

							TString ext = "";
							if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

							//PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"
							//+ext+nucleus[WhichNucleus]+"_" 
							//+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

							//delete PlotCanvas;

							// -----------------------------------------------------------------------------------------------------------------------------------------


						} // End of the loop over the plots

/*
				std::vector<double> UncBand = GetUncertaintyBand(SectorPlots);

				leg->SetBorderSize(0);
				leg->SetTextFont(FontStyle);
				leg->SetTextSize(TextSize);
				leg->Draw(); // Just data + e.g. susav2


				TString PathToFiles = "../../myFiles/"+ E[0] + "/"+FSIModel[0]+"/"+xBCut[0]+"/";
				TString FileName = PathToFiles+nucleus[0]+"_"+E[0]+"_"+FSIModel[0]+"_Plots_FSI_em.root";
				TFile* FileSample = TFile::Open(FileName);

				TH1D* Nom = nullptr;

				if ( NameOfPlots[0] == "h1_EQE_InSector_0" ) { Nom = (TH1D*)(FileSample->Get("h_Erec_subtruct_piplpimi_noprot_3pi") ); }
				if ( NameOfPlots[0] == "h1_ECal_InSector_0" ) { Nom = (TH1D*)(FileSample->Get("epRecoEnergy_slice_0") ); }

				TCanvas* UncCanvas = new TCanvas("UncCanvas","UncCanvas",205,34,1024,768);
				UncCanvas->cd();

				// ----------------------------------------------------------------------------------

				// Apply Systematic Uncertainties on Data Points

				double SystUnc = 0;
				if ( DoubleE[WhichEnergy] == 1.161 ) { SystUnc = SystUnc1GeV; }
				if ( DoubleE[WhichEnergy] == 2.261 ) { SystUnc = SystUnc2GeV; }
				if ( DoubleE[WhichEnergy] == 4.461 ) { SystUnc = SystUnc4GeV; }

				if (string(FSILabel[0]).find("Data") != std::string::npos) { ApplySystUnc(Nom, SystUnc); }

				// ---------------------------------------------------------------------------------------------------

				// Max, min, title & # divisions

				double max = Nom->GetMaximum();
				Nom->GetYaxis()->SetRangeUser(0.,1.2*max);

				TString XLabel = Plots[0]->GetXaxis()->GetTitle();
				Nom->GetXaxis()->SetTitle(XLabel);

				Nom->GetXaxis()->SetNdivisions(Ndivisions);
				Nom->GetYaxis()->SetNdivisions(Ndivisions);

				// --------------------------------------------------------------------------------------------------

				double ScaleBy = 1.;

				if (FSILabel[0] == "Pinned Data") { 

					ScaleBy = 1. / (IntegratedCharge_PinnedFiles[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

					Nom->Scale(ScaleBy);
				}

				// --------------------------------------------------------------------------------------------------

				if (string(FSILabel[0]).find("Data") != std::string::npos) { 

					Nom->SetMarkerStyle(20); 
					Nom->SetMarkerSize(2.); 
					Nom->SetMarkerColor(kBlack); 

					gStyle->SetErrorX(0); // Removing the horizontal errors
					Nom->Draw("e same"); 

				} else { 

					Nom->SetLineStyle(Style[0]); 
					Nom->Draw("C hist same");  // draw them as lines

				}

				// ---------------------------------------------------------------------------------------------------

				ReweightPlots(Nom);

				//ApplySectorSystUnc(Nom,UncBand);

				Nom->SetMarkerSize(2.);
				Nom->Draw("e");
*/

					} // End of the loop over the var of interest

				} // End of the loop over the FSI Models 

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
