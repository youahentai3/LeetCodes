#include <iostream>
#include <vector>

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
};

int main()
{
    return 0;
}