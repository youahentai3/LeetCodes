#include <iostream>

using namespace std;

struct ListNode 
{
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution
{
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(!pHead)
            return nullptr;
        ListNode* p1=pHead,*p2=pHead;

        while (p1 && p2)
        {
            p1=p1->next;
            p2=p2->next;
            if(p2)
                p2=p2->next;
            if(p1==p2)
                break;
        }
        
        if(!p2)
            return nullptr;

        int n=1;
        p1=p1->next;
        while (p1!=p2)
        {
            n++;
            p1=p1->next;
        }
        
        p1=pHead;
        p2=pHead;
        while (n--)
        {
            p2=p2->next;
        }
        
        while (p1!=p2)
        {
            p1=p1->next;
            p2=p2->next;
        }
        
        return p1;
    }

    ListNode* ReverseList(ListNode* pHead) 
    {
        ListNode* p=pHead;
        ListNode* p1=nullptr;
        ListNode* p2=nullptr;

        while(p)
        {
            p2=p->next;
            if(!p1)
                p->next=nullptr;
            else
                p->next=p1;
            p1=p;
            p=p2;
        }

        return p1;
    }

    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        //递归
        if(!pHead1 && !pHead2)
            return nullptr;
        if(!pHead2)
            return pHead1;
        if(!pHead1)
            return pHead2;

        ListNode* head=nullptr;
        if(pHead1->val>pHead2->val)
        {
            head=pHead2;
            head->next=Merge(pHead1,pHead2->next);
        }
        else
        {
            head=pHead1;
            head->next=Merge(pHead1->next,pHead2);
        }

        return head;
        //非递归
        /*if(!pHead1 && !pHead2)
            return nullptr;
        if(!pHead2)
            return pHead1;
        if(!pHead1)
            return pHead2;

        ListNode* head=nullptr;
        ListNode* p=nullptr;    
        ListNode* p1=pHead1;
        ListNode* p2=pHead2;
        while(p1 && p2)
        {
            ListNode* minp=nullptr;
            if(p1->val>p2->val)
            {
                minp=p2;
                p2=p2->next;
            }
            else
            {
                minp=p1;
                p1=p1->next;
            }
            
            if(!p)
            {
                p=minp;
                head=p;
            }
            else
            {
                p->next=minp;
               // cout<<p->val<<" ";
                p=p->next;
            }
        }

        ListNode* p3=nullptr;
        if(p1)
            p3=p1;
        else if(p2)
            p3=p2;

        while (p3)
        {
          // cout<<p->val<<" ";
            p->next=p3;
            p3=p3->next;
            p=p->next;
        }
           
        return head;*/
    }
};

ListNode* add_node(ListNode* head,int val)
{
    if(!head)
    {
        head=new ListNode(val);
        return head;
    }

    ListNode* p=head;
    while (p->next)
    {
        p=p->next;
    }
    p->next=new ListNode(val);

    return head;
}

ListNode* create_list(ListNode* head,int n)
{
    for(int i=0;i<n;i++)
    {
        int val;
        cin>>val;
        head=add_node(head,val);
    }
    return head;
}

void print_list(ListNode* head)
{
    ListNode* p=head;
    while (p)
    {
        cout<<p->val<<" ";
        p=p->next;
    }
    cout<<endl;
}

int main()
{
    int n;
    cin>>n;
    ListNode* head1=nullptr;
    ListNode* head2=nullptr;
    head1=create_list(head1,n);
    print_list(head1);
    head2=create_list(head2,n);
    print_list(head2);
    head1=(new Solution())->Merge(head1,head2);
    print_list(head1);

    return 0; 
}