@echo off
chcp 65001 >nul
cd /d "%~dp0"
copy /y /b project.tgz.part00 + project.tgz.part01 + project.tgz.part02 project.tar.gz >nul
certutil -hashfile project.tar.gz SHA1
echo 应为 111533267e903ccf4fbc26ec6439606845dc6a07
echo 解压到 project 文件夹（同名文件会被新版覆盖）...
tar -xzf project.tar.gz
if errorlevel 1 (echo 解压失败 & pause & exit /b)
del project.tar.gz project.tgz.part00 project.tgz.part01 project.tgz.part02 
echo 完成
pause
