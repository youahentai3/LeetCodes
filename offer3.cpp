#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct TreeNode 
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct RandomListNode 
{
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution 
{
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) 
    {
        if(pushV.empty() && popV.empty())
            return true;
        if(pushV.empty() || popV.empty())
            return false;

        stack<int> sta;
        auto ite=popV.cbegin();

        for(int a : pushV)
        {
            sta.push(a);
            while(!sta.empty() && ite!=popV.cend())
            {
                if(*ite==sta.top())
                {
                    ite++;
                    sta.pop();
                }
                else
                    break;
            }
        }

        return sta.empty() && ite==popV.cend();
    }

    bool vsBST_core(vector<int>& vec,int be,int en)
    {
        if(be>=en)
            return true;
        int root=vec[en];
        int mid=be;

        int i=be;
        while(vec[i++]<=root && i<en)
            ;
        mid=i;
        while(i<=en-1)
        {
            if(vec[i++]<root)
                return false;
        }
        //cout<<mid<<endl;
        return vsBST_core(vec,be,mid-1) && vsBST_core(vec,mid,en-1);
    }

    bool VerifySquenceOfBST(vector<int> sequence) 
    {
        if(sequence.empty())
            return false;
        
        return vsBST_core(sequence,0,sequence.size()-1);
    }

    void find_path_core(vector<vector<int> >& vecc,vector<int>& vec,TreeNode* root,int sum,int target)
    {
        vec.push_back(root->val);
        sum+=root->val;
        if(!(root->left) && !(root->right))
        {
            if(sum==target)
            {
                vecc.push_back(vec);
            }
            vec.pop_back();
            return;
        }
        if(root->left)
        {
            find_path_core(vecc,vec,root->left,sum,target);
        }
        if(root->right)
        {
            find_path_core(vecc,vec,root->right,sum,target);
        }
        vec.pop_back();
        return;
    }

    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) 
    {
        vector<vector<int> > vecc;
        vector<int> vec;
        if(!root)
            return vecc;
        int sum=0;
        find_path_core(vecc,vec,root,sum,expectNumber);

        return vecc;
    }

    RandomListNode* Clone(RandomListNode* pHead)
    {   
        if(!pHead)
            return nullptr;
        RandomListNode* nHead=nullptr;
        RandomListNode* p1=pHead;
        RandomListNode* p2=nullptr;

        while(p1)
        {
            RandomListNode* te=p1->next;
            p1->next=new RandomListNode(p1->label);
            p1->next->next=te;
            //p1->next->random=p1->random;
            p1=te;
        }
        p1=pHead;
        while(p1)
        {
            if(p1->random)
                p1->next->random=p1->random->next;
            else
                p1->next->random=nullptr;
            //RandomListNode* te=p1->next;
            //p1->next=p1->next->next;
            p1=p1->next->next;
        }

        p1=pHead;
        while(p1)
        {
            if(!p2)
            {
                p2=p1->next;
                nHead=p2;
            }
            else 
            {
                p2->next=p1->next;
                p2=p2->next;
            }
            p1->next=p1->next->next;
            p1=p1->next;
        }

        return nHead;
    }

    void convert_core(TreeNode* root,TreeNode*& pre,TreeNode*& head)
    {
        if(root->left)
            convert_core(root->left,pre,head);
        if(pre)
        {
            pre->right=root;
            root->left=pre;
        }
        else 
        {
            head=root;
            //root->left=root;
        }
        pre=root;
        if(root->right)
            convert_core(root->right,pre,head);
    }

    TreeNode* Convert(TreeNode* pRootOfTree)
    {   
        if(!pRootOfTree)
            return nullptr;
        
        TreeNode* head=nullptr;
        TreeNode* pre=nullptr;
        convert_core(pRootOfTree,pre,head);
        pre->right=head;
        head->left=pre;

        return head;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        if(!root)
            return "$";
        return to_string(root->val)+" "+serialize(root->left)+" "+serialize(root->right);   
    }

    TreeNode* deserialize_core(stringstream& data)
    {
        string str;
        if(!(data>>str))
            return nullptr;
        if(str=="$")
            return nullptr;

        TreeNode* root=new TreeNode(stoi(str));
        root->left=deserialize_core(data);
        root->right=deserialize_core(data);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {    
        stringstream dat(data);
        return deserialize_core(dat);
    }

    void swap(int& a,int& b)
    {
        a=a^b;
        b=a^b;
        a=a^b;
    }

    void swap(char& a,char& b)
    {
        auto te=a;
        a=b;
        b=te;
    }

    unordered_set<char> set;
    void permutation_core(vector<string>& vec, string& s,int k)
    {
        if(k==s.size())
        {
            vec.push_back(s);
            return;
        }
        unordered_set<char> set;
        for(int i=k;i<s.size();i++)
        {
            if(set.insert(s[i]).second)
            {
//                set.insert(s[i]);
                swap(s[k],s[i]);
                permutation_core(vec,s,k+1);
                swap(s[k],s[i]);
                //set.erase(s[i]);
            }
        }
    }

    vector<string> permutation(string s) 
    {
        vector<string> vec;
        if(s.empty())
            return vec;
        permutation_core(vec,s,0);
        return vec;
    }

    int partition(vector<int>& nums,int p,int r)
    {
        int ind=rand()%(r-p+1)+p;
        std::swap(nums[ind],nums[r]);

        int k=p;
        for(int i=p;i<r;i++)
        {
            if(nums[i]<nums[r])
                std::swap(nums[k++],nums[i]);
        }
        std::swap(nums[k],nums[r]);

        return k;
    }

    int size1;
    int majot_core(vector<int>& nums,int p,int r)
    {
        int q=partition(nums,p,r);
        if(q==size1)
            return nums[q];
        else if(q<size1)
            return majot_core(nums,q+1,r);
        else 
            return majot_core(nums,p,q-1);
    }

    int majorityElement(vector<int>& nums) 
    {
        int cou=1,a=nums[0];
        for(auto ite=nums.begin()+1;ite!=nums.end();ite++)
        {
            if(*ite==a)
                cou++;
            else 
            {
                cou--;
                if(!cou)
                {
                    a=*ite;
                    cou++;
                }
            }
        }
        return a;
        /*size1=nums.size()/2;
        int p=0,r=nums.size()-1;
        int q=partition(nums,p,r);
        while(q!=size1)
        {
            if(q<size1)
            {
                p=q+1;
            }
            else 
                r=q-1;
            q=partition(nums,p,r);
        }
        return nums[q];*/
        //return majot_core(nums,0,nums.size()-1);
    }

    vector<int> getLeastNumbers(vector<int>& arr, int k) 
    {
        vector<int> re;
        if(!k)
            return re;
        if(k>arr.size())
            return arr;
        int p=0,r=arr.size()-1;
        int q=partition(arr,p,r);
        while(q!=k-1)
        {
            if(q<k)
            {
                p=q+1;
            }
            else 
                r=q-1;
            q=partition(arr,p,r);
        }
        vector<int> re(arr.begin(),arr.begin()+q+1);
        return re;
    }

    vector<int> min_heap,max_heap;
    bool fflag=true;
    void addNum(int num) 
    {
        if(!fflag)
        {
            if(!max_heap.empty() && max_heap[0]>num)
            {
                max_heap.push_back(num);
                push_heap(max_heap.begin(),max_heap.end(),[](const int& a,const int& b){return a<b;});
                num=max_heap[0];
                pop_heap(max_heap.begin(),max_heap.end(),[](const int& a,const int& b){return a<b;});
                max_heap.pop_back();
            }
            min_heap.push_back(num);
            push_heap(min_heap.begin(),min_heap.end(),[](const int& a,const int& b){return a>b;});
        }
        else 
        {
            if(!min_heap.empty() && min_heap[0]<num)
            {
                min_heap.push_back(num);
                push_heap(min_heap.begin(),min_heap.end(),[](const int& a,const int& b){return a>b;});
                num=min_heap[0];
                pop_heap(min_heap.begin(),min_heap.end(),[](const int& a,const int& b){return a>b;});
                min_heap.pop_back();
            }
            max_heap.push_back(num);
            push_heap(max_heap.begin(),max_heap.end(),[](const int& a,const int& b){return a<b;});
        }
        fflag=!fflag;
    }
    
    double findMedian() 
    {
        if(!fflag)
        {
            return (max_heap.size()>min_heap.size() ? max_heap[0] : min_heap[0]);
        }
        else 
        {
            if(!min_heap.empty() && !max_heap.empty())
                return (min_heap[0]+max_heap[0])/2.0;
            return -1;
        }
    }
};

int main()
{
    Solution solution;
    vector<int> vec;
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        int te;
        cin>>te;
        vec.push_back(te);
    }
    cout<<solution.VerifySquenceOfBST(vec);

    return 0;
}