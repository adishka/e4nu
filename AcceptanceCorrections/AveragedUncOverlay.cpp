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

#include "../myFunctions.cpp"
#include "../AfroConstants.h"

TGraph* RMSAveragedFunc(TH1D* h, std::vector<TH1D*> hVec, TString Energy, TString Var) {

	TH1D::SetDefaultSumw2();

	double DoubleE = -99., reso = 0.;
	if (Energy == "1_161") { DoubleE = 1.161; reso = 0.07; }
	if (Energy == "2_261") { DoubleE = 2.261; reso = 0.08; }
	if (Energy == "4_461") { DoubleE = 4.461; reso = 0.06; }

	const int NBins = h->GetXaxis()->GetNbins();

	// ---------------------------------------------------------------------------------------------------------

	TH1D* RMSClone = (TH1D*)(hVec[0]->Clone("RMSClone"));
	TString XaxisTitle = RMSClone->GetXaxis()->GetTitle();  
	RMSClone->Add(hVec[1],-1);
	RMSClone->Divide(h);
	RMSClone->Scale(1./TMath::Sqrt(12.));

	double sum = 0; int nbins = 0;

	for (int WhichBin = 1; WhichBin <= NBins; WhichBin++) {

		double BinCenter = RMSClone->GetBinCenter(WhichBin);
		double BinContent = TMath::Abs(RMSClone->GetBinContent(WhichBin)) * 100.;

		RMSClone->SetBinContent(WhichBin,BinContent);

		if (BinCenter > (1-reso) * DoubleE && BinCenter < (1+reso) * DoubleE ) {

			sum += BinContent; nbins++;

		}

	}

	sum = sum / double(nbins);

	// ---------------------------------------------------------------------------------------------------------

	double bincenter[NBins];
	double binentry[NBins];

	// For Ecal only
	// Use the average around the Ecal peak in the bins (1 +/- reso) Ebeam

	if (Var == "epRecoEnergy_slice_0") {

		for (int WhichBin = 1; WhichBin <= NBins; WhichBin++) {

			double BinCenter = RMSClone->GetBinCenter(WhichBin);
			double BinContent = RMSClone->GetBinContent(WhichBin);

			if (BinCenter/DoubleE < 1.1) {

				bincenter[WhichBin-1] = BinCenter;

				if (BinCenter > (1-reso) * DoubleE && BinCenter < (1+reso) * DoubleE ) {

					RMSClone->SetBinContent(WhichBin,sum);
					binentry[WhichBin-1] = sum;

				} else { binentry[WhichBin-1] = BinContent; }

			}

		}

	} else {

		for (int WhichBin = 1; WhichBin <= NBins; WhichBin++) {

			double BinCenter = RMSClone->GetBinCenter(WhichBin);
			double BinContent = RMSClone->GetBinContent(WhichBin);

			bincenter[WhichBin-1] = BinCenter;
			binentry[WhichBin-1] = BinContent;

		}

	}

	// ---------------------------------------------------------------------------------------------------------

	TGraph* GraphClone = new TGraph(NBins,bincenter,binentry);
	GraphClone->GetXaxis()->SetTitle(XaxisTitle);

	// ---------------------------------------------------------------------------------------------------------

	return GraphClone;

}

// ----------------------------------------------------------------------------------------------------------------

