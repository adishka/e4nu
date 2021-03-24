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

#include "../AfroConstants.h"
#include "../myFunctions.cpp"

// ----------------------------------------------------------------------------------------------------------------

void PrettyPlot(TH2D* h){


		h->GetXaxis()->CenterTitle();
		h->GetXaxis()->SetTitle("");
		h->GetXaxis()->SetTitleSize(TextSize);
		h->GetXaxis()->SetLabelSize(0.);
		h->GetXaxis()->SetTitleFont(FontStyle);		
		h->GetXaxis()->SetLabelFont(FontStyle);
		h->GetXaxis()->SetNdivisions(6);

		h->GetYaxis()->CenterTitle();		
		h->GetYaxis()->SetTitle("");
		h->GetYaxis()->SetTitleSize(TextSize);
		h->GetYaxis()->SetLabelSize(0.1);
		h->GetYaxis()->SetTitleFont(FontStyle);		
		h->GetYaxis()->SetLabelFont(FontStyle);
		h->GetYaxis()->SetNdivisions(5);


}

// ----------------------------------------------------------------------------------------------------------------

void Q0VsQ3_TwoDThetaEPrimeT2KEQEResoSlicesStudy() {

	// ----------------------------------------------------------------------------------------------------------------
	
	gStyle->SetOptStat(0);	
	
	double GlobalMax = 19.;

	// ---------------------------------------------------------------------------------------------------------------

	std::vector<TString> NucleusString; NucleusString.clear();
	std::vector<TString> NucleusLatex; NucleusLatex.clear();

//	NucleusString.push_back("4He"); NucleusLatex.push_back("^{4}He");
	NucleusString.push_back("12C"); NucleusLatex.push_back("^{12}C");
//	NucleusString.push_back("56Fe"); NucleusLatex.push_back("^{56}Fe");

	const int NNuclei = NucleusString.size();

	// Loop over the nuclei

	for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus++) {

		// ---------------------------------------------------------------------------------------------------------------

		std::vector<TString> EnergyString; EnergyString.clear();
		std::vector<double> EnergyDouble; EnergyDouble.clear();

		EnergyString.push_back("1_161"); EnergyDouble.push_back(1.161);
//		EnergyString.push_back("2_261"); EnergyDouble.push_back(2.261);
//		EnergyString.push_back("4_461"); EnergyDouble.push_back(4.461);

		const int NEnergies = EnergyString.size();

		// ----------------------------------------------------------------------------------------------------------------	

		// Loop over the energies

		for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy++) {

			// ----------------------------------------------------------------------------------------------------------------	

			// Data set at 1.1 GeV only on 12C

			if (EnergyDouble[WhichEnergy] == 1.161 && NucleusString[WhichNucleus] != "12C") { continue; }

			// ----------------------------------------------------------------------------------------------------------------	

			// SuSav2 ECal in EePrime and ThetaPrime Slices 		

			double MinCosTheta2D = 0.6, MaxCosTheta2D = 0.99; int CosThetaSlices2D = 3;	

			if(EnergyDouble[WhichEnergy]>1. && EnergyDouble[WhichEnergy]<2.) { MaxCosTheta2D = 0.96; }
			if(EnergyDouble[WhichEnergy]>2. && EnergyDouble[WhichEnergy]<3.) { MaxCosTheta2D = 0.96; }

			double CosThetaStep2D = (MaxCosTheta2D - MinCosTheta2D) / CosThetaSlices2D;

			double MinEePrime2D = -1, MaxEePrime2D = -1;
			int EePrimeSlices2D = 3;

			// ---------------------------------------------------------------------------------------------------------------

			// Dimensions of TPads

			double Xmin = 0.07, Xmax = 1.;
			double Ymax = 1., Ymin = 0.08;
			double Xstep = (Xmax - Xmin) / double(EePrimeSlices2D);
			double Ystep = ( Ymax - Ymin  ) / double(CosThetaSlices2D);

			// ---------------------------------------------------------------------------------------------------------------

			if(EnergyDouble[WhichEnergy]>1. && EnergyDouble[WhichEnergy]<2.) { MinEePrime2D = 0.5; MaxEePrime2D = 1.1; }
			if(EnergyDouble[WhichEnergy]>2. && EnergyDouble[WhichEnergy]<3.) { MinEePrime2D = 1.3; MaxEePrime2D = 2.2; }
			if(EnergyDouble[WhichEnergy]>4. && EnergyDouble[WhichEnergy]<5.) { MinEePrime2D = 2.5; MaxEePrime2D = 4.; }

			double EePrimeStep2D = (MaxEePrime2D - MinEePrime2D) / EePrimeSlices2D;

			// ---------------------------------------------------------------------------------------------------------------

			TFile* file = TFile::Open("../../myFiles/"+EnergyString[WhichEnergy]+"/Pinned_Data_Final/NoxBCut/"+\
							NucleusString[WhichNucleus]+"_"+EnergyString[WhichEnergy]+"_Pinned_Data_Final_Plots_FSI_em.root","readonly");
//			TFile* file = TFile::Open("../../myFiles/"+EnergyString[WhichEnergy]+"/SuSav2_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc/NoxBCut/"+NucleusString[WhichNucleus]+"_"+EnergyString[WhichEnergy]+"_SuSav2_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc_Plots_FSI_em.root","readonly");	
//			TFile* file = TFile::Open("../../myFiles/"+EnergyString[WhichEnergy]+"/hA2018_Final_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc/NoxBCut/"+NucleusString[WhichNucleus]+"_"+EnergyString[WhichEnergy]+"_hA2018_Final_NoRadCorr_LFGM_Truth0pi_WithoutFidAcc_Plots_FSI_em.root","readonly");	

			TString CanvasName = NucleusString[WhichNucleus]+"_"+EnergyString[WhichEnergy]+"_T2KQ0VsQ3Canvas_EePrimeAndCosThetaSlices_2D";

			TCanvas* SuSav2Canvas_ECal_EePrimeAndThetaSlices = new TCanvas(CanvasName,CanvasName,205,34,1300,1300);

			for (int WhichCosThetaSlice2D = 0 ; WhichCosThetaSlice2D < CosThetaSlices2D; WhichCosThetaSlice2D++ ) {		

				double MinCosThetaSlice2D = (MinCosTheta2D+WhichCosThetaSlice2D*CosThetaStep2D);
				double MaxCosThetaSlice2D = (MinCosTheta2D+(WhichCosThetaSlice2D+1)*CosThetaStep2D);

				for (int WhichEePrimeSlice2D = 0 ; WhichEePrimeSlice2D < EePrimeSlices2D; WhichEePrimeSlice2D++ ) {

					double MinEePrimeSlice2D = (MinEePrime2D+WhichEePrimeSlice2D*EePrimeStep2D);
					double MaxEePrimeSlice2D = (MinEePrime2D+(WhichEePrimeSlice2D+1)*EePrimeStep2D);

					// ---------------------------------------------------------------------------------------------------------------

					double XMinPad = Xmin + WhichEePrimeSlice2D * Xstep, XMaxPad = Xmin + ( WhichEePrimeSlice2D + 1) * Xstep;
					double YMinPad = Ymax - ( WhichCosThetaSlice2D + 1) * Ystep, YMaxPad = Ymax - WhichCosThetaSlice2D * Ystep;
					double space = 0.;

					TPad* pad = new TPad(); 

					TString TPadName = CanvasName+"_EePrimeSlice_"+ToStringInt(WhichEePrimeSlice2D)+"_CosThetaSlice_"+ToStringInt(WhichCosThetaSlice2D);

					if (WhichEePrimeSlice2D == 0) 
						{ pad = new TPad(TPadName,TPadName,XMinPad,YMinPad,XMaxPad,YMaxPad, 21); }
					else 
						{ pad = new TPad(TPadName,TPadName,XMinPad,YMinPad+space,XMaxPad,YMaxPad+space, 21); }

					pad->SetFillColor(kWhite); 
					SuSav2Canvas_ECal_EePrimeAndThetaSlices->cd();
					pad->Draw();
					pad->cd();

					pad->SetBottomMargin(0.0);
					if (WhichCosThetaSlice2D == CosThetaSlices2D-1 ) { pad->SetBottomMargin(0.14); }
					pad->SetTopMargin(0.0);
					if (WhichCosThetaSlice2D == 0) { pad->SetTopMargin(0.01); }
					pad->SetLeftMargin(0.);
					if (WhichEePrimeSlice2D == 0 ) { pad->SetLeftMargin(0.12); }
					pad->SetRightMargin(0.0);
					if (WhichEePrimeSlice2D == EePrimeSlices2D-1 ) { pad->SetRightMargin(0.12); }
					pad->SetFrameBorderSize(10);

					TString NamePlot = Form("h1_T2K_Q0VsQ3_Int_0_InEePrime_%d_To_%d_InCosTheta_%d_To_%d_Slices",								WhichEePrimeSlice2D,WhichEePrimeSlice2D+1,WhichCosThetaSlice2D,WhichCosThetaSlice2D+1);

					TH2D* Q0VsQ3Plot = (TH2D*)file->Get(NamePlot);

					PrettyPlot(Q0VsQ3Plot);

					if (WhichCosThetaSlice2D == CosThetaSlices2D-1 ) {

						Q0VsQ3Plot->GetXaxis()->SetLabelSize(0.1);

					}	

					if (EnergyString[WhichEnergy] == "2_261") { Q0VsQ3Plot->GetXaxis()->SetRangeUser(0.5,2.5); }
										
					Q0VsQ3Plot->Draw("colt");

					// -------------------------------------------------------------------------------------------------------------

					TLegend* legSuSav2_Slice = new TLegend(0.11,0.77,0.2,0.96);

					if (WhichEePrimeSlice2D == 0) { legSuSav2_Slice = new TLegend(0.18,0.77,0.27,0.96); }

					legSuSav2_Slice->SetBorderSize(0);
					legSuSav2_Slice->SetTextFont(FontStyle);
					legSuSav2_Slice->SetTextSize(1.3*TextSize);	

					legSuSav2_Slice->AddEntry(Q0VsQ3Plot,ToStringDouble(MinEePrimeSlice2D)+ " < E_{e'} < " + ToStringDouble(MaxEePrimeSlice2D)+" GeV","");
					legSuSav2_Slice->AddEntry(Q0VsQ3Plot,ToStringDouble(MinCosThetaSlice2D)+ " < cos(#theta_{e'}) < " + ToStringDouble(MaxCosThetaSlice2D),"");

					legSuSav2_Slice->Draw();

				} // End of the loop over the cos theta slices

			} // End of the loop over the Ee' slices

			// ----------------------------------------------------------------------------------------------------------------	

			SuSav2Canvas_ECal_EePrimeAndThetaSlices->cd();
			TPad* padWeightedEventsPerGeV = new TPad("padWeightedEventsPerGeV","padWeightedEventsPerGeV",0.0,0.,0.07,1.,21); 
			padWeightedEventsPerGeV->SetFillColor(kWhite); 
			padWeightedEventsPerGeV->Draw();
			padWeightedEventsPerGeV->cd();

			TLatex latexYTitlepadWeightedEventsPerGeV;
			latexYTitlepadWeightedEventsPerGeV.SetTextFont(FontStyle);
			latexYTitlepadWeightedEventsPerGeV.SetTextSize(6.5*TextSize);
			latexYTitlepadWeightedEventsPerGeV.SetTextColor(kBlack);
			latexYTitlepadWeightedEventsPerGeV.SetTextAngle(90);
			latexYTitlepadWeightedEventsPerGeV.DrawLatexNDC(0.5,0.44,"#frac{d#sigma}{dE_{QE}^{Reso}} [#mub]");

			// ----------------------------------------------------------------------------------------------------------------	

			SuSav2Canvas_ECal_EePrimeAndThetaSlices->cd();
			TPad* padEcal = new TPad("padEcal","padEcal",0.35,0.01,0.7,0.08,21); 
			padEcal->SetFillColor(kWhite); 
			padEcal->Draw();
			padEcal->cd();

			TLatex latexpadEcal;
			latexpadEcal.SetTextFont(FontStyle);
			latexpadEcal.SetTextSize(8*TextSize);
			latexpadEcal.SetTextColor(kBlack);
			latexpadEcal.DrawLatexNDC(0.26,0.5,"(e,e')_{0#pi} E_{QE} Reso");
			
			// ----------------------------------------------------------------------------------------------------------------	

			//SuSav2Canvas_ECal_EePrimeAndThetaSlices->SaveAs("./myPlots/"+CanvasName+".pdf");

			// ----------------------------------------------------------------------------------------------------------------

		} // End of the loop over the energies

		// ----------------------------------------------------------------------------------------------------------------

	} // End of the loop over the nuclei	

} // End of the program
