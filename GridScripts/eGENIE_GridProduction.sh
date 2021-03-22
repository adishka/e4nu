#export GenieRelease=v3_00_06_WithSuSav2
export GenieRelease=v3_2

export SplinePath=/pnfs/genie/persistent/users/apapadop/mySplines
export ScratchPath=/pnfs/genie/scratch/users/apapadop

###################################################################################################################################################################

# FSI Study

declare -a TunesFSI=("GTEST19_10b_00_000" "G18_10a_02_11a" "G18_10b_02_11a")
declare -a NucleiFSI=("1000060120")

export JobsFSI=1000

#for tune in "${TunesFSI[@]}"; 

#	do

#	echo ""

#	for nucleus in "${NucleiFSI[@]}"; 

#		do

#		# Electrons & Default (CC + NC) Neutrinos w/ FSI @ 1.161 GeV

#		./submit_samples.sh ${JobsFSI} apapadop_${tune}_${nucleus}_1161_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/${nucleus}_1_161GeV/${tune}/ origin/master_Q2_0_1 1.161 11 ${nucleus} ${tune} EM

#		./submit_samples.sh ${JobsFSI} apapadop_${tune}_${nucleus}_1161_nuGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/14_${nucleus}_Default_${tune}_Q2_0_1.xml ${ScratchPath}/nuGENIE_grid/${nucleus}_1_161GeV/${tune}/ origin/master_Q2_0_1 1.161 14 ${nucleus} ${tune} Default

#		# Electrons & Default (CC + NC) Neutrinos w/o FSI @ 1.161 GeV

#		./submit_samples.sh ${JobsFSI} apapadop_${tune}_${nucleus}_1161_eGENIE_NoFSI ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_${nucleus}_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/${nucleus}_1_161GeV/${tune}_NoFSI/ origin/master_Q2_0_1_NoFSI 1.161 11 ${nucleus} ${tune} EM

#		./submit_samples.sh ${JobsFSI} apapadop_${tune}_${nucleus}_1161_nuGENIE_NoFSI ${SplinePath}/master_Q2_0_1/${GenieRelease}/14_${nucleus}_Default_${tune}_Q2_0_1.xml ${ScratchPath}/nuGENIE_grid/${nucleus}_1_161GeV/${tune}_NoFSI/ origin/master_Q2_0_1_NoFSI 1.161 14 ${nucleus} ${tune} Default

#		done

#	done
#	echo ""


#./submit_samples.sh ${JobsFSI} apapadop_GTEST19_10a_00_000_1000060120_1161_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_GTEST19_10a_00_000_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000060120_1_161GeV/GTEST19_10a_00_000/ origin/devel_Q2_0_1_GTEST19_10a 1.161 11 1000060120 GTEST19_10a_00_000 EM

#./submit_samples.sh ${JobsFSI} apapadop_GTEST19_10a_00_000_1000060120_1161_eGENIE_NoFSI ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_GTEST19_10a_00_000_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000060120_1_161GeV/GTEST19_10a_00_000_NoFSI/ origin/devel_Q2_0_1_GTEST19_10a_NoFSI 1.161 11 1000060120 GTEST19_10a_00_000 EM

#./submit_samples.sh ${JobsFSI} apapadop_GTEST19_10a_00_000_1000060120_1161_nuGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/14_1000060120_Default_GTEST19_10a_00_000_Q2_0_1.xml ${ScratchPath}/nuGENIE_grid/1000060120_1_161GeV/GTEST19_10a_00_000/ origin/devel_Q2_0_1_GTEST19_10a 1.161 14 1000060120 GTEST19_10a_00_000 Default

#./submit_samples.sh ${JobsFSI} apapadop_GTEST19_10a_00_000_1000060120_1161_nuGENIE_NoFSI ${SplinePath}/master_Q2_0_1/${GenieRelease}/14_1000060120_Default_GTEST19_10a_00_000_Q2_0_1.xml ${ScratchPath}/nuGENIE_grid/1000060120_1_161GeV/GTEST19_10a_00_000_NoFSI/ origin/devel_Q2_0_1_GTEST19_10a_NoFSI 1.161 14 1000060120 GTEST19_10a_00_000 Default


