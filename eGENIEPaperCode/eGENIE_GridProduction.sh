
export GenieRelease=v3_00_06_WithSuSav2

###################################################################################################################################################################

# Neutrino 12C @ 1.1 GeV with Q2 > 0.1 w/o FSI

./submit_genie_cc_G00_00a_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_G00_00a_12C_1_161_nuGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G00_00a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_G00_00a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV_NoFSI/G00_00a/ origin/master_Q2_0_1_NoFSI

./submit_genie_cc_G18_02a_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_G18_02a_12C_1_161_nuGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G18_02a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_G18_02a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV_NoFSI/G18_02a/ origin/master_Q2_0_1_NoFSI

./submit_genie_cc_G2018_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_G2018_12C_1_161_nuGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G2018_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV_NoFSI/G2018/ origin/master_Q2_0_1_NoFSI

./submit_genie_cc_SuSav2_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_SuSav2_12C_1_161_nuGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_cc_SuSav2_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV_NoFSI/SuSav2/ origin/master_Q2_0_1_NoFSI

###################################################################################################################################################################

# Neutrino 12C @ 1.1 GeV with Q2 > 0.1 w/ FSI

./submit_genie_cc_G00_00a_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_G00_00a_12C_1_161_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G00_00a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_G00_00a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV/G00_00a/ origin/master_Q2_0_1

./submit_genie_cc_G18_02a_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_G18_02a_12C_1_161_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G18_02a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_G18_02a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV/G18_02a/ origin/master_Q2_0_1

./submit_genie_cc_G2018_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_G2018_12C_1_161_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G2018_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV/G2018/ origin/master_Q2_0_1

./submit_genie_cc_SuSav2_12C_1_161_Q2_0_1_NoRad_nuGENIE.sh 100 apapadop_SuSav2_12C_1_161_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_SuSav2_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_CCinclMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/12C_1_161GeV/SuSav2/ origin/master_Q2_0_1

###################################################################################################################################################################

# Electron 12C @ 1.1 GeV with Q2 > 0.1 w/o FSI

./submit_genie_em_G00_00a_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_G00_00a_12C_1_161_eGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_em_G00_00a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G00_00a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV_NoFSI/G00_00a/ origin/master_Q2_0_1_NoFSI

./submit_genie_em_G18_02a_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_G18_02a_12C_1_161_eGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_em_G18_02a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_02a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV_NoFSI/G18_02a/ origin/master_Q2_0_1_NoFSI

./submit_genie_em_G2018_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_G2018_12C_1_161_eGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV_NoFSI/G2018/ origin/master_Q2_0_1_NoFSI

./submit_genie_em_SuSav2_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_SuSav2_12C_1_161_eGENIE_NoFSI /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV_NoFSI/SuSav2/ origin/master_Q2_0_1_NoFSI


###################################################################################################################################################################


# Electron 12C @ 1.1 GeV with Q2 > 0.1 w/ FSI


./submit_genie_em_G00_00a_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_G00_00a_12C_1_161_eGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_em_G00_00a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G00_00a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV/G00_00a/ origin/master_Q2_0_1

./submit_genie_em_G18_02a_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_G18_02a_12C_1_161_eGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_em_G18_02a_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_02a_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV/G18_02a/ origin/master_Q2_0_1

./submit_genie_em_G2018_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_G2018_12C_1_161_eGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV/G2018/ origin/master_Q2_0_1

./submit_genie_em_SuSav2_12C_1_161_Q2_0_1_NoRad_eGENIE.sh 100 apapadop_SuSav2_12C_1_161_eGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_1_161_Q2_0_1_NoRad.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV/SuSav2/ origin/master_Q2_0_1


###################################################################################################################################################################
###################################################################################################################################################################


# Neutrino fluxes using DUNE/BNB/T2K/NOvA fluxes

	# NOvA


	# T2K


	# BNB

. ../submit_genie_cc_G00_00a_40Ar_BNBFlux_Q2_0_0_nuGENIE.sh 50 apapadop_G00_00a_40Ar_BNBFlux_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G00_00a_40Ar_BNBFlux_Q2_0_0_NoRad_nuGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/v3_0_6_WithSuSav2/argon40_spline_CCinclMEC_G00_00a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/40Ar_BNBFlux/G00_00a/ origin/master

. ../submit_genie_cc_G18_02a_40Ar_BNBFlux_Q2_0_0_nuGENIE.sh 50 apapadop_G18_02a_40Ar_BNBFlux_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G18_02a_40Ar_BNBFlux_Q2_0_0_NoRad_nuGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/v3_2/carbon12_spline_CCinclMEC_G18_02a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/40Ar_BNBFlux/G18_02a/ origin/master

