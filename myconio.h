/**
 * myconio.h - Cross-platform conio.h implementation
 * Kompatibel untuk Windows (MinGW/CodeBlocks) dan Linux
 * TIDAK memerlukan conio.h - implementasi penuh custom
 * 
 * Cara pakai:
 * - Ganti #include <conio.h> dengan #include "myconio.h"
 * - Windows: gcc program.c -o program.exe
 * - Linux: gcc program.c -o program
 */

#ifndef MYCONIO_H
#define MYCONIO_H

#include <stdio.h>

#ifdef _WIN32
    // ===== WINDOWS (MinGW/CodeBlocks) =====
    #include <windows.h>
    
    // Konstanta warna untuk textcolor()
    #define BLACK        0
    #define BLUE         1
    #define GREEN        2
    #define CYAN         3
    #define RED          4
    #define MAGENTA      5
    #define BROWN        6
    #define LIGHTGRAY    7
    #define DARKGRAY     8
    #define LIGHTBLUE    9
    #define LIGHTGREEN   10
    #define LIGHTCYAN    11
    #define LIGHTRED     12
    #define LIGHTMAGENTA 13
    #define YELLOW       14
    #define WHITE        15
    
    /**
     * getch() - Membaca satu karakter tanpa echo dan tanpa perlu Enter
     * Return: karakter yang ditekan
     */
    int getch(void) {
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode, count;
        char ch;
        
        // Simpan mode lama
        GetConsoleMode(hStdin, &mode);
        
        // Set mode: matikan line input dan echo
        SetConsoleMode(hStdin, 0);
        
        // Baca satu karakter
        ReadConsole(hStdin, &ch, 1, &count, NULL);
        
        // Kembalikan mode lama
        SetConsoleMode(hStdin, mode);
        
        return ch;
    }
    
    /**
     * getche() - Membaca satu karakter dengan echo (terlihat di layar)
     * Return: karakter yang ditekan
     */
    int getche(void) {
        int ch = getch();
        putchar(ch);  // Echo karakter
        fflush(stdout);
        return ch;
    }
    
    /**
     * kbhit() - Cek apakah ada keyboard input (non-blocking)
     * Return: 1 jika ada input, 0 jika tidak
     */
    int kbhit(void) {
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD events;
        INPUT_RECORD buffer;
        
        // Cek jumlah event di buffer
        PeekConsoleInput(hStdin, &buffer, 1, &events);
        
        if (events > 0) {
            // Cek apakah ada key event
            if (buffer.EventType == KEY_EVENT && buffer.Event.KeyEvent.bKeyDown) {
                return 1;
            } else {
                // Buang event yang bukan keyboard
                ReadConsoleInput(hStdin, &buffer, 1, &events);
                return kbhit();  // Cek lagi
            }
        }
        return 0;
    }
    
    /**
     * clrscr() - Clear screen (membersihkan layar)
     */
    void clrscr(void) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coordScreen = {0, 0};
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;
        
        // Dapatkan ukuran buffer
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        
        // Reset ke warna default (putih text, hitam background)
        WORD defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        
        // Isi dengan spasi
        FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
        
        // Isi dengan atribut warna default (ini yang penting!)
        FillConsoleOutputAttribute(hConsole, defaultColor, dwConSize, coordScreen, &cCharsWritten);
        
        // Set warna console ke default
        SetConsoleTextAttribute(hConsole, defaultColor);
        
        // Pindah cursor ke (0,0)
        SetConsoleCursorPosition(hConsole, coordScreen);
    }
    
    /**
     * gotoxy() - Pindahkan cursor ke posisi (x, y)
     * x: kolom (horizontal), mulai dari 1
     * y: baris (vertical), mulai dari 1
     */
    void gotoxy(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord;
        coord.X = x - 1;  // Windows mulai dari 0
        coord.Y = y - 1;
        SetConsoleCursorPosition(hConsole, coord);
    }
    
    /**
     * textcolor() - Set warna text
     * color: gunakan konstanta warna (RED, GREEN, dll)
     */
    void textcolor(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        
        // Pertahankan warna background, ganti foreground
        WORD newColor = (csbi.wAttributes & 0xF0) | (color & 0x0F);
        SetConsoleTextAttribute(hConsole, newColor);
    }
    
    /**
     * textbackground() - Set warna background
     * color: gunakan konstanta warna
     */
    void textbackground(int color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        
        // Pertahankan warna foreground, ganti background
        WORD newColor = (csbi.wAttributes & 0x0F) | ((color & 0x0F) << 4);
        SetConsoleTextAttribute(hConsole, newColor);
    }
    
    /**
     * wherex() - Dapatkan posisi kolom cursor saat ini
     * Return: posisi X (kolom), mulai dari 1
     */
    int wherex(void) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        return csbi.dwCursorPosition.X + 1;  // Kembalikan 1-based
    }
    
    /**
     * wherey() - Dapatkan posisi baris cursor saat ini
     * Return: posisi Y (baris), mulai dari 1
     */
    int wherey(void) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        return csbi.dwCursorPosition.Y + 1;  // Kembalikan 1-based
    }
    
    /**
     * delay() - Delay/pause program dalam milidetik
     * ms: waktu delay dalam milidetik
     */
    void delay(int ms) {
        Sleep(ms);
    }
    
