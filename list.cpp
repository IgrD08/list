#include "list.h"

returnStatus_t listInit(list_t *list)
{
    list->nodes = (listNodes_t *)calloc(initialCapacity, sizeof(listNodes_t));

    list->nodes[0].data = POISON;
    list->nodes[0].next = 0;
    list->nodes[0].prev = 0;

    for (size_t i = 1; i < initialCapacity; i++)
    {
        list->nodes[i].data = -1;
        list->nodes[i].next = -1;
        list->nodes[i].prev = -1;
    }

    list->firstFree = 1;

    return CORRECT_STATUS;
}

returnStatus_t listPushFront(list_t *list, listElem_t valueToAdd)
{
    if (searchFirstFree(list) == ERROR_STATUS)
        return ERROR_STATUS;

    listElem_t index = list->firstFree;

    list->nodes[index].data = valueToAdd;

    list->nodes[list->nodes[0].prev].next = index;

    list->nodes[index].prev = list->nodes[0].prev;

    list->nodes[index].next = 0;

    list->nodes[0].prev = index;

    return CORRECT_STATUS;
}

returnStatus_t listPushBack(list_t *list, listElem_t valueToAdd)
{
    if (searchFirstFree(list) == ERROR_STATUS)
        return ERROR_STATUS;

    listElem_t index = list->firstFree;

    list->nodes[index].data = valueToAdd;

    list->nodes[index].prev = 0;

    list->nodes[list->nodes[0].next].prev = index;

    list->nodes[index].next = list->nodes[0].next;

    list->nodes[0].next = index;

    return CORRECT_STATUS;
}

returnStatus_t listInsert(list_t *list, listElem_t position, listElem_t previousPosition, listElem_t valueToAdd)
{
    if (searchFirstFree(list) == ERROR_STATUS)
        return ERROR_STATUS;

    listElem_t index = list->firstFree;

    list->nodes[index].data = valueToAdd;

    list->nodes[index].next = list->nodes[previousPosition].next;

    list->nodes[index].prev = previousPosition;

    list->nodes[list->nodes[previousPosition].next].prev = index;

    list->nodes[previousPosition].next = index;

    return CORRECT_STATUS;
}

returnStatus_t listPopFront(list_t *list)
{
    listElem_t index = list->nodes[0].prev;

    list->nodes[list->nodes[index].prev].next = 0;

    list->nodes[0].prev = list->nodes[index].prev;

    list->nodes[index].data = -1;

    list->nodes[index].next = -1;

    list->nodes[index].prev = -1;

    return CORRECT_STATUS;
}

returnStatus_t listPopBack(list_t *list)
{
    listElem_t index = list->nodes[0].next;

    list->nodes[list->nodes[index].next].prev = 0;

    list->nodes[0].next = list->nodes[index].next;

    list->nodes[index].data = -1;

    list->nodes[index].next = -1;

    list->nodes[index].prev = -1;

    return CORRECT_STATUS;
}

returnStatus_t listErase(list_t *list, listElem_t position, listElem_t previousPosition)
{
    list->nodes[list->nodes[position].prev].prev = list->nodes[position].prev;

    list->nodes[previousPosition].next = list->nodes[position].next;

    list->nodes[position].data = -1;

    list->nodes[position].next = -1;

    list->nodes[position].prev = -1;

    return CORRECT_STATUS;
}

returnStatus_t searchFirstFree(list_t *list)//TODO - not good
{
    bool flag = 0;

    list->firstFree = 0;

    for (size_t i = 1; i < initialCapacity && flag == 0; i++)
    {
        if (list->nodes[i].prev == (size_t)0.0-1)
        {
            flag = 1;

            list->firstFree = i;

            return CORRECT_STATUS;
        }
    }

    fprintf(stderr, "List full\n");

    return ERROR_STATUS;
}

returnStatus_t listDestroy(list_t *list)
{
    free(list->nodes);

    return CORRECT_STATUS;
}

returnStatus_t listDump(list_t *list)
{
    printf("#\t\tdata\t\tnext\t\tprev\n");

    for (size_t i = 0; i < initialCapacity; i++)
    {
        printf("%zu\t\t" SPEC "\t\t" SPEC "\t\t" SPEC "\n", i, list->nodes[i].data, list->nodes[i].next, list->nodes[i].prev);
    }

    return CORRECT_STATUS;
}

returnStatus_t print(list_t *list)
{
    size_t i = list->nodes[0].next;

    for (; i != 0; i = list->nodes[i].next)
    {
        printf(SPEC " ", list->nodes[i].data);
    }

    printf(SPEC " ", list->nodes[i].data);

    printf("\n");

    return CORRECT_STATUS;
}

size_t previousIndex(list_t *list, listElem_t position)
{
    size_t i = 0;

    for (; i < position - 1; i = list->nodes[i].next);

    return i;
}
