

/*
 * Complete the 'reverse' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
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

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    if(llist == nullptr || llist->next == nullptr) return llist;
    
    auto rev = reverse(llist->next);    
    //reverse llist from the second entry
    
    auto node_one = llist -> next;
    node_one->next = llist;
    llist->next = nullptr;
    return rev;
    
    
}

//c2 khong dung de quy
SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    SinglyLinkedListNode* prev = nullptr;
    SinglyLinkedListNode* cur = llist;
    SinglyLinkedListNode* next = nullptr;
    while(cur != nullptr){
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}