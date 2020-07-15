/* mymemory.c
 * 
 * provides interface to memory management
 * 
 */
// Created by: Stefan Nikolov
// Student ID: 51768275
// Student at University of Aberdeen
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "mymemory.h"

// our memory
Byte mymemory[MAXMEM];
Segment_t *segmenttable = NULL;

void initialize()
{
   printf("initialize> start\n");
   // set memory to 0
   memset(mymemory, '\0', sizeof(MAXMEM));

   // create segment table
   // contains one segment description that declares the whole memory
   // as one free segment
   //
   // create a single segment descriptor

   // segmenttable = (void *)mymemory;
   segmenttable = (void *)malloc(sizeof(Segment_t));
   segmenttable->allocated = FALSE;
   segmenttable->start = (void *)mymemory;
   segmenttable->size = sizeof(mymemory);
   segmenttable->next = NULL;
   // initialise the segment

   printf("initialize> end\n");
}

void *mymalloc(size_t size)
{
   printf("mymalloc> start\n");

   // implement the mymalloc functionality
   // Create a new segment descriptor
   Segment_t *free = findFree(segmenttable, size);
   if (free != NULL && free->size > size)
   {
      Segment_t *new = (void *)(malloc(sizeof(Segment_t)));
      insertAfter(free, new);
      new->allocated = FALSE;
      new->start = free->start + size;
      new->size = free->size - size;
      free->allocated = TRUE;
      free->size = size;
      return (void *)(free->start);
   }
   return NULL;

   printf("mymalloc> ends\n");
}

void myfree(void *ptr)
{
   printf("myfree> start\n");
   Segment_t *toRemove = findSegment(segmenttable, ptr);
   // This just "frees up" the memory in mymemory
   // of whatever was stored in the segment
   // but the segment still remains in the list
   memset(ptr, '\0', toRemove->size);
   toRemove->allocated = FALSE;
   printf("myfree> ends\n");
}

void mydefrag(void **ptrlist)
{
   printf("mydefrag> start\n");

   Segment_t *freeDesc = segmenttable;
   int len = 0;
   while (freeDesc->next != NULL)
   {
      len++;
      freeDesc = freeDesc->next;
   }

   Segment_t *previous = NULL;
   Segment_t *currentSegment = NULL;
   int j = 0;
   while (currentSegment != freeDesc)
   {
      currentSegment = findSegment(segmenttable, ptrlist[j]);
      if (j > 0)
      {
         previous = findSegment(segmenttable, ptrlist[j - 1]);
      }
      if (currentSegment->allocated == FALSE && currentSegment != freeDesc)
      {
         if (previous)
         {
            freeDesc->size += currentSegment->size;
            previous->next = currentSegment->next;
            Segment_t *border = previous->next;
            while (border)
            {
               border->start = border->start - currentSegment->size;
               border = border->next;
            }
            j--;
         }
         else
         {
            // Having issues with segmentation faults
            // when trying to defrag after removing the first segment
            // and the faults occur right after the first print statement
            // I could not figure out how to solve them.
         }
      }
      j++;
   }

   printf("doing this in mydefrag\n");

   for (int i = 0; i < len; i++)
   {
      if (*(char *)ptrlist[i] == '\0')
      {
         for (int j = i + 1; j < len; j++)
         {
            strcpy(ptrlist[j - 1], (char *)ptrlist[j]);
            memset(ptrlist[j], '\0', findSegment(segmenttable, ptrlist[j])->size);
         }
      }
   }

   printf("mydefrag> finish \n");
}

void *moveSegment(Segment_t *list, Segment_t *toMove)
{
   printf("movesegment> start\n");

   printf("movesegment> end\n");
}

// // helper functions for management segmentation table
Segment_t *findFree(Segment_t *list, size_t size)
{
   while (list->allocated == TRUE || list->size <= size)
   {
      if (list->next == NULL)
      {
         return NULL;
      }
      else
      {
         list = list->next;
      }
   }
   return (Segment_t *)list;
}

void insertAfter(Segment_t *oldSegment, Segment_t *newSegment)
{
   newSegment->next = oldSegment->next;
   oldSegment->next = newSegment;
}

Segment_t *findSegment(Segment_t *list, void *ptr)
{
   Segment_t *current = list;

   while (current->start != ptr)
   {
      current = current->next;
   }
   if (current)
   {
      return (void *)current;
   }
   else
   {
      return NULL;
   }
}

int isPrintable(int c)
{
   if (c >= 0x20 && c <= 0x7e)
      return c;

   return 0;
}

void printmemory()
{
   for (int i = 0; i < MAXMEM; i++)
   {
      if (i == 0)
      {
         printf(" [%4d]", i);
      }
      if (i % 10 == 0 && i != 0)
      {
         printf(" | ");
         for (int j = 10; j > 0; j--)
         {
            if (isPrintable(mymemory[i - j]))
            {
               printf("%c", mymemory[i - j]);
            }
            else
            {
               printf(".");
            }
         }
         printf("\n [%4d]", i);
      }
      printf(" %02x ", mymemory[i]);
   }
   printf("\n");
}

void printsegmenttable()
{
   int i = 0;
   // Create a currentseg variable so we don't accidentaly modify the original table
   Segment_t *currentSegment = segmenttable;

   while (currentSegment)
   {
      printf("Segment %d\n", i);
      printf("\tallocated = %s\n", (currentSegment->allocated == FALSE ? "FALSE" : "TRUE"));
      printf("\tstart     = %p\n", currentSegment->start);
      printf("\tsize      = %lu\n", currentSegment->size);
      i++;
      currentSegment = currentSegment->next;
   }
}

void printsegmentdescriptor(Segment_t *descriptor)
{
   printf("\tallocated = %s\n", (descriptor->allocated == FALSE ? "FALSE" : "TRUE"));
   printf("\tstart     = %p\n", descriptor->start);
   printf("\tsize      = %lu\n", descriptor->size);
}
