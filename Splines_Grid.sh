
# Splines to be produced with every new GENIE release

#declare -a Tunes=("GTEST19_10b_00_000" "G18_10a_02_11a" "G18_02a_00_000" "G00_00a_00_000")
#declare -a Nuclei=("1H" "2H" "3He" "4He" "12C" "16O" "56Fe" "184W" "208Pb")

declare -a Tunes=("G00_00a_00_000")
declare -a Nuclei=("12C")

#export GenieRelease=v3_0_6_WithSuSav2
export GenieRelease=v3_2



###############################################################################################################################################################################################

# master
# Neutrinos: Q2 > 10^-4
# Electrons: Q2 > 0.02

#./submit_splines_G18_10a_02_11a_1H.sh em_apapadop_G18_10a_02_11a_1H /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_G18_10a_02_11a_1H.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

#./submit_splines_G00_00a_00_000_12C.sh em_apapadop_G00_00a_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_G00_00a_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

#./submit_splines_G18_02a_00_000_12C.sh em_apapadop_G18_02a_00_000_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_G18_02a_00_000_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

for nucleus in "${Nuclei[@]}"; 

	do

	echo ""

	for tune in "${Tunes[@]}"; 

		do

		./submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

		done

	done
	echo ""


###############################################################################################################################################################################################

# master_Q2_0_02
# Neutrinos: Q2 > 0.02
# Electrons: Q2 > 0.02




###############################################################################################################################################################################################

# master_Q2_0_1
# Neutrinos: Q2 > 0.1
# Electrons: Q2 > 0.1


###############################################################################################################################################################################################

# master_Q2_0_4
# Neutrinos: Q2 > 0.4
# Electrons: Q2 > 0.4


###############################################################################################################################################################################################

# master_Q2_0_8
# Neutrinos: Q2 > 0.8
# Electrons: Q2 > 0.8

#./submit_splines_G18_10a_02_11a_16O_Q2_0_8.sh apapadop_G18_10a_02_11a_16O_Q2_0_8 /pnfs/genie/persistent/users/apapadop/Grid/args_spline_G18_10a_02_11a_16O_Q2_0_8.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8 



