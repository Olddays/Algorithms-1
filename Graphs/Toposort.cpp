//RandomUsername (Nikola Jovanovic)
//Toposort

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

// toposort = linear ordering of vertices, edge u -> v => topo[u] < topo[v]
// DAG <=> has at least 1 toposort (Directed cycles <=> No toposort)

struct node
{
    int indeg;
    vector<int> adj;
};

node g[MAXN];
int topo[MAXN];
int cnt;

//n nodes, m edges
int n, m;
int u, v;

bool Toposort()
{
    int curr;
    int limit, nxt;
    queue<int> q;
    for(int i=1; i<=n; i++)
    {
       //we start from vertices with indegree=0 (they always exist in a DAG)
       if(g[i].indeg == 0) q.push(i);
    }

    while(!q.empty())
    {
        curr = q.front();
        q.pop();
        topo[cnt++] = curr;
        limit = g[curr].adj.size();
        for(int i=0; i<limit; i++)
        {
            nxt = g[curr].adj[i];
            g[nxt].indeg--; //removing the curr node and all edges from curr
            if(g[nxt].indeg == 0) //new indegree=0 node?
                q.push(nxt);
        }
    }
    if(cnt < n+1)
    {
        //Cycles!
        return false;
    }
    return true;
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i=1; i<=m; i++)
    {
        scanf("%d %d", &u, &v);
        g[u].adj.push_back(v);
        g[v].indeg++;
    }
    cnt = 1;
    if( Toposort() )
    {
        for(int i=1; i<=n; i++)
        {
           printf("%d ",topo[i]);
        }
    }
    else
    {
        printf("Cycles!");
    }
}
