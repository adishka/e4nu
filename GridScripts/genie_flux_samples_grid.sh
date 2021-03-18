#!/bin/bash

STEM=$1
SPLINES_FILE=$2
GIT_CHECKOUT=$3
ENERGY=$4
PROBE=$5
TARGET=$6
TUNE=$7
EVENTGENLIST=$8
FLUXFILE=$9
FLUXHISTO=${10}

if (( ${TARGET} == 1000070130 )); then TARGET=1000060120[0.923076],1000010010[0.076924]
if (( ${TARGET} == 1000080140 )); then TARGET=1000060120[0.85714],1000010010[0.14286]

# Create a dummy file in the output directory. This is a hack to get jobs
# that fail to end themselves quickly rather than hanging on for a long time
# waiting for output to arrive.
DUMMY_OUTPUT_FILE=${CONDOR_DIR_OUTPUT}/${JOBSUBJOBID}_${STEM}_dummy_output
touch ${DUMMY_OUTPUT_FILE}

# Get the source code for GENIE v3
cd $CONDOR_DIR_INPUT
source /cvmfs/fermilab.opensciencegrid.org/products/larsoft/setups
setup git v2_15_1

#git clone https://github.com/GENIE-MC/Generator.git genie-build

git clone https://github.com/afropapp13/Generator.git genie-build

#git clone https://github.com/afropapp13/Schwinger_Rad_Corr.git genie-build

#git clone https://github.com/afropapp13/Fork_SuSav2_SG.git genie-build
#git clone http://github.com/apapadop/SuSav2_Fork.git genie-build
#git clone git@github.com:afropapp13/SuSav2_Fork.git genie-build

#git clone https://github.com/sjgardiner/Generator.git genie-build

# Set up GENIE environment
setup root v6_12_04e -q e15:prof
setup lhapdf v5_9_1k -q e15:prof
setup log4cpp v1_1_3a -q e15:prof
setup pdfsets v5_9_1b

echo "Setting GENIE environment variables..."

export GENIEBASE=$(pwd)
export GENIE=$GENIEBASE/genie-build
export PYTHIA6=$PYTHIA_FQ_DIR/lib
# This is handled by the pdfsets ups product
#export LHAPATH=$LHAPDF_FQ_DIR
export LHAPDF5_INC=$LHAPDF_INC
export LHAPDF5_LIB=$LHAPDF_LIB
export LD_LIBRARY_PATH=$GENIE/lib:$LD_LIBRARY_PATH
export PATH=$GENIE/bin:$PATH
unset GENIEBASE

### Check out tagged v3_0_2 release
#cd $GENIE
#git checkout tags/R-3_00_02 -b v3.0.2

# Check out the requested git branch, tag, or commit
cd $GENIE
git checkout -b temp ${GIT_CHECKOUT}

# Configure for the build
./configure \
  --enable-gsl \
  --enable-rwght \
  --with-optimiz-level=O2 \
  --with-log4cpp-inc=${LOG4CPP_INC} \
  --with-log4cpp-lib=${LOG4CPP_LIB} \
  --with-libxml2-inc=${LIBXML2_INC} \
  --with-libxml2-lib=${LIBXML2_LIB} \
  --with-lhapdf5-lib=${LHAPDF_LIB} \
  --with-lhapdf5-inc=${LHAPDF_INC} \
  --with-pythia6-lib=${PYTHIA_LIB}

# Build GENIE
make

# Get a randomly-selected random number seed using bash
myseed=${RANDOM}

echo STEM ${STEM}
echo SPLINES_FILE ${SPLINES_FILE}
echo GIT_CHECKOUT ${GIT_CHECKOUT}
echo ENERGY ${ENERGY}
echo PROBE ${PROBE}
echo TARGET ${TARGET}
echo TUNE ${TUNE}
echo EVENTGENLIST ${EVENTGENLIST}
echo FLUXFILE ${FLUXFILE}
echo FLUXHISTO ${FLUXHISTO}

# Generate some events
cd ${CONDOR_DIR_INPUT}
printf -v PADDED_PROCESS "%05d" $EVENTGENLIST
output_file_stem="${CONDOR_DIR_OUTPUT}/${STEM}_${myseed}_${PADDED_PROCESS}"
gevgen -n 100000 -e 0.,${ENERGY} -p ${PROBE} -t ${TARGET} --tune ${TUNE} --event-generator-list ${EVENTGENLIST} --seed ${myseed} --cross-sections ${SPLINES_FILE} -o ${output_file_stem}.ghep.root -f ${FLUXFILE},${FLUXHISTO} 

# Make a gst-format summary file for easy plotting
gntpc -i ${output_file_stem}.ghep.root -o ${output_file_stem}.gst.root -f gst
