#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>

#ifdef _WIN32 
    #include<windows.h>
    #define CLEAR "cls"
#elif __linux__ 
    #include <unistd.h>
    #define CLEAR "clear"
#endif

#include <sys/ioctl.h>

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



int main(){
    int asu = 0; // ini namanyua local variable 
    centertext(TERMINALWIDTH, "halo", ' ');
}