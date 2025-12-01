#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "myconio.h"
#include "char.h"

char PASSWORD[100] = "1234";
char USERNAME[100] = "admin";

// TOLONG SETING INI SESUAI DENGAN SPESIFIKASI TERMINAL ANDA
#define TERMINALWIDTH 120
#define TERMINALHEIGH 25

bool isLogin = false;

int centerPointTerminalX = round(TERMINALWIDTH / 2);
int centerPointTerminalY = round(TERMINALHEIGH / 2);

struct Layanan {
    char nama[50];
    int harga;
};

struct Layanan daftar[10] = {
    {"Potong", 15000},
    {"Potong Cuci Blow", 20000},
    {"Cuci Catok", 25000},
    {"Coloring", 150000},
    {"Smoothing", 150000},
};
// bagian global deklarasi function
// !! CAUTION PLEASE DO NOT TIUCH IT !!
void centertext(int, const char *, char);
void prtEmty(int many);
void loading1();

void LoginPage();

void commonloading(int, const char *, const char *,
                   const char *,
                   void (*)(int), bool,
                   const int, const int, int);
void createBox(int, int, int, int,
               const char *,
               const char *,
               const char *,
               const char *,
               const char *,
               const char *);
void DaftarHarga();
void cetakStruk(int*, int);
// ======================================

/**
    @brief Untuk menaruh text menjadi di tengah dengan mengetahui width yang tersedia
    @param width itu harus lebih besar dari panjang text yang ingin anda print.
    @param text adalah bagian yang ingin anda print.
    @param space adalah character untuk yang di print ketika ada spcae misalnya kosong " "
    @return hasilnya text akan menjadi di tengah tanpa ada enter didalamnya.
*/
void centertext(int widht, const char *text, char space) // ini yang di dalam sini juga namanya local variable
{
    if (widht < strlen(text))
    {
        printf("Eror while print text, expected width > lenght text");
        exit(1);
    }

    int centerPoint = round(widht / 2);
    int textCenterpoint = round(strlen(text) / 2);

    for (int i = 0; i < widht; i++)
    {

        if (i == centerPoint - textCenterpoint)
        {
            printf("%s", text);
            i += strlen(text);
        }
        printf("%c", space);
    }
}

/**
 * @brief bagian ini untuk menulis seberapa banyak spasi yang dibutuhkan. dimulai dari 0
 * @param many adalah bagian dari banyaknnya space yang akan diulang.
 * @return kluaran dari fungsi ini adala bentuk text. kosong saja
 */
void prtEmty(int many)
{
    for (int i = 0; i < many; i++)
    {
        printf(" ");
    }
}

/**
 * @brief bagian ini akan print loading seperti yang anda mau dengan bentuk horizontal
 * @param lenght adalah seberapa panjang loading dapat terbentuk
 * @param kurungBuka adalah bagian awal dari loading
 * @param kurungTutup adalah bagian akhir dari loadng
 * @param barProgres adalah isi dari loadingbar bisa anda ganti
 * @param cb adalah callback untuk memberikan retrun nilai dari progres ubah ke NULL untuk tidak memakainya
 * @param showProgres untuk memberikan informasi terkait persentase di akhir dari loading
 * @param posx adalah lokasi X yang ditentukan untuk dapat di isi biasanya 0
 * @param posy adalah lokasi Y yang ditentukan untuk dapat di isi biasanya 0
 * @param loadingMS adalah lamanya loading berjalan dengan menggunakan Miliseacond
 * @result hasilnya adalah bar progres
 */
void commonloading(int lenght, const char *kurungBuka, const char *kurungTutup,
                   const char *barProgres,
                   void (*cb)(int), bool showProgres = true,
                   const int posx = 0, const int posy = 0, int loadingMS = 500)
{
    int total = lenght;

    gotoxy(posx, posy);
    printf("%s", kurungBuka);
    gotoxy(posx + lenght + 1, posy);
    printf("%s", kurungTutup);
    for (int i = 1; i <= total; i++)
    {
        int percent = (i * 100) / total;
        gotoxy(posx + i, posy);

        printf("%s", barProgres);

        if (cb != NULL)
        {
            cb(total);
        }
        if (showProgres)
        {
            gotoxy(posx + lenght + 2, posy);
            printf(" %d%%", percent);
        }

        fflush(stdout);
        delay(loadingMS);
    }
}

