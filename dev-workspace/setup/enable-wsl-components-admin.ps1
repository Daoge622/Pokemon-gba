$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
Start-Transcript -Path (Join-Path $root 'logs\wsl-components.log') -Force
try {
    $results = @()
    foreach ($name in @('VirtualMachinePlatform', 'Microsoft-Windows-Subsystem-Linux')) {
        $state = Get-WindowsOptionalFeature -Online -FeatureName $name
        if ($state.State -eq 'Enabled') {
            $results += [PSCustomObject]@{ Feature=$name; State='Enabled'; RestartNeeded=$false }
        } else {
            $enabled = Enable-WindowsOptionalFeature -Online -FeatureName $name -All -NoRestart
            $results += [PSCustomObject]@{
                Feature=$name
                State=(Get-WindowsOptionalFeature -Online -FeatureName $name).State.ToString()
                RestartNeeded=$enabled.RestartNeeded
            }
        }
    }
    $results | Format-Table
    $results | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $root 'logs\wsl-components-result.json') -Encoding UTF8
} finally {
    Stop-Transcript
}
