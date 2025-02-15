//C1
void printLinkedList(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* tmp = head;
    while(tmp!=nullptr)
    {
        std::cout << tmp->data << std::endl;
        tmp = tmp->next;
    }
    

}

//C2
void printLinkedList(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* tmp = head;
    for(;tmp!=nullptr;tmp=tmp->next)
    {
        std::cout << tmp->data << std::endl;
    }
    

}