/**
 * @brief bagian ini digunakan untuk membuat sebuah box yang ada
 * @param posX adalah letak awal dari box. Box dibuat dari top left to bottom right
 * @param width adalah lebar dari box
 * @param posY adalah letak dari box
 * @param height adalah tinggi dari box
 * @param horizontalLine adalah character yang akan di print dibagian horizontal defaulth = "-"
 * @param verticalLine adalah character yantg akan di print di bagian vertical defaulth = "|"
 * @param topLeftChar adalah karakter yang diprint di ujung atas kiri box defaulth = "+"
 * @param topRightChar adalah karakter yang akan di print di ujung atas kanan box defaulth = "+"
 * @param bottomLeftChar adalah karakter yang akan di print di ujung bawah kiri box defaulth = "+"
 * @param bottomrightChar adalah karakter yang akan di print di ujung bawah kanan box defaulth = "+"
 * @return hasilnya adalah sebuah box yang dapat anda atur sendiri
 */

void createBox(int posX, int width, int posY, int height,
               const char *horizontalLine = "-",
               const char *verticaLine = "|",
               const char *topLeftChar = "+",
               const char *topRightChar = "+",
               const char *bottomLeftChar = "+",
               const char *bottomrightChar = "+")
{

    // top
    for (int i = 0; i < width; i++)
    {

        gotoxy(posX + i, posY);
        if (i == 0)
        {
            printf("%s", topLeftChar);
        }
        else
        {

            printf("%s", horizontalLine);
        }
    }

    // left
    for (int i = 1; i < height; i++)
    {
        gotoxy(posX, posY + i);
        if (i == height - 1)
        {
            printf("%s", bottomLeftChar);
        }
        else
        {

            printf("%s", verticaLine);
        }
    }

    // bottom
    for (int i = 1; i < width; i++)
    {

        gotoxy(posX + i, posY + height - 1);
        if (i == width - 1)
        {
            printf("%s", bottomrightChar);
        }
        else
        {

            printf("%s", horizontalLine);
        }
    }

    // right
    for (int i = 0; i < height - 1; i++)
    {
        gotoxy(posX + width - 1, posY + i);
        if (i == 0)
        {
            printf("%s", topRightChar);
        }
        else
        {

            printf("%s", verticaLine);
        }
    }
}

void loading1()
{
    int centerTerminal = round(TERMINALWIDTH / 2);
    int length = 20;
    int startpointX = centerTerminal - round(length / 2); // X pos
    int startpointY = 5;                                  // Y pos

    createBox(startpointX - 4, length + 10, startpointY - 2, 4);

    gotoxy(startpointX - 3, startpointY - 1);
    centertext(length + 8, "GOTO MAIN MENU", ' ');
    commonloading(length, BR_VERTICAL_LIGHT, BR_VERTICAL_LIGHT, BR_VERTICAL_FULLBLOCK, NULL, false, startpointX, startpointY, 100);
}

void starttoLoginLoading()
{
    loading1();
    clrscr();
    LoginPage();
}

