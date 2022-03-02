#define GENIE_ANALYSIS_C
#include "genie_analysis.h"
#include "Constants.h"
#include <TStyle.h>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVectorT.h>
#include <TRandom3.h>
#include <TF1.h>
#include <TH3.h>

#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <exception>
#include <fstream>

using namespace std;

// ------------------------------------------------------------------------------------------------------------------

void genie_analysis::Loop() {

	TH1D::SetDefaultSumw2();

	// ---------------------------------------------------------------------------------------------------------------

	target_name = ftarget; //std string for target name
	en_beam["1161"]=1.161;
	en_beam["2261"]=2.261;
	en_beam["4461"]=4.461;

	en_beam_Ecal["1161"]=1.161;
	en_beam_Ecal["2261"]=2.261;
	en_beam_Ecal["4461"]=4.461;

	en_beam_Eqe["1161"]=1.161;
	en_beam_Eqe["2261"]=2.261;
	en_beam_Eqe["4461"]=4.461;

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	//Resolutions for Smearing for GENIE simulation data
	double reso_p = 0.01; // smearing for the proton
	double reso_e = 0.005; // smearing for the electrons
	double reso_pi = 0.007; //smearing for pions, executive decision by Larry (28.08.19)

	// Resolution defined above seems to be insufficient at 1.1 GeV -> tripled it for all particles
	if(fbeam_en == "1161") { reso_p = 3*reso_p; reso_e = 3*reso_e; reso_pi = 3*reso_pi; }

	double Wcut = 2; //cut for all beam energies < 2
	double Q2cut = 0; // cut for 1.1 GeV > 0.1, for 2.2 GeV > 0.4 and 4.4 GeV > 0.8

	TString E_acc_file;

	if(en_beam[fbeam_en]>1. && en_beam[fbeam_en]<2.) //1.1 GeV Configuration parameters and cuts
	{
		E_acc_file="1_161";
		Q2cut = 0.1;
	}


	if(en_beam[fbeam_en]>2. && en_beam[fbeam_en]<3.) //2.2 GeV Configuration parameters and cuts
	{
		E_acc_file="2_261";
		Q2cut = 0.4;
	}

	if(en_beam[fbeam_en]>4. && en_beam[fbeam_en]<5.) //4.4 GeV Configuration parameters and cuts
	{
		E_acc_file="4_461";
		Q2cut = 0.8;
	}

	// ----------------------------------------------------------------------------------------

	gRandom = new TRandom3();
	gRandom->SetSeed(10);

	TLorentzVector V4_beam(0,0,en_beam[fbeam_en],en_beam[fbeam_en]);

	//Acceptance Maps

	TString WhichMap = "e2a_maps";
	TString Target = "12C";
	if ( TString(ftarget.c_str()) == "3He") { Target = "3He"; }
	if ( TString(ftarget.c_str()) == "4He") { Target = "4He"; }

	TFile* file_acceptance = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+".root");
	TFile* file_acceptance_p = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+"_p.root");
	TFile* file_acceptance_pip = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+"_pip.root");
	TFile* file_acceptance_pim = TFile::Open(WhichMap+"/"+WhichMap+"_"+Target+"_E_"+E_acc_file+"_pim.root");

	// ---------------------------------------------------------------------------------------------------------------

	//Output file definition
	TString FileName =  Form("genie_e2a_ep_%s_%s_neutrino6_united4_radphot_test_SuSav2.root",ftarget.c_str(),fbeam_en.c_str()); 
	TFile * file_out = new TFile(FileName, "recreate");

	// ---------------------------------------------------------------------------------------------------------------

	fiducialcut->InitPiMinusFit(fbeam_en);

	//initialize Fiducial functions for EC limits
	fiducialcut->InitEClimits();
	std::cout << " Test InitEClimits Loop " << fiducialcut->up_lim1_ec->Eval(60) << std::endl;

	TH1F *h1_Nprot=new TH1F("h1_Nprot","",5,-0.5,4.5);
	TH1F *h1_Nphot=new TH1F("h1_Nphot","",10,-0.5,4.5);
	TH1F *h1_Npiphot=new TH1F("h1_Npiphot","",10,-0.5,4.5);
	TH1F *h1_Npiphot_norad=new TH1F("h1_Npiphot_norad","",10,-0.5,4.5);
	TH1F *h1_Npi=new TH1F("h1_Npi","",5,-0.5,4.5);
	TH1F *h1_Npipl=new TH1F("h1_Npipl","",10,-0.5,4.5);
	TH1F *h1_Npimi=new TH1F("h1_Npimi","",10,-0.5,4.5);

	// ---------------------------------------------------------------------------------------------------------------

	TF1 *myElectronFit = new TF1("myElectronFit","[0]+[1]/x",0.,5.);

	if (en_beam[fbeam_en] == 1.161) { myElectronFit->SetParameters(17,7); }
	if (en_beam[fbeam_en] == 2.261) { myElectronFit->SetParameters(16,10.5); }
	if (en_beam[fbeam_en] == 4.461) { myElectronFit->SetParameters(13.5,15); }

	// ---------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		//Read Entry
		int nb = GetEntry(jentry);
		if (nb == 0) { std::cout <<"Event loop: 0 byte read for entry " << jentry << ". Indicate failure in reading the file" <<	std::endl;}

		if (jentry%1000 == 0) {std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/double(fChain->GetEntries())*100. << " %"<< std::endl;}

		if( jentry%200000 == 0 ) { gDirectory->Write("hist_Files", TObject::kOverwrite); }

		// ---------------------------------------------------------------------------------------------------------------

		std::string StoreEnergy = fbeam_en;

		// ---------------------------------------------------------------------------------------------------------------

		if(jentry == 0){ //first entry to initialize TorusCurrent, Fiducials and Subtraction classes

			//The TorusField has to be set before the Fiducialcut parameters are initialized
			if(en_beam[fbeam_en]>1. && en_beam[fbeam_en]<2. ) //1.1 GeV, we are not using the 1.1 GeV data with 1500 current field
			{
				 fTorusCurrent = 750;
			}
			else if( (en_beam[fbeam_en]>2. && en_beam[fbeam_en]<3.) || (en_beam[fbeam_en]>4. && en_beam[fbeam_en]<5.) ) //2.2 GeV	or 4.4 GeV
			{
				 fTorusCurrent = 2250;
			}
			else { std::cout << "genie_analysis::Loop(): fTorusCurrent could not be assigned" << std::endl;}

			fiducialcut->SetConstants(fTorusCurrent, target_name, en_beam);
			fiducialcut->SetFiducialCutParameters(fbeam_en);
			std::cout << " EventLoop: Finished setting up fiducial cut class " << std::endl;
		}

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------

		//V4_el and V3_el will be changed by smearing for GENIE simulation data
		TLorentzVector V4_el(pxl,pyl,pzl,El);
		TLorentzVector V4_el_uncorr(pxl,pyl,pzl,El);
		TVector3 V3_el(pxl,pyl,pzl);

		double el_momentum = V3_el.Mag();
		double el_theta = V3_el.Theta();

		// ----------------------------------------------------------------------------------------------------------------------	

		//Smearing of Electron Vector from Simulation
		double SmearedPe = gRandom->Gaus(pl,reso_e*pl);
		double SmearedEe = sqrt( SmearedPe*SmearedPe + e_mass * e_mass );
		V3_el.SetXYZ(SmearedPe/pl * pxl,SmearedPe/pl * pyl,SmearedPe/pl * pzl);
		V4_el.SetPxPyPzE(V3_el.X(),V3_el.Y(),V3_el.Z(),SmearedEe);
		double phi_ElectronOut = V3_el.Phi(); //in Radians

		V3_el.SetPhi(phi_ElectronOut + TMath::Pi() ); // Vec.Phi() is between (-180,180), GENIE coordinate system flipped with respect to CLAS

		phi_ElectronOut += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
		el_momentum = V3_el.Mag(); //Momentum after smearing
		el_theta = V3_el.Theta(); //Angle after smearing

		// acceptance_c takes phi in radians and here unmodified by 30 degree.
		double e_acc_ratio = acceptance_c(el_momentum, cos(el_theta), phi_ElectronOut, 11,file_acceptance,true);
		if ( fabs(e_acc_ratio) != e_acc_ratio ) { continue; }

		// ----------------------------------------------------------------------------------------------------------------------

		double theta_min = myElectronFit->Eval(el_momentum); // in deg
		if (el_theta*180./TMath::Pi() < theta_min) { continue; }

		// ----------------------------------------------------------------------------------------------------------------------

		// Explicit cuts on electron momentum

		if (fbeam_en=="1161" && el_momentum < 0.4) { continue; }
		if (fbeam_en=="2261" && el_momentum < 0.55) { continue; }
		if (fbeam_en=="4461" && el_momentum < 1.1) { continue; }

		//Definition as for data. It is also correct for GENIE simulation data since V3_el is rotated above by 180 degree in phi
		double el_phi_mod = V3_el.Phi()*TMath::RadToDeg()  + 30; //Add 30 degree for plotting and photon phi cut
		if(el_phi_mod<0)  el_phi_mod  = el_phi_mod+360; //Add 360 so that electron phi is between 0 and 360 degree

		double reco_Q2 = -(V4_el-V4_beam).Mag2();
		double Q4 = reco_Q2 * reco_Q2;
		double Mott_cross_sec = (1./Q4);

		// ---------------------------------------------------------------------------------------------------------------------

		// Sanity check, especially for radiation
		if (wght < 0 || wght > 10) { std::cout << "Something is really wrong with your weights !!!" << std::endl; }

		double WeightIncl = wght*e_acc_ratio / Mott_cross_sec;

		// Securing ourselves against infinities
		if ( fabs(WeightIncl) != WeightIncl ) { continue; }

		//Calculation of kinematic quantities (nu, Q2, x bjorken, q and W)
		double nu = -(V4_el-V4_beam).E();

		TVector3 V3_q = (V4_beam-V4_el).Vect();
		double W_var = TMath::Sqrt((m_prot+nu)*(m_prot+nu)-V3_q*V3_q);

		//converting theta to degrees
		el_theta = el_theta*TMath::RadToDeg();

		//Cuts on Q2 and W, only keep events with Q2 > Q2cut and W < Wcut
		if ( reco_Q2 < Q2cut || W_var > Wcut) continue;

		// ---------------------------------------------------------------------------------------------------------------------			

		//Fiducial Cuts with the smeared values
		if (!EFiducialCut(fbeam_en,V3_el) ) continue; // Electron theta & phi fiducial cuts 
		
		// ---------------------------------------------------------------------------------------------------------------------

		int ElectronSector = el_phi_mod / 60.;

		// ---------------------------------------------------------------------------------------------------------------------

		// Ditching bad sectors
		// Counting sectors from 0 to 5

		if ( (ElectronSector == 2 || ElectronSector == 4) &&  fbeam_en == "1161") { continue; }
		if ( (ElectronSector == 2 || ElectronSector == 3 || ElectronSector == 4) &&  fbeam_en == "2261") { continue; }

		// ---------------------------------------------------------------------------------------------------------------------
 
		//Number of hadrons
		int num_p = 0;
		int num_pi = 0;
		int num_pi_phot = 0; //couting all pions and photons
		int num_pimi = 0;
		int num_pipl = 0;
		int num_pi_phot_nonrad = 0; //counting all pions and non-radiation photons
		int num_phot_rad = 0; //counting radiation photons
		int num_phot_nonrad = 0;
		//Index and number variables for neutral particles
		int ec_num_n = 0;
		bool ec_radstat_n[20];

		//Array initialize to -1 or false
		for (int i = 0; i < 20; i++) {
			ec_radstat_n[i] = false;
		}

		const double phot_rad_cut = 40;
		const double phot_e_phidiffcut = 30; //electron - photon phi difference cut

		//Loop for Hadrons
		for (int i = 0; i < nf; i++) {

			// -----------------------------------------------------------------------------------------------------------------------------------------------

			//Start of proton selection

			if (pdgf[i] == 2212  && pf[i] > 0.3) {

				//Smearing of proton
				double temp_smear_P = gRandom->Gaus(pf[i],reso_p*pf[i]);

				TVector3 V3_prot_corr(temp_smear_P/pf[i] * pxf[i],temp_smear_P/pf[i] * pyf[i],temp_smear_P/pf[i] * pzf[i]);
				double phi_prot = V3_prot_corr.Phi();
				V3_prot_corr.SetPhi(phi_prot + TMath::Pi()); // Vec.Phi() is between (-180,180), // GENIE coordinate system flipped with respect to CLAS

				if (!PFiducialCut(StoreEnergy, V3_prot_corr) ) { continue; } // Proton theta & phi fiducial cuts

				num_p = num_p + 1;

				phi_prot += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
				double ProtonCosTheta = V3_prot_corr.CosTheta(); 
				double ProtonMag = V3_prot_corr.Mag(); 

				//acceptance_c takes phi in radians and here unmodified by 30 degree.
				double ProtonWeight = wght*acceptance_c(ProtonMag,ProtonCosTheta, phi_prot, 2212,file_acceptance_p,true);
				if ( fabs(ProtonWeight) != ProtonWeight ) { continue; } 

			}

			// -------------------------------------------------------------------------------------------------------------------

			if (pdgf[i] == -211  && pf[i] > 0.15)  { //Pi minus

				//Smearing of pi minus
				double temp_smear_P = gRandom->Gaus(pf[i],reso_pi*pf[i]);

				TVector3 V3_pi_corr(temp_smear_P/pf[i] * pxf[i],temp_smear_P/pf[i] * pyf[i],temp_smear_P/pf[i] * pzf[i]);
				double phi_pion = V3_pi_corr.Phi();
				V3_pi_corr.SetPhi(phi_pion + TMath::Pi()); // Vec.Phi() is between (-180,180)

				if ( !Pi_phot_fid_united(StoreEnergy, V3_pi_corr, -1) ) {  continue; }

				num_pimi = num_pimi + 1;
				num_pi = num_pi + 1;
				num_pi_phot = num_pi_phot + 1;
				num_pi_phot_nonrad = num_pi_phot_nonrad + 1;

				phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
				double PiMinusCosTheta = V3_pi_corr.CosTheta(); 
				double PiMinusMag = V3_pi_corr.Mag(); 

				// acceptance_c takes phi in radians and here unmodified by 30 degree.
				double PiMinusWeight = wght * acceptance_c(PiMinusMag,PiMinusCosTheta, phi_pion, -211,file_acceptance_pim,true);
				if ( fabs(PiMinusWeight) != PiMinusWeight ) { continue; }

			}

			// -------------------------------------------------------------------------------------------------------------------

			if ( pdgf[i] == 211  && pf[i] > 0.15)  {

				//Smearing of pi plus
				double temp_smear_P = gRandom->Gaus(pf[i],reso_pi*pf[i]);

				TVector3 V3_pi_corr(temp_smear_P/pf[i] * pxf[i],temp_smear_P/pf[i] * pyf[i],temp_smear_P/pf[i] * pzf[i]);
				double phi_pion = V3_pi_corr.Phi();
				V3_pi_corr.SetPhi(phi_pion + TMath::Pi()); // Vec.Phi() is between (-180,180)

				if ( !Pi_phot_fid_united(StoreEnergy, V3_pi_corr, 1) ) {  continue; }

				num_pipl = num_pipl + 1;
				num_pi  = num_pi + 1;
				num_pi_phot = num_pi_phot + 1;
				num_pi_phot_nonrad = num_pi_phot_nonrad + 1;

				phi_pion += TMath::Pi(); // GENIE coordinate system flipped with respect to CLAS
				double PiPlusCosTheta = V3_pi_corr.CosTheta(); 
				double PiPlusMag = V3_pi_corr.Mag(); 

				// acceptance_c takes phi in radians and here unmodified by 30 degree.
				double PiPlusWeight = wght * acceptance_c(PiPlusMag,PiPlusCosTheta, phi_pion, 211,file_acceptance_pip,true);
				if ( fabs(PiPlusWeight) != PiPlusWeight ) { continue; }

			}

			// ---------------------------------------------------------------------------------------------------------------------------

			if (pdgf[i] == 22  && pf[i] > 0.3) {

				//Determine photon vector for the cut on radiation photon via angle with respect to the electron
				TVector3 V3_phot_angles(pxf[i],pyf[i],pzf[i]);
				//no smearing of GENIE photons
				double phi_photon = V3_phot_angles.Phi();
				V3_phot_angles.SetPhi(phi_photon + TMath::Pi()); // Vec.Phi() is between (-180,180)
				if ( !Pi_phot_fid_united(fbeam_en, V3_phot_angles, 0) )  { continue;}

				double neut_phi_mod = V3_phot_angles.Phi()*TMath::RadToDeg() + 30; //Add 30 degree
				if (neut_phi_mod < 0) neut_phi_mod = neut_phi_mod + 360;  //Neutral particle is between 0 and 360 degree

				ec_num_n = ec_num_n + 1;
				num_pi_phot = num_pi_phot + 1;

				// within 40 degrees in theta and 30 degrees in phi. Electron phi has already added 30 degree and between 0 to 360

				if(V3_phot_angles.Angle(V3_el)*TMath::RadToDeg() < phot_rad_cut && fabs(neut_phi_mod-el_phi_mod) < phot_e_phidiffcut ) {

					ec_radstat_n[num_pi_phot - 1] = true; // select radiation photons
					num_phot_rad = num_phot_rad + 1;

				 }

				 if(!ec_radstat_n[num_pi_phot - 1]) {

					num_phot_nonrad = num_phot_nonrad + 1;
					num_pi_phot_nonrad = num_pi_phot_nonrad + 1;

				 }

			}

		} // end of hadron loop

		// ----------------------------------------------------------------------------------------------------------------------------

		//Skip event if there is at least one radiation photon

		if (num_phot_rad > 0) { continue; }

		// -----------------------------------------------------------------------------------------------------------------------------

		// Filling Histograms with particle multiplicities

		h1_Npi->Fill(num_pi);
		h1_Nprot->Fill(num_p);
		h1_Nphot->Fill(ec_num_n);
		h1_Npipl->Fill(num_pipl);
		h1_Npimi->Fill(num_pimi);
		h1_Npiphot->Fill(num_pi_phot);
		h1_Npiphot_norad->Fill(num_pi_phot_nonrad);

	} //end of event loop (jentry)

	std::cout << "File " << FileName << " created" << std::endl << std::endl;

	file_out->cd();
	file_out->Write();

} // End of program

