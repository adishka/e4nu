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

double GetEntriesInBins(TH1D* h, int MinBin, int MaxBin) {

	int NBins = h->GetXaxis()->GetNbins();

	double SumEntries = 0;

	for (int i = 0; i < NBins; i++) {

		if ( i + 1 >= MinBin && i + 1 <= MaxBin ) {

			SumEntries += h->GetBinContent(i+1) * h->GetBinWidth(i+1);

		}

	}

	return SumEntries;

}

// ----------------------------------------------------------------------------------------------------------------

void AbsXSec_OverlayECalTable_TabulatedYield_e4nuPaper() {

	// ------------------------------------------------------------------------

	GlobalSettings();

	// ------------------------------------------------------------------------

	std::vector<TString> xBCut; 
	std::vector<TString> nucleus;
	std::vector<TString> E; 
	std::vector<double> DoubleE;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; std::vector<TString> NameOfPlots; std::vector<TString> LabelOfPlots;  
	std::vector<TString> OutputPlotNames; std::vector<TH1D*> BreakDownPlots;
	std::vector<int> Colors;

	nucleus.push_back("12C");
	nucleus.push_back("56Fe");

	E.push_back("1_161"); DoubleE.push_back(1.161);
	E.push_back("2_261"); DoubleE.push_back(2.261);	
	E.push_back("4_461"); DoubleE.push_back(4.461);

	xBCut.push_back("NoxBCut");
 
	Colors.push_back(kBlack); Colors.push_back(kBlack); Colors.push_back(kBlack); 
	Colors.push_back(kMagenta); Colors.push_back(kGreen); Colors.push_back(kOrange + 7);

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Pinned Data");
	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("G2018");

//	FSIModel.push_back("Pinned_Data_Final_SixSectors"); FSILabel.push_back("Pinned Data");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM_SixSectors"); FSILabel.push_back("SuSav2");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_SixSectors"); FSILabel.push_back("G2018");

	NameOfPlots.push_back("epRecoEnergy_slice_0"); LabelOfPlots.push_back("(e,e'p)_{1p0#pi} E^{cal} [GeV]"); OutputPlotNames.push_back("epRecoEnergy_slice_0");

	std::vector<TH1D*> Plots;

	int NxBCuts = xBCut.size();
	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NFSIModels = FSIModel.size();
	int NPlots = NameOfPlots.size();

	// ---------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over the xB kinematics

	for (int WhichxBCut = 0; WhichxBCut < NxBCuts; WhichxBCut ++) {						

		// Loop over the plots

		for (int WhichPlot = 0; WhichPlot < NPlots; WhichPlot ++) {

			// Loop over the energies

			for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

				cout << endl << "Energy = " << E[WhichEnergy] << endl << endl;

				// Loop over the nuclei

				for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

					cout << endl << "Nucleus = " << nucleus[WhichNucleus] << endl << endl;

					// -------------------------------------------------------------------------------

					// No data on 56Fe @ 1.161 GeV

					if ( nucleus[WhichNucleus] == "56Fe" && DoubleE[WhichEnergy] == 1.161 ) { continue; }

					// ---------------------------------------------------------------------------------------------

					Plots.clear();

					// Loop over the FSI Models				

					for (int WhichFSIModel = 0; WhichFSIModel < NFSIModels; WhichFSIModel ++) {

						TString PathToFiles = "../../../myFiles/"+ E[WhichEnergy] + "/"+FSIModel[WhichFSIModel]+"/"+xBCut[WhichxBCut]+"/";
						TString FileName = PathToFiles+nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+FSIModel[WhichFSIModel]+"_Plots_FSI_em.root";
						TFile* FileSample = TFile::Open(FileName);

						Plots.push_back( (TH1D*)( FileSample->Get(NameOfPlots[WhichPlot]) ) );

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

						//-----------------------------------------------------------------------------------------------

						double range = 0.05;
						if (DoubleE[WhichEnergy] == 2.261) { range = 0.03; }
						if (DoubleE[WhichEnergy] == 4.461) { range = 0.02; }

						double LowE = (1-range)*DoubleE[WhichEnergy];
						double HighE = (1+range)*DoubleE[WhichEnergy];

						int LowEBin = Plots[WhichFSIModel]->FindBin(LowE);
						int HighEBin = Plots[WhichFSIModel]->FindBin(HighE);

						double LowEdgeLowLimit = Plots[WhichFSIModel]->GetBinLowEdge(LowEBin);
						double HighEdgeHighLimit = Plots[WhichFSIModel]->GetBinLowEdge(HighEBin) + Plots[WhichFSIModel]->GetBinWidth(HighEBin);

						cout << "LowEdgeLowLimit = " << LowEdgeLowLimit << "  HighEdgeHighLimit = " << HighEdgeHighLimit << endl;

						//double PeakIntegral = Plots[WhichFSIModel]->Integral(LowEBin,HighEBin);

						double PeakEntries = GetEntriesInBins(Plots[WhichFSIModel], LowEBin, HighEBin); 

//						cout << FSILabel[WhichFSIModel] << " Peak Integral = " << PeakIntegral << "   Peak Entries = " << PeakEntries << endl;
						cout << FSILabel[WhichFSIModel] << " Peak Entries = " << PeakEntries << endl;

					} // End of the loop over the FSI Models 				

					// ---------------------------------------------------------------------------------------------------------

				} // End of the loop over the energies

				cout << endl;
				cout << "----------------------------------------------" << endl;

			} // End of the loop over the nuclei

		} // End of the loop over the plots

	} // End of the loop over the xB kinematics

} // End of the program