void LoginPage()
{
    int menuwidth = 30;
    int menuHeight = 7;
    int posX = centerPointTerminalX - (round(menuwidth / 2));
    int posY = centerPointTerminalY - (round(menuHeight / 2));

    char username[100];
    char password[100];

    clrscr();
    gotoxy(posX + 7, posY - 3);
    printf("┓   ┏┓  ┏┓  ┳  ┳┓");
    gotoxy(posX + 7, posY - 2);
    printf("┃   ┃┃  ┃┓  ┃  ┃┃");
    gotoxy(posX + 7, posY - 1);
    printf("┗┛  ┗┛  ┗┛  ┻  ┛┗");

    createBox(posX, menuwidth, posY, menuHeight, BR_HORIZONTAL_HEAVY, BR_VERTICAL_HEAVY, BR_HD_R, BR_HD_L, BR_HD_BR, BR_HD_BL);
    gotoxy(posX + 1, posY + 1);
    centertext(menuwidth - 2, "Hi WELCOME HERE", ' ');
    gotoxy(posX + 2, posY + 3);
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    gotoxy(posX + 2, posY + 4);
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(USERNAME, username) == 0 && strcmp(PASSWORD, password) == 0)
    {
        clrscr();
        char message[] = "login anda berhasil";
        for (int i = 0; i < strlen(message); i++)
        {
            gotoxy(centerPointTerminalX - (round(strlen(message) / 2)) + i, centerPointTerminalY);
            textcolor(GREEN);
            printf("%c", message[i]);
            fflush(stdout);
            delay(100);
        }
        delay(2000);
        isLogin = true;
    }
    else
    {
        clrscr();
        char message[] = "USERNAME OR PASSWORD WRONG!";
        for (int i = 0; i < strlen(message); i++)
        {
            gotoxy(centerPointTerminalX - (round(strlen(message) / 2)) + i, centerPointTerminalY);
            textcolor(RED);
            printf("%c", message[i]);
            fflush(stdout);
            delay(100);
        }

        clrscr();
        textcolor(WHITE);
        char question[] = "Apakah anda mau mencoba lagi? [tekan a | d]";
        gotoxy(centerPointTerminalX - (round(strlen(question) / 2)), centerPointTerminalY);
        printf("%s", question);

        gotoxy(centerPointTerminalX - 4, centerPointTerminalY + 1);
        textcolor(WHITE);
        printf("Y");
        printf(" / ");
        printf("N");

        int pilihan = 0;
        while (true)
        {
            if (kbhit)
            {
                int ch = getch();
                if (ch == 'a' || ch == 75)
                {
                    gotoxy(centerPointTerminalX - 4, centerPointTerminalY + 1);
                    textcolor(GREEN);
                    printf("Y");
                    textcolor(WHITE);
                    printf(" / ");
                    printf("N");
                    pilihan = 1;
                }
                else if (ch == 'd' || ch == 77)
                {
                    gotoxy(centerPointTerminalX - 4, centerPointTerminalY + 1);
                    textcolor(WHITE);
                    printf("Y");
                    printf(" / ");
                    textcolor(RED);
                    printf("N");
                    pilihan = 0;
                }
                else if (ch == 10 || ch == 13)
                {
                    break;
                }
            }
        }

        if (pilihan == 1)
        {
            LoginPage();
        }
        else
        {
            isLogin = false;
        }
    }
}

void MenuBar()
{
    int menuWidth = 30;
    int menuHeight = 10;
    int posX = centerPointTerminalX - (menuWidth / 2);
    int posY = centerPointTerminalY - (menuHeight / 2);

    while (1) // loop menu
    {
        clrscr();
        textcolor(WHITE);
        // Buat box menu
        createBox(posX, menuWidth, posY, menuHeight,
                  BR_HORIZONTAL_HEAVY, BR_VERTICAL_HEAVY,
                  BR_HD_R, BR_HD_L, BR_HD_BR, BR_HD_BL);

        // Judul
        gotoxy(posX + 1, posY + 1);
        centertext(menuWidth - 2, "MAIN MENU", ' ');

        // Isi dari menu
        gotoxy(posX + 3, posY + 3);
        printf("1. Pricelist");
        gotoxy(posX + 3, posY + 4);
        printf("2. Exit");

        int pilih;
        gotoxy(posX + 3, posY + 8);
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        // Logika menu
        switch (pilih)
        {
        case 1:
            clrscr();
            DaftarHarga();
            break;

        case 2:
            clrscr();
            return; // keluar dari fungsi → selesai

        default:
            clrscr();
            printf("Pilihan tidak valid!\n");
            printf("Tekan ENTER untuk kembali...");
            getchar();
            getchar();
            break;
        }
    }
}

void loadingtoMenubar()
{
    int lenght = 20;
    int height = 4;
    int padding = 2;
    int posX = centerPointTerminalX - round((lenght + padding + 2) / 2);
    int posY = 6;

    char msg[] = "load file please wait";
    gotoxy(posX + padding, posY + 1);
    centertext(lenght, "load file", ' ');
    createBox(posX, lenght + padding + 4, posY, height);
    commonloading(lenght, BR_VERTICAL_LIGHT, BR_VERTICAL_LIGHT, BR_VERTICAL_FULLBLOCK, NULL, false, posX + padding, posY + 2, 150);
}

