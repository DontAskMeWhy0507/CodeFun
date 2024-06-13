#include <iostream>
using namespace std;

/*
Node* deleteDuplicates(Node* head)
{
    if (head == NULL)
        return head;
    Node *current = head;
    while (current->next != NULL)
    {
        if (current->value == current->next->value)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
            current = current->next;
    }
    
    return head;
}

Node* insert(Node* head, int value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    // If the list is empty or the new value is smaller than the head value
    if (head == nullptr || value < head->value) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    return head;
}
*/





/*
print reverse
void printReverse(Node* head)
{
    if (head == NULL)
        return;
    printReverse(head->next);
    cout << head->value << " ";
}
/*void printReverse(Node* head)
{
   Node* reverse = nullptr;
   Node* tmp = head;
   while (tmp!= nullptr)
   {
      Node* temp = new Node();
      temp ->value = tmp->value;
      temp ->next = reverse;
      reverse = temp;
      tmp = tmp->next;
   }
    Node* tmp2 = reverse;
    while (tmp2!= nullptr)
    {
        cout << tmp2->value << " ";
        tmp2 = tmp2->next;
    }
}*/





/*
//Viết hàm Node* concat(vector<Node*> heads); nhận đầu vào là một vector chứa các node
 đầu tiên của 1 tập các danh sách liên kết, nối các danh sách liên kết đầu vào thành 1 danh sách liên kết mới và trả về node
 đầu tiên của danh sách liên kết mới đó.
 
void assign(Node** head, Node* temp) {
    Node** tail = head; // dung node** de thay doi gia tri va giu gia tri
    while (*tail) {
        tail = &((*tail)->next); // tro den nut cuoi cung
        // ko dung *tail = (*tail)->next vi ta ko muon thay doi node hien tai 
    }
    while (temp != NULL) {
        Node* newNode = new Node; // tao nut moi
        newNode->value = temp->value; // gan gia tri
        newNode->next = NULL; 
        *tail = newNode; // them vao cuoi danh sach
        tail = &(newNode->next); // tail tro den vi tri con tro next (ko phai gia tri)
        temp = temp->next; //dich temp
    }
}

Node* concat(vector<Node*> heads)
{
    Node* res = NULL;
    for (int i = 0; i < (int)heads.size(); i++) {
        assign(&res, heads[i]);
    }
    return res;
}
*/




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



/*
Node* convert(Node* head)
{
    if(head == nullptr) return head;
    Node* pSlow = head, *pFast = head;
    Node* preSlow = nullptr;
    while(pFast!=NULL)
    {
        preSlow = pSlow;
        pSlow = pSlow->next;
        pFast = pFast->next->next;
    }
    Node* a = head;
    Node* b = pSlow;
    preSlow->next = nullptr;
    while(b!=nullptr)
    {
        Node* tmp = a->next;
        a->next = b;
        b = b->next;
        a = a->next;
        a->next = tmp;
        a = a->next;
        
    }
    return head;
}*/