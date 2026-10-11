param(
    [ValidateSet('Build','Test','Release','Sync','RecordDeltas','Run','Map','Code')]
    [string]$Action='Build',
    [string]$WorkspaceRoot='D:\Pokemon gba'
)
$ErrorActionPreference='Stop'
if ($Action -in @('Run','Map','Code')) { throw 'GUI/emulator/ROM launching is disabled. Open editors manually if needed.' }
$project=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$info=Get-Content -LiteralPath (Join-Path $project 'project-env.json') -Raw | ConvertFrom-Json
$mode=switch ($Action) { 'Release' {'release'} 'Sync' {'sync'} 'RecordDeltas' {'record-deltas'} default {'build'} }
$arguments=@('-d',$info.distribution,'-u',$info.linuxUser,'--exec','python3','/mnt/d/Pokemon gba/project/scripts/windows/mirror-build.py',$mode)
& wsl.exe @arguments
if ($LASTEXITCODE -ne 0) { throw "Operation failed with exit code $LASTEXITCODE. No GUI or ROM was launched." }
