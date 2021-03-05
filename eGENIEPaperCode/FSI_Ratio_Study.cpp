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

void Reweight(TH1D* h, double SF = 1) {

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

// ----------------------------------------------------------------------------------------------------------------

void FSI_Ratio_Study() {

	TH1D::SetDefaultSumw2();
//	TGaxis::SetMaxDigits(3);
//	TGaxis::SetExponentOffset(-0.1, 1., "y");

	int Ndivisions = 6;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.07;
	gStyle->SetOptStat(0);

	// ----------------------------------------------------------------------------------

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<int> NEvents; 
	std::vector<double> GenieXSec; 

	//nucleus.push_back("40Ar");LabelsOfSamples.push_back("^{40}Ar");
	nucleus.push_back("C12");LabelsOfSamples.push_back("^{12}C");

	std::vector<TString> E; E.push_back("1161");
	std::vector<TString> LabelE; LabelE.push_back(" @ E = 1.161 GeV");

	//std::vector<int> Colors; Colors.push_back(kBlack); Colors.push_back(610);
	std::vector<int> Colors;
	std::vector<int> Styles;

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Must be introduced in pairs (FSI / NoFSI)

	std::vector<TString> FSIModel;std::vector<TString> FSILabel; std::vector<TString> RatioLabel; 

	FSIModel.push_back("GTEST19_10b_00_000_CCinclMEC_Q2_0_1_NoFSI"); NEvents.push_back(10000000); GenieXSec.push_back(14.616779);
	FSIModel.push_back("GTEST19_10b_00_000_CCinclMEC_Q2_0_1"); NEvents.push_back(10000000); GenieXSec.push_back(14.616779);
	FSIModel.push_back("GTEST19_10b_00_000_EM+MEC_Q2_0_1_NoFSI"); NEvents.push_back(9900000); GenieXSec.push_back(1.2896728e+09);
	FSIModel.push_back("GTEST19_10b_00_000_EM+MEC_Q2_0_1"); NEvents.push_back(9900000); GenieXSec.push_back(1.2896728e+09);

//	FSIModel.push_back("G18_10a_02_11a_CCinclMEC_Q2_0_1"); NEvents.push_back(10000000); GenieXSec.push_back(14.616779);
//	FSIModel.push_back("G18_10a_02_11a_CCinclMEC_Q2_0_1_NoFSI"); NEvents.push_back(10000000); GenieXSec.push_back(14.616779);
//	FSIModel.push_back("G18_10a_02_11a_EM+MEC_Q2_0_1"); NEvents.push_back(9600000); GenieXSec.push_back(1.2896728e+09);
//	FSIModel.push_back("G18_10a_02_11a_EM+MEC_Q2_0_1_NoFSI"); NEvents.push_back(10000000); GenieXSec.push_back(1.2896728e+09);

	FSILabel.push_back("#nu w/o FSI");
	FSILabel.push_back("#nu w/  FSI"); 
	FSILabel.push_back("e w/o FSI");
	FSILabel.push_back("e w/  FSI");

	RatioLabel.push_back("#nu"); 
	RatioLabel.push_back("#nu");
	RatioLabel.push_back("e");
	RatioLabel.push_back("e");


	Colors.push_back(kBlue-7); 
	Colors.push_back(kBlue-7);
	Colors.push_back(kOrange+1);
	Colors.push_back(kOrange+1);

	Styles.push_back(kDashed);
	Styles.push_back(kSolid);
	Styles.push_back(kDashed); 
	Styles.push_back(kSolid);
	
	//FSIModel.push_back("G18_10a_02_11a_CCinclMEC");FSILabel.push_back("#nu G2018");
	//FSIModel.push_back("G18_10a_02_11a_EM+MEC");FSILabel.push_back("e G2018");
	//FSIModel.push_back("G18_10a_02_11a_NoFSI_CCinclMEC");FSILabel.push_back("#nu G2018 NoFSI");
	//FSIModel.push_back("G18_10a_02_11a_NoFSI_EM+MEC");FSILabel.push_back("e G2018 NoFSI");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	std::vector<TString> NameOfPlots;
	std::vector<double> IntegralPlots;

	IntegralPlots.push_back(1.);
	IntegralPlots.push_back(1.);
	IntegralPlots.push_back(1.);
	IntegralPlots.push_back(1.);

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

//	NameOfPlots.push_back("MissMomentum_OneProtonPlot"); 
//	NameOfPlots.push_back("MissMomentum_OneProtonPlot"); 
//	NameOfPlots.push_back("MissMomentum_OneProtonPlot"); 
//	NameOfPlots.push_back("MissMomentum_OneProtonPlot"); 

//	NameOfPlots.push_back("QEMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("QEMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("QEMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("QEMissMomentumPlot_OneProton");

//	NameOfPlots.push_back("MECMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("MECMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("MECMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("MECMissMomentumPlot_OneProton");

	NameOfPlots.push_back("RESMissMomentumPlot_OneProton");
	NameOfPlots.push_back("RESMissMomentumPlot_OneProton");
	NameOfPlots.push_back("RESMissMomentumPlot_OneProton");
	NameOfPlots.push_back("RESMissMomentumPlot_OneProton");

//	NameOfPlots.push_back("DISMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("DISMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("DISMissMomentumPlot_OneProton");
//	NameOfPlots.push_back("DISMissMomentumPlot_OneProton");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

//	NameOfPlots.push_back("MissMomentum_VectorSum");
//	NameOfPlots.push_back("DeltaAlphaT_VectorSum"); 
//	NameOfPlots.push_back("DeltaPhiT_VectorSum");

//	NameOfPlots.push_back("QEMissMomentum_OneProton");                                                                                                                                            
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

			//for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

			        TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]; 
				TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768) ;

				PlotCanvas->SetBottomMargin(0.14);
				PlotCanvas->SetLeftMargin(0.2);
				PlotCanvas->SetRightMargin(0.02);

				Plots.clear();

				TLegend* leg = new TLegend(0.5,0.6,0.85,0.85);
				leg->SetNColumns(1);
				leg->SetMargin(0.15);

				TLegend* legRatio = new TLegend(0.75,0.8,0.89,0.89);
				legRatio->SetNColumns(2);
				legRatio->SetMargin(0.15);

				double max = -99.;

				// Loop over the FSI Models
				
				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					TString PathToFiles = "myFiles/";
					TFile* FileSample = TFile::Open(PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+".root");

					Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichFSIModel]) ) );
					
					Plots[WhichFSIModel]->SetLineColor(Colors[WhichFSIModel]);
					Plots[WhichFSIModel]->SetLineStyle(Styles[WhichFSIModel]);
					Plots[WhichFSIModel]->SetLineWidth(3);

					Plots[WhichFSIModel]->GetXaxis()->SetLabelFont(FontStyle);
					Plots[WhichFSIModel]->GetXaxis()->SetTitleFont(FontStyle);
					Plots[WhichFSIModel]->GetXaxis()->SetLabelSize(TextSize);
					Plots[WhichFSIModel]->GetXaxis()->SetTitleSize(TextSize);
					Plots[WhichFSIModel]->GetXaxis()->SetTitleOffset(0.95);
					Plots[WhichFSIModel]->GetXaxis()->SetNdivisions(Ndivisions);
					Plots[WhichFSIModel]->GetXaxis()->CenterTitle();

					Plots[WhichFSIModel]->GetYaxis()->SetLabelFont(FontStyle);
					Plots[WhichFSIModel]->GetYaxis()->SetTitleFont(FontStyle);
					Plots[WhichFSIModel]->GetYaxis()->SetLabelSize(TextSize);
					Plots[WhichFSIModel]->GetYaxis()->SetTitleSize(TextSize);
					Plots[WhichFSIModel]->GetYaxis()->SetNdivisions(Ndivisions);
					Plots[WhichFSIModel]->GetYaxis()->SetTitleOffset(1.2);
