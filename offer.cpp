#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <cstdint>

using namespace std;

class ListNode
{
public:
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class TreeLinkNode 
{
public:
    int val;
    TreeLinkNode* left;
    TreeLinkNode* right;
    TreeLinkNode* next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
private:
    int countRange(vector<int>& nums,int be,int en)
    {
        int sum = 0;
        for (const auto a : nums)
        {
            if (a >= be && a <= en)
                sum++;
        }
        return sum;
    }
public:
    int findRepeatNumber(vector<int>& nums) 
    {
        /*int be=0, en=nums.size()-1;

        while (be<=en)
        {
            int mid = ((en - be) >> 1)+be;
            int sum = countRange(nums,be,mid);
            cout<<be<<" "<<en<<" " << sum << endl;

            if (be == en)
            {
                if (sum > 1)
                    return  be;
                break;
            }
            if (sum > mid - be + 1)
            {
                en = mid;
            }
            else
                be = mid + 1;
        }
        return -1;*/
        for (decltype(nums.size()) i = 0; i < nums.size(); i++)
        {
            while (nums[i]!=i)
            {
                if (nums[i] == nums[nums[i]])
                    return nums[i];
                else
                {
                    int temp = nums[i];
                    nums[i] = nums[nums[i]];
                    nums[temp] = temp;
                }
            }
        }
        return -1;
    }

    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) 
    {
        if (matrix.empty() || matrix[0].empty())
            return false;
        int row=0;
        int col=matrix[0].size()-1;

        while (row<matrix.size() && col>=0)
        {
            int a = matrix[row][col];
            if (a == target)
                return true;
            else if (a > target)
                col--;
            else
                row++;
        }
        return false;
    }

    string replaceSpace(string s) 
    {
        string str;
        for (auto ch : s)
            if (ch != ' ')
                str += ch;
            else
                str += "%20";
        return str;
    }

    void reverseP(ListNode* head, vector<int>& vec)
    {
        if (!head)
            return;
        reverseP(head->next, vec);
        vec.push_back(head->val);
    }

    vector<int> reversePrint(ListNode* head) 
    {
        vector<int> re;
        reverseP(head, re);
        return re;
        /*vector<int> re;
        stack<int> te;

        while (head)
        {
            te.push(head->val);
            head = head->next;
        }
        while (!te.empty())
        {
            re.push_back(te.top());
            te.pop();
        }
        return re;*/
    }

