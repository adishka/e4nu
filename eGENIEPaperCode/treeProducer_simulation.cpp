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

	double BE = 0.02; // GeV
	double Ebeam = 1.161;

	// -------------------------------------------------------------------------------

	TString FileName = "myFiles/"+fNucleus+"_"+fEnergy+"_"+fTune+"_"+fInteraction+"_"+fQ2_Thres+".root";
	
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
	int NBinsPionMulti = 4; double MinPionMulti = -0.5, MaxPionMulti = 3.5; TString TitlePionMulti = ";Pion Multiplicity;";
	int NBinsReso = 30; double MinReso = -50., MaxReso = 10.; TString TitleReso = ";#frac{E^{cal} - E^{beam}}{E^{beam}} (%);";
	int NBinsDeltaPhiT = 18; double MinDeltaPhiT = 0., MaxDeltaPhiT = 80.; TString TitleDeltaPhiT = ";#delta#phi_{T} [deg];";
	int NBinsDeltaAlphaT = 18; double MinDeltaAlphaT = 0., MaxDeltaAlphaT = 180.; TString TitleDeltaAlphaT = ";#delta#alpha_{T} [deg];";

	TString TitleQ2Vsnu = ";Energy Transfer [GeV];Q^{2} [GeV^{2}/c^{2}];";
	TString TitleQ2VsW = ";W [GeV/c^{2}];Q^{2} [GeV^{2}/c^{2}];";

	// -------------------------------------------------------------------------------

	// Electron

	int NBinsElectronEnergy = 40; double MinElectronEnergy = 0., MaxElectronEnergy = 1.2; TString TitleElectronEnergy = ";E_{e'} [GeV];";
	int NBinsElectronPhi = 45; double MinElectronPhi = 0., MaxElectronPhi = 360.; TString TitleElectronPhi = ";#phi_{e'} [deg];";
	int NBinsElectronTheta = 15; double MinElectronTheta = 15., MaxElectronTheta = 53.; TString TitleElectronTheta = ";#theta_{e'} [deg];";
	int NBinsElectronCosTheta = 20; double MinElectronCosTheta = -1, MaxElectronCosTheta = 1.; TString TitleElectronCosTheta = ";cos(#theta_{e'});";
	int NBinsElectronMom = 30; double MinElectronMom = 0.2, MaxElectronMom = 1.2; TString TitleElectronMom = ";P_{e'} [GeV/c];";

	TString TitleElectronPhiVsTheta = ";#phi_{e'} [deg];#theta_{e'} [deg];";

	// -------------------------------------------------------------------------------
	
	// Proton

	int NBinsEp = 40; double MinEp = 0.9, MaxEp = 2.2;
	int NBinsPp = 20; double MinPp = 0.2, MaxPp = 1.7; 
	TString TitleEp = ";E_{p} [GeV];"; TString TitlePp = ";P_{p} [GeV/c];";
	int NBinsProtonPhi = 45; double MinProtonPhi = 0., MaxProtonPhi = 360.; TString TitleProtonPhi = ";#phi_{p} [deg];";
	int NBinsProtonTheta = 30; double MinProtonTheta = 10., MaxProtonTheta = 120.; TString TitleProtonTheta = ";#theta_{p} [deg];";
	int NBinsProtonCosTheta = 40; double MinProtonCosTheta = -0.2, MaxProtonCosTheta = 1.; TString TitleProtonCosTheta = ";cos(#theta_{p});";

	TString TitleProtonEnergyVsMissMomentum = ";P_{T} (GeV/c);E_{p} [GeV];";
	TString TitleQ2VsMissMomentum = ";P_{T} (GeV/c);Q^{2} [GeV^{2}/c^{2}];";

	// -------------------------------------------------------------------------------

	TH1D* Q2Plot = new TH1D("Q2Plot",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* UnweightedQ2Plot = new TH1D("UnweightedQ2Plot",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* Q2Plot_OneProton = new TH1D("Q2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* UnweightedQ2Plot_OneProton = new TH1D("UnweightedQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* QEQ2Plot_OneProton = new TH1D("QEQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* UnweightedQEQ2Plot_OneProton = new TH1D("UnweightedQEQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* MECQ2Plot_OneProton = new TH1D("MECQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* UnweightedMECQ2Plot_OneProton = new TH1D("UnweightedMECQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* RESQ2Plot_OneProton = new TH1D("RESQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* UnweightedRESQ2Plot_OneProton = new TH1D("UnweightedRESQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* DISQ2Plot_OneProton = new TH1D("DISQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);
	TH1D* UnweightedDISQ2Plot_OneProton = new TH1D("UnweightedDISQ2Plot_OneProton",TitleQ2,NBinsQ2,MinQ2,MaxQ2);

	TH1D* xBPlot = new TH1D("xBPlot",TitlexB,NBinsxB,MinxB,MaxxB);

	TH1D* nuPlot = new TH1D("nuPlot",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* UnweightednuPlot = new TH1D("UnweightednuPlot",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* nuPlot_OneProton = new TH1D("nuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* UnweightednuPlot_OneProton = new TH1D("UnweightednuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* QEnuPlot_OneProton = new TH1D("QEnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* UnweightedQEnuPlot_OneProton = new TH1D("UnweightedQEnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* MECnuPlot_OneProton = new TH1D("MECnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* UnweightedMECnuPlot_OneProton = new TH1D("UnweightedMECnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* RESnuPlot_OneProton = new TH1D("RESnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* UnweightedRESnuPlot_OneProton = new TH1D("UnweightedRESnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* DISnuPlot_OneProton = new TH1D("DISnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);
	TH1D* UnweightedDISnuPlot_OneProton = new TH1D("UnweightedDISnuPlot_OneProton",Titlenu,NBinsnu,Minnu,Maxnu);


	TH1D* WPlot = new TH1D("WPlot",TitleW,NBinsW,MinW,MaxW);
	TH1D* PionMultiPlot = new TH1D("PionMultiPlot",TitlePionMulti,NBinsPionMulti,MinPionMulti,MaxPionMulti);
	TH1D* PionMultiQEPlot = new TH1D("PionMultiQEPlot",TitlePionMulti,NBinsPionMulti,MinPionMulti,MaxPionMulti);
	TH2D* Q2VsnuPlot = new TH2D("Q2VsnuPlot",TitleQ2Vsnu,NBinsnu,Minnu,Maxnu,NBinsQ2,MinQ2,MaxQ2);
	TH2D* Q2VsWPlot = new TH2D("Q2VsWPlot",TitleQ2VsW,NBinsW,MinW,MaxW,NBinsQ2,MinQ2,MaxQ2);

	// Electron

	TH1D* ElectronEnergyPlot = new TH1D("ElectronEnergyPlot",TitleElectronEnergy,NBinsElectronEnergy,MinElectronEnergy,MaxElectronEnergy);
	TH1D* ElectronPhiPlot = new TH1D("ElectronPhiPlot",TitleElectronPhi,NBinsElectronPhi,MinElectronPhi,MaxElectronPhi);
	TH1D* ElectronThetaPlot = new TH1D("ElectronThetaPlot",TitleElectronTheta,NBinsElectronTheta,MinElectronTheta,MaxElectronTheta);
	TH2D* ElectronPhiThetaPlot = new TH2D("ElectronPhiThetaPlot",TitleElectronPhiVsTheta,NBinsElectronPhi,MinElectronPhi,MaxElectronPhi,NBinsElectronTheta,MinElectronTheta,MaxElectronTheta);

	TH1D* ElectronCosThetaPlot = new TH1D("ElectronCosThetaPlot",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);
	TH1D* ElectronCosThetaPlot_OneProton = new TH1D("ElectronCosThetaPlot_OneProton",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);
	TH1D* QEElectronCosThetaPlot_OneProton = new TH1D("QEElectronCosThetaPlot_OneProton",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);
	TH1D* MECElectronCosThetaPlot_OneProton = new TH1D("MECElectronCosThetaPlot_OneProton",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);
	TH1D* RESElectronCosThetaPlot_OneProton = new TH1D("RESElectronCosThetaPlot_OneProton",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);
	TH1D* DISElectronCosThetaPlot_OneProton = new TH1D("DISElectronCosThetaPlot_OneProton",TitleElectronCosTheta,NBinsElectronCosTheta,MinElectronCosTheta,MaxElectronCosTheta);

	TH1D* ElectronMomentumPlot = new TH1D("ElectronMomentumPlot",TitleElectronMom,NBinsElectronMom,MinElectronMom,MaxElectronMom);
	TH1D* ElectronMomentumPlot_OneProton = new TH1D("ElectronMomentumPlot_OneProton",TitleElectronMom,NBinsElectronMom,MinElectronMom,MaxElectronMom);
	TH1D* QEElectronMomentumPlot_OneProton = new TH1D("QEElectronMomentumPlot_OneProton",TitleElectronMom,NBinsElectronMom,MinElectronMom,MaxElectronMom);
	TH1D* MECElectronMomentumPlot_OneProton = new TH1D("MECElectronMomentumPlot_OneProton",TitleElectronMom,NBinsElectronMom,MinElectronMom,MaxElectronMom);
	TH1D* RESElectronMomentumPlot_OneProton = new TH1D("RESElectronMomentumPlot_OneProton",TitleElectronMom,NBinsElectronMom,MinElectronMom,MaxElectronMom);
	TH1D* DISElectronMomentumPlot_OneProton = new TH1D("DISElectronMomentumPlot_OneProton",TitleElectronMom,NBinsElectronMom,MinElectronMom,MaxElectronMom);

	// Proton

	TH1D* ProtonEnergyPlot = new TH1D("ProtonEnergyPlot",TitleEp,NBinsEp,MinEp,MaxEp);
	TH1D* ProtonPhiPlot = new TH1D("ProtonPhiPlot",TitleProtonPhi,NBinsProtonPhi,MinProtonPhi,MaxProtonPhi);
	TH1D* ProtonThetaPlot = new TH1D("ProtonThetaPlot",TitleProtonTheta,NBinsProtonTheta,MinProtonTheta,MaxProtonTheta);
	TH1D* ProtonCosThetaPlot = new TH1D("ProtonCosThetaPlot",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);
	TH1D* EcalResoPlot = new TH1D("EcalResoPlot",TitleReso,NBinsReso,MinReso,MaxReso);

	TH1D* ProtonCosThetaPlot_OneProton = new TH1D("ProtonCosThetaPlot_OneProton",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);
	TH1D* QEProtonCosThetaPlot_OneProton = new TH1D("QEProtonCosThetaPlot_OneProton",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);
	TH1D* MECProtonCosThetaPlot_OneProton = new TH1D("MECProtonCosThetaPlot_OneProton",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);
	TH1D* RESProtonCosThetaPlot_OneProton = new TH1D("RESProtonCosThetaPlot_OneProton",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);
	TH1D* DISProtonCosThetaPlot_OneProton = new TH1D("DISProtonCosThetaPlot_OneProton",TitleProtonCosTheta,NBinsProtonCosTheta,MinProtonCosTheta,MaxProtonCosTheta);

	TH1D* ProtonMomentumPlot_OneProton = new TH1D("ProtonMomentumPlot_OneProton",TitlePp,NBinsPp,MinPp,MaxPp);
	TH1D* QEProtonMomentumPlot_OneProton = new TH1D("QEProtonMomentumPlot_OneProton",TitlePp,NBinsPp,MinPp,MaxPp);
	TH1D* MECProtonMomentumPlot_OneProton = new TH1D("MECProtonMomentumPlot_OneProton",TitlePp,NBinsPp,MinPp,MaxPp);
	TH1D* RESProtonMomentumPlot_OneProton = new TH1D("RESProtonMomentumPlot_OneProton",TitlePp,NBinsPp,MinPp,MaxPp);
	TH1D* DISProtonMomentumPlot_OneProton = new TH1D("DISProtonMomentumPlot_OneProton",TitlePp,NBinsPp,MinPp,MaxPp);

	TH2D* EpVsMissMomentumPlot = new TH2D("EpVsMissMomentumPlot",TitleProtonEnergyVsMissMomentum,NBinsPmiss,MinPmiss,MaxPmiss,NBinsEp,MinEp,MaxEp);
	TH2D* Q2VsMissMomentumPlot = new TH2D("Q2VsMissMomentumPlot",TitleQ2VsMissMomentum,NBinsPmiss,MinPmiss,MaxPmiss,NBinsQ2,MinQ2,MaxQ2);

	// -------------------------------------------------------------------------------------

	TH1D* DeltaPhiTPlot = new TH1D("DeltaPhiTPlot",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* DeltaAlphaTPlot = new TH1D("DeltaAlphaTPlot",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* MissMomentumPlot = new TH1D("MissMomentumPlot",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	TH1D* QEDeltaPhiTPlot_OneProton = new TH1D("QEDeltaPhiTPlot_OneProton",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* QEDeltaAlphaTPlot_OneProton = new TH1D("QEDeltaAlphaTPlot_OneProton",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* QEMissMomentumPlot_OneProton = new TH1D("QEMissMomentumPlot_OneProton",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	TH1D* MECDeltaPhiTPlot_OneProton = new TH1D("MECDeltaPhiTPlot_OneProton",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* MECDeltaAlphaTPlot_OneProton = new TH1D("MECDeltaAlphaTPlot_OneProton",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* MECMissMomentumPlot_OneProton = new TH1D("MECMissMomentumPlot_OneProton",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	TH1D* RESDeltaPhiTPlot_OneProton = new TH1D("RESDeltaPhiTPlot_OneProton",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* RESDeltaAlphaTPlot_OneProton = new TH1D("RESDeltaAlphaTPlot_OneProton",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* RESMissMomentumPlot_OneProton = new TH1D("RESMissMomentumPlot_OneProton",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	TH1D* DISDeltaPhiTPlot_OneProton = new TH1D("DISDeltaPhiTPlot_OneProton",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* DISDeltaAlphaTPlot_OneProton = new TH1D("DISDeltaAlphaTPlot_OneProton",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* DISMissMomentumPlot_OneProton = new TH1D("DISMissMomentumPlot_OneProton",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	TH1D* DeltaPhiTPlot_OneProton = new TH1D("DeltaPhiT_OneProtonPlot",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* DeltaAlphaTPlot_OneProton = new TH1D("DeltaAlphaT_OneProtonPlot",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* MissMomentumPlot_OneProton = new TH1D("MissMomentum_OneProtonPlot",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	// -------------------------------------------------------------------------------------

	TH1D* DeltaPhiTPlot_VectorSum = new TH1D("DeltaPhiT_VectorSumPlot",TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
	TH1D* DeltaAlphaTPlot_VectorSum = new TH1D("DeltaAlphaT_VectorSumPlot",TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
	TH1D* MissMomentumPlot_VectorSum = new TH1D("MissMomentum_VectorSumPlot",TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	// -------------------------------------------------------------------------------------

	int NBreakDown = 5; // All, QE, MEC, RES, DIS, COH

	TH1D* DeltaPhiTPlot_BreakDown[NBreakDown];
	TH1D* DeltaAlphaTPlot_BreakDown[NBreakDown];
	TH1D* MissMomentumPlot_BreakDown[NBreakDown];

	TH1D* DeltaPhiTPlot_OneProton_BreakDown[NBreakDown];
	TH1D* DeltaAlphaTPlot_OneProton_BreakDown[NBreakDown];
	TH1D* MissMomentumPlot_OneProton_BreakDown[NBreakDown];

	TH1D* DeltaPhiTPlot_VectorSum_BreakDown[NBreakDown];
	TH1D* DeltaAlphaTPlot_VectorSum_BreakDown[NBreakDown];
	TH1D* MissMomentumPlot_VectorSum_BreakDown[NBreakDown];

	for (int i = 0; i < NBreakDown; i++) {

		DeltaPhiTPlot_BreakDown[i] = new TH1D("DeltaPhiTPlot_BreakDown_"+ToString(i),TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
		DeltaAlphaTPlot_BreakDown[i] = new TH1D("DeltaAlphaTPlot_BreakDown_"+ToString(i),TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
		MissMomentumPlot_BreakDown[i] = new TH1D("MissMomentumPlot_BreakDown_"+ToString(i),TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

		DeltaPhiTPlot_OneProton_BreakDown[i] = new TH1D("DeltaPhiT_OneProtonPlot_BreakDown_"+ToString(i),TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
		DeltaAlphaTPlot_OneProton_BreakDown[i] = new TH1D("DeltaAlphaT_OneProtonPlot_BreakDown_"+ToString(i),TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
		MissMomentumPlot_OneProton_BreakDown[i] = new TH1D("MissMomentum_OneProtonPlot_BreakDown_"+ToString(i),TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

		DeltaPhiTPlot_VectorSum_BreakDown[i] = new TH1D("DeltaPhiT_VectorSumPlot_BreakDown_"+ToString(i),TitleDeltaPhiT,NBinsDeltaPhiT,MinDeltaPhiT,MaxDeltaPhiT);
		DeltaAlphaTPlot_VectorSum_BreakDown[i] = new TH1D("DeltaAlphaT_VectorSumPlot_BreakDown_"+ToString(i),TitleDeltaAlphaT,NBinsDeltaAlphaT,MinDeltaAlphaT,MaxDeltaAlphaT);
		MissMomentumPlot_VectorSum_BreakDown[i] = new TH1D("MissMomentum_VectorSumPlot_BreakDown_"+ToString(i),TitlePmiss,NBinsPmiss,MinPmiss,MaxPmiss);

	}


	// -------------------------------------------------------------------------------------

	int NBinsCalorimetricEnergy = 400; double MinCalorimetricEnergy = 0.,MaxCalorimetricEnergy = 6.; TString TitleCalorimetricEnergy = ";E^{cal} (GeV);";
	TH1D* epRecoEnergy_slice_0Plot = new TH1D("epRecoEnergy_slice_0Plot",TitleCalorimetricEnergy,NBinsCalorimetricEnergy,MinCalorimetricEnergy,MaxCalorimetricEnergy);
	TH1D* epRecoEnergy_slice_1Plot = new TH1D("epRecoEnergy_slice_1Plot",TitleCalorimetricEnergy,NBinsCalorimetricEnergy,MinCalorimetricEnergy,MaxCalorimetricEnergy);
	TH1D* epRecoEnergy_slice_2Plot = new TH1D("epRecoEnergy_slice_2Plot",TitleCalorimetricEnergy,NBinsCalorimetricEnergy,MinCalorimetricEnergy,MaxCalorimetricEnergy);
	TH1D* epRecoEnergy_slice_3Plot = new TH1D("epRecoEnergy_slice_3Plot",TitleCalorimetricEnergy,NBinsCalorimetricEnergy,MinCalorimetricEnergy,MaxCalorimetricEnergy);

	int NBinsLeptonicEnergy = 200; double MinLeptonicEnergy = 0.,MaxLeptonicEnergy = 6.; TString TitleLeptonicEnergy = ";E^{QE} (GeV);";
	TH1D* eRecoEnergy_slice_0Plot = new TH1D("eRecoEnergy_slice_0Plot",TitleLeptonicEnergy,NBinsLeptonicEnergy,MinLeptonicEnergy,MaxLeptonicEnergy);
	TH1D* eRecoEnergy_slice_1Plot = new TH1D("eRecoEnergy_slice_1Plot",TitleLeptonicEnergy,NBinsLeptonicEnergy,MinLeptonicEnergy,MaxLeptonicEnergy);
	TH1D* eRecoEnergy_slice_2Plot = new TH1D("eRecoEnergy_slice_2Plot",TitleLeptonicEnergy,NBinsLeptonicEnergy,MinLeptonicEnergy,MaxLeptonicEnergy);
	TH1D* eRecoEnergy_slice_3Plot = new TH1D("eRecoEnergy_slice_3Plot",TitleLeptonicEnergy,NBinsLeptonicEnergy,MinLeptonicEnergy,MaxLeptonicEnergy);

	// -------------------------------------------------------------------------------------------------------------

	// 2D Inclusive Plots

	TH2D* QE_Q0_Q3_Plot = new TH2D("QE_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* MEC_Q0_Q3_Plot = new TH2D("MEC_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* RES_Q0_Q3_Plot = new TH2D("RES_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* DIS_Q0_Q3_Plot = new TH2D("DIS_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);

	TH2D* UnweightedQE_Q0_Q3_Plot = new TH2D("UnweightedQE_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* UnweightedMEC_Q0_Q3_Plot = new TH2D("UnweightedMEC_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* UnweightedRES_Q0_Q3_Plot = new TH2D("UnweightedRES_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);
	TH2D* UnweightedDIS_Q0_Q3_Plot = new TH2D("UnweightedDIS_Q0_Q3_Plot",";q_{3} [GeV/c];q_{0} [GeV]",200,0,2.,200,0.,2.);

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

	if (nentries > 90000000) { nentries = 90000000; }

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// ------------------------------------------------------------------------------------------

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

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
		int LeadProtonID = -99;
		double LeadProtonMag = -99.;

		double ProtonVectorSumX = 0.;
		double ProtonVectorSumY = 0.;
		double ProtonVectorSumZ = 0.;
		double ProtonVectorSumE = 0.;

		for (int i = 0; i < nf; i++) {

			if (pdgf[i] == 2212 && pf[i] > 0.3) {

				ProtonTagging ++;

				ProtonVectorSumX += pxf[i];
				ProtonVectorSumY += pyf[i];
				ProtonVectorSumZ += pzf[i];
				ProtonVectorSumE += Ef[i];

				if ( pf[i] > LeadProtonMag) {

					LeadProtonID = i;
					LeadProtonMag = pf[i];

				}

			}

			if (pdgf[i] == 211 && pf[i] > 0.07)  {

				ChargedPionPlusTagging ++;

			}

			if (pdgf[i] == -211 && pf[i] > 0.07)  {

				ChargedPionMinusTagging ++;

			}

			if (pdgf[i] == 22  /*&& pf[i] > 0.3*/) { GammaTagging ++; }

			if (pdgf[i] == 111 /*&& pf[i] > 0.5*/) { NeutralPionTagging ++; }

		}

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

		// -------------------------------------------------------------------------------------------------------

		double Weight = 1.;
		if (fInteraction == "EM+MEC" || fInteraction == "EM") { Weight = Q2*Q2; }

        	if (fabs(Weight) != Weight) continue;

		// -----------------------------------------------------------------------------------------------

		EvPlot->Fill(Ev,Weight);
		EvPlot_Interaction[Interaction]->Fill(Ev,Weight);

		// -----------------------------------------------------------------------------------------------

		countEvents ++;	// Increase the number of the events that pass the cuts by one   

		// ------------------------------------------------------------------------------------------------

		Q2Plot->Fill(Q2,Weight);
		nuPlot->Fill(nu,Weight);
		UnweightedQ2Plot->Fill(Q2);
		UnweightednuPlot->Fill(nu);
		WPlot->Fill(W,Weight);
		xBPlot->Fill(x,Weight);

		// 1D Electron Plots

		ElectronThetaPlot->Fill(ElectronTheta,Weight);
		ElectronCosThetaPlot->Fill(ElectronCosTheta,Weight);
		ElectronPhiPlot->Fill(ElectronPhi,Weight);
		ElectronEnergyPlot->Fill(El,Weight);
		ElectronMomentumPlot->Fill(pl,Weight);

		ElectronPhiThetaPlot->Fill(ElectronPhi,ElectronTheta,Weight);

		// 2D Plots

		Q2VsWPlot->Fill(W,Q2,Weight);
		Q2VsnuPlot->Fill(nu,Q2,Weight);

		if (qel == 1) { QE_Q0_Q3_Plot->Fill(q3,nu,Weight); UnweightedQE_Q0_Q3_Plot->Fill(q3,nu); }
		if (mec == 1) { MEC_Q0_Q3_Plot->Fill(q3,nu,Weight); UnweightedMEC_Q0_Q3_Plot->Fill(q3,nu); }
		if (res == 1) { RES_Q0_Q3_Plot->Fill(q3,nu,Weight); UnweightedRES_Q0_Q3_Plot->Fill(q3,nu); }
		if (dis == 1) { DIS_Q0_Q3_Plot->Fill(q3,nu,Weight); UnweightedDIS_Q0_Q3_Plot->Fill(q3,nu); }

		// -------------------------------------------------------------------------------------

		// From this point & below
		// Requiring the existence of at least one proton above threshold 
		// To performs STV study

		// -------------------------------------------------------------------------------------

		if (ProtonTagging == 0) { continue; }
		if (ChargedPionPlusTagging != 0) { continue; }
		if (ChargedPionMinusTagging != 0) { continue; }
		if (GammaTagging != 0) { continue; }
		if (NeutralPionTagging != 0) { continue; }

		// -----------------------------------------------------------------------------------------------------
		
		// Leading Proton

                TLorentzVector ProtonV4(pxf[LeadProtonID],pyf[LeadProtonID],pzf[LeadProtonID],Ef[LeadProtonID]);
		double ProtonE = ProtonV4.E(); 
		double ProtonMom  = ProtonV4.Rho();
		double ProtonTheta = ProtonV4.Theta()*180./TMath::Pi();
		if (ProtonTheta < 0) { ProtonTheta += 180.; }
		if (ProtonTheta > 180) { ProtonTheta -= 180.; }
		double ProtonCosTheta = ProtonV4.CosTheta();
		double ProtonPhi = ProtonV4.Phi()*180./TMath::Pi();
		if (ProtonPhi < 0) { ProtonPhi += 360; }
		if (ProtonPhi > 360) { ProtonPhi -= 360; }

		// Calorimetric Energy Reconstruction

		double Ecal = El + ProtonE - ProtonMass + BE;

		// Transverse variables

		TVector3 ProtonT(ProtonV4.X(),ProtonV4.Y(),0);
		double ProtonTMag = ProtonT.Mag();
		TVector3 ElectronT(ElectronV4.X(),ElectronV4.Y(),0);
		double ElectronTMag = ElectronT.Mag();
		TVector3 MissMomentumT = ProtonT + ElectronT;
		double MissMomentumTMag = MissMomentumT.Mag();

		double DeltaPhiT = TMath::ACos(-ProtonT*ElectronT/ProtonTMag/ElectronTMag)*180/TMath::Pi();
		double DeltaAlphaT = TMath::ACos(-MissMomentumT*ElectronT/MissMomentumTMag/ElectronTMag)*180/TMath::Pi();

		// -----------------------------------------------------------------------------------------------------------

		// Proton Vector Sum

                TLorentzVector VectorSumProtonV4(ProtonVectorSumX,ProtonVectorSumY,ProtonVectorSumZ,ProtonVectorSumE);
		double VectorSumProtonE = VectorSumProtonV4.E(); 
		double VectorSumProtonMom  = VectorSumProtonV4.Rho();
		double VectorSumProtonTheta = VectorSumProtonV4.Theta()*180./TMath::Pi();
		if (VectorSumProtonTheta < 0) { VectorSumProtonTheta += 180.; }
		if (VectorSumProtonTheta > 180) { VectorSumProtonTheta -= 180.; }
		double VectorSumProtonCosTheta = VectorSumProtonV4.CosTheta();
		double VectorSumProtonPhi = VectorSumProtonV4.Phi()*180./TMath::Pi();
		if (VectorSumProtonPhi < 0) { VectorSumProtonPhi += 360; }
		if (VectorSumProtonPhi > 360) { VectorSumProtonPhi -= 360; }

		// Vector Sum Transverse variables

		TVector3 VectorSumProtonT(VectorSumProtonV4.X(),VectorSumProtonV4.Y(),0);
		double VectorSumProtonTMag = VectorSumProtonT.Mag();
		TVector3 VectorSumMissMomentumT = VectorSumProtonT + ElectronT;
		double VectorSumMissMomentumTMag = VectorSumMissMomentumT.Mag();

		double VectorSumDeltaPhiT = TMath::ACos(-VectorSumProtonT*ElectronT/VectorSumProtonTMag/ElectronTMag)*180/TMath::Pi();
		double VectorSumDeltaAlphaT = TMath::ACos(-VectorSumMissMomentumT*ElectronT/VectorSumMissMomentumTMag/ElectronTMag)*180/TMath::Pi();

		// -----------------------------------------------------------------------------------------------------------

		ProtonCosThetaPlot->Fill(ProtonCosTheta,Weight);	
		ProtonThetaPlot->Fill(ProtonTheta,Weight);
		ProtonPhiPlot->Fill(ProtonPhi,Weight);
		ProtonEnergyPlot->Fill(ProtonE,Weight);
		EcalResoPlot->Fill((Ecal - Ebeam) / Ebeam * 100.,Weight);

		EpVsMissMomentumPlot->Fill(MissMomentumTMag,ProtonE,Weight);
		Q2VsMissMomentumPlot->Fill(MissMomentumTMag,Q2,Weight);

		DeltaPhiTPlot->Fill(DeltaPhiT,Weight);
		DeltaAlphaTPlot->Fill(DeltaAlphaT,Weight);
		MissMomentumPlot->Fill(MissMomentumTMag,Weight);

		DeltaPhiTPlot_BreakDown[Interaction]->Fill(DeltaPhiT,Weight);
		DeltaAlphaTPlot_BreakDown[Interaction]->Fill(DeltaAlphaT,Weight);
		MissMomentumPlot_BreakDown[Interaction]->Fill(MissMomentumTMag,Weight);

		DeltaPhiTPlot_VectorSum->Fill(VectorSumDeltaPhiT,Weight);
		DeltaAlphaTPlot_VectorSum->Fill(VectorSumDeltaAlphaT,Weight);
		MissMomentumPlot_VectorSum->Fill(VectorSumMissMomentumTMag,Weight);

		DeltaPhiTPlot_VectorSum_BreakDown[Interaction]->Fill(VectorSumDeltaPhiT,Weight);
		DeltaAlphaTPlot_VectorSum_BreakDown[Interaction]->Fill(VectorSumDeltaAlphaT,Weight);
		MissMomentumPlot_VectorSum_BreakDown[Interaction]->Fill(VectorSumMissMomentumTMag,Weight);

		if (ProtonTagging == 1) {

			Q2Plot_OneProton->Fill(Q2,Weight);
			nuPlot_OneProton->Fill(nu,Weight);
			ElectronMomentumPlot_OneProton->Fill(pl,Weight);
			ElectronCosThetaPlot_OneProton->Fill(ElectronCosTheta,Weight);	

			UnweightedQ2Plot_OneProton->Fill(Q2);
			UnweightednuPlot_OneProton->Fill(nu);

			ProtonMomentumPlot_OneProton->Fill(ProtonMom,Weight);
			ProtonCosThetaPlot_OneProton->Fill(ProtonCosTheta,Weight);	

			DeltaPhiTPlot_OneProton->Fill(DeltaPhiT,Weight);
			DeltaAlphaTPlot_OneProton->Fill(DeltaAlphaT,Weight);
			MissMomentumPlot_OneProton->Fill(MissMomentumTMag,Weight);

			if (qel) {

				QEnuPlot_OneProton->Fill(nu,Weight);
				UnweightedQEnuPlot_OneProton->Fill(nu);
				QEElectronMomentumPlot_OneProton->Fill(ElectronMom,Weight);
				QEElectronCosThetaPlot_OneProton->Fill(ElectronCosTheta,Weight);	

				QEQ2Plot_OneProton->Fill(Q2,Weight);
				UnweightedQEQ2Plot_OneProton->Fill(Q2);

				QEProtonMomentumPlot_OneProton->Fill(ProtonMom,Weight);
				QEProtonCosThetaPlot_OneProton->Fill(ProtonCosTheta,Weight);

				QEDeltaPhiTPlot_OneProton->Fill(DeltaPhiT,Weight);
				QEDeltaAlphaTPlot_OneProton->Fill(DeltaAlphaT,Weight);
				QEMissMomentumPlot_OneProton->Fill(MissMomentumTMag,Weight);

			}

			if (mec) {

				MECnuPlot_OneProton->Fill(nu,Weight);
				UnweightedMECnuPlot_OneProton->Fill(nu);
				MECElectronMomentumPlot_OneProton->Fill(ElectronMom,Weight);
				MECElectronCosThetaPlot_OneProton->Fill(ElectronCosTheta,Weight);

				MECQ2Plot_OneProton->Fill(Q2,Weight);
				UnweightedMECQ2Plot_OneProton->Fill(Q2);

				MECProtonMomentumPlot_OneProton->Fill(ProtonMom,Weight);
				MECProtonCosThetaPlot_OneProton->Fill(ProtonCosTheta,Weight);

				MECDeltaPhiTPlot_OneProton->Fill(DeltaPhiT,Weight);
				MECDeltaAlphaTPlot_OneProton->Fill(DeltaAlphaT,Weight);
				MECMissMomentumPlot_OneProton->Fill(MissMomentumTMag,Weight);

			}

			if (res) {

				RESnuPlot_OneProton->Fill(nu,Weight);
				UnweightedRESnuPlot_OneProton->Fill(nu);
				RESElectronMomentumPlot_OneProton->Fill(ElectronMom,Weight);
				RESElectronCosThetaPlot_OneProton->Fill(ElectronCosTheta,Weight);

				RESQ2Plot_OneProton->Fill(Q2,Weight);
				UnweightedRESQ2Plot_OneProton->Fill(Q2);

				RESProtonMomentumPlot_OneProton->Fill(ProtonMom,Weight);
				RESProtonCosThetaPlot_OneProton->Fill(ProtonCosTheta,Weight);

				RESDeltaPhiTPlot_OneProton->Fill(DeltaPhiT,Weight);
				RESDeltaAlphaTPlot_OneProton->Fill(DeltaAlphaT,Weight);
				RESMissMomentumPlot_OneProton->Fill(MissMomentumTMag,Weight);

			}

			if (dis) {

				DISnuPlot_OneProton->Fill(nu,Weight);
				UnweightedDISnuPlot_OneProton->Fill(nu);
				DISElectronMomentumPlot_OneProton->Fill(ElectronMom,Weight);
				DISElectronCosThetaPlot_OneProton->Fill(ElectronCosTheta,Weight);

				DISQ2Plot_OneProton->Fill(Q2,Weight);
				UnweightedDISQ2Plot_OneProton->Fill(Q2);

				DISProtonMomentumPlot_OneProton->Fill(ProtonMom,Weight);
				DISProtonCosThetaPlot_OneProton->Fill(ProtonCosTheta,Weight);

				DISDeltaPhiTPlot_OneProton->Fill(DeltaPhiT,Weight);
				DISDeltaAlphaTPlot_OneProton->Fill(DeltaAlphaT,Weight);
				DISMissMomentumPlot_OneProton->Fill(MissMomentumTMag,Weight);

			}

			DeltaPhiTPlot_OneProton_BreakDown[Interaction]->Fill(DeltaPhiT,Weight);
			DeltaAlphaTPlot_OneProton_BreakDown[Interaction]->Fill(DeltaAlphaT,Weight);
			MissMomentumPlot_OneProton_BreakDown[Interaction]->Fill(MissMomentumTMag,Weight);

		}

		// ----------------------------------------------------------------------------------------------

		// Define the missing momentum bin
		/*
		if (MissMomentumTMag < 0.2) MissMomentumBin = 1;
		if (MissMomentumTMag > 0.2 && MissMomentumTMag < 0.4) MissMomentumBin = 2;
		if (MissMomentumTMag > 0.4) MissMomentumBin = 3;
		*/

		// Reconstructed Energy Plots

		epRecoEnergy_slice_0Plot->Fill(Ecal,Weight); eRecoEnergy_slice_0Plot->Fill(EQE,Weight);
//		if (MissMomentumBin == 1) { epRecoEnergy_slice_1Plot->Fill(Ecal,Weight); eRecoEnergy_slice_1Plot->Fill(EQE,Weight);}
//		if (MissMomentumBin == 2) { epRecoEnergy_slice_2Plot->Fill(Ecal,Weight); eRecoEnergy_slice_2Plot->Fill(EQE,Weight);}
//		if (MissMomentumBin == 3) { epRecoEnergy_slice_3Plot->Fill(Ecal,Weight); eRecoEnergy_slice_3Plot->Fill(EQE,Weight);}
		

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
