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

void PlotGenieAbsXSec() {

	// ------------------------------------------------------------------------

	GlobalSettings();

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus; 
	std::vector<TString> JustNucleus;
	std::vector<TString> E;
	std::vector<double>  DoubleE;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames;

	// ------------------------------------------------------------------------

	nucleus.push_back("12C"); 
	JustNucleus.push_back("C");
	E.push_back("1_161"); DoubleE.push_back(1.161);

//	nucleus.push_back("12C"); 
//	JustNucleus.push_back("C");
//	E.push_back("2_261"); DoubleE.push_back(2.261);

//	nucleus.push_back("12C"); 
//	JustNucleus.push_back("C");
//	E.push_back("4_461"); DoubleE.push_back(4.461);

//	nucleus.push_back("56Fe"); 
//	JustNucleus.push_back("Fe");
//	E.push_back("2_261"); DoubleE.push_back(2.261);

//	nucleus.push_back("56Fe"); 
//	JustNucleus.push_back("Fe");
//	E.push_back("4_461"); DoubleE.push_back(4.461);

//	nucleus.push_back("4He"); 
//	JustNucleus.push_back("4He");
//	E.push_back("2_261");

//	nucleus.push_back("4He"); 
//	JustNucleus.push_back("4He");
//	E.push_back("4_461");

	// ------------------------------------------------------------------------

	xBCut.push_back("NoxBCut");

	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); LabelOfPlots.push_back("(e,e')_{0#pi} E_{QE} [GeV]");  OutputPlotNames.push_back("InclusiveeRecoEnergy_slice_0");
//	NameOfPlots.push_back("epRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E_{cal} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");

	if (NameOfPlots[0] == "h_Erec_subtruct_piplpimi_noprot_3pi") {

		FSIModel.push_back("hA2018_Final_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc"); FSILabel.push_back("G2018");
		FSIModel.push_back("SuSav2_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc"); FSILabel.push_back("SuSav2");	

	} else {

		FSIModel.push_back("hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("G2018");
		FSIModel.push_back("SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("SuSav2");	

	}

	// ------------------------------------------------------------------------

	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				// Loop over the plots				

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					// ---------------------------------------------------------------------------

					TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];
					TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
					PlotCanvas->SetLogy();

					// ---------------------------------------------------------------------------

					// Dimensions of TPad

					double XMinPadOne = 0., XMaxPadOne = 1., YMinPadOne = 0., YMaxPadOne = 1.;

					TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadOne,YMinPadOne,XMaxPadOne,YMaxPadOne, 21); 
					pad1->SetFillColor(kWhite); pad1->Draw();
					pad1->SetTopMargin(0.1);
					pad1->SetBottomMargin(0.18);
					pad1->SetLeftMargin(0.18); 
					if (NameOfPlots[WhichPlot] == "epRecoEnergy_slice_0" && E[WhichEnergy] == "1_161") { pad1->SetLeftMargin(0.15); }
					pad1->SetRightMargin(0.04);
					pad1->cd();

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					double LegXmin = 0.21, LegYmin = 0.45, YSpread = 0.35;

					TLegend* legGenieBlackLine = new TLegend(LegXmin,0.74,LegXmin+0.15,0.88);
					legGenieBlackLine->SetNColumns(1);

					double max = -99.;
					double min = 1E12;

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(DataSetColors[WhichFSIModel]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);

						Plots[WhichFSIModel]->GetXaxis()->SetTitle(JustNucleus[WhichNucleus]+LabelOfPlots[WhichPlot]);
						Plots[WhichFSIModel]->GetXaxis()->CenterTitle(0);

						Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(1.1);
						if (NameOfPlots[WhichPlot] == "epRecoEnergy_slice_0"  && E[WhichEnergy] == "1_161") 
							{ Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(0.85); }

						if (NameOfPlots[0] == "h_Erec_subtruct_piplpimi_noprot_3pi") 
							{ Plots[WhichFSIModel]->GetYaxis()->SetTitle(XSecEQELabel); }
						if (NameOfPlots[0] == "epRecoEnergy_slice_0") 
							{ Plots[WhichFSIModel]->GetYaxis()->SetTitle(XSecEcalLabel); }

						// -----------------------------------------------------------------------------------

						// Use the universal e4v function that 
						// scales by all the necessary scaling factors (multiply by GENIE xsec, division by number of events in the file)
						// divides by the bin width to obtain normalized yields / absolute cross sections	

						UniversalE4vFunction(Plots[WhichFSIModel],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot]);

						// --------------------------------------------------------------------------------------------------

						if (FSILabel[WhichFSIModel] == "G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
						Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines

						legGenieBlackLine->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel], "l"); 

		                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

					gPad->RedrawAxis();
					legGenieBlackLine->SetBorderSize(0);
					legGenieBlackLine->SetTextFont(FontStyle);
					legGenieBlackLine->SetNColumns(1); 
					legGenieBlackLine->SetTextSize(TextSize-0.03); 
					legGenieBlackLine->Draw(); 				

				} // End of the loop over the plots
				
				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program