. ../submit_genie_cc_G18_10a_40Ar_BNBFlux_Q2_0_0_nuGENIE.sh 50 apapadop_G18_10a_40Ar_BNBFlux_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G18_10a_40Ar_BNBFlux_Q2_0_0_NoRad_nuGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/v3_2/carbon12_spline_CCinclMEC_G18_10a_02_11a.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/40Ar_BNBFlux/G2018/ origin/master

. ../submit_genie_cc_GTEST19_10b_40Ar_BNBFlux_Q2_0_0_nuGENIE.sh 50 apapadop_G18_10a_40Ar_BNBFlux_nuGENIE /pnfs/genie/persistent/users/apapadop/Grid/args_cc_GTEST19_10b_40Ar_BNBFlux_Q2_0_0_NoRad_nuGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/v3_2/carbon12_spline_CCinclMEC_GTEST19_10b_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/nuGENIE_grid/40Ar_BNBFlux/SuSav2/ origin/master

	# DUNE

# Q2 > 0.02

./submit_genie_cc_G00_00a_40Ar_BNBFlux_Q2_0_0_nuGENIE.sh 50 apapadop_G00_00a_40Ar_BNBFlux_nuGENIE_Q2_0_02 /pnfs/genie/persistent/users/apapadop/Grid/args_cc_G00_00a_40Ar_BNBFlux_Q2_0_0_NoRad_nuGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/v3_0_6_WithSuSav2/argon40_spline_CCinclMEC_G00_00a_00_000_Q2_0_02.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/nuGENIE_grid_Q2_0_02/40Ar_BNBFlux/G00_00a/ origin/master_Q2_0_02



###################################################################################################################################################################
###################################################################################################################################################################


# Electron fluxes using DUNE/BNB/T2K/NOvA fluxes

	# NOvA

. ../submit_genie_em_G2018_CH2_NOvAFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G2018_CH2_NOvAFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_CH2_NOvAFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/CH_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC_Flux_NOvA_ND_2017.root flux_numu /pnfs/genie/scratch/users/apapadop/eGENIE_grid/CH2_NOvAFlux/G2018/ origin/master

. ../submit_genie_em_G18_02a_CH2_NOvAFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G18_02a_CH2_NOvAFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G18_02a_CH2_NOvAFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/CH_spline_EMPlusMEC_G18_02a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC_Flux_NOvA_ND_2017.root flux_numu /pnfs/genie/scratch/users/apapadop/eGENIE_grid/CH2_NOvAFlux/G18_02a/ origin/master

. ../submit_genie_em_G00_00a_CH2_NOvAFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G00_00a_CH2_NOvAFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G00_00a_CH2_NOvAFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/CH_spline_EMPlusMEC_G00_00a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC_Flux_NOvA_ND_2017.root flux_numu /pnfs/genie/scratch/users/apapadop/eGENIE_grid/CH2_NOvAFlux/G00_00a/ origin/master


	# T2K


. ../submit_genie_em_G2018_CH_T2KFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G2018_CH_T2KFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_CH_T2KFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/CH_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/persistent/users/apapadop/Grid/t2kflux_2016_plus250kA.root enu_nd280_numu /pnfs/genie/scratch/users/apapadop/eGENIE_grid/CH_T2KFlux/G2018/ origin/master

. ../submit_genie_em_G18_02a_CH_T2KFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G18_02a_CH_T2KFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G18_02a_CH_T2KFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/CH_spline_EMPlusMEC_G18_02a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/t2kflux_2016_plus250kA.root enu_nd280_numu /pnfs/genie/scratch/users/apapadop/eGENIE_grid/CH_T2KFlux/G18_02a/ origin/master

. ../submit_genie_em_G00_00a_CH_T2KFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G00_00a_CH_T2KFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G00_00a_CH_T2KFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/CH_spline_EMPlusMEC_G00_00a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/t2kflux_2016_plus250kA.root enu_nd280_numu /pnfs/genie/scratch/users/apapadop/eGENIE_grid/CH_T2KFlux/G00_00a/ origin/master


	# BNB


. ../submit_genie_em_G00_00a_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G00_00a_40Ar_BNBFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G00_00a_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_G00_00a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_BNBFlux/G00_00a/ origin/master

. ../submit_genie_em_G18_02a_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G18_02a_40Ar_BNBFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G18_02a_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_G18_02a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_BNBFlux/G18_02a/ origin/master

. ../submit_genie_em_SuSav2_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_SuSav2_40Ar_BNBFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_BNBFlux/SuSav2/ origin/master

. ../submit_genie_em_G2018_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G2018_40Ar_BNBFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_40Ar_BNBFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/persistent/users/apapadop/Grid/MCC9_FluxHist_volTPCActive.root  hEnumu_cv /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_BNBFlux/G2018/ origin/master


	# DUNE

