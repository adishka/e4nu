export SplinePath=/pnfs/genie/persistent/users/apapadop/mySplines
export ScratchPath=/pnfs/genie/scratch/users/apapadop
 
#export GenieRelease=v3_00_06_WithSuSav2
export GenieRelease=v3_2

export NJOBS=700

# NEED TO CHANGE PROCESSES TO EM INSTEAD OF EM+MEC

# ./submit_samples.sh 4 test_apapadop_GTEST19_10b_EM_1GeV /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/v3_2/save/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/eGENIE_grid/12C_1_161GeV/SuSav2/ origin/master_Q2_0_1 1.161 11 1000060120 GTEST19_10b_00_000 EM

###############################################################################################################################################################################################

declare -a Tunes=("GTEST19_10b_00_000" "G18_10a_02_11a")
declare -a Nuclei=("1000020040" "1000060120" "1000260560")

for tune in "${Tunes[@]}"; 

	do

	echo ""

	for nucleus in "${Nuclei[@]}"; 

		do

		# No Rad

		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_2261_NoRad ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_4.xml ${ScratchPath}/grid/NoRad/${nucleus}_2261GeV/${tune}/ origin/master_Q2_0_4 2.261 11 ${nucleus} ${tune} EM

		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_4461_NoRad ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_8.xml ${ScratchPath}/grid/NoRad/${nucleus}_4461GeV/${tune}/ origin/master_Q2_0_8 4.461 11 ${nucleus} ${tune} EM

		# Rad

		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_2261_Rad ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_4.xml ${ScratchPath}/grid/Rad/${nucleus}_2261GeV/${tune}/ origin/adi_radcorr_Q2_0_4 2.261 11 ${nucleus} ${tune} EM

		./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_4461_Rad ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_8.xml ${ScratchPath}/grid/Rad/${nucleus}_4461GeV/${tune}/ origin/adi_radcorr_Q2_0_8 4.461 11 ${nucleus} ${tune} EM

		done

	done
	echo ""

	# No Rad
	
	./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_1161_NoRad SplinePath/master_Q2_0_1/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_1.xml ${ScratchPath}/grid/NoRad/${nucleus}_1161GeV/${tune}/ origin/master_Q2_0_1 1.161 11 ${nucleus} ${tune} EM

	# Rad
	
	./submit_samples.sh ${NJOBS} apapadop_${tune}_${nucleus}_1161_Rad SplinePath/master_Q2_0_1/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_1.xml ${ScratchPath}/grid/Rad/${nucleus}_1161GeV/${tune}/ origin/adi_radcorr_Q2_0_1 1.161 11 ${nucleus} ${tune} EM


###############################################################################################################################################################################################

# Rad

	# SuSav2

#. ../GridJobs/e4v/submit_genie_em_SuSav2_12C_1_161_Q2_0_1_Rad.sh 500 apapadop_SuSav2_C12_1_161_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_1_161_Q2_0_1_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/C12_1161GeV/SuSav2/ origin/adi_radcorr_Q2_0_1;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_12C_2_261_Q2_0_4_Rad.sh 500 apapadop_SuSav2_C12_2_261_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_2_261_Q2_0_4_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/C12_2261GeV/SuSav2/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_12C_4_461_Q2_0_8_Rad.sh 500 apapadop_SuSav2_C12_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_4_461_Q2_0_8_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/C12_4461GeV/SuSav2/ origin/adi_radcorr_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_56Fe_2_261_Q2_0_4_Rad.sh 500 apapadop_SuSav2_56Fe_2_261_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_2_261_Q2_0_4_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/56Fe_2261GeV/SuSav2/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_56Fe_4_461_Q2_0_8_Rad.sh 500 apapadop_SuSav2_56Fe_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_4_461_Q2_0_8_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/56Fe_4461GeV/SuSav2/ origin/adi_radcorr_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_4He_2_261_Q2_0_4_Rad.sh 500 apapadop_SuSav2_4He_2_261_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_4He_2_261_Q2_0_4_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/helium4_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/4He_2261GeV/SuSav2/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_4He_4_461_Q2_0_8_Rad.sh 500 apapadop_SuSav2_4He_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_4He_4_461_Q2_0_8_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/helium4_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/4He_4461GeV/SuSav2/ origin/adi_radcorr_Q2_0_8;


	# G2018

#. ../GridJobs/e4v/submit_genie_em_G2018_12C_1_161_Q2_0_1_Rad.sh 500 apapadop_G2018_C12_1_161_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_1_161_Q2_0_1_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/C12_1161GeV/G2018/ origin/adi_radcorr_Q2_0_1;

