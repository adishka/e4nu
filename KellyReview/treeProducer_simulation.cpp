#define treeProducer_simulation_cxx
#include "treeProducer_simulation.h"
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

TString ToString(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

void treeProducer_simulation::Loop() {

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	// -------------------------------------------------------------------------------

	// Binding Energy

	double BE = 0.025; // GeV
	double Ebeam = 1.161;

	// -------------------------------------------------------------------------------

	TString FileName = fNucleus+"_"+fEnergy+"_"+fTune+"_"+fInteraction+".root";
	
	TFile* file = new TFile(FileName,"recreate");

	std::cout << std::endl << "File " << FileName << " will be created" << std::endl << std::endl; 
	const double ProtonMass = .9383, MuonMass = .106, NeutronMass = 0.9396, ElectronMass = 0.000511; // [GeV]
	int MissMomentumBin = 99;

	// -------------------------------------------------------------------------------

	// Ranges & Binning

	int NBinsQ2 = 56; double MinQ2 = 0.1, MaxQ2 = 1.5; TString TitleQ2 = ";Q^{2} [GeV^{2}/c^{2}];";
	int NBinsxB = 25; double MinxB = 0.7, MaxxB = 1.3; TString TitlexB = ";x_{B};";
	int NBinsnu = 50; double Minnu = 0., Maxnu = 1.2; TString Titlenu = ";Energy Transfer [GeV];";
	int NBinsW = 20; double MinW = 0.7, MaxW = 1.2; TString TitleW = ";W (GeV/c^{2});";
	int NBinsPmiss = 40; double MinPmiss = 0., MaxPmiss = 1.; TString TitlePmiss = ";P_{T} [GeV/c];";
	int NBinsEmiss = 40; double MinEmiss = 0., MaxEmiss = 0.12; TString TitleEmiss = ";E_{miss} [GeV];";
	int NBinsPionMulti = 4; double MinPionMulti = -0.5, MaxPionMulti = 3.5; TString TitlePionMulti = ";Pion Multiplicity;";
	int NBinsReso = 30; double MinReso = -50., MaxReso = 10.; TString TitleReso = ";#frac{E^{cal} - E^{beam}}{E^{beam}} (%);";

	TString TitleQ2Vsnu = ";Energy Transfer [GeV];Q^{2} [GeV^{2}/c^{2}];";
	TString TitleQ2VsW = ";W [GeV/c^{2}];Q^{2} [GeV^{2}/c^{2}];";

	// -------------------------------------------------------------------------------

	// Electron

	int NBinsElectronEnergy = 40; double MinElectronEnergy = 0., MaxElectronEnergy = 1.2; TString TitleElectronEnergy = ";E_{e'} (GeV);";
	int NBinsElectronPhi = 45; double MinElectronPhi = 0., MaxElectronPhi = 360.; TString TitleElectronPhi = ";#phi_{e'} (degrees);";
	int NBinsElectronTheta = 15; double MinElectronTheta = 15., MaxElectronTheta = 53.; TString TitleElectronTheta = ";#theta_{e'} (degrees);";
	int NBinsElectronCosTheta = 40; double MinElectronCosTheta = -1, MaxElectronCosTheta = 1.; TString TitleElectronCosTheta = ";cos(#theta_{e'});";
	int NBinsElectronMom = 40; double MinElectronMom = 1.7, MaxElectronMom = 4.; TString TitleElectronMom = ";P_{e'} (GeV/c);";

	TString TitleElectronPhiVsTheta = ";#phi_{e'} (degrees);#theta_{e'} (degrees);";

	// -------------------------------------------------------------------------------
	
	// Proton

	int NBinsEp = 40; double MinEp = 0.9, MaxEp = 2.2; TString TitleEp = ";E_{p} (GeV);";
	int NBinsProtonPhi = 45; double MinProtonPhi = 0., MaxProtonPhi = 360.; TString TitleProtonPhi = ";#phi_{p} (degrees);";
	int NBinsProtonTheta = 30; double MinProtonTheta = 10., MaxProtonTheta = 120.; TString TitleProtonTheta = ";#theta_{p} (degrees);";
	int NBinsProtonCosTheta = 40; double MinProtonCosTheta = -0.2, MaxProtonCosTheta = 1.; TString TitleProtonCosTheta = ";cos(#theta_{p});";

	TString TitleProtonEnergyVsMissMomentum = ";P_{T} (GeV/c);E_{p} (GeV);";
	TString TitleQ2VsMissMomentum = ";P_{T} (GeV/c);Q^{2} (GeV^{2}/c^{2});";

	// -------------------------------------------------------------------------------

	TH1D* Q2Plot = new TH1D("Q2Plot",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* xBPlot = new TH1D("xBPlot",TitlexB,NBinsxB,MinxB,MaxxB);
	TH1D* nuPlot = new TH1D("nuPlot",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* WPlot = new TH1D("WPlot",TitleW,NBinsW,MinW,MaxW);
	TH2D* Q2VsnuPlot = new TH2D("Q2VsnuPlot",TitleQ2Vsnu,NBinsnu,Minnu,Maxnu,NBinsQ2,MinQ2,MaxQ2);
	TH2D* Q2VsWPlot = new TH2D("Q2VsWPlot",TitleQ2VsW,NBinsW,MinW,MaxW,NBinsQ2,MinQ2,MaxQ2);

	// Electron

	TH1D* ElectronEnergyPlot = new TH1D("ElectronEnergyPlot",TitleElectronEnergy,NBinsElectronEnergy,MinElectronEnergy,MaxElectronEnergy);
	TH1D* ElectronPhiPlot = new TH1D("ElectronPhiPlot",TitleElectronPhi,NBinsElectronPhi,MinElectronPhi,MaxElectronPhi);
	TH1D* ElectronThetaPlot = new TH1D("ElectronThetaPlot",TitleElectronTheta,NBinsElectronTheta,MinElectronTheta,MaxElectronTheta);
	TH1D* ElectronCosThetaPlot = new TH1D("ElectronCosThetaPlot",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);
	TH2D* ElectronPhiThetaPlot = new TH2D("ElectronPhiThetaPlot",TitleElectronPhiVsTheta,NBinsElectronPhi,MinElectronPhi,MaxElectronPhi,NBinsElectronTheta,MinElectronTheta,MaxElectronTheta);

	// Proton

	TH1D* ProtonEnergyPlot = new TH1D("ProtonEnergyPlot",TitleEp,NBinsEp,MinEp,MaxEp);
	TH1D* ProtonPhiPlot = new TH1D("ProtonPhiPlot",TitleProtonPhi,NBinsProtonPhi,MinProtonPhi,MaxProtonPhi);
	TH1D* ProtonThetaPlot = new TH1D("ProtonThetaPlot",TitleProtonTheta,NBinsProtonTheta,MinProtonTheta,MaxProtonTheta);
	TH1D* ProtonCosThetaPlot = new TH1D("ProtonCosThetaPlot",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);

	TH2D* EpVsMissMomentumPlot = new TH2D("EpVsMissMomentumPlot",TitleProtonEnergyVsMissMomentum,NBinsPmiss,MinPmiss,MaxPmiss,NBinsEp,MinEp,MaxEp);
	TH2D* Q2VsMissMomentumPlot = new TH2D("Q2VsMissMomentumPlot",TitleQ2VsMissMomentum,NBinsPmiss,MinPmiss,MaxPmiss,NBinsQ2,MinQ2,MaxQ2);

	TH1D* MissMomentumPlot = new TH1D("MissMomentumPlot",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);
	TH1D* MissEnergyPlot = new TH1D("MissEnergyPlot",TitleEmiss,NBinsEmiss,MinEmiss,MaxEmiss);

	// -------------------------------------------------------------------------------------

	int NBreakDown = 5;

	TH1D* MissMomentumPlot_BreakDown[NBreakDown];

	TH1D* MissEnergyPlot_BreakDown[NBreakDown];

	for (int i = 0; i < NBreakDown; i++) {

		MissMomentumPlot_BreakDown[i] = new TH1D("MissMomentumPlot_BreakDown_"+ToString(i),TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

		MissEnergyPlot_BreakDown[i] = new TH1D("MissEnergyPlot_BreakDown_"+ToString(i),TitleEmiss,NBinsEmiss,MinEmiss,MaxEmiss);

	}

	// -------------------------------------------------------------------------------------------------------------

	// 2D Inclusive Plots

	TH2D* QE_Q0_Q3_Plot = new TH2D("QE_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* MEC_Q0_Q3_Plot = new TH2D("MEC_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);

	// -------------------------------------------------------------------------------------------------------------

	int NBinsEv = 60; double MinEv = 0., MaxEv = 9.; TString EvTitle = ";E_{#nu} [GeV]"; 

	TH1D* EvPlot = new TH1D("EvPlot",EvTitle,NBinsEv,MinEv,MaxEv);

	TH1D* EvPlot_Interaction[NBreakDown];

	for (int WhichInteraction = 0; WhichInteraction < NBreakDown; WhichInteraction++) {

		EvPlot_Interaction[WhichInteraction] = new TH1D("EvPlot_Interaction_"+ToString(WhichInteraction),EvTitle,NBinsEv,MinEv,MaxEv);

	}

	// -------------------------------------------------------------------------------------------------------------

	int countEvents = 0; Long64_t nbytes = 0, nb = 0;

	// -------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// ------------------------------------------------------------------------------------------

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

		// -------------------------------------------------------------------------------------

		TLorentzVector ProbeV4(pxv,pyv,pzv,Ev);

		TLorentzVector ElectronV4(pxl,pyl,pzl,El);
		double ElectronMom = ElectronV4.Rho(); 

		double ElectronTheta = ElectronV4.Theta()*180./TMath::Pi();
		if (ElectronTheta < 0) { ElectronTheta += 180.;}
		if (ElectronTheta > 180) { ElectronTheta -= 180.;}

		double ElectronCosTheta = ElectronV4.CosTheta();
		double ElectronPhi = ElectronV4.Phi()*180./TMath::Pi();
		if (ElectronPhi < 0) { ElectronPhi += 360.;}
		if (ElectronPhi > 360) { ElectronPhi -= 360.;}

		TLorentzVector qV4 = ProbeV4 - ElectronV4;

		double nu = qV4.E();
		double q3 = qV4.Rho();

		// QE Energy Reconstruction

		double EQE = (2*ProtonMass*BE + 2*ProtonMass*El - pow(ElectronMass,2)) / 2 / (ProtonMass - El + ElectronMom *  ElectronCosTheta);

		// ------------------------------------------------------------------------------------------

		int Interaction = -99;
		if (qel == 1) { Interaction = 0; }
		else if (mec == 1) { Interaction = 1; }
		else if (res == 1) { Interaction = 2; }
		else if (dis == 1) { Interaction = 3; }
		else if (coh == 1) { Interaction = 4; }
		else { continue; }

		// ------------------------------------------------------------------------------------------

		int ProtonTagging = 0, ChargedPionPlusTagging = 0, ChargedPionMinusTagging = 0, GammaTagging = 0, NeutralPionTagging = 0;
		std::vector<int> ProtonID;

		for (int i = 0; i < nf; i++) {

			if (pdgf[i] == 2212) {

				TLorentzVector ProtonV4(pxf[i],pyf[i],pzf[i],Ef[i]);
				double theta_pq = (qV4.Vect()).Angle(ProtonV4.Vect()) * 180./TMath::Pi();

				if (TMath::Abs(theta_pq) < 8) {

					ProtonTagging ++;
					ProtonID.push_back(i);

				}

			}

			if (pdgf[i] == 211)  {

				ChargedPionPlusTagging ++;

			}

			if (pdgf[i] == -211)  {

				ChargedPionMinusTagging ++;

			}

			if (pdgf[i] == 22) { GammaTagging ++; }

			if (pdgf[i] == 111) { NeutralPionTagging ++; }

		} 

		// -------------------------------------------------------------------------------------------------------

		double Weight = 1.;

		if (ProtonTagging == 0) { continue; }

		// -----------------------------------------------------------------------------------------------

		EvPlot->Fill(Ev,Weight);
		EvPlot_Interaction[Interaction]->Fill(Ev,Weight);

		// -----------------------------------------------------------------------------------------------

		countEvents ++;	// Increase the number of the events that pass the cuts by one   

		// ------------------------------------------------------------------------------------------------

		Q2Plot->Fill(Q2,Weight);
		nuPlot->Fill(nu,Weight);
		WPlot->Fill(W,Weight);
		xBPlot->Fill(x,Weight);

		// 1D Electron Plots

		ElectronThetaPlot->Fill(ElectronTheta,Weight);
		ElectronCosThetaPlot->Fill(ElectronCosTheta,Weight);
		ElectronPhiPlot->Fill(ElectronPhi,Weight);
		ElectronEnergyPlot->Fill(El,Weight);

		ElectronPhiThetaPlot->Fill(ElectronPhi,ElectronTheta,Weight);

		// 2D Plots

		Q2VsWPlot->Fill(W,Q2,Weight);
		Q2VsnuPlot->Fill(nu,Q2,Weight);

		if (qel == 1) { QE_Q0_Q3_Plot->Fill(q3,nu,Weight); }
		if (mec == 1) { MEC_Q0_Q3_Plot->Fill(q3,nu,Weight); }

		// -----------------------------------------------------------------------------------------------------

		for (int i = 0; i < ProtonTagging; i++) {
		
		        TLorentzVector ProtonV4(pxf[i],pyf[i],pzf[i],Ef[i]);
			double ProtonE = ProtonV4.E(); 
			double ProtonMom  = ProtonV4.Rho();

			double ProtonTheta = ProtonV4.Theta()*180./TMath::Pi();
			if (ProtonTheta < 0) { ProtonTheta += 180.; }
			if (ProtonTheta > 180) { ProtonTheta -= 180.; }

			double ProtonCosTheta = ProtonV4.CosTheta();

			double ProtonPhi = ProtonV4.Phi()*180./TMath::Pi();
			if (ProtonPhi < 0) { ProtonPhi += 360; }
			if (ProtonPhi > 360) { ProtonPhi -= 360; }

			// Calorimetric Energy Reconstruction && Emiss

			double Ecal = El + ProtonE - ProtonMass + BE;

			double Emiss = Ebeam - Ecal;

			TVector3 ProtonT(ProtonV4.X(),ProtonV4.Y(),0);
			double ProtonTMag = ProtonT.Mag();
			TVector3 ElectronT(ElectronV4.X(),ElectronV4.Y(),0);
			double ElectronTMag = ElectronT.Mag();
			TVector3 MissMomentumT = ProtonT + ElectronT;
			double MissMomentumTMag = MissMomentumT.Mag();

			// -----------------------------------------------------------------------------------------------------------

			ProtonCosThetaPlot->Fill(ProtonCosTheta,Weight);	
			ProtonThetaPlot->Fill(ProtonTheta,Weight);
			ProtonPhiPlot->Fill(ProtonPhi,Weight);
			ProtonEnergyPlot->Fill(ProtonE,Weight);

			EpVsMissMomentumPlot->Fill(MissMomentumTMag,ProtonE,Weight);
			Q2VsMissMomentumPlot->Fill(MissMomentumTMag,Q2,Weight);

			MissMomentumPlot->Fill(MissMomentumTMag,Weight);
			MissMomentumPlot_BreakDown[Interaction]->Fill(MissMomentumTMag,Weight);

			MissEnergyPlot->Fill(Emiss,Weight);
			MissEnergyPlot_BreakDown[Interaction]->Fill(Emiss,Weight);

		}

	} // end of the loop over events

	// ----------------------------------------------------------------------------------------------------------------
	
	// Print this message after the loop over the events

	std::cout << std::endl;
	std::cout << "File " << FileName << " created " << std::endl; 
	std::cout << std::endl;
	std::cout << "Efficiency = " << double(countEvents)/ double(nentries)*100. << " %" << std::endl; std::cout << std::endl;
	file->Write(); file->Close(); 

} // End of the program

// ----------------------------------------------------------------------------------------------------------------
