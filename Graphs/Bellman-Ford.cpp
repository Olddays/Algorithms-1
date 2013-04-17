//RandomUsername(Nikola Jovanovic)
//Bellman-Ford algorithm (Shortest paths)
//Runtime:E*V, single source, works also for negative edge weights
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#define MAXN 100010
#define MAXM 80010
#define FAKEMAXINT 2000000000
using namespace std;
 
struct edge
{
       int a,b,c;//a-b is the edge, c-the price
};

struct node
{
      vector<edge> adj; //adjacency list, not used in the actual algorithm, but often needed
                        //adj[i].a is not needed here but nvm
      int d;//distance
      int cameFrom;//possible reconstruction of the path
};

node a[MAXN];//the graph
edge e[2*MAXM];//the edges

edge pom;
int n,m,start,end,v1,v2,cost;
int from,to;
bool possible;

bool BellmanFord(int start)
{
     for(int i=1;i<=n;i++)
       a[i].d=FAKEMAXINT;//set initial distances to maxint
       
     a[start].d=0; //begin with start
     for(int i=1;i<=n-1;i++)//relax all edges n-1(number of vertices) times
     { //we guarantee that every path of length i is successfully computed
       //in first i iteratons. Therefore n-1 iterations should do the work.
       for(int j=0;j<=2*m-1;j++)//all edges, m-1 goes here if not bidirectional
       {
            from=e[j].a;
            to=e[j].b;
            cost=e[j].c;
            if( a[from].d + cost < a[to].d )
              {
                 a[to].d = a[from].d + cost;
                 a[to].cameFrom=from;
              }
       }   
     }
     //if anything can be optimized in n-th iteration there is a negative cycle
     //which means that every walk around the cycle can decrease the cost
     //=>There is no shortest path
     //The n-th iteration is written separate from the main loops for the sake of
     //simplicity and understanding
     for(int j=0;j<=2*m-1;j++)//all edges, m-1 goes here if not bidirectional
       {
            from=e[j].a;
            to=e[j].b;
            cost=e[j].c;
            if( a[from].d + cost < a[to].d )
                  return false;//can be optimized=>negative cycle
       }
     return true;//no negative cycle, shortest path exists
}

int main(int argc, char *argv[])
{
    //input, 1 based numbering, find path from start to end
    scanf("%d %d %d %d",&n,&m,&start,&end);
    for(int i=0;i<=m-1;i++)
    {
            scanf("%d %d %d",&v1,&v2,&cost);//input edges
            e[i].c=cost;
            e[i].a=v1; e[i].b=v2; a[v1].adj.push_back(e[i]);
            //you add both only if bidirectional 
            e[m+i].c=cost;
            e[m+i].a=v2; e[m+i].b=v1; a[v2].adj.push_back(e[m+i]);
            //last edge on 2*m-1
    }
    possible=BellmanFord(start);
    if(a[end].d==FAKEMAXINT || !possible) printf("-1\n");//start and end are not connected
    else printf("%d\n",a[end].d);//distance
   //system("PAUSE");
}
/*
Practice task:
mit-indiv09-shtpaths
although it's pretty gay
*/
