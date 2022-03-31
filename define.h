#ifndef DEFINE_H
#define DEFINE_H

#define FILE_SIZE       500
// only 26*n is support due to invert matrix function
// only 26 and 676 add to git
#define DICT_SIZE       650
//linux
#define FILE_PATH       "../doc/FILE0001.txt"
#define MATRIX_PATH     "../firstMS/Matrix/Matrix650trans.txt"
#define MATRIXinv_PATH  "../firstMS/Matrix/Matrix650inv.txt"
#define SK_PATH         "../SK.txt"

//windows
//#define FILE_PATH       "..\\doc\\FILE0001.txt"
//#define MATRIX_PATH     "..\\MS\\Matrix\\Matrix650trans.txt"
//#define MATRIXinv_PATH  "..\\MS\\Matrix\\Matrix650inv.txt"
//#define SK_PATH         "..\\SK.txt"


// struct of node
typedef struct tree_node {
    int ID; // node ID
    double D[2][DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
} Node;

// max function
double max( double a, double b ){ return (a>b)?a:b; }


#endif // DEFINE_H
