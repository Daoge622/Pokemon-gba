#!/usr/bin/env bash
set -euo pipefail
file="${1:-/home/pokemon/projects/emerald-story}"
line="${2:-1}"
if [[ -d "$file" ]]; then
    "/mnt/c/Users/29051/AppData/Local/Programs/Microsoft VS Code/bin/code" --remote wsl+Ubuntu-24.04 "$file"
else
    "/mnt/c/Users/29051/AppData/Local/Programs/Microsoft VS Code/bin/code" --remote wsl+Ubuntu-24.04 --goto "$file:$line"
fi
