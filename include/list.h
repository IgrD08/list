#ifndef LIST_H
#define LIST_H

typedef int listElem_t;
#define SPEC "%d"

#define LIST_DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "../include/logger.h"

const size_t     initialCapacity = 10;
const listElem_t POISON          = -67;

struct listNodes_t
{
    listElem_t  data;
    ssize_t     next;
    ssize_t     prev;
};

struct list_t
{
    listNodes_t *nodes;
    ssize_t     free;
    size_t      listSize;
};

enum returnStatus_t
{
    CORRECT_STATUS        = 0,
    ERROR_STATUS          = 1,
    ALLOCATION_ERROR      = 2,
    INCORRECT_NEXT_FREE   = 3,
    LIST_STRUCTURE_ERROR  = 4,
    FILE_ERROR            = 5,
    CHANGING_ZERO_ELEMENT = 6
};

returnStatus_t listPushFront   (list_t *list, listElem_t valueToAdd);
returnStatus_t listPushBack    (list_t *list, listElem_t valueToAdd);
returnStatus_t listInsert      (list_t *list, ssize_t position, listElem_t valueToAdd);
returnStatus_t listPopFront    (list_t *list);
returnStatus_t listPopBack     (list_t *list);
returnStatus_t listErase       (list_t *list, ssize_t position);
returnStatus_t listInit        (list_t *list);
returnStatus_t listDestroy     (list_t *list);
returnStatus_t listDump        (list_t *list);
returnStatus_t print           (list_t *list);
returnStatus_t graphDump       (list_t *list);
bool fileOpening               (FILE **fp, const char *fileName, const char *fileFlag);
bool closeFile                 (FILE **fp);

#endif