###################################################################################################################################################################

# Neutrino & Electron Flux Studies

declare -a TunesFlux=("GTEST19_10b_00_000" "G18_10a_02_11a" "G18_02a_00_000")

export JobsFlux=200
export PathFluxFile=/pnfs/genie/persistent/users/apapadop/Grid

#for tune in "${TunesFlux[@]}"; 

#	do

#	echo ""

#		# Neutrinos Q2 > 0

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000180400_BNB_nuGENIE ${SplinePath}/master/${GenieRelease}/14_1000180400_Default_${tune}.xml ${ScratchPath}/nuGENIE_grid/1000180400_BNBFlux/${tune}/ origin/master 3 14 1000180400 ${tune} CC ${PathFluxFile}/MCC9_FluxHist_volTPCActive.root hEnumu_cv

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000180400_DUNE_nuGENIE ${SplinePath}/master/${GenieRelease}/14_1000180400_Default_${tune}.xml ${ScratchPath}/nuGENIE_grid/1000180400_DUNEFlux/${tune}/ origin/master 6 14 1000180400 ${tune} CC ${PathFluxFile}/FHC-dune-ND-file.root numu_flux

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000070130_T2K_nuGENIE ${SplinePath}/master/${GenieRelease}/14_1000070130_Default_${tune}.xml ${ScratchPath}/nuGENIE_grid/1000070130_T2KFlux/${tune}/ origin/master 6 14 1000070130 ${tune} CC ${PathFluxFile}/t2kflux_2016_plus250kA.root enu_nd280_numu

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000080140_NOvA_nuGENIE ${SplinePath}/master/${GenieRelease}/14_1000070130_Default_${tune}.xml ${ScratchPath}/nuGENIE_grid/1000080140_NOvAFlux/${tune}/ origin/master 5 14 1000080140 ${tune} CC ${PathFluxFile}/FHC_Flux_NOvA_ND_2017.root flux_numu

#		# Electrons Q2 > 0.02

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000180400_BNB_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000180400_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000180400_BNBFlux/${tune}/ origin/master 3 11 1000180400 ${tune} EM ${PathFluxFile}/MCC9_FluxHist_volTPCActive.root hEnumu_cv

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000180400_DUNE_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000180400_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000180400_DUNEFlux/${tune}/ origin/master 6 11 1000180400 ${tune} EM ${PathFluxFile}/FHC-dune-ND-file.root numu_flux

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000070130_T2K_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000070130_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000070130_T2KFlux/${tune}/ origin/master 6 11 1000070130 ${tune} EM ${PathFluxFile}/t2kflux_2016_plus250kA.root enu_nd280_numu

#		./submit_flux_samples.sh ${JobsFlux} apapadop_${tune}_1000080140_NOvA_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000070130_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000080140_NOvAFlux/${tune}/ origin/master 5 11 1000080140 ${tune} EM ${PathFluxFile}/FHC_Flux_NOvA_ND_2017.root flux_numu

#	done 


###################################################################################################################################################################

# Monoenergetic inclusive electron studies at fixed angles

declare -a TunesFixAngle=("GTEST19_10b_00_000" "G18_10a_02_11a")

export JobsFixAngle=200

#for tune in "${TunesFixAngle[@]}"; 

