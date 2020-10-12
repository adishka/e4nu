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

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<int> SectorIndex;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;
	std::vector<TString> Var;

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV"); DoubleE.push_back(1.161);
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);	
	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");  DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");
 
//	Colors.push_back(kBlack); Colors.push_back(kRed); Colors.push_back(kBlue); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);
	Colors.push_back(kBlack); Colors.push_back(610); Colors.push_back(410); Colors.push_back(kMagenta); Colors.push_back(kGreen+3); Colors.push_back(kBlue);  Colors.push_back(610);

//	Style.push_back(9); Style.push_back(3); Style.push_back(7); Style.push_back(5);
//	Style.push_back(9); Style.push_back(9); Style.push_back(9); Style.push_back(9); // fancy dashed lines 
	Style.push_back(1); Style.push_back(kDashed); Style.push_back(1); Style.push_back(1);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");

/*
	NameOfPlots.push_back("h1_EQE_InSector_0"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); SectorIndex.push_back("1st");  OutputPlotNames.push_back("h1_EQE_InSector_0");
	NameOfPlots.push_back("h1_EQE_InSector_1"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); SectorIndex.push_back("2nd");  OutputPlotNames.push_back("h1_EQE_InSector_1");
//	NameOfPlots.push_back("h1_EQE_InSector_2"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); SectorIndex.push_back("3rd");  OutputPlotNames.push_back("h1_EQE_InSector_2");
//	NameOfPlots.push_back("h1_EQE_InSector_3"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); SectorIndex.push_back("4th");  OutputPlotNames.push_back("h1_EQE_InSector_3");
//	NameOfPlots.push_back("h1_EQE_InSector_4"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); SectorIndex.push_back("5th");  OutputPlotNames.push_back("h1_EQE_InSector_4");
	NameOfPlots.push_back("h1_EQE_InSector_5"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]"); SectorIndex.push_back("6th");  OutputPlotNames.push_back("h1_EQE_InSector_5");
*/


//	NameOfPlots.push_back("h1_ECal_InSector_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{Cal} [GeV]"); SectorIndex.push_back("1st");  OutputPlotNames.push_back("h1_ECal_InSector_0");
//	NameOfPlots.push_back("h1_ECal_InSector_1"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{Cal} [GeV]"); SectorIndex.push_back("2nd");  OutputPlotNames.push_back("h1_ECal_InSector_1");
////	NameOfPlots.push_back("h1_ECal_InSector_2"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{Cal} [GeV]"); SectorIndex.push_back("3rd");  OutputPlotNames.push_back("h1_ECal_InSector_2");
////	NameOfPlots.push_back("h1_ECal_InSector_3"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{Cal} [GeV]"); SectorIndex.push_back("4th");  OutputPlotNames.push_back("h1_ECal_InSector_3");
////	NameOfPlots.push_back("h1_ECal_InSector_4"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{Cal} [GeV]"); SectorIndex.push_back("5th");  OutputPlotNames.push_back("h1_ECal_InSector_4");
//	NameOfPlots.push_back("h1_ECal_InSector_5"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{Cal} [GeV]"); SectorIndex.push_back("6th");  OutputPlotNames.push_back("h1_ECal_InSector_5");

	SectorIndex.push_back(0);
	SectorIndex.push_back(1);
	SectorIndex.push_back(5);

	Var.push_back("ECal"); 
//	Var.push_back("EQE");

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

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

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

							Plots[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel][WhichVar][WhichPlot] = (TH1D*)Files[WhichxBCut][WhichNucleus][WhichEnergy][WhichFSIModel]->Get(PlotName);

							// --------------------------------------------------------------------------------------
