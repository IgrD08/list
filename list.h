#ifndef LIST_H
#define LIST_H

typedef int listElem_t;
#define SPEC "%d"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const size_t initialCapacity = 10;
const listElem_t POISON      = -67;

struct listNodes_t
{
    listElem_t  data;
    listElem_t  next;
    listElem_t  prev;
};

struct list_t
{
    listNodes_t *nodes;
    size_t      firstFree;
};

enum returnStatus_t
{
    CORRECT_STATUS = 0,
    ERROR_STATUS   = 1
};

returnStatus_t listPushFront   (list_t *list, listElem_t valueToAdd);
returnStatus_t listPushBack    (list_t *list, listElem_t valueToAdd);
returnStatus_t listInsert      (list_t *list, listElem_t position, listElem_t previousPosition, listElem_t valueToAdd);
returnStatus_t listPopFront    (list_t *list);
returnStatus_t listPopBack     (list_t *list);
returnStatus_t listErase       (list_t *list, listElem_t position, listElem_t previousPosition);
returnStatus_t listInit        (list_t *list);
returnStatus_t searchFirstFree (list_t *list);
returnStatus_t listDestroy     (list_t *list);
returnStatus_t listDump        (list_t *list);
returnStatus_t print           (list_t *list);
size_t previousIndex           (list_t *list, listElem_t position);

#endif
