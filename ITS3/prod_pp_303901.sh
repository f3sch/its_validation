#!/bin/bash

# Test setup to run ITS3 with TPC matching in 13.6 TeV at 675 MHz.

# make sure O2DPG + O2 is loaded
[ ! "${O2DPG_ROOT}" ] && echo "Error: This needs O2DPG loaded" && exit 1
[ ! "${O2_ROOT}" ] && echo "Error: This needs O2 loaded" && exit 1

# select transport engine
SIMENGINE=${SIMENGINE:-TGeant4}
# number of timeframes to simulate
NTFS=${NTFS:-1}
# number of simulation workers per timeframe
NWORKERS=${NWORKERS:-8}
# number of events to be simulated per timeframe
NEVENTS=${NEVENTS:-2200} # this actually just needs to be more than we expect from the IR!
# interaction rate
INTRATE=${INTRATE:-675000}

EXTRA=";Diamond.width[2]=6.;"
CONFKEY=";$EXTRA;"

# create workflow
${O2DPG_ROOT}/MC/bin/o2dpg_sim_workflow.py -eCM 13600 -seed 42 -col pp -gen pythia8 -proc inel -tf ${NTFS} \
    -ns ${NEVENTS} -e ${SIMENGINE} -run 303901 \
    -j ${NWORKERS} -interactionRate ${INTRATE} \
    --first-orbit 0 --orbits-early 0 --no-combine-smaller-digi -confKey "$CONFKEY" \
    --detectorList ALICE2.1 --anchor-config config_303901.json

# run workflow
export IGNORE_VALIDITYCHECK_OF_CCDB_LOCALCACHE=1
${O2DPG_ROOT}/MC/bin/o2_dpg_workflow_runner.py -f workflow.json -tt aod ${MEMLIMIT} ${CPULIMIT} --optimistic-resources
RETMC=${?}

return ${RETMC} 2>/dev/null || exit ${RET}
