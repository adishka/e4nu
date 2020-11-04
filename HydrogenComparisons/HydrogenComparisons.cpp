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

#include <iostream>
#include <map>
#include <utility>

using namespace std;

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

// ----------------------------------------------------------------------------------------------------------------

double Integrate(TH1D* h) {

	int NBins = h->GetXaxis()->GetNbins();

	double SumEntries = 0;

	for (int i = 0; i < NBins; i++) {

		if (h->GetBinCenter(i+1) >= 0.9 && h->GetBinCenter(i+1) <= 0.95) {
		//if (h->GetBinContent(i+1) > 0) {

		SumEntries += h->GetBinContent(i+1) /** h->GetBinWidth(i+1)*/;
//cout << "h->GetBinContent(i+1) = " << h->GetBinContent(i+1) << endl;
		}

	}

	return SumEntries;

}

// ----------------------------------------------------------------------------------------------------------------

void HydrogenComparisons() {

	// ------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	gStyle->SetTitleSize(TextSize,"t"); 
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetOptStat(0);

	std::vector<TString> xBCut; std::vector<TString> nucleus; std::vector<TString> JustNucleus; std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E; std::vector<double> DoubleE;
	std::vector<TString> LabelE; std::vector<TString> FSIModel; std::vector<TString> DirNames;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;
	std::vector<int> Style;

	// ------------------------------------------------------------------------

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He"); JustNucleus.push_back("He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C"); JustNucleus.push_back("C");
	nucleus.push_back("CH2"); LabelsOfSamples.push_back("CH2"); JustNucleus.push_back("CH2");
//	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");  JustNucleus.push_back("Fe");

	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV"); DoubleE.push_back(1.161);
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV"); DoubleE.push_back(2.261);	
//	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");  DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");
 
//	Colors.push_back(kBlack); Colors.push_back(kRed); Colors.push_back(kBlue); Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);
	Colors.push_back(kBlack); Colors.push_back(610); Colors.push_back(410); Colors.push_back(kMagenta); Colors.push_back(kGreen+3); Colors.push_back(kBlue);  Colors.push_back(610);

//	Style.push_back(9); Style.push_back(3); Style.push_back(7); Style.push_back(5);
//	Style.push_back(9); Style.push_back(9); Style.push_back(9); Style.push_back(9); // fancy dashed lines 
	Style.push_back(1); Style.push_back(kDashed); Style.push_back(1); Style.push_back(1);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");
//	FSIModel.push_back("Pinned_Data_NoRotations"); FSILabel.push_back("Pinned Data No Rotations"); DirNames.push_back("Pinned Data No Rotations");

//	FSIModel.push_back("Data_Final"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("hA2018_Final_NoRadCorr_LFGM"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");  DirNames.push_back("G2018");
//	FSIModel.push_back("SuSav2_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2 NoRad");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("SuSav2");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_NoAccMaps"); FSILabel.push_back("SuSav2_NoAccMaps");  DirNames.push_back("SuSav2_NoAccMaps");

//	FSIModel.push_back("SuSav2_02_11a_NoRadCorr_LFGM"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("Data_Final_FilterRuns"); FSILabel.push_back("Data_FilterRuns"); DirNames.push_back("Data_FilterRuns");
//	FSIModel.push_back("Data_Final_NewFilterRuns"); FSILabel.push_back("Data_NewFilterRuns"); DirNames.push_back("Data_NewFilterRuns");

//	FSIModel.push_back("GoodRunList_Data_Final"); FSILabel.push_back("GoodRunList_Data"); DirNames.push_back("GRL Data");
//	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data"); DirNames.push_back("Pinned Data");
//	FSIModel.push_back("LowCurrent_GoodRunList_Data_Final"); FSILabel.push_back("LowCurrent_GoodRunList_Data"); DirNames.push_back("LC GRL Data");
//	FSIModel.push_back("HighCurrent_GoodRunList_Data_Final"); FSILabel.push_back("HighCurrent_GoodRunList_Data"); DirNames.push_back("HC GRL Data");

//	FSIModel.push_back("Data_Final_NoChargedPions"); FSILabel.push_back("Data"); DirNames.push_back("Data");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_NoChargedPions"); FSILabel.push_back("G2018");  DirNames.push_back("hA2018_Truth_RadCorr");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_NoChargedPions"); FSILabel.push_back("SuSav2");  DirNames.push_back("hA2018_Truth_RadCorr");

//	FSIModel.push_back("hA2018_Final_NoRadCorr"); FSILabel.push_back("Genie");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hA2018_Truth_NoRadCorr"); FSILabel.push_back("Genie (Truth)");  DirNames.push_back("hA2018_Truth_NoRadCorr");
//	FSIModel.push_back("hN2018_Final_NoRadCorr_LFGM"); FSILabel.push_back("Genie hN2018");  DirNames.push_back("hN2018_Truth_NoRadCorr");
//	FSIModel.push_back("hN2018_Final_RadCorr_LFGM"); FSILabel.push_back("Genie hN2018");  DirNames.push_back("hN2018_Truth_NoRadCorr");



//	NameOfPlots.push_back("h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0"); LabelOfPlots.push_back("1st Sector Energy Transfer [GeV]"); OutputPlotNames.push_back("h1_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_0");

//	NameOfPlots.push_back("h1_Q2_weight"); LabelOfPlots.push_back("(e,e') W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
//	NameOfPlots.push_back("h1_Q2_weight"); LabelOfPlots.push_back("(e,e') W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
//	NameOfPlots.push_back("h1_Wvar_weight"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
//	NameOfPlots.push_back("h1_W_weight_ThetaSlice_InAllSectors"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
//	NameOfPlots.push_back("h1_W_weight_ThetaSlice_InSector_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
//	NameOfPlots.push_back("h1_W_weight_FullyInclusive_ThetaSlice_InAllSectors"); LabelOfPlots.push_back("(e,e') W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
	NameOfPlots.push_back("h1_W_weight_FullyInclusive_ThetaSlice_InSector_0"); LabelOfPlots.push_back("1st sector (e,e') W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");
//	NameOfPlots.push_back("h1_W_weight_FullyInclusive_ThetaSlice_InSector_1"); LabelOfPlots.push_back("(e,e') W [GeV]"); OutputPlotNames.push_back("h1_Wvar_weight");


	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// This analysis is cutting on phi +/- 15 deg

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

IntegratedCharge_PinnedFiles[std::make_pair("12C", E[WhichEnergy])] = 0.004843377;

			// Loop over the plots

			for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

				TCanvas* PlotCanvas = new TCanvas(E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
								 E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]+"_"+xBCut[WhichxBCut],
								 205,34,1024,768);

				PlotCanvas->SetBottomMargin(0.2);
				PlotCanvas->SetLeftMargin(0.17);

				// ---------------------------------------------------------------------------------------

				TLegend* leg = leg = new TLegend(0.7,0.73,0.8,0.87);

				leg->SetNColumns(1);

				double max = -99.;
				double min = 1E12;

				double DataIntegral = 1.;
				double SuSav2Integral = 1.;
				double G2018Integral = 1.;

				// Loop over the FSI Models

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					// Loop over the nuclei

					Plots.clear();

					for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

						TString PathToFiles = "mySamples/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

						//UniversalE4vFunction(Plots[WhichNucleus],FSIModelsToLabels[FSIModel[WhichFSIModel]],nucleus[WhichNucleus],E[WhichEnergy],NameOfPlots[WhichPlot]);

						// --------------------------------------------------------------------------------------

						// Make the plot pretty

						Plots[WhichNucleus]->SetLineColor(Colors[WhichNucleus]);
						Plots[WhichNucleus]->SetTitle(FSILabel[WhichFSIModel] + ", " + LabelsOfSamples[WhichNucleus]);
						Plots[WhichNucleus]->GetXaxis()->SetTitle(LabelOfPlots[WhichPlot]);
						PrettyDoubleXSecPlot(Plots[WhichNucleus]);
						Plots[WhichNucleus]->GetYaxis()->SetTitle("# Counts");

						// --------------------------------------------------------------------------------------

						// Scale to obtain absolute double differential cross sections 
						// Use charge, density and length for data samples
						// Use total number of events in genie sample and relevant genie cross sections for simulation

						//AbsoluteXSecScaling(Plots[WhichNucleus],FSILabel[WhichFSIModel],nucleus[WhichNucleus],E[WhichEnergy]);

						// -----------------------------------------------------------------------------------

						// Accounting for the fact that the bin width might not be constant

						//ReweightPlots(Plots[WhichNucleus]);

						// --------------------------------------------------------------------------------------

						// Rebining & ranges

						ApplyRebinning(Plots[WhichNucleus],DoubleE[WhichEnergy],NameOfPlots[WhichPlot]);
						ApplyRange(Plots[WhichNucleus],DoubleE[WhichEnergy],NameOfPlots[WhichPlot]);

						//Plots[WhichNucleus]->Scale(MassNumber[nucleus[WhichNucleus]]);

						// Scaling the 12C plot to the CH2 equivalent

						if (nucleus[WhichNucleus] == "12C") {

							double SF = IntegratedCharge_PinnedFiles[std::make_pair("CH2", E[WhichEnergy])] * (6./7.) * TargetLength[std::make_pair("CH2",E[WhichEnergy])] * TargetDensity[std::make_pair("CH2",E[WhichEnergy])] / (IntegratedCharge_PinnedFiles[std::make_pair("12C", E[WhichEnergy])] * TargetLength[std::make_pair("12C",E[WhichEnergy])] * TargetDensity[std::make_pair("12C",E[WhichEnergy])]);


							Plots[WhichNucleus]->Scale(SF);

						}

						// ---------------------------------------------------------------------------------------------------

						// Max, min, title & # divisions

						double localmax = Plots[WhichNucleus]->GetMaximum();

						if (localmax > max) { max = localmax; }
						double height = 1.1;
						if ( xBCut[WhichxBCut] == "xBCut" ) { height = 1.15; }
						Plots[0]->GetYaxis()->SetRangeUser(0.,height*max);

