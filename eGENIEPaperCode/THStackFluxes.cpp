#include <TFile.h>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaletteAxis.h>
#include <TMath.h>
#include <TLine.h>
#include <TPad.h>
#include <THStack.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

TString ToStringInt(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

void THStackFluxes() {

	// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(3);
	//TGaxis::SetExponentOffset(-0.1, 1., "y");

	int Ndivisions = 4;
	int FontStyle = 132;
	double TextSize = 0.07;
	int NBreakDown = 5;

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t");

	const std::vector<int> Colors{610,410,kRed+1,kGreen+3,kBlue};

	// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> XLabelOfPlots; 
	std::vector<TString> YLabelOfPlots;  
	std::vector<TString> OutputPlotNames; 

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He");
	nucleus.push_back("C12"); LabelsOfSamples.push_back("^{12}C");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

	E.push_back("1161"); LabelE.push_back(" @ E = 1.161 GeV");
//	E.push_back("2261"); LabelE.push_back(" @ E = 2.261 GeV");
//	E.push_back("4461"); LabelE.push_back(" @ E = 4.461 GeV");

	FSIModel.push_back("GTEST19_10b_00_000_CCinclMEC");FSILabel.push_back("#nu SuSav2");
	FSIModel.push_back("G18_10a_02_11a_CCinclMEC");FSILabel.push_back("#nu G2018");

//	FSIModel.push_back("GTEST19_10b_00_000_EM+MEC");FSILabel.push_back("e SuSav2");
//	FSIModel.push_back("G18_10a_02_11a_EM+MEC");FSILabel.push_back("e G2018");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	NameOfPlots.push_back("EvPlot"); XLabelOfPlots.push_back("E_{#nu} [GeV]"); YLabelOfPlots.push_back("# Events"); OutputPlotNames.push_back("EvPlot");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// Loop over the energies

	for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

		// Loop over the nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot];
				TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,2024,768);

				// ---------------------------------------------------------------------------------------------------------------------------

				TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0,0,0.5,1., 21); 
				pad1->SetFillColor(kWhite); pad1->Draw();
				TPad* pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.5,0,1.,1,22); 
				pad2->SetFillColor(kWhite); pad2->Draw(); 
				pad1->SetBottomMargin(0.18);
				pad2->SetBottomMargin(0.18);

				// ---------------------------------------------------------------------------------------------------------------------------

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					if (WhichFSIModel == 0) 
						{ pad1->cd(); gStyle->SetTitleSize(TextSize,"t"); pad1->SetRightMargin(0.); pad1->SetLeftMargin(0.15); pad1->SetTitle("");}
					else { pad2->cd(); pad2->SetLeftMargin(0.0); pad2->SetRightMargin(0.15); }

					THStack* THStacks = new THStack(NameOfPlots[WhichPlot]+"_"+FSIModel[WhichFSIModel],"");

					TString PathToFiles = "myFiles/";
					TFile* FileSample = TFile::Open(PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+".root");

					TH1D* Plots[NBreakDown];

					for (int WhichInteraction = 0; WhichInteraction < NBreakDown; WhichInteraction++) {

						Plots[WhichInteraction] =  (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]+"_Interaction_"+ToStringInt(WhichInteraction) ) ) ;

						Plots[WhichInteraction]->GetXaxis()->CenterTitle();
						Plots[WhichInteraction]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichInteraction]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichInteraction]->GetXaxis()->SetLabelSize(TextSize);
						Plots[WhichInteraction]->GetXaxis()->SetTitleSize(TextSize);
						Plots[WhichInteraction]->GetXaxis()->SetTitleOffset(1.);
						Plots[WhichInteraction]->GetXaxis()->SetTitle(XLabelOfPlots[WhichPlot]);
						Plots[WhichInteraction]->GetXaxis()->SetNdivisions(5);

						Plots[WhichInteraction]->GetYaxis()->CenterTitle();
						Plots[WhichInteraction]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichInteraction]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichInteraction]->GetYaxis()->SetLabelSize(TextSize);
						Plots[WhichInteraction]->GetYaxis()->SetTitleSize(TextSize);
						Plots[WhichInteraction]->GetYaxis()->SetTitleOffset(1.);
						Plots[WhichInteraction]->GetYaxis()->SetTitle(YLabelOfPlots[WhichPlot]);
						Plots[WhichInteraction]->GetYaxis()->SetNdivisions(5);

						Plots[WhichInteraction]->SetLineColor(Colors[WhichInteraction]);
						Plots[WhichInteraction]->SetFillColor(Colors[WhichInteraction]);
						//Plots[WhichInteraction]->SetFillStyle(3004);
						Plots[WhichInteraction]->SetLineWidth(1);

						Plots[WhichInteraction]->GetXaxis()->SetRangeUser(0.1,9.7);
						Plots[WhichInteraction]->GetYaxis()->SetRangeUser(0.,4*TMath::Power(10.,6.));

						Plots[WhichInteraction]->Draw("hist same");
						THStacks->Add(Plots[WhichInteraction],"hist");
						THStacks->Draw("hist same");
		

					}

					// --------------------------------------------------------------------------------------------------------------------------

					// Rebinning & Ranges

					// -----------------------------------------------------------------------------------------------------------------------------

					TLatex *sample = new TLatex(); 
					sample->SetTextFont(FontStyle); 
					sample->SetTextColor(kBlack); 
					sample->SetTextSize(TextSize);
					if (WhichFSIModel == 0) { sample->DrawLatexNDC(0.6,0.84,FSILabel[WhichFSIModel]); }
					else { sample->DrawLatexNDC(0.45,0.84,FSILabel[WhichFSIModel]); }

					//delete PlotCanvas;

				} // End of the loop over the FSI Models 

//				PlotCanvas->SaveAs("../../myPlots/pdf/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"+nucleus[WhichNucleus]+"_" 
//							+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

				//delete PlotCanvas;

			} // End of the loop over the plots

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
