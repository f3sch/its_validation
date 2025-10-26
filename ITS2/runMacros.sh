run_root_merge() {
  local ROOT_CMD="$1"
  local OUTNAME="$2"

  # Loop through all directories matching tf*/
  for d in tf*/; do
    pushd "$d" > /dev/null || continue
    echo "Running ROOT command in $d ..."
    root -n -l -q -b "$ROOT_CMD"
    popd > /dev/null || continue
  done

  # Remove existing output if present
  if [[ -f "$OUTNAME" ]]; then
    echo "Removing existing $OUTNAME"
    rm "$OUTNAME"
  fi

  # Merge results with hadd
  echo "Merging results into $OUTNAME ..."
  hadd "$OUTNAME" $(find . -name "$OUTNAME")
}

# Digits
ROOT_CMD='${ALIBUILD_WORK_DIR}/../O2/Detectors/ITSMFT/ITS/macros/test/CheckTracksCA.C++(true, false, false, true, "o2trac_its.root","sgn_grp.root","o2clus_its.root","sgn_Kine.root")'
OUTNAME='CheckTracksCA.root'
run_root_merge "$ROOT_CMD" "$OUTNAME"