//End Loop function

// -------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------

double genie_analysis::acceptance_c(double p, double cost, double phi, int particle_id,TFile* file_acceptance, bool ApplyAccWeights) {

	if (ApplyAccWeights) {

		//Redefinition of the phi angle
		//because the acceptance maps are defined between (-30,330)

		TH3D * acc;
		TH3D * gen;

		acc = (TH3D*)file_acceptance->Get("Accepted Particles");
		gen = (TH3D*)file_acceptance->Get("Generated Particles");

		//map 330 till 360 to [-30:0] for the acceptance map histogram
		if(phi > (2*TMath::Pi() - TMath::Pi()/6.) ) { phi -= 2*TMath::Pi(); }
		//Find number of generated events

		double pbin_gen = gen->GetXaxis()->FindBin(p);
		double tbin_gen = gen->GetYaxis()->FindBin(cost);
		double phibin_gen = gen->GetZaxis()->FindBin(phi*180/TMath::Pi());
		double num_gen = gen->GetBinContent(pbin_gen, tbin_gen, phibin_gen);

		//Find number of accepted events

		double pbin_acc = acc->GetXaxis()->FindBin(p);
		double tbin_acc = acc->GetYaxis()->FindBin(cost);
		double phibin_acc = acc->GetZaxis()->FindBin(phi*180/TMath::Pi());
		double num_acc = acc->GetBinContent(pbin_acc, tbin_acc, phibin_acc);

		double acc_ratio = (double)num_acc / (double)num_gen;

		return acc_ratio;

	}

	else { return 1.; }

}