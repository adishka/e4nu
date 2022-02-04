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

#include  "/home/afroditi/Dropbox/PhD/Secondary_Code/CenterAxisTitle.cpp"
#include "/home/afroditi/Dropbox/PhD/Secondary_Code/SetOffsetAndSize.cpp"
#include "/home/afroditi/Dropbox/PhD/Secondary_Code/ToString.cpp"

// ----------------------------------------------------------------------------------------------------------------

void ChargedPionMultiplicities_ZeroProton() {

	// ------------------------------------------------------------------------

	SetOffsetAndSize();
	TGaxis::SetMaxDigits(3);

	int Ndivisions = 4;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.08;

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");

	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);	

	xBCut.push_back("NoxBCut");
 
	Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kBlue); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);

	Style.push_back(1); Style.push_back(1); Style.push_back(7); Style.push_back(3);

	const std::vector<int> BreakDownColors{kBlue+1,kRed-3,kGreen+1,kOrange+1};
	const std::vector<TString> GenieFSILabel{"QE","MEC","RES","DIS"};	

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Data");
	FSIModel.push_back("SuSav2"); FSILabel.push_back("SuSav2");  DirNames.push_back("SuSav2");
//	FSIModel.push_back("hA2018"); FSILabel.push_back("Genie");  DirNames.push_back("G2018");	

	NameOfPlots.push_back("h1_Npi_ZeroProton_"); LabelOfPlots.push_back("#pi^{#pm} Multiplicities"); 
	OutputPlotNames.push_back("ZeroProton_PionMultiPlot");

	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	TString WhatModelsAreIncluded = "";
	for (int LoopOverFSIModels = 0 ; LoopOverFSIModels < NFSIModels ; LoopOverFSIModels ++) { WhatModelsAreIncluded += "_"+DirNames[LoopOverFSIModels]; };

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				TCanvas* PlotCanvas = new TCanvas(nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+"Multiplicities"+"_"+xBCut[WhichxBCut],
									 nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+"Multiplicities"+"_"+xBCut[WhichxBCut],
									 205,34,1024,768);

				PlotCanvas->SetLeftMargin(0.18);
				PlotCanvas->SetBottomMargin(0.17);

				PlotCanvas->cd();

				TLegend* leg = new TLegend(0.7,0.65,0.89,0.89);
				leg->SetNColumns(1);
				leg->SetMargin(0.2);

				// Loop over the plots

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					double max = -99.;
					double min = 1E12;

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString FileName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]+"0") ) );

						Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
						CenterAxisTitle(Plots[WhichFSIModel]);

						std::vector<TH1D*> TruePlots;

						if ( !(string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) ) {

							for (int i = 1; i < 6; i++) {

								TruePlots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot] + TString(std::to_string(i))) ) );

							}

						}

						// --------------------------------------------------------------------------------------

						// X-axis label

						Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(0.9);

						// X-axis Title

						Plots[WhichFSIModel]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]); 

						// X-axis Title/Tick Size

						Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(TextSize); 
						Plots[WhichFSIModel]->GetYaxis()->SetTickSize(0.02);

						// --------------------------------------------------------------------------------------
						// Y-axis label

						Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
						Plots[WhichFSIModel]->GetYaxis()->SetTitle("# Events");

						// --------------------------------------------------------------------------------------

						Plots[WhichFSIModel]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(0.8); 

						Plots[WhichFSIModel]->SetLineWidth(LineWidth);

						// --------------------------------------------------------------------------------------

						// Scaling Factor
						// Normalize things so that the 0-pion bin are at the same height
						double ScalingFactor = ScalingFactor = double(Plots[0]->GetBinContent(1)) / double(Plots[WhichFSIModel]->GetBinContent(1) );

						Plots[WhichFSIModel]->Scale(ScalingFactor);					

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						double height = 1.05;

						// multiplicity 4 is the highest one in data
						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4));
						if (localmin < min && localmin != 0) { min = localmin; }

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();

						Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(5);
						Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);

						// --------------------------------------------------------------------------------------------------

						// Multiplicity plots

						Plots[WhichFSIModel]->GetYaxis()->SetLabelOffset(-0.004);
						Plots[WhichFSIModel]->GetYaxis()->SetRangeUser(1E1,2*1E7);
						PlotCanvas->SetLogy();

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 
						 
							Plots[WhichFSIModel]->SetMarkerSize(3.); 
							Plots[WhichFSIModel]->SetLineColor(kBlack); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 
							Plots[WhichFSIModel]->SetMarkerStyle(20);
							gStyle->SetErrorX(0); 
							Plots[WhichFSIModel]->Draw("e same"); 

							leg->AddEntry(Plots[WhichFSIModel],DirNames[WhichFSIModel],"p");

						} else {

							Plots[WhichFSIModel]->Draw("hist same");
							leg->AddEntry(Plots[WhichFSIModel],DirNames[WhichFSIModel],"l");	

							for (int i = 0; i < 4; i++) {

								TruePlots[i]->Scale(ScalingFactor);
								TruePlots[i]->SetLineColor( BreakDownColors.at(i) );
								TruePlots[i]->SetLineWidth(LineWidth);
								TruePlots[i]->Draw("hist same");

								leg->AddEntry(TruePlots[i],GenieFSILabel[i],"l");

							}													

						}

		                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 


				} // End of the loop over the plots

				// -----------------------------------------------------------------------------------------------------------------------------------------

				leg->SetBorderSize(0);
				leg->SetTextFont(FontStyle);
				leg->SetTextSize(0.05);
				leg->Draw();

				TLatex latexData;
				latexData.SetTextFont(FontStyle);
				latexData.SetTextSize(TextSize);
				latexData.DrawLatexNDC(0.2,0.91,"0 Detected Protons");

				// -----------------------------------------------------------------------------------------------------------------------------------------

				PlotCanvas->SaveAs(nucleus[WhichNucleus]+"_" +E[WhichEnergy]+"_" +"ChargedPion_ZeroProton_Multiplicities.pdf");

				delete PlotCanvas;

				// -----------------------------------------------------------------------------------------------------------------------------------------

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
