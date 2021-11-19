#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "./ballots1.txt"

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef struct vFile
{
    int candidates; // number of candidates
    int ballots;    // number of ballots
    int **voting;   // 2d matrix of voting detail
    int *remainingColumn; // remaining column for iteration
} vFile;

typedef struct candidate
{
    int count; // overall score
    int index;
} candidate;
