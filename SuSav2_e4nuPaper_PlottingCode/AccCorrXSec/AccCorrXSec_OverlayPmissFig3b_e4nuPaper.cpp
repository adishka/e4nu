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

void AccCorrXSec_OverlayPmissFig3b_e4nuPaper() {

	// ------------------------------------------------------------------------

	GlobalSettings();
	TGaxis::SetMaxDigits(4);

	// ------------------------------------------------------------------------

	double YPadStart = 0.04;
	double YRange[4] = {0.04,0.4,0.7,0.99};
	double LeftMargin = 0.23;
	double TextSize = 0.15;
	int Ndivisions = 3;

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus;
	std::vector<TString> E; 
	std::vector<double> DoubleE;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots; 
	std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames;

	// ------------------------------------------------------------------------

	nucleus.push_back("12C");

	E.push_back("2_261"); DoubleE.push_back(2.261);	

	xBCut.push_back("NoxBCut");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_NoRadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("hA2018_Final_NoRadCorr_LFGM_Truth_WithoutFidAcc"); FSILabel.push_back("G2018");

	NameOfPlots.push_back("h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_3"); LabelOfPlots.push_back("P_{T} > 400 [MeV/c]");  OutputPlotNames.push_back("epRecoEnergy_slice_3");
	NameOfPlots.push_back("h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_2"); LabelOfPlots.push_back("200 < P_{T} < 400 [MeV/c]");  OutputPlotNames.push_back("epRecoEnergy_slice_2");
	NameOfPlots.push_back("h1_Etot_p_bkgd_slice_sub2p1pi_1p0pi_1"); LabelOfPlots.push_back("0 < P_{T} < 200 [MeV/c]");  OutputPlotNames.push_back("epRecoEnergy_slice_1");

	// ------------------------------------------------------------------------

	std::vector<TH1D*> Plots;
	std::vector<TH1D*> BreakDownPlots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// ------------------------------------------------------------------------

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
					double XMinPad = 0., XMaxPad = 1., YMinPad = YRange[WhichPlot], YMaxPad = YRange[WhichPlot+1];

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

					TH1D* DataPlot = nullptr;				

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichFSIModel]->SetLineColor(DataSetColors[WhichFSIModel]);
						PrettyDoubleXSecPlot(Plots[WhichFSIModel]);

						// --------------------------------------------------------------------------------------

						// X-axis label

						Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);

						Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(1.05);
						Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(5);
						Plots[WhichFSIModel]->GetXaxis()->SetTickLength(0.05);

						// -------------------------------------------------------------------------------------


						if (WhichPlot != 0) { Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(0.); }
					        else { Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(0.13); }

						// --------------------------------------------------------------------------------------

						// Y-axis label

						Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
						Plots[WhichFSIModel]->GetYaxis()->SetTickSize(0.02);
						Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);
						Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(0.35);
						Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(0.);

					        if (WhichPlot == 0) { Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(0.13); }
					        if (WhichPlot == 0) { Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(0.12); }

						//-----------------------------------------------------------------------------------------------

//						double LowE = 0.95*DoubleE[WhichEnergy];

//						//Larry's suggestion because ECal has a sharp peak and a low tail 
//						//Thus we scale the peak down by EnhaceTail

//						if ( (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_0" || OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1") 
//							&& DoubleE[WhichEnergy] == 2.261 && nucleus[WhichNucleus] == "12C" ) {

//							int LowEBin = Plots[WhichFSIModel]->FindBin(LowE);
//							int HighEBin = Plots[WhichFSIModel]->GetNbinsX();

//							for (int i = LowEBin + 1; i <= HighEBin; i++) { 
//					
//								double content = Plots[WhichFSIModel]->GetBinContent(i);
//								double error = Plots[WhichFSIModel]->GetBinError(i);
//								double newcontent = EnhaceTail * content;
//								double newerror = EnhaceTail * error;				
//								Plots[WhichFSIModel]->SetBinContent(i,newcontent);
//								Plots[WhichFSIModel]->SetBinError(i,newerror);

//							}