/*
						// Make the plot pretty

						Plots[WhichPlot]->SetLineColor(SectorColors[WhichPlot]);
						Plots[WhichPlot]->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples[WhichNucleus]+LabelE[WhichNucleus]);
						Plots[WhichPlot]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]);
						PrettyDoubleXSecPlot(Plots[WhichPlot]);

						// --------------------------------------------------------------------------------------

						// Scaling Factor
						// Scale to data integral after dividing by integrated charge & length

						double ScalingFactor = 1.;
						double ScaleBy = 1.;

int MinBin = 0;
int MaxBin = Plots[WhichFSIModel]->GetXaxis()->GetNbins()+1;


						if (FSILabel[WhichFSIModel] == "Data") { 

							ScaleBy = 1. / ( IntegratedCharge[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]] ) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);

							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "Data_FilterRuns") { 

							ScaleBy = 1. / (IntegratedCharge_FilterRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "Data_NewFilterRuns") { 

							ScaleBy = 1. / (IntegratedCharge_NewFilterRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "GoodRunList_Data") { 

							ScaleBy = 1. / (IntegratedCharge_GoodRunList_AllRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "LowCurrent_GoodRunList_Data") { 

							ScaleBy = 1. / (IntegratedCharge_GoodRunList_LowCurrentRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}


						if (FSILabel[WhichFSIModel] == "HighCurrent_GoodRunList_Data") { 

							ScaleBy = 1. / (IntegratedCharge_GoodRunList_HighCurrentRuns[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "Pinned Data") { 

							ScaleBy = 1. / (IntegratedCharge_PinnedFiles[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetLength[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    TargetDensity[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
										    OverallUnitConversionFactor / MassNumber[nucleus[WhichNucleus]]) * ConversionFactorCm2ToMicroBarn / dOmega;

							Plots[WhichFSIModel]->Scale(ScaleBy);
							DataIntegral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						// -------------------------------------------------------------------------------------------------------------------------------------------------

						if (FSILabel[WhichFSIModel] == "SuSav2" || FSILabel[WhichFSIModel] == "SuSav2_NoAccMaps" ) { 

							ScalingFactor = (SuSav2GenieXSec[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] * TMath::Power(10.,-38.) *\
								ConversionFactorCm2ToMicroBarn / (SuSav2NumberEvents[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
								dOmega) ) ;

							Plots[WhichFSIModel]->Scale(ScalingFactor);
							ScaleBy = ScalingFactor;
							SuSav2Integral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						if (FSILabel[WhichFSIModel] == "G2018") { 

							ScalingFactor = ( G2018GenieXSec[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] * TMath::Power(10.,-38.) *\
								ConversionFactorCm2ToMicroBarn / (G2018NumberEvents[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])] *\
								dOmega) );

							Plots[WhichFSIModel]->Scale(ScalingFactor);
							ScaleBy = ScalingFactor;
							G2018Integral =  Plots[WhichFSIModel]->Integral(MinBin,MaxBin);
						}

						// -----------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						ReweightPlots(Plots[WhichFSIModel]);

						// --------------------------------------------------------------------------------------

						// Rebining & ranges


						if (string(NameOfPlots[WhichPlot]).find("Omega_FullyInclusive") != std::string::npos) {

							if (DoubleE[WhichEnergy] == 1.161)  
								{ for (int i = 0; i < 5; i++) { Plots[WhichFSIModel]->Rebin(); } Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.,0.7);  }

							if ( DoubleE[WhichEnergy] == 2.261) 
								{ for (int i = 0; i < 5; i++) { Plots[WhichFSIModel]->Rebin(); } Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.,1.5); }

							if ( DoubleE[WhichEnergy] == 4.461) 
								{ for (int i = 0; i < 6; i++) { Plots[WhichFSIModel]->Rebin(); } Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.5,3.); }

						} else {

							if (DoubleE[WhichEnergy] == 1.161)  { 
								//for (int i = 0; i < 5; i++) { Plots[WhichFSIModel]->Rebin(); }
								Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.4,1.7); 
							}

							if ( DoubleE[WhichEnergy] == 2.261) { 
								//for (int i = 0; i < 5; i++) { Plots[WhichFSIModel]->Rebin(); }
								Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(0.6,3.); 
							}

							if ( DoubleE[WhichEnergy] == 4.461) { 
								//for (int i = 0; i < 6; i++) { Plots[WhichFSIModel]->Rebin(); }
								Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(1.5,6.); 
							}

						}

						// ----------------------------------------------------------------------------------

						// Apply Systematic Uncertainties on Data Points

						double SystUnc = 0;
						if ( DoubleE[WhichEnergy] == 1.161 ) { SystUnc = SystUnc1GeV; }
						if ( DoubleE[WhichEnergy] == 2.261 ) { SystUnc = SystUnc2GeV; }
						if ( DoubleE[WhichEnergy] == 4.461 ) { SystUnc = SystUnc4GeV; }

						if (FSILabel[WhichFSIModel] == "Data") { ApplySystUnc(Plots[WhichFSIModel], SystUnc); }

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();

						if (localmax > max) { max = localmax; }
						double height = 1.2;
						if ( xBCut[WhichxBCut] == "xBCut" ) { height = 1.1; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();
						Plots[0]->GetXaxis()->SetTitle(XLabel);

						Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(Ndivisions);
						Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);

						// --------------------------------------------------------------------------------------------------

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(Colors[WhichPlot]); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 

							Plots[WhichFSIModel]->SetLineStyle(Style[WhichFSIModel]); 
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines

						}

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
							{ leg->AddEntry(Plots[WhichFSIModel],SectorIndex[WhichPlot], "lep");}
						else { leg->AddEntry(Plots[WhichFSIModel],SectorIndex[WhichPlot], "l"); }
				
						SectorPlots.push_back(Plots[WhichFSIModel]);


		                                // ---------------------------------------------------------------------------------------------------
		                                // --------------------------------------------------------------------------------------------------


					// -----------------------------------------------------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

//					PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
//						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

					delete PlotCanvas;

					// -----------------------------------------------------------------------------------------------------------------------------------------

*/
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
					Nom->SetMarkerColor(Colors[0]); 

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
