#!/usr/bin/env bash
set -euo pipefail
binary="$HOME/tools/porymap-6.3.1/porymap"
test -x "$binary"
if pgrep -x porymap > /dev/null; then exit 0; fi
config="$HOME/.local/share/pret/porymap/porymap.cfg"
mkdir -p "$(dirname "$config")"
python3 - "$config" <<'PY'
from pathlib import Path
import sys
p=Path(sys.argv[1])
values={}
if p.exists():
    for line in p.read_text().splitlines():
        if '=' in line:
            key,value=line.split('=',1)
            values[key]=value
values.pop('text_editor_open_folder',None)
values.update({
    'recent_project':'/home/pokemon/projects/emerald-story',
    'reopen_on_launch':'1','project_manually_closed':'0','monitor_files':'1',
    'text_editor_goto_line':'/home/pokemon/projects/emerald-story/scripts/open-vscode-file.sh %F %L',
    'text_editor_open_directory':'/home/pokemon/projects/emerald-story/scripts/open-vscode-file.sh %D'
})
p.write_text(''.join(f'{k}={v}\n' for k,v in values.items()))
PY
exec "$binary"
