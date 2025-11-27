@echo off
REM ==========================================
REM   RUN WITH POPUP TERMINAL - WINDOWS
REM ==========================================

echo ==========================================
echo   COMPILE DAN JALANKAN DENGAN POPUP
echo ==========================================
echo.

REM Compile main.C
echo [INFO] Compiling main.C...
gcc main.C -o main.exe

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Kompilasi gagal!
    pause
    exit /b 1
)

echo [INFO] Kompilasi berhasil!
echo.

REM Jalankan di terminal baru
echo [INFO] Membuka popup terminal...
start cmd /k "main.exe && echo. && echo Tekan tombol apapun untuk keluar... && pause && exit"

echo.
echo ==========================================
echo   Program berjalan di terminal baru!
echo ==========================================
