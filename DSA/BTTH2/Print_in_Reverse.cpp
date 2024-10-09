

/*
 * Complete the 'reversePrint' function below.
 *
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
//c1
using namespace std;
void reversePrint(SinglyLinkedListNode* llist) {
    if(llist == nullptr) return;
    reversePrint(llist->next);
        cout << llist->data<<endl;

    
}
//c2
void reversePrint(SinglyLinkedListNode* llist) {
    stack<int> s;
    while(llist != nullptr){
        s.push(llist->data);
        llist = llist->next;
    }
    while(!s.empty()){
        cout << s.top()<<endl;
        s.pop();
    }
}

