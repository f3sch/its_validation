#!/bin/bash

# make sure O2DPG + O2 is loaded
[ ! "${O2DPG_ROOT}" ] && echo "Error: This needs O2DPG loaded" && exit 1
[ ! "${O2_ROOT}" ] && echo "Error: This needs O2 loaded" && exit 1

# ----------- START ACTUAL JOB  -----------------------------

# select transport engine
SIMENGINE=${SIMENGINE:-TGeant4}
# number of timeframes to simulate
NTFS=${NTFS:-50}
# number of simulation workers per timeframe
NWORKERS=${NWORKERS:-8}
# number of events to be simulated per timeframe
NEVENTS=${NEVENTS:-150}
# interaction rate
INTRATE=${INTRATE:-50000}

EXTRA=";Diamond.width[2]=6.;"
CONFKEY=";$EXTRA;"

# create workflow
rm -rf ccdb pipeline*.log *.root *.dat *.ini
if ! [ -f workflow.json ]; then
	${O2DPG_ROOT}/MC/bin/o2dpg_sim_workflow.py -eCM 5360  -seed 42 -col PbPb -gen pythia8 -proc "heavy_ion" -tf ${NTFS} \
	                                                       -ns ${NEVENTS} -e ${SIMENGINE} --condition-not-after 3385078236000 --timestamp 1731911703921 -run 560184 \
	                                                       -j ${NWORKERS} -interactionRate ${INTRATE} -confKey "$CONFKEY" \
							       --orbits-early 0 --first-orbit 0 \
							       -mod "--skipModules ZDC" \
							       --readoutDets ITS --no-combine-smaller-digi --overwrite-config config-json.json
fi

# run workflow
python3 cleanJSONITS.py
nice -n 19 ${O2DPG_ROOT}/MC/bin/o2_dpg_workflow_runner.py -f filtered_workflow.json -tt itsreco --cpu-limit $(nproc) --optimistic-resources
