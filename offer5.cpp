#include <iostream>
#include <vector>
#include <climits>
#include <deque>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct c_list
{
    int val;
    c_list* next;
    c_list(int _val,c_list* n):val(_val),next(n){}
};

class MaxQueue 
{
private:
    deque<int> deq;
    queue<int> que;
    int index=0;
public:
    MaxQueue() {}
    
    int max_value() 
    {
        if(deq.empty())
            return -1;
        return deq.front();
    }
    
    void push_back(int value) 
    {
        while(!deq.empty() && deq.back()<=value)
        {
            deq.pop_back();
            index++;
        }
        deq.push_back(value);
        que.push(value);
    }
    
    int pop_front()
    {
        if(deq.empty())
            return -1;
        int te=que.front();
        if(te==deq.front())
            deq.pop_front();
        que.pop();

        return te;
    }
};

class Solution
{
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        vector<int> re;
        int p=0,r=nums.size()-1;

        while(p<=r)
        {
            int sum=nums[p]+nums[r];
            if(sum==target)
            {
                re.push_back(nums[p]);
                re.push_back(nums[r]);
                break;
            }
            else if(sum<target)
            {
                p++;
            }
            else 
                r--;
        }
        return re;
    }

    vector<vector<int>> findContinuousSequence(int target) 
    {
        vector<vector<int> > re;
        int p=1,r=2;
        int sum=p+r;
        int q=(1+target)/2;

        while(p<=q)
        {
            if(sum==target)
            {
                vector<int> vec;
                for(int i=p;i<=r;i++)
                    vec.push_back(i);
                re.push_back(vec);
                r++;
                sum+=r;
            }
            else if(sum<target)
            {
                r++;
                sum+=r;
            }
            else 
            {
                sum-=p;
                p++;
            }
        }

        return re;
    }

    void reverse_string(string& s,int p,int r)
    {
        while(p<r)
        {
            char te=s[p];
            s[p]=s[r];
            s[r]=te;
            p++;
            r--;
        }
        //cout<<s<<endl;
    }

    string reverseWords(string s) 
    {
        reverse_string(s,0,s.size()-1);
        //cout<<s<<endl;
        int p=0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==' ')
            {
                reverse_string(s,p,i-1);
                p=i+1;
            }
            else if(i==s.size()-1)
                reverse_string(s,p,i);
        }
        string str="";
        for(auto ite=s.begin();ite!=s.end();)
        {
            if(str.empty() && *ite==' ')
            {
                ite++;
                continue;
            }
            if(*ite==' ')
            {
                while(ite!=s.end() && *ite==' ')
                    ite++;
                if(ite==s.end())
                    break;
                str+=' ';
            }
            else 
            {
                str+=*ite;
                ite++;
            }
        }

        return str;
    }

    string reverseLeftWords(string s, int n) 
    {
        reverse_string(s,0,n-1);
        reverse_string(s,n,s.size()-1);
        reverse_string(s,0,s.size()-1);
        return s;
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {
        vector<int> vec;
        if(nums.empty() || nums.size()<k)
            return vec;
        deque<int> index_que;
        for(int i=0;i<k-1;i++)
        {
            while(!index_que.empty() && nums[index_que.back()]<nums[i])
            {
                index_que.pop_back();
            }
            index_que.push_back(i);
        }
        for(int i=k-1;i<nums.size();i++)
        {
            while(!index_que.empty() && nums[index_que.back()]<nums[i])
            {
                index_que.pop_back();
            }
            index_que.push_back(i);
            if(index_que.back()-index_que.front()>=k)
                index_que.pop_front();
            vec.push_back(nums[index_que.front()]);
        }

        return vec;
    }

    vector<double> twoSum(int n) 
    {
        vector<double> re;
        vector<vector<double>> vec;
        vec.push_back(vector<double>(n*6+1));
        vec.push_back(vector<double>(n*6+1));
        int cur=0;

        for(int i=1;i<=6;i++)
            vec[cur][i]=1;
        cur=!cur;

        for(int i=1;i<n;i++)
        {
            for(int j=1;j<=6*n;j++)
            {
                vec[cur][j]=0;
                for(int k=1;k<=6;k++)
                {
                    if(k>j)
                        break;
                    vec[cur][j]+=vec[!cur][j-k];
                }
            }
            cur=!cur;
        }

        double total=pow(6,n);
        for(int i=1;i<vec[!cur].size();i++)
        {
            if(vec[!cur][i])
                re.push_back((vec[!cur][i]/total));
        }

        return re;
    }

    bool isStraight(vector<int>& nums) 
    {
        sort(nums.begin(),nums.end());
        int cou=0;
        for(auto ite=nums.begin();ite!=nums.end();ite++)
        {
            if(!(*ite))
                cou++;
            else 
            {
                if(ite+1!=nums.end())
                {                    
                    if(*(ite+1)==*ite)
                        return false;
                    int gap=*(ite+1)-(*ite);
                    if(gap>cou)
                    {
                        return false;
                    }
                    else 
                        cou-=gap;
                }
            }
        }

        return true;
    }

    int lastRemaining(int n, int m) 
    {
        //数学公式实现
        if(n<1 || m<1)
            return -1;
        int re=0;
        for(int i=2;i<=m;i++)
        {
            re=(re+m)%i;
        }
        return re;
        //循环链表实现
        if(n<1)
            return -1;
        c_list* head=nullptr,*p;
        for(int i=0;i<n;i++)
        {
            if(!head)
            {
                head=new c_list(0,nullptr);
                p=head;
            }
            else 
            {
                p->next=new c_list(i,nullptr);
                p=p->next;
            }
        }
        p->next=head;

        c_list* pre_p=p;
        p=head;
        while(p->next!=p)
        {
            for(int i=1;i<m;i++)
            {
                pre_p=p;
                p=p->next;
            }
           // cout<<p->val<<endl;
            pre_p->next=pre_p->next->next;
            p=pre_p->next;
        }

        return p->val;
    }

    int maxProfit(vector<int>& prices) 
    {
        int min_cost=INT_MAX,profit=0;
        for(auto a : prices)
        {
            profit=(profit>(a-min_cost) ? profit : (a-min_cost));
            min_cost=(min_cost<a ? min_cost : a);
        }

        return profit;
    }

    typedef int (*fun)(int);

    static fun f[2];

    static int add1(int a)
    {
        return 0;
    }
    static int add2(int a)
    {
        //static fun f[2]={add1,add2};
        return a+f[!!a](a-1);
    }

    int sumNums(int n) 
    {
        return f[!!n](n);
    }
};
Solution::fun Solution::f[2]={add1,add2};

int main()
{
    int n,m;
    cin>>n>>m;
    Solution solution;
    cout<<solution.lastRemaining(n,m)<<endl;

    return 0;
}