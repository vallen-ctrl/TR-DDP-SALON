#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#define TERMINALWIDTH 45 //ini namanya global variable

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
    for(int i = 0; i<many; i++){
        printf(" ");
    }
}

void loading(){
    int marginRight = 20;
    int width = 20;
    for(int progres = 0; progres < 100; progres ++){
       printf("|");
       
    }


}

void menu(){
    prtEmty(10);
    centertext(21, "=", '=');
    printf("\n");
    prtEmty(10);
    printf("|");
    centertext(18, "SALON ANJAY MABAR", ' ');
    printf("|");
    printf("\n");
    prtEmty(10);
    centertext(21, "=", '=');
    printf("\n");
    prtEmty(10);
    printf("|");
    centertext(19, "1. pilihan1", ' ');
    printf("|");
    printf("\n");
    prtEmty(10);
    printf("|");
    centertext(19, "2. pilihan2", ' ');
    printf("|");
    printf("\n");
    prtEmty(10);
    printf("|");
    centertext(19, "3. pilihan3", ' ');
    printf("|");
    printf("\n");
    prtEmty(10);
    printf("|");
    centertext(19, "4. pilihan4", ' ');
    printf("|");
    printf("\n");
    prtEmty(10);
    centertext(21, "=", '=');
    printf("\n");
    prtEmty(10);
    printf("masukkan pilihan : ");
}

int main(){
    int pil;
    menu();
    scanf("%d", &pil);
    if(pil == 1){
        printf("anjay");
    }
    else if(pil == 2){
        printf("anjay juga");
    }
    else if(pil == 3){
        printf("anjay lagi");
    }
    else if(pil == 4){
        printf("anjay terus");
    }
    else {
        printf("milih yang bener lah!");
    }
}