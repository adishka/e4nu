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

#include <iostream>
#include <map>
#include <utility>

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

void HydrogenComparisons() {

	// ------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

	// ------------------------------------------------------------------------

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He"); JustNucleus.push_back("He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");
	nucleus.push_back("CH2"); LabelsOfSamples.push_back("CH2"); JustNucleus.push_back("CH2");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");  JustNucleus.push_back("Fe");

	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV"); DoubleE.push_back(1.161);
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");  DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");
 
//	Colors.push_back(kBlack); Colors.push_back(kRed); Colors.push_back(kBlue); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);
	Colors.push_back(kBlack); Colors.push_back(610); Colors.push_back(410); Colors.push_back(kMagenta); Colors.push_back(kGreen+3); Colors.push_back(kBlue);  Colors.push_back(610);

//	Style.push_back(9); Style.push_back(3); Style.push_back(7); Style.push_back(5);
//	Style.push_back(9); Style.push_back(9); Style.push_back(9); Style.push_back(9); // fancy dashed lines 
	Style.push_back(1); Style.push_back(kDashed); Style.push_back(1); Style.push_back(1);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");

//	FSIModel.push_back("Data_Final"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("hA2018_Final_NoRadCorr_LFGM"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");  DirNames.push_back("G2018");
//	FSIModel.push_back("SuSav2_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2 NoRad");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("SuSav2");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_NoAccMaps"); FSILabel.push_back("SuSav2_NoAccMaps");  DirNames.push_back("SuSav2_NoAccMaps");

//	FSIModel.push_back("SuSav2_02_11a_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("Data_Final_FilterRuns"); FSILabel.push_back("Data_FilterRuns"); DirNames.push_back("Data_FilterRuns");
//	FSIModel.push_back("Data_Final_NewFilterRuns"); FSILabel.push_back("Data_NewFilterRuns"); DirNames.push_back("Data_NewFilterRuns");

//	FSIModel.push_back("GoodRunList_Data_Final"); FSILabel.push_back("GoodRunList_Data"); DirNames.push_back("GRL Data");
//	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");
//	FSIModel.push_back("LowCurrent_GoodRunList_Data_Final"); FSILabel.push_back("LowCurrent_GoodRunList_Data"); DirNames.push_back("LC GRL Data");
//	FSIModel.push_back("HighCurrent_GoodRunList_Data_Final"); FSILabel.push_back("HighCurrent_GoodRunList_Data"); DirNames.push_back("HC GRL Data");

//	FSIModel.push_back("Data_Final_NoChargedPions"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_NoChargedPions"); FSILabel.push_back("G2018");  DirNames.push_back("hA2018_Truth_RadCorr");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_NoChargedPions"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("hA2018_Final_NoRadCorr"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hA2018_Truth_NoRadCorr"); FSILabel.push_back("Genie (Truth)");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hN2018_Final_NoRadCorr_LFGM"); FSILabel.push_back("Genie hN2018");  DirNames.push_back("hN2018_Truth_NoRadCorr");
//	FSIModel.push_back("hN2018_Final_RadCorr_LFGM"); FSILabel.push_back("Genie hN2018");  DirNames.push_back("hN2018_Truth_NoRadCorr");



//	NameOfPlots.push_back("h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0"); LabelOfPlots.push_back("1st Sector Energy Transfer [GeV]"); OutputPlotNames.push_back("h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0");

	NameOfPlots.push_back("h1_Wvar_weight"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");


	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TCanvas* PlotCanvas = new TCanvas(E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
								 E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
								 205,34,1024,768);

				PlotCanvas->SetBottomMargin(0.2);
				PlotCanvas->SetLeftMargin(0.17);

				// ---------------------------------------------------------------------------------------

				TLegend* leg = leg = new TLegend(0.2,0.73,0.35,0.87);

				leg->SetNColumns(1);

				double max = -99.;
				double min = 1E12;

				double DataIntegral = 1.;
				double SuSav2Integral = 1.;
				double G2018Integral = 1.;

				// Loop over the FSI Models

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					// Loop over the nuclei

					Plots.clear();

					for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

						TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichNucleus]->SetLineColor(Colors[WhichNucleus]);
						Plots[WhichNucleus]->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples[WhichNucleus]);
						Plots[WhichNucleus]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]);
						PrettyDoubleXSecPlot(Plots[WhichNucleus]);

						// --------------------------------------------------------------------------------------

						// Scale to obtain absolute double differential cross sections 
						// Use charge, density and length for data samples
						// Use total number of events in genie sample and relevant genie cross sections for simulation

						AbsoluteXSecScaling(Plots[WhichNucleus],FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]);

						// -----------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						ReweightPlots(Plots[WhichNucleus]);

						// --------------------------------------------------------------------------------------

						// Rebining & ranges

						ApplyRebinning(Plots[WhichNucleus],DoubleE[WhichEnergy],NameOfPlots[WhichPlot]);
						ApplyRange(Plots[WhichNucleus],DoubleE[WhichEnergy],NameOfPlots[WhichPlot]);

Plots[WhichNucleus]->Scale(MassNumber[nucleus[WhichNucleus]]);

						// ----------------------------------------------------------------------------------

						// Apply Systematic Uncertainties on Data Points
						// using numbers obtained from Mariana's thesis

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
								{ ApplySystUnc(Plots[WhichNucleus], DoubleE[WhichEnergy]); }

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichNucleus]->GetMaximum();

						if (localmax > max) { max = localmax; }
						double height = 1.05;
						if ( xBCut[WhichxBCut] == "xBCut" ) { height = 1.1; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

//						TString XLabel = Plots[WhichNucleus]->GetXaxis()->GetTitle();
//						Plots[0]->GetXaxis()->SetTitle(XLabel);

						// --------------------------------------------------------------------------------------------------

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichNucleus]->SetMarkerStyle(20); 
							Plots[WhichNucleus]->SetMarkerSize(2.); 
							Plots[WhichNucleus]->SetMarkerColor(Colors[WhichNucleus]); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichNucleus]->Draw("e same"); 

						} else { 

							Plots[WhichNucleus]->SetLineStyle(Style[WhichFSIModel]); 
							Plots[WhichNucleus]->Draw("C hist same");  // draw them as lines
							Plots[0]->Draw("e same"); 

						}

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
							{ leg->AddEntry(Plots[WhichNucleus],LabelsOfSamples[WhichNucleus], "lep");}
						else { leg->AddEntry(Plots[WhichNucleus],LabelsOfSamples[WhichNucleus], "l"); }
				

		                                // ---------------------------------------------------------------------------------------------------
		                                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the nuclei

					leg->SetBorderSize(0);
					leg->SetTextFont(FontStyle);
					leg->SetTextSize(TextSize);
					leg->Draw(); // Just data + e.g. susav2

					// -----------------------------------------------------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

//					PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
//						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

					//delete PlotCanvas;

					// -----------------------------------------------------------------------------------------------------------------------------------------

				} // End of the loop over the FSI Models

			} // End of the loop over the plots

			TCanvas* DiffCanvas = new TCanvas("DiffCanvas","DiffCanvas",205,34,1024,768);
			DiffCanvas->SetBottomMargin(0.2);
			DiffCanvas->SetLeftMargin(0.17);
			
			TH1D* Clone = (TH1D*)Plots[1]->Clone("Clone");
			Clone->Add(Plots[0],-1);
			Clone->Scale(0.5);
			DiffCanvas->cd();
			Clone->Draw();

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
