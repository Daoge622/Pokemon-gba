$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$image = Join-Path $root 'downloads\ubuntu-24.04-amd64.wsl'
$info = Get-Content -LiteralPath (Join-Path $root 'setup\ubuntu-release.json') -Raw | ConvertFrom-Json
if ((Get-FileHash -LiteralPath $image -Algorithm SHA256).Hash.ToLower() -ne $info.Amd64Url.Sha256) {
    throw 'Official Ubuntu image checksum mismatch.'
}
$existing = @(Get-ChildItem HKCU:\SOFTWARE\Microsoft\Windows\CurrentVersion\Lxss -ErrorAction SilentlyContinue | Get-ItemProperty | Where-Object DistributionName -eq 'Ubuntu-24.04')
if ($existing.Count -eq 0) {
    & wsl.exe --install --from-file $image --name Ubuntu-24.04 --location (Join-Path $root 'wsl\Ubuntu-24.04') --no-launch
    if ($LASTEXITCODE -ne 0) { throw 'Ubuntu installation failed. Verify the required Windows restart has completed.' }
}
& wsl.exe -d Ubuntu-24.04 -u root --exec bash '/mnt/d/Pokemon gba/source/scripts/bootstrap/bootstrap-linux.sh'
if ($LASTEXITCODE -ne 0) { throw 'Linux bootstrap failed. Preserve logs and diagnose before retrying.' }
& wsl.exe --manage Ubuntu-24.04 --set-default-user pokemon
if ($LASTEXITCODE -ne 0) { throw 'Could not set the project Linux user.' }
$envPath = Join-Path $root 'project-env.json'
$envInfo = Get-Content -LiteralPath $envPath -Raw | ConvertFrom-Json
$envInfo.status = 'linux-source-ready'
$envInfo.windowsSource = '\\wsl.localhost\Ubuntu-24.04\home\pokemon\projects\emerald-story'
$envInfo | ConvertTo-Json | Set-Content -LiteralPath $envPath -Encoding UTF8
Write-Output 'Linux source is ready; compile, emulator, and map verification are still pending.'
