<<<<<<< HEAD
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* ans = new ListNode(0);
        ListNode* current = ans;
        while( list1 && list2)
        {
            if(list1->val > list2->val)
            {
                current->next = list2;
                list2 = list2 -> next;
            }
            else
            {
                current->next = list1;
                list1 = list1 -> next;
            }
            current = current -> next;
        }
        current-> next = list1 ? list1 : list2;
        return ans -> next;
=======
class Solution {
public:
    bool isValid(string s) {
        stack <char> st;
        for(char c: s)
        {
            if(c=='[' || c == '{' || c == '(')
            {
                st.push(c);
            }
            else
            {
                if  (st.empty() ||
                    (c == ')' && st.top() != '(') ||
                    (c == ']' && st.top() != ']') ||
                    (c == '}' && st.top() != '}')
                ) return false;
                st.pop();
            }
        }
                    return st.empty();

>>>>>>> 53fd8e330602366f9fb3856809c9d1c362419e1c
    }
};