//					Plots[WhichFSIModel]->GetYaxis()->SetTitle("#frac{d#sigma}{dP_{T}} #left[#frac{10^{-38}}{GeV/c ^{12}C}#right]");
					Plots[WhichFSIModel]->GetYaxis()->SetTitle("Area Normalized");
					Plots[WhichFSIModel]->GetYaxis()->CenterTitle();

					TLegendEntry* l1 = leg->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel], "l");
					l1->SetTextColor(Colors[WhichFSIModel]);

					Plots[WhichFSIModel]->Rebin();
				
					//double ExtraSF = 1.;
					//if (string(FSIModel[WhichFSIModel]).find("EM+MEC") != std::string::npos) { ExtraSF = 3*1E-7; }
//					double ScalingFactor = GenieXSec[WhichFSIModel] / NEvents[WhichFSIModel] * ExtraSF;

					IntegralPlots[WhichFSIModel] = Plots[WhichFSIModel]->Integral();
					int PlotIndex = std::floor(WhichFSIModel/2) == 0? 0:2;
cout << "Plot Index = " << PlotIndex << endl;
					double ScalingFactor = 1./IntegralPlots[PlotIndex];

//					double ScalingFactor = 1.;

					//Reweight(Plots[WhichFSIModel]);

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
				//latex->DrawLatexNDC(0.2,0.4,LabelsOfSamples[WhichNucleus]+LabelE[WhichEnergy]);

				//PlotCanvas->SaveAs("myPlots/"+nucleus[WhichNucleus]+"_" +E[WhichEnergy]+"_" +NameOfPlots[WhichPlot]+"_SuSav2.pdf"); 

				// ----------------------------------------------------------------------------------------------------------------------

				// Ratio plot to quantify FSI effect on e/v

			        //TString RatioCanvasName = "Ratio_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+NameOfPlots[WhichPlot]; 
			        TString RatioCanvasName = "Ratio_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]; 
				TCanvas* RatioPlotCanvas = new TCanvas(RatioCanvasName,RatioCanvasName,205,34,1024,768) ;

				RatioPlotCanvas->SetBottomMargin(0.14);
				RatioPlotCanvas->SetLeftMargin(0.13);
				RatioPlotCanvas->SetRightMargin(0.02);

				std::vector<TH1D*> Ratios; Ratios.clear();

				for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

					TH1D* TempPlot = (TH1D*)(Plots[WhichFSIModel]->Clone());
					TempPlot->Divide(Plots[WhichFSIModel+1]);
					Ratios.push_back(TempPlot);

					WhichFSIModel ++;

				}

				int NRatios = Ratios.size();

 				for (int WhichRatio = 0; WhichRatio < NRatios; WhichRatio ++) {

					Ratios[WhichRatio]->GetYaxis()->SetRangeUser(0.,4.);
					Ratios[WhichRatio]->GetYaxis()->SetTitle("No FSI / FSI");
					Ratios[WhichRatio]->GetYaxis()->SetTitleOffset(0.9);
					Ratios[WhichRatio]->GetYaxis()->SetNdivisions(5);

					Ratios[WhichRatio]->SetLineStyle(kSolid);
					Ratios[WhichRatio]->Draw("hist same");

					TLegendEntry* l1 = legRatio->AddEntry(Ratios[WhichRatio],RatioLabel[2*WhichRatio], "l");
					l1->SetTextColor(Colors[2*WhichRatio]);

				}

				legRatio->SetBorderSize(0);
				legRatio->SetTextFont(FontStyle);
				legRatio->SetTextSize(0.07);			
				legRatio->Draw();

				//RatioPlotCanvas->SaveAs("myPlots/Ratio_"+nucleus[WhichNucleus]+"_" +E[WhichEnergy]+"_" +NameOfPlots[WhichPlot]+"_SuSav2.pdf"); 

				// ----------------------------------------------------------------------------------------------------------------------

			//} // End of the loop over the plots

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
