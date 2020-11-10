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
#include <TGraphAsymmErrors.h>

#include <iostream>
#include <vector>

using namespace std;

#include "../../myFunctions.cpp"
#include "../../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

void AccCorrXSec_OverlayEQE_Fig2() {

	// ------------------------------------------------------------------------

	GlobalSettings();

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus; 
	std::vector<TString> JustNucleus;
	std::vector<TString> E;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames;

	nucleus.push_back("12C"); 
	JustNucleus.push_back("C");
	E.push_back("1_161");

	xBCut.push_back("NoxBCut");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("SuSav2");	
	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("G2018");

	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]");  OutputPlotNames.push_back("InclusiveeRecoEnergy_slice_0");

	// ------------------------------------------------------------------------

	std::vector<TH1D*> Plots;
	std::vector<TH1D*> BreakDownPlots;

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

					TCanvas* PlotCanvas = new TCanvas(nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
									 nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
									 205,34,1024,768);

					// ---------------------------------------------------------------------------

					// Dimensions of TPad

					double XMinPadOne = 0., XMaxPadOne = 1., YMinPadOne = 0., YMaxPadOne = 1.;

					TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadOne,YMinPadOne,XMaxPadOne,YMaxPadOne, 21); 
					pad1->SetFillColor(kWhite); pad1->Draw();
					pad1->SetTopMargin(0.1);
					pad1->SetBottomMargin(0.18);
					pad1->SetLeftMargin(0.17); 
					pad1->SetRightMargin(0.04);
					pad1->cd();

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					double LegXmin = 0.22, LegYmin = 0.45, YSpread = 0.35;

					TLegend* legGenie = new TLegend(LegXmin,LegYmin,LegXmin+0.15,LegYmin+YSpread);
					legGenie->SetNColumns(1);

					TLegend* legGenieBlackLine = new TLegend(LegXmin,0.68,LegXmin+0.15,0.82);
					legGenieBlackLine->SetNColumns(1);

					TLegend* legGenieBreak = new TLegend(LegXmin,0.51,0.4,0.68);					
					legGenieBreak->SetNColumns(2);

					double max = -99.;
					double min = 1E12;

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(DataSetColors[WhichFSIModel]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);

						Plots[WhichFSIModel]->GetXaxis()->SetTitle(JustNucleus[WhichNucleus]+LabelOfPlots[WhichPlot]);
						Plots[WhichFSIModel]->GetXaxis()->CenterTitle(0);

						// -----------------------------------------------------------------------------------

						// Use the universal e4v function that 
						// scales by all the necessary scaling factors
						// divides by the bin width to obtain normalized yields / absolute cross sections
						// uses the relevant binning
						// gets the relevant x axis range
						// If data sample: 
						//                 apply systematics due to rotations et al
						//                 apply acceptance systematics using sector-by -sector uncertainties

						UniversalE4vFunction(Plots[WhichFSIModel],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot]);

						// ----------------------------------------------------------------------------------

						// Genie Break Down

						if (
							FSILabel[WhichFSIModel] == "SuSav2"
						) {

							legGenie->AddEntry(Plots[0],"Data", "lep"); 
							legGenieBlackLine->AddEntry(Plots[0],"Data", "lep"); 

							legGenie->AddEntry(Plots[WhichFSIModel],"SuSav2 (Total)", "l"); 
//							legGenieBlackLine->AddEntry(Plots[WhichFSIModel],"GENIE (Total)", "l"); 

							BreakDownPlots.clear();

							for (int j = 1; j < 5; j++) {

								BreakDownPlots.push_back( (TH1D*)( FileSample->Get("InclusiveEQE_Int_"+ToStringInt(j)) ) ); 

								UniversalE4vFunction(BreakDownPlots[j-1],FSIModelsToLabels[FSIModel[WhichFSIModel]],\
										     nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot]);

								//-----------------------------------------------------------------------------------------------

								BreakDownPlots[j-1]->SetLineColor(BreakDownColors[j-1]);
								BreakDownPlots[j-1]->SetLineWidth(3);

								TLegendEntry* l1 = legGenie->AddEntry(BreakDownPlots[j-1],GenieFSILabel[j-1], "l");
								l1->SetTextColor(BreakDownColors[j-1]);

								TLegendEntry* l1Break = legGenieBreak->AddEntry(BreakDownPlots[j-1],GenieFSILabel[j-1], "l");
								l1Break->SetTextColor(BreakDownColors[j-1]);

								BreakDownPlots[j-1]->Draw("C hist same");

							} // end of the look over the GENIE break down

						} // End of the SuSav2 if statement for breakdown

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						double height = 1.05;
						if ( xBCut[WhichxBCut] == "xBCut" ) { height = 1.1; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						// --------------------------------------------------------------------------------------------------

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							//Plots[WhichFSIModel]->Draw("e same"); 

							TH1D* DataPlot = AcceptanceCorrection(Plots[WhichFSIModel],"SuSav2", nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot],xBCut[WhichxBCut]);

							DataPlot->SetMarkerStyle(20); 
							DataPlot->SetMarkerSize(2.); 
							DataPlot->SetLineColor(kRed);	
							DataPlot->SetMarkerColor(kRed);	
							DataPlot->Draw("e same"); 							

						} else { 

							if (FSILabel[WhichFSIModel] == "G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							
							if (FSILabel[WhichFSIModel] == "SuSav2") 
								{ legGenieBlackLine->AddEntry(Plots[WhichFSIModel],"SuSav2 (Total)", "l"); }

							//Plots[0]->Draw("e same"); 

						}

		                                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

					legGenie->SetBorderSize(0);
					legGenie->SetTextFont(FontStyle);

					legGenieBlackLine->SetBorderSize(0);
					legGenieBlackLine->SetTextFont(FontStyle);

					legGenieBreak->SetBorderSize(0);
					legGenieBreak->SetTextFont(FontStyle);

					legGenie->SetTextSize(TextSize);

					legGenieBlackLine->SetNColumns(1); 
					legGenieBlackLine->SetTextSize(TextSize-0.03); 
					legGenieBlackLine->Draw(); 

					legGenieBreak->SetTextSize(TextSize-0.03);
					legGenieBreak->AddEntry(Plots[2],"G2018","l");					
					legGenieBreak->Draw();

					TLatex* myNucleus = new TLatex();
					myNucleus->SetTextFont(FontStyle);
					myNucleus->SetTextColor(kBlack);
					myNucleus->SetTextSize(TextSize-0.02);
					myNucleus->DrawLatexNDC(0.22,0.85,JustNucleus[WhichNucleus]+"(e,e')_{0#pi}");

					TLatex* myEbeam = new TLatex();
					myEbeam->SetTextFont(FontStyle);
					myEbeam->SetTextColor(kAzure+4);
					myEbeam->SetTextSize(TextSize-0.02);
					myEbeam->DrawLatexNDC(0.72,0.35,"E_{beam}");

					TLatex* myArrow = new TLatex();
					myArrow->SetTextFont(FontStyle);
					myArrow->SetTextColor(kAzure+4);
					myArrow->SetTextSize(1.2*TextSize);
					myArrow->DrawLatex(1.141,0.1,"#Downarrow");

					// Monitor where 1.161 GeV is
					//TLine* line = new TLine(1.161,0.,1.161,2.);
					//line->Draw();

					// -------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

					PlotCanvas->SaveAs("../../../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"
						+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+"_SuSav2_AccCorrXSec.pdf");

					//delete PlotCanvas;

					// --------------------------------------------------------------------------------------


				} // End of the loop over the plots
				
				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
