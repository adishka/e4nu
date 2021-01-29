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

const Double_t fid_2gev_2250_pimifid_outline[6][6][5]={ { {437.992 , -6758.33 , 44725 , -130667 , 140000},
                { -108.89 , 2441.34 , -16273.9,  46629.1 , -48613.3},
                {23.4972 , -22.8102 , 58.051 , 455.812 , -1355.76},
                {-1282.61 , 26039.3 , -176254 , 497349 , -504262},
                {79.2767 , 10.9846 , -1097.42 , -2505.95 , 11295.1},
                {-116.656 , 5464.17 , -39666.7 , 121333 , -133333} },
                { {294.906 , -3993.33 , 25700 , -74666.7 , 80000},
                {-1.73619 , 230.33 , -230.96 , -2041.14 , 4247.97},
                {-8.35081 , 294.696 , -351.216 , -2783.33 , 6284.44},
                { -654.396 , 13447.8 , -95677.4 , 289413 , -316333},
                {-1087.77 , 21543.4 , -150270 , 446839 , -481346},
                {-12.4219 , 3796.67 , -30450 , 101333 , -120000} },
                { {169.867 , -1621.67 , 9791.67 , -29333.3 , 33333.3},
                {1.31563 , 228.273 , -277.831 , -2151.54 , 4681.77},
                {4.99614 , 143.415 , -99.2912 , -1182.49 , 2131.09},
                {-442.257 , 10171.2 , -74092.5 , 222973 , -240250},
                {286.575 , -4807.23 , 31987.4 , -94543 , 102888},
                {-80.793 , 4620.91 , -32275.5 , 94668.1 , -100002} },
                { {171.781 , -1604.17 , 9133.31 , -25333.3 , 26666.7},
                {15.4017 , 65.7045 , -29.3075 , -398.534 , 391.892},
                {-105.713 , 2167.31 , -13426.9 , 36592.6 , -36900.5},
                {-117.86 , 4749.21 , -44679.4 , 161213 , -199605},
                {-1228.95 , 24386.5 , -171732 , 516890 , -564141},
                {314.227 , -2770.83 , 17208.3 , -46666.6 , 46666.7} },
                { {227.727 , -2592.5 , 15608.3 , -44000 , 46666.7},
                {-108.819 , 2413.21 , -16243.6 , 47773.3 , -51709},
                {-1.34202 , 206.441 , -194.54 , -1788.54 , 3644.16},
                {-2105.78 , 42101.1 , -299023 , 908108 , -1.00031e+06},
                {-542.533 , 11447.1 , -83967.3 , 260870 , -292292},
                {198.746 , -468.327 , 479.183 , 5155.48 , -11578.4} },
                { {205.403 , -1966.22 , 9777.77 , -22675.4 , 20010.2},
                {5.0732 , 177.775 , -195.135 , -1565.26 , 3219.17},
                {114.9 , -2022.82 , 15044.2 , -46493.2 , 51247.4},
                {214.243 , -4966.33 , 42750.9 , -149352 , 180657},
                {1230.36 , -24868.8 , 180507 , -555189 , 613732},
                {166.471 , -85.4706 , -94.7685 , 1150.18 , -2073.65} } };