void DaftarHarga() {
    clrscr();

    int jumlah = 5;
    int width = 70;
    int height = jumlah + 12;
    int posX = centerPointTerminalX - (width/2);
    int posY = centerPointTerminalY - (height/2);

    createBox(posX, width, posY, height,
              BR_HORIZONTAL_HEAVY, BR_VERTICAL_HEAVY,
              BR_HD_R, BR_HD_L, BR_HD_BR, BR_HD_BL);

    gotoxy(posX+1, posY+1);
    centertext(width-2, "DAFTAR HARGA SALON", ' ');

    int pilihan[5] = {0}; // Array untuk menyimpan pilihan (max 10)
    int jumlahPilihan = 0; // Counter jumlah pilihan yang sudah dipilih
    bool selesai = false;

    while (!selesai) {
        // Tampilkan daftar layanan
        for (int i = 0; i < jumlah; i++) {
            gotoxy(posX+3, posY + 3 + i);
            
            // Cek apakah layanan ini sudah dipilih
            bool sudahDipilih = false;
            int jumlahKaliDipilih = 0;
            
            for (int j = 0; j < jumlahPilihan; j++) {
                if (pilihan[j] == i + 1) {
                    sudahDipilih = true;
                    jumlahKaliDipilih++;
                }
            }

            // Tampilkan dengan warna hijau jika sudah dipilih
            if (sudahDipilih) {
                textcolor(GREEN);
                printf("[%dx] ", jumlahKaliDipilih); // Tampilkan berapa kali dipilih
            } else {
                textcolor(WHITE);
                printf("[ ] ");
            }

            printf("%d. %-22s : Rp %d        ", i+1, daftar[i].nama, daftar[i].harga);
            textcolor(WHITE);
        }

        // Tampilkan instruksi
        gotoxy(posX+3, posY + 3 + jumlah + 1);
        textcolor(CYAN);
        printf("Masukkan nomor layanan (1-%d)", jumlah);
        textcolor(WHITE);

        gotoxy(posX+3, posY + 3 + jumlah + 2);
        textcolor(YELLOW);
        printf("0  = Selesai & Lanjut");
        textcolor(WHITE);

        gotoxy(posX+3, posY + 3 + jumlah + 3);
        textcolor(YELLOW);
        printf("99 = Hapus pilihan terakhir");
        textcolor(WHITE);

        // Tampilkan pilihan yang sudah dipilih
        gotoxy(posX+3, posY + height - 4);
        printf("Jumlah dipilih: %d/5", jumlahPilihan);

        gotoxy(posX+3, posY + height - 3);
        printf("Pilihan Anda: ");
        
        // Tampilkan semua pilihan dengan detail
        if (jumlahPilihan > 0) {
            // Hitung berapa kali setiap layanan dipilih
            int count[6] = {0}; // Index 0 tidak dipakai, 1-5 untuk layanan
            for (int i = 0; i < jumlahPilihan; i++) {
                count[pilihan[i]]++;
            }
            
            // Tampilkan ringkasan
            bool pertama = true;
            for (int i = 1; i <= jumlah; i++) {
                if (count[i] > 0) {
                    if (!pertama) printf(", ");
                    printf("%d(%dx)", i, count[i]);
                    pertama = false;
                }
            }
        } else {
            printf("-");
        }
        printf("                "); // Clear sisa

        // Input pilihan
        gotoxy(posX+3, posY + height - 2);
        printf("Masukkan pilihan: ");
        printf("    "); // Clear input sebelumnya
        
        gotoxy(posX+22, posY + height - 2);
        
        int input;
        scanf("%d", &input);

        // Proses input
        if (input == 0) {
            // Selesai memilih
            if (jumlahPilihan > 0) {
                selesai = true;
            } else {
                // Tampilkan peringatan jika belum ada pilihan
                gotoxy(posX+3, posY + height + 1);
                textcolor(RED);
                printf("Pilih minimal 1 layanan!");
                textcolor(WHITE);
                getch();
                getch();
                gotoxy(posX+3, posY + height + 1);
                printf("                                        ");
            }
        }
        else if (input == 99) {
            // Hapus pilihan terakhir
            if (jumlahPilihan > 0) {
                jumlahPilihan--;
                pilihan[jumlahPilihan] = 0;
                
                // Feedback
                gotoxy(posX+3, posY + height + 1);
                textcolor(YELLOW);
                printf("Pilihan terakhir dihapus!");
                textcolor(WHITE);
                getch();
                getch();
                gotoxy(posX+3, posY + height + 1);
                printf("                                        ");
            } else {
                gotoxy(posX+3, posY + height + 1);
                textcolor(RED);
                printf("Tidak ada pilihan untuk dihapus!");
                textcolor(WHITE);
                getch();
                getch();
                gotoxy(posX+3, posY + height + 1);
                printf("                                        ");
            }
        }
        else if (input >= 1 && input <= jumlah) {
            // Tambah pilihan jika belum mencapai maksimal
            if (jumlahPilihan < 5) {
                pilihan[jumlahPilihan] = input;
                jumlahPilihan++;
                
                // Feedback
                gotoxy(posX+3, posY + height + 1);
                textcolor(GREEN);
                printf("Layanan '%s' ditambahkan!", daftar[input-1].nama);
                textcolor(WHITE);
                getch();
                getch();
                gotoxy(posX+3, posY + height + 1);
                printf("                                        ");
            } else {
                // Sudah mencapai maksimal
                gotoxy(posX+3, posY + height + 1);
                textcolor(RED);
                printf("Maksimal 10 layanan!");
                textcolor(WHITE);
                getch();
                getch();
                gotoxy(posX+3, posY + height + 1);
                printf("                                        ");
            }
        }
        else {
            // Input tidak valid
            gotoxy(posX+3, posY + height + 1);
            textcolor(RED);
            printf("Pilihan tidak valid!");
            textcolor(WHITE);
            getch();
            getch();
            gotoxy(posX+3, posY + height + 1);
            printf("                                        ");
        }
    }

    // Lanjut ke cetak struk
    cetakStruk(pilihan, jumlahPilihan);
}

