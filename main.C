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

struct typedaftar
{
    char nama[100];
    int harga;
};

struct typedaftar class_harga[] = {
    {"potong rambut", 15000},
    {"potong cuci tonik", 20000}};

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
        char question[] = "Apakah anda mau mencoba lagi? [tekan a | b]";
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
                }else if(ch == 'd' || ch == 77){
                    gotoxy(centerPointTerminalX - 4, centerPointTerminalY + 1);
                    textcolor(WHITE);
                    printf("Y");
                    printf(" / ");
                    textcolor(RED);
                    printf("N");
                    pilihan = 0;
                }else if (ch == 10)
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
        printf("2. Laporan Pendapatan");
        gotoxy(posX + 3, posY + 5);
        printf("3.  ");
        gotoxy(posX + 3, posY + 6);
        printf("4. Exit");

        int pilih;
        gotoxy(posX + 3, posY + 8);
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        // Logika menu
        switch (pilih)
        {
        case 1:
            clrscr();
            printf("Pricelist...\n");
            printf("Tekan ENTER untuk kembali...");
            getchar();
            getchar();
            break;

        case 2:
            clrscr();
            printf("Laporan Pendapatan...\n");
            printf("Tekan ENTER untuk kembali...");
            getchar();
            getchar();
            break;

        case 3:
            clrscr();
            printf(" ...\n");
            printf("Tekan ENTER untuk kembali...");
            getchar();
            getchar();
            break;

        case 4:
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

void loadingtoMenubar(){
    int lenght = 20;
    int height = 4;
    int padding = 2;
    int posX = centerPointTerminalX - round((lenght+padding+2)/2);
    int posY = 6;
    
    char msg[]= "load file please wait";
    gotoxy(posX+padding, posY+1);
    centertext(lenght, "load file", ' ');
    createBox(posX, lenght+padding+4, posY,height);
    commonloading(lenght, BR_VERTICAL_LIGHT,BR_VERTICAL_LIGHT, BR_VERTICAL_FULLBLOCK, NULL, false, posX+padding, posY+2, 150);
}

int main()
{
#ifdef _WIN32
    system("chcp 65001");
#endif

    clrscr();
    // showDaftarHarga();
    starttoLoginLoading();
    clrscr();
    if (isLogin)
    {
        loadingtoMenubar();
        clrscr();
        MenuBar();
    }else{
        printf(" ██████╗  ██████╗  ██████╗ ██████╗     ██████╗ ██╗   ██╗███████╗    ██╗\n");
        printf("██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗    ██╔══██╗╚██╗ ██╔╝██╔════╝    ██║\n");
        printf("██║  ███╗██║   ██║██║   ██║██║  ██║    ██████╔╝ ╚████╔╝ █████╗      ██║\n");
        printf("██║   ██║██║   ██║██║   ██║██║  ██║    ██╔══██╗  ╚██╔╝  ██╔══╝      ╚═╝\n");
        printf("╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝    ██████╔╝   ██║   ███████╗    ██╗\n");
        printf(" ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝     ╚═════╝    ╚═╝   ╚══════╝    ╚═╝\n");
    }
}