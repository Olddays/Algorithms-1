//RandomUsername(Nikola Jovanovic)
//Dijkstra's algorithm (Shortest paths)
//Implemented for task: highwayz (z-trening)
//Runtime:E+VlogV, single source, only nonnegative egde weights
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#define MAXN 100010
#define FAKEMAXINT 2000000000
using namespace std;
 
struct edge
{
       int b,c;//b-neighbour number, c-the price
};

struct node
{
      vector<edge> adj;//neighbours
      bool visited;//visited?
      int d;//distance
      int from;//possible reconstruction of the path
};

struct data
{
       int num,d;
};

node a[MAXN];//the graph

struct cmp//compare function for the heap
{
       
  bool operator()
  (const data x,const data y)
  const
  {
       return x.d>y.d;
  }
  
};

int n,m,start,end,v1,v2,cost;
int limit,curr,next;
edge pom;
priority_queue<data,vector<data>,cmp> h;//heap
data temp;

void Dijkstra(int start)
{
     for(int i=1;i<=n;i++)
       a[i].d=FAKEMAXINT;//set initial distances to maxint
       
     a[start].d=0;
     temp.d=0; temp.num=start; h.push(temp);//begin with start
     while(!h.empty() && !a[end].visited)//end when you explore the component/reach the end
     {
          curr=h.top().num;
          h.pop(); //current node, we always pick a node from the top of the heap(min dist)
          if(!a[curr].visited)//if not already visited
          {
             a[curr].visited=true;//visit it
             limit=a[curr].adj.size();
             for(int i=0;i<=limit-1;i++)//go through all the neighbours
             {
               next= a[curr].adj[i].b;
               if(!a[next].visited && a[curr].d + a[curr].adj[i].c < a[next].d )
               {//if you should update the distance, go update it
                  a[next].d = a[curr].d + a[curr].adj[i].c;
                  a[next].from = curr;
                  temp.d=a[next].d; temp.num=next; h.push(temp);//add next to the heap
               }
             }
          }     
     }
}

int main(int argc, char *argv[])
{
    //input, 1 based numbering
    scanf("%d %d %d %d",&n,&m,&start,&end);
    for(int i=1;i<=m;i++)
    {
            scanf("%d %d %d",&v1,&v2,&cost);
            pom.c=cost;
            pom.b=v2;  a[v1].adj.push_back(pom);
            pom.b=v1;  a[v2].adj.push_back(pom);//only if bidirectional
    }
    Dijkstra(start);
    if(!a[end].visited) printf("-1\n");//start and end are not connected
    else printf("%d\n",a[end].d);
   //system("PAUSE");
}
