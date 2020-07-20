#include <string>
#include <cstring>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

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
};
int main()
{
    Solution solution;
    int n;
    cin>>n;
    cout<<solution.findNthDigit(n)<<endl;

    return 0;
}