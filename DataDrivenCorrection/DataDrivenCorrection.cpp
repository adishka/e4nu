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

void DataDrivenCorrection() {

	// ------------------------------------------------------------------------

	GlobalSettings();
	const std::vector<int> LocalDataSetColors{1,410,kRed,kBlue,kOrange,kCyan,kGreen,kGray+1, kRed + 2, kBlue-2, kOrange+3, kGray+5};
	double split = 0.1;

//	TString identifier = "_AllTopologies";
//	TString identifier = "_1p0pi_Np4pi";
//	TString identifier = "_1p0pi_4p0pi_5p0pi";
//	TString identifier = "_1p0pi_5p0pi";
//	TString identifier = "_1p0pi_4p0pi";
//	TString identifier = "_1p0pi_1p1pi_1p2pi_1p3pi_2p0pi_2p1pi_2p2pi_3p0pi_3p1pi_4p0pi";
//	TString identifier = "_1p0pi_1p1pi_1p2pi_1p3pi_2p0pi_2p1pi_2p2pi_3p0pi_3p1pi";
//	TString identifier = "_1p0pi_1p1pi_1p2pi_2p0pi_2p1pi_2p2pi_3p0pi_3p1pi";
//	TString identifier = "_1p0pi_1p1pi_2p0pi_2p1pi_2p2pi_3p0pi_3p1pi_4p0pi";
//	TString identifier = "_1p0pi_1p1pi_2p0pi_2p1pi_2p2pi_3p0pi_3p1pi";
//	TString identifier = "_1p0pi_1p1pi_2p0pi_2p1pi_2p2pi_3p0pi";
//	TString identifier = "_1p0pi_1p1pi_2p0pi_2p1pi_2p2pi";
//	TString identifier = "_1p0pi_1p1pi_2p0pi_2p1pi";
//	TString identifier = "_1p0pi_2p2pi";
//	TString identifier = "_1p0pi_1p3pi";
//	TString identifier = "_1p0pi_1p2pi";
//	TString identifier = "_1p0pi_1p1pi_2p0pi";
//	TString identifier = "_1p0pi_2p0pi_3p0pi_4p0pi";
//	TString identifier = "_1p0pi_2p0pi_3p0pi";
//	TString identifier = "_1p0pi_4p0pi";
///	TString identifier = "_1p0pi_2p1pi";
//	TString identifier = "_1p0pi_3p0pi";
//	TString identifier = "_1p0pi_1p1piminus_MinThetaq";
//	TString identifier = "_1p0pi_1p1piminus_PhiThetaBand_AngThres_RotBeamLine";
//	TString identifier = "_1p0pi_1p1piminus_PhiThetaBand_AngThres";
//	TString identifier = "_1p0pi_1p1piplus_PhiThetaBand_1000Rot";
//	TString identifier = "_1p0pi_2p0pi";
//	TString identifier = "_1p0pi_1p1piminus_PhiThetaBand";
//	TString identifier = "_1p0pi_1p1piplus_PhiThetaBand";
//	TString identifier = "_1p0pi_1p1piminus";
//	TString identifier = "_1p0pi_1p1piplus";
//	TString identifier = "_1p0pi_1p1pi";
	TString identifier = "";
//	TString identifier = "_1p0pi";
//	TString identifier = "_PhiThetaBand_NoThetaCut";
//	TString identifier = "_PhiThetaBand_WithThetaCut";

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus; 
	std::vector<TString> JustNucleus;
	std::vector<TString> E; 
	std::vector<double> DoubleE;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> SampleLabel; 
	std::vector<TString> NameOfPlots; 

	TString LabelOfPlots = "(e,e'p)_{1p0#pi} E^{cal} [GeV]";

	// ------------------------------------------------------------------------

//	nucleus.push_back("4He"); JustNucleus.push_back("He");
//	nucleus.push_back("12C"); JustNucleus.push_back("C");
	nucleus.push_back("56Fe"); JustNucleus.push_back("Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.157 GeV"); DoubleE.push_back(1.161);	
	E.push_back("2_261"); LabelE.push_back(" @ E = 2.257 GeV"); DoubleE.push_back(2.261);	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.457 GeV"); DoubleE.push_back(4.461);	

	xBCut.push_back("NoxBCut");

//	FSIModel.push_back("Pinned_Data_Final");
	FSIModel.push_back("SuSav2_RadCorr_LFGM");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_Truth_WithFidAcc"); FSILabel.push_back("True 1p0pi");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_SixSectors"); FSILabel.push_back("SuSav2");

//	FSIModel.push_back("SuSav2_RadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("True 1p0pi W/O");

	// Subtraction Layers

	NameOfPlots.push_back("h1_E_tot_cut2");SampleLabel.push_back("1p0pi W/O Sub");

//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_factor"); SampleLabel.push_back("1p1pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_prot"); SampleLabel.push_back("2p0pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_32prot"); SampleLabel.push_back("3p to 2p->1p");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_31prot"); SampleLabel.push_back("3p to 1p");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_43prot"); SampleLabel.push_back("4p to 3p->2->1");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_431prot"); SampleLabel.push_back("4p to 3p->1p");

