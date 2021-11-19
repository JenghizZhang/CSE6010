#include "constructGraph.h"

// read the words from the input file and return a pointer to strings (array of strings)
char **readInWords(char *fileName)
{
    // allocate space for a list of words
    char **words = (char **)malloc(sizeof(char *) * 500);
    // interate to allocate space for each word
    for (int i = 0; i < 500; i++)
    {
        words[i] = (char *)malloc(sizeof(char) * 5);
    }

    // open file and read
    FILE *fp = NULL;
    char buff[5];
    // open the file and read only
    fp = fopen(fileName, "r");
    for (int i = 0; i < 500; i++)
    {
        // interatly assign the words variable based on the file
        fscanf(fp, "%s", buff);
        strcpy(words[i], buff);
    }
    // close file
    fclose(fp);
    return words;
}

// given a list of words and swap option, construct a graph using adjacency list representation
// return a list of Node pointers
Node **formGraph(char *words[], int swapOption)
{
    // graph[i]: the head of the linkedlist which links all of word[i]'s connected words
    Node **graph = (Node **)malloc(sizeof(Node *) * 500);

    // for each node, check the edge and build the adjacency list (loop all words)
    for (int i = 0; i < 500; i++)
    {
        graph[i] = NULL;
        Node *cur = NULL;
        // loop all words to check whether an edge exist between the two words
        for (int j = 0; j < 500; j++)
        {
            // within each iteration, build a linkedlist of connected nodes for a single node(word)
            if (isConnected(i, j, words, swapOption))
            {
                if (graph[i] == NULL)
                {
                    // initiate the first node and let cur points to it
                    graph[i] = newNode;
                    cur = graph[i];
                }
                else
                {
                    // add the node and make the previous node point to it
                    cur->next = newNode;
                    cur = cur->next;
                }
                cur->num = j;
            }
        }
    }
    return graph;
}

// test if two words are connected
// input the index of two words, word list and the swap option
// return 1 if has an edge and 0 if has no edge
int isConnected(int i, int j, char *words[], int swapOption)
{
    // check if two nodes are same
    if (i == j)
    {
        return 0;
    }

    // for non-swap option
    if (swapOption == 0)
    {
        int countDif = 0;
        // iterate each char to count the diff
        for (int m = 0; m < 4; m++)
        {
            // if only 1 diff, return 1
            // else return 0
            if (words[i][m] != words[j][m])
                countDif++;
            if (countDif > 1)
                return 0;
        }
        return 1;
    }
    // for swap option
    else if (swapOption)
    {
        int countDif = 0, dif1 = 0, dif2 = 0;
        // iterate each char to count the diff
        for (int m = 0; m < 4; m++)
        {
            // if only 1 diff, return 1
            // else return 0
            if (words[i][m] != words[j][m])
            {
                countDif++;
                // store the diff char
                if (countDif == 1)
                    dif1 = m;
                else if (countDif == 2)
                    dif2 = m;
                else if (countDif > 2)
                    return 0;
            }
        }
        // check if it changes 1 char or swap two char
        if (countDif == 1 ||
            (countDif == 2 && dif1 + 1 == dif2 && words[i][dif1] == words[j][dif2] && words[i][dif2] == words[j][dif1]))
            return 1;
        else
            return 0;
    }
    return 0;
}
