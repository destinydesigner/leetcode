/**
 * Definition for singly-linked list.
 * struct ListNode {
 *      int val;
 *      ListNode *next;
 *      ListNode(int x) : val(x), next(NULL) {}
 * };
 * */

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int carry = 0, val;

        // Just being careful the pointer usage.
        ListNode *result = NULL, **p = &result;
        while (l2)
        {
            val = l1 ? l1->val : 0;
            *p = new ListNode((val + l2->val + carry) % 10);
            carry = (val + l2->val + carry) / 10;
            p = &(*p)->next;
            l1 = l1 ? l1->next : NULL;
            l2 = l2->next;
            
            if (l2 == NULL)
            {
                l2 = l1;
                l1 = NULL;
            }
        }

        if (carry)
        {
            *p = new ListNode(carry);
        }

        return result;
    }
};

