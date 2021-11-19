#include "header.h"

// read in voting info to a struct
// file name as input and return the vFile structure
extern vFile readVoting(char *fileName);

// free the space allocated for voting info
extern void freeVoting(vFile votingFile);

// sort candidats by their points gained using insertion sort
// an array of candidate structure and the length of the array as input
extern void insertionSort(candidate candArr[], int length);

// after each iteration we kick out some candidates, change voting detail accordingly
// a parameter in vFile structure and the index of the candidate with the lowest score as input
// return a new vFile structure parameter
extern vFile modifyVotingFile(vFile votingFile, int minIndex);

// borda count
// a parameter in vFile structure, detail (whether with d argument), and interation number as input
extern void bordaCount(vFile votingFile, int detail, int interationNum);

// instant runoff
// a parameter in vFile structure, detail (whether with d argument), and interation number as input
extern void instantRunoff(vFile votingFile, int detail, int interationNum);

// pair wise comparison
// a parameter in vFile structure and detail (whether with d argument) as input
extern void pairWise(vFile votingFile, int detail);

// pair schulzeBeatPath comparison
// a parameter in vFile structure and detail (whether with d argument) as input
extern void schulzeBeatPath(vFile votingFile, int detail);

// ***************************************************************************

int main(int argc, char *argv[])
{
    vFile votingFile = readVoting(FILENAME);

    // default
    if (argc == 1)
    {
        // do 4 comparition algorithms
        printf("Default:\n");
        printf("Method pair1: Borda Count\n");
        bordaCount(votingFile, 0, 1);
        printf("Method pair1: Instant Runoff\n");
        instantRunoff(votingFile, 0, 1);
        
        printf("Method pair2: Pairwise Comparison\n");
        pairWise(votingFile, 0);
        printf("Method pair2: Schulze Beatpath\n");
        schulzeBeatPath(votingFile, 0);
    }
    // with "d" argument
    else if (argc == 2 && strcmp(argv[1], "d") == 0)
    {
        // do 4 comparition algorithms
        printf("Description:\n");
        printf("Method pair1: Borda Count\n");
        bordaCount(votingFile, 1, 1);
        printf("Method pair1: Instant Runoff\n");
        instantRunoff(votingFile, 1, 1);
        printf("Method pair2: Pairwise Comparison\n");
        pairWise(votingFile, 1);
        printf("Method pair2: Schulze Beatpath\n");
        schulzeBeatPath(votingFile, 1);
    }
    else
    {
        printf("Wrong argument\n");
    }

    freeVoting(votingFile);
    return 0;
}