. ../submit_genie_em_G00_00a_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G00_00a_40Ar_DUNEFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G00_00a_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_G00_00a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC-dune-ND-file.root numu_flux /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_DUNEFlux/G00_00a/ origin/master

. ../submit_genie_em_G18_02a_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G18_02a_40Ar_DUNEFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G18_02a_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_G18_02a_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC-dune-ND-file.root numu_flux /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_DUNEFlux/G18_02a/ origin/master

. ../submit_genie_em_SuSav2_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_SuSav2_40Ar_DUNEFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC-dune-ND-file.root numu_flux /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_DUNEFlux/SuSav2/ origin/master

. ../submit_genie_em_G2018_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.sh 50 apapadop_G2018_40Ar_DUNEFlux_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_40Ar_DUNEFlux_Q2_0_02_NoRad_eGENIE.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/argon40_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/persistent/users/apapadop/Grid/FHC-dune-ND-file.root numu_flux /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_DUNEFlux/G2018/ origin/master


###################################################################################################################################################################
###################################################################################################################################################################

# SuSav2 # Fixed energy and angle

. ../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_0_24_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_12C_0_24_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_0_24_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_0_24GeV/SuSav2/ origin/master

. ../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_0_56_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_12C_0_56_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_0_56_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_0_56GeV/SuSav2/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_0_961_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_12C_0_961_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_0_961_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_0_961GeV/SuSav2/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_1_299_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_12C_1_299_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_1_299_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_299GeV/SuSav2/ origin/master



. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_2_222_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_12C_2_222_NoRad_Q2_0_1 /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_2_222_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_2_222GeV/SuSav2/ origin/master_Q2_0_1

. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_3_595_Q2_0_02_NoRad_eGENIE.sh 600 apapadop_SuSav2_12C_3_595_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_3_595_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_3_595GeV/SuSav2/ origin/master_Q2_0_1

. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_12C_1_501_Q2_0_1_NoRad_eGENIE.sh 300 apapadop_SuSav2_12C_1_501_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_1_501_Q2_0_1_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_501GeV/SuSav2/ origin/master_Q2_0_1



. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_40Ar_2_222_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_40Ar_2_222_NoRad_Q2_0_1 /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_40Ar_2_222_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/argon40_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_2_222GeV/SuSav2/ origin/master_Q2_0_1




. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_56Fe_0_56_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_56Fe_0_56_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_0_56_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/56Fe_0_56GeV/SuSav2/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_56Fe_0_961_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_56Fe_0_961_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_0_961_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/56Fe_0_961GeV/SuSav2/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_SuSav2_56Fe_1_299_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_SuSav2_56Fe_1_299_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_1_299_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/56Fe_1_299GeV/SuSav2/ origin/master



# G2018 # Fixed energy and angle

. ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_0_24_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_12C_0_24_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_0_24_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_0_24GeV/G2018/ origin/master

 . ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_0_56_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_12C_0_56_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_0_56_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_0_56GeV/G2018/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_0_961_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_12C_0_961_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_0_961_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_0_961GeV/G2018/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_1_299_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_12C_1_299_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_1_299_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_299GeV/G2018/ origin/master




. ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_2_222_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_12C_2_222_NoRad_Q2_0_1 /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_2_222_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_2_222GeV/G2018/ origin/master_Q2_0_1

. ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_3_595_Q2_0_02_NoRad_eGENIE.sh 600 apapadop_G2018_12C_3_595_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_3_595_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_3_595GeV/G2018/ origin/master_Q2_0_1

. ../../GridJobs/eGENIE/submit_genie_em_G2018_12C_1_501_Q2_0_1_NoRad_eGENIE.sh 300 apapadop_G2018_12C_1_501_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_1_501_Q2_0_1_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_501GeV/G2018/ origin/master_Q2_0_1





. ../../GridJobs/eGENIE/submit_genie_em_G2018_40Ar_2_222_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_40Ar_2_222_NoRad_Q2_0_1 /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_40Ar_2_222_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/argon40_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/40Ar_2_222GeV/G2018/ origin/master_Q2_0_1




. ../../GridJobs/eGENIE/submit_genie_em_G2018_56Fe_0_56_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_56Fe_0_56_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_0_56_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/56Fe_0_56GeV/G2018/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_G2018_56Fe_0_961_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_56Fe_0_961_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_0_961_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/56Fe_0_961GeV/G2018/ origin/master

. ../../GridJobs/eGENIE/submit_genie_em_G2018_56Fe_1_299_Q2_0_02_NoRad_eGENIE.sh 300 apapadop_G2018_56Fe_1_299_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_1_299_Q2_0_02_NoRad_eGENIE.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/56Fe_1_299GeV/G2018/ origin/master

