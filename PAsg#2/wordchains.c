#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constructGraph.h"
#include "dijkstra.h"

int main(int argc, char *argv[])
{
    int src = 0, dest = 0, swapOption = 0;
    // check whether it has more than 2 arguments
    if (argc < 3)
    {
        // not meet the argument requirements
        printf("Please specify the source indice and destination indice\n");
        return 0;
    }
    else
    {
        // change the source and dest to integers
        src = atoi(argv[1]);
        dest = atoi(argv[2]);
        // check whether it is in the "swap" option
        if (argc == 4 && strcmp(argv[3], "-swap") == 0)
        {
            swapOption = 1;
        }
    }
    // read the wordlist.txt and
    char **words = readInWords("wordlist.txt");
    // form the graph
    Node **graph = formGraph(words, swapOption);

    // // you can see the adjacency list representation if you want to
    // for (int i = 0; i < 500; i++)
    // {
    //     printf("%s    ", words[i]);
    //     Node *cur = graph[i];
    //     while (cur != NULL)
    //     {
    //         printf("%s ", words[cur->num]);
    //         cur = cur->next;
    //     }
    //     printf("\n");
    // }

    // find path from src to dest
    if (swapOption)
        printf("Swap transformation enabled");
    findPath(src, dest, graph, words);

    return 0;
}
