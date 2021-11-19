#include "header.h"

// read in voting info to a struct
// file name as input and return the vFile structure
vFile readVoting(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        // open file with error
        printf("Open Failed, check if there is a file\n");
        exit(0);
    }
    else
    {
        int candidates, ballots;
        fscanf(fp, "%d %d", &candidates, &ballots);
        vFile votingFile;
        votingFile.candidates = candidates;
        votingFile.ballots = ballots;
        votingFile.remainingColumn = (int *)malloc(sizeof(int) * candidates);
        for (int i = 0; i < candidates; i++)
        {
            // set the remainingColumn as the index of the candidates
            votingFile.remainingColumn[i] = i;
        }

        int **voting = (int **)malloc(sizeof(int *) * ballots);

        // interate to allocate space for each ballot
        for (int i = 0; i < ballots; i++)
        {
            voting[i] = (int *)malloc(sizeof(int) * candidates);
        }

        int row = 0;
        // loop until the end of the file
        while (!feof(fp))
        {
            for (int column = 0; column < candidates; column++)
            {
                // store a number in to the 2-D array
                fscanf(fp, "%d", &voting[row][column]);
            }
            row++;
        }
        votingFile.voting = voting;
        fclose(fp);
        return votingFile;
    }
}

// free the space allocated for voting info
void freeVoting(vFile votingFile)
{
    // free each ballots
    for (int i = 0; i < votingFile.ballots; i++)
    {
        free(votingFile.voting[i]);
    }
    // free the ballot array
    free(votingFile.voting);
    //free the remaining column array
    free(votingFile.remainingColumn);
}

// sort candidats by their points gained using insertion sort
// an array of candidate structure and the length of the array as input
void insertionSort(candidate candArr[], int length)
{
    for (int i = 1; i < length; i++)
    {
        candidate key = candArr[i];
        int j = i - 1;
        for (; j >= 0 && candArr[j].count < key.count; j--)
        {
            candArr[j + 1] = candArr[j];
        }
        candArr[j + 1] = key;
    }
}

// after each iteration we kick out some candidates, change voting detail accordingly
// a parameter in vFile structure and the index of the candidate with the lowest score as input
// return a new vFile structure parameter
vFile modifyVotingFile(vFile votingFile, int minIndex)
{
    vFile votingFileNew;
    votingFileNew.ballots = votingFile.ballots;
    votingFileNew.candidates = votingFile.candidates - 1;
    votingFileNew.remainingColumn = (int *)malloc(sizeof(int) * votingFileNew.candidates);
    // remove the candidate with the lowest score and reset the remainingColumn array
    for (int i = 0; i < votingFileNew.candidates; i++)
    {
        if (i < minIndex)
        {
            votingFileNew.remainingColumn[i] = votingFile.remainingColumn[i];
        }
        else
        {
            // skip the removed index
            votingFileNew.remainingColumn[i] = votingFile.remainingColumn[i + 1];
        }
    }

    int **votingNew = (int **)malloc(sizeof(int *) * votingFileNew.ballots);
    // interate to allocate space for each ballot
    for (int i = 0; i < votingFileNew.ballots; i++)
    {
        votingNew[i] = (int *)malloc(sizeof(int) * votingFileNew.candidates);
    }
    votingFileNew.voting = votingNew;

    for (int i = 0; i < votingFileNew.ballots; i++)
    {
        for (int j = 0; j < votingFileNew.candidates; j++)
        {
            // remove the candidate with the lowest score and create a new voting array
            if (j < minIndex)
            {
                int rank = votingFile.voting[i][j];
                if (rank > votingFile.voting[i][minIndex])
                {
                    votingFileNew.voting[i][j] = rank - 1;
                }
                else
                {
                    votingFileNew.voting[i][j] = rank;
                }
            }
            else
            {
                // skip the removed candidate
                int rank = votingFile.voting[i][j + 1];
                if (rank > votingFile.voting[i][minIndex])
                {
                    votingFileNew.voting[i][j] = rank - 1;
                }
                else
                {
                    votingFileNew.voting[i][j] = rank;
                }
            }
        }
    }
    return votingFileNew;
}

