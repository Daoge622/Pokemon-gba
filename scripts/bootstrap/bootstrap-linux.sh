#!/usr/bin/env bash
set -euo pipefail
if [[ $(id -u) != 0 ]]; then
    echo 'Run bootstrap as the WSL root user.' >&2
    exit 1
fi
workspace='/mnt/d/Pokemon gba'
stage="$workspace/source"
project='/home/pokemon/projects/emerald-story'
export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get upgrade -y
apt-get install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3 unzip pkg-config ripgrep qt6-declarative-dev qt6-charts-dev libmgba-dev
if ! id pokemon >/dev/null 2>&1; then
    # WSL can select this user without a password. Do not create a shared password
    # or grant passwordless sudo. Package management uses wsl.exe -u root.
    useradd --create-home --shell /bin/bash pokemon
    usermod --append --groups sudo pokemon
fi
mkdir -p /home/pokemon/projects
if [[ ! -e "$project" ]]; then
    git -c safe.directory="$stage" -c safe.directory="$stage/.git" clone --no-local -c core.autocrlf=false --branch project/main "$stage" "$project"
    git -C "$project" remote remove origin
    git -C "$project" remote add upstream https://github.com/rh-hideout/pokeemerald-expansion.git
fi
test -d "$project/.git"
mkdir -p "$project/tools/poryscript"
unzip -jo "$workspace/downloads/poryscript-3.6.1-linux.zip" '*/poryscript' -d "$project/tools/poryscript"
chmod +x "$project/tools/poryscript/poryscript"
chown -R pokemon:pokemon /home/pokemon/projects
su -s /bin/bash pokemon -c "cd '$project' && tools/poryscript/poryscript -v && arm-none-eabi-gcc --version && git status --short"
dpkg-query -W build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi git libpng-dev python3 > "$workspace/logs/linux-package-versions.txt"
echo 'Linux dependencies and source migration completed. Full GBA build still requires verification.'
