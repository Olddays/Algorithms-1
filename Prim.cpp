#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#define MAXN 1000

using namespace std;

struct edge
{
  int a,b,w;//edge from a to b with weight w
};

struct node
{
  vector<edge> adj;//adjacency list
  bool visited;//visited?
};

struct cmp//edge comparator for our heap. Just compares weights
{
    bool operator()
    (const edge x,const edge y)
    const
    {
         return x.w>y.w;
    }
};


int n,m;
int v1,v2,weight;
node a[MAXN];//the graph
edge pom;
edge mst[MAXN];//array of edges in mst 1 - n-1 edges
int mstsum;//sum of mst weights

void Prim()//Prim dies in the third book.
{
    priority_queue<edge,vector<edge>,cmp> h;//heap
    edge pom,next;
    int curr,limit;
    
    //You can pick any vertex as a starting vertex, let's say 1
    a[1].visited=true;//we visited it 
    curr=1;//it's the current one
    for(int i=1;i<=n-1;i++)//take n-1 edges, after that you must have MST
    {
            limit=a[curr].adj.size();
            for(int j=0;j<=limit-1;j++)//add all neighbours who are not visited
            {                          //(add edges from curr to them)
              pom.a=a[curr].adj[j].a;
              pom.b=a[curr].adj[j].b;
              pom.w=a[curr].adj[j].w;
              if(!a[pom.b].visited)//if not visited
                h.push(pom);
            }
            pom=h.top();//we want the edge from the top of the heap
            h.pop();
            while(a[pom.b].visited)//but not those who contain visited vertices at both ends
            {
              pom=h.top();
              h.pop();
            }
            a[pom.b].visited=true;//new node is visited
            mst[i]=pom;//add it to mst[]
            curr=pom.b;//make it current
            mstsum+=pom.w;//increase mstsum
    }
}

int main(int argc, char *argv[])
{
     //input
      scanf("%d %d",&n,&m);
      for(int i=0;i<=m-1;i++)
      {
             scanf("%d %d %d",&v1,&v2,&weight);//1 based graph
             pom.w=weight;
             pom.a=v1; pom.b=v2;
             a[v1].adj.push_back(pom);
             pom.a=v2; pom.b=v1; //Only if bidirectional
             a[v2].adj.push_back(pom); //Only if bidirectional
      }
    prim();
    printf("Minimum spanning tree:\n");
    for(int i=1;i<=n-1;i++)
     printf("Edge %d - %d ( Weight: %d )\n",mst[i].a,mst[i].b,mst[i].w);
    printf("Sum of weights: %d\n",mstsum);
    //system("PAUSE");
    return  0;
}
/*
Test case taken froM: http://en.wikipedia.org/wiki/Minimum_spanning_tree
10 21
1 2 3
1 3 9
1 6 6
2 6 4
2 3 9
2 4 9
3 4 8
4 5 8
2 5 2
5 6 2
5 7 9
6 7 9
7 4 7
3 10 18
10 4 10
4 9 9
9 10 3
8 10 4
8 9 1
9 7 5
8 7 4
*/
