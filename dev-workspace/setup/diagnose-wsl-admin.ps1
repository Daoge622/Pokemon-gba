$ErrorActionPreference = 'Continue'
$root = Split-Path $PSScriptRoot -Parent
Start-Transcript -Path (Join-Path $root 'logs\wsl-diagnostics-after-reboot.log') -Force
Get-Date
Get-WindowsOptionalFeature -Online -FeatureName VirtualMachinePlatform | Format-List
Get-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux | Format-List
Get-Service WslService, vmcompute, hns -ErrorAction SilentlyContinue | Format-List Name,Status,StartType
Get-CimInstance Win32_OperatingSystem | Format-List LastBootUpTime
& bcdedit.exe /enum
Get-WinEvent -FilterHashtable @{LogName='System';ProviderName='Microsoft-Windows-Kernel-General';Id=12} -MaxEvents 3 -ErrorAction SilentlyContinue | Format-List TimeCreated,Message
Stop-Transcript
