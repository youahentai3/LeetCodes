#include <iostream>
#include <stack>

using namespace std;

class Solution 
{
private:
    stack<int> sta;
    stack<int> sta_min;
    int min_val=INT_MAX;
public:
    void push(int value) 
    {    
        sta.push(value);
        if(value<min_val)
            min_val=value;
        sta_min.push(min_val);
    }
    void pop() 
    {
        sta.pop();
        sta_min.pop();
        min_val=sta_min.top();    
    }
    int top() 
    {
        return sta.top();
    }
    int min() 
    {
        return min_val;
    }
};