//						}

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
						
						// ----------------------------------------------------------------------------------

						// Genie Break Down

						if (
							FSILabel[WhichFSIModel] == "SuSav2"
						) {

							//legGenie->AddEntry(Plots[0],"Data", "lep"); 

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

								UniversalE4vFunction(BreakDownPlots[j-1],FSIModelsToLabels[FSIModel[WhichFSIModel]],\
										     nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot]);

								//-----------------------------------------------------------------------------------------------

								BreakDownPlots[j-1]->SetLineColor(BreakDownColors[j-1]);
								
								BreakDownPlots[j-1]->SetLineWidth(3);

								pad->cd();
								BreakDownPlots[j-1]->Draw("C hist same");

							} // end of the look over the GENIE break down

						} // End of the SuSav2 / break down option						

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
//						double height = 1.2;
						double height = 3.7;
						if (WhichPlot == 1) { height = 4.3; }
						if (WhichPlot == 2) { height = 5.2; }

						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						// --------------------------------------------------------------------------------------------------
 
						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 
							Plots[WhichFSIModel]->SetMarkerSize(2.);
							gStyle->SetErrorX(0); // Removing the horizontal errors
							//Plots[WhichFSIModel]->Draw("e same"); 

							DataPlot = Plots[WhichFSIModel];

							DataPlot = AcceptanceCorrection(Plots[WhichFSIModel],"SuSav2", nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot],xBCut[WhichxBCut]);

							DataPlot->SetMarkerStyle(20); 
							DataPlot->SetMarkerSize(2.); 
							DataPlot->SetLineColor(kBlack);	
							DataPlot->SetMarkerColor(kBlack);
							DataPlot->GetYaxis()->SetRangeUser(0.,height*DataPlot->GetMaximum());	
							DataPlot->Draw("e same"); 

//							TH1D* DataPlotG2018 = AcceptanceCorrection(Plots[WhichFSIModel],"hA2018_Final", nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot],xBCut[WhichxBCut]);

