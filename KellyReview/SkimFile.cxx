#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TFile.h>
#include <iomanip>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

void SkimFile(){

	TFile* oldfile = TFile::Open("16O_2442GeV_EM+MEC_GTEST19_10b_00_000_Q2_0_7.root","readonly");
	TFile* newfile = TFile::Open("16O_2442GeV_EM+MEC_GTEST19_10b_00_000_Q2_0_7_Skimmed_Final.root","recreate");

	TTree* oldtree = (TTree*)(oldfile->Get("gst"));
	TTree *newtree = oldtree->CloneTree(0);

	double cthl;
	double Q2;
	int nfp, nfpi0, nfpip, nfpim;

	oldtree->SetBranchAddress("cthl",&cthl);
	oldtree->SetBranchAddress("Q2",&Q2);
	oldtree->SetBranchAddress("nfp",&nfp);
	oldtree->SetBranchAddress("nfpi0",&nfpi0);
	oldtree->SetBranchAddress("nfpim",&nfpim);
	oldtree->SetBranchAddress("nfpip",&nfpip);

	int nevents = (int) oldtree->GetEntries();
	int nbytes = 0;

	for(int ievent=0; ievent<nevents; ievent++) {

		nbytes += oldtree->GetEntry(ievent);

		if ( TMath::Abs( TMath::ACos(cthl)*180./TMath::Pi() - 37.17 ) > 2  ) { continue; }
		if ( Q2 > 0.85  || Q2 < 0.75 ) { continue; }
		if ( nfp == 0 ) { continue; }
		if ( nfpi0 != 0 ) { continue; }
		if ( nfpip != 0 ) { continue; }
		if ( nfpip != 0 ) { continue; }

		newtree->Fill();

	}


	newtree->Write();
	newfile->Close();
	oldfile->Close();

}
