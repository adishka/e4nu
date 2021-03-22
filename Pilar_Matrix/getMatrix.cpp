#include "TH1.h"
#include "TH3.h"
#include "TFile.h"
#include "TF1.h"
#include "TGraph.h"
#include "TChain.h"
#include "TMath.h"
#include "TVector3.h"
#include "TStyle.h"
#include "TH2D.h"
#include "TGaxis.h"
#include "TImage.h"
#include "TCanvas.h"
#include "TPaveLabel.h"
#include "TSystem.h"
#include "TMatrixD.h"
#include "TDecompSVD.h"
#include "TRandom3.h"
#include "TLegend.h"
#include "TStyle.h"
#include <string> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void getMatrix() {

	// The 3 resolution plots need to have the same binning

	// ----------------------------------------------------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	// -----------------------------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);

	int Ndivisions = 4;
	int FontStyle = 132;
	double TextSize = 0.08;

	gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); 
	gStyle->SetTitleSize(TextSize,"xyzt"); gStyle->SetTitleFont(FontStyle,"xyzt");
	gStyle->SetLabelSize(TextSize,"xyzt"); gStyle->SetLabelFont(FontStyle,"xyzt");

	// -----------------------------------------------------------------------------------------------------------------------

//	XSec
	string inputFile = "/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/e4nu/SuSav2_e4nuPaper_PlottingCode/AccCorrXSec/myXSec/FineBin_ECalReso_AccCorr_XSec_NoxBCut.root";

//	Normalized Yield
//	string inputFile = "/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/e4nu/SuSav2_e4nuPaper_PlottingCode/AbsXSecNorm/myXSec/FineBin_ECalReso_NormYield_NoxBCut.root";

//	Area Normalized
//	string inputFile = "/home/afroditi/Dropbox/PhD/myCode/30th_Refactorization/e4nu/SuSav2_e4nuPaper_PlottingCode/AreaNormalized/myXSec/FineBin_ECalReso_AreaNorm_NoxBCut.root";

	// -----------------------------------------------------------------------------------------------------------------------

	int Nbins = 50;
	float Emin = 0.;
	float Emax = 5.;
	int itts = 10000000; // 1M iterations // default