    TreeNode* buildTreeCore(int* pres, int* pree, int* ins, int* ine)
    {
        if (pres > pree || ins > ine)
            return NULL;
        TreeNode* te = new TreeNode(*pres);
        if (pres == pree && ins == ine)
            return te;
        int* ro = nullptr;
        for (int* i = ins; i <= ine ; i++)
        {
            if ((*i) == (*pres))
            {
                ro = i;
                break;
            }
        }
        if (ro)
        {
            int gap = ro - ins;
            te->left = buildTreeCore(pres + 1, pres + gap,ins,ro-1);
            te->right = buildTreeCore(pres + gap + 1, pree, ro + 1, ine);
        }
        return te;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        if (preorder.size() == 0 || inorder.size() == 0)
            return NULL;
        int* pre = new int[preorder.size()];
        int* ino = new int[inorder.size()];
        memcpy(pre, &preorder[0], preorder.size() * sizeof(int));
        memcpy(ino, &inorder[0], inorder.size() * sizeof(int));
        TreeNode* root = buildTreeCore(pre,pre+preorder.size()-1,ino,ino+inorder.size()-1);
        
        delete[]pre;
        delete[]ino;
        return root;
    }

    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if (!pNode)
            return NULL;
        if (pNode->right)
        {
            TreeLinkNode* p = pNode->right;
            while (p->left)
            {
                p = p->left;
            }
            return p;
        }
        else if (pNode->next)
        {
            TreeLinkNode* p = pNode;
            while (p->next && p->next!=p && p->next->left!=p)
            {
                p = p->next;
            }
            if (p->next && p->next->left == p)
                return p->next;
        }
        return NULL;
    }

    stack<int> sta1, sta2;

    void appendTail(int value) 
    {
        sta1.push(value);
    }

    int deleteHead() 
    {
        if (sta2.empty())
        {
            while (!sta1.empty())
            {
                sta2.push(sta1.top());
                sta1.pop();
            }
        }
        if (!sta2.empty())
        {
            int te = sta2.top();
            sta2.pop();
            return te;
        }
        return -1;
    }

    int fib(int n) 
    {
        if (n == 0 || n == 1)
            return n;
        long long a = 0, b = 1;
        for (int i = 2; i <= n; i++)
        {
            long long te = b;
            b = (a + b) % 1000000007;
            a = te;
        }

        return b % (1000000007);
    }

    int numWays(int n) 
    {
        if (n == 1 || n == 1)
            return 1;
        long long a = 1, b = 1;
        for (int i = 2; i <= n; i++)
        {
            long long te = b;
            b = (a + b) % 1000000007;
            a = te;
        }

        return b % (1000000007);
    }

    int findMin(vector<int>& numbers)
    {
        if (!numbers.size())
            return -1;
        int min1 = numbers[0];
        for (auto i = numbers.begin() + 1; i != numbers.end(); i++)
            if ((*i) < min1)
                min1 = (*i);
        return min1;
    }

    int minArray(vector<int>& numbers) 
    {
        int be=0, en=numbers.size()-1, mid=0;
        
        while (numbers[be]>=numbers[en])
        {
            if (en - be == 1)
            {
                mid = en;
                break;
            }
            mid = (be + en) / 2;
            if (numbers[be] == numbers[mid] && numbers[mid] == numbers[en])
                return findMin(numbers);
            if (numbers[mid] >= numbers[be])
                be = mid;
            else if (numbers[mid] <= numbers[en])
                en = mid;
        }
        return numbers[mid];
    }

    bool** used;

    bool existCore(vector<vector<char>>& board, string word, int cen,int x,int y)
    {
        if (board[x][y] != word[cen])
            return false;
        else
            cen++;
        if (cen == word.size())
        {
            return true;
        }
        used[x][y] = 1;
        if (x > 0 && !used[x - 1][y])
        {
           // used[x - 1][y] = 1;
            if (existCore(board, word, cen, x - 1, y))
                return true;
           // used[x - 1][y] = 0;
        }
        if (x < board.size() - 1 && !used[x + 1][y])
        {
         //   used[x][y] = 1;
            if (existCore(board, word, cen, x + 1, y))
                return true;
          //  used[x + 1][y] = 0;
        }
        if (y > 0 && !used[x][y - 1])
        {
          //  used[x][y] = 1;
            if (existCore(board, word, cen, x, y-1))
                return true;
           // used[x][y] = 0;
        }
        if (y < board[x].size() - 1 && !used[x][y + 1])
        {
           // used[x][y ] = 1;
            if (existCore(board, word, cen, x, y + 1))
                return true;
           // used[x][y] = 0;
        }
        used[x][y] = 0;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) 
    {
        if (board.empty() || board[0].empty())
            return !word.size();
        used = new bool* [board.size()];
        for (int i = 0; i < board.size(); i++)
        {
            used[i] = new bool[board[i].size()];
            memset(used[i], 0, sizeof(bool) * board[i].size());
        }

        bool re=false;
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (re = existCore(board, word, 0, i, j))
                    break;
            }
            if (re)
                break;
        }

        for (int i = 0; i < board.size(); i++)
            delete[]used[i];
        delete[]used;

        return re;
    }

    int maxcou = 0;
    int getWei(int a)
    {
        int sum = 0;
        while(a>0)
        {
            sum += a % 10;
            a /= 10;
        }
        return sum;
    }
    void movingCountCore(int m, int n, int x, int y, int k,int& cou)
    {
        int sum = getWei(x) + getWei(y);
        if (sum > k)
            return;
        ++cou;
        cout << x << " " << y << endl;

        used[x][y] = 1;
        if (x > 0 && !used[x - 1][y])
        {
            movingCountCore(m, n, x - 1, y, k, cou);
        }
        if (x < m - 1 && !used[x + 1][y])
        {
            movingCountCore(m, n, x + 1, y, k,cou);            
        }
        if (y > 0 && !used[x][y - 1])
        {
            movingCountCore(m, n, x, y-1, k,cou);
        }
        if (y < n - 1 && !used[x][y + 1])
        {
            movingCountCore(m, n, x, y+1, k,cou);
        }
      //  used[x][y] = 0;
    }

    int movingCount(int m, int n, int k) 
    {
        used = new bool* [m];
        for (int i = 0; i < m; i++)
        {
            used[i] = new bool[n];
            memset(used[i], 0, sizeof(bool) * n);
        }

        int cou = 0;
        movingCountCore(m, n, 0, 0, k, cou);

        for (int i = 0; i < m; i++)
            delete[]used[i];
        delete[]used;

        return maxcou;
    }

    int mod = (int)1e9 + 7;

    int quickPow(long long x, long long y)
    {
        long long re = 1;
        while (y>0)
        {
            if (y & 0x1)
            {
                re *= x;
                re %= mod;
            }
            x *= x;
            x %= mod;
            y >>= 1;
        }
        return re;
    }

    int cuttingRope(int n) 
    {
        //贪心
        if (n < 2)
            return 0;
        if (n < 4)
            return n - 1;
        int a3 = n / 3;
        if (n - a3 * 3 == 1)
            a3--;
        int a2 = (n - a3 * 3) / 2;
        long long re3 = quickPow(3, a3),re2= quickPow(2, a2);

        return re3 * re2 % mod;
        //dp
        /*if (n < 2)
            return -1;
        int* a = new int[n+1];
        a[1] = 1;
        a[2] = 1;
        for (int i = 3; i <= n; i++)
        {
            int max1 = 0;
            for (int j = 1; j <= i / 2; j++)
            {
                int b = (a[j] > j ? a[j] : j);
                int c = (a[i - j] > (i - j) ? a[i - j] : (i - j));
                cout <<i<<" "<<j<<":  "<< b << " " << c << endl;
                if (b*c > max1)
                    max1 = b * c;
            }
            a[i] = max1;
        }

        int re = a[n];
        delete[]a;
        return re;*/
    }

    int hammingWeight(uint32_t n) 
    {
        int sum = 0;
        uint32_t a = 0x1;
        while (a)
        {
            sum += !!(a & n);
            a <<= 1;
        }
        return sum;
    }

    double myPowCore(double x, long long n)
    {
        if (!n)
            return 1;
        if (n == 1)
            return x;

        double res = myPowCore(x , n >> 1);
        res *= res;
        if (n & 0x1)
        {
            res *= x;
        }

        return res;
    }

    double myPow(double x, int n) 
    {
        //递归
        int flag = n > 0;
        long long nn = n;
        nn = (nn > 0 ? nn : -nn);

        double res = myPowCore(x, nn);
        if (!flag)
            res = 1.0 / res;

        return res;
        //非递归
        /*if (!n)
            return 1;
        int flag = n > 0;
        long long nn = n;
        nn = (nn > 0 ? nn : -nn);
        double res = 1;
        while (nn > 0)
        {
            if (nn & 0x1)
            {
                res *= x;
            }
            nn >>= 1;
            x *= x;
        }
        if (!flag)
            res = 1.0 / res;
        return res;*/
    }

    void  printNumbersCore(vector<int>& vec,int a,int t, int n)
    {
        if (t == n)
        {
            if(a)
                vec.push_back(a);
            return;
        }

        for (int i = 0; i <= 9; i++)
        {
            printNumbersCore(vec, a * 10 + i, t + 1, n);
        }
    }

    vector<int> printNumbers(int n) 
    {
        vector<int> vec;
        int a = 0;
        printNumbersCore(vec, 0, 0, n);

        return vec;
    }

    ListNode* deleteNode(ListNode* head, int val) 
    {
        if (!head)
            return nullptr;

        if (head->val == val)
            return head->next;

        ListNode* p1 = head,*p2=head->next;
        while (p2)
        {
            if (p2->val == val)
            {
                p1->next = p2->next;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        return head;
    }

    ListNode* createLinkedList(int n)
    {
        int x;
        cin >> x;
        ListNode* head = new ListNode(x), * p = head;
        for (int i = 1; i < n; i++)
        {
            cin >> x;
            p->next = new ListNode(x);
            p = p->next;
        }
        return head;
    }

    void display(ListNode* head)
    {
        ListNode* p = head;

        while (p)
        {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    ListNode* deleteDuplication(ListNode* pHead)
    {
        if (!pHead)
            return nullptr;

        ListNode* p1 = nullptr, *p2 = pHead;
        //pHead = nullptr;
        while (p2)
        {
            int val = p2->val;
            ListNode* p3 = p2->next;

            if(p3 && p3->val==val)
            {
                while (p3 && p3->val==val)
                {
                    p3 = p3->next;
                }
                if (!p1)
                    pHead = p3;
                else
                    p1->next = p3;
            }
            else
            {
                p1 = p2;
                p2 = p2->next;
            }
            p2 = p3;
        }
        return pHead;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums, int be, int en)
    {
        if (be > en)
            return nullptr;

        int mid = be + (en - be) / 2;
        TreeNode* ph = new TreeNode(nums[mid]);
        ph->left = sortedArrayToBST(nums, be, mid - 1);
        ph->right = sortedArrayToBST(nums, mid + 1, en);

        return ph;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) 
    {
        if (nums.empty())
            return nullptr;

        int n = nums.size();
        TreeNode* head = new TreeNode(nums[n / 2]);

        head->left = sortedArrayToBST(nums, 0, n / 2 - 1);
        head->right = sortedArrayToBST(nums, n / 2 + 1, n - 1);

        return head;
    }

    bool isMatchCore(string s,string p,int x1,int x2)
    {
       // cout<<s.length()<<"***"<<p.length()<<endl;
        //cout<<x1<<" "<<x2<<endl;
        if(x1==s.length() && x2==p.length())
            return true;
        if(x1!=s.length() && x2==p.length())
        {
            cout<<x1<<" "<<x2<<endl;
            return false;
        }
        
        if(x2+1<p.length() && p[x2+1]=='*')
        {
            if(x1<s.length() && (p[x2]==s[x1] || p[x2]=='.'))
                return isMatchCore(s,p,x1+1,x2) || isMatchCore(s,p,x1+1,x2+2) || isMatchCore(s,p,x1,x2+2);
            else
                return isMatchCore(s,p,x1,x2+2);
        }
        else
        {
            if(x1<s.length() && (p[x2]==s[x1] || p[x2]=='.'))
                return isMatchCore(s,p,x1+1,x2+1);
            else
                return false;
        }
        
    }

    bool isMatch(string s, string p) 
    {
        int** match;
        int n=s.length()+1,m=p.length()+1;
        match=new int* [n];
        for(int i=0;i<n;i++)
        {
            match[i]=new int[m];
            //memset(match,0,sizeof(bool)*m);
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(!i && !j)
                {
                    match[i][j]=1;
                }
                else if(!j && i)
                {
                    match[i][j]=0;
                }
                else
                {
                    match[i][j]=0;
                    if(i && (p[j-1]==s[i-1] || p[j-1]=='.'))
                    {
                        match[i][j]=match[i-1][j-1];
                    }
                    else if(p[j-1]=='*')
                    {
                        if(j-1>0 && (i>0 && (p[j-2]==s[i-1] || p[j-2]=='.')))
                        {
                            match[i][j]=match[i-1][j];
                        }
                        if(j>1)
                            match[i][j]=match[i][j] || match[i][j-2];
                    }
                    else
                    {
                        match[i][j]=0;
                    }
                    
                }
                
            }
        }

        int re=match[n-1][m-1];
        for(int i=0;i<n;i++)
            delete []match[i];
        delete []match;

        return re;
    }

    bool scan_unsigned(string str,int& x)
    {
        int te=x;
        while(x<str.length() && str[x]>='0' && str[x]<='9')
            x++;
        return x>te;
    }

    bool scan_int(string str,int& x)
    {
        if(str[x]=='+' || str[x]=='-')
            x++;
        return scan_unsigned(str,x);
    }

    bool isNumber(string s) 
    {
        if(s.empty())
            return false;
        
        int x=0;
        bool flag=scan_int(s,x);
       // cout<<flag<<" "<<x<<endl;

        if(s[x]=='.')
        {
            x++;
            flag=scan_unsigned(s,x) || flag;
           // cout<<flag<<" "<<x<<endl;
        }

        if(s[x]=='e' || s[x]=='E')
        {
            x++;
            flag=flag && scan_int(s,x);
            cout<<flag<<" "<<x<<endl;
        }
       // cout<<flag<<" "<<x<<endl;

        return flag && x==s.length();
    }

    void swap(int& a,int& b)
    {
        a=a^b;
        b=a^b;
        a=a^b;
    }

    void reOrderArray(vector<int> &array) 
    {
        if(array.empty())
            return;
        auto be=array.begin(),en=array.end()-1;

        while (be<en)
        {
            while (be<en && (*be)%2)
                be++;
            while (be<en && !((*en)%2))
                en--;
            if(be<en)
                swap(*be,*en);
        }
                
    }

    ListNode* getKthFromEnd(ListNode* head, int k) 
    {
        if(!head || k==0)
            return nullptr;

        ListNode* p1=head,*p2=head;
        for(int i=0;i<k-1;i++)
        {
            if(p1->next)
                p1=p1->next;
            else
                return nullptr;
        }

        while (p1->next)
        {
            p1=p1->next;
            p2=p2->next;
        }

        return p2;
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
    solution.reOrderArray(vec);
    for(int a : vec)
        cout<<a<<" ";
    cout<<endl;
    //cout<<solution.isNumber(s1)<<endl;;

    return 0;
}
