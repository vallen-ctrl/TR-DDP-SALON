#!/bin/bash
# ==========================================
#   RUN WITH POPUP TERMINAL - LINUX
# ==========================================

echo "=========================================="
echo "  COMPILE DAN JALANKAN DENGAN POPUP"
echo "=========================================="
echo ""

# Compile main.C
echo "[INFO] Compiling main.C..."
gcc main.C -o main

if [ $? -ne 0 ]; then
    echo ""
    echo "[ERROR] Kompilasi gagal!"
    read -p "Tekan ENTER untuk keluar..."
    exit 1
fi

# Buat executable
chmod +x main

echo "[INFO] Kompilasi berhasil!"
echo ""

# Jalankan di terminal baru
echo "[INFO] Membuka popup terminal..."

# Coba berbagai terminal emulator
if command -v gnome-terminal &> /dev/null; then
    gnome-terminal -- bash -c './main; echo ""; echo "Tekan ENTER untuk keluar..."; read'
elif command -v xfce4-terminal &> /dev/null; then
    xfce4-terminal -e 'bash -c "./main; echo \"\"; echo \"Tekan ENTER untuk keluar...\"; read"'
elif command -v konsole &> /dev/null; then
    konsole -e bash -c './main; echo ""; echo "Tekan ENTER untuk keluar..."; read'
elif command -v xterm &> /dev/null; then
    xterm -e bash -c './main; echo ""; echo "Tekan ENTER untuk keluar..."; read'
elif command -v mate-terminal &> /dev/null; then
    mate-terminal -e 'bash -c "./main; echo \"\"; echo \"Tekan ENTER untuk keluar...\"; read"'
elif command -v terminator &> /dev/null; then
    terminator -e 'bash -c "./main; echo \"\"; echo \"Tekan ENTER untuk keluar...\"; read"'
elif command -v kitty &> /dev/null; then
    kitty bash -c './main; echo ""; echo "Tekan ENTER untuk keluar..."; read'
elif command -v alacritty &> /dev/null; then
    alacritty -e bash -c './main; echo ""; echo "Tekan ENTER untuk keluar..."; read'
else
    echo "[WARNING] Tidak ada terminal GUI yang tersedia."
    echo "[INFO] Menjalankan di terminal saat ini..."
    echo ""
    ./main
    echo ""
    read -p "Tekan ENTER untuk keluar..."
fi

echo ""
echo "=========================================="
echo "  Program berjalan di terminal baru!"
echo "=========================================="