//	int itts = 100; // trial

	gRandom = new TRandom3(0);

	// -------------------------------------------------------------------------------------------------------------------------

	string element = "12C";
	vector<string> energies;
	energies.push_back("1_161");
	energies.push_back("2_261");
	energies.push_back("4_461");

	// -------------------------------------------------------------------------------------------------------------------------

	vector<float> energy_vals;
	energy_vals.push_back(1.161);
	energy_vals.push_back(2.261);
	energy_vals.push_back(4.461);

	// --------------------------------------------------------------------------------------------------------------------------

	vector<string> datasets;
	datasets.push_back("Data");
	datasets.push_back("SuSav2");
	datasets.push_back("G2018");

	// -----------------------------------------------------------------------------------------------------------------------

	vector <int> colors;
	colors.push_back(1);
	colors.push_back(kBlue); // cyan
	colors.push_back(610); // green
	colors.push_back(402); // yellowish
	colors.push_back(801); // orange
	colors.push_back(629); // red 
	colors.push_back(610); // magenta

	// -----------------------------------------------------------------------------------------------------------------------

	TList *l = new TList();

	TFile *f = TFile::Open(inputFile.c_str());

	for (unsigned int ids = 0 ; ids < datasets.size() ; ids++) { 

		string dataset = datasets[ids];

		TH2D *hMM = new TH2D(Form("%s%sMigrationMatrix",dataset.c_str(),element.c_str()),";True E_{e} [GeV]; Reco E_{cal} [GeV]",Nbins,Emin,Emax,Nbins,Emin,Emax);

		vector <TH1F*> hs;

		std::cout << std::endl << "Processing dataset " << dataset << std::endl;

		// Storing the relevant histos based on the energy / nucleus / dataset

		for (unsigned int ie = 0 ; ie < energies.size() ; ie++) {

			string energy = energies[ie];
			float energy_val = energy_vals[ie];

			TH1F *h = (TH1F*)f->Get(Form("ECalReso_FineBin_12C_%s_%s",energy.c_str(),dataset.c_str()));
			h->SetName(Form("feeddown_%s_%s_%s",element.c_str(),energy.c_str(),dataset.c_str()));

			for (int i = 0 ; i < h->GetNbinsX() ; i++) {

			 	if (h->GetBinContent(i+1) < 0) h->SetBinContent(i+1,0.);

			}

//			h->Scale(1./h->Integral()); // Adi is that the correct way to go if we have xsecs ?
			hs.push_back(h);

			std::cout << "dataset " << dataset << " energy "<<energies[ie]<<std::endl;

		}

		std::cout << std::endl;


		std::cout<<"done with loop over energies"<<std::endl;

		vector <TGraph*> gs;
		vector <TF1*> fit1s;
		vector <TF1*> fit2s;

		// Perform the linear fitting with the 3 points from the 3 energies

		// Loop over the bins

		for (int i = 0 ; i < hs[0]->GetNbinsX() ; i++) {

			//std::cout << "a bin " << i << std::endl;

			gs.push_back(new TGraph());

			//std::cout << "b bin " << i << std::endl;

			gs[i]->SetName(Form("g_%s_%d",dataset.c_str(),i));

			//std::cout << "c bin " << i << std::endl;

			gs[i]->SetTitle(Form("Extrapolate %s Fractional Feeddown For Bin %d",dataset.c_str(),i));

			//std::cout << "d bin " << i << std::endl;

			for (unsigned int ie = 0 ; ie < energies.size() ; ie++) { 

				string energy = energies[ie];
				float energy_val = energy_vals[ie]; 
				gs[i]->SetPoint(ie, energy_val, hs[ie]->GetBinContent(i+1));

			}

			TF1 *fit1 = new TF1(Form("fit1_%s_%d",dataset.c_str(),i),"pol1",0,2.262);
			TF1 *fit2 = new TF1(Form("fit2_%s_%d",dataset.c_str(),i),"pol1",2.26,5.);
			gs[i]->Fit(Form("fit1_%s_%d",dataset.c_str(),i),"QR+"); // Q: suppress minuit output messages
			gs[i]->Fit(Form("fit2_%s_%d",dataset.c_str(),i),"QR+");
			fit1s.push_back(fit1);
			fit2s.push_back(fit2);

			// Fit canvases
			
//			TCanvas *cfits = new TCanvas();
//			cfits->cd();
//			gs[i]->Draw();
//			fit1s[i]->Draw("same");
//			fit2s[i]->Draw("same");
//			cfits->SaveAs(Form("./myPlots/%s_%d.pdf",dataset.c_str(),i));
//			delete cfits;

		}

		// At this point, we have the TGraph fits on a bin-by-bin basis
		// For any energy between 0 up to 5 GeV

		std::cout << std::endl << dataset << " :done saving fits" << std::endl << std::endl;
		
		vector<TH1F*> hies;		
	
		for (int i = 0 ; i < hMM->GetNbinsX() ; i++) {

			float etrue = hMM->GetXaxis()->GetBinCenter(i+1);
			TH1F *hie = new TH1F(Form("h_%s_%.2f",dataset.c_str(),etrue),Form("Feeddown Ev = %.2f [GeV]",etrue),100,-1.,1.);

			for (int j = 0 ; j < hie->GetNbinsX() ; j++) {

				if (etrue <= 2.261) { hie->SetBinContent(j+1,fit1s[j]->Eval(etrue)); }

				if (etrue > 2.261 && etrue <= 4.461) { hie->SetBinContent(j+1,fit2s[j]->Eval(etrue)); }

				if (etrue > 4.461) { hie->SetBinContent(j+1,hs[2]->GetBinContent(j+1)); }

				if (hie->GetBinContent(j+1) < 0) {

					// if negative entry, set it to 0
					//std::cout<<"negative val i "<<i<<" bin j "<<j<<" val "<<hie->GetBinContent(j+1)<<std::endl;
					hie->SetBinContent(j+1,0);

				}

			}

			hie->Scale(1./hie->Integral()); // here we need the area normalization
			hies.push_back(hie);

		}

		// At this point, we have the extrapolated 1D histos with the relevant resolutions
		// For any energy between 0 up to 5 GeV

		//std::cout << " done loop over mms bins"<<std::endl;
		std::cout << dataset << " :done saving extrapolated feeddowns "<<std::endl;

		for (int i = 0 ; i < hMM->GetNbinsX() ; i++) {

			// Extrapolated feeddown spectra in each bin

//			TCanvas *ch = new TCanvas();
//			TLegend *lh = new TLegend(0.6,0.66,0.88,0.88);
//			ch->cd();

//			hies[i]->SetLineWidth(2);
//			hies[i]->SetLineColor(1);

//			lh->AddEntry(hies[i],"Extrapolated Feeddown","l");
//			hies[i]->Draw();

//			for (unsigned int ie = 0 ; ie < energies.size() ; ie++) {

//				hs[ie]->SetLineColor(colors[ie+1]);
//				hs[ie]->Draw("same");
//				lh->AddEntry(hs[ie],Form("Feeddown E = %.2f [GeV]",energy_vals[ie]),"l");

//			}
//	 
//			lh->Draw("same");
//			ch->SaveAs(Form("./myPlots/feeddown_%s_%d.pdf",dataset.c_str(),i));
//			delete ch;
			
			float etrue = hMM->GetXaxis()->GetBinCenter(i+1);

// Was commented out Feb 19 2021
////			double sum = 0.;
////			for (int j = 0 ; j < hMM->GetNbinsY() ; j++) {

////				double erec = hMM->GetYaxis()->GetBinCenter(j+1); 
////				double reso = (erec - etrue)/etrue;
////				int resobin = hies[i]->FindBin(reso);
////				double migration_val = hies[i]->GetBinContent(resobin);
////				hMM->SetBinContent(i+1,j+1, migration_val);
////				//sum+= hMM->GetBinContent(i+1,j+1);
////			}


			// This is the place where we fill the 2D migration matrix

			for (int j = 0 ; j < itts ; j++) {

				double erec = etrue * hies[i]->GetRandom() + etrue;
				hMM->Fill(etrue,erec,1./itts);

			}

		}
	 
		l->Add(hMM);
		TCanvas *cMM = new TCanvas();
		cMM->cd();
		cMM->SetLeftMargin(0.12);
		cMM->SetRightMargin(0.14);
		cMM->SetBottomMargin(0.17);

		hMM->GetXaxis()->CenterTitle();
		hMM->GetXaxis()->SetNdivisions(6);

		hMM->GetYaxis()->CenterTitle();
		hMM->GetYaxis()->SetNdivisions(6);
		hMM->GetYaxis()->SetTitleOffset(0.7);

		hMM->GetZaxis()->SetNdivisions(6);

		TLegend *MigrLegend = new TLegend(0.2,0.66,0.4,0.88);
		MigrLegend->AddEntry(hMM,TString(dataset),"");
		MigrLegend->SetBorderSize(0);
		MigrLegend->SetTextSize(TextSize);
		MigrLegend->SetTextFont(FontStyle);

		hMM->Draw("colz");

		MigrLegend->Draw("same");

		cMM->SaveAs(Form("./myPlots/migrationMatrix%s.pdf",dataset.c_str()));
		delete cMM;

	} // End of the loop over the datasets

	TFile *fout = TFile::Open("./MigrationMatrices.root","recreate");
	fout->cd();
	l->Write();
	fout->Write();
	fout->Close(); 

	//f->Close();

} // End of the program
