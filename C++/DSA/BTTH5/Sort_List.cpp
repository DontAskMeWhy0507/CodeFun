
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        
        auto left = head, right = head;

        int len = 0;
        for (auto i = head; i; i = i ->next) ++len;
        if(len <= 1) return head;
        for (int i = 0; i < len/2 - 1; ++i ) right = right ->next;
        auto tmp = right -> next;
        right -> next = nullptr;
        right = tmp;

        left = sortList(left);
        right = sortList(right);
        return merge(left,right);
    }
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode dummy;
        ListNode* tail = &dummy;

        while (a && b) {
            if (a->val < b->val) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }

        // Attach the remaining elements
        if (a) tail->next = a;
        if (b) tail->next = b;

        return dummy.next;
    }
};