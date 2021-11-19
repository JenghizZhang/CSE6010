#include <limits.h>
#include "dijkstra.h"

// use dijkstra's algorithm to calculate shortest path
// input includes the src and dest word indexs, graph, and words list
void findPath(int src, int dest, Node *graph[], char *words[])
{
    Vertice Q[500];
    Vertice S[500];
    int SSize = 0, QSize = 500;

    // initialize Q for all words in the word list
    // set distance to infinity and pre vertice to -1
    for (int i = 0; i < 500; i++)
    {
        Q[i].num = i;
        if (i != src)
        {
            Q[i].d = INT_MAX;
        }
        else
        {
            Q[i].d = 0;
        }
        Q[i].pre = -1;
    }

    int hashMap[500];
    // iterate until all vertice in Q has been added to S
    while (QSize > 0)
    {
        // u = vertex in Q with minimum value of u.d
        // S = S U u; Q = Q –u;
        // build the priority queue
        buildPQ(Q, QSize);
        // pop out the vertice with minumum distance
        Vertice u = pop(Q, QSize);
        // add u to S
        S[SSize] = u;
        QSize--;
        SSize++;

        // how to find a vertex in S: id-->index
        hashMap[u.num] = SSize - 1;

        // For each vertex 𝑤∈𝑄 where (𝑢,𝑤)∈𝐸 Relax (u,w);
        // start of the adjacency list of u
        Node *w = graph[u.num];
        // iterate until all the edges of the new added vertice
        while (w != NULL)
        {
            int spot = -1;
            // check whether there is
            if (find(w->num, Q, QSize, &spot))
            {
                relax(&u, &Q[spot]);
            }
            w = w->next;
        }
    }

    // print the result
    printResult(S, SSize, words, src, dest, hashMap);
}

// set the distance of the vertice as the minimum value
// input include two pointers to vertice
void relax(Vertice *u, Vertice *v)
{
    if (u->d == INT_MAX)
        return;
    // if the new path has smaller dist, reset the dist valu
    if (u->d + 1 < v->d)
    {
        v->d = u->d + 1;
        v->pre = u->num;
    }
}

// find a vertex from a PQ using the given id , if found, pass out the spot in the PQ
// input includes the id of the vertice, vertice array, size of the array and the spot as index
// return whether we find the vertice
int find(int id, Vertice Q[], int qsize, int *pSpot)
{
    // iterate all vertice in Q to find the vertice with the input id
    for (int i = 0; i < qsize; i++)
    {
        if (Q[i].num == id)
        {
            *pSpot = i;
            return 1;
        }
    }
    return 0;
}

// print the result
// input includes the vertice array S and its size, word list, src and dest word, and a hash map to map the word from S
void printResult(Vertice S[], int SSize, char* words[], int src, int dest, int hashMap[])
{
    // print shortest path
    printf("\nThe shortest path from \"%s\" to \"%s\" is:\n", words[src], words[dest]);
    int curId = dest;
    char *ans[500];
    // num of vertice to go to this dest
    int i = 0;
    // interate all vetices in the path
    while (curId != -1)
    {
        // get the vertice according to the index
        Vertice cur = S[hashMap[curId]];
        curId = cur.num;
        // right now we are going in reverse order, need to store the words first
        ans[i++] = words[curId];
        curId = cur.pre;
    }

    // print in the right order
    if (i == 1)
    {
        // if it only has 1 in the path to the dest, it means there is no viable path to the dest
        printf("No viable Path!!!\n");
    }
    else
    {
        printf("The number of transformation is %d\n", i-1);
        // reversly iterate the ans array to print the words
        for (i -= 1; i > 0; i--)
        {
            printf("%s-->", ans[i]);
        }
        printf("%s\n", ans[0]);
    }

    // print out the total number of words that are “reachable” from the specified source word
    // and the average number of transformations needed to reach the reachable words
    int cnt = 0;
    float avgDist = 0;
    // iterate all vertices
    for (int i = 0; i < SSize; i++)
    {
        // if the dist is infinity, it is unreachable
        if (S[i].d != INT_MAX)
        {
            avgDist += S[i].d;
            cnt++;
        }
    }
    cnt -= 1;   // remove the word itself
    if(cnt!=0)
        avgDist /= cnt;
    printf("\nThe total number of words that are “reachable” from \"%s\" is: %d\n", words[src], cnt);
    printf("The average number of transformations needed is: %.1f\n\n", avgDist);
}

/*
The rest are Priority queue operations
*/

// adjust the tree under node "index" to be a min-heap (priority queue)
// size is the heap size
void adjust(Vertice arr[], int size, int index)
{
    int left = 2 * index + 1;  // left son of index
    int right = 2 * index + 2; // right son of index

    int minIdx = index;
    // check whether parent vertice or its children has the smallest dist
    if (left < size && arr[left].d < arr[minIdx].d)
        minIdx = left;
    if (right < size && arr[right].d < arr[minIdx].d)
        minIdx = right;

    // if the minimum index is not the parent's index, we need to swap the value with it's child
    if (minIdx != index)
    {
        // swap
        Vertice temp = arr[minIdx];
        arr[minIdx] = arr[index];
        arr[index] = temp;
        adjust(arr, size, minIdx);
    }
}

// build a priority Queue given an array of random elements
// input include vertice array and size of array
void buildPQ(Vertice arr[], int size)
{
    // adjust one by one, starting from the first non-leaf node, right-to-left, down-to-top
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        adjust(arr, size, i);
    }
}

// pop the min element
// input includes vertice array and size of array
// return the poped vertice
Vertice pop(Vertice arr[], int size)
{
    // delete the min element, put the last one on top, then adjust
    Vertice u = arr[0];
    arr[0] = arr[size - 1];
    return u;
}