void cetakStruk(int pilihanList[], int count) {
    clrscr();

    int width = 60;
    int height = 10 + count;
    int posX = centerPointTerminalX - (width/2);
    int posY = centerPointTerminalY - (height/2);

    createBox(posX, width, posY, height,
              BR_HORIZONTAL_HEAVY, BR_VERTICAL_HEAVY,
              BR_HD_R, BR_HD_L, BR_HD_BR, BR_HD_BL);

    gotoxy(posX+1, posY+1);
    centertext(width-2, "STRUK PEMBAYARAN", ' ');

    int total = 0;

    // Tampilkan setiap layanan yang dipilih
    for (int i = 0; i < count; i++) {
        int index = pilihanList[i] - 1; // Convert ke index array (1->0, 2->1, dst)
        
        gotoxy(posX+3, posY + 3 + i);
        printf("%d. %-25s : Rp %d",
               i+1,
               daftar[index].nama,
               daftar[index].harga);

        total += daftar[index].harga;
    }

    // Garis pemisah
    gotoxy(posX+3, posY + 4 + count);
    for (int i = 0; i < width-6; i++) {
        printf("-");
    }

    // Total
    gotoxy(posX+3, posY + 5 + count);
    textcolor(YELLOW);
    printf("TOTAL");
    textcolor(WHITE);
    printf(" : Rp %d", total);

    // Instruksi kembali
    gotoxy(posX+3, posY + 7 + count);
    textcolor(CYAN);
    printf("Tekan ENTER untuk kembali");
    textcolor(WHITE);
    getch();
    getch(); // Tunggu input
}

int main()
{
#ifdef _WIN32
    system("chcp 65001");
#endif

    clrscr();
    starttoLoginLoading();
    clrscr();
    if (isLogin)
    {
        loadingtoMenubar();
        clrscr();
        MenuBar();
    }

    textcolor(RED);
    printf(" ██████╗  ██████╗  ██████╗ ██████╗     ██████╗ ██╗   ██╗███████╗    ██╗\n");
    printf("██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗    ██╔══██╗╚██╗ ██╔╝██╔════╝    ██║\n");
    printf("██║  ███╗██║   ██║██║   ██║██║  ██║    ██████╔╝ ╚████╔╝ █████╗      ██║\n");
    printf("██║   ██║██║   ██║██║   ██║██║  ██║    ██╔══██╗  ╚██╔╝  ██╔══╝      ╚═╝\n");
    printf("╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝    ██████╔╝   ██║   ███████╗    ██╗\n");
    printf(" ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝     ╚═════╝    ╚═╝   ╚══════╝    ╚═╝\n");
}