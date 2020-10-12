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

#include  "/home/afroditi/Dropbox/PhD/Secondary_Code/CenterAxisTitle.cpp"
#include "/home/afroditi/Dropbox/PhD/Secondary_Code/SetOffsetAndSize.cpp"
//#include "/home/afroditi/Dropbox/PhD/Secondary_Code/ToString.cpp"
#include "/home/afroditi/Dropbox/PhD/Secondary_Code/myFunctions.cpp"

// ----------------------------------------------------------------------------------------------------------------

// Accounting for the fact that the bin width is not constant

void ReweightPlots(TH1D* h) {

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
		double content = h->GetBinContent(i);
		double error = h->GetBinError(i);
		double width = h->GetBinWidth(i);
		double newcontent = content / width;
		double newerror = error / width;				
		h->SetBinContent(i,newcontent);
		h->SetBinError(i,newerror);

	}

}

// ----------------------------------------------------------------------------------------------------------------

void ApplySystUnc(TH1D* h, double systunc) {

	double NBins = h->GetNbinsX(); 
				
	for (int i = 1; i <= NBins; i++) { 
					
		double error = h->GetBinError(i);
		double newerror = error * (1. + systunc);
		h->SetBinError(i,newerror);

	}

}

// ----------------------------------------------------------------------------------------------------------------

void AbsXSec_OverlayEQE_Fig2() {

	// ------------------------------------------------------------------------

	SetOffsetAndSize();
	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	int Ndivisions = 6;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.08;
	
	TString version = "v3_0_6/";

	// From Mariana's analysis note

	double SystUnc1GeV = 0.02; // 2% syst uncertainty at 1.161 GeV
	double SystUnc2GeV = 0.021; // 2.1% syst uncertainty at 2.261 GeV
	double SystUnc4GeV = 0.047; // 4.7% syst uncertainty at 4.461 GeV

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;  std::vector<int> BreakDownColors;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");

	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV"); DoubleE.push_back(1.161);
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV"); DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
 
	Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);

	Style.push_back(1); Style.push_back(1); Style.push_back(1); Style.push_back(1);

	BreakDownColors.push_back(kBlue); BreakDownColors.push_back(429); BreakDownColors.push_back(410); BreakDownColors.push_back(610);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Data");
//	FSIModel.push_back("Data_Final"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("GoodRunList_Data_Final"); FSILabel.push_back("GRLData"); DirNames.push_back("GRLData");

//	FSIModel.push_back("SuSav2_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("SuSav2_NoRadCorr");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("SuSav2_NoRadCorr");	
	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");  DirNames.push_back("hA2018_Truth_NoRadCorr");

	NameOfPlots.push_back("h_Erec_subtruct_piplpimi_noprot_3pi"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]");  OutputPlotNames.push_back("InclusiveeRecoEnergy_slice_0");
//	NameOfPlots.push_back("h1_EQE_SuperFine"); LabelOfPlots.push_back("(e,e')_{0#pi} E^{QE} [GeV]");  OutputPlotNames.push_back("InclusiveeRecoEnergy_slice_0");

	std::vector<TH1D*> Plots;
