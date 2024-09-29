

/*
 * Complete the 'insertNodeAtPosition' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER data
 *  3. INTEGER position
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

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    SinglyLinkedListNode *chenvao = new SinglyLinkedListNode(data);
    position--;
   
    SinglyLinkedListNode* cur = llist;
    while(position--)
    {
        cur = cur->next;
    }
    chenvao->next = cur->next;
    cur->next = chenvao;
    
    return llist;
}

//c2 de quy
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    if(position == 0)
    {
        SinglyLinkedListNode* chenvao = new SinglyLinkedListNode(data);
        chenvao->next = llist;
        return chenvao;
    }
    llist->next = insertNodeAtPosition(llist->next, data, position-1);
    return llist;
}