//						TString XLabel = Plots[WhichNucleus]->GetXaxis()->GetTitle();
//						Plots[0]->GetXaxis()->SetTitle(XLabel);

						// --------------------------------------------------------------------------------------------------

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) { 

							Plots[WhichNucleus]->SetMarkerStyle(20); 
							Plots[WhichNucleus]->SetMarkerSize(2.); 
							Plots[WhichNucleus]->SetMarkerColor(Colors[WhichNucleus]); 

							gStyle->SetErrorX(0); // Removing the horizontal errors
							Plots[WhichNucleus]->Draw("e same"); 

						} else { 

							Plots[WhichNucleus]->SetLineStyle(Style[WhichFSIModel]); 
							Plots[WhichNucleus]->Draw("C hist same");  // draw them as lines
							Plots[0]->Draw("e same"); 

						}

						if (string(FSILabel[WhichFSIModel]).find("Data") != std::string::npos) 
							{ leg->AddEntry(Plots[WhichNucleus],LabelsOfSamples[WhichNucleus], "lep");}
						else { leg->AddEntry(Plots[WhichNucleus],LabelsOfSamples[WhichNucleus], "l"); }
				

		                                // ---------------------------------------------------------------------------------------------------
		                                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the nuclei

					leg->SetBorderSize(0);
					leg->SetTextFont(FontStyle);
					leg->SetTextSize(TextSize);
					leg->Draw(); // Just data + e.g. susav2

					// -----------------------------------------------------------------------------------------------------------------------------------------

					TString ext = "";
					if ( xBCut[WhichxBCut] == "xBCut" ) { ext = "xB_"; } 

