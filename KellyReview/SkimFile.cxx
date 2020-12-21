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

using namespace std;

void SkimFile(){

	TFile* oldfile = TFile::Open("16O_2442GeV_EM+MEC_GTEST19_10b_00_000_Q2_0_7_Full_Sample.root","readonly");
	TFile* newfile = TFile::Open("16O_2442GeV_EM+MEC_GTEST19_10b_00_000_Q2_0_7.root","recreate");

	TTree* oldtree = (TTree*)(oldfile->Get("gst"));
	TTree *newtree = oldtree->CloneTree(0);

	double cthl, Q2, Ev, El;
	int nfp, nfpi0, nfpip, nfpim;

	oldtree->SetBranchAddress("El",&El);
	oldtree->SetBranchAddress("Ev",&Ev);
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

		if (ievent%1000 == 0) { std::cout << ievent/1000 << " k " << std::setprecision(3) << double(ievent)/nevents*100. << " %"<< std::endl; }

//		if ( TMath::Abs( TMath::ACos(cthl)*180./TMath::Pi() - 37.17 ) > 1.5  ) { continue; }
//		if ( Q2 > 0.85  || Q2 < 0.75 ) { continue; }
//		if ( nfp == 0 ) { continue; }
//		if ( nfpi0 != 0 ) { continue; }
//		if ( nfpip != 0 ) { continue; }
//		if ( nfpip != 0 ) { continue; }
		if ( TMath::Abs( (Ev-El) - 0.445 ) > 0.015  ) { continue; }

		newtree->Fill();

	}


	newtree->Write();
	newfile->Close();
	oldfile->Close();

}
