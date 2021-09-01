void MergePanelsFigFour() {

	gStyle->SetOptStat(0);	
	gStyle->SetErrorX(0);

	// ---------------------------------------------------------------------------------------------------------

	// Fig 4: (left) PT, (right) ECal

	TFile* fLeft = new TFile("Fig3a_PT.root","readonly");
	TCanvas* cLeft = (TCanvas*)(fLeft->Get("12C_2_261_MissMomentum_NoxBCut"));

	TFile* fRight = new TFile("Fig3b_ECal.root","readonly");
	TCanvas* cRight = (TCanvas*)(fRight->Get("12C_2_261_ECalInPmissSlices_NoxBCut"));

	TCanvas *ctot = new TCanvas("ctot","",1700,1000);
	ctot->cd();

	TPad* left = new TPad("left","left",0.,0.,0.5,1.,21);
	left->SetFillColor(kWhite); 
	left->Draw();
	left->cd();

	cLeft->DrawClonePad();

	ctot->cd();
	TPad* right = new TPad("right","right",0.5,0.,1.,1.,21);
	right->SetFillColor(kWhite); 
	right->Draw();
	right->cd();

	cRight->DrawClonePad();

	ctot->SaveAs("Merged_Fig4.pdf");
	ctot->SaveAs("Merged_Fig4.eps");

	delete ctot;
	fLeft->Close();
	fRight->Close();

	// ---------------------------------------------------------------------------------------------------------

	// Fig Ext Data 3: (left) Multiplicities, (right) Inclusive XSecs

	TFile* fLeftExtDataFigThree = new TFile("../AreaNormalized/Multiplicities.root","readonly");
	TCanvas* cLeftExtDataFigThree = (TCanvas*)(fLeftExtDataFigThree->Get("12C_2_261_Multiplicities_NoxBCut"));

	TFile* fRightExtDataFigThree = new TFile("../../InclusiveXSecBenchmark/DataXSec_Inclusive_Validation.root","readonly");
	TCanvas* cRightExtDataFigThree = (TCanvas*)(fRightExtDataFigThree->Get("DataXSec_Inclusive_Validation"));

	TCanvas *ctotExtDataFigThree = new TCanvas("ctotExtDataFigThree","",2048,768);
	ctotExtDataFigThree->cd();

	TPad* leftExtDataFigThree = new TPad("leftExtDataFigThree","leftExtDataFigThree",0.,0.,0.5,1.,21);
	leftExtDataFigThree->SetFillColor(kWhite); 
	leftExtDataFigThree->Draw();
	leftExtDataFigThree->cd();

	cLeftExtDataFigThree->DrawClonePad();

	ctotExtDataFigThree->cd();
	TPad* rightExtDataFigThree = new TPad("rightExtDataFigThree","rightExtDataFigThree",0.5,0.,1.,1.,21);
	rightExtDataFigThree->SetFillColor(kWhite); 
	rightExtDataFigThree->Draw();
	rightExtDataFigThree->cd();

	TGaxis::SetMaxDigits(3);
	TGaxis::SetExponentOffset(-0.1, 1., "y");

	cRightExtDataFigThree->DrawClonePad();

	ctotExtDataFigThree->SaveAs("Merged_FigExtData3.pdf");
	ctotExtDataFigThree->SaveAs("Merged_FigExtData3.eps");

	delete ctotExtDataFigThree;
	fLeftExtDataFigThree->Close();
	fRightExtDataFigThree->Close();

	// ---------------------------------------------------------------------------------------------------------

	// Fig Ext Data 4: ECal & EQE Resolutions

	TFile* fLeftExtDataFigFour = new TFile("Resolutions.root","readonly");
	TCanvas* cUpperLeftExtDataFigFour = (TCanvas*)(fLeftExtDataFigFour->Get("12C_h_Etot_subtruct_piplpimi_2p1pi_1p0pi_fracfeed_NoxBCut"));
	TCanvas* cUpperRightExtDataFigFour = (TCanvas*)(fLeftExtDataFigFour->Get("12C_h_Erec_subtruct_piplpimi_noprot_frac_feed3pi_NoxBCut"));
	TCanvas* cLowerLeftExtDataFigFour = (TCanvas*)(fLeftExtDataFigFour->Get("56Fe_h_Etot_subtruct_piplpimi_2p1pi_1p0pi_fracfeed_NoxBCut"));
	TCanvas* cLowerRightExtDataFigFour = (TCanvas*)(fLeftExtDataFigFour->Get("56Fe_h_Erec_subtruct_piplpimi_noprot_frac_feed3pi_NoxBCut"));

	TCanvas *ctotExtDataFigFour = new TCanvas("ctotExtDataFigFour","",2048,1536);
	ctotExtDataFigFour->cd();

	TPad* upperleftExtDataFigFour = new TPad("upperleftExtDataFigFour","upperleftExtDataFigFour",0.,0.5,0.5,1.,21);
	upperleftExtDataFigFour->SetFillColor(kWhite); 
	upperleftExtDataFigFour->Draw();
	upperleftExtDataFigFour->cd();
	cUpperLeftExtDataFigFour->DrawClonePad();

	ctotExtDataFigFour->cd();
	TPad* upperrightExtDataFigFour = new TPad("upperrightExtDataFigFour","upperrightExtDataFigFour",0.5,0.5,1.,1.,21);
	upperrightExtDataFigFour->SetFillColor(kWhite); 
	upperrightExtDataFigFour->Draw();
	upperrightExtDataFigFour->cd();
	cUpperRightExtDataFigFour->DrawClonePad();

	ctotExtDataFigFour->cd();
	TPad* lowerleftExtDataFigFour = new TPad("lowerleftExtDataFigFour","lowerleftExtDataFigFour",0.,0.,0.5,0.5,21);
	lowerleftExtDataFigFour->SetFillColor(kWhite); 
	lowerleftExtDataFigFour->Draw();
	lowerleftExtDataFigFour->cd();
	cLowerLeftExtDataFigFour->DrawClonePad();

	ctotExtDataFigFour->cd();
	TPad* lowerrightExtDataFigFour = new TPad("lowerrightExtDataFigFour","lowerrightExtDataFigFour",0.5,0.,1.,0.5,21);
	lowerrightExtDataFigFour->SetFillColor(kWhite); 
	lowerrightExtDataFigFour->Draw();
	lowerrightExtDataFigFour->cd();
	cLowerRightExtDataFigFour->DrawClonePad();

	ctotExtDataFigFour->SaveAs("Merged_FigExtData4.pdf");
	ctotExtDataFigFour->SaveAs("Merged_FigExtData4.eps");

	delete ctotExtDataFigFour;
	fLeftExtDataFigFour->Close();

	// ---------------------------------------------------------------------------------------------------------

	// Fig Ext Data 6: (upper) Delta AlphaT panel, (bottom) Delta PhiT panel

	TFile* fLeftExtDataFigSix = new TFile("ExtDataFig6_DeltaAlphaT.root","readonly");
	TCanvas* cLeftExtDataFigSix = (TCanvas*)(fLeftExtDataFigSix->Get("NoxBCut"));

	TFile* fRightExtDataFigSix = new TFile("ExtDataFig6_DeltaPhiT.root","readonly");
	TCanvas* cRightExtDataFigSix = (TCanvas*)(fRightExtDataFigSix->Get("NoxBCut"));

	TCanvas *ctotExtDataFigSix = new TCanvas("ctotExtDataFigSix","",1600,1800);
	ctotExtDataFigSix->cd();

	TPad* leftExtDataFigSix = new TPad("leftExtDataFigSix","leftExtDataFigSix",0.,0.5,1.,1.,21);
	leftExtDataFigSix->SetFillColor(kWhite); 
	leftExtDataFigSix->Draw();
	leftExtDataFigSix->cd();

	cLeftExtDataFigSix->DrawClonePad();

	ctotExtDataFigSix->cd();
	TPad* rightExtDataFigSix = new TPad("rightExtDataFigSix","rightExtDataFigSix",0.,0.,1.,0.5,21);
	rightExtDataFigSix->SetFillColor(kWhite); 
	rightExtDataFigSix->Draw();
	rightExtDataFigSix->cd();

	TGaxis::SetMaxDigits(3);
	TGaxis::SetExponentOffset(-0.1, 1., "y");

	cRightExtDataFigSix->DrawClonePad();

	ctotExtDataFigSix->SaveAs("Merged_FigExtData6.pdf");
	ctotExtDataFigSix->SaveAs("Merged_FigExtData6.eps");

	//delete ctotExtDataFigSix;
	//fLeftExtDataFigSix->Close();
	//fRightExtDataFigSix->Close();

	// ---------------------------------------------------------------------------------------------------------

}
