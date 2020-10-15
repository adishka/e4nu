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

void AbsXSec_OverlayPmissFig3b_e4nuPaper() {

	// ------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	TGaxis::SetMaxDigits(4);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	double YPadStart = 0.04;
	double YRange[4] = {0.04,0.4,0.7,0.99};
	double LeftMargin = 0.15;
	double TextSize = 0.15;
	int Ndivisions = 2;

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He"); JustNucleus.push_back("He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");  JustNucleus.push_back("Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV"); DoubleE.push_back(1.161);
	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");  DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");
 
	Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);

	Style.push_back(1); Style.push_back(1); Style.push_back(1); Style.push_back(1);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_NoRadCorr");
	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");  DirNames.push_back("hA2018_Truth_NoRadCorr");

	NameOfPlots.push_back("h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_3"); LabelOfPlots.push_back("P_{T} > 400 [MeV/c]");  OutputPlotNames.push_back("epRecoEnergy_slice_3");
	NameOfPlots.push_back("h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_2"); LabelOfPlots.push_back("200 < P_{T} < 400 [MeV/c]");  OutputPlotNames.push_back("epRecoEnergy_slice_2");
	NameOfPlots.push_back("h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_1"); LabelOfPlots.push_back("0 < P_{T} < 200 [MeV/c]");  OutputPlotNames.push_back("epRecoEnergy_slice_1");

	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	TString WhatModelsAreIncluded = "";
	for (int LoopOverFSIModels = 0 ; LoopOverFSIModels < NFSIModels ; LoopOverFSIModels ++) { WhatModelsAreIncluded += "_"+DirNames[LoopOverFSIModels]; };

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				TCanvas* PlotCanvas = new TCanvas(nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_ECalInPmissSlices_"+xBCut[WhichxBCut],
									 nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_ECalInPmissSlices_"+xBCut[WhichxBCut],
									 205,34,850,1024);

				PlotCanvas->SetTopMargin(0.);
				PlotCanvas->SetBottomMargin(0.);
				PlotCanvas->SetLeftMargin(0.);
				PlotCanvas->SetRightMargin(0.);

				// Loop over the plots

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					// --------------------------------------------------------------------------------------------

					// Dimensions of TPad

					PlotCanvas->cd();
					double step = (1. - YPadStart) / 3.;
//					double XMinPad = 0., XMaxPad = 1., YMinPad = YPadStart + step * WhichPlot, YMaxPad = YPadStart + step * (WhichPlot+1);
					double XMinPad = 0., XMaxPad = 1., YMinPad = YRange[WhichPlot], YMaxPad = YRange[WhichPlot+1];
					//if (WhichPlot == 0) { YMinPad = 0.; }

					// ----------------------------------------------------------------------------------------

					TPad* pad = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPad,YMinPad,XMaxPad,YMaxPad, 21); 
					pad->SetFillColor(kWhite); pad->SetFrameBorderSize(5); pad->Draw();

					pad->SetLeftMargin(LeftMargin);
					pad->SetRightMargin(0.05);
					pad->SetTopMargin(0.01);
					pad->SetBottomMargin(0.07);
					if (WhichPlot == 0) { pad->SetBottomMargin(0.27); }
					pad->cd();

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					double max = -99.;
					double min = 1E12;

					// Loop over the FSI Models
					
					int LowBin = -1;
					int HighBin = -1;					

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

//						if (NameOfPlots[WhichPlot] == "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_1") { Plots.push_back( (TH1D*)( FileSample->Get("Unc_ECal_Slice1") ) ); }

						// --------------------------------------------------------------------------------------

//						Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
						//Plots[WhichFSIModel]->SetLineWidth(LineWidth);

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);

						// --------------------------------------------------------------------------------------

//						// X-axis label

						Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);

						Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(1.05);
						Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(5);

						// -------------------------------------------------------------------------------------


						if (WhichPlot != 0) { Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(0.); }
					        else { Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(0.13); }

						// --------------------------------------------------------------------------------------

//						// Y-axis label

						Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
//						Plots[WhichFSIModel]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
//						Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(TextSize);
						Plots[WhichFSIModel]->GetYaxis()->SetTickSize(0.02);
						Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);
						Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(0.35);
						Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(0.);

					        if (WhichPlot == 0) { Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(0.13); }

						//-----------------------------------------------------------------------------------------------

						double LowE = 0.95*DoubleE[WhichEnergy];

						//Larry's suggestion because ECal has a sharp peak and a low tail 
						//Thus we scale the peak down by EnhaceTail

						if ( (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_0" || OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1") 
							&& DoubleE[WhichEnergy] == 2.261 && nucleus[WhichNucleus] == "12C" ) {

							int LowEBin = Plots[WhichFSIModel]->FindBin(LowE);
							int HighEBin = Plots[WhichFSIModel]->GetNbinsX();

							for (int i = LowEBin + 1; i <= HighEBin; i++) { 
					
								double content = Plots[WhichFSIModel]->GetBinContent(i);
								double error = Plots[WhichFSIModel]->GetBinError(i);
								double newcontent = EnhaceTail * content;
								double newerror = EnhaceTail * error;				
								Plots[WhichFSIModel]->SetBinContent(i,newcontent);
								Plots[WhichFSIModel]->SetBinError(i,newerror);

							}

						}

						// -----------------------------------------------------------------------------------

						// Scale to obtain absolute double differential cross sections 
						// Use charge, density and length for data samples
						// Use total number of events in genie sample and relevant genie cross sections for simulation

						AbsoluteXSecScaling(Plots[WhichFSIModel],FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]); 
