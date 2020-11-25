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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include  "../Secondary_Code/CenterAxisTitle.cpp"
#include "../Secondary_Code/SetOffsetAndSize.cpp"
#include "../Secondary_Code/ToString.cpp"

// -------------------------------------------------------------------------------------------------------------

void Create2DPlots_FitOutline_Proton() {

	int FontStyle = 132;
	double TextSize = 0.08;
	const int n = 500; const double min = 0., max = 5.;

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t"); SetOffsetAndSize();

	// -------------------------------------------------------------------------------------------------------------

	TString YLabelOfPlots = "#theta_{p}";
	TString XLabelOfPlots = "P_{p} [GeV/c]";
	TString PlotName = "h2_Proton_Theta_Momentum";

	// -------------------------------------------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots;
	std::vector<TString> Title; 
	std::vector<int> IntSector;

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV");
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV");
	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");

	xBCut.push_back("NoxBCut");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("True 1p0pi W/");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	NameOfPlots.push_back(PlotName+"_FirstSector"); Title.push_back(" (1st Sector)"); IntSector.push_back(3);
//	NameOfPlots.push_back(PlotName+"_SecondSector"); Title.push_back(" (2nd Sector)"); IntSector.push_back(4);
//	NameOfPlots.push_back(PlotName+"_ThirdSector"); Title.push_back(" (3rd Sector)"); IntSector.push_back(5);
//	NameOfPlots.push_back(PlotName+"_FourthSector"); Title.push_back(" (4th Sector)"); IntSector.push_back(0);
//	NameOfPlots.push_back(PlotName+"_FifthSector"); Title.push_back(" (5th Sector)"); IntSector.push_back(1);
//	NameOfPlots.push_back(PlotName+"_SixthSector"); Title.push_back(" (6th Sector)"); IntSector.push_back(2);

	// ---------------------------------------------------------------------------------------------------------------------------------------------------

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// ---------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				if (nucleus[WhichNucleus] == "4He" && E[WhichEnergy] == "1_161") { continue; }
				if (nucleus[WhichNucleus] == "56Fe" && E[WhichEnergy] == "1_161") { continue; }

				// Loop over the plots

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

					TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut];

					TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,2024,768);

					// ---------------------------------------------------------------------------------------------------------------------------

					// Dimensions of TPads (pad2 will be deleted at the very end for the Ereco plots)

					double XMinPadOne = 0., XMaxPadOne = 0.5, YMinPadOne = 0., YMaxPadOne = 1.;
					double XMinPadTwo = 0.5, XMaxPadTwo = 1., YMinPadTwo = 0., YMaxPadTwo = YMaxPadOne;
					double XMinPadThree = 0.5, XMaxPadThree = 0.53, YMinPadThree = 0.07, YMaxPadThree = 0.17;
					double XMinPadFour = 0.2, XMaxPadFour = 0.8, YMinPadFour = 0.91, YMaxPadFour = 1.;

					// ---------------------------------------------------------------------------------------------------------------------------

					TPad* pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadOne,YMinPadOne,XMaxPadOne,YMaxPadOne, 21); 
					pad1->SetFillColor(kWhite); pad1->Draw();
					TPad* pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadTwo,YMinPadTwo,XMaxPadTwo,YMaxPadTwo,22); 
					pad2->SetFillColor(kWhite); pad2->Draw(); 
					TPad* pad3 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadThree,YMinPadThree,XMaxPadThree,YMaxPadThree,23); 
					pad3->SetFillColor(kWhite); pad3->Draw();
					TPad* pad4 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],XMinPadFour,YMinPadFour,XMaxPadFour,YMaxPadFour,24); 
					pad4->SetFillColor(kWhite); pad4->Draw();
					pad1->SetBottomMargin(0.18);
					pad2->SetBottomMargin(0.18);

					pad4->cd();
					TLatex *title = new TLatex(); 
					title->SetNDC();
					title->SetTextFont(FontStyle); 
					title->SetTextColor(kBlack); 
					title->SetTextSize(0.8);
					TString myTitle = LabelsOfSamples[WhichNucleus] + " " +LabelE[WhichEnergy]+Title[WhichPlot];
					title->DrawLatex(0.2,0.3,myTitle);

					// ---------------------------------------------------------------------------------------------------------------------------

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						if (WhichFSIModel == 0) 
							{ pad1->cd(); gStyle->SetTitleSize(TextSize,"t"); pad1->SetRightMargin(0.); pad1->SetLeftMargin(0.15); }
						else { pad2->cd(); pad2->SetLeftMargin(0.0); pad2->SetRightMargin(0.15); }

						TString PathToFiles = "../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						TH2D* Plots =  (TH2D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) ;

						CenterAxisTitle(Plots);
						Plots->SetTitleSize(TextSize,"t");
						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { gStyle->SetTitleX(.54); }
						else { gStyle->SetTitleX(.47); }

						Plots->GetXaxis()->SetLabelFont(FontStyle);
						Plots->GetXaxis()->SetTitleFont(FontStyle);
						Plots->GetXaxis()->SetLabelSize(TextSize);
						Plots->GetXaxis()->SetTitleSize(TextSize);
						Plots->GetXaxis()->SetTitleOffset(1.);
						Plots->GetXaxis()->SetTitle(XLabelOfPlots);

						Plots->GetYaxis()->SetLabelFont(FontStyle);
						Plots->GetYaxis()->SetTitleFont(FontStyle);
						Plots->GetYaxis()->SetLabelSize(TextSize);
						Plots->GetYaxis()->SetTitleSize(TextSize);
						Plots->GetYaxis()->SetTitleOffset(0.8);
						Plots->GetYaxis()->SetTitle(YLabelOfPlots);

						// -----------------------------------------------------------------------------------------------------------------------------

						// Max

						Plots->GetZaxis()->SetRangeUser(1.,Plots->GetMaximum());
						double ScalingFactor = 1. / Plots->GetMaximum();
						Plots->Scale(ScalingFactor);
						Plots->GetZaxis()->SetLabelSize(TextSize);
						Plots->GetZaxis()->SetLabelFont(FontStyle);
						Plots->GetZaxis()->SetTitle("Weighted Events");
						Plots->GetZaxis()->CenterTitle();
						Plots->GetZaxis()->SetTitleFont(FontStyle);
						Plots->GetZaxis()->SetTitleSize(TextSize);

						Plots->GetXaxis()->SetNdivisions(5);
						Plots->GetYaxis()->SetNdivisions(5);

						// -----------------------------------------------------------------------------------------------------------------------------

						// Rebinning & Ranges

						double XMin =-99.,XMax =-99.;
						double YMin =-99.,YMax =-99.;

						for (int i = 0; i < 1; i ++) { Plots->Rebin2D(); }
						YMin = 5; YMax = 140; Plots->GetYaxis()->SetRangeUser(YMin,YMax);

						if (E[WhichEnergy] == "1_161") { XMin = 0.0; XMax = 1.; Plots->GetXaxis()->SetRangeUser(XMin,XMax); }
						if (E[WhichEnergy] == "2_261") { XMin = 0.; XMax = 2.5; Plots->GetXaxis()->SetRangeUser(XMin,XMax); }
						if (E[WhichEnergy] == "4_461") { XMin = 0.; XMax = 4.4; Plots->GetXaxis()->SetRangeUser(XMin,XMax); }

						Plots->Draw("colt");
						PlotCanvas->Update();

						// ----------------------------------------------------------------------------------------------------------------

						// TLines & TLatex

						TLatex *sample = new TLatex(); 
						sample->SetTextFont(FontStyle); 
						sample->SetTextColor(kBlack); 
						sample->SetTextSize(TextSize);
						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { sample->DrawTextNDC(0.4,0.84,FSILabel[WhichFSIModel]); }
						else { sample->DrawTextNDC(0.25,0.84,FSILabel[WhichFSIModel]); } 

						// ----------------------------------------------------------------------------------------------------------------

						if (E[WhichEnergy] == "1_161") {

							TF1* f = new TF1("f","10.+2./TMath::Power(x,1.)",0,5.);
							f->SetLineWidth(3);
							f->SetLineColor(kGreen);
							//f->Draw("same");

							TF1* f2 = new TF1("f2","12",0,5.);
							f2->SetLineWidth(3);
							f2->SetLineColor(kRed);
							f2->Draw("same");

						}

						if (E[WhichEnergy] == "2_261") {

							TF1* f = new TF1("f","11.+1/TMath::Power(x,1.)",0,5.);
							f->SetLineWidth(3);
							f->SetLineColor(kGreen);
							//f->Draw("same");

							TF1* f2 = new TF1("f2","12",0,5.);
							f2->SetLineWidth(3);
							f2->SetLineColor(kRed);
							f2->Draw("same");

						}

						if (E[WhichEnergy] == "4_461") {

							TF1* f = new TF1("f","11.+2/TMath::Power(x,1.)",0,5.);
							f->SetLineWidth(3);
							f->SetLineColor(kGreen);
							//f->Draw("same");

							TF1* f2 = new TF1("f2","12",0,5.);
							f2->SetLineWidth(3);
							f2->SetLineColor(kRed);
							f2->Draw("same");
							
						}
				
						// ----------------------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

				} // End of the loop over the plots

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
