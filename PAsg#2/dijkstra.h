#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constructGraph.h"


// define the vertice of the graph
typedef struct Vertice
{
    int num;        // ID of this Vertice
    int d;          // current estimated shortest distance to the src Vertice
    int pre;          // predecessor Vertice on the current shortest path
}Vertice;

// use dijkstra's algorithm to calculate shortest path
// input includes the src and dest word indexs, graph, and words list
void findPath(int src, int destr, Node* graph[], char* words[]);

// find a vertex from a PQ using the given id , if found, pass out the spot in the PQ
// input includes the id of the vertice, vertice array, size of the array and the spot as index
// return whether we find the vertice
int find(int id, Vertice Q[], int QSize, int* pSpot);

// set the distance of the vertice as the minimum value
// input include two pointers to vertice
void relax(Vertice* u, Vertice* v);

// print the result
// input includes the vertice array S and its size, word list, src and dest word, and a hash map to map the word from S
void printResult(Vertice S[], int SSize, char* words[], int src, int dest, int hashMap[]);

// build a priority Queue given an array of random elements
// input include vertice array and size of array
void buildPQ(Vertice arr[], int size);
// adjust the tree under node "index" to be a min-heap (priority queue)
void adjust(Vertice arr[], int size, int index);

// pop the min element
// input includes vertice array and size of array
// return the poped vertice
Vertice pop(Vertice arr[], int size);

#endif