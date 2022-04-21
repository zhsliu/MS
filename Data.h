#ifndef DATA_H
#define DATA_H

#define FILE_SIZE       500
#define DICT_SIZE       650
typedef struct tree_node {
    int ID; // node ID
    double D[2][DICT_SIZE]; // index data
    struct tree_node *Pl; // pointer to left node
    struct tree_node *Pr; // pointer to right node
    int FID; // pointer to file, use file's ID here
} Node;

#endif // DATA_H
