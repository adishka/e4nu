#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TGaxis.h>
#include <TROOT.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

TString ToString(double num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;
}

void QuickInclusiveComparison() {

	int FontStyle = 132;
	int Ndivisions = 8;
	double TextSize = 0.07;
	TGaxis::SetMaxDigits(3);
	TGaxis::SetExponentOffset(-0.1, 1., "y");
//	TGaxis::SetExponentOffset(-0.05, 0., "y");

	// ---------------------------------------------------------------------------------------------

	TString target = "C"; 

	double Energy = 1.161;

	double angle = 37.5;

//	TString Tune = "GTEST19_10b_00_000";

	// ---------------------------------------------------------------------------------------------

	// Event Files

//	TString dicriminator = "";
//	TString dicriminator = "_TwoRes";
//	TString dicriminator = "_Q2_0_8";

//	TString PathToSamples = "mySamples/";
//	TString PathToSimSamples = "/pnfs/genie/persistent/users/apapadop/"+Tune+dicriminator+"/";
//	TFile* DataFile = TFile::Open(PathToSamples+"eQEupdated.root");
//	TTree* DataTree = (TTree*)(DataFile->Get("qent"));
	
	TString EnergyString = ToString(Energy).ReplaceAll(".",""); 
	TString angleString = ToString(angle).ReplaceAll(".","_");	

	// ---------------------------------------------------------------------------------------------

	// XSec Files

//	TString PathToXSec = "myXSec/";
	vector <TString> xsec_file;
	TString Nucleus = "";
	int Z = 6, A = 12;

	xsec_file.push_back("/pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/v3_2/xsec_11_1000060120_EM_G18_10a_02_11a_Q2_0_1.root");
//	xsec_file.push_back("/pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/v3_2/xsec_11_1000060120_EM_GTEST19_10b_00_000_Q2_0_1.root");
		
	vector <TFile*> SimulationFile;
	SimulationFile.clear();

	vector <TString> xsec_Eventfile;
	xsec_Eventfile.push_back("/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/C12_1161GeV/apapadop_G2018_C12_1161GeV_master.root");	
//	xsec_Eventfile.push_back("/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/C12_1161GeV/apapadop_SuSav2_C12_1161GeV_master.root");	

	// ---------------------------------------------------------------------------------------------

	// TChain common for data & simulation

	vector <TChain*> event_chain;
	event_chain.push_back(new TChain("gst"));

	// ---------------------------------------------------------------------------------------------

	// Constants

	int NBins = 30;

	double ThetaCut = 1.5; // degrees
//	double ThetaCut = 2.; // degrees
	double ThetaCut_Rad = ThetaCut * TMath::Pi() / 180.; // degrees


	const TString dirname = "e-_"+target+ToString(A);
	const TString xsec_spline_name = "tot_em";
//	const TString xsec_spline_name = "qel_em_p";

	// ---------------------------------------------------------------------------------------------

	// Vectors / Angles

//	vector <double> angle;
//	vector <TString> angleString;

	double min = -1;
	double max = 10;

	if (angle == 60 && Energy == 0.24) { min = 0.005; max = 0.12; }
	if (Energy == 0.56 && target == "C" && angle == 36) { min = 0.0; max = 0.42; }
	if (Energy == 0.56 && target == "C" && angle == 60) { min = 0.0; max = 0.47; }	
	if (Energy == 0.56 && target == "Fe") { min = 0.05; max = 0.42; }	
	if (Energy == 0.961 && target == "He") { min = 0.0; max = 0.7; }	
	if (Energy == 0.961 && target == "C") { min = 0.0; max = 0.7; }
	if (Energy == 0.961 && target == "Fe") { min = 0.0; max = 0.71; }	
	if (Energy == 1.161 && target == "C") { min = 0.05; max = 0.75; }
	if (Energy == 1.299 && target == "C") { min = 0.1; max = 0.84; }
	if (Energy == 1.299 && target == "Fe") { min = 0.1; max = 0.83; }
	if (Energy == 1.501 && target == "C") { min = 0.22; max = 1.; }	
	if (Energy == 2.222) { min = 0.0; max = 0.98; }		
	if (Energy == 3.595 && target == "C" && angle == 16) { min = 0.2; max = 1.6; }		
	if (Energy == 3.595 && target == "C" && angle == 20) { min = 0.3; max = 1.; }		
	if (Energy == 3.595 && target == "C" && angle == 25) { min = 0.66; max = 1.2; }
        if (Energy == 2.222 && target == "Ar" && angle == 15.54) { min = 0.; max = 1.; }	

	const int NAngles = 1;
	TH1D* hData[NAngles];

	// ---------------------------------------------------------------------------------------------

	for (int WhichSimFile = 0; WhichSimFile < (int)(xsec_file.size()); WhichSimFile++) {

		SimulationFile.push_back(TFile::Open(xsec_file[WhichSimFile]));

		vector <TString> CurrentTitle;
		vector <TLatex*> CurrentLatexTitle;
		vector <TCanvas*> CurrentCan;
		vector <TLegend*> CurrentLeg;

		event_chain[WhichSimFile]->Add(xsec_Eventfile[WhichSimFile]);

		for (int WhichAngle = 0; WhichAngle < NAngles; WhichAngle++) {

			// Create the legent, title etc

			CurrentTitle.push_back("^{"+ToString(A)+"}"+target+" @E = "+ToString(Energy)+" GeV & #it{#theta} = " + ToString(angle) + "^{o}");
//			CurrentTitle.push_back(target+"(e,e\'): "+ToString(Energy)+" GeV at " + ToString(angle) + "^{o}");
//			CurrentLatexTitle.push_back(new TLatex(0.2,0.92,CurrentTitle[WhichAngle]));
			CurrentLatexTitle.push_back(new TLatex(0.22,0.92,CurrentTitle[WhichAngle]));
//			CurrentLatexTitle.push_back(new TLatex(0.29,0.83,CurrentTitle[WhichAngle]));
			CurrentLatexTitle[WhichAngle]->SetNDC(kTRUE);
			CurrentLatexTitle[WhichAngle]->SetTextFont(FontStyle);
			CurrentLatexTitle[WhichAngle]->SetTextSize(TextSize);

			CurrentLeg.push_back(new TLegend(0.22,0.7,0.62,0.87));

			CurrentCan.push_back(new TCanvas(target+"_"+ToString(angle),target+"_"+ToString(angle),205,34,1024,768));

			// Declare the cuts

			double Emin = Energy - 0.002;
			double Emax = Energy + 0.002;

			// ---------------------------------------------------------------------------------------------

			// Data 

//			int nData = DataTree->Draw("v:xsec:xsec_err","(E == "+ToString(Energy)+" && Z == "+ToString(Z)
//				+" && A == "+ToString(A)+" && abs(theta - "+
//				ToString(angle)+") < "+ToString(ThetaCut)+")*xsec","goff"); 
//			TGraphErrors *DataGraph = new TGraphErrors(nData,DataTree->GetV1(),DataTree->GetV2(),0,DataTree->GetV3());

//			hData[WhichAngle] = new TH1D("hData"+ ToString(angle),";Ev - El;",NBins,min,max);

//			DataTree->Draw("v>>hData"+ ToString(angle),"(E == "+ToString(Energy)+" && Z == "+ToString(Z)
//				+" && A == "+ToString(A)+" && abs(theta - "+ToString(angle)
//				+") < "+ToString(ThetaCut)+")*xsec");

//			double DataIntegral = DataGraph->GetHistogram()->GetMaximum();

			CurrentCan[WhichAngle]->cd();
			CurrentCan[WhichAngle]->SetBottomMargin(0.13);
			CurrentCan[WhichAngle]->SetLeftMargin(0.16);

//			DataGraph->SetTitle("");
//			DataGraph->SetMarkerStyle(20);
//			DataGraph->SetMarkerSize(1.5);
//			DataGraph->SetLineWidth(3);

//			DataGraph->GetHistogram()->GetXaxis()->SetRangeUser(min,max);
//			DataGraph->GetHistogram()->GetXaxis()->CenterTitle();
//			DataGraph->GetHistogram()->GetXaxis()->SetTitle("Energy Transfer [GeV]");
//			DataGraph->GetHistogram()->GetXaxis()->SetLabelSize(TextSize);
//			DataGraph->GetHistogram()->GetXaxis()->SetTitleSize(TextSize);
//			DataGraph->GetHistogram()->GetXaxis()->SetLabelFont(FontStyle);
//			DataGraph->GetHistogram()->GetXaxis()->SetTitleFont(FontStyle);
//			DataGraph->GetHistogram()->GetXaxis()->SetNdivisions(Ndivisions);
//			DataGraph->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);

//			DataGraph->GetHistogram()->GetYaxis()->SetRangeUser(0,1.3*DataGraph->GetHistogram()->GetMaximum());

			double YMaxRange = 1.15;
			if (Energy == 3.595) { YMaxRange = 1.5; }	
			if (Energy == 1.501) { YMaxRange = 1.7; }
			if (Energy == 1.299) { YMaxRange = 1.35; }	
			if (Energy == 0.56 && angle == 36) { YMaxRange = 1.2; }
			if (Energy == 0.56 && angle == 60) { YMaxRange = 1.25; }

//			DataGraph->GetHistogram()->GetYaxis()->SetRangeUser(0,YMaxRange*DataGraph->GetHistogram()->GetMaximum());
//			if (Energy == 0.24) { DataGraph->GetHistogram()->GetYaxis()->SetRangeUser(0,0.26*DataGraph->GetHistogram()->GetMaximum()); }
//			
//			
//			DataGraph->GetHistogram()->GetYaxis()->CenterTitle();
////			DataGraph->GetHistogram()->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [nb/sr/GeV]");
//			DataGraph->GetHistogram()->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [#mub/sr/GeV]");
//			DataGraph->GetHistogram()->GetYaxis()->SetLabelSize(TextSize);
//			DataGraph->GetHistogram()->GetYaxis()->SetTitleSize(TextSize);
//			DataGraph->GetHistogram()->GetYaxis()->SetLabelFont(FontStyle);
//			DataGraph->GetHistogram()->GetYaxis()->SetTitleFont(FontStyle);
//			DataGraph->GetHistogram()->GetYaxis()->SetNdivisions(Ndivisions);
//			DataGraph->GetYaxis()->SetTitleOffset(1.);

//			DataGraph->Draw("ap");
//			CurrentLeg[WhichAngle]->AddEntry(DataGraph,"Data","lep");
			
			TString OutputFileString = TString(target)+ToString(A)+"_E_"+EnergyString+"_theta_"+angleString+".root";
			TFile* OutputFile = new TFile(OutputFileString,"recreate");
			OutputFile->cd();
//			DataGraph->Write("Data");			

			// ---------------------------------------------------------------------------------------------

			// Simulation

			SimulationFile[WhichSimFile]->cd();
			TDirectory * dir = (TDirectory*)SimulationFile[WhichSimFile]->Get(dirname);

			TGraph * xsec_em_gr = (TGraph*)dir->Get(xsec_spline_name);
			double xsec_em = xsec_em_gr->Eval(Energy);

			xsec_em *= (1E-5); // (1E-38  * units::cm2 / units::nb); // convert from cm2 to nbarn
//			xsec_em *= (1E-2); // (1E-38  * units::cm2 / units::nb); // convert from cm2 to microbarn   
						                                                             
			event_chain[WhichSimFile]->Draw("1", Form("(Ev>=%f)&&(Ev<%f)&&(Z==%d)&&(A==%d)&&(em)",Emin,Emax,Z,A), "GOFF");
			double nentries_all = event_chain[WhichSimFile]->GetSelectedRows();

			double dv = (max - min) / NBins;

			double scale = xsec_em / (nentries_all*dv * 2 * TMath::Pi() 
				       * abs( cos( (angle + ThetaCut) *TMath::Pi() / 180.) - cos( (angle - ThetaCut) *TMath::Pi() / 180.) ));

			const int ngraphs = 5;

                        TString StandardCuts = "Ev > " + ToString(Emin) +" && Ev < " + ToString(Emax)+" && Z == "+ToString(Z)+" && A == "+ToString(A);

			TString SimulationCuts = StandardCuts + " && abs(TMath::ACos(cthl)*180./TMath::Pi() - " + ToString(angle) +") < "+ToString(ThetaCut);

			TString cut = "ThetaCut";

			TString select_events_in_costheta_bin[ngraphs] = {
				SimulationCuts + " &&(em)", SimulationCuts + " &&(em && qel)", SimulationCuts + " &&(em && mec)", SimulationCuts + " &&(em && res)", 
				SimulationCuts + " &&(em && (!qel&&!mec&&!res))"
			};

			//TString label[ngraphs] = { "Total", "Quasi-elastic", "Meson Exchange", "Resonance", "Other"};
//			TString label[ngraphs] = { "GENIE (Total)", "QE", "MEC", "RES", "DIS"};
			TString label[ngraphs] = { "SuSav2 (Total)", "QE", "MEC", "RES", "DIS"};
//			int color[ngraphs] = { kBlack, kBlue,  kMagenta,   kRed,   kGreen };
//			int color[ngraphs] = { kBlack, kBlue,  429,   410,   610 };
			int color[ngraphs] = { kBlack, kBlue+1,kRed-3,kGreen+1,kOrange+1 };
			int style[ngraphs] = { kSolid, kSolid, kSolid, kSolid, kSolid };
			int width[ngraphs] = { 2,      2,      2,       2,      2      };

			// ---------------------------------------------------------------------------------------------

			// Loop over the different interaction channels

			for(int igr = 0; igr < ngraphs; igr++) {

				TH1D * v_distribution = new TH1D("v_distribution_"+ToString(igr)+"_"+ToString(angle),"",NBins,min,max);
				event_chain[WhichSimFile]->Draw("Ev-El>>v_distribution_"+ToString(igr)+"_"+ToString(angle), select_events_in_costheta_bin[igr], "goff");
				double nentries = event_chain[WhichSimFile]->GetSelectedRows();
				v_distribution->GetXaxis()->SetRangeUser(min,max);

				v_distribution->Scale(scale);
				double * v = new double[NBins];
				double * d2sigma_dEpdOmega = new double[NBins];

				for(int i=0; i < NBins; i++) {

					v[i] = v_distribution->GetBinCenter(i+1);
					d2sigma_dEpdOmega[i] = v_distribution->GetBinContent(i+1);

				}

				TGraph * gr = new TGraph(NBins,v,d2sigma_dEpdOmega);

				CurrentCan[WhichAngle]->cd();
				gr->SetTitle("");
				gr->SetLineColor(color[igr]);
				gr->SetLineStyle(style[igr]);
				gr->SetLineWidth(3);
				//gr->Draw("c same");

				CurrentLeg[WhichAngle]->AddEntry(gr,label[igr],"l");

				// ---------------------------------------------------------------------------------------------

				// Latex 

				TLatex* LatexProcess = new TLatex();
				LatexProcess->SetTextFont(FontStyle);
				LatexProcess->SetTextSize(TextSize);
				LatexProcess->SetTextColor(color[igr]);

				if (label[igr] == "SuSav2 (Total)") { 
					
					gr->GetHistogram()->GetXaxis()->SetRangeUser(min,max);
					gr->GetHistogram()->GetXaxis()->CenterTitle();
					gr->GetHistogram()->GetXaxis()->SetTitle("Energy Transfer [GeV]");
					gr->GetHistogram()->GetXaxis()->SetLabelSize(TextSize);
					gr->GetHistogram()->GetXaxis()->SetTitleSize(TextSize);
					gr->GetHistogram()->GetXaxis()->SetLabelFont(FontStyle);
					gr->GetHistogram()->GetXaxis()->SetTitleFont(FontStyle);
					gr->GetHistogram()->GetXaxis()->SetNdivisions(Ndivisions);
					gr->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);

					gr->GetHistogram()->GetYaxis()->CenterTitle();
					gr->GetHistogram()->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{d#Omega dE} [#mub/sr/GeV]");
					gr->GetHistogram()->GetYaxis()->SetLabelSize(TextSize);
					gr->GetHistogram()->GetYaxis()->SetTitleSize(TextSize);
					gr->GetHistogram()->GetYaxis()->SetLabelFont(FontStyle);
					gr->GetHistogram()->GetYaxis()->SetTitleFont(FontStyle);
					gr->GetHistogram()->GetYaxis()->SetNdivisions(Ndivisions);
					gr->GetYaxis()->SetTitleOffset(1.);

					gr->Draw("ac same");

				} else { gr->Draw("c same"); }
				
				if (label[igr] == "SuSav2 (Total)") { 
					
					if (target != "Ar") { LatexProcess->DrawLatexNDC(0.29,0.76,label[igr]); }
					else { LatexProcess->DrawLatexNDC(0.29,0.62,label[igr]); }
				}
				if (label[igr] == "QE") { 
				
					if (target != "Ar") { LatexProcess->DrawLatexNDC(0.36,0.45,label[igr]); }
					else { LatexProcess->DrawLatexNDC(0.3,0.45,label[igr]); }
					
				}
				
				if (label[igr] == "MEC") { LatexProcess->DrawLatexNDC(0.29,0.23,label[igr]); }
				
				if (label[igr] == "RES") { 
				
					if (target != "Ar") { LatexProcess->DrawLatexNDC(0.64,0.37,label[igr]); }
					else { LatexProcess->DrawLatexNDC(0.52,0.3,label[igr]); }
					
				}
				
				if (label[igr] == "DIS") { 
				
					if (target != "Ar") { LatexProcess->DrawLatexNDC(0.7,0.23,label[igr]); }
					else { LatexProcess->DrawLatexNDC(0.7,0.18,label[igr]); }
					
				}

				if (igr == 4) { 

					TLatex* LatexData = new TLatex();
					LatexData->SetTextFont(FontStyle);
					LatexData->SetTextSize(TextSize);
					LatexData->SetTextColor(kBlack);
					//if (target != "Ar") { LatexData->DrawLatexNDC(0.31,0.53,"Data"); }
					//else { LatexData->DrawLatexNDC(0.19,0.74,"Data"); } 

				}

				// ---------------------------------------------------------------------------------------------

				delete [] v;
				delete [] d2sigma_dEpdOmega;
				delete v_distribution;
				
				if (igr == 0) { OutputFile->cd(); gr->Write("Simulation"); }
				if (igr == 1) { OutputFile->cd(); gr->Write("SimulationQE"); }					
				if (igr == 2) { OutputFile->cd(); gr->Write("SimulationMEC"); }
				if (igr == 3) { OutputFile->cd(); gr->Write("SimulationRES"); }
				if (igr == 4) { OutputFile->cd(); gr->Write("SimulationDIS"); }	

			}

			// Plot the data graph again so that the points are on top of the genie breakdown lines

//			DataGraph->Draw("p");

			// ---------------------------------------------------------------------------------------------

			// Legend

			CurrentLeg[WhichAngle]->SetBorderSize(0);
			CurrentLeg[WhichAngle]->SetNColumns(3);
			CurrentLeg[WhichAngle]->SetColumnSeparation(2.);
			CurrentLeg[WhichAngle]->SetTextFont(FontStyle);
			CurrentLeg[WhichAngle]->SetTextSize(TextSize);
			//CurrentLeg[WhichAngle]->Draw(); // Remove it for now because we want the latex labels

//			TString CurrentTitle = target+"(e,e\'): "+ToString(Energy)+" GeV at " + ToString(angle) + "^{o}";
			TString CurrentTitle = "(e,e\') ^{"+ToString(A)+"}"+target+", #theta = "+ToString(angle) + "^{o}, "+ToString(Energy)+" GeV";
				
			double XPos = 0.23, YPos = 0.92;

			TLatex* CurrentLatexTitle = new TLatex(XPos,YPos,CurrentTitle);
			CurrentLatexTitle->SetNDC(kTRUE);
			CurrentLatexTitle->SetTextFont(FontStyle);
			CurrentLatexTitle->SetTextSize(TextSize);
			CurrentLatexTitle->Draw();								
			
			// Export as pdf

//			TString Extension = "";
//			TString NamePlot = Extension+"InteractiveOverlay_"+target+"_E_"+EnergyString+"_theta_"+angleString;
//			CurrentCan[WhichAngle]->SaveAs("./myPlots/"+NamePlot+".pdf");
			

		} // End of the loop over the angles

	} // End of the loop over the simulation files
	
	

} // End of the program
