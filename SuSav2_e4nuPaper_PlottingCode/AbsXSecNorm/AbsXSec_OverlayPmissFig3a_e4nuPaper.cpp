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

#include "../../myFunctions.cpp"
#include "../../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

void AbsXSec_OverlayPmissFig3a_e4nuPaper() {

	// ------------------------------------------------------------------------

	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;  std::vector<int> BreakDownColors;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");

	E.push_back("2_261"); LabelE.push_back(" @ E = 2.257 GeV"); DoubleE.push_back(2.261);	

	xBCut.push_back("NoxBCut");
 
	Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);

	Style.push_back(1); Style.push_back(1); Style.push_back(1); Style.push_back(1);

	BreakDownColors.push_back(kBlue); BreakDownColors.push_back(429); BreakDownColors.push_back(410); BreakDownColors.push_back(610);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_NoRadCorr");	
	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");

//	NameOfPlots.push_back("MissMomentum"); LabelOfPlots.push_back("P_{miss}^{#perp} [GeV/c]"); OutputPlotNames.push_back("MissMomentum");
	NameOfPlots.push_back("MissMomentum"); LabelOfPlots.push_back("P_{T} [GeV/c]"); OutputPlotNames.push_back("MissMomentum");

	std::vector<TH1D*> Plots;
	std::vector<TH1D*> Plots_Clones;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	TString WhatModelsAreIncluded = "";
	for (int LoopOverFSIModels = 0 ; LoopOverFSIModels < NFSIModels ; LoopOverFSIModels ++) { WhatModelsAreIncluded += "_"+DirNames[LoopOverFSIModels]; };

	TString RecoCalorimetry = "(e,e'p)";
	TString FSI = "FSI";

	std::vector<TString> GenieFSILabel; GenieFSILabel.clear();
	GenieFSILabel.push_back("QE"); GenieFSILabel.push_back("MEC"); GenieFSILabel.push_back("RES"); GenieFSILabel.push_back("DIS");

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				// Loop over the plots

				double max = -99.;
				double min = 1E12;
				double height = 1.05;

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					TCanvas* PlotCanvas = new TCanvas(nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
									 nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
									 205,34,850,1024);

					// ----------------------------------------------------------------------------------------------

					// Dimensions of TPads (pad2 will be deleted at the very end for the Ereco plots)

					double XMinPadOne = 0., XMaxPadOne = 1., YMinPadOne = 0.15, YMaxPadOne = 0.7;
					double XMinPadTwo = 0., XMaxPadTwo = 1., YMinPadTwo = YMaxPadOne+0.01, YMaxPadTwo = 0.85;

					// ----------------------------------------------------------------------------------------

					TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadOne,YMinPadOne,XMaxPadOne,YMaxPadOne, 21); 
					pad1->SetFillColor(kWhite); pad1->Draw();
					TPad* pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadTwo,YMinPadTwo,XMaxPadTwo,YMaxPadTwo,22); 
					pad2->SetFillColor(kWhite); pad2->Draw(); 

					pad1->SetTopMargin(0.);
					pad1->SetBottomMargin(0.19);
					pad1->SetLeftMargin(0.17);
					pad1->SetRightMargin(0.04);

					pad2->SetTopMargin(0.);
					pad2->SetBottomMargin(0.);
					pad1->cd();

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					TLegend* legGenie = new TLegend(0.15,0.01,0.9,0.7);					
					legGenie->SetNColumns(3);

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

