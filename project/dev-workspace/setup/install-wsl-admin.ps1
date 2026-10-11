$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$log = Join-Path $root 'logs\wsl-admin.log'
Start-Transcript -Path $log -Append
try {
    # Only stop the earlier installer started for this project, if still running.
    $pidFile = Join-Path $root 'logs\wsl-install.pid'
    if (Test-Path -LiteralPath $pidFile) {
        $setupProcessId = [int](Get-Content -LiteralPath $pidFile)
        $setupProcess = Get-Process -Id $setupProcessId -ErrorAction SilentlyContinue
        if ($setupProcess -and $setupProcess.ProcessName -eq 'wsl') {
            Stop-Process -Id $setupProcessId
        }
    }
    $msiExitCode = 0
    if (-not (Test-Path -LiteralPath 'C:\Program Files\WSL\wsl.exe')) {
        $installer = Join-Path $root 'downloads\wsl.3.0.1.0.x64.msi'
        $expected = '28b1a0d013640a2ac95898ea705fa186e5b4ff767a1c1b49257161bc106599c6'
        if ((Get-FileHash -LiteralPath $installer -Algorithm SHA256).Hash.ToLower() -ne $expected) {
            throw 'Official WSL installer SHA256 mismatch.'
        }
        if ((Get-AuthenticodeSignature -LiteralPath $installer).Status -ne 'Valid') {
            throw 'WSL installer signature is not valid.'
        }
        $msiLog = Join-Path $root 'logs\wsl-msi.log'
        $install = Start-Process msiexec.exe -ArgumentList "/i `"$installer`" /qn /norestart /L*v `"$msiLog`"" -WindowStyle Hidden -Wait -PassThru
        $msiExitCode = $install.ExitCode
        Write-Output "MSI exit code: $msiExitCode"
        if ($msiExitCode -notin @(0, 3010)) { throw 'WSL MSI installation failed; see wsl-msi.log.' }
    } else {
        Write-Output 'WSL is already installed; skipping duplicate installation.'
    }
    $feature = Enable-WindowsOptionalFeature -Online -FeatureName VirtualMachinePlatform -All -NoRestart
    $feature | Format-List
    [ordered]@{
        WslMsiExitCode = $msiExitCode
        VirtualMachinePlatform = (Get-WindowsOptionalFeature -Online -FeatureName VirtualMachinePlatform).State.ToString()
        RestartNeeded = ($feature.RestartNeeded -or $msiExitCode -eq 3010)
        CompletedAt = (Get-Date).ToString('o')
    } | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $root 'logs\wsl-admin-result.json') -Encoding UTF8
} catch {
    $_ | Out-String | Add-Content -LiteralPath (Join-Path $root 'logs\wsl-admin-error.txt')
    throw
} finally {
    Stop-Transcript
}