//							DataPlotG2018->SetMarkerStyle(20); 
//							DataPlotG2018->SetMarkerSize(2.); 
//							DataPlotG2018->SetLineColor(kRed);	
//							DataPlotG2018->SetMarkerColor(kRed);	
//							DataPlotG2018->Draw("e same");


						} else { 
						
							if (FSILabel[WhichFSIModel] == "G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
						
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							//Plots[0]->Draw("e same"); 
						}

						// ---------------------------------------------------------------------------------------------------

						TLatex* myPmissSlice = new TLatex();
						myPmissSlice->SetTextFont(FontStyle);
						myPmissSlice->SetTextColor(kBlack);
						myPmissSlice->SetTextSize(TextSize);

						TLatex* label = new TLatex();
						label->SetTextFont(FontStyle);
						label->SetTextColor(kBlack);
						label->SetTextSize(TextSize-0.01);

						pad->cd();

						if (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_3") { 

							myPmissSlice->SetTextSize(TextSize-0.03);
							myPmissSlice->DrawLatexNDC(0.27,0.85,LabelOfPlots[WhichPlot]); 

							label->SetTextSize(TextSize-0.03);
							label->DrawLatexNDC(0.895,0.85,"(c)"); 

						}
						else { 
						
							myPmissSlice->SetTextSize(TextSize-0.01);
							myPmissSlice->DrawLatexNDC(0.27,0.8,LabelOfPlots[WhichPlot]); 

							if (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1") { label->DrawLatexNDC(0.895,0.85,"(a)"); }
							if (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_2") { label->DrawLatexNDC(0.895,0.85,"(b)"); }

						}

						// -----------------------------------------------------------------------------------

						// TLine for Pmiss < 200 MeV / c slice  

//						TLine* line1 = new TLine(LowE,0.,LowE,height*max);
//						line1->SetLineColor(kBlack); 
//						line1->SetLineWidth(LineWidth);
//						if ( OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1" ) { line1->Draw(); }

						// -----------------------------------------------------------------------------------

						// Add the x1/3 label to show that the last 5 bins in the Pmiss < 200 MeV / c slice have been scaled down

//						TLatex latexScale;
//						latexScale.SetTextFont(FontStyle);
//						latexScale.SetTextSize(TextSize);
//						latexScale.SetTextColor(kBlack);
//						if ( OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1" ) { latexScale.DrawLatexNDC(0.85,0.47,"x1/3"); }

						gPad->RedrawAxis();

					} // End of the loop over the FSI Models 

// -----------------------------------------------------------------------------------------------------------------------------------

if (OutputPlotNames[WhichPlot] == "epRecoEnergy_slice_1") {

	// ---------------------------------------

	double PadNDCXmin = 0.28,PadNDCXmax = 0.86, PadNDCYmin = 0.15,PadNDCYmax = 0.7;
	double PadLeftMargin = 0.105, PadRightMargin = 0.05, PadBottomMargin = 0.1;

	double Xmin = 0.9, Xmax = 2.1, Ymin = 0.001, Ymax = 0.09;

	// ---------------------------------------

	TH1D* DataPlotClone = (TH1D*)(DataPlot->Clone("DataPlotClone"));
	TH1D* SuSav2PlotClone = (TH1D*)(Plots[1]->Clone("SuSav2PlotClone"));
	TH1D* G2018PlotClone = (TH1D*)(Plots[2]->Clone("G2018PlotClone"));

	TH1D* QEPlotClone = (TH1D*)(BreakDownPlots[0]->Clone("QEPlotClone"));
	TH1D* MECPlotClone = (TH1D*)(BreakDownPlots[1]->Clone("MECPlotClone"));
	TH1D* RESPlotClone = (TH1D*)(BreakDownPlots[2]->Clone("RESPlotClone"));
	TH1D* DISPlotClone = (TH1D*)(BreakDownPlots[3]->Clone("DISPlotClone"));

	// ---------------------------------------

	TString PadName = "ZoomInPad";
	TPad* padZoomIn = new TPad(PadName,PadName,PadNDCXmin,PadNDCYmin,PadNDCXmax,PadNDCYmax,21); 
	padZoomIn->SetFillColor(kWhite); 
	padZoomIn->SetFrameLineWidth(3);
	padZoomIn->Draw();
	padZoomIn->SetTopMargin(0.005);
	padZoomIn->SetBottomMargin(PadBottomMargin);
	padZoomIn->SetLeftMargin(PadLeftMargin);
	padZoomIn->SetRightMargin(PadRightMargin);
	padZoomIn->SetFillStyle(4000); // make pad trasnparent
	padZoomIn->cd();

	// ---------------------------------------------------------------

	auto frame = PlotCanvas->DrawFrame(Xmin,Ymin,Xmax,Ymax);

	frame->GetXaxis()->SetNdivisions(4);
//	frame->GetXaxis()->SetLabelSize(0.1);
	frame->GetXaxis()->SetLabelSize(0.);
	frame->GetXaxis()->SetLabelFont(FontStyle);
	frame->GetXaxis()->SetTickSize(0.1);

	frame->GetYaxis()->SetNdivisions(5);
	frame->GetYaxis()->SetLabelSize(0.15);
	frame->GetYaxis()->SetLabelFont(FontStyle);
	frame->GetYaxis()->SetLabelOffset(-0.1);
	frame->GetYaxis()->SetTickSize(-0.02);

	DataPlotClone->GetYaxis()->SetNdivisions(4);
	DataPlotClone->GetYaxis()->SetLabelOffset(0.1);
	DataPlotClone->Draw("e same");

	G2018PlotClone->Draw("c hist same");
	SuSav2PlotClone->Draw("c hist same");
	QEPlotClone->Draw("c hist same");
	MECPlotClone->Draw("c hist same");
	RESPlotClone->Draw("c hist same");
	DISPlotClone->Draw("c hist same");

	DataPlotClone->Draw("e same");

	gPad->RedrawAxis();

}

// -----------------------------------------------------------------------------------------------------------------------------------

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
				latexXTitle.DrawLatexNDC(0.3,0.5,"(e,e'p)_{1p0#pi} E_{cal} [GeV]");

				// -----------------------------------------------------------------------------------------

				// Extra pad for the common title over the 3 pads

				PlotCanvas->cd();
				TPad* padTitle = new TPad("padTitle","padTitle",0.,0.2,LeftMargin*0.6,1., 21); 
				padTitle->SetFillColor(kWhite); 
				padTitle->Draw();
				padTitle->cd();

				TLatex latexYTitle;
				latexYTitle.SetTextFont(FontStyle);
				latexYTitle.SetTextSize(3*TextSize);
				latexYTitle.SetTextColor(kBlack);
				latexYTitle.SetTextAngle(90);
				latexYTitle.DrawLatexNDC(0.59,0.27,"#frac{d#sigma}{dE^{cal}} #left[#frac{#mub}{GeV}#right]");

				// --------------------------------------------------------------------------------------------

				// Pads to get rid of some 0's on the axes

//				PlotCanvas->cd();
//				TPad* padWhite1 = new TPad("padWhite1","padWhite1",0.06,0.67,0.105,0.72, 21); 
//				padWhite1->SetFillColor(kWhite); 
//				padWhite1->SetFillColor(kBlack); 
//				padWhite1->Draw();
//				padWhite1->cd();

//				PlotCanvas->cd();
//				TPad* padWhite2 = new TPad("padWhite2","padWhite2",0.06,0.4,0.105,0.45, 21); 
//				padWhite2->SetFillColor(kWhite); 
//				padWhite2->SetFillColor(kBlack);
//				padWhite2->Draw();
//				padWhite2->cd();				

				// ------------------------------------------------------------------------------------------------

				TString ext = "";
				if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

				PlotCanvas->SaveAs("../../../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"
					+E[WhichEnergy]+"/"+ext+"Fig3b_"+nucleus[WhichNucleus]+"_" 
					+E[WhichEnergy]+"_SuSav2_AccCorrXSec.pdf");

				//delete PlotCanvas;

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
