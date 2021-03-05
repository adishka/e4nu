#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <TGaxis.h>

#include <iostream>
#include <vector>

#include "eGENIE_Constants.h"
#include "eGENIE_Functions.cpp"

using namespace std;

// ----------------------------------------------------------------------------------------------------------------

void NuInclusiveOverlayPlots() {

	// ----------------------------------------------------------------------------------

	int Ndivisions = 7;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.07;
	gStyle->SetOptStat(0);

	// ----------------------------------------------------------------------------------

	std::vector<TString> nucleus; nucleus.push_back("C12");

	std::vector<TString> E; E.push_back("1161");
	std::vector<TString> LabelE; LabelE.push_back(" @ E = 1.161 GeV");

	// ----------------------------------------------------------------------------------

	std::vector<int> Colors;
	std::vector<int> Styles;

	std::vector<TString> FSIModel;std::vector<TString> FSILabel; 

	FSIModel.push_back("GTEST19_10b_00_000_CCinclMEC_Q2_0_1");FSILabel.push_back("#nu"); Colors.push_back(kBlue-7); Styles.push_back(kSolid); 
	FSIModel.push_back("GTEST19_10b_00_000_EM+MEC_Q2_0_1");FSILabel.push_back("e"); Colors.push_back(kOrange+1); Styles.push_back(kSolid); 
	
	std::vector<TString> NameOfPlots;

	NameOfPlots.push_back("nuPlot_OneProton");
	NameOfPlots.push_back("nuPlot_OneProton");

	// -------------------------------------------------------------------------------------------

	std::vector<TH1D*> Plots;

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// -------------------------------------------------------------------------------------------------------

	// Loop over the energies

	for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

		// Loop over the nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]; 

			TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768) ;

			PlotCanvas->SetBottomMargin(0.15);
			PlotCanvas->SetLeftMargin(0.16);
			PlotCanvas->SetRightMargin(0.05);

			Plots.clear();

			double max = -99.;

			// Loop over the FSI Models
				
			for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

				TString PathToFiles = "myFiles/";
				TFile* FileSample = TFile::Open(PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+".root");

				Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichFSIModel]) ) );
				  
				Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
				Plots[WhichFSIModel]->SetLineStyle(Styles[WhichFSIModel]);
				Plots[WhichFSIModel]->SetLineWidth(LineWidth);

				Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
				Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
				Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
				Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);
				Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(0.95);
				Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(Ndivisions);
				Plots[WhichFSIModel]->GetXaxis()->CenterTitle();

				Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
				Plots[WhichFSIModel]->GetYaxis()->SetTitleFont(FontStyle);
				Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
				Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(TextSize);
				Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);
				Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(1.2);
				Plots[WhichFSIModel]->GetYaxis()->SetTitle("Area Normalized");
				Plots[WhichFSIModel]->GetYaxis()->CenterTitle();

				for (int i = 0; i < 2 ; i++) { Plots[WhichFSIModel]->Rebin(); }

				double ScalingFactor = 1./Plots[WhichFSIModel]->Integral();
				Plots[WhichFSIModel]->Scale(ScalingFactor);

				// -----------------------------------------------------------------------------------

				double localmax = Plots[WhichFSIModel]->GetMaximum();
				if (localmax > max) { max = localmax; }
				Plots[0]->GetYaxis()->SetRangeUser(0,1.1*max);

				Plots[WhichFSIModel]->Draw("C hist same");
				Plots[0]->Draw("C hist same");

				TLatex* latex = new TLatex();
				latex->SetTextFont(FontStyle);
				latex->SetTextColor(Colors[WhichFSIModel]);
				latex->SetTextSize(0.07);			
				if (FSILabel[WhichFSIModel] == "#nu") { latex->DrawLatexNDC(0.53,0.3,FSILabel[WhichFSIModel]); }
				if (FSILabel[WhichFSIModel] == "e") { latex->DrawLatexNDC(0.5,0.48,FSILabel[WhichFSIModel]); }
				  
			} // End of the loop over the FSI Models 

			PlotCanvas->SaveAs("myPlots/"+nucleus[WhichNucleus]+"_" +E[WhichEnergy]+"_nuPlot_OneProton_SuSav2.pdf"); 

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
