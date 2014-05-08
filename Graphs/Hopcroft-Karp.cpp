//RandomUsername(Nikola Jovanovic)
//Hopcroft-Karp Max Matching On Bipartite Graphs
//Runtime: O(Esqrt(V))

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
#define MAXN 1000

using namespace std;

struct node //a node in our graph
{
    int p; //partition
    int par; //pair
    int level; //dfsbfs stuff
    bool vis; //visited (needed for dfs)
    vector<int> adj; //adjacency list
};

int n1,n0,n; //number of vertices in each component
int m;//number of edges
node g[MAXN]; //the graph
int v1,v2;
queue<int> q;
int limit;
int curr,nxt;
vector<int> p0,p1;
int matched;
int lastlvl;

void findPartitions()
{
    //we do a simple BFS to sort the nodes in two components
    q.push(1);
    g[1].p=0;
    p0.push_back(1);
    //node 1 is in component 0
    while(!q.empty())
    {
        curr=q.front();
        q.pop();
        limit=g[curr].adj.size();
        for(int i=0;i<limit;i++)//all of curr's neighbours
        {
            nxt=g[curr].adj[i];
            if(g[nxt].p==-1)//if not visited
            {
                q.push(nxt);
                //add him to the q, and mark his comp
                if(g[curr].p==0)
                {
                    g[nxt].p=1;
                    p1.push_back(nxt);
                }
                else
                {
                    g[nxt].p=0;
                    p0.push_back(nxt);
                }
            }
        }
    }

    n0=p0.size();
    n1=p1.size();

}

bool AugPaths()
{
    //This function should detect all shortest AugPaths
    //(Paths that start from comp0 free node, and end on comp1 free node,
       //but alternate between matched and ummatched egdes)
    //We start the DFS search by placing all free comp0 nodes in a queue
    for(int i=1;i<=n0;i++)
        if(g[p0[i-1]].par==-1)
        {
            g[p0[i-1]].level=0;
            q.push(p0[i-1]);
        }
    while(!q.empty())
    {
        curr=q.front();
        q.pop();
        limit=g[curr].adj.size();
        for(int i=0;i<limit;i++)//for each comp0 node, visit all neighbours
        {
            nxt=g[curr].adj[i];
            if(g[nxt].level==-1)//nxt is from comp1, if not visited:
            {
                if(g[nxt].par==-1)//if nxt is free this is one of the shortest AugPaths
                  {
                      g[nxt].level=g[curr].level+1;
                      lastlvl=g[nxt].level; //lastlvl is the first level that has A.P. , don't search beyond
                  }
                else //if nxt is not free mark it and use it's matched edge
                {
                    g[nxt].level=g[curr].level+1;
                    nxt=g[nxt].par;
                    if(g[nxt].level==-1 && g[curr].level+1!=lastlvl)
                    {
                        //lastlvl is the first level that has A.P. , don't search beyond
                        g[nxt].level=g[curr].level+2;
                        q.push(nxt);
                        //continue the search
                    }
                }
            }
        }
    }
    //lastlvl is the first level that has A.P. , don't search beyond
    if(lastlvl==-1) return false;
    return true;
}

bool DFS(int x)
{
    //now our nodes are marked with their levels, use all the disjoint A.P.
    int limity,nxty;
    if(x==0)
        return true;//DFS returns true if it hits an unvisited node

    //if this node is not visited, go!
    if(g[x].vis) return false;
        g[x].vis=true;

    limity=g[x].adj.size();
    for(int i=0;i<limity;i++)
    {
        nxty=g[x].adj[i];//all neighbours
        if(g[nxty].vis)//that are unvisited
            continue;
        if(g[nxty].level!=g[x].level+1)//that are on the next level
            continue;
        nxty=g[nxty].par;//take their pairs, if they are unpaired x=0 => DFS returns true
        if(DFS(nxty))
        {
            g[g[x].adj[i]].vis=true;//g[x].adj[i] is visited now
            g[g[x].adj[i]].par=x;//we have found his pair
            g[x].par=g[x].adj[i];//pairs are bidirectional tho
            return true;//we return true so other DFS calls know that we are modifying the pairs
        }
    }
    return false;//if we miss everything return false
}

void HK()
{
    while(AugPaths())
    {
        //AugPahts() returns false when there are no new augmenting paths <=> we found max matching

        //if there are, do DFS starting from every free node in component 0:
        for(int i=0;i<=n0-1;i++)
        {
            if(g [ p0[i] ].par==-1 && DFS(p0[i]) )
                matched++; //if DFS returns true, we used up 1 aug. path => we increase the size of our matching
        }
        for(int i=1;i<=n;i++)//preparation for the next BFS
        {
            g[i].vis=false;
            g[i].level=-1;
        }
        lastlvl=-1;
    }
}

void Print() //Basic printing
{
   printf("Component A:\n");
   for(int i=1;i<=n0;i++)
   {
       printf("%d %d\n",p0[i-1],g[p0[i-1]].level);
   }
   printf("\nComponent B:\n");
   for(int i=1;i<=n1;i++)
   {
       printf("%d %d\n",p1[i-1],g[p1[i-1]].level);
   }
   printf("\nPairs (A-B) :\n");
   for(int i=1;i<=n0;i++)
   {
       if(g[p0[i-1]].par!=-1)
        printf("%d %d\n",p0[i-1],g[p0[i-1]].par);
   }
}

int main()
{
    //input
    scanf("%d %d",&n,&m);
    matched=0; //initially, 0 nodes are matched
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&v1,&v2);
        g[v1].adj.push_back(v2);
        g[v2].adj.push_back(v1);
        g[v1].level=-1, g[v2].level=-1;
        g[v1].par=-1, g[v2].par=-1;
        g[v1].p=-1, g[v2].p=-1;
    }
    //We have to assume that one of these holds:
    //A: The graph is connected
    //B: The g[].p is given in the task
    //If both A and B are false the partitions of a bipartite graph are not unique
    //Here we will assume A
    findPartitions(); //it's a bipartite graph, so find partitions
    HK(); //Do the algorithm
    Print();
    return 0;
}
