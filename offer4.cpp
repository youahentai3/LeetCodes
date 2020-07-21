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
};
int main()
{
    Solution solution;
    string n;
    cin>>n;
    cout<<solution.lengthOfLongestSubstring(n)<<endl;

    return 0;
}