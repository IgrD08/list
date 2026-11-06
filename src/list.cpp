#include "../include/list.h"
#include "../include/listVerify.h"

returnStatus_t listInit(list_t *list)
{
    list->nodes = (listNodes_t *)calloc(initialCapacity, sizeof(listNodes_t));

    if (printListVerify(list, allocationCheck(list->nodes)) == ALLOCATION_ERROR)
    {
        return ALLOCATION_ERROR;
    }

    list->nodes[0].data = POISON;
    list->nodes[0].next = 0;
    list->nodes[0].prev = 0;

    for (size_t i = 1; i < initialCapacity; i++)
    {
        list->nodes[i].data = -1;
        list->nodes[i].next = (ssize_t)i + 1;
        list->nodes[i].prev = -1;
    }

    list->nodes[initialCapacity - 1].next = 0;

    list->free = 1;

    list->listSize = 1;

    return CORRECT_STATUS;
}

returnStatus_t listPushFront(list_t *list, listElem_t valueToAdd)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    ssize_t index = list->free;

    list->free = list->nodes[index].next;

    list->nodes[index].data = valueToAdd;

    list->nodes[index].next = 0;

    list->nodes[index].prev = list->nodes[0].prev;

    list->nodes[list->nodes[0].prev].next = index;

    list->nodes[0].prev = index;

    #ifdef LIST_DEBUG
        LOG("List after adding <<%zu>> to head:", list->nodes[index].data);

        graphDump(list);
    #endif

    list->listSize++;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    return CORRECT_STATUS;
}

returnStatus_t listPushBack(list_t *list, listElem_t valueToAdd)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    ssize_t index = list->free;

    list->free = list->nodes[index].next;

    list->nodes[index].data = valueToAdd;

    list->nodes[index].prev = 0;

    list->nodes[list->nodes[0].next].prev = index;

    list->nodes[index].next = list->nodes[0].next;

    list->nodes[0].next = index;

    #ifdef LIST_DEBUG
        LOG("List after adding <<%zu>> to tail:", list->nodes[index].data);

        graphDump(list);
    #endif

    list->listSize++;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    return CORRECT_STATUS;
}

returnStatus_t listInsert(list_t *list, ssize_t position, listElem_t valueToAdd)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    ssize_t index = list->free;

    list->free = list->nodes[index].next;

    list->nodes[index].data = valueToAdd;

    list->nodes[index].next = list->nodes[position].next;

    list->nodes[index].prev = position;

    list->nodes[list->nodes[position].next].prev = index;

    list->nodes[position].next = index;

    #ifdef LIST_DEBUG
        LOG("List after adding <<%zu>> to <<%zu>> position:", list->nodes[index].data, position);

        graphDump(list);
    #endif

    list->listSize++;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    return CORRECT_STATUS;
}

returnStatus_t listPopFront(list_t *list)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    ssize_t index = list->nodes[0].prev;

    list->nodes[list->nodes[index].prev].next = 0;

    list->nodes[0].prev = list->nodes[index].prev;

    list->nodes[index].data = -1;

    list->nodes[index].next = list->free;

    list->nodes[index].prev = -1;

    list->free = index;

    #ifdef LIST_DEBUG
        LOG("List after deleting <<%zu>> from head:", index);

        graphDump(list);
    #endif

    list->listSize--;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    return CORRECT_STATUS;
}

returnStatus_t listPopBack(list_t *list)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    ssize_t index = list->nodes[0].next;

    list->nodes[list->nodes[index].next].prev = 0;

    list->nodes[0].next = list->nodes[index].next;

    list->nodes[index].data = -1;

    list->nodes[index].next = list->free;

    list->nodes[index].prev = -1;

    list->free = index;

    #ifdef LIST_DEBUG
        LOG("List after deleting <<%zu>> from tail:", index);

        graphDump(list);
    #endif

    list->listSize--;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    return CORRECT_STATUS;
}