const Float_t fgPar_2GeV_2250_Efid[6][6][9] = {{
              {62.2935, -92.5133, 87.0360, -38.4696, 6.3177, 0, 0, 0, 0},
              {78.5134, -58.5975, 3.30928, 77.4749, -64.3984, 14.4860, 0, 0, 0},
              {-140.845, 1381.30, -4499.99, 7557.27, -7140.27, 3828.75, -1086.21, 126.468, 0},
              {497.951, -1846.42, 2759.58, -1634.71, 345.006, 0, 0, 0, 0},
              {9.40986, 180.752, -646.771, 1055.14, -909.094, 424.435, -99.8368, 9.02086, 0},
              {288.485, -1016.03, 1463.72, -859.231, 185.976, 0, 0, 0, 0}},
              {{61.1474, -88.768, 82.6446, -36.2780, 5.92310, 0, 0, 0, 0},
              {78.5134, -58.5975, 3.30928, 77.4749, -64.3984, 14.4860, 0, 0, 0},
              {21.3087, 138.975, -672.710, 1324.20, -1326.12, 714.866, -197.531, 21.9144, 0},
              {375.091, -1411.50, 2082.58, -1192.17, 239.685, 0, 0, 0, 0},
              {-121.816, 1182.59, -3800.98, 6319.82, -5937.33, 3179.37, -903.954, 105.764, 0},
              {-4781.96, 43165.9, -159567, 318502, -376469, 271207, -116893, 27698.9, -2775.61}},
                 {{61.1474, -88.7680, 82.6446, -36.2780, 5.92310, 0, 0, 0, 0},
              {73.7620, -34.6321, -41.8796, 117.543, -81.2043, 17.1718, 0, 0, 0},
              {157.046, -765.472, 1735.21, -2053.86, 1371.34, -515.214, 101.081, -8.07402, 0},
              {-608.740, 4827.18, -13239.6, 17742.4, -12420.0, 4369.11, -607.877, 0, 0},
              {-274.278, 2380.63, -7560.19, 12582.3, -11924.5, 6464.66, -1863.44, 221.134, 0},
              {-1240.72, 8096.04, -19407.0, 23942.9, -16052.3, 5559.32, -776.123, 0, 0}},
                 {{61.1474, -88.7680, 82.6446, -36.2780, 5.92310, 0, 0, 0, 0},
              {78.5134, -58.5975, 3.30928, 77.4749, -64.3984, 14.4860, 0, 0, 0},
              {-71.2528, 879.668, -3027.37, 5226.61, -4999.19, 2689.35, -761.206, 88.1242, 0},
              {-1269.89, 9486.25, -26103.8, 35581.2, -25373.0, 9062.87, -1277.60, 0, 0},
              {-186.640, 1811.85, -6032.01, 10283.3, -9808.11, 5285.35, -1501.87, 174.799, 0},
              {-530.826, 4643.56, -13864.2, 20580.2, -15898.0, 6106.69, -916.365, 0, 0}},
                 {{61.6665, -90.4268, 84.5606, -37.2240, 6.09207, 0, 0, 0, 0},
              {78.5134, -58.5975, 3.30928, 77.4749, -64.3984, 14.4860, 0, 0, 0},
              {-1.53910, 216.936, -701.057, 1167.26, -1111.92, 615.364, -183.854, 22.8595, 0},
              {-19.7415, 454.317, -1250.51, 1512.52, -762.408, 137.695, 0, 0, 0},
              {-55.9612, 657.449, -2049.73, 3295.30, -2995.85, 1553.68, -427.764, 48.4324, 0},
              {-522.682, 3356.77, -7535.50, 8756.49, -5518.61, 1795.60, -235.144, 0, 0}},
                 {{61.1474, -88.7680, 82.6446, -36.2780, 5.92310, 0, 0, 0, 0},
              {73.7620, -34.6321, -41.8796, 117.543, -81.2043, 17.1718, 0, 0, 0},
              {-82.0368, 883.261, -2828.84, 4621.53, -4223.56, 2185.52, -598.218, 67.2908, 0},
              {608.323, -2743.56, 4942.01, -4045.58, 1558.07, -226.240, 0, 0, 0},
              {4.07203, 138.882, -321.983, 282.702, -12.9566, -129.159, 74.5884, -12.9994, 0},
              {-866.737, 5984.13, -15129.6, 19134.6, -12757.7, 4276.79, -566.056, 0, 0}}};

// -------------------------------------------------------------------------------------------------------------

