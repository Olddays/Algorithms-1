//RandomUsername(Nikola Jovanovic)
//HLD + LCA
//Runtime: O(n) for HLD and O(logn) for each LCA query
//Implemented for: http://www.spoj.com/problems/LCA/

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
#define MAXN 1005
#define lld long long

using namespace std;

struct node //the node for our graph
{
    vector<int> adj; //adjacency list
    int parent; //parent
    int level; //dfs level
    int nodesUnder; //number of nodes in this node's subtree
    int chainTop; //top of this node's heavy chain
};

node g[MAXN]; //the graph

//input vars
int t,n,q;
int cnt,v1,v2;
int root;

int DFS(int curr,int level)//classic DFS
{
    g[curr].level=level; //set level
    g[curr].nodesUnder=1; //set nodesUnder initial value
    int limit=g[curr].adj.size();
    for(int i=0;i<limit;i++)//for each child
    {
        g[curr].nodesUnder+=DFS(g[curr].adj[i],level+1); //do DFS and add all nodes to nodesUnder
    }
    return g[curr].nodesUnder; //DP
}

void HLD(int curr,int chainTop)//computing chainTop
{
    g[curr].chainTop=chainTop; //set chainTop
    int limit=g[curr].adj.size();
    for(int i=0;i<limit;i++)//visit each child
    {  //if we travel down the light edge, our nodesUnder should be reduced by at least 50%
        //this can guarantee at most logN nodes in each root->leaf path
        if( (1.0*g[g[curr].adj[i]].nodesUnder) > (0.5*g[curr].nodesUnder) )//heavy edge condition
            HLD(g[curr].adj[i],chainTop); //continue the chain
        else
            HLD(g[curr].adj[i],g[curr].adj[i]); //new chain
    }
}

int LCA(int a,int b)//computing lowest common ancestor for nodes a and b
{
    if(g[a].chainTop==g[b].chainTop)//if they are on the same heavy chain LCA=a v LCA=b
    {
        if(g[a].level<g[b].level)
            return a;
        else
            return b;
    }
    //if they are not on the same chain we skip to the lower of the chainTops
    //and traverse ONE light edge
    //O(lca)=logn since there are at most logn light edges from root to every node
    if( g[ g[a].chainTop ].level > g[ g[b].chainTop ].level )
    {
        a=g[a].chainTop;
        a=g[a].parent;
        return LCA(a,b);
    }
    else
    {
        b=g[b].chainTop;
        b=g[b].parent;
        return LCA(a,b);
    }

}

int main()
{
    //t test cases
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++)
    {
        scanf("%d",&n);
        //reset everything
        for(int i=1;i<=n;i++)
        {
            g[i].parent=0;
            g[i].adj.clear();
            g[i].nodesUnder=0;
            g[i].chainTop=0;
            g[i].level=0;
            root=0;
        }
        //input format can easily tell us which node is the root
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&cnt);
            for(int j=1;j<=cnt;j++)
            {
                scanf("%d",&v2);
                g[i].adj.push_back(v2);
                g[v2].parent=i;
            }
        }
        //find the root (orphan node) and do a DFS to calculate nodesUnder
        for(int i=1;i<=n;i++)
        {
            if(g[i].parent==0)
            {
                root=i;
                DFS(root,1);
                break;
            }
        }
        //initializing HLD
        HLD(root,root);
        //handling LCA queries
        scanf("%d",&q);
        printf("Case %d:\n",tt);
        for(int i=1;i<=q;i++)//tree
        {
            scanf("%d %d",&v1,&v2);
            printf("%d\n",LCA(v1,v2));
        }
    }
    return 0;
}
