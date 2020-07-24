#include <string>
#include <cstring>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <memory>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };

 struct TreeNode 
 {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution
{
public:
    int maxSubArray(vector<int>& nums) 
    {
        if(nums.empty())
            return 0;

        int max_val=nums[0],val=nums[0];
        for(auto ite=nums.begin()+1;ite!=nums.end();ite++)
        {
            if(val+*ite<*ite)
                val=*ite;
            else 
                val+=*ite;
            if(val>max_val)
                max_val=val;
        }
        return max_val;
    }

    int countDigitOne(int n) 
    {
        long long re=0;
        long long a=n/10,b=n%10,c=n,d=0;
        long long digit=1;
        while(a || b)
        {
           // cout<<b<<" "<<d<<endl;
            if(!b)
            {
                re+=a*digit;
            }
            else if(b==1)
            {
                re+=a*digit+d+1;
            }
            else 
            {
                re+=(a+1)*digit;
            }
            d+=b*digit;
            n/=10;
            digit*=10;
            a=n/10;
            b=n%10;
        }

        return re;
    }

    int findNthDigit(int n) 
    {
        long long a=10,b=1,c=0;
        while(n>a)
        {
            b++;
            n-=a;
            if(c)
                c*=10;
            else
                c=10;
            a=b*9*c;
        }

        //cout<<n<<endl;
        int d=(n)/b;
        int e=(n)%b;
        int re=c+d;
        //cout<<to_string(re)<<endl;

        return to_string(re)[e]-'0';
    }

    static bool compare1(const string& s1,const string& s2)
    {
        string str1=s1+s2,str2=s2+s1;
        return str1<str2;
    }

    string minNumber(vector<int>& nums) 
    {
        vector<string> snums;
        for(auto a : nums)
            snums.push_back(to_string(a));
        sort(snums.begin(),snums.end(),compare1);

        string re;
        for(auto str : snums)
            re+=str;
        return re;
    }

    int translateNum(int num) 
    {
        string str=to_string(num);
        unique_ptr<int[]> ptr(new int[str.size()+1]);

        ptr[0]=1;
        ptr[1]=1;
        for(int i=2;i<=str.size();i++)
        {
            //if(i>)
            {
                if(str[i-2]=='1' || str[i-1]<'6' && str[i-2]=='2')
                    ptr[i]=ptr[i-1]+ptr[i-2];
                else 
                    ptr[i]=ptr[i-1];
            }
            //else 
              //  ptr[i]=ptr[i-1];
        }

        return ptr[str.size()];
    }

    int maxValue(vector<vector<int>>& grid) 
    {
        if(grid.empty())
            return 0;

        //unique_ptr<unique_ptr<int[]>[]> ptrs(new unique_ptr<int[]>[grid.size()+1]);
        int n=grid.size()+1,m=grid[0].size()+1;
        int** ptrs=new int*[n];
        for(int i=0;i<n;i++)
            ptrs[i]=new int[m];
            //ptrs[i].reset(new int[grid[0].size()+1]);
        for(int i=0;i<=grid.size();i++)
        {
            for(int j=0;j<=grid[i].size();j++)
            {
                if(i==0 || j==0)
                    ptrs[i][j]=0;
                else 
                {
                    ptrs[i][j]=(ptrs[i-1][j] > ptrs[i][j-1] ? ptrs[i-1][j] : ptrs[i][j-1]);
                    ptrs[i][j]+=grid[i-1][j-1];
                }
            }
        }

        return ptrs[grid.size()][grid[0].size()];
    }
    
    int lengthOfLongestSubstring(string s) 
    {
        if(s.empty())
            return 0;

        unordered_map<char,string::iterator> ma;
        int dmp=0,max1=0;

        for(auto ite=s.begin();ite!=s.end();ite++)
        {
            auto a=ma.insert(make_pair(*ite,ite));
            if(a.second)
                dmp++;
            else 
            {
                int te=ite-a.first->second;
                if(te<=dmp)
                    dmp=te;
                else 
                    dmp++;
                ma[*ite]=ite;
            }
           // cout<<dmp<<endl;
            if(dmp>max1)
                max1=dmp;
        }

        return max1;
    }

    int nthUglyNumber(int n) 
    {
        if(n<=0)
            return 0;

        unique_ptr<int[]> ptr(new int[n]);
        int a=0,b=0,c=0;
        ptr[0]=1;

        for(int i=1;i<n;i++)
        {
            int ate=ptr[a]*2,bte=ptr[b]*3,cte=ptr[c]*5;
            int te=ate;
            if(te>bte)
                te=bte;
            if(te>cte)
                te=cte;
            if(te==ate)
                a++;
            if(te==bte)
                b++;
            if(te==cte)
                c++;
            ptr[i]=te;
        }

        return ptr[n-1];
    }

    char firstUniqChar(string s) 
    {
        unordered_map<char,int> ma;

        for(auto a : s)
        {
            ma[a]++;
        }
        for(auto a : s)
        {
            if(ma[a]==1)
                return a;
        }
        return 0;
    }

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {   
        if(!headA || !headB)
            return nullptr;
        
        int al=0,bl=0;
        ListNode* p1=headA;
        ListNode* p2=headB;
        while(p1)
        {
            al++;
            p1=p1->next;
        }
        while(p2)
        {
            bl++;
            p2=p2->next;
        }

        int gap=0;
        if(bl>al)
        {
            gap=bl-al;
            p1=headB;
            p2=headA;
        }
        else 
        {
            gap=al-bl;
            p1=headA;
            p2=headB;
        }

        while(gap--)
        {
            p1=p1->next;
        }
        while(p1!=p2 && p1 && p2)
        {
            p1=p1->next;
            p2=p2->next;
        }

        return p1;
    }

    int cou=0;
    void rmerge(vector<int>& nums,int p,int q,int r)
    {
        vector<int> left(nums.begin()+p,nums.begin()+q+1);
        vector<int> right(nums.begin()+q+1,nums.begin()+r+1);
        left.push_back(INT_MAX);
        right.push_back(INT_MAX);

        int i=0,j=0;
        for(int k=p;k<=r;k++)
        {
            //cout<<left[i]<<"ggg "<<right[j]<<endl;
            if(left[i]>right[j])
            {
                //cout<<left[i]<<" "<<right[j]<<endl;
                //cout<<left.size()<<" "<<i<<" "<<j<<endl;
                cou+=left.size()-i-1;
                nums[k]=right[j++];
            }
            else
                nums[k]=left[i++];
        }
    }

    void reverse_core(vector<int>& nums,int p,int r)
    {
        if(p>=r)
            return;

        int q=p+(r-p)/2;
        reverse_core(nums,p,q);
        reverse_core(nums,q+1,r);
        rmerge(nums,p,q,r);
    }

    int reversePairs(vector<int>& nums) 
    {
        if(nums.empty())
            return cou;
        
        reverse_core(nums,0,nums.size()-1);

        return cou;
    }

    int maxDepth(TreeNode* root) 
    {
        if(!root)
            return 0;

        int a=maxDepth(root->left);
        int b=maxDepth(root->right);

        return (a>b ? a : b)+1;
    }

    bool isBalanced_core(TreeNode* root,int& depth)
    {
        if(!root)
            return true;

        int left=0,right=0;
        if(!isBalanced_core(root->left,left) || !isBalanced_core(root->right,right))
            return false;

        if(abs(left-right)>1)
            return false;
        depth+=(left>right ? left : right)+1;
        return true;
    }

    bool isBalanced(TreeNode* root) 
    {
        int depth=0;
        return isBalanced_core(root,depth);
    }

    vector<int> singleNumbers(vector<int>& nums) 
    {
        int a=0;
        for(auto b : nums)
            a^=b;
        
        int ind=0,x=0x1;
        while(x)
        {
            if(a&x)
                break;
            x<<=1;
        }

        int c=0;
        a=0;
        for(auto b : nums)
        {
            if(b&x)
                a^=b;
            else 
                c^=b;
        }

        vector<int> vec({a,c});
        return vec;
    }
};
int main()
{
    Solution solution;
    int n;
    vector<int> nums;
    cin>>n;
    while(n--)
    {
        int te;
        cin>>te;
        nums.push_back(te);
    }
    cout<<solution.reversePairs(nums)<<endl;

    return 0;
}