
# Splines to be produced with every new GENIE release

declare -a Tunes=("GTEST19_10b_00_000" "G18_10a_02_11a" "G18_02a_00_000" "G00_00a_00_000")
declare -a Nuclei=("1H" "2H" "3He" "4He" "12C" "16O" "56Fe" "208Pb")

#declare -a Tunes=("G00_00a_00_000")
#declare -a Nuclei=("12C")

#export GenieRelease=v3_0_6_WithSuSav2
export GenieRelease=v3_2



###############################################################################################################################################################################################

for nucleus in "${Nuclei[@]}"; 

	do

	echo ""

	for tune in "${Tunes[@]}"; 

		do

		./em_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

		./cc_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master/${GenieRelease}/ origin/master

		./em_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_02/${GenieRelease}/ origin/master_Q2_0_02

		./cc_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_02/${GenieRelease}/ origin/master_Q2_0_02

		./em_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

		./cc_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1

		./em_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4

		./cc_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4

		./em_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8

		./cc_submit_splines_${tune}_12C.sh em_apapadop_${tune}_12C /pnfs/genie/persistent/users/apapadop/Grid/em_args_spline_${tune}_12C.txt /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8

		done

	done
	echo ""
