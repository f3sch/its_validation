import json
import re

# --- Configuration ---
input_file = "workflow.json"
output_file = "filtered_workflow.json"

# Keep stages whose name includes one of these substrings
accepted_names = [
    "__global_init_task__",
    "grpcreate",
    "precollcontext",
    "sim_alignment",
    "qedsim",
    "linkGRP",
    "geomprefetch",
    "gensgnconf",
    "sgngen",
    "sgnsim",
    "digicontext",
    "itsdigi",
    "itsrec"
]

# Append rules: stage_name_substring -> text to append to 'cmd'
append_map = {
    "sim_alignment": " --onlyDet ITS",
    "sgnsim": " -m ITS",
}

# Replace rules: stage_name_substring -> (pattern, replacement)
replace_map = {
    "qedsim": (r"-m\s+ITS\s+MFT\s+FT0\s+FV0\s+FDD", "-m ITS"),
    "sgnsim": (r"--skipModules ZDC", ""),
}

# --- Load JSON ---
with open(input_file, "r", encoding="utf-8") as f:
    data = json.load(f)

# --- Helper: substring match ---
def matches_any(name: str, accepted):
    """True if any of the accepted substrings appears in the name."""
    if not name:
        return False
    name_lower = name.lower()
    return any(acc.lower() in name_lower for acc in accepted)

# --- Filter and modify 'stages' ---
if "stages" in data and isinstance(data["stages"], list):
    filtered_stages = []
    for stage in data["stages"]:
        name = stage.get("name", "")
        if matches_any(name, accepted_names):
            cmd = stage.get("cmd", "")

            # Apply replacement rule if stage name *contains* any key
            for key, (pattern, repl) in replace_map.items():
                if key.lower() in name.lower():
                    new_cmd = re.sub(pattern, repl, cmd)
                    if new_cmd != cmd:
                        print(f"Replaced pattern for stage '{name}' (rule: '{key}')")
                    cmd = new_cmd

            # Apply append rule if stage name *contains* any key
            for key, append_text in append_map.items():
                if key.lower() in name.lower():
                    if append_text.strip() not in cmd:
                        if cmd.endswith("'"):
                            cmd = cmd[:-1] + append_text + "'"
                        else:
                            cmd = cmd + append_text
                        print(f"Appended text for stage '{name}' (rule: '{key}')")

            stage["cmd"] = cmd
            filtered_stages.append(stage)

    data["stages"] = filtered_stages

# --- Save filtered JSON ---
with open(output_file, "w", encoding="utf-8") as f:
    json.dump(data, f, indent=2, ensure_ascii=False)

print(f"Filtered and modified JSON saved to {output_file}")

