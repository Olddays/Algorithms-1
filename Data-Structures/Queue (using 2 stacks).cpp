//RandomUsername (Nikola Jovanovic)
//Queue (using 2 stacks)

#include <bits/stdc++.h>
#define MAXN 100005
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2

using namespace std;

/*
Queue can be implemented using two stacks : inbox and outbox
Push : inbox.push()
Pop : if outbox is empty, refill by popping each element from inbox and pushing it onto outbox
      outbox.pop()
This data structure supports max/min/sum/... queries on all the elements currently inside
Each element holds cumulative max/min/sum... of all elements below
MaxQueue = max(MaxInbox, MaxOutbox)
Useful when dealing with sliding windows ( http://codeforces.com/contest/514/problem/D )
*/

struct queue_twostacks
{
    //we will use pair<int, int>
    //first element -> value
    //second element -> cumulative maximum

    stack<par> in; //inbox
    stack<par> out; //outbox

    void push(int x)
    {
        if(in.empty())
        {
            par nw = par(x, x);
            in.push(nw);
        }
        else
        {
            par nw = par( x, max(x, in.top().se) );
            in.push(nw);
        }
    }

    void pop()
    {
        if(out.empty())
        {
            //flip inbox into outbox
            while(!in.empty())
            {
                int x = in.top().fi;
                in.pop();
                if(out.empty())
                {
                    par nw = par(x, x);
                    out.push(nw);
                }
                else
                {
                    par nw = par( x, max(x, out.top().se) );
                    out.push(nw);
                }
            }
        }
        if(!out.empty())
            out.pop();
    }

    int getMax()
    {
        int m1, m2;
        if(in.empty()) m1 = -1;
        else m1 = in.top().se;
        if(out.empty()) m2 = -1;
        else m2 = out.top().se;
        return max(m1, m2);
    }
};

queue_twostacks q;

int main()
{
    q.push(2);
    q.push(3);
    cout<<q.getMax()<<endl;
    q.push(7);
    q.push(5);
    cout<<q.getMax()<<endl;
    q.pop();
    q.pop();
    cout<<q.getMax()<<endl;
    q.pop();
    cout<<q.getMax()<<endl;
    //3 7 7 5
    return 0;
}