//						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );
						Plots.push_back( (TH1D*)( FileSample->Get("Unc_DeltaPT") ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);
						Plots[WhichFSIModel]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]);

						// --------------------------------------------------------------------------------------

						// Scale to obtain absolute double differential cross sections 
						// Use charge, density and length for data samples
						// Use total number of events in genie sample and relevant genie cross sections for simulation

						//AbsoluteXSecScaling(Plots[WhichFSIModel],FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]); 

						// --------------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						//ReweightPlots(Plots[WhichFSIModel]);

						// --------------------------------------------------------------------------------------

						// Binning & Range

						//BinningAndRange(Plots[WhichFSIModel],DoubleE[WhichEnergy],"PT");

						// ----------------------------------------------------------------------------------

						// Genie Break Down

						if (
							FSILabel[WhichFSIModel] == "SuSav2"
						) {

							legGenie->AddEntry(Plots[0],"Data", "lep"); 
//							legGenie->AddEntry(Plots[WhichFSIModel],"GENIE (Total)", "l"); 

							BreakDownPlots.clear();

							for (int j = 1; j < 5; j++) {

								BreakDownPlots.push_back( (TH1D*)( FileSample->Get("Pmiss_Int_"+ToStringInt(j)) ) );

								ReweightPlots(BreakDownPlots[j-1]);
								AbsoluteXSecScaling(BreakDownPlots[j-1],FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]);
								ApplyRebinning(BreakDownPlots[j-1],DoubleE[WhichEnergy],"PT");
								ApplyRange(BreakDownPlots[j-1],DoubleE[WhichEnergy],"PT");

								//-----------------------------------------------------------------------------------------------

								BreakDownPlots[j-1]->SetLineColor(BreakDownColors[j-1]);

//								int GenieNBins = Plots[WhichFSIModel]->GetNbinsX();
//								int GenieMin = Plots[WhichFSIModel]->GetXaxis()->GetXmin();
//								int GenieMax = Plots[WhichFSIModel]->GetXaxis()->GetXmax();
//								BreakDownPlots[j-1]->SetBins(GenieNBins,GenieMin,GenieMax);
								
								BreakDownPlots[j-1]->SetLineWidth(3);
								BreakDownPlots[j-1]->SetLineStyle(Style[j-1]);

								TLegendEntry* l1 = legGenie->AddEntry(BreakDownPlots[j-1],GenieFSILabel[j-1], "l");
								if (j == 2) { legGenie->AddEntry(Plots[WhichFSIModel],"SuSav2 (Total)", "l");  }
								//if (j == 2) { legGenie->AddEntry(UncertaintyPlots[1],"GENIE (Total)", "lf");  }
								l1->SetTextColor(BreakDownColors[j-1]);

								pad1->cd();
								BreakDownPlots[j-1]->Draw("C hist same");

							} // end of the look over the GENIE break down

						} // End of the SuSav2 / break down option

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();
						Plots[0]->GetXaxis()->SetTitle(XLabel);

//						Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(5); 
//						Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);

						// --------------------------------------------------------------------------------------------------

						// Drawing The Plots

						pad1->cd();

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 
						
							if (FSILabel[WhichFSIModel] =="Genie") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines

							Plots[0]->Draw("e same"); 

						}

					} // End of the loop over the FSI Models 

					// -----------------------------------------------------------------------------------

					// Transverse Missing Momentum Slices // Vertical Lines

					pad1->cd();
					double LowPmiss = 0.2, MidPmiss = 0.4, HighPmiss = 1.;

					TLine* line1 = new TLine(LowPmiss,0.,LowPmiss,height*max);
					line1->SetLineColor(kBlack); line1->SetLineWidth(LineWidth);
					line1->Draw(); 

					TLine* line2 = new TLine(MidPmiss,0.,MidPmiss,height*max);
					line2->SetLineColor(kBlack); line2->SetLineWidth(LineWidth);
					line2->Draw(); 

					legGenie->SetBorderSize(0);
					legGenie->SetTextFont(FontStyle);

					pad2->cd(); 
					legGenie->SetTextSize(3.*TextSize);
					legGenie->AddEntry(Plots[2],"G2018", "l"); 
					legGenie->Draw(); 

					// ---------------------------------------------------------------------------------------------------

					TLatex* myNucleus = new TLatex();
					myNucleus->SetTextFont(FontStyle);
					myNucleus->SetTextColor(kBlack);
					myNucleus->SetTextSize(3.5*TextSize);
					pad2->cd();
					myNucleus->DrawLatexNDC(0.25,0.8,JustNucleus[WhichNucleus]+"(e,e'p)_{1p0#pi}"+LabelE[WhichEnergy]);

					// ---------------------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

					PlotCanvas->SaveAs("../../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"
						+ext+"Fig3a_"+nucleus[WhichNucleus]+"_" 
						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+WhatModelsAreIncluded+"_SuSav2_AbsXSec.pdf");

					//delete PlotCanvas;

					// ------------------------------------------------------------------------------


				} // End of the loop over the plots
				
				// --------------------------------------------------------------------------------------				
				
				// Chi2 calculation
				
				int NBinsX = Plots[0]->GetXaxis()->GetNbins();
				int Chi2Double = Chi2(Plots[0],Plots[1]);
				
				cout << endl << endl << "SuSav2 Chi2/ndof = " << Chi2Double << "/" << NBinsX << endl << endl;
				
				int G2018Chi2Double = Chi2(Plots[0],Plots[2]);
				
				cout << "G2018 Chi2/ndof = " << G2018Chi2Double << "/" << NBinsX << endl << endl;				
				
				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
