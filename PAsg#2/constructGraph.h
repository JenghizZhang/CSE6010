#ifndef _CONSTRUCTGRAPH_H
#define _CONSTRUCTGRAPH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define newNode (Node *)malloc(sizeof(Node))

// The structure of a node, containing the indice number
// and a pointer to the next node
typedef struct Node
{
    int num; // index of the node
    struct Node *next; // next node
} Node;

// read the words from the input file and return a pointer to strings (array of strings)
char **readInWords(char *fileName);
// given a list of words and swap option, construct a graph using adjacency list representation
// return a list of Node pointers
Node **formGraph(char *words[], int swapOption);
// test if two words are connected
// input the index of two words, word list and the swap option
// return 1 if has an edge and 0 if has no edge
int isConnected(int i, int j, char *words[], int swapOption);
#endif