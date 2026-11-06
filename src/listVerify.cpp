#include "../include/list.h"
#include "../include/listVerify.h"

returnStatus_t listVerify(list_t *list)
{
    returnStatus_t flag = CORRECT_STATUS;

    if ((flag = allocationCheck(list->nodes)) != CORRECT_STATUS) return flag;

    if ((flag = essentialCheck(list)) != CORRECT_STATUS) return flag;

    if ((flag = changingZeroElement(list)) != CORRECT_STATUS) return flag;

    return CORRECT_STATUS;
}

returnStatus_t allocationCheck(listNodes_t *pointer)
{
    if (pointer == NULL)
        return ALLOCATION_ERROR;

    return CORRECT_STATUS;
}

returnStatus_t essentialCheck(list_t *list)
{
    if (list->listSize == 0 || list->listSize > initialCapacity)
    {
        return LIST_STRUCTURE_ERROR;
    }

    if (list->free < 1 || list->free >= (ssize_t)initialCapacity)
    {
        return INCORRECT_NEXT_FREE;
    }

    ssize_t current = list->nodes[0].next;
    size_t count = 1;
    ssize_t prev = 0;

    while (current != 0)
    {
        if (current < 0 || list->nodes[current].prev == -1)
        {
            return LIST_STRUCTURE_ERROR;
        }

        if (list->nodes[current].prev != prev)
        {
            return LIST_STRUCTURE_ERROR;
        }

        count++;

        if (count > list->listSize)
        {
            return LIST_STRUCTURE_ERROR;
        }

        prev = current;

        current = list->nodes[current].next;
    }

    if (list->nodes[0].prev != prev || count != list->listSize)
    {
        return LIST_STRUCTURE_ERROR;
    }

    size_t countFree = 0;
    ssize_t currentFree = list->free;

    while (currentFree != 0)
    {
        if (currentFree < 1 || currentFree >= (ssize_t)initialCapacity)
        {
            return INCORRECT_NEXT_FREE;
        }

        if (list->nodes[currentFree].prev != -1)
        {
            return LIST_STRUCTURE_ERROR;
        }

        countFree++;

        if (countFree > initialCapacity - 1)
        {
            return INCORRECT_NEXT_FREE;
        }

        currentFree = list->nodes[currentFree].next;
    }

    return CORRECT_STATUS;
}

returnStatus_t changingZeroElement(list_t *list)
{
    if (list->nodes[0].data != POISON)
        return CHANGING_ZERO_ELEMENT;

    return CORRECT_STATUS;
}

returnStatus_t printListVerify(list_t *list, returnStatus_t flag)
{
    if (flag == CORRECT_STATUS && list != NULL)
    {
        return CORRECT_STATUS;
    }

    return logListError(list, flag);
}

returnStatus_t logListError(list_t *list, returnStatus_t flag)
{
    FILE *filePointer = NULL;
    if (fileOpening(&filePointer, "logs/errors.log", "w") != 0)
    {
        return FILE_ERROR;
    }

    returnStatus_t status = ERROR_STATUS;
    bool needDump = false;

    if (list == NULL)
    {
        fprintf(filePointer, "ERROR: The list was created incorrectly\n");
    }
    else
    {
        switch (flag)
        {
            case ALLOCATION_ERROR:

                fprintf(filePointer, "ERROR: incorrect allocation\n");

                return ALLOCATION_ERROR;

                break;

            case INCORRECT_NEXT_FREE:

                fprintf(filePointer, "ERROR: no more free objects\n");

                return INCORRECT_NEXT_FREE;

                break;

            case LIST_STRUCTURE_ERROR:

                fprintf(filePointer, "ERROR: incorrect structure of list\n");

                return LIST_STRUCTURE_ERROR;

                break;

            case CHANGING_ZERO_ELEMENT:

                fprintf(filePointer, "ERROR: attempt to change zero element\n");

                return CHANGING_ZERO_ELEMENT;

                break;

            default:
                break;
        }

        if (needDump)
        {
            listDump(list);
        }
    }

    if (closeFile(&filePointer) != 0)
    {
        return FILE_ERROR;
    }

    return status;
}


bool fileOpening(FILE **fp, const char *fileName, const char *fileFlag)
{
    if ((*fp = fopen(fileName, fileFlag)) == NULL)
    {
        fprintf(stderr, "ERROR: Failed to open file %s\n", fileName);

        return 1;
    }

    return 0;
}

bool closeFile(FILE **fp)
{
    if (fclose(*fp) == EOF)
    {
        fprintf(stderr, "ERROR: Failed to close file\n");

        return 1;
    }

    return 0;
}
