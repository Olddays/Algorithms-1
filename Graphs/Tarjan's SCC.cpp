//RandomUsername (Nikola Jovanovic)
//Tarjan's SCC
//O(V + E)

#include <bits/stdc++.h>
#define MAXN 30005
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2

using namespace std;

struct node
{
    int disc; //dfs numbering, time discovered
    int low; //lowpoint, reachable node with the lowest disc
    bool onStack; //is it in the current SCC
    int comp; //component?
    vector<int> adj; //children
};

int compCnt; //number of components
int discCnt; //discovery counter

node g[MAXN]; //the graph

int n, m;
int u, v;
stack<int> s;

void SCC(int curr)
{
    int nxt;

    //process curr
    g[curr].disc = ++discCnt;
    g[curr].low = g[curr].disc;
    s.push(curr);
    g[curr].onStack = true;

    int limit = g[curr].adj.size();
    for(int i=0; i<limit; i++)
    {
        nxt = g[curr].adj[i]; //next node we process

        if(g[nxt].disc == 0) //tree edge
        {
            SCC(nxt);
            g[curr].low = min(g[curr].low, g[nxt].low);
        }
        else if(g[nxt].onStack) //relevant back/cross edge
        {
            g[curr].low = min(g[curr].low, g[nxt].disc);
        }
    }
    if(g[curr].low == g[curr].disc) //we found a new SCC
    {
        ++compCnt;
        nxt = 0; //curr = SCC component head
        while(!s.empty() && nxt != curr) //pop until we hit curr
        {
            nxt = s.top();
            s.pop();
            g[nxt].onStack = false;
            g[nxt].comp = compCnt;
        }
    }
}

int main()
{
    //input
    compCnt = 0;
    discCnt = 0;
    scanf("%d %d", &n, &m);
    for(int i=1; i<=m; i++)
    {
        scanf("%d %d", &u, &v);
        g[u].adj.push_back(v);
    }
    
    //SCC
    for(int i=1; i<=n; i++)
    {
       if(g[i].disc == 0)
        SCC(i);
    }
    
    //output
    for(int i=1; i<=n; i++)
    {
       printf("Node : %d SCC : %d\n", i, g[i].comp);
    }
    return 0;
}

/*
Practice problem : http://codeforces.com/problemset/problem/427/C
TP : http://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
8 14
1 2
3 1
4 3
4 2
2 3
4 5
5 4
5 6
6 3
6 7
7 6
8 8
8 7
8 5
*/
