#!/bin/bash
# Script to simplify GENIE job submission to the grid
#
# Afroditi Papadopoulou  <apapadop@fnal.gov>

##### Parse any command-line options passed to this script ######
# This section is based on https://stackoverflow.com/a/29754866/4081973
#
# Currently, the allowed options for invoking this script are
#
# -p, --prod:  Submit jobs with the VOMS Production role (rather than the
#              usual Analysis role). The job will be run on the grid
#              using the anniepro account instead of your normal user
#              account. Job submission will fail unless you have permission
#              to submit production jobs.

# Check for a suitable version of the getopt program (should be installed
# on just about any flavor of Linux these days)
getopt --test > /dev/null
if [[ $? -ne 4 ]]; then
    echo "ERROR: enhanced getopt is not installed on this system."
    exit 1
fi

# Number of expected command-line arguments
NUM_EXPECTED=8

# Define the command-line options accepted by this script
OPTIONS=p:
LONGOPTIONS=prod:

# Parse the command line used to run this script using getopt
PARSED=$(getopt --options=$OPTIONS --longoptions=$LONGOPTIONS --name "$0" -- "$@")

if [[ $? -ne 0 ]]; then
    # getopt has complained about wrong arguments to stdout, so we can quit
    exit 2
fi

# Read getopt’s output this way to handle the quoting right
eval set -- "$PARSED"

# Process the options in order until we see --
while true; do
    case "$1" in
        -p|--prod)
            USE_PRODUCTION="y"
            shift
            ;;
        --)
            shift
            break
            ;;
        *)
            echo "Error encountered while parsing the command-line options!"
            exit 3
            ;;
    esac
done

if [ "$#" -ne "$NUM_EXPECTED" ]; then
  echo "Usage: ./submit_splines.sh [--prod] JOB_NAME OUTPUT_DIRECTORY GIT_CHECKOUT PROBE NUCLEUS UPPERENERGY TUNE EVENTGENLIS"
  exit 1
fi

STEM=$1
OUTPUT_DIRECTORY=$2
GIT_CHECKOUT=$3
PROBE=$4
TARGET=$5
UPPERENERGY=$6
TUNE=$7
EVENTGENLIST=$8

GRID_RESOURCES_DIR=/pnfs/genie/persistent/users/apapadop/Grid/

# Check if the USE_PRODUCTION variable is set
if [ ! -z ${USE_PRODUCTION+x} ]; then
  echo "Production job will run as geniepro"
  PROD_OPTION="--role=Production"
else
  echo "Analysis job will run as $(whoami)"
  PROD_OPTION="--role=Analysis"
fi

source /cvmfs/fermilab.opensciencegrid.org/products/common/etc/setups
setup fife_utils

echo
echo
echo "hello apapadop you are producing splines for" ${TUNE} ${EVENTGENLIST}

jobsub_submit -G genie --expected-lifetime=72h $PROD_OPTION \
  -d OUTPUT $OUTPUT_DIRECTORY \
  --resource-provides=usage_model=DEDICATED,OPPORTUNISTIC,OFFSITE \
  file://${GRID_RESOURCES_DIR}/genie_splines_grid.sh $STEM $GIT_CHECKOUT ${PROBE} ${TARGET} ${UPPERENERGY} ${TUNE} ${EVENTGENLIST}  