//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_431prot"); SampleLabel.push_back("4p to 3p->1p");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_42prot"); SampleLabel.push_back("4p to 2p->1");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_41prot"); SampleLabel.push_back("4p to 1p");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_1p2pi"); SampleLabel.push_back("1p 2pi->1p1pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_1p2pi_1p0pi"); SampleLabel.push_back("1p 2pi->1p0pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_1p3pi"); SampleLabel.push_back("1p 3pi-> 1p 0pi");

//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_1p3pi"); SampleLabel.push_back("1p 3pi-> 1p 0pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_2p2pi"); SampleLabel.push_back("2p 2pi -> 1p 0pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_3p1pi"); SampleLabel.push_back("3p 1pi -> 1p 0pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_2p1pi_2p0pi"); SampleLabel.push_back("2p 1pi -> 2p 0pi");
//	NameOfPlots.push_back("h_Etot_subtruct_piplpimi_2p1pi_1p1pi"); SampleLabel.push_back("2p 1pi -> 1p 1pi");

//	NameOfPlots.push_back("h1_E_tot_4pto1p"); SampleLabel.push_back("4p->1p effect");
//	NameOfPlots.push_back("h1_E_tot_4pto3p"); SampleLabel.push_back("4p to 3p->2p->1p effect");
//	NameOfPlots.push_back("h1_E_tot_4pto2p"); SampleLabel.push_back("4p to 2p->1p effect");
//	NameOfPlots.push_back("h1_E_tot_43pto1p"); SampleLabel.push_back("4p to 3p->1p effect");

	// Final plot

//	NameOfPlots.push_back("epRecoEnergy_slice_0"); SampleLabel.push_back("2p 1pi -> 1p 0pi");
	NameOfPlots.push_back("epRecoEnergy_slice_0"); SampleLabel.push_back("1p0pi W/ Sub");

	// -------------------------------------------------------------------------------------------

//	NameOfPlots.push_back("h1_E_rec_0pi");SampleLabel.push_back("0pi W/O Sub");
//	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot"); SampleLabel.push_back("1pi");
//	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_2pi"); SampleLabel.push_back("2pi");
//	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); SampleLabel.push_back("3pi");
//	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_4pi"); SampleLabel.push_back("4pi");

//	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); SampleLabel.push_back("0pi W/ Sub");

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
				double height = 1.15;

				TString PlotCanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+xBCut[WhichxBCut];
				TCanvas* PlotCanvas = new TCanvas(PlotCanvasName,PlotCanvasName,205,34,1024,768);

				PlotCanvas->SetLeftMargin(0.15);
				PlotCanvas->SetBottomMargin(0.17);

				TLegend* legGenie = new TLegend(0.05,0.9,0.95,0.99);					
				legGenie->SetNColumns(6);

				// ---------------------------------------------------------------------------------------

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					Plots.clear();

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = GlobalPathToFiles + E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
//						TString PathToFiles = "./OlderSamples/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em"+identifier+".root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(LocalDataSetColors[WhichPlot]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);
						Plots[WhichFSIModel]->GetXaxis()->SetTitle(LabelOfPlots);

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
//						Plots[0]->GetYaxis()->SetRangeUser(-1.,height*max);

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();
						Plots[0]->GetXaxis()->SetTitle(XLabel);

						// --------------------------------------------------------------------------------------------------

						// Drawing The Plots

						if (string(SampleLabel[WhichPlot]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 
						
//							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							Plots[WhichFSIModel]->Draw("e hist same");  // draw them as histos

						}

						legGenie->AddEntry(Plots[WhichFSIModel],SampleLabel[WhichPlot]);

					} // End of the loop over the FSI Models 

					// -----------------------------------------------------------------------------------

				} // End of the loop over the plots

				// --------------------------------------------------------------------------------------				

				TString PathToFiles = GlobalPathToFiles + E[WhichEnergy] + "/SuSav2_RadCorr_LFGM_Truth_WithFidAcc/"+xBCut[WhichxBCut]+"/";
//				TString PathToFiles = "./OlderSamples/";
				TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_SuSav2_RadCorr_LFGM_Truth_WithFidAcc_Plots_FSI_em"+identifier+".root";
				TFile* FileSample = TFile::Open(FileName);

				TH1D* TruePlot = (TH1D*)( FileSample->Get(NameOfPlots[NPlots-1]));

				// Make the plot pretty

				TruePlot->SetLineColor(610);
				PrettyDoubleXSecPlot(TruePlot);
				TruePlot->GetXaxis()->SetTitle(LabelOfPlots);

				UniversalE4vFunction(TruePlot,"SuSav2",nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[NPlots-1]);
//				TruePlot->Draw("C hist same");
				TruePlot->Draw("e hist same");

				//legGenie->AddEntry(Plots[NPlots-1],SampleLabel[NPlots-1]);
				legGenie->AddEntry(TruePlot,"True 1p0pi");

				// --------------------------------------------------------------------------------------				

				legGenie->SetBorderSize(0);
				legGenie->SetTextFont(FontStyle);

				PlotCanvas->cd();
				legGenie->Draw(); 

				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
