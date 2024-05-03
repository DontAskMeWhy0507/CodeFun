#include <iostream>
using namespace std;
struct Node
{
    int value;
    Node* next;
};
void print(Node* head)
{
   Node*  current  = head;
   while (current != NULL)
   {
       cout << current->value << ' ';
       current = current->next;
   }
   cout<< endl;
}

Node* insertHead(Node* head, int value)
{
    Node * newhead = new Node();
    newhead->value = value;
    newhead->next = head;
    return newhead;
}

Node* insertTail(Node* head, int value)
{
    Node* NewTail = new Node();
    NewTail->value = value;
    NewTail->next = NULL;
    if(head == nullptr) head = NewTail;
    else
    {
        Node * tmp = head;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next; 
        }
        tmp -> next = NewTail;
    
    }
    return head;
}

Node* deleteNode(Node* head, int pos)
{
    if(pos == 0)
    {
        Node* tmp = head;
        head = head -> next;
        delete tmp; // delete head
        return head;
    }
    Node* tmp = head;
    while (tmp->next != nullptr)
    {
        pos--;
        if(pos == 0)
        {
            Node* del = tmp->next;
            tmp->next = del->next;
            delete del;
            return head;
        }
        tmp = tmp->next;
    }
    return head;
}



int getValue(Node* head, int pos)
{
    Node* tmp = head;
    if(head -> next == nullptr) return head->value;
    while (tmp->next!=nullptr)
    {
                tmp = tmp -> next;
              pos--;        
        if(pos == 0 )
        {
            int ans = tmp->value;
            return ans;
        }
          
    }
    return 0;
}
int main()
{
    Node* head = NULL;
    head = insertTail(head, 1);
    head = insertTail(head, 2);
    head = insertTail(head, 3);
    head = insertTail(head, 4);
    head = insertTail(head, 5);
    print(head);
    head = insertHead(head, 0);
    print(head);
    head = deleteNode(head, 0);
    print(head);
    cout << getValue(head, 2);
    return 0;
}