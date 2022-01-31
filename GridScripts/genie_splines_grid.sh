#!/bin/bash

STEM=$1
GIT_CHECKOUT=$2
PROBE=$3
TARGET=$4
UPPERENERGY=$5
TUNE=$6
EVENTGENLIST=$7

# Create a dummy file in the output directory. This is a hack to get jobs
# that fail to end themselves quickly rather than hanging on for a long time
# waiting for output to arrive.
DUMMY_OUTPUT_FILE=${CONDOR_DIR_OUTPUT}/${JOBSUBJOBID}_${STEM}_dummy_output
touch ${DUMMY_OUTPUT_FILE}

# Get the source code for GENIE v3
cd $CONDOR_DIR_INPUT
#source /cvmfs/fermilab.opensciencegrid.org/products/larsoft/setups
source /cvmfs/fermilab.opensciencegrid.org/products/genie/bootstrap_genie_ups.sh
setup git v2_15_1
#git clone https://github.com/GENIE-MC/Generator.git genie-build
git clone https://github.com/afropapp13/Generator.git genie-build

# Set up GENIE environment
setup root v6_12_04e -q e15:prof
setup lhapdf v5_9_1k -q e15:prof
setup pdfsets v5_9_1b
setup log4cpp v1_1_3a -q e15:prof

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

### Check out specified branch, tag, or commit on a temporary
### local branch
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

# Integrate splines
cd ${CONDOR_DIR_INPUT}
printf -v PADDED_PROCESS "%05d" $PROCESS
Replace="origin/master"
extra="${GIT_CHECKOUT//${Replace}/}"
output_file_stem="${CONDOR_DIR_OUTPUT}/${PROBE}_${TARGET}_${EVENTGENLIST}_${TUNE}${extra}"
echo hello apapadop 
echo Tune ${TUNE} 
echo Eventgenlist ${EVENTGENLIST} 
echo stem ${STEM}
echo gitcheckout ${GIT_CHECKOUT}
echo probe ${PROBE} 
echo target ${TARGET} 
echo upperenergy ${UPPERENERGY}
gmkspl -p ${PROBE} -t ${TARGET} -e ${UPPERENERGY} --tune ${TUNE} --event-generator-list ${EVENTGENLIST} --seed ${myseed} -o ${output_file_stem}.xml
