

/*
 * Complete the 'getNode' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER positionFromTail
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

int getNode(SinglyLinkedListNode* llist, int positionFromTail) {
    int n = 0;
    SinglyLinkedListNode* cur1 = llist;
    SinglyLinkedListNode* cur = llist;
    while(cur1!= nullptr) {
        n++;
        cur1 = cur1 -> next;
    }
    while(n--)
    {
        if(n==positionFromTail) return cur->data;
        cur = cur-> next;
    }
    return 0;
}

//c2 de quy
int getNode(SinglyLinkedListNode* llist, int positionFromTail) {
    if(llist == nullptr) return 0;
    int index = getNode(llist->next, positionFromTail) + 1;
    if(index == positionFromTail) return llist->data;
    return 0;
}