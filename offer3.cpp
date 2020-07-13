#include <iostream>
#include <vector>
#include <stack>

using namespace std;

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
};