//	std::vector<TGraphAsymmErrors*> UncertaintyPlots;
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

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// Pinned Data
	std::map<std::pair<TString,TString>,double> PinnedDataSF =
	{
		{ std::make_pair("4He", "2_261"), 1.7*TMath::Power(10.,-7.) },
		{ std::make_pair("4He", "4_461"), 2.03*TMath::Power(10.,-7.) },
		{ std::make_pair("12C", "1_161"), 2.27*TMath::Power(10.,-5.) },
		{ std::make_pair("12C", "2_261"), 6.32*TMath::Power(10.,-7.) },
		{ std::make_pair("12C", "4_461"), 7.75*TMath::Power(10.,-7.) },
		{ std::make_pair("56Fe", "2_261"), 5.82*TMath::Power(10.,-5.) },
		{ std::make_pair("56Fe", "4_461"), 4.1*TMath::Power(10.,-5.) }
	};

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// Data
	std::map<std::pair<TString,TString>,double> DataSF =
	{
		{ std::make_pair("4He", "2_261"), 1.84*TMath::Power(10.,-7.) },
		{ std::make_pair("4He", "4_461"), 2.28*TMath::Power(10.,-7.) },
		{ std::make_pair("12C", "1_161"), 2.27*TMath::Power(10.,-5.) },
		{ std::make_pair("12C", "2_261"), 1.0*TMath::Power(10.,-6.) },
		{ std::make_pair("12C", "4_461"), 8.37*TMath::Power(10.,-7.) },
		{ std::make_pair("56Fe", "2_261"), 5.75*TMath::Power(10.,-5.) },
		{ std::make_pair("56Fe", "4_461"), 4.36*TMath::Power(10.,-5.) }
	};

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// GRL Data
	std::map<std::pair<TString,TString>,double> GRLDataSF =
	{
		{ std::make_pair("4He", "2_261"), 1.7*TMath::Power(10.,-7.) },
		{ std::make_pair("4He", "4_461"), 2.03*TMath::Power(10.,-7.) },
		{ std::make_pair("12C", "1_161"), 9.72*TMath::Power(10.,-6.) },
		{ std::make_pair("12C", "2_261"), 2.35*TMath::Power(10.,-4.) },
		{ std::make_pair("12C", "4_461"), 7.75*TMath::Power(10.,-7.) },
		{ std::make_pair("56Fe", "2_261"), 5.82*TMath::Power(10.,-5.) },
		{ std::make_pair("56Fe", "4_461"), 4.1*TMath::Power(10.,-5.) }
	};

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// SuSav2
	std::map<std::pair<TString,TString>,double> SuSav2SF =
	{
		{ std::make_pair("4He", "2_261"), 4.2*TMath::Power(10.,-6.) },
		{ std::make_pair("4He", "4_461"), 1.51*TMath::Power(10.,-6.) },
		{ std::make_pair("12C", "1_161"), 3.25*TMath::Power(10.,-5.) },
		{ std::make_pair("12C", "2_261"), 1.04*TMath::Power(10.,-6.) },
		{ std::make_pair("12C", "4_461"), 4.66*TMath::Power(10.,-7.) },
		{ std::make_pair("56Fe", "2_261"), 6.32*TMath::Power(10.,-6.) },
		{ std::make_pair("56Fe", "4_461"), 2.94*TMath::Power(10.,-6.) }
	};

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// G2018
	std::map<std::pair<TString,TString>,double> G2018SF =
	{
		{ std::make_pair("4He", "2_261"), 3.28*TMath::Power(10.,-6.) },
		{ std::make_pair("4He", "4_461"), 3.04*TMath::Power(10.,-6.) },
		{ std::make_pair("12C", "1_161"), 2.22*TMath::Power(10.,-5.) },
		{ std::make_pair("12C", "2_261"), 8.67*TMath::Power(10.,-7.) },
		{ std::make_pair("12C", "4_461"), 5.46*TMath::Power(10.,-7.) },
		{ std::make_pair("56Fe", "2_261"), 1.8*TMath::Power(10.,-6.) },
		{ std::make_pair("56Fe", "4_461"), 2.51*TMath::Power(10.,-6.) }
	};

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				// Loop over the plots
				
				int LowBin = -1;
				int HighBin = -1;				

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
					pad1->SetBottomMargin(0.23);
					pad1->SetLeftMargin(0.15); 
					pad1->SetRightMargin(0.04);
					pad1->cd();

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					double LegXmin = 0.17, LegYmin = 0.45, YSpread = 0.35;

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

						TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);
						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
						Plots[WhichFSIModel]->SetLineWidth(LineWidth);

						// --------------------------------------------------------------------------------------

						// X-axis label

						Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);
						Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(1.3);
						Plots[WhichFSIModel]->GetXaxis()->SetLabelOffset(0.02);
						Plots[WhichFSIModel]->GetXaxis()->SetTitle(JustNucleus[WhichNucleus]+LabelOfPlots[WhichPlot]);
						
						double LowRange = 0.47;
						double HighRange = 1.4;	

						if (E[WhichEnergy] == "2_261") { LowRange = 0.5; HighRange = 2.8; }
						if (E[WhichEnergy] == "4_461") { LowRange = 1.6; HighRange = 6.; }
					
						Plots[WhichFSIModel]->GetXaxis()->SetRangeUser(LowRange,HighRange);
						
						LowBin = Plots[WhichFSIModel]->GetXaxis()->FindBin(LowRange);
						HighBin = Plots[WhichFSIModel]->GetXaxis()->FindBin(HighRange);						

						// --------------------------------------------------------------------------------------

						// Y-axis label

						Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(TextSize); 
						Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
