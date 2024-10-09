

/*
 * Complete the 'deleteNode' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER position
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
    SinglyLinkedListNode* tmp = llist;
    if(position == 0)
    {
        SinglyLinkedListNode* tmp = llist;
        llist = llist->next;
        delete tmp;
        return llist;
    }
    while(tmp->next != nullptr)
    {
        position--;
        if(position ==0)
        {
            SinglyLinkedListNode* del = tmp->next;
            tmp->next = del->next;
            delete del;
            return llist;
        }
        tmp = tmp->next;
    }
    return llist;
}

//c2 de quy
SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
    if(position == 0)
    {
        SinglyLinkedListNode* tmp = llist;
        llist = llist->next;
        delete tmp;
        return llist;
    }
    llist->next = deleteNode(llist->next, position-1);
    return llist;
}