#include <TFile.h>
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
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

void Reweight(TH1D* h, double SF) {

	int NBins = h->GetXaxis()->GetNbins();

	for (int i = 0; i < NBins; i++) {

		double CurrentEntry = h->GetBinContent(i+1);
		double NewEntry = CurrentEntry * SF / h->GetBinWidth(i+1);

		double CurrentError = h->GetBinError(i+1);
		double NewError = CurrentError * SF / h->GetBinWidth(i+1);

		h->SetBinContent(i+1,NewEntry); 
//		h->SetBinError(i+1,NewError); 
		h->SetBinError(i+1,0.000001); 

	}

}

void THStackFluxes() {

	// -------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(3);
	//TGaxis::SetExponentOffset(-0.1, 1., "y");

	int Ndivisions = 4;
	int FontStyle = 132;
	double TextSize = 0.08;
//	int NBreakDown = 5;
	int NBreakDown = 4; // leaving COH out for now

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t");

//	const std::vector<int> Colors{610,410,kRed+1,kGreen+3,kBlue};
//	const std::vector<int> Colors{kBlue-4,kOrange+1,kRed+1,kGreen+3,610};
//	const std::vector<int> Colors{kBlue-5,kYellow+1,kOrange+7,kGray,kBlue};
//	const std::vector<int> Colors{kBlue-5,410,kOrange+7,kRed+1,kBlue}; // not happy
	const std::vector<int> Colors{kBlue-5,kYellow+1,kOrange+7,kRed+1,kBlue};

	// -----------------------------------------------------------------------------------------------------------------------------------

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
//	nucleus.push_back("C12"); LabelsOfSamples.push_back("^{12}C");
	nucleus.push_back("40Ar"); LabelsOfSamples.push_back("^{40}Ar");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

//	E.push_back("1161"); LabelE.push_back(" @ E = 1.161 GeV");
//	E.push_back("2261"); LabelE.push_back(" @ E = 2.261 GeV");
//	E.push_back("4461"); LabelE.push_back(" @ E = 4.461 GeV");

	E.push_back("uBFlux"); LabelE.push_back(" BNB Flux"); YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-39} #frac{cm^{2}}{GeV Ar}#right]");
	E.push_back("DUNEFlux"); LabelE.push_back(" DUNE Flux"); YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-39} #frac{cm^{2}}{GeV Ar}#right]");
	E.push_back("NovaFlux"); LabelE.push_back(" NOvA Flux");  YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-39} #frac{cm^{2}}{GeV CH2}#right]");
	E.push_back("T2KFlux"); LabelE.push_back(" T2K Flux");  YLabelOfPlots.push_back("#frac{d#sigma}{dE_{#nu}} #left[10^{-39} #frac{cm^{2}}{GeV CH}#right]");			

	FSIModel.push_back("GTEST19_10b_00_000_CCinclMEC");FSILabel.push_back("SuSav2");
	FSIModel.push_back("G18_10a_02_11a_CCinclMEC");FSILabel.push_back("G2018");
	FSIModel.push_back("G18_02a_00_000_CCinclMEC");FSILabel.push_back("G18_02a");	

