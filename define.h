#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>

#define FILE_SIZE       500
#define DICT_SIZE       650
//linux
#define FILE_PATH       "../doc/FILE0001.txt"
#define MATRIX_PATH     "../firstMS/Matrix/Matrix650trans.txt"
#define MATRIXinv_PATH  "../firstMS/Matrix/Matrix650inv.txt"
#define SK_PATH         "../SK.txt"
extern double TF[FILE_SIZE][DICT_SIZE], IDF[DICT_SIZE];
extern double M[2][DICT_SIZE][DICT_SIZE];
extern double Dtmp[DICT_SIZE];
extern double D[2][DICT_SIZE];
extern int SK[DICT_SIZE];
extern int front;
extern int rear;
extern int itemCount;



//windows
//#define FILE_PATH       "..\\doc\\FILE0001.txt"
//#define MATRIX_PATH     "..\\MS\\Matrix\\Matrix650trans.txt"
//#define MATRIXinv_PATH  "..\\MS\\Matrix\\Matrix650inv.txt"
//#define SK_PATH         "..\\SK.txt"





// max function
double max( double a, double b ){ return (a>b)?a:b; }

#endif // DEFINE_H