//Plots[WhichFSIModel]->Scale(1./Plots[WhichFSIModel]->Integral());
						// -----------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						ReweightPlots(Plots[WhichFSIModel]);

						// --------------------------------------------------------------------------------------

						// Rebining & ranges

						double LowRange = 0.6;
						double HighRange = 2.35;						
						Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(LowRange,HighRange);

						ApplyRebinning(Plots[WhichFSIModel],DoubleE[WhichEnergy],"ECal");
						ApplyRange(Plots[WhichFSIModel],DoubleE[WhichEnergy],"ECal");
						
						LowBin = Plots[WhichFSIModel]->GetXaxis()->FindBin(LowRange);
						HighBin = Plots[WhichFSIModel]->GetXaxis()->FindBin(HighRange);						

						// ----------------------------------------------------------------------------------

						// Apply Systematic Uncertainties on Data Points
						// using numbers obtained from Mariana's thesis

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { ApplySystUnc(Plots[WhichFSIModel], DoubleE[WhichEnergy]); }
						
						// ----------------------------------------------------------------------------------

						// Genie Break Down

						if (
							FSILabel[WhichFSIModel] == "SuSav2"
						) {

							//legGenie->AddEntry(Plots[0],"Data", "lep"); 
//							//legGenie->AddEntry(Plots[WhichFSIModel],"GENIE (Total)", "l"); 

							BreakDownPlots.clear();

							for (int j = 1; j < 5; j++) {
							
								TString PlotName = "";

								if (NameOfPlots[WhichPlot] == "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_3") 
									{ PlotName = "ECal_HighPmiss_Int_"; }

								if (NameOfPlots[WhichPlot] == "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_2") 
									{ PlotName = "ECal_MidPmiss_Int_"; }
									
								if (NameOfPlots[WhichPlot] == "h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_1") 
									{ PlotName = "ECal_LowPmiss_Int_"; }							

								BreakDownPlots.push_back( (TH1D*)( FileSample->Get(PlotName+ToStringInt(j)) ) );

								AbsoluteXSecScaling(BreakDownPlots[j-1],FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]);
								ReweightPlots(BreakDownPlots[j-1]);
								ApplyRebinning(BreakDownPlots[j-1],DoubleE[WhichEnergy],"ECal");
								ApplyRange(BreakDownPlots[j-1],DoubleE[WhichEnergy],"ECal");

								//for (int i = 0; i < 2; i++) { BreakDownPlots[j-1]->Rebin(); }

								//-----------------------------------------------------------------------------------------------

								BreakDownPlots[j-1]->SetLineColor(BreakDownColors[j-1]);

								BreakDownPlots[j-1]->GetXaxis()->SetRangeUser(LowRange,HighRange);
								//int GenieNBins = Plots[WhichFSIModel]->GetNbinsX();
								//int GenieMin = Plots[WhichFSIModel]->GetXaxis()->GetXmin();
								//int GenieMax = Plots[WhichFSIModel]->GetXaxis()->GetXmax();
								//BreakDownPlots[j-1]->SetBins(GenieNBins,GenieMin,GenieMax);
								
								BreakDownPlots[j-1]->SetLineWidth(3);
								BreakDownPlots[j-1]->SetLineStyle(Style[j-1]);
								//BreakDownPlots[j-1]->Scale(ScalingFactor);
								//TLegendEntry* l1 = legGenie->AddEntry(BreakDownPlots[j-1],GenieFSILabel[j-1], "l");
								//if (j == 2) { legGenie->AddEntry(Plots[WhichFSIModel],"SuSav2 (Total)", "l");  }
								//if (j == 2) { legGenie->AddEntry(UncertaintyPlots[1],"GENIE (Total)", "lf");  }
								//l1->SetTextColor(BreakDownColors[j-1]);

								pad->cd();
								BreakDownPlots[j-1]->Draw("C hist same");

							} // end of the look over the GENIE break down

						} // End of the SuSav2 / break down option						

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						double height = 1.2;
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);
						//Plots[0]->GetYaxis()->SetRangeUser(-0.15,height*max);						

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						// --------------------------------------------------------------------------------------------------
 
						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 
							Plots[WhichFSIModel]->SetMarkerSize(2.);
							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 
						
							if (FSILabel[WhichFSIModel] == "G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
						
//							Plots[WhichFSIModel]->Draw("hist same"); // draw them as histos
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							Plots[0]->Draw("e same"); 
						}

						// ---------------------------------------------------------------------------------------------------

						TLatex* myPmissSlice = new TLatex();
						myPmissSlice->SetTextFont(FontStyle);
						myPmissSlice->SetTextColor(kBlack);
						myPmissSlice->SetTextSize(TextSize);
						pad->cd();
						if (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_3") { 
							myPmissSlice->SetTextSize(TextSize-0.02);
							myPmissSlice->DrawLatexNDC(0.2,0.85,LabelOfPlots[WhichPlot]); 
						}
						else { myPmissSlice->DrawLatexNDC(0.2,0.8,LabelOfPlots[WhichPlot]); }

						// -----------------------------------------------------------------------------------

						// TLine for Pmiss < 200 MeV / c slice  

						TLine* line1 = new TLine(LowE,0.,LowE,height*max);
						line1->SetLineColor(kBlack); 
						line1->SetLineWidth(LineWidth);
						//if ( OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1" ) { line1->Draw(); }

						// -----------------------------------------------------------------------------------

						// Add the x1/3 label to show that the last 5 bins in the Pmiss < 200 MeV / c slice have been scaled down

						TLatex latexScale;
						latexScale.SetTextFont(FontStyle);
						latexScale.SetTextSize(TextSize);
						latexScale.SetTextColor(kBlack);
						//if ( OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1" ) { latexScale.DrawLatexNDC(0.85,0.47,"x1/3"); }

					} // End of the loop over the FSI Models 

					// --------------------------------------------------------------------------------------				
					
					// Chi2 calculation
					
					cout << endl << endl << NameOfPlots[WhichPlot] << endl;
					
					int NBinsX = HighBin - LowBin +1;
					int Chi2Double = Chi2(Plots[0],Plots[1],LowBin,HighBin);
					
					cout << "SuSav2 Chi2/ndof = " << Chi2Double << "/" << NBinsX << endl << endl;
					
					int G2018Chi2Double = Chi2(Plots[0],Plots[2],LowBin,HighBin);
					
					cout << "G2018 Chi2/ndof = " << G2018Chi2Double << "/" << NBinsX << endl << endl;
					
					// --------------------------------------------------------------------------------------				

				} // End of the loop over the plots
			

				// Extra pad to add the X-axis label

				PlotCanvas->cd();
				TPad* padLabel = new TPad("padLabel","padLabel",0.,0.,1.,0.07, 21); 
				padLabel->SetFillColor(kWhite); padLabel->Draw();

				padLabel->SetLeftMargin(0.);
				padLabel->SetRightMargin(0.);
				padLabel->SetTopMargin(0.0);
				padLabel->SetBottomMargin(0.0);
				padLabel->cd();

				TLatex latexXTitle;
				latexXTitle.SetTextFont(FontStyle);
				latexXTitle.SetTextSize(5*TextSize);
				latexXTitle.SetTextColor(kBlack);
				latexXTitle.DrawLatexNDC(0.25,0.5,"(e,e'p)_{1p0#pi} E_{cal} [GeV]");

				// -----------------------------------------------------------------------------------------

				// Extra pad for the common title over the 3 pads

				PlotCanvas->cd();
				TPad* padTitle = new TPad("padTitle","padTitle",0.,0.,LeftMargin/2.,1., 21); 
				padTitle->SetFillColor(kWhite); 
				padTitle->Draw();
				padTitle->cd();

				TLatex latexYTitle;
				latexYTitle.SetTextFont(FontStyle);
				latexYTitle.SetTextSize(8*TextSize);
				latexYTitle.SetTextColor(kBlack);
				latexYTitle.SetTextAngle(90);
