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

using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void CreateTTree() {
 TFile *f = new TFile("Noemmi_12C_1GeV_37deg.root" ,"recreate");
 //TTree *t = new TTree("qent","qent");
 ifstream newInput("C12_1161_37p5_pwia.out");

 const int NBins = 80; 

 double v[NBins] = {0};
 double XSec[NBins] = {0};
 double XSecErr[NBins] = {0};

 string line;

 if (newInput.is_open())
  {
    int Counter = 0;
    while ( getline (newInput,line) )
    {
      cout << line << '\n';
      vector<string> words = split (line," ");
      v[Counter] = 0.001*strtod(words[0].c_str(),NULL); 
      XSec[Counter] = strtod(words[1].c_str(),NULL);
      XSecErr[Counter] = strtod(words[2].c_str(),NULL);

	Counter++;

    }

    TGraph* g = new TGraph(NBins,v,XSec);

    g->SetMarkerStyle(20);
    g->SetMarkerColor(kBlack);
    g->SetMarkerSize(1.2);

	TFile* CorrectedDatae4vFile = TFile::Open("../InclusiveXSecBenchmark/e4v_C12_E_1_161_theta_37_5.root");

	TH1D* CorrectedDatae4vPlot = (TH1D*)CorrectedDatae4vFile->Get("Correctede4vData"); // already extracted xsec in e4vXSecRatio.cxx solid angle for 24 < phi < 36 && 36 < theta < 39 

	CorrectedDatae4vPlot->SetLineColor(kGreen+2);
	CorrectedDatae4vPlot->SetMarkerColor(kGreen+2);
	CorrectedDatae4vPlot->SetMarkerStyle(20);
	CorrectedDatae4vPlot->SetMarkerSize(1.);
	CorrectedDatae4vPlot->SetLineWidth(1);
	CorrectedDatae4vPlot->Draw("e1x0 same");

    g->Draw("p same");

    newInput.close();
  }


  f->Write();
  f->Close();
 
}
