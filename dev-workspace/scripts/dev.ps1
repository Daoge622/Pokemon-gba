param(
    [ValidateSet('Build', 'Test', 'Release', 'Run', 'Map', 'Code')]
    [string]$Action = 'Build'
)
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$envInfo = Get-Content -LiteralPath (Join-Path $root 'project-env.json') -Raw | ConvertFrom-Json
$entry = Join-Path $envInfo.windowsSource 'scripts\windows\dev.ps1'
& $entry -Action $Action -WorkspaceRoot $root
