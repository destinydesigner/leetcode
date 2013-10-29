/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    // Cycle detection
    bool hasCycle(ListNode *head) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        ListNode *fp = head, *sp = head;
        while(fp && fp->next)
        {
            fp = fp->next->next;
            sp = sp->next;
            if (fp == sp)
                return true;
        }
        return false;
    }
};