//	FSIModel.push_back("GTEST19_10b_00_000_EM+MEC");FSILabel.push_back("e SuSav2");
//	FSIModel.push_back("G18_10a_02_11a_EM+MEC");FSILabel.push_back("e G2018");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	NameOfPlots.push_back("EvPlot"); XLabelOfPlots.push_back("E_{#nu} [GeV]"); OutputPlotNames.push_back("EvPlot");

	// --------------------------------------------------------------------------------------------------------------------------------
	
	std::vector<TString> ProcessLabel = {"QE","MEC","RES","DIS","COH"}; 
	
	// --------------------------------------------------------------------------------------------------------------------------------	

	// 10^{-38} cm^2 / nucleus

	static std::map<TString,double> GENIEXSec =
	{
		{ "uB_GTEST19_10b_00_000", 0.321417},
		{ "uB_G18_10a_02_11a", 0.273469},
		{ "uB_G18_02a_00_000", 0.30599},
		{ "DUNE_GTEST19_10b_00_000", 0.860894},
		{ "DUNE_G18_10a_02_11a", 0.778348},
		{ "DUNE_G18_02a_00_000", 0.833582},
		{ "Nova_GTEST19_10b_00_000", 0.31159240},
		{ "Nova_G18_10a_02_11a", 0.27670760},
		{ "Nova_G18_02a_00_000", 0.30358940},
		{ "T2K_GTEST19_10b_00_000", 0.92115570},
		{ "T2K_G18_10a_02_11a", 0.75945490},
		{ "T2K_G18_02a_00_000", 0.90182870},
	};

	static std::map<TString,double> GENIEEvents =
	{
		{ "uB_GTEST19_10b_00_000", 3800000},
		{ "uB_G18_10a_02_11a", 2400000},
		{ "uB_G18_02a_00_000", 4000000},
		{ "DUNE_GTEST19_10b_00_000", 3400000},
		{ "DUNE_G18_10a_02_11a", 4000000},
		{ "DUNE_G18_02a_00_000", 4000000},
		{ "Nova_GTEST19_10b_00_000", 4000000},
		{ "Nova_G18_10a_02_11a", 4000000},
		{ "Nova_G18_02a_00_000", 3800000},
		{ "T2K_GTEST19_10b_00_000", 3800000},
		{ "T2K_G18_10a_02_11a", 4000000},
		{ "T2K_G18_02a_00_000", 4000000},
	};

	// --------------------------------------------------------------------------------------------------------------------------------	

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// Loop over the energies

	for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

		// Loop over the nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			if (E[WhichEnergy] == "NovaFlux" || E[WhichEnergy] == "T2KFlux") { nucleus[0] = "C12"; }

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot];
				TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,2624,768);

				// ---------------------------------------------------------------------------------------------------------------------------

				TPad* pad1 = nullptr;
				TPad* pad2 = nullptr;
				TPad* pad3 = nullptr;

				if (NFSIModels == 2) {

					pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0,0,0.5,1., 21); 
					pad1->SetFillColor(kWhite); pad1->Draw();
					pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.5,0,1.,1,22); 
					pad2->SetFillColor(kWhite); pad2->Draw(); 
					pad1->SetBottomMargin(0.18);
					pad2->SetBottomMargin(0.18);
				
				}
				
				if (NFSIModels == 3) {

					pad1 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.06,0,0.38,1.,21); 
					pad1->SetFillColor(kWhite); pad1->Draw();
					pad2 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.38,0,0.69,1,22); 
					pad2->SetFillColor(kWhite); pad2->Draw(); 
					pad3 = new TPad(NameOfPlots[WhichPlot],NameOfPlots[WhichPlot],0.69,0,1.,1,22); 
					pad3->SetFillColor(kWhite); pad3->Draw(); 					
					pad1->SetBottomMargin(0.18);
					pad2->SetBottomMargin(0.18);
					pad3->SetBottomMargin(0.18);					
				
				}				

				// --------------------------------------------------------------------------------------------------

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					if (WhichFSIModel == 0) 
						{ pad1->cd(); gStyle->SetTitleSize(TextSize,"t"); pad1->SetRightMargin(0.); pad1->SetLeftMargin(0.1); pad1->SetTitle("");}
					if (WhichFSIModel == 1)  { pad2->cd(); pad2->SetLeftMargin(0.0); pad2->SetRightMargin(0.0); }
					
					if (WhichFSIModel == 2)  { pad3->cd(); pad3->SetLeftMargin(0.0); pad3->SetRightMargin(0.04); }

					THStack* THStacks = new THStack(NameOfPlots[WhichPlot]+"_"+FSIModel[WhichFSIModel],"");

					// The files are located under 
					// scp apapadop@geniegpvm02.fnal.gov:/genie/app/users/apapadop/True1p0piElectronNeutrinoComparisons/myFiles/*Flux*.root ./myFiles/

					TString PathToFiles = "myFiles/";
					TFile* FileSample = TFile::Open(PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+".root");

					TH1D* Plots[NBreakDown];
					
					TLegend* leg = new TLegend(0.6,0.67,0.95,0.8);
					leg->SetNColumns(2);

					for (int WhichInteraction = 0; WhichInteraction < NBreakDown; WhichInteraction++) {

						Plots[WhichInteraction] =  (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]+"_Interaction_"+ToStringInt(WhichInteraction) ) ) ;

						double Weight = 1.;

						if ( E[WhichEnergy] == "uBFlux" && FSIModel[WhichFSIModel] == "GTEST19_10b_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["uB_GTEST19_10b_00_000"] / GENIEEvents["uB_GTEST19_10b_00_000"]; }
						if ( E[WhichEnergy] == "uBFlux" && FSIModel[WhichFSIModel] == "G18_10a_02_11a_CCinclMEC" ) 
							{ Weight = GENIEXSec["uB_G18_10a_02_11a"] / GENIEEvents["uB_G18_10a_02_11a"]; }
						if ( E[WhichEnergy] == "uBFlux" && FSIModel[WhichFSIModel] == "G18_02a_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["uB_G18_10a_02_11a"] / GENIEEvents["uB_G18_02a_00_000"]; }

						if ( E[WhichEnergy] == "DUNEFlux" && FSIModel[WhichFSIModel] == "GTEST19_10b_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["DUNE_GTEST19_10b_00_000"] / GENIEEvents["DUNE_GTEST19_10b_00_000"]; }
						if ( E[WhichEnergy] == "DUNEFlux" && FSIModel[WhichFSIModel] == "G18_10a_02_11a_CCinclMEC" ) 
							{ Weight = GENIEXSec["DUNE_G18_10a_02_11a"] / GENIEEvents["DUNE_G18_10a_02_11a"]; }
						if ( E[WhichEnergy] == "DUNEFlux" && FSIModel[WhichFSIModel] == "G18_02a_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["DUNE_G18_10a_02_11a"] / GENIEEvents["DUNE_G18_02a_00_000"]; }

						if ( E[WhichEnergy] == "NovaFlux" && FSIModel[WhichFSIModel] == "GTEST19_10b_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["Nova_GTEST19_10b_00_000"] / GENIEEvents["Nova_GTEST19_10b_00_000"]; }
						if ( E[WhichEnergy] == "NovaFlux" && FSIModel[WhichFSIModel] == "G18_10a_02_11a_CCinclMEC" ) 
							{ Weight = GENIEXSec["Nova_G18_10a_02_11a"] / GENIEEvents["Nova_G18_10a_02_11a"]; }
						if ( E[WhichEnergy] == "NovaFlux" && FSIModel[WhichFSIModel] == "G18_02a_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["Nova_G18_10a_02_11a"] / GENIEEvents["Nova_G18_02a_00_000"]; }

						if ( E[WhichEnergy] == "T2KFlux" && FSIModel[WhichFSIModel] == "GTEST19_10b_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["T2K_GTEST19_10b_00_000"] / GENIEEvents["T2K_GTEST19_10b_00_000"]; }
						if ( E[WhichEnergy] == "T2KFlux" && FSIModel[WhichFSIModel] == "G18_10a_02_11a_CCinclMEC" ) 
							{ Weight = GENIEXSec["T2K_G18_10a_02_11a"] / GENIEEvents["T2K_G18_10a_02_11a"]; }
						if ( E[WhichEnergy] == "T2KFlux" && FSIModel[WhichFSIModel] == "G18_02a_00_000_CCinclMEC" ) 
							{ Weight = GENIEXSec["T2K_G18_10a_02_11a"] / GENIEEvents["T2K_G18_02a_00_000"]; }

						//std::cout << "XSec = " << GENIEXSec["ub_G18_10a_02_11a"] << ",  Events = " << GENIEEvents["uB_G18_10a_02_11a"] << std::endl;
						//std::cout << "XSec Weight = " << Weight << std::endl;
						Reweight(Plots[WhichInteraction],10*Weight); // that explains the 10^-39 cm^2 units

						Plots[WhichInteraction]->GetXaxis()->CenterTitle();
						Plots[WhichInteraction]->GetXaxis()->SetLabelFont(FontStyle);
						Plots[WhichInteraction]->GetXaxis()->SetTitleFont(FontStyle);
						Plots[WhichInteraction]->GetXaxis()->SetLabelSize(TextSize);

						if (FSIModel[WhichFSIModel] == "G18_10a_02_11a_CCinclMEC") { Plots[WhichInteraction]->GetXaxis()->SetTitleSize(TextSize); }
						else { Plots[WhichInteraction]->GetXaxis()->SetTitleSize(0); }

						Plots[WhichInteraction]->GetXaxis()->SetTitleOffset(1.);
						Plots[WhichInteraction]->GetXaxis()->SetTitle(XLabelOfPlots[WhichPlot]);
						Plots[WhichInteraction]->GetXaxis()->SetNdivisions(6);
						Plots[WhichInteraction]->GetXaxis()->SetTickSize(0.01);

						Plots[WhichInteraction]->GetYaxis()->CenterTitle();
						Plots[WhichInteraction]->GetYaxis()->SetLabelFont(FontStyle);
						Plots[WhichInteraction]->GetYaxis()->SetTitleFont(FontStyle);
						Plots[WhichInteraction]->GetYaxis()->SetLabelSize(TextSize);
						Plots[WhichInteraction]->GetYaxis()->SetLabelOffset(0.01);
						Plots[WhichInteraction]->GetYaxis()->SetTitleSize(TextSize);
						//Plots[WhichInteraction]->GetYaxis()->SetTitleOffset(1.35);
						//Plots[WhichInteraction]->GetYaxis()->SetTitle(YLabelOfPlots[WhichEnergy]);
						Plots[WhichInteraction]->GetYaxis()->SetNdivisions(5);
						Plots[WhichInteraction]->GetYaxis()->SetTickSize(0.02);

						Plots[WhichInteraction]->SetLineColor(Colors[WhichInteraction]);
						Plots[WhichInteraction]->SetFillColor(Colors[WhichInteraction]);
						//Plots[WhichInteraction]->SetFillStyle(3004);
						Plots[WhichInteraction]->SetLineWidth(1);

						Plots[WhichInteraction]->GetXaxis()->SetRangeUser(0.15,9.);
						//Plots[WhichInteraction]->GetYaxis()->SetRangeUser(0.,9*TMath::Power(10.,5.));
						Plots[WhichInteraction]->GetYaxis()->SetRangeUser(0.,3.1);
						
						if (E[WhichEnergy] == "uBFlux") { Plots[WhichInteraction]->GetXaxis()->SetRangeUser(0.2,2.7); }
						if (E[WhichEnergy] == "DUNEFlux") { 
							Plots[WhichInteraction]->GetXaxis()->SetRangeUser(0.3,5.3); 
							Plots[WhichInteraction]->GetYaxis()->SetRangeUser(0.,4.1); 
						}
						if (E[WhichEnergy] == "T2KFlux") { 
							Plots[WhichInteraction]->GetXaxis()->SetRangeUser(0.3,5.3); 
							Plots[WhichInteraction]->GetYaxis()->SetRangeUser(0.,13); 
						}
						if (E[WhichEnergy] == "NovaFlux") { 
							Plots[WhichInteraction]->GetXaxis()->SetRangeUser(0.6,4.9);
							Plots[WhichInteraction]->GetYaxis()->SetRangeUser(0.,2.1); 
						}

						Plots[WhichInteraction]->Draw("hist same");
						THStacks->Add(Plots[WhichInteraction],"hist");
						THStacks->Draw("hist same");
						
						TLegendEntry* lEntry = leg->AddEntry(Plots[WhichInteraction],ProcessLabel[WhichInteraction], "");
						lEntry->SetTextColor(Colors[WhichInteraction]);
		

					}

					// -------------------------------------------------------------------------------------------

					// Rebinning & Ranges

					// -------------------------------------------------------------------------------------------------------
					
					leg->SetBorderSize(0);
					leg->SetTextFont(FontStyle);
					leg->SetTextSize(TextSize);

					TLatex *sample = new TLatex(); 
					sample->SetTextFont(FontStyle); 
					sample->SetTextColor(kBlack); 
					sample->SetTextSize(TextSize);
					if (WhichFSIModel == 0) { 
					
						sample->DrawLatexNDC(0.64,0.84,FSILabel[WhichFSIModel]); 
						leg->Draw(); 
					
					}
					else { sample->DrawLatexNDC(0.45,0.84,FSILabel[WhichFSIModel]); }
					
					if (WhichFSIModel == 1) {
					
						TLatex *flux = new TLatex(); 
						flux->SetTextFont(FontStyle); 
						flux->SetTextColor(kBlack); 
						flux->SetTextSize(TextSize);
						flux->DrawLatexNDC(0.6,0.64,LabelE[WhichEnergy]);
					
					}

					gPad->RedrawAxis();

					PlotCanvas->cd();
					TPad* padTitle = new TPad("padTitle","padTitle",0.,0.,0.05,1., 21); 
					padTitle->SetFillColor(kWhite); 
					padTitle->Draw();
					padTitle->cd();

					TLatex latexYTitle;
					latexYTitle.SetTextFont(FontStyle);
					latexYTitle.SetTextSize(6*TextSize);
					latexYTitle.SetTextColor(kBlack);
					latexYTitle.SetTextAngle(90);
					latexYTitle.DrawLatexNDC(0.66,0.2,YLabelOfPlots[WhichEnergy]);

					//delete PlotCanvas;

				} // End of the loop over the FSI Models 

				PlotCanvas->SaveAs("myPlots/"+E[WhichEnergy]+".pdf");

				//delete PlotCanvas;

			} // End of the loop over the plots

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
