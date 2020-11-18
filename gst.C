#define gst_cxx
#include "gst.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

void gst::Loop() {

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;

	// --------------------------------------------------------------

	TFile* FilteredFile = new TFile("FilteredGenie_56Fe_4461GeV_1p0pi_1p1pi.root","recreate");
	TTree *maketreenew = fChain->CloneTree(0); 

	// --------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
	
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		// --------------------------------------------------------------

		if (jentry%1000 == 0) {std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/fChain->GetEntries()*100. << " %"<< std::endl;}

		// --------------------------------------------------------------

		// Electron threshods for 4.4 GeV

		if (El < 1.1) { continue; }
		if (Q2 < 0.8) { continue; }
		if (W > 2) { continue; }

		// --------------------------------------------------------------

		int ProtonCounter = 0;
		int ChargedPionCounter = 0;

		//Loop for Hadrons
		for (int i = 0; i < nf; i++) {

			if (pdgf[i] == 2212  && pf[i] > 0.3) { ProtonCounter++; }
			if (TMath::Abs(pdgf[i]) == 211  && pf[i] > 0.15) { ChargedPionCounter++; }


		}

		// --------------------------------------------------------------

		// 1p0pi + 1p1pi		
		if (ProtonCounter != 1) { continue; }
		if (ChargedPionCounter != 0 || ChargedPionCounter != 1) { continue; }

		// --------------------------------------------------------------

		// 1p0pi + 2p0pi		
		//if (ProtonCounter != 1 || ProtonCounter != 2) { continue; }
		//if (ChargedPionCounter != 0) { continue; }

		// --------------------------------------------------------------

		maketreenew->Fill();

		// --------------------------------------------------------------


   } // End of the loop over the events

   maketreenew->Write();
   FilteredFile->Close();

} // End of the Loop()