// borda count
// a parameter in vFile structure, detail (whether with d argument), and interation number as input
void bordaCount(vFile votingFile, int detail, int interationNum)
{
    candidate *candArr = (candidate *)malloc(sizeof(candidate) * votingFile.candidates);
    // initialize the candidate array
    for (int i = 0; i < votingFile.candidates; i++)
    {
        candArr[i].index = i;
        candArr[i].count = 0;
    }

    // int *count = (int *)malloc(sizeof(int) * votingFile.candidates);
    // memset(count, 0, sizeof(int) * votingFile.candidates);
    for (int i = 0; i < votingFile.ballots; i++)
    {
        for (int j = 0; j < votingFile.candidates; j++)
        {
            candArr[j].count += votingFile.candidates + 1 - votingFile.voting[i][j];
        }
    }

    // print the status for each iteration
    if (detail)
    {
        printf("Interation#%d:\t", interationNum);
        for (int i = 0; i < votingFile.candidates; i++)
        {
            printf("candidate#%d: %d\t", votingFile.remainingColumn[i], candArr[i].count);
        }
        printf("\n");
    }

    // sort the candidates
    insertionSort(candArr, votingFile.candidates);

    // if we do not get the candidate with the highest score
    if (candArr[0].count == candArr[1].count && candArr[0].count != candArr[votingFile.candidates - 1].count)
    {
        // interativly calling this function
        int min = candArr[votingFile.candidates - 1].count;
        int minIndex = candArr[votingFile.candidates - 1].index;

        vFile votingFileNew = modifyVotingFile(votingFile, minIndex);
        // loop until we have removed all candidate with the same lowest score
        for (int i = votingFile.candidates - 2; i > 0; i--)
        {
            if (candArr[i].count == min)
            {
                int minIndexNew = candArr[i].index;
                votingFileNew = modifyVotingFile(votingFileNew, minIndexNew);
            }
            else
            {
                break;
            }
        }

        bordaCount(votingFileNew, detail, interationNum + 1);
        freeVoting(votingFileNew);
    }
    // if all the candidates have the same scores
    else if (candArr[0].count == candArr[votingFile.candidates - 1].count)
    {
        printf("Winners include ");
        for (int i = 0; i < votingFile.candidates; i++)
        {
            printf("%d ", votingFile.remainingColumn[i]);
        }
        printf("\n");
    }
    // we got the candidate with the highest score
    else
    {
        printf("Winner is %d\n\n", candArr[0].index);
    }
}

// instant runoff
// a parameter in vFile structure, detail (whether with d argument), and interation number as input
void instantRunoff(vFile votingFile, int detail, int interationNum)
{
    int half = votingFile.ballots / 2;

    candidate *candArr = (candidate *)malloc(sizeof(candidate) * votingFile.candidates);
    // initialize the candidate array
    for (int i = 0; i < votingFile.candidates; i++)
    {
        candArr[i].index = i;
        candArr[i].count = 0;
    }

    for (int i = 0; i < votingFile.ballots; i++)
    {
        for (int j = 0; j < votingFile.candidates; j++)
        {
            if (votingFile.voting[i][j] == 1)
            {
                candArr[j].count += 1;
            }
        }
    }
    // print the status for each iteration
    if (detail)
    {
        printf("Interation#%d:\t", interationNum);
        for (int i = 0; i < votingFile.candidates; i++)
        {
            printf("candidate#%d: %d\t", votingFile.remainingColumn[i], candArr[i].count);
        }
        printf("\n");
    }

    // sort the candidates
    insertionSort(candArr, votingFile.candidates);

    // if we get the candidate with the highest score
    if (candArr[0].count > half)
    {
        printf("Winner is %d", votingFile.remainingColumn[candArr[0].index]);
        printf("\n\n");
    }
    // if we do not get the candidate with the highest score
    else
    {
        int min = candArr[votingFile.candidates - 1].count;
        int minIndex = candArr[votingFile.candidates - 1].index;
        vFile votingFileNew = modifyVotingFile(votingFile, minIndex);

        // loop until we have removed all candidate with the same lowest score
        for (int i = votingFile.candidates - 2; i > 0; i--)
        {
            if (candArr[i].count == min)
            {
                int minIndexNew = candArr[i].index;
                votingFileNew = modifyVotingFile(votingFileNew, minIndexNew);
            }
            else
            {
                break;
            }
        }
        instantRunoff(votingFileNew, detail, interationNum + 1);
        freeVoting(votingFileNew);
    }
}
