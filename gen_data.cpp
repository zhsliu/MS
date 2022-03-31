#include <QCoreApplication>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>




#define FILE_SIZE       500
// only 26*n is support due to invert matrix function
// only 26 and 676 add to git
#define DICT_SIZE       650
//#define FILE_PATH       "/home/liu/QtProjece/firstMS/doc/FILE0001.txt"
#define FILE_PATH       "../doc/FILE0001.txt"   //linux路径



int gen_data() {
    int i, j;
    FILE *fp;
    struct stat st = {0};

    // initial the random seed
    srand( time(nullptr) );
    // if no dir "doc", creat it
    //printf("%d",stat("/home/liu/QtProjece/firstMS/doc",&st)); //检测文件状态
    if (stat("../doc", &st) == -1) {
        mkdir("../doc",0700);
    }

    // for each file
    for( i = 0; i < FILE_SIZE; i++ ) {
        //initial file name
        char filename[] = FILE_PATH;
        char *ptr = strstr(filename, "FILE");
        sprintf(ptr, "FILE%04d.txt", i+1);
        fp = fopen(filename, "w");

        // for each keyword in file
        for( j = 0; j < DICT_SIZE; j++ ) {
            // initial keyword name
            char word[] = "aa";
            word[0] = 'a' + j / 26;
            word[1] = 'a' + j % 26;

            // generate keyword size, half set to 0
            int a = rand()%(DICT_SIZE*2) - DICT_SIZE;
            if( a < 0 ) a = 0;
            fprintf(fp, "%s %d\n", word, a);
        }

        // close file
        fclose(fp);
    }

    return 0;
}
