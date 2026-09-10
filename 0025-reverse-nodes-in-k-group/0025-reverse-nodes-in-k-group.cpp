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
    ListNode* reverseKGroup(ListNode* h, int k) {
        ListNode d(0);
        d.next=h;
        ListNode* p=&d;

        while(true){
            ListNode* x=p;
            for(int i=0;i<k&&x;i++) x=x->next;
            if(!x) break;

            ListNode* n=x->next;
            ListNode* a=n;
            ListNode* b=p->next;

            while(b!=n){
                ListNode* t=b->next;
                b->next=a;
                a=b;
                b=t;
            }

            ListNode* t=p->next;
            p->next=x;
            p=t;
        }

        return d.next;
    }
};