returnStatus_t listErase(list_t *list, ssize_t position)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    ssize_t prev = list->nodes[position].prev;
    ssize_t next = list->nodes[position].next;

    list->nodes[prev].next = next;

    list->nodes[next].prev = prev;

    list->nodes[position].data = -1;

    list->nodes[position].prev = -1;

    list->nodes[position].next = list->free;

    list->free = position;

    #ifdef LIST_DEBUG
        LOG("List after deleting <<%zu>> from <<%zd>> position:", list->nodes[position].data, position);

        graphDump(list);
    #endif

    list->listSize--;

    if ((flag = printListVerify(list, listVerify(list))) != CORRECT_STATUS)
    {
        return flag;
    }

    return CORRECT_STATUS;
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
        printf("%zu\t\t" SPEC "\t\t%zd\t\t%zd\n", i, list->nodes[i].data, list->nodes[i].next, list->nodes[i].prev);
    }

    return CORRECT_STATUS;
}

returnStatus_t print(list_t *list)
{
    ssize_t i = list->nodes[0].next;

    for (; i != 0; i = list->nodes[i].next)
    {
        printf(SPEC " ", list->nodes[i].data);
    }

    printf(SPEC " ", list->nodes[i].data);

    printf("\n");

    return CORRECT_STATUS;
}

returnStatus_t graphDump(list_t *list)
{
    FILE *filePointer = NULL;

    time_t timeInSeconds = time(NULL);

    tm *parsedTime = localtime(&timeInSeconds);

    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    long millis = ts.tv_nsec / 1000000;

    char time[64] = {};
    strftime(time, sizeof(time), "%Y%m%d%H%M%S", parsedTime);

    char command[256];
    char fileName[256];
    snprintf(fileName, sizeof(fileName), "logs/img/%s%ld.dot", time, millis);

    filePointer = fopen(fileName, "w");

    fprintf(filePointer, "digraph\n{\n\trankdir = \"LR\";\n");

    fprintf(filePointer, "\tnode[shape = Mrecord; style = filled;];\nedge[ color = \"#008000\";];\n");

    fprintf(filePointer, "\tnode0[label=\"index = 0 | value = " SPEC " | {<prev> prev = %zd | <next> next = %zd}\"];\n",
            list->nodes[0].data, list->nodes[0].prev, list->nodes[0].next);

    for (size_t i = 1; i < initialCapacity; i++)
    {
        fprintf(filePointer, "\tnode%zu[label=\"index = %zu | value = " SPEC " | {<prev> prev = %zd | <next> next = %zd}\";",
                i, i, list->nodes[i].data, list->nodes[i].prev, list->nodes[i].next);

        if (i != 0)
        {
            fprintf(filePointer, "fillcolor = \"#C0FFC0\"; color = \"#008000\";");
        }

        if (list->nodes[i].prev == -1)
        {
            fprintf(filePointer, "fillcolor = \"#f9ff82\"; color = \"#c0b900\";");
        }

        fprintf(filePointer, "];\n");
    }

    for (size_t i = 0; i + 1 < initialCapacity; i++)
    {
        fprintf(filePointer, "\tnode%zu -> node%zu [style = invis, weight = 1000];\n", i, i + 1);
    }

    for (ssize_t i = list->free; list->nodes[i].next != 0; i = list->nodes[i].next)
    {
        fprintf(filePointer, "\tnode%zd -> node%zd [color = \"#c0b900\";];\n", i, list->nodes[i].next);
    }

    for (size_t i = 0; i < initialCapacity; i++)
    {
        if (list->nodes[i].next >= 0 && list->nodes[i].next < (ssize_t)initialCapacity && list->nodes[i].prev != -1)
        {
            fprintf(filePointer, "\tnode%zu:<next> -> node%zd:<prev> [dir = both, constraint = false];\n", i, list->nodes[i].next);
        }
    }

    fprintf(filePointer, "}\n");

    fclose(filePointer);

    snprintf(command, sizeof(command), "dot -Tpng logs/img/%s%ld.dot -o logs/img/%s%ld.png", time, millis, time, millis);

    system(command);

    fprintf(logFile, "<img src= %s%ld.png width = 1500px>\n", time, millis);

    return CORRECT_STATUS;
}
