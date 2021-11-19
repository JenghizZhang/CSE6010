#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "./ballots1.txt"
// #define FILENAME "./ballots2.txt"
// #define FILENAME "./ballots3.txt"

typedef struct vFile
{
    int candidates;
    int ballots;
    int **voting;
    int *remainingColumn; // remaining column for iteration
} vFile;

typedef struct candidate
{
    int count;
    int index;
} candidate;

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
            votingFile.remainingColumn[i] = i;
        }

        int **voting = (int **)malloc(sizeof(int *) * ballots);

        // interate to allocate space for each ballot
        for (int i = 0; i < ballots; i++)
        {
            voting[i] = (int *)malloc(sizeof(int) * candidates);
        }

        int row = 0;
        while (!feof(fp))
        {
            for (int column = 0; column < candidates; column++)
            {
                fscanf(fp, "%d", &voting[row][column]);
            }
            row++;
        }
        votingFile.voting = voting;
        fclose(fp);
        return votingFile;
    }
}

void freeVoting(vFile votingFile)
{
    for (int i = 0; i < votingFile.ballots; i++)
    {
        free(votingFile.voting[i]);
    }
    free(votingFile.voting);
    free(votingFile.remainingColumn);
}

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

vFile modifyVotingFile(vFile votingFile, int minIndex)
{
    vFile votingFileNew;
    votingFileNew.ballots = votingFile.ballots;
    votingFileNew.candidates = votingFile.candidates - 1;
    votingFileNew.remainingColumn = (int *)malloc(sizeof(int) * votingFileNew.candidates);
    for (int i = 0; i < votingFileNew.candidates; i++)
    {
        if (i < minIndex)
        {
            votingFileNew.remainingColumn[i] = votingFile.remainingColumn[i];
        }
        else
        {
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

void bordaCount(vFile votingFile, int detail, int interationNum)
{
    candidate *candArr = (candidate *)malloc(sizeof(candidate) * votingFile.candidates);
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

    if (detail)
    {
        printf("Interation#%d:\t", interationNum);
        for (int i = 0; i < votingFile.candidates; i++)
        {
            printf("candidate#%d: %d\t", votingFile.remainingColumn[i], candArr[i].count);
        }
        printf("\n");
    }

    insertionSort(candArr, votingFile.candidates);

    if (candArr[0].count == candArr[1].count && candArr[0].count != candArr[votingFile.candidates - 1].count)
    {
        // interativly calling this function
        int min = candArr[votingFile.candidates - 1].count;
        int minIndex = candArr[votingFile.candidates - 1].index;

        vFile votingFileNew = modifyVotingFile(votingFile, minIndex);
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
    else if (candArr[0].count == candArr[votingFile.candidates - 1].count)
    {
        printf("Winners include ");
        for (int i = 0; i < votingFile.candidates; i++)
        {
            printf("%d ", votingFile.remainingColumn[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Winner is %d\n", candArr[0].index);
    }
}

void instantRunoff(vFile votingFile, int detail, int interationNum)
{
    int half = votingFile.ballots / 2;

    candidate *candArr = (candidate *)malloc(sizeof(candidate) * votingFile.candidates);
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

    if (detail)
    {
        printf("Interation#%d:\t", interationNum);
        for (int i = 0; i < votingFile.candidates; i++)
        {
            printf("candidate#%d: %d\t", votingFile.remainingColumn[i], candArr[i].count);
        }
        printf("\n");
    }

    insertionSort(candArr, votingFile.candidates);

    if (candArr[0].count > half)
    {
        printf("Winner is %d", votingFile.remainingColumn[candArr[0].index]);
        printf("\n");
    }
    else
    {
        int min = candArr[votingFile.candidates - 1].count;
        int minIndex = candArr[votingFile.candidates - 1].index;
        vFile votingFileNew = modifyVotingFile(votingFile, minIndex);

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

int main(int argc, char *argv[])
{
    vFile votingFile = readVoting(FILENAME);

    if (argc == 1)
    {
        printf("Default:\n");
        printf("Method pair1: Borda Count\n");
        bordaCount(votingFile, 0, 1);
        printf("Method pair1: Instant Runoff\n");
        instantRunoff(votingFile, 0, 1);
    }
    else if (argc == 2 && strcmp(argv[1], "d") == 0)
    {
        printf("Description:\n");
        printf("Method pair1: Borda Count\n");
        bordaCount(votingFile, 1, 1);
        printf("Method pair1: Instant Runoff\n");
        instantRunoff(votingFile, 1, 1);
    }
    else
    {
        printf("Wrong argument\n");
    }

    freeVoting(votingFile);
    return 0;
}