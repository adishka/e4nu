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

using namespace std;

// ----------------------------------------------------------------------------------------------------------------

void OverlayPlots() {

//	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	int Ndivisions = 6;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.08;
	gStyle->SetOptStat(0);

	// ----------------------------------------------------------------------------------

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 

	//	nucleus.push_back("40Ar");LabelsOfSamples.push_back("^{40}Ar");
	nucleus.push_back("C12");LabelsOfSamples.push_back("^{12}C");

	std::vector<TString> E; E.push_back("1161");
	std::vector<TString> LabelE; LabelE.push_back(" @ E = 1.161 GeV");

	//std::vector<int> Colors; Colors.push_back(kBlack); Colors.push_back(610);
	std::vector<int> Colors; Colors.push_back(kBlue-7); Colors.push_back(kOrange+1); Colors.push_back(kGreen+3); Colors.push_back(kRed+1);

	std::vector<TString> FSIModel;std::vector<TString> FSILabel; 

	FSIModel.push_back("GTEST19_10b_00_000_CCinclMEC");FSILabel.push_back("#nu SuSav2");
	FSIModel.push_back("GTEST19_10b_00_000_EM+MEC");FSILabel.push_back("e SuSav2");
//	FSIModel.push_back("GTEST19_10b_00_000_NoFSI_CCinclMEC");FSILabel.push_back("#nu SuSav2 NoFSI");
//	FSIModel.push_back("GTEST19_10b_00_000_NoFSI_EM+MEC");FSILabel.push_back("e SuSav2 NoFSI");
	
	//FSIModel.push_back("G18_10a_02_11a_CCinclMEC");FSILabel.push_back("#nu G2018");
	//FSIModel.push_back("G18_10a_02_11a_EM+MEC");FSILabel.push_back("e G2018");
	//FSIModel.push_back("G18_10a_02_11a_NoFSI_CCinclMEC");FSILabel.push_back("#nu G2018 NoFSI");
	//FSIModel.push_back("G18_10a_02_11a_NoFSI_EM+MEC");FSILabel.push_back("e G2018 NoFSI");
	
	std::vector<TString> NameOfPlots;

//	NameOfPlots.push_back("nu");
//      NameOfPlots.push_back("Q2");

//       NameOfPlots.push_back("ElectronCosTheta");
//       NameOfPlots.push_back("ElectronEnergy");

        //NameOfPlots.push_back("ProtonCosTheta");
        //NameOfPlots.push_back("ProtonEnergy");

        //NameOfPlots.push_back("epRecoEnergy_slice_0");
        //NameOfPlots.push_back("eRecoEnergy_slice_0");

//	NameOfPlots.push_back("MissMomentum");
//	NameOfPlots.push_back("DeltaAlphaT"); 
//	NameOfPlots.push_back("DeltaPhiT"); 

	NameOfPlots.push_back("MissMomentum_VectorSum");
	NameOfPlots.push_back("DeltaAlphaT_VectorSum"); 
	NameOfPlots.push_back("DeltaPhiT_VectorSum");

//	NameOfPlots.push_back("MissMomentum_OneProton");                                                                                                                                            
//      NameOfPlots.push_back("DeltaAlphaT_OneProton");                                                                                                                                               
//      NameOfPlots.push_back("DeltaPhiT_OneProton");

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

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

			        TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]; 

				TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768) ;

				PlotCanvas->SetBottomMargin(0.18);
				PlotCanvas->SetLeftMargin(0.15);

				Plots.clear();

				TLegend* leg = new TLegend(0.1,0.92,0.95,0.98);
				leg->SetNColumns(2);

				double max = -99.;

				// Loop over the FSI Models
				
				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

				  TString PathToFiles = "myFiles/";
				  TFile* FileSample = TFile::Open(PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+".root");

				  Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]+"Plot") ) );
				  
				  Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
				  Plots[WhichFSIModel]->SetLineWidth(3);

				  Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
				  Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
				  Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
				  Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);
				  Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(0.95);
				  Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(Ndivisions);

				  Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
				  Plots[WhichFSIModel]->GetYaxis()->SetTitleFont(FontStyle);
				  Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
				  Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(TextSize);
				  Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);
				  Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(0.9);

				  TLegendEntry* l1 = leg->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel], "l");
				  l1->SetTextColor(Colors[WhichFSIModel]);

				  double ScalingFactor = 1. / Plots[WhichFSIModel]->Integral();

				  //Plots[WhichFSIModel]->Rebin();
				  Plots[WhichFSIModel]->Scale(ScalingFactor);

				  // -----------------------------------------------------------------------------------

				  double localmax = Plots[WhichFSIModel]->GetMaximum();
				  if (localmax > max) { max = localmax; }
				  Plots[0]->GetYaxis()->SetRangeUser(0,1.1*max);

				  Plots[WhichFSIModel]->Draw("C hist same");
				  Plots[0]->Draw("C hist same");
				  
				} // End of the loop over the FSI Models 
				
				leg->SetBorderSize(0);
				leg->SetTextFont(FontStyle);
				leg->SetTextSize(0.07);			
				leg->Draw();

				TLatex* latex = new TLatex();
				latex->SetTextFont(FontStyle);
				latex->SetTextSize(0.07);			
				latex->DrawLatexNDC(0.2,0.4,LabelsOfSamples[WhichNucleus]+LabelE[WhichEnergy]);

				//PlotCanvas->SaveAs("myPlots/"+nucleus[WhichNucleus]+"_" +E[WhichEnergy]+"_" +NameOfPlots[WhichPlot]+WhatModelsAreIncluded+"_SuSav2.pdf"); 

			} // End of the loop over the plots

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
