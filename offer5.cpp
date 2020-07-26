#include <iostream>
#include <vector>
#include <climits>
#include <deque>

using namespace std;

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
};

int main()
{
    string s;
    getline(cin,s);
    Solution solution;
    cout<<solution.reverseWords(s)<<endl;

    return 0;
}