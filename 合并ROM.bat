@echo off
chcp 65001 >nul
cd /d "%~dp0"
copy /y /b r_aa + r_ab "EmeraldStory-一周目完整版.gba" >nul
certutil -hashfile "EmeraldStory-一周目完整版.gba" SHA1
echo 应为 977610b33caf395b38683279b16aae90f5f34060
pause