//				latexYTitle.DrawLatexNDC(0.8,0.27,"Weighted Events / GeV");		
				latexYTitle.DrawLatexNDC(0.8,0.27,"Normalized Yield");

				// --------------------------------------------------------------------------------------------

				// Pads to get rid of some 0's on the axes

				PlotCanvas->cd();
				TPad* padWhite1 = new TPad("padWhite1","padWhite1",0.06,0.67,0.105,0.72, 21); 
				padWhite1->SetFillColor(kWhite); 
//				padWhite1->SetFillColor(kBlack); 
				//padWhite1->Draw();
				//padWhite1->cd();

				PlotCanvas->cd();
				TPad* padWhite2 = new TPad("padWhite2","padWhite2",0.06,0.4,0.105,0.45, 21); 
				padWhite2->SetFillColor(kWhite); 
//				padWhite2->SetFillColor(kBlack);
				//padWhite2->Draw();
				//padWhite2->cd();				

				// ------------------------------------------------------------------------------------------------

				TString ext = "";
				if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

				PlotCanvas->SaveAs("../../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"
					+E[WhichEnergy]+"/"+ext+"Fig3b_"+nucleus[WhichNucleus]+"_" 
					+E[WhichEnergy]+"_"+WhatModelsAreIncluded+"_SuSav2_AbsXSec.pdf");

				//delete PlotCanvas;

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
