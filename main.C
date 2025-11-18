#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "conio.h"
#include "char.h"
#define TERMINALWIDTH 45 //ini namanya global variable

// bagian global deklarasi function
void centertext(int, const char *,char);
void prtEmty(int many);
void loading1();

void menu();

void commonloading(int, const char *, const char *, 
    const char *,
    void (*)(int), bool,
    const int ,const int ,int 
    );
void createBox(int , int , int , int ,
    const char * , 
    const char * ,
    const char * ,
    const char * ,
    const char * ,
    const char * );
// =======================

/** 
    @brief Untuk menaruh text menjadi di tengah dengan mengetahui width yang tersedia
    @param width itu harus lebih besar dari panjang text yang ingin anda print.
    @param text adalah bagian yang ingin anda print.
    @param space adalah character untuk yang di print ketika ada spcae misalnya kosong " "
    @return hasilnya text akan menjadi di tengah tanpa ada enter didalamnya.
*/
void centertext(int widht, const char *text,char space) // ini yang di dalam sini juga namanya local variable
{
    if (widht < strlen(text))
    {
        printf ("Eror while print text, expected width > lenght text");
        exit(1);
    }

    int centerPoint = round(widht/2);
    int textCenterpoint = round(strlen(text)/2);

    for (int i = 0; i < widht; i++)
    {

        if (i == centerPoint-textCenterpoint)
        {
            printf("%s",text);
            i+= strlen(text);
        }
        printf("%c", space);
        
    }
}

/**
 * @brief bagian ini untuk menulis seberapa banyak spasi yang dibutuhkan. dimulai dari 0
 * @param many adalah bagian dari banyaknnya space yang akan diulang.
 * @return kluaran dari fungsi ini adala bentuk text. kosong saja 
 */
void prtEmty(int many){
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
    const int posx=0,const int posy=0,int loadingMS=500
    ){
    int total = lenght;

    gotoxy(posx, posy);
    printf("%s", kurungBuka);
    gotoxy(posx+lenght+1, posy);
    printf("%s", kurungTutup);
    for (int i = 1; i <= total; i++) {
        int percent = (i * 100) / total;
        gotoxy(posx+i, posy);

        printf("%s", barProgres);

        if (cb != NULL)
        {
            cb(total);
        }
        if (showProgres)
        {
            gotoxy(posx+lenght+2, posy);
            printf(" %d%%",percent);
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
    const char *horizontalLine= "-", 
    const char *verticaLine = "|",
    const char *topLeftChar = "+",
    const char *topRightChar = "+",
    const char *bottomLeftChar = "+",
    const char *bottomrightChar = "+"){

    // top 
    for (int i = 0; i < width; i++)
    {
        
        gotoxy(posX+i, posY);
        if (i == 0)
        {
            printf("%s", topLeftChar);
        }else{

            printf("%s", horizontalLine);
        }
        
    }

    //left
    for (int i = 1; i < height; i++)
    {
        gotoxy(posX, posY+i);
        if (i == height-1)
        {
            printf("%s", bottomLeftChar);
        }else{

            printf("%s", verticaLine);
        }
    }
    
    // bottom
    for (int i = 1; i < width; i++)
    {
        
        gotoxy(posX+i, posY+height-1);
        if (i == width-1)
        {
            printf("%s", bottomrightChar);
        }else{

            printf("%s", horizontalLine);
        }
    }
    
    // right
    for (int i = 0; i < height-1; i++)
    {
        gotoxy(posX+width-1, posY+i);
        if (i == 0)
        {
            printf("%s", topRightChar);
        }else{

            printf("%s", verticaLine);
        }
        
    }
    
    
    
}

void loading1(){
    int centerTerminal = round(TERMINALWIDTH/2);
    int length = 20;
    int startpointX = centerTerminal - round(length/2); //X pos
    int startpointY = 5; //Y pos

    createBox(startpointX-4, length+10, startpointY-2, 4);

    gotoxy(startpointX-3, startpointY-1); centertext(length+8, "GOTO MAIN MENU", ' ');
    commonloading(length, "[", "]", BR_VERTICAL_HEAVY, NULL,false, startpointX, startpointY, 300);
}

void starttomenuLoading(){
    loading1();
    clrscr();
    menu();
}

void menu(){
    prtEmty(10);
    centertext(20, "=", '=');
    printf("\n");
    prtEmty(10);
    printf("|");
    centertext(18, "MENU BAR", ' ');
    printf("|");
    printf("\n");
    prtEmty(10);
    centertext(20, "=", '=');
}

int main(){
    clrscr();
    starttomenuLoading();
    printf("\n\n\n");
}