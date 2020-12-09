# Runs to be used for the 1.1 GeV 12C 1500 samples

18294
18297
18298
18306
18307
18335

# ------------------------------------------------------

When Mikhail's cook is gonna be ready

1) make runnb private member of the class
2) declare array with runs for each energy / target
3) run (GetCharge_)FilterData for each run number 

4) store output under "scratch" area
   /lustre19/expphy/volatile/clas/clase2/apapadop

5) merge them under "persistent" area
   /w/hallb-scifs17exp/clas/claseg2/apapadop


export nucleus="56Fe"; export energy="2261"; 
hadd /w/hallb-scifs17exp/clas/claseg2/apapadop/MikhailCook_genie_filtered_data_e2a_ep_${nucleus}_${energy}_neutrino6_united4_radphot_test_100M.root /lustre19/expphy/volatile/clas/clase2/apapadop/MikhailCook_RunNumber_*_genie_filtered_data_e2a_ep_${nucleus}_${energy}_neutrino6_united4_radphot_test_100M.root


# Don't forget to pin the files or they will be deleted from cache 

jcache pin /cache/clas/e2a/production/pass3/v1/4461/C12/HROOT/*.root -D 60
