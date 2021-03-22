import ROOT

#datasets = ["DT","MC"]
datasets = ["Data","SuSav2","G2018"]
#mms = ["", "ShiftedFeeddowns"]
#mms = ["SuSav2_NoRadCorr_LFGM_Plots_FSI_em"]
#mms = ["CSMigrationMatrices"]

mms = ["MigrationMatrices_XSec"]
#mms = ["MigrationMatrices_NormYield"]
#mms = ["MigrationMatrices_AreaNorm"]

for mm in mms:
  for dataset in datasets:
    #f = ROOT.TFile.Open("MigrationMatrices%s.root"%mm);
    f = ROOT.TFile.Open("%s.root"%mm);
    #h = f.Get("%s12CMigrationMatrix"%dataset);
    h = f.Get("%s12CMigrationMatrix"%dataset);

    output = open("%s_%s.txt"%(mm,dataset),"w") 
    for i in range(h.GetNbinsX()):
        for j in range(h.GetNbinsY()):
            output.write("%.5f\t"%h.GetBinContent(i+1,j+1)); # reads the true columns vertically
        output.write("\n");

print("\nDone!\n")