#	do
#	echo ""

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_0_24GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_0_24GeV/${tune}/ origin/master 0.24 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_0_56GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_0_56GeV/${tune}/ origin/master 0.56 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_0_519GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_0_519GeV/${tune}/ origin/master 0.519 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_0_62GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_0_620GeV/${tune}/ origin/master 0.62 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_0_56GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_0_680GeV/${tune}/ origin/master 0.68 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_0_961GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_0_961GeV/${tune}/ origin/master 0.961 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_1_299GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000060120_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000060120_1_299GeV/${tune}/ origin/master 1.299 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_1_501GeV_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000060120_1_501GeV/${tune}/ origin/master_Q2_0_1 1.501 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_2_222GeV_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000060120_2_222GeV/${tune}/ origin/master_Q2_0_1 2.222 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_3_595GeV_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000060120_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000060120_3_595GeV/${tune}/ origin/master_Q2_0_1 3.595 11 1000060120 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000060120_5_766GeV_eGENIE ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_1000060120_EM_${tune}_Q2_0_8.xml ${ScratchPath}/eGENIE_grid/1000060120_5_766GeV/${tune}/ origin/master_Q2_0_8 5.766 11 1000060120 ${tune} EM



#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000180400_2_222GeV_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000180400_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000180400_2_222GeV/${tune}/ origin/master_Q2_0_1 2.222 11 1000180400 ${tune} EM



#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000130270_2_222GeV_eGENIE ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_1000130270_EM_${tune}_Q2_0_4.xml ${ScratchPath}/eGENIE_grid/1000130270_2_222GeV/${tune}/ origin/master_Q2_0_4 2.222 11 1000130270 ${tune} EM



#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000220480_2_222GeV_eGENIE ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_1000220480_EM_${tune}_Q2_0_4.xml ${ScratchPath}/eGENIE_grid/1000220480_2_222GeV/${tune}/ origin/master_Q2_0_4 2.222 11 1000220480 ${tune} EM



#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000260560_0_56GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000260560_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000260560_0_56GeV/${tune}/ origin/master 0.56 11 1000260560 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000260560_0_961GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000260560_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000260560_0_961GeV/${tune}/ origin/master 0.961 11 1000260560 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000260560_1_299GeV_eGENIE ${SplinePath}/master/${GenieRelease}/11_1000260560_EM_${tune}.xml ${ScratchPath}/eGENIE_grid/1000260560_1_299GeV/${tune}/ origin/master 1.299 11 1000260560 ${tune} EM


#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000010010_5_500GeV_eGENIE ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_1000010010_EM_${tune}_Q2_0_8.xml ${ScratchPath}/eGENIE_grid/1000010010_5_500GeV/${tune}/ origin/master_Q2_0_8 5.5 11 1000010010 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000010010_3_245GeV_eGENIE ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_1000010010_EM_${tune}_Q2_0_4.xml ${ScratchPath}/eGENIE_grid/1000010010_3_245GeV/${tune}/ origin/master_Q2_0_4 3.245 11 1000010010 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000010010_2_445GeV_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000010010_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000010010_2_445GeV/${tune}/ origin/master_Q2_0_1 2.445 11 1000010010 ${tune} EM


#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000010020_5_500GeV_eGENIE ${SplinePath}/master_Q2_0_8/${GenieRelease}/11_1000010020_EM_${tune}_Q2_0_8.xml ${ScratchPath}/eGENIE_grid/1000010020_5_500GeV/${tune}/ origin/master_Q2_0_8 5.5 11 1000010020 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000010020_3_245GeV_eGENIE ${SplinePath}/master_Q2_0_4/${GenieRelease}/11_1000010020_EM_${tune}_Q2_0_4.xml ${ScratchPath}/eGENIE_grid/1000010020_3_245GeV/${tune}/ origin/master_Q2_0_4 3.245 11 1000010020 ${tune} EM

#		./submit_samples.sh ${JobsFixAngle} apapadop_${tune}_1000010020_2_445GeV_eGENIE ${SplinePath}/master_Q2_0_1/${GenieRelease}/11_1000010020_EM_${tune}_Q2_0_1.xml ${ScratchPath}/eGENIE_grid/1000010020_2_445GeV/${tune}/ origin/master_Q2_0_1 2.445 11 1000010020 ${tune} EM


#	done
#	echo ""

###################################################################################################################################################################

