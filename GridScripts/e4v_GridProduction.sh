export SplinePath=/pnfs/genie/persistent/users/apapadop/mySplines
export ScratchPath=/pnfs/genie/scratch/users/apapadop
 
#export GenieRelease=v3_00_06_WithSuSav2
export GenieRelease=v3_2

export NJOBS=700

###############################################################################################################################################################################################

declare -a Tunes=("GTEST19_10b_00_000" "G18_10a_02_11a")
declare -a Nuclei=("1000020040" "1000060120" "1000260560")

#for tune in "${Tunes[@]}"; 

#	do

#	echo ""

#	for nucleus in "${Nuclei[@]}"; 

#		do

#		# No Rad

#		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_2261_NoRad ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_4.xml ${ScratchPath}/grid/NoRad/${nucleus}_2261GeV/${tune}/ origin/master_Q2_0_4 2.261 11 ${nucleus} ${tune} EM

#		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_4461_NoRad ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_8.xml ${ScratchPath}/grid/NoRad/${nucleus}_4461GeV/${tune}/ origin/master_Q2_0_8 4.461 11 ${nucleus} ${tune} EM

#		# Rad

#		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_2261_Rad ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_4.xml ${ScratchPath}/grid/Rad/${nucleus}_2261GeV/${tune}/ origin/adi_radcorr_Q2_0_4 2.261 11 ${nucleus} ${tune} EM

#		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_4461_Rad ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_8.xml ${ScratchPath}/grid/Rad/${nucleus}_4461GeV/${tune}/ origin/adi_radcorr_Q2_0_8 4.461 11 ${nucleus} ${tune} EM

#		done

#	# No Rad
#	
#	./submit_samples.sh ${NJOBS} apapadop_${tune}_1000060120_1161_NoRad ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_${tune}_Q2_0_1.xml ${ScratchPath}/grid/NoRad/1000060120_1161GeV/${tune}/ origin/master_Q2_0_1 1.161 11 1000060120 ${tune} EM

#	# Rad
#	
#	./submit_samples.sh ${NJOBS} apapadop_${tune}_1000060120_1161_Rad ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_${tune}_Q2_0_1.xml ${ScratchPath}/grid/Rad/1000060120_1161GeV/${tune}/ origin/adi_radcorr_Q2_0_1 1.161 11 1000060120 ${tune} EM

#	done
#	echo ""

###############################################################################################################################################################################################
