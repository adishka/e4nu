
# Splines to be produced with every new GENIE release

declare -a Tunes=("GTEST19_10b_00_000" "G18_10a_02_11a" "G18_02a_00_000" "G00_00a_00_000")
declare -a Nuclei=("1H" "2H" "3He" "4He" "12C" "16O" "40Ar" "56Fe" "208Pb")

#declare -a Tunes=("G00_00a_00_000")
#declare -a Nuclei=("12C")

#maybe add
#"GTEST18_02c_00_000" #INCL++ "GTEST18_02d_00_000" #G4Bertini

#export GenieRelease=v3_0_6_WithSuSav2
export GenieRelease=v3_2



###############################################################################################################################################################################################

for nucleus in "${Nuclei[@]}"; 

	do

	echo ""

	for tune in "${Tunes[@]}"; 

		do

		./em_submit_splines_${tune}_${nucleus}.sh em_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

		./cc_submit_splines_${tune}_${nucleus}.sh cc_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/cc_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

		./em_submit_splines_${tune}_${nucleus}.sh em_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_02/${GenieRelease}/ origin/master_Q2_0_02

		./cc_submit_splines_${tune}_${nucleus}.sh cc_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/cc_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_02/${GenieRelease}/ origin/master_Q2_0_02

		./em_submit_splines_${tune}_${nucleus}.sh em_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

		./cc_submit_splines_${tune}_${nucleus}.sh cc_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/cc_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

		./em_submit_splines_${tune}_${nucleus}.sh cc_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4

		./cc_submit_splines_${tune}_${nucleus}.sh cc_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/cc_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4

		./em_submit_splines_${tune}_${nucleus}.sh em_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8

		./cc_submit_splines_${tune}_${nucleus}.sh cc_apapadop_${tune}_${nucleus} /pnfs/genie/persistent/users/apapadop/Grid/cc_args_spline_${tune}_${nucleus}.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8

		done

	done
	echo ""

###############################################################################################################################################################################################

# Splines for Pilar (nu_e / nu_tau / anti_nu_mu / anti_nu_e / anti_nu_tau x G2018/SuSav2) # nu_mu has been produced above

./cc_nu_mu_submit_splines_G18_10a_02_11a_12C.sh cc_nu_mu_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_nu_mu_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_nu_e_submit_splines_G18_10a_02_11a_12C.sh cc_nu_e_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_nu_e_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_nu_tau_submit_splines_G18_10a_02_11a_12C.sh cc_nu_tau_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_nu_tau_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_anti_nu_e_submit_splines_G18_10a_02_11a_12C.sh cc_anti_nu_e_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_anti_nu_e_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_anti_nu_mu_submit_splines_G18_10a_02_11a_12C.sh cc_anti_nu_mu_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_anti_nu_mu_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_anti_nu_tau_submit_splines_G18_10a_02_11a_12C.sh cc_anti_nu_tau_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_anti_nu_tau_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master


./cc_nu_mu_submit_splines_GTEST19_10b_00_000_12C.sh cc_nu_mu_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_nu_mu_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_nu_e_submit_splines_GTEST19_10b_00_000_12C.sh cc_nu_e_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_nu_e_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_nu_tau_submit_splines_GTEST19_10b_00_000_12C.sh cc_nu_tau_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_nu_tau_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_anti_nu_e_submit_splines_GTEST19_10b_00_000_12C.sh cc_anti_nu_e_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_anti_nu_e_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_anti_nu_mu_submit_splines_GTEST19_10b_00_000_12C.sh cc_anti_nu_mu_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_anti_nu_mu_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

./cc_anti_nu_tau_submit_splines_GTEST19_10b_00_000_12C.sh cc_anti_nu_tau_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/cc_anti_nu_tau_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master


###############################################################################################################################################################################################

# New FSI models from Robert Hatcher // Q2 > 0.4 @ E = 2.2 GeV

./em_submit_splines_GTEST18_02d_00_000_12C.sh cc_apapadop_GTEST18_02d_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_GTEST18_02d_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4

./em_submit_splines_GTEST18_02d_00_000_12C.sh cc_apapadop_GTEST18_02d_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_GTEST18_02d_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4

###############################################################################################################################################################################################

# default & NC nu mu (CC + NC nu mu) Q2 > 0.1

./default_nu_mu_submit_splines_G18_10a_02_11a_12C.sh default_nu_mu_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/default_nu_mu_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

./default_nu_mu_submit_splines_GTEST19_10b_00_000_12C.sh default_nu_mu_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/default_nu_mu_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

./nc_nu_mu_submit_splines_G18_10a_02_11a_12C.sh nc_nu_mu_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/nc_nu_mu_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

./nc_nu_mu_submit_splines_GTEST19_10b_00_000_12C.sh nc_nu_mu_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/nc_nu_mu_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

./ncmec_nu_mu_submit_splines_G18_10a_02_11a_12C.sh ncmec_nu_mu_apapadop_G18_10a_02_11a_12C /pnfs/genie/persistent/users/apapadop/Grid/ncmec_nu_mu_args_spline_G18_10a_02_11a_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

./ncmec_nu_mu_submit_splines_GTEST19_10b_00_000_12C.sh ncmec_nu_mu_apapadop_GTEST19_10b_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/ncmec_nu_mu_args_spline_GTEST19_10b_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1
