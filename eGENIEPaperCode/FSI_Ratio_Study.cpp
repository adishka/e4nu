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

void FSI_Ratio_Study() {

	// ----------------------------------------------------------------------------------

	std::vector<TString> nucleus; 
	std::vector<TString> LabelsOfSamples; 
	std::vector<int> Colors;
	std::vector<int> DoubleRatiosColors;
	std::vector<int> Styles;
	std::vector<TString> E;
	std::vector<TString> LabelE;
	std::vector<TString> NameOfPlots;
	std::vector<double> IntegralPlots;
	std::vector<TString> FSIModel;
	std::vector<TString> FSILabel; 
	std::vector<TString> RatioLabel; 
	std::vector<TH1D*> Plots;
	std::vector<TString> Config; 
	std::vector<TString> ConfigLabels; 
	std::vector<TString> InteractionChannel; 
	std::vector<TString> Vars; 

	// ----------------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	int Ndivisions = 6;
	int LineWidth = 3;
	int FontStyle = 132;
	double TextSize = 0.07;
	gStyle->SetOptStat(0);
	gStyle->SetTitleFont(FontStyle,"t");
	gStyle->SetTitleFontSize(TextSize);

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	nucleus.push_back("C12");LabelsOfSamples.push_back("^{12}C");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	E.push_back("1161"); LabelE.push_back(" @ E = 1.161 GeV");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Config.push_back("GTEST19_10a_00_000"); ConfigLabels.push_back("SuSav2 / hA");
	Config.push_back("GTEST19_10b_00_000"); ConfigLabels.push_back("SuSav2 / hN");
	Config.push_back("G18_10a_02_11a"); ConfigLabels.push_back("G2018 / hA");
	Config.push_back("G18_10b_02_11a"); ConfigLabels.push_back("G2018 / hN");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	InteractionChannel.push_back("QE");
//	InteractionChannel.push_back("MEC");
//	InteractionChannel.push_back("RES");
//	InteractionChannel.push_back("DIS");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Vars.push_back("ElectronCosTheta");
	Vars.push_back("ElectronMomentum");
	Vars.push_back("ProtonCosTheta");
	Vars.push_back("ProtonMomentum");
	Vars.push_back("MissMomentum");
	Vars.push_back("DeltaAlphaT");
	Vars.push_back("DeltaPhiT");

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Colors.push_back(kBlue-7); Styles.push_back(7); IntegralPlots.push_back(1.);
	Colors.push_back(kBlue-7); Styles.push_back(kSolid); IntegralPlots.push_back(1.);
	Colors.push_back(kOrange+1); Styles.push_back(7); IntegralPlots.push_back(1.);
	Colors.push_back(kOrange+1); Styles.push_back(kSolid); IntegralPlots.push_back(1.);

	DoubleRatiosColors.push_back(kBlue-7); DoubleRatiosColors.push_back(kOrange+1);  DoubleRatiosColors.push_back(kRed + 1);  DoubleRatiosColors.push_back(kGreen + 2);

	// -------------------------------------------------------------------------------------------

	int NNuclei = nucleus.size();
	int NEnergies = E.size();
	int NPlots = NameOfPlots.size();
	int NConfig = Config.size();
	int NIntChannel = InteractionChannel.size();
	int NVars = Vars.size();

	// -------------------------------------------------------------------------------------------------------

	TH1D* DoubleRatios[NConfig][NIntChannel][NVars];

	// -------------------------------------------------------------------------------------------------------

	// Loop over the energies

	for (int WhichEnergy = 0; WhichEnergy < NEnergies; WhichEnergy ++) {

		// Loop over the nuclei

		for (int WhichNucleus = 0; WhichNucleus < NNuclei; WhichNucleus ++) {

			// Loop over the configurations // GTEST19_10b_00_000 et al

			for (int WhichConfig = 0; WhichConfig < NConfig; WhichConfig ++) {

				// ------------------------------------------------------------------------------------------------------------------------------------------------

				// Must be introduced in pairs (FSI / NoFSI)

				FSIModel.clear(); FSILabel.clear(); RatioLabel.clear();

//				FSIModel.push_back(Config[WhichConfig]+"_CCinclMEC_Q2_0_1_NoFSI"); FSILabel.push_back("#nu_{#mu} CC w/o FSI"); RatioLabel.push_back("#nu_{#mu} CC");
//				FSIModel.push_back(Config[WhichConfig]+"_CCinclMEC_Q2_0_1"); FSILabel.push_back("#nu_{#mu} CC w/  FSI"); RatioLabel.push_back("#nu_{#mu} CC");
//				FSIModel.push_back(Config[WhichConfig]+"_EM+MEC_Q2_0_1_NoFSI"); FSILabel.push_back("e w/o FSI"); RatioLabel.push_back("e");
//				FSIModel.push_back(Config[WhichConfig]+"_EM+MEC_Q2_0_1"); FSILabel.push_back("e w/  FSI"); RatioLabel.push_back("e");

				FSIModel.push_back(Config[WhichConfig]+"_Default_Q2_0_1_NoFSI"); FSILabel.push_back("#nu_{#mu} CC+NC w/o FSI"); RatioLabel.push_back("#nu_{#mu} CC+NC");
				FSIModel.push_back(Config[WhichConfig]+"_Default_Q2_0_1"); FSILabel.push_back("#nu_{#mu} CC+NC w/  FSI"); RatioLabel.push_back("#nu_{#mu} CC+NC");
				FSIModel.push_back(Config[WhichConfig]+"_EM_Q2_0_1_NoFSI"); FSILabel.push_back("e w/o FSI"); RatioLabel.push_back("e");
				FSIModel.push_back(Config[WhichConfig]+"_EM_Q2_0_1"); FSILabel.push_back("e w/  FSI"); RatioLabel.push_back("e");

				int NFSIModels = FSIModel.size();

				// Loop over the interaction channels

				for (int WhichIntChannel = 0; WhichIntChannel < NIntChannel; WhichIntChannel ++) {

					// Loop over the variables to plot

					for (int WhichVar = 0; WhichVar < NVars; WhichVar ++) {

						// --------------------------------------------------------------------------------------------------------------------------------------------

						NameOfPlots.clear();

						NameOfPlots.push_back(InteractionChannel[WhichIntChannel]+Vars[WhichVar]+"Plot_OneProton");
						NameOfPlots.push_back(InteractionChannel[WhichIntChannel]+Vars[WhichVar]+"Plot_OneProton");
						NameOfPlots.push_back(InteractionChannel[WhichIntChannel]+Vars[WhichVar]+"Plot_OneProton");
						NameOfPlots.push_back(InteractionChannel[WhichIntChannel]+Vars[WhichVar]+"Plot_OneProton");

						// --------------------------------------------------------------------------------------------------------------------------------------------------

						TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+Vars[WhichVar]+"_"+Config[WhichConfig]+"_"+InteractionChannel[WhichIntChannel]; 
						TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768) ;

						PlotCanvas->SetBottomMargin(0.14);
						PlotCanvas->SetLeftMargin(0.2);
						PlotCanvas->SetRightMargin(0.02);

						Plots.clear();

						TLegend* leg = new TLegend(0.5,0.6,0.85,0.85);
						if (Vars[WhichVar] == "ElectronMomentum") { leg = new TLegend(0.3,0.6,0.65,0.85); }
						if (Vars[WhichVar] == "ProtonCosTheta") { leg = new TLegend(0.25,0.6,0.6,0.85); }
						if (Vars[WhichVar] == "DeltaAlphaT") { leg = new TLegend(0.5,0.2,0.85,0.45); }
				
						leg->SetNColumns(1);
						leg->SetMargin(0.15);

						TLegend* legRatio = new TLegend(0.6,0.8,0.89,0.89);
						if (Vars[WhichVar] == "ProtonMomentum") { legRatio = new TLegend(0.25,0.8,0.55,0.89); }

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
							Plots[WhichFSIModel]->SetTitle(InteractionChannel[WhichIntChannel] + " " + ConfigLabels[WhichConfig]);

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
							Plots[WhichFSIModel]->GetYaxis()->SetTitle("Area Normalized");
							Plots[WhichFSIModel]->GetYaxis()->CenterTitle();

							TLegendEntry* l1 = leg->AddEntry(Plots[WhichFSIModel],FSILabel[WhichFSIModel], "l");
							l1->SetTextColor(Colors[WhichFSIModel]);

							Plots[WhichFSIModel]->Rebin();

							IntegralPlots[WhichFSIModel] = Plots[WhichFSIModel]->Integral();
							int PlotIndex = 0;
							if (WhichFSIModel == 2 || WhichFSIModel == 3) { PlotIndex = 2; }
							if (WhichFSIModel == 4 || WhichFSIModel == 5) { PlotIndex = 4; }
							if (WhichFSIModel == 6 || WhichFSIModel == 7) { PlotIndex = 6; }
							double ScalingFactor = 1./IntegralPlots[PlotIndex];

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

						PlotCanvas->SaveAs("myPlots/"+CanvasName+".pdf"); 
						delete PlotCanvas;

						// ----------------------------------------------------------------------------------------------------------------------

						// Ratio plot to quantify FSI effect on e/v

						TString RatioCanvasName = "Ratio_"+CanvasName; 
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

							Ratios[WhichRatio]->GetYaxis()->SetRangeUser(0.,2.);
							Ratios[WhichRatio]->GetYaxis()->SetTitle("No FSI / FSI");
							Ratios[WhichRatio]->GetYaxis()->SetTitleOffset(0.9);
							Ratios[WhichRatio]->GetYaxis()->SetNdivisions(5);

							Ratios[WhichRatio]->SetLineStyle(kSolid);
							Ratios[WhichRatio]->Draw("c hist same");

							TLegendEntry* l1 = legRatio->AddEntry(Ratios[WhichRatio],RatioLabel[2*WhichRatio], "l");
							l1->SetTextColor(Colors[2*WhichRatio]);

						}

						legRatio->SetBorderSize(0);
						legRatio->SetTextFont(FontStyle);
						legRatio->SetTextSize(0.07);			
						legRatio->Draw();

						RatioPlotCanvas->SaveAs("myPlots/"+RatioCanvasName+".pdf"); 
						delete RatioPlotCanvas;

						TH1D* DoubleRatio = (TH1D*)Ratios[0]->Clone();
						DoubleRatio->Divide(Ratios[1]);
						DoubleRatios[WhichConfig][WhichIntChannel][WhichVar] = DoubleRatio;
//						DoubleRatio->GetYaxis()->SetRangeUser(0,10);
//						DoubleRatio->GetYaxis()->SetTitle("Double Ratio #nu_{#mu} CC / e");
//						DoubleRatio->Draw("hist same");

						// ----------------------------------------------------------------------------------------------------------------------

					} // End of the loop over the variables to plot

				} // End of the loop over the interaction channels

			} // End of the loop over the configurations

			// ----------------------------------------------------------------------------------------------------------------------

			// Last step: double ratio

			for (int WhichVar = 0; WhichVar < NVars; WhichVar++ ) {
	
				for (int WhichInt = 0; WhichInt < NIntChannel; WhichInt++ ) {

					TString CanvasName = nucleus[WhichNucleus]+"_"+E[WhichEnergy]+"_"+Vars[WhichVar]+"_"+InteractionChannel[WhichInt]; 
					TString DoubleRatioCanvasName = "DoubleRatio_"+CanvasName; 
					TCanvas* DoubleRatioPlotCanvas = new TCanvas(DoubleRatioCanvasName,DoubleRatioCanvasName,205,34,1024,768) ;

					DoubleRatioPlotCanvas->SetBottomMargin(0.14);
					DoubleRatioPlotCanvas->SetLeftMargin(0.13);
					DoubleRatioPlotCanvas->SetRightMargin(0.02);

					TLegend* legDR = new TLegend(0.2,0.62,0.55,0.85);
					if (Vars[WhichVar] == "MissMomentum") { legDR = new TLegend(0.5,0.62,0.85,0.85); }

					legDR->SetNColumns(1);
					legDR->SetMargin(0.15);

					for (int WhichConfig = 0; WhichConfig < NConfig; WhichConfig++ ) {

						DoubleRatios[WhichConfig][WhichInt][WhichVar]->SetTitle("");
						DoubleRatios[WhichConfig][WhichInt][WhichVar]->SetLineColor(DoubleRatiosColors[WhichConfig]);
						DoubleRatios[WhichConfig][WhichInt][WhichVar]->GetYaxis()->SetRangeUser(0,2);
						DoubleRatios[WhichConfig][WhichInt][WhichVar]->GetYaxis()->SetTitle("Double Ratio #nu_{#mu} / e");
						DoubleRatios[WhichConfig][WhichInt][WhichVar]->Draw("c hist same");

						TLegendEntry* l1 = legDR->AddEntry(DoubleRatios[WhichConfig][WhichInt][WhichVar],ConfigLabels[WhichConfig], "l");
						l1->SetTextColor(DoubleRatiosColors[WhichConfig]);

					}	

					legDR->SetBorderSize(0);
					legDR->SetTextFont(FontStyle);
					legDR->SetTextSize(0.07);			
					legDR->Draw();	

					DoubleRatioPlotCanvas->SaveAs("myPlots/"+DoubleRatioCanvasName+".pdf"); 
					delete 	DoubleRatioPlotCanvas;		

				}

			}

		} // End of the loop over the nuclei

	} // End of the loop over the energies

} // End of the program