void Create2DPlots_FitOutline_PiMinus() {

	int FontStyle = 132;
	double TextSize = 0.08;
	const int n = 500; const double min = 0., max = 5.;

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(TextSize,"t"); gStyle->SetTitleFont(FontStyle,"t"); SetOffsetAndSize();

	// -------------------------------------------------------------------------------------------------------------

	TString YLabelOfPlots = "#theta_{#pi^{-}}";
	TString XLabelOfPlots = "P_{#pi^{-}} [GeV/c]";
	TString PlotName = "h2_PiMinus_Theta_Momentum";

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
//	nucleus.push_back("12C"); LabelsOfSamples.push_back("^{12}C");
	nucleus.push_back("56Fe"); LabelsOfSamples.push_back("^{56}Fe");

//	E.push_back("1_161"); LabelE.push_back(" @ E = 1.161 GeV");
//	E.push_back("2_261"); LabelE.push_back(" @ E = 2.261 GeV");
	E.push_back("4_461"); LabelE.push_back(" @ E = 4.461 GeV");

	xBCut.push_back("NoxBCut");

	FSIModel.push_back("Pinned_Data_Final"); FSILabel.push_back("Data");
//	FSIModel.push_back("SuSav2_RadCorr_LFGM"); FSILabel.push_back("SuSav2");
	FSIModel.push_back("SuSav2_RadCorr_LFGM_UpdatedSchwinger"); FSILabel.push_back("SuSav2 (Ext+Int Rad)");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM"); FSILabel.push_back("True 1p0pi W/");
//	FSIModel.push_back("hA2018_Final_RadCorr_LFGM_UpdatedSchwinger"); FSILabel.push_back("G2018 (Ext+Int Rad)");

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	NameOfPlots.push_back(PlotName+"_FirstSector"); Title.push_back(" (1st Sector)"); IntSector.push_back(3);
	NameOfPlots.push_back(PlotName+"_SecondSector"); Title.push_back(" (2nd Sector)"); IntSector.push_back(4);
	NameOfPlots.push_back(PlotName+"_ThirdSector"); Title.push_back(" (3rd Sector)"); IntSector.push_back(5);
	NameOfPlots.push_back(PlotName+"_FourthSector"); Title.push_back(" (4th Sector)"); IntSector.push_back(0);
	NameOfPlots.push_back(PlotName+"_FifthSector"); Title.push_back(" (5th Sector)"); IntSector.push_back(1);
	NameOfPlots.push_back(PlotName+"_SixthSector"); Title.push_back(" (6th Sector)"); IntSector.push_back(2);

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

						// Outline

						double x[n],y[n];

						for (int i = 0; i < n; i++) {

							double CurrentX = min + i * (max - min) / n;
							x[i] = CurrentX;
							
							double CurrentY = 50.;
							double params = 0;

							// ----------------------------------------------------------------------------------------------------------------

							if (E[WhichEnergy] == "2_261" || E[WhichEnergy] == "4_461") {

								if (CurrentX <= 0.35) {

									for (int d = 4; d >= 0; d--) {

										params = params * CurrentX + fid_2gev_2250_pimifid_outline[IntSector[WhichPlot]][0][d];

									} // calculate the parameters using pol4

								} else {

									for (int d = 8; d>= 0; d--) {

										params = params * CurrentX +  fgPar_2GeV_2250_Efid[IntSector[WhichPlot]][0][d];

									} // calculate the parameters using pol8

								}

							}

							// ----------------------------------------------------------------------------------------------------------------

							CurrentY = params;
							y[i] = CurrentY;

						}

						TGraph* g = new TGraph(n,x,y);
						g->SetLineWidth(3);
						g->SetLineColor(kRed);
						//g->Draw("c");

						// ----------------------------------------------------------------------------------------------------------------

						if (E[WhichEnergy] == "1_161") {

							TF1* f = new TF1("f","17.+4./TMath::Power(x,1.)",0,5.);
							f->SetLineWidth(3);
							f->SetLineColor(kGreen);
							f->Draw("same");

						}

						if (E[WhichEnergy] == "2_261") {

							TF1* f = new TF1("f","(x<0.35)*(25.+7./TMath::Power(x,1.)) + (x>0.35)*(16.+10/TMath::Power(x,1.))",0,5.);
							f->SetLineWidth(3);
							f->SetLineColor(kGreen);
							f->Draw("same");

						}

						if (E[WhichEnergy] == "4_461") {

							TF1* f = new TF1("f","(x<0.35)*(25.+7./TMath::Power(x,1.)) + (x>0.35)*(16.+10/TMath::Power(x,1.))",0,5.);
							f->SetLineWidth(3);
							f->SetLineColor(kGreen);
							f->Draw("same");
							
						}
				
						// ----------------------------------------------------------------------------------------------------------------

					} // End of the loop over the FSI Models 

				} // End of the loop over the plots

			} // End of the loop over the nuclei

		} // End of the loop over the energies

	} // End of the loop over the xB kinematics

} // End of the program
