// Created by: Stefan Nikolov
// Student ID: 51768275
// Student at University of Aberdeen

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "mymemory.h"

int main()
{
    printf("$shell> start\n");
    initialize();

    printmemory();
    printsegmenttable();

    printf("$shell> end\n");
    return 0;
}