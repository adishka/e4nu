# Splines to be produced with every new GENIE release
#maybe add at some point "GTEST18_02c_00_000" #INCL++ "GTEST18_02d_00_000" #G4Bertini
declare -a Tunes=("GTEST19_10b_00_000" "G18_10a_02_11a" "G18_02a_00_000" "G00_00a_00_000" "G18_10b_02_11a" "G18_01a_00_000","GEM21_11b_00_000")
declare -a Nuclei=("1000010010" "1000010020" "1000020030" "1000020040" "1000060120" "1000080160" "1000130270" "1000180400" "1000200400" "1000220480" "1000260560" "1000822080")

#declare -a Tunes=("G00_00a_00_000")
#declare -a Nuclei=("1000060120")

#export GenieRelease=v3_0_6_WithSuSav2
export GenieRelease=v3_2

export UpperELim=20
export SplinePath=/pnfs/genie/persistent/users/apapadop/mySplines

###############################################################################################################################################################################################

for nucleus in "${Nuclei[@]}"; 

	do

	echo ""

	for tune in "${Tunes[@]}"; 

		do

		# EM

		./submit_splines.sh apapadop_${tune}_${nucleus}_EM ${SplinePath}/master/${GenieRelease}/ origin/master 11 ${nucleus} ${UpperELim} ${tune} EM
		./submit_splines.sh apapadop_${tune}_${nucleus}_EM ${SplinePath}/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1 11 ${nucleus} ${UpperELim} ${tune} EM
		./submit_splines.sh apapadop_${tune}_${nucleus}_EM ${SplinePath}/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4 11 ${nucleus} ${UpperELim} ${tune} EM
		./submit_splines.sh apapadop_${tune}_${nucleus}_EM ${SplinePath}/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8 11 ${nucleus} ${UpperELim} ${tune} EM

		# Default

		./submit_splines.sh apapadop_${tune}_${nucleus}_Default ${SplinePath}/master/${GenieRelease}/ origin/master 14 ${nucleus} ${UpperELim} ${tune} Default
		./submit_splines.sh apapadop_${tune}_${nucleus}_Default ${SplinePath}/master_Q2_0_02/${GenieRelease}/ origin/master_Q2_0_02 14 ${nucleus} ${UpperELim} ${tune} Default
		./submit_splines.sh apapadop_${tune}_${nucleus}_Default ${SplinePath}/master_Q2_0_1/${GenieRelease}/ origin/master_Q2_0_1 14 ${nucleus} ${UpperELim} ${tune} Default
		./submit_splines.sh apapadop_${tune}_${nucleus}_Default ${SplinePath}/master_Q2_0_4/${GenieRelease}/ origin/master_Q2_0_4 14 ${nucleus} ${UpperELim} ${tune} Default
		./submit_splines.sh apapadop_${tune}_${nucleus}_Default ${SplinePath}/master_Q2_0_8/${GenieRelease}/ origin/master_Q2_0_8 14 ${nucleus} ${UpperELim} ${tune} Default


		done

	./submit_splines.sh apapadop_GTEST19_10a_00_000_${nucleus}_Default ${SplinePath}/master_Q2_0_1/${GenieRelease}/ origin/devel_Q2_0_1_GTEST19_10a 14 ${nucleus} ${UpperELim} GTEST19_10a_00_000 Default
	./submit_splines.sh apapadop_GTEST19_10a_00_000_${nucleus}_EM ${SplinePath}/master_Q2_0_1/${GenieRelease}/ origin/devel_Q2_0_1_GTEST19_10a 11 ${nucleus} ${UpperELim} GTEST19_10a_00_000 EM

	done
	echo ""

###############################################################################################################################################################################################
