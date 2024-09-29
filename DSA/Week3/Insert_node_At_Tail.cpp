
using namespace std;
// Complete the insertNodeAtTail function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

//c1
SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
    SinglyLinkedListNode *tail = new SinglyLinkedListNode(data);
        if(head == nullptr) return tail;

    SinglyLinkedListNode * cur = head;
    
    while(cur->next!=nullptr)
    {
        cur = cur->next;
    }
    cur->next = tail;
    return head;
}

//c2 de quy
SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
    if(head == nullptr) return new SinglyLinkedListNode(data);
    head->next = insertNodeAtTail(head->next, data);
    return head;
}



