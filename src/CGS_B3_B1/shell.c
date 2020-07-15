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

    char *ptr1 = (char *)mymalloc(50);
    strcpy(ptr1, "this test1");
    printf("shell> content of allocated memory: %s\n", ptr1);

    char *ptr2 = (char *)mymalloc(50);
    strcpy(ptr2, "this test2");
    printf("shell> content of allocated memory: %s\n", ptr2);

    char *ptr3 = (char *)mymalloc(50);
    strcpy(ptr3, "this test3");
    printf("shell> content of allocated memory: %s\n", ptr3);

    printmemory();
    printsegmenttable();

    myfree(ptr2);

    printmemory();
    printsegmenttable();

    printf("$shell> end\n");
    return 0;
}