//						Plots[WhichFSIModel]->GetYaxis()->SetTitle("Weighted Events / GeV");
//						Plots[WhichFSIModel]->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [#frac{#mub}{sr GeV nucleus}]");
						Plots[WhichFSIModel]->GetYaxis()->SetTitle("Weighted Events");

						Plots[WhichFSIModel]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(0.7);

						// --------------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						ReweightPlots(Plots[WhichFSIModel]);

						// -----------------------------------------------------------------------------------

						// Scaling Factor

//						double ScalingFactor = 1. / Plots[WhichFSIModel]->Integral();  // area normalized

						double ScalingFactor = 1.;

						if (FSILabel[WhichFSIModel] == "Pinned Data") { ScalingFactor = PinnedDataSF[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])]; }
						if (FSILabel[WhichFSIModel] == "Data") { ScalingFactor = DataSF[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])]; }
						if (FSILabel[WhichFSIModel] == "GRLData") { ScalingFactor = GRLDataSF[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])]; }
						if (FSILabel[WhichFSIModel] == "SuSav2") { ScalingFactor = SuSav2SF[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])]; }
						if (FSILabel[WhichFSIModel] == "G2018") { ScalingFactor = G2018SF[std::make_pair(nucleus[WhichNucleus], E[WhichEnergy])]; }

						Plots[WhichFSIModel]->Scale(ScalingFactor);

						// ----------------------------------------------------------------------------------

						// Apply Systematic Uncertainties on Data Points

						double SystUnc = 0;
						if ( DoubleE[WhichEnergy] == 1.161 ) { SystUnc = SystUnc1GeV; }
						if ( DoubleE[WhichEnergy] == 2.261 ) { SystUnc = SystUnc2GeV; }
						if ( DoubleE[WhichEnergy] == 4.461 ) { SystUnc = SystUnc4GeV; }

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { ApplySystUnc(Plots[WhichFSIModel], SystUnc); }

						// ----------------------------------------------------------------------------------

						// Genie Break Down

						if (
							FSILabel[WhichFSIModel] == "SuSav2"
						) {

							legGenie->AddEntry(Plots[0],"Data", "lep"); 
							legGenieBlackLine->AddEntry(Plots[0],"Data", "lep"); 

							legGenie->AddEntry(Plots[WhichFSIModel],"SuSav2 (Total)", "l"); 
//							legGenieBlackLine->AddEntry(Plots[WhichFSIModel],"GENIE (Total)", "l"); 
/*
							BreakDownPlots.clear();

							for (int j = 1; j < 5; j++) {

								BreakDownPlots.push_back( (TH1D*)( FileSample->Get("InclusiveEQE_Int_"+ToString(j)) ) ); 

								ReweightPlots(BreakDownPlots[j-1]);

								//-----------------------------------------------------------------------------------------------

								BreakDownPlots[j-1]->SetLineColor(BreakDownColors[j-1]);

								BreakDownPlots[j-1]->SetLineWidth(3);
								BreakDownPlots[j-1]->SetLineStyle(Style[j-1]);
								BreakDownPlots[j-1]->Scale(ScalingFactor);
								TLegendEntry* l1 = legGenie->AddEntry(BreakDownPlots[j-1],GenieFSILabel[j-1], "l");
								l1->SetTextColor(BreakDownColors[j-1]);

								TLegendEntry* l1Break = legGenieBreak->AddEntry(BreakDownPlots[j-1],GenieFSILabel[j-1], "l");
								l1Break->SetTextColor(BreakDownColors[j-1]);

								BreakDownPlots[j-1]->Draw("C hist same");

							} // end of the look over the GENIE break down
*/
						}

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichFSIModel]->GetMaximum();
						if (localmax > max) { max = localmax; }
						double height = 1.05;
						if ( xBCut[WhichxBCut] == "xBCut" ) { height = 1.1; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

						double localmin = Plots[WhichFSIModel]->GetBinContent(Plots[WhichFSIModel]->FindBin(4)); // multiplicity 4 is the highest one in data
						if (localmin < min && localmin != 0) { min = localmin; }

						TString XLabel = Plots[WhichFSIModel]->GetXaxis()->GetTitle();
						Plots[0]->GetXaxis()->SetTitle(XLabel);

						Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(Ndivisions);
						Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions/2);

						// --------------------------------------------------------------------------------------------------

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichFSIModel]->SetMarkerStyle(20); 
							Plots[WhichFSIModel]->SetMarkerSize(2.); 
							Plots[WhichFSIModel]->SetMarkerColor(kBlack); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichFSIModel]->Draw("e same"); 

						} else { 

							if (FSILabel[WhichFSIModel] == "G2018") { Plots[WhichFSIModel]->SetLineStyle(kDashed); }
							Plots[WhichFSIModel]->Draw("C hist same");  // draw them as lines
							
							if (FSILabel[WhichFSIModel] == "SuSav2") 
								{ legGenieBlackLine->AddEntry(Plots[WhichFSIModel],"SuSav2 (Total)", "l"); }
							
							/*UncertaintyPlots[1]->SetMarkerColor(kBlack);	
							UncertaintyPlots[1]->SetLineColor(kBlack);
							UncertaintyPlots[1]->SetFillColor(kBlack);
							UncertaintyPlots[1]->SetFillStyle(3002);
							UncertaintyPlots[1]->SetMarkerSize(2.);
							UncertaintyPlots[1]->SetMarkerStyle(20);
							UncertaintyPlots[1]->Draw("4C same");
							legGenieBlackLine->AddEntry(UncertaintyPlots[1],"GENIE (Total)", "lf"); */

							Plots[0]->Draw("e same"); 

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
					myNucleus->DrawLatexNDC(0.17,0.85,JustNucleus[WhichNucleus]+"(e,e')_{0#pi}");

					TLatex* myEbeam = new TLatex();
					myEbeam->SetTextFont(FontStyle);
					myEbeam->SetTextColor(kAzure+4);
					myEbeam->SetTextSize(TextSize-0.02);
//					myEbeam->DrawLatexNDC(0.72,0.35,"E_{beam}");

					TLatex* myArrow = new TLatex();
					myArrow->SetTextFont(FontStyle);
					myArrow->SetTextColor(kAzure+4);
					myArrow->SetTextSize(1.2*TextSize);
//					myArrow->DrawLatex(1.141,0.1,"#Downarrow");

					// Monitor where 1.161 GeV is
					//TLine* line = new TLine(1.161,0.,1.161,2.);
					//line->Draw();

					// -------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

//					PlotCanvas->SaveAs("../../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"
//						+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
//						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+WhatModelsAreIncluded+"_SuSav2_AbsXSc.pdf");

					//delete PlotCanvas;

					// --------------------------------------------------------------------------------------


				} // End of the loop over the plots
				
				// --------------------------------------------------------------------------------------				
				
				// Chi2 calculation
				
				int NBinsX = HighBin - LowBin +1;
				int Chi2Double = Chi2(Plots[0],Plots[1],LowBin,HighBin);
				
				cout << endl << endl << "SuSav2 Chi2/ndof = " << Chi2Double << " / " << NBinsX << endl << endl;
				
				int G2018Chi2Double = Chi2(Plots[0],Plots[2],LowBin,HighBin);
				
				cout << endl << endl << "G2018 Chi2/ndof = " << G2018Chi2Double << " / " << NBinsX << endl << endl;				
				
				// --------------------------------------------------------------------------------------				

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