#else
    // ===== LINUX =====
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <sys/ioctl.h>
    
    // Konstanta warna untuk textcolor()
    #define BLACK        0
    #define BLUE         1
    #define GREEN        2
    #define CYAN         3
    #define RED          4
    #define MAGENTA      5
    #define BROWN        6
    #define LIGHTGRAY    7
    #define DARKGRAY     8
    #define LIGHTBLUE    9
    #define LIGHTGREEN   10
    #define LIGHTCYAN    11
    #define LIGHTRED     12
    #define LIGHTMAGENTA 13
    #define YELLOW       14
    #define WHITE        15
    
    /**
     * getch() - Membaca satu karakter tanpa echo dan tanpa perlu Enter
     * Return: karakter yang ditekan
     */
    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        
        // Simpan setting terminal lama
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        
        // Matikan canonical mode dan echo
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        
        // Baca karakter
        ch = getchar();
        
        // Kembalikan setting terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        
        return ch;
    }
    
    /**
     * getche() - Membaca satu karakter dengan echo (terlihat di layar)
     * Return: karakter yang ditekan
     */
    int getche(void) {
        struct termios oldattr, newattr;
        int ch;
        
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        
        // Matikan canonical mode, tapi biarkan echo
        newattr.c_lflag &= ~ICANON;
        newattr.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        
        ch = getchar();
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        
        return ch;
    }
    
    /**
     * kbhit() - Cek apakah ada keyboard input (non-blocking)
     * Return: 1 jika ada input, 0 jika tidak
     */
    int kbhit(void) {
        struct termios oldattr, newattr;
        int byteswaiting;
        
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        
        ioctl(STDIN_FILENO, FIONREAD, &byteswaiting);
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        
        return byteswaiting > 0;
    }
    
    /**
     * clrscr() - Clear screen (membersihkan layar)
     */
    void clrscr(void) {
        // ANSI escape code untuk clear screen
        printf("\e[1;1H\e[2J");
        fflush(stdout);
    }
    
    /**
     * gotoxy() - Pindahkan cursor ke posisi (x, y)
     * x: kolom (horizontal), mulai dari 1
     * y: baris (vertical), mulai dari 1
     */
    void gotoxy(int x, int y) {
        printf("\033[%d;%dH", y, x);
        fflush(stdout);
    }
    
    /**
     * textcolor() - Set warna text
     * color: gunakan konstanta warna (RED, GREEN, dll)
     */
    void textcolor(int color) {
        // ANSI color codes
        const char* colors[] = {
            "\033[0;30m",  // BLACK
            "\033[0;34m",  // BLUE
            "\033[0;32m",  // GREEN
            "\033[0;36m",  // CYAN
            "\033[0;31m",  // RED
            "\033[0;35m",  // MAGENTA
            "\033[0;33m",  // BROWN
            "\033[0;37m",  // LIGHTGRAY
            "\033[1;30m",  // DARKGRAY
            "\033[1;34m",  // LIGHTBLUE
            "\033[1;32m",  // LIGHTGREEN
            "\033[1;36m",  // LIGHTCYAN
            "\033[1;31m",  // LIGHTRED
            "\033[1;35m",  // LIGHTMAGENTA
            "\033[1;33m",  // YELLOW
            "\033[1;37m"   // WHITE
        };
        
        if (color >= 0 && color <= 15) {
            printf("%s", colors[color]);
            fflush(stdout);
        }
    }
    
    /**
     * textbackground() - Set warna background
     * color: gunakan konstanta warna
     */
    void textbackground(int color) {
        // ANSI background color codes
        const char* bgcolors[] = {
            "\033[40m",  // BLACK
            "\033[44m",  // BLUE
            "\033[42m",  // GREEN
            "\033[46m",  // CYAN
            "\033[41m",  // RED
            "\033[45m",  // MAGENTA
            "\033[43m",  // BROWN
            "\033[47m",  // LIGHTGRAY
            "\033[40m",  // DARKGRAY (same as black)
            "\033[44m",  // LIGHTBLUE (same as blue)
            "\033[42m",  // LIGHTGREEN (same as green)
            "\033[46m",  // LIGHTCYAN (same as cyan)
            "\033[41m",  // LIGHTRED (same as red)
            "\033[45m",  // LIGHTMAGENTA (same as magenta)
            "\033[43m",  // YELLOW (same as brown)
            "\033[47m"   // WHITE (same as lightgray)
        };
        
        if (color >= 0 && color <= 15) {
            printf("%s", bgcolors[color]);
            fflush(stdout);
        }
    }
    
    /**
     * wherex() - Dapatkan posisi kolom cursor saat ini
     * Return: posisi X (kolom)
     * Note: Implementasi sederhana, return 0 (tidak akurat di Linux)
     */
    int wherex(void) {
        // Implementasi lengkap butuh parsing ANSI response
        // Untuk simplicity, return 0
        return 0;
    }
    
    /**
     * wherey() - Dapatkan posisi baris cursor saat ini
     * Return: posisi Y (baris)
     * Note: Implementasi sederhana, return 0 (tidak akurat di Linux)
     */
    int wherey(void) {
        return 0;
    }
    
    /**
     * delay() - Delay/pause program dalam milidetik
     * ms: waktu delay dalam milidetik
     */
    void delay(int ms) {
        usleep(ms * 1000);
    }
    
#endif // _WIN32

// Fungsi tambahan yang berguna untuk kedua platform

/**
 * resetcolor() - Reset warna ke default
 */
static inline void resetcolor(void) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #else
        printf("\033[0m");
        fflush(stdout);
    #endif
}

/**
 * clearline() - Hapus baris saat ini
 */
static inline void clearline(void) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD coord;
        DWORD written;
        
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        coord.X = 0;
        coord.Y = csbi.dwCursorPosition.Y;
        
        FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, coord, &written);
        SetConsoleCursorPosition(hConsole, coord);
    #else
        printf("\033[2K\r");
        fflush(stdout);
    #endif
}

#endif // MYCONIO_H