//RandomUsername(Nikola Jovanovic)
//Kruskal's algorithm for MST
//O(E log E) <=> O(E log V)
//Prim<=>Kruskal except Prim can't work on disconnected graphs 
//and compute MSForests, while Kruskal can.
#include <cstdlib>
#include <iostream>
#include <stdio.h>
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

struct data//struct for DSU
{
  int rank,p;//rank and parent
};

bool cmp(edge a,edge b)
{
     return a.w<b.w;
}

data uf[MAXN];//dsu
int xroot,yroot;

int n,m;
int v1,v2,weight;
node a[MAXN];//the graph,actually not needed here but nvm
edge pom;
edge e[MAXN];//all the edges
edge mst[MAXN];//array of edges in mst 1 - n-1 edges
int it;//iterator: where to put the next mst edge
int mstsum;//sum of mst weights

void build()
{
     for(int i=1;i<=n;i++)
      {
        uf[i].p=i;             //every vertex is a head of it's own component
        uf[i].rank=0;          //all ranks are 0 (Union by rank optimization)
      } 
}

int find(int x)
{
    //Path compression
    if( uf[x].p!=x )//If he's not the head
     uf[x].p=find(uf[x].p);//Connect him directly to the head when you finish
    return uf[x].p;//return head
}
      
bool connect(int x,int y)//returns true if connected, false if already connected
{
     xroot=find(x);//find roots
     yroot=find(y);//find roots
     if(xroot==yroot)
      return false; //already connected
      
     //Union by rank:
     if(uf[xroot].rank<uf[yroot].rank)
         uf[xroot].p=yroot;
     else if(uf[yroot].rank<uf[xroot].rank)
         uf[yroot].p=xroot;
     else//same rank
     {
         uf[yroot].p=xroot;
         uf[xroot].rank++;
     }
     return true;
}

void Kruskal()
{
     it=1;//mst edges go from mst[1] to mst[n-1]
     build();//build DSU
     sort(e,e+m,cmp);//sort the edges by weight
     for(int i=0;i<=m-1;i++)//go through all the edges
     {
       if(connect(e[i].a,e[i].b))//if you can connect two of them
       {                         //do it, and reduce the number of components.
           mstsum+=e[i].w;       //At the end: 1 component <=> MST
           mst[it].a=e[i].a; mst[it].b=e[i].b; mst[it].w=e[i].w;
           it++;
           //add it to mst[]                
       }
     }
}

int main(int argc, char *argv[])
{
     //input
      scanf("%d %d",&n,&m);
      for(int i=0;i<=m-1;i++)
      {
             scanf("%d %d %d",&v1,&v2,&weight);//1 based graph
             e[i].w=weight;
             
             e[i].a=v1; e[i].b=v2;
             a[v1].adj.push_back(e[i]);
             
             e[i].a=v2; e[i].b=v1; //Only if bidirectional
             a[v2].adj.push_back(e[i]); 
      }
    Kruskal();
    printf("Minimum spanning tree:\n");
    for(int i=1;i<=n-1;i++)
     printf("Edge %d - %d ( Weight: %d )\n",mst[i].a,mst[i].b,mst[i].w);
    printf("Sum of weights: %d\n",mstsum);
    system("PAUSE");
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