//					PlotCanvas->SaveAs("../myPlots/pdf/"+xBCut[WhichxBCut]+"/"+version+nucleus[WhichNucleus]+"/"+E[WhichEnergy]+"/"+ext+nucleus[WhichNucleus]+"_" 
//						+E[WhichEnergy]+"_" +OutputPlotNames[WhichPlot]+".pdf");

					//delete PlotCanvas;

					// -----------------------------------------------------------------------------------------------------------------------------------------

				} // End of the loop over the FSI Models

			} // End of the loop over the plots

			// ----------------------------------------------------------------------------------------------------------------------

			TCanvas* DiffCanvas = new TCanvas("DiffCanvas","DiffCanvas",205,34,1024,768);
			DiffCanvas->SetBottomMargin(0.2);
			DiffCanvas->SetLeftMargin(0.17);

			// ----------------------------------------------------------------------------------------------------------------------

			// Scaling the CH2 integral to the 12C one in the region 0.6 to 0.9

//			double LowRange = 0.6;
//			double HighRange = 0.9;

//			double LowRange = 1.1;
//			double HighRange = 1.4;

			double LowRange = 0.83;
			double HighRange = 0.9;

			int LowBin = Plots[1]->FindBin(LowRange);
			int HighBin = Plots[1]->FindBin(HighRange);

			double IntegralCH2 = Plots[1]->Integral(LowBin,HighBin);
			double IntegralC = Plots[0]->Integral(LowBin,HighBin);

