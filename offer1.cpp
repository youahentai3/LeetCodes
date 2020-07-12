#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct ListNode 
{
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
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

    bool HasSubtree_core(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot2)
            return true;
        if(!pRoot1)
            return false;
        
        if(pRoot1->val==pRoot2->val)
        {
            bool flag=HasSubtree_core(pRoot1->left,pRoot2->left) && HasSubtree_core(pRoot1->right,pRoot2->right);
            if(flag)
                return true;
        }
        return HasSubtree_core(pRoot1->left,pRoot2) || HasSubtree_core(pRoot1->right,pRoot2);
    }

    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot1 || !pRoot2)
            return false;
        return HasSubtree_core(pRoot1,pRoot2);
    }

    void Mirror(TreeNode *pRoot) 
    {
        if(!pRoot)
            return;
        
        Mirror(pRoot->left);
        Mirror(pRoot->right);
        TreeNode* te=pRoot->left;
        pRoot->left=pRoot->right;
        pRoot->right=te;
    }

    bool isSymmetrical_core(TreeNode* pRoot1,TreeNode* pRoot2)
    {
        if(!pRoot1 && !pRoot2)
            return true;
        if(!pRoot1 || !pRoot2)
            return false;
        
        if(pRoot1->val!=pRoot2->val)
            return false;
        /*TreeNode* te=pRoot2->left;
        pRoot2->left=pRoot2->right;
        pRoot2->right=te;*/
        return isSymmetrical_core(pRoot1->left,pRoot2->right) && isSymmetrical_core(pRoot1->right,pRoot2->left);
    }

    bool isSymmetrical(TreeNode* pRoot)
    {
        if(!pRoot)
            return true;
        return isSymmetrical_core(pRoot->left,pRoot->right);
    }
    
    vector<int> printMatrix(vector<vector<int> > matrix) 
    {
        vector<int> vec;
        return vec;
    }
    
    vector<int> PrintFromTopToBottom(TreeNode* root) 
    {
        vector<int> vec;
        if(!root)
            return vec;
        queue<TreeNode*> que;
        que.push(root);

        while(!que.empty())
        {
            TreeNode* p=que.front();
            vec.push_back(p->val);
            que.pop();
            if(p->left)
                que.push(p->left);
            if(p->right)
                que.push(p->right);
        }

        return vec;
    }

    vector<vector<int> > Print2(TreeNode* pRoot) 
    {    
        vector<vector<int> > vec;
        vector<int> vecc;
        if(!pRoot)
            return vec;
        int pren=1,nren=0;
        queue<TreeNode*> que;
        que.push(pRoot);

        while(!que.empty())
        {
            TreeNode* p=que.front();
            vecc.push_back(p->val);
            que.pop();
            if(p->left)
            {
                que.push(p->left);
                nren++;
            }
            if(p->right)
            {
                que.push(p->right);
                nren++;
            }
            if(!(--pren))
            {
                pren=nren;
                nren=0;
                vec.push_back(vecc);
                vecc.clear();
            }
        }

        return vec;
    }

    vector<vector<int> > Print(TreeNode* pRoot) 
    {
        vector<vector<int> > vec;
        vector<int> vecc;
        if(!pRoot)
            return vec;
        int pren=1,nren=0,cur=0;
        stack<TreeNode*> sta[2];
        sta[0].push(pRoot);

        while(!sta[0].empty() || !sta[1].empty())
        {
            TreeNode* p=sta[cur].top();
            vecc.push_back(p->val);
            sta[cur].pop();

            TreeNode* first;
            TreeNode* second;
            if(cur)
            {
                first=p->right;
                second=p->left;
            }
            else
            {
                first=p->left;
                second=p->right;
            }
            if(first)
            {
                sta[!cur].push(first);
                nren++;
            }
            if(second)
            {
                sta[!cur].push(second);
                nren++;
            }
            if(!(--pren))
            {
                cur=!cur;
                pren=nren;
                nren=0;
                vec.push_back(vecc);
                vecc.clear();
            }
        }

        return vec;
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
    

    return 0; 
}