#include "header.h"

// for detailed info, print beatpath
void printBeatPath(int **beatPath, int numCandidates)
{
    printf("BeatPath:\n");
    for(int i=0; i<numCandidates; i++)
    {
        for(int j=0; j<numCandidates; j++)
        {
            printf("%d  ", beatPath[i][j]);
        }
        printf("\n");
    }
}

// after knowing candidate scores, rank them and print result
void printResult(float *points, int numCandidates, int detail)
{
    // print out detailed points each candidates got
    if(detail)
    {
        for(int i=0; i<numCandidates; i++)
            printf("candidate#%d: %1.1fpoints\n", i, points[i]);
    }
    // find max number of points among candidates
    float maxWins = 0;
    for(int i=0; i<numCandidates; i++)
    {
        maxWins = maxWins > points[i] ? maxWins : points[i];
    }
    // find winners with that max number of points
    int *winnerIdxes =  (int*)malloc(sizeof(int) * numCandidates);
    for(int i=0; i<numCandidates; i++)
    {
        // -1 means not a winner
        winnerIdxes[i] = -1;
    }
    int j = 0;
    for(int i=0; i<numCandidates; i++)
    {
        if(points[i] == maxWins)
            winnerIdxes[j++] = i;
    }
    // print winners
    printf("winner(s) is(are):  ");
    for(int i=0; i<numCandidates; i++)
    {
        if(winnerIdxes[i] != -1)
            printf("%d ", winnerIdxes[i]);
    }
    printf("\n\n");

    free(winnerIdxes);

}

// pairwise
void pairWise(vFile votingFile, int detail)
{
    int ** votes = votingFile.voting;
    int numCandidates = votingFile.candidates;
    int numVoters =  votingFile.ballots;

    // create an array to store candidates' information
    float *points = (float*)malloc(sizeof(float) * numCandidates);
    // initialize to all 0
    for(int i=0; i<numCandidates; i++)
        points[i] = 0;

    for(int candi = 0; candi< numCandidates; candi++)
        for(int candj = candi+1; candj< numCandidates; candj++)
        {
            // compare the number of voters who rank candidate i before j and 
            // the number of voters who favor candidate j over i 
            int iOutRankJ=0, jOutRankI = 0;
            for(int voter = 0; voter<numVoters; voter++)
            {
                if(votes[voter][candi] < votes[voter][candj])
                    iOutRankJ++;
                else if(votes[voter][candi] > votes[voter][candj])
                    jOutRankI++;
            }
            if(iOutRankJ > jOutRankI)
                // i wins, +1 point
                points[candi]+= 1;
            else if(iOutRankJ < jOutRankI)
                // j wins, +1 point
                points[candj]+= 1;
            else
            {
                // A tie gives both candidates 0.5 points
                points[candi]+= 0.5;
                points[candj]+= 0.5;
            }
        }
    printResult(points, numCandidates, detail);

    free(points);
}

// perform multiplications to find all pairs shortest path (A^N-1)
void multiPly(int **A, int **beatPath, int numCandidates)
{
    for(int i = 0; i<numCandidates; i++)
        for(int j = 0; j< numCandidates; j++)
        {
            beatPath[i][j] = A[i][j];
        }
    int exp = 1;
    while(exp < numCandidates-1)
    {
        // beatpath = beatpath^2

        // copy beatPath to A
        for(int i = 0; i<numCandidates; i++)
            for(int j = 0; j< numCandidates; j++)
            {
                A[i][j] = beatPath[i][j];
            }
        // new beatPath = A^2
        for(int i = 0; i< numCandidates; i++)
            for(int j = 0; j< numCandidates; j++)
            {
                for(int k=0; k<numCandidates; k++)
                {
                    if(k==i || k==j)
                        continue;
                    beatPath[i][j] = max( beatPath[i][j], min(A[i][k], A[k][j]));
                }
            }

        exp*= 2; 
    }

    // for(int cnt = 0; cnt<numCandidates-1; cnt++)
    // {
    //     for(int i = 0; i< numCandidates; i++)
    //         for(int j = 0; j< numCandidates; j++)
    //         {
    //             for(int k=0; k<numCandidates; k++)
    //             {
    //                 if(k==i || k==j)
    //                     continue;
    //                 beatPath[i][j] = max( beatPath[i][j], min(beatPath[i][k], beatPath[k][j]));
    //             }
    //         }
    // }

    return;
}

// schulzeBeatPath
void schulzeBeatPath(vFile votingFile, int detail)
{
    int ** votes = votingFile.voting;
    int numCandidates = votingFile.candidates;
    int numVoters =  votingFile.ballots;

    // create a 2D array for matrix multiplication
    int **A = (int**)malloc(sizeof(int*) * numCandidates);
    for(int i=0; i<numCandidates; i++)
    {
        A[i] = (int*)malloc(sizeof(int) * numCandidates);
    }
    // initialize A
    for(int candi = 0; candi< numCandidates; candi++)
        for(int candj = candi; candj< numCandidates; candj++)
        {
            // diagonal line == 0
            if(candi == candj)
                A[candi][candj] = 0;
            // compare the number of voters who rank candidate i before j and 
            // the number of voters who favor candidate j over i 
            int iOutRankJ=0, jOutRankI = 0;
            for(int voter = 0; voter<numVoters; voter++)
            {
                if(votes[voter][candi] < votes[voter][candj])
                    iOutRankJ++;
                else if(votes[voter][candi] > votes[voter][candj])
                    jOutRankI++;
            }
            if(iOutRankJ > jOutRankI)
            {
                // i wins
                A[candi][candj] = iOutRankJ - jOutRankI;
                A[candj][candi] = 0;
            }
            else if(iOutRankJ <= jOutRankI)
            {
                // j wins or ties
                A[candj][candi] = jOutRankI - iOutRankJ;
                A[candi][candj] = 0;
            }
        }

    int ** beatPath = (int**)malloc(sizeof(int*) * numCandidates);
    for(int i=0; i<numCandidates; i++)
    {
        beatPath[i] = (int*)malloc(sizeof(int) * numCandidates);
    }
    // calc the final beatPath matrix
    multiPly(A, beatPath, numCandidates);

    // create an array to store candidates' information
    float *points = (float*)malloc(sizeof(float) * numCandidates);
    // initialize to all 0
    for(int i=0; i<numCandidates; i++)
        points[i] = 0;

    // calc final points for every one
    for(int i = 0; i< numCandidates; i++)
        for(int j = i+1; j< numCandidates; j++)
        {
            // compare the stronger beatPath 
            if(beatPath[i][j] > beatPath[j][i])
            {
                // i wins
                points[i] += 1;
            }
            else if(beatPath[i][j] < beatPath[j][i])
            {
                // j wins
                points[j] += 1;
            }
            else{
                // ties
                points[i] += 0.5;
                points[j] += 0.5;
            }
        }
    
    // print result
    if(detail)
        printBeatPath(beatPath, numCandidates);
    printResult(points, numCandidates, detail);
    free(A);
    free(beatPath);
    free(points);
}