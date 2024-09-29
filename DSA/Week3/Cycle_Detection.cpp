

// Complete the has_cycle function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
bool has_cycle(SinglyLinkedListNode* head) {
    if (head == nullptr) return false;

    SinglyLinkedListNode* slow = head;
    SinglyLinkedListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // Move slow by one step
        fast = fast->next->next;    // Move fast by two steps

        if (slow == fast) {
            return true;  // Cycle detected
        }
    }

    return false;  // No cycle
}


//c2 de quy
bool has_cycle(SinglyLinkedListNode* head) {
    if (head == nullptr) return false;

    SinglyLinkedListNode* slow = head;
    SinglyLinkedListNode* fast = head;

    if (fast->next == nullptr || fast->next->next == nullptr) {
        return false;
    }

    if (slow == fast) {
        return true;
    }

    return has_cycle(slow->next, fast->next->next);
}