#. ../GridJobs/e4v/submit_genie_em_G2018_12C_2_261_Q2_0_4_Rad.sh 500 apapadop_G2018_C12_2_261_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_2_261_Q2_0_4_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/C12_2261GeV/G2018/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_G2018_12C_4_461_Q2_0_8_Rad.sh 500 apapadop_G2018_C12_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_4_461_Q2_0_8_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/C12_4461GeV/G2018/ origin/adi_radcorr_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_G2018_56Fe_2_261_Q2_0_4_Rad.sh 500 apapadop_G2018_56Fe_2_261_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_2_261_Q2_0_4_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/56Fe_2261GeV/G2018/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_G2018_56Fe_4_461_Q2_0_8_Rad.sh 500 apapadop_G2018_56Fe_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_4_461_Q2_0_8_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/56Fe_4461GeV/G2018/ origin/adi_radcorr_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_G2018_4He_2_261_Q2_0_4_Rad.sh 500 apapadop_G2018_4He_2_261_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_4He_2_261_Q2_0_4_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/helium4_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/4He_2261GeV/G2018/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_G2018_4He_4_461_Q2_0_8_Rad.sh 500 apapadop_G2018_4He_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_4He_4_461_Q2_0_8_Rad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/helium4_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/Rad/4He_4461GeV/G2018/ origin/adi_radcorr_Q2_0_8;



# NoRad

	# SuSav2

#. ../GridJobs/e4v/submit_genie_em_SuSav2_12C_1_161_Q2_0_1_NoRad.sh 500 apapadop_SuSav2_C12_1_161_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_1_161_Q2_0_1_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/C12_1161GeV/SuSav2/ origin/master_Q2_0_1;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_12C_2_261_Q2_0_4_NoRad.sh 500 apapadop_SuSav2_C12_2_261_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_2_261_Q2_0_4_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/C12_2261GeV/SuSav2/ origin/master_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_12C_4_461_Q2_0_8_NoRad.sh 500 apapadop_SuSav2_C12_4_461_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_12C_4_461_Q2_0_8_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/carbon12_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/C12_4461GeV/SuSav2/ origin/master_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_56Fe_2_261_Q2_0_4_NoRad.sh 500 apapadop_SuSav2_56Fe_2_261_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_2_261_Q2_0_4_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/56Fe_2261GeV/SuSav2/ origin/master_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_56Fe_4_461_Q2_0_8_NoRad.sh 500 apapadop_SuSav2_56Fe_4_461_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_56Fe_4_461_Q2_0_8_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/iron56_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/56Fe_4461GeV/SuSav2/ origin/master_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_4He_2_261_Q2_0_4_NoRad.sh 500 apapadop_SuSav2_4He_2_261_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_4He_2_261_Q2_0_4_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/helium4_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/4He_2261GeV/SuSav2/ origin/master_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_SuSav2_4He_4_461_Q2_0_8_NoRad.sh 500 apapadop_SuSav2_4He_4_461_Rad /pnfs/genie/persistent/users/apapadop/Grid/args_em_SuSav2_4He_4_461_Q2_0_8_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/helium4_spline_EMPlusMEC_GTEST19_10b_00_000_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/4He_4461GeV/SuSav2/ origin/master_Q2_0_8;

	# G2018

#. ../GridJobs/e4v/submit_genie_em_G2018_12C_1_161_Q2_0_1_NoRad.sh 500 apapadop_G2018_C12_1_161_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_1_161_Q2_0_1_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_1/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_1.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/C12_1161GeV/G2018/ origin/master_Q2_0_1;

#. ../GridJobs/e4v/submit_genie_em_G2018_12C_2_261_Q2_0_4_NoRad.sh 500 apapadop_G2018_C12_2_261_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_2_261_Q2_0_4_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/C12_2261GeV/G2018/ origin/master_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_G2018_12C_4_461_Q2_0_8_NoRad.sh 500 apapadop_G2018_C12_4_461_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_12C_4_461_Q2_0_8_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/carbon12_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/C12_4461GeV/G2018/ origin/master_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_G2018_56Fe_2_261_Q2_0_4_NoRad.sh 500 apapadop_G2018_56Fe_2_261_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_2_261_Q2_0_4_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/56Fe_2261GeV/G2018/ origin/master_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_G2018_56Fe_4_461_Q2_0_8_NoRad.sh 500 apapadop_G2018_56Fe_4_461_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_56Fe_4_461_Q2_0_8_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/iron56_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/56Fe_4461GeV/G2018/ origin/master_Q2_0_8;

#. ../GridJobs/e4v/submit_genie_em_G2018_4He_2_261_Q2_0_4_NoRad.sh 500 apapadop_G2018_4He_2_261_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_4He_2_261_Q2_0_4_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_4/${GenieRelease}/helium4_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_4.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/4He_2261GeV/G2018/ origin/adi_radcorr_Q2_0_4;

#. ../GridJobs/e4v/submit_genie_em_G2018_4He_4_461_Q2_0_8_NoRad.sh 500 apapadop_G2018_4He_4_461_NoRad /pnfs/genie/persistent/users/apapadop/Grid/args_em_G2018_4He_4_461_Q2_0_8_NoRad.txt  /pnfs/genie/persistent/users/apapadop/mySplines/master_Q2_0_8/${GenieRelease}/helium4_spline_EMPlusMEC_G18_10a_02_11a_Q2_0_8.xml /pnfs/genie/scratch/users/apapadop/grid/NoRad/4He_4461GeV/G2018/ origin/adi_radcorr_Q2_0_8;

