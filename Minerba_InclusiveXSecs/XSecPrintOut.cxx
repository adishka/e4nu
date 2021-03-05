#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TString.h>
#include <TColor.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

// ------------------------------------------------------------------------------------------------------------------------------------------------------

void XSecPrintOut() {

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	int SignDigits = 8;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	// Format requested by Pilar Coloma

	//logE     xsec(nue)/E     xsec(numu)/E       xsec(nutau)/E       xsec(nuebar)/E     xsec(numubar)/E       xsec(nutaubar)/E

	cout << fixed;
	std::cout << std::setprecision(SignDigits);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	ofstream G2018File;
	G2018File.open("G2018XSecs.txt");
	G2018File << fixed << setprecision(SignDigits) << endl;

	TFile* G2018File_numu = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_nu_mu_G18_10a_02_11a.root");
	TDirectory* G2018Dir_numu = (TDirectory*)(G2018File_numu->Get("nu_mu_C12"));
	TGraph* G2018Graph_numu = (TGraph*)(G2018Dir_numu->Get("tot_cc"));

	TFile* G2018File_nue = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_nu_e_G18_10a_02_11a.root");
	TDirectory* G2018Dir_nue = (TDirectory*)(G2018File_nue->Get("nu_e_C12"));
	TGraph* G2018Graph_nue = (TGraph*)(G2018Dir_nue->Get("tot_cc"));

	TFile* G2018File_nutau = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_nu_tau_G18_10a_02_11a.root");
	TDirectory* G2018Dir_nutau = (TDirectory*)(G2018File_nutau->Get("nu_tau_C12"));
	TGraph* G2018Graph_nutau = (TGraph*)(G2018Dir_nutau->Get("tot_cc"));

	TFile* G2018File_antinumu = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_anti_nu_mu_G18_10a_02_11a.root");
	TDirectory* G2018Dir_antinumu = (TDirectory*)(G2018File_antinumu->Get("nu_mu_bar_C12"));
	TGraph* G2018Graph_antinumu = (TGraph*)(G2018Dir_antinumu->Get("tot_cc"));

	TFile* G2018File_antinue = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_anti_nu_e_G18_10a_02_11a.root");
	TDirectory* G2018Dir_antinue = (TDirectory*)(G2018File_antinue->Get("nu_e_bar_C12"));
	TGraph* G2018Graph_antinue = (TGraph*)(G2018Dir_nue->Get("tot_cc"));

	TFile* G2018File_antinutau = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_anti_nu_tau_G18_10a_02_11a.root");
	TDirectory* G2018Dir_antinutau = (TDirectory*)(G2018File_antinutau->Get("nu_tau_bar_C12"));
	TGraph* G2018Graph_antinutau = (TGraph*)(G2018Dir_antinutau->Get("tot_cc"));

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	int WhichPointG2018 = 0;

	// The splines go up to 10 GeV, beyond that, they are 0
	// No need to go beyond that

	//cout << "G2018" << endl;
	//cout << "log10(E)\txsec(nue)/E\txsec(numu)/E\txsec(nutau)/E\txsec(nuebar)/E\txsec(numubar)/E\txsec(nutaubar)/E" << endl << endl;
	G2018File << "log10(E)\txsec(nue)/E\txsec(numu)/E\txsec(nutau)/E\txsec(nuebar)/E\txsec(numubar)/E\txsec(nutaubar)/E" << endl << endl;

	while (G2018Graph_numu->GetPointX(WhichPointG2018) < 10) {

		double E = G2018Graph_numu->GetPointX(WhichPointG2018);
		double log10E = log10(E);

		double NuE_XSec = G2018Graph_nue->GetPointY(WhichPointG2018);
		double NuMu_XSec = G2018Graph_numu->GetPointY(WhichPointG2018);
		double NuTau_XSec = G2018Graph_nutau->GetPointY(WhichPointG2018);

		double AntiNuE_XSec = G2018Graph_antinue->GetPointY(WhichPointG2018);
		double AntiNuMu_XSec = G2018Graph_antinumu->GetPointY(WhichPointG2018);
		double AntiNuTau_XSec = G2018Graph_antinutau->GetPointY(WhichPointG2018);

		//cout << log10E << "\t" << NuE_XSec/E << "\t" << NuMu_XSec/E << "\t" << NuTau_XSec/E << "\t" << AntiNuE_XSec/E << "\t" << AntiNuMu_XSec/E << "\t" << AntiNuTau_XSec/E << endl;
		G2018File << log10E << "\t" << NuE_XSec/E << "\t" << NuMu_XSec/E << "\t" << NuTau_XSec/E << "\t" << AntiNuE_XSec/E << "\t" << AntiNuMu_XSec/E << "\t" << AntiNuTau_XSec/E << endl;

		WhichPointG2018++;

	}

	G2018File.close();
	cout << endl << "G2018XSecs.txt created" << endl;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	ofstream SuSav2File;
	SuSav2File.open("SuSav2XSecs.txt");
	SuSav2File << fixed << setprecision(SignDigits) << endl;	

	TFile* SuSav2File_numu = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_nu_mu_GTEST19_10b_00_000.root");
	TDirectory* SuSav2Dir_numu = (TDirectory*)(SuSav2File_numu->Get("nu_mu_C12"));
	TGraph* SuSav2Graph_numu = (TGraph*)(SuSav2Dir_numu->Get("tot_cc"));

	TFile* SuSav2File_nue = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_nu_e_GTEST19_10b_00_000.root");
	TDirectory* SuSav2Dir_nue = (TDirectory*)(SuSav2File_nue->Get("nu_e_C12"));
	TGraph* SuSav2Graph_nue = (TGraph*)(SuSav2Dir_nue->Get("tot_cc"));

	TFile* SuSav2File_nutau = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_nu_tau_GTEST19_10b_00_000.root");
	TDirectory* SuSav2Dir_nutau = (TDirectory*)(SuSav2File_nutau->Get("nu_tau_C12"));
	TGraph* SuSav2Graph_nutau = (TGraph*)(SuSav2Dir_nutau->Get("tot_cc"));

	TFile* SuSav2File_antinumu = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_anti_nu_mu_GTEST19_10b_00_000.root");
	TDirectory* SuSav2Dir_antinumu = (TDirectory*)(SuSav2File_antinumu->Get("nu_mu_bar_C12"));
	TGraph* SuSav2Graph_antinumu = (TGraph*)(SuSav2Dir_antinumu->Get("tot_cc"));

	TFile* SuSav2File_antinue = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_anti_nu_e_GTEST19_10b_00_000.root");
	TDirectory* SuSav2Dir_antinue = (TDirectory*)(SuSav2File_antinue->Get("nu_e_bar_C12"));
	TGraph* SuSav2Graph_antinue = (TGraph*)(SuSav2Dir_nue->Get("tot_cc"));

	TFile* SuSav2File_antinutau = TFile::Open("myXSec/xsec_carbon12_spline_CCinclMEC_anti_nu_tau_GTEST19_10b_00_000.root");
	TDirectory* SuSav2Dir_antinutau = (TDirectory*)(SuSav2File_antinutau->Get("nu_tau_bar_C12"));
	TGraph* SuSav2Graph_antinutau = (TGraph*)(SuSav2Dir_antinutau->Get("tot_cc"));

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

	int WhichPointSuSav2 = 0;

	// The splines go up to 10 GeV, beyond that, they are 0
	// No need to go beyond that

	//cout << endl << "SuSav2" << endl;
	//cout << endl << "log10(E)\txsec(nue)/E\txsec(numu)/E\txsec(nutau)/E\txsec(nuebar)/E\txsec(numubar)/E\txsec(nutaubar)/E" << endl << endl;
	SuSav2File << "log10(E)\txsec(nue)/E\txsec(numu)/E\txsec(nutau)/E\txsec(nuebar)/E\txsec(numubar)/E\txsec(nutaubar)/E" << endl << endl;

	while (SuSav2Graph_numu->GetPointX(WhichPointSuSav2) < 10) {

		double E = SuSav2Graph_numu->GetPointX(WhichPointSuSav2);
		double log10E = log10(E);

		double NuE_XSec = SuSav2Graph_nue->GetPointY(WhichPointSuSav2);
		double NuMu_XSec = SuSav2Graph_numu->GetPointY(WhichPointSuSav2);
		double NuTau_XSec = SuSav2Graph_nutau->GetPointY(WhichPointSuSav2);

		double AntiNuE_XSec = SuSav2Graph_antinue->GetPointY(WhichPointSuSav2);
		double AntiNuMu_XSec = SuSav2Graph_antinumu->GetPointY(WhichPointSuSav2);
		double AntiNuTau_XSec = SuSav2Graph_antinutau->GetPointY(WhichPointSuSav2);

		//cout << log10E << "\t" << NuE_XSec/E << "\t" << NuMu_XSec/E << "\t" << NuTau_XSec/E << "\t" << AntiNuE_XSec/E << "\t" << AntiNuMu_XSec/E << "\t" << AntiNuTau_XSec/E << endl;
		SuSav2File << log10E << "\t" << NuE_XSec/E << "\t" << NuMu_XSec/E << "\t" << NuTau_XSec/E << "\t" << AntiNuE_XSec/E << "\t" << AntiNuMu_XSec/E << "\t" << AntiNuTau_XSec/E << endl;

		WhichPointSuSav2++;

	}

	SuSav2File.close();
	cout << endl << "SuSav2XSecs.txt created" << endl << endl;

	// ------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program