void AveragedUncOverlay() {

	// ------------------------------------------------------------------------

	GlobalSettings();
	TH1D::SetDefaultSumw2();
	const std::vector<int> Colors{kBlack,610,410,kRed+1,kCyan+1,kBlue,kOrange+1};

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut;
	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<TString> E;
	std::vector<TString> LabelE; 
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> NameOfPlots;
	std::vector<TString> NameOfSubPlots;

//	nucleus.push_back("4He"); LabelsOfSamples.push_back("^{4}He");
	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C");
	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

//	E.push_back("1_161"); LabelE.push_back(", 1.1 GeV");
//	E.push_back("2_261"); LabelE.push_back(", 2.2 GeV");	
	E.push_back("4_461"); LabelE.push_back(", 4.4 GeV");

	xBCut.push_back("NoxBCut");
//	xBCut.push_back("xBCut");

	FSIModel.push_back("SuSav2"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("hA2018_Final"); FSILabel.push_back("G2018");

	TString Var = "epRecoEnergy_slice_0";
//	TString Var = "MissMomentum";
//	TString Var = "DeltaAlphaT_Int_0";
//	TString Var = "DeltaPhiT_Int_0";

//	NameOfPlots.push_back("Reco_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("TrueWithFid_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("True_eRecoEnergy_slice_0");

//	NameOfPlots.push_back("BkgCorrection_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("FidCorrection_eRecoEnergy_slice_0");
//	NameOfPlots.push_back("AccCorrection_eRecoEnergy_slice_0");

//	NameOfPlots.push_back("Reco_epRecoEnergy_slice_0");
//	NameOfPlots.push_back("TrueWithFid_epRecoEnergy_slice_0");
//	NameOfPlots.push_back("True_epRecoEnergy_slice_0");

//	NameOfPlots.push_back("AccCorrection_epRecoEnergy_slice_0");

	NameOfPlots.push_back("InverseAccCorrection_"+Var);

	// ------------------------------------------------------------------------

	std::vector<TH1D*> Plots;
	std::vector<TH1D*> average;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// ------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {

		TString NameCanvas = Var+"_"+xBCut[WhichxBCut];
		TCanvas* PlotCanvas = new TCanvas(NameCanvas,NameCanvas,205,34,1024,768);
				
		PlotCanvas->SetLeftMargin(0.15);
		PlotCanvas->SetBottomMargin(0.17);	
		PlotCanvas->SetGridx();	
		PlotCanvas->SetGridy();

		int ColorCounter = 0;
		average.clear();

		TLegend* leg = new TLegend(0.1,0.9,0.92,0.99);
		leg->SetNColumns(4);
		leg->SetBorderSize(0);
		leg->SetTextFont(132);
		leg->SetTextSize(0.05);
		leg->SetFillStyle(0);

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

			// Loop over the nuclei

			for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

				if (E[WhichEnergy] == "1_161" && nucleus[WhichNucleus] != "12C") { continue; }

				// Loop over the plots

				for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {	

					// ---------------------------------------------------------------------------------------

					Plots.clear();

					double max = -99.;
					double min = 1E12;

					// Loop over the FSI Models

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString FileName = "myFiles/Efficiency_"+FSIModel[WhichFSIModel]+"_"+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+xBCut[WhichxBCut]+".root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(FSIModel[WhichFSIModel]+"_"+NameOfPlots[WhichPlot]) ) );

						Plots[WhichFSIModel]->SetLineColor(Colors[ColorCounter]);

//						// ---------------------------------------------------------------------------------------------------

//						TLegendEntry* l1 = leg->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel], "l");
//						l1->SetTextColor(Colors[WhichFSIModel]);

//						// ---------------------------------------------------------------------------------------------------

//						// Max, min, title & # divisions

//						double localmax = Plots[WhichFSIModel]->GetMaximum();
//						if (localmax > max) { max = localmax; }
//						double height = 1.1;
//						Plots[0]->SetMaximum(height*max);

//		                                // --------------------------------------------------------------------------------------------------

////						Plots[WhichFSIModel]->Draw("C hist same");
////						Plots[0]->Draw("C hist same");

//						Plots[WhichFSIModel]->Draw("e  same");
////						Plots[0]->Draw("e  same");

		                                // --------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

//					leg->SetBorderSize(0);
//					leg->SetTextFont(FontStyle);
//					leg->SetTextSize(TextSize);
//					leg->Draw();

					average.push_back( (TH1D*)(Plots[0]->Clone()) );
					average[ColorCounter]->Add(Plots[1]);
					average[ColorCounter]->Scale(0.5);

					std::vector<TH1D*> VectorPlots; VectorPlots.clear();

					for (int i = 0; i < NFSIModels; i++) {

						VectorPlots.push_back(Plots[i]);

					}

					TGraph* clone = RMSAveragedFunc(average[ColorCounter],VectorPlots,E[WhichEnergy],Var);
					//clone->Scale(100.);

					clone->SetTitle("");
					//clone->GetXaxis()->SetTitle("E^{reco}/E^{beam}");
					clone->GetYaxis()->SetTitle("Fractional Contribution (%)");
//					clone->GetYaxis()->SetRangeUser(-20,20);
					clone->GetYaxis()->SetRangeUser(0,40);

					clone->GetXaxis()->SetNdivisions(8);
					clone->GetYaxis()->SetNdivisions(10);

					clone->SetMarkerStyle(20);
					clone->SetMarkerSize(2.);
					clone->SetMarkerColor(Colors[ColorCounter]);

					if (ColorCounter == 0) { clone->Draw("ap"); }
					else { clone->Draw("p"); }

					TLegendEntry* l1 = leg->AddEntry(clone,nucleus[WhichNucleus] + LabelE[WhichEnergy], "");
					l1->SetTextColor(Colors[ColorCounter]);

					// -----------------------------------------------------------------------------------------------------------------------------------------

				} // End of the loop over the plots

				ColorCounter++;

			} // End of the loop over the nuclei

		} // End of the loop over the energies

		leg->Draw();

	} // End of the loop over the xB kinematics

} // End of the program
