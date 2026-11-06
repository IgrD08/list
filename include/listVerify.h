#ifndef LIST_VERIFY_H
#define LIST_VERIFY_H

returnStatus_t listVerify(list_t *list);
returnStatus_t printListVerify(list_t *list, returnStatus_t flag);
returnStatus_t logListError(list_t *list, returnStatus_t flag);

returnStatus_t allocationCheck(listNodes_t *pointer);
returnStatus_t essentialCheck(list_t *list);
returnStatus_t changingZeroElement(list_t *list);

#endif
