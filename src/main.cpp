#include "../include/list.h"

returnStatus_t printMenu(list_t *list);

int main()
{
    if (fileOpening(&logFile, "logs/img/graphDumpHtml.htm", "w") == 1)
        return 1;

    fprintf(logFile, "<pre>");

    list_t list = {};

    if (listInit(&list) != CORRECT_STATUS)
        return 1;

    printMenu(&list);

    listDestroy(&list);

    if (closeFile(&logFile) == 1)
        return 1;

    return 0;
}


returnStatus_t printMenu(list_t *list)
{
    bool flag = 1;
    int callNumber = 0;

    do
    {
        printf("\033[34mEnter a number from 0 to 2.\n"
               "0 - add to front\n"
               "1 - add to back\n"
               "2 - add element to position\n"
               "3 - delete from front\n"
               "4 - delete from back\n"
               "5 - delete element from position\n"
               "6 - print\n"
               "7 - dump list\n"
               "8 - exit the program\033[0m\n"
              );

        if (scanf("%d", &callNumber) != 1)
        {
            while (getchar() != '\n');
            continue;
        }

        switch (callNumber)
        {
            case 0:
            {
                int value = 0;

                scanf(SPEC, &value);

                listPushFront(list, value);
            }

                break;

            case 1:
            {
                int value = 0;

                scanf(SPEC, &value);

                listPushBack(list, value);
            }

                break;

            case 2:
            {
                int value = 0, position = 0;

                scanf(SPEC SPEC , &position, &value);

                listInsert(list, position, value);
            }

                break;

            case 3:

                listPopFront(list);

                break;

            case 4:

                listPopBack(list);

                break;

            case 5:
            {
                int position = 0;

                scanf(SPEC, &position);

                listErase(list, position);
            }

                break;

            case 6:

                print(list);

                break;

            case 7:

                listDump(list);

                break;

            case 8:

                flag = 0;

                break;

            default:

                break;
        }

    }while(flag);

    return CORRECT_STATUS;
}