//cout << "IntegralC/IntegralCH2 =" << IntegralC/IntegralCH2 << endl;

			Plots[1]->Scale(IntegralC/IntegralCH2);

			// ----------------------------------------------------------------------------------------------------------------------

			TH1D* Clone = (TH1D*)Plots[1]->Clone("Clone");
			Clone->Add(Plots[0],-1);

//cout << "Clone->Integral() = " << Clone->Integral() << endl;
 
			// ----------------------------------------------------------------------------------------------------------------

			// Getting to the cross section

			double CloneSF = 7. * ConversionFactorChargeToElectrons / (dOmega * IntegratedCharge_PinnedFiles[std::make_pair("CH2", E[WhichEnergy])] * AvogadroNumber *\
			       TargetLength[std::make_pair("CH2",E[WhichEnergy])] * TargetDensity[std::make_pair("CH2",E[WhichEnergy])]);
			Clone->Scale(CloneSF);

			Clone->GetYaxis()->SetTitle("Normalized Yield");
			DiffCanvas->cd();
			Clone->Draw();

			Clone->Fit("gaus","","",0.9,0.96);

			double dsigmadOmega = Integrate(Clone);

			cout << "Data dsigmadOmega = " << dsigmadOmega << endl;

			//cout << "Data Sigma = " << dsigmadOmega*dOmega << endl;

			// --------------------------------------------------------------------------------------------------------------

			// Hydrogen GENIE File

			TString HydrogenPathToFiles = "../../myFiles/1_161/hA2018_Final_RadCorr_LFGM/NoxBCut/";
			TString HydrogenFileName = HydrogenPathToFiles+"1H_1_161_hA2018_Final_RadCorr_LFGM_Plots_FSI_em.root";

			if (FSILabel[0] == "Pinned Data No Rotations") { 

				HydrogenPathToFiles = "../../myFiles/1_161/hA2018_NoRotations/NoxBCut/"; 
				HydrogenFileName = HydrogenPathToFiles+"1H_1_161_hA2018_NoRotations_Plots_FSI_em.root";

			}

			TFile* HydrogenFileSample = TFile::Open(HydrogenFileName);

			TH1D* G2018histo = (TH1D*)(HydrogenFileSample->Get(NameOfPlots[0]));

			//UniversalE4vFunction(G2018histo,"G2018","1H","1_161","h1_Wvar_weight");

			//AbsoluteXSecScaling(G2018histo,"G2018","1H","1_161");

			// -------------------------------------------------------------------------------------------

			double GeniedsigmadOmega = G2018histo->GetEntries() * G2018GenieXSec[std::make_pair("1H", "1_161")] * TMath::Power(10.,-38.) *\
								ConversionFactorCm2ToMicroBarn / (G2018NumberEvents[std::make_pair("1H", "1_161")] *\
								dOmega) ;

			double GenieSF = G2018GenieXSec[std::make_pair("1H", "1_161")] * TMath::Power(10.,-38.) *\
								ConversionFactorCm2ToMicroBarn / (G2018NumberEvents[std::make_pair("1H", "1_161")] *\
								dOmega) ;

			cout << "Genie dsigmadOmega = " << GeniedsigmadOmega << endl;

			//cout << "Genie Sigma = " << GeniedsigmadOmega*dOmega << endl;

			// -------------------------------------------------------------------------------------------


			G2018histo->Scale(GenieSF);

			G2018histo->SetLineColor(kBlue);
			G2018histo->SetLineWidth(3);
			//G2018histo->Draw("C hist same");

			TLegend* leg = new TLegend(0.6,0.6,0.7,0.7);

			leg->AddEntry(Clone,"Data","lep");
			//leg->AddEntry(G2018histo,"GENIE","l");

			leg->SetTextFont(FontStyle);
			leg->SetTextSize(TextSize);
			leg->SetBorderSize(0);

			leg->Draw();

			// -------------------------------------------------------------------------------------------

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
