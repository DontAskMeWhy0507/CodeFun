Node* addLastNode (Node* head, int value)
{
    Node* newnode = head;
    Node* tmp = new Node();
    tmp->value = value;
    tmp->nextNode = nullptr;
    if(head == nullptr)
    {
        head = tmp;
        return head;
    }
    while(newnode->nextNode  !=nullptr)
    {
        newnode = newnode->nextNode;
    }
    newnode->nextNode =  tmp;
    return head;
}