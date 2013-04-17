//RandomUsername(Nikola Jovanovic)
//Floyd-Warshall algorithm (All pairs shortest paths)
//Runtime:V^3, works for negative edge weights, negative cycles=>bad values+reported
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#define MAXN 1000
#define MAXM MAXN*MAXN
#define FAKEMAXINT 1000000000
using namespace std;
 
struct edge
{
       int a,b,c;//a-b is the edge, c-the price
};

struct node
{
      vector<edge> adj; //adjacency list, not used in the actual algorithm, but often needed
                        //adj[i].a is not important here but nvm
};

node a[MAXN];//the graph
edge e[2*MAXM];//the edges
int d[MAXN][MAXN];//distance matrix
int path[MAXN][MAXN];//path matrix (explained in FW function)

int n,m,start,end,v1,v2,cost;
bool negcyc=false;//negative cycles flag
queue<int> ret;//output queue (when reconstructing the path)

void FloydWarshall()
{
    //d[i][j] = distance from i to j
    //path[i][j] = node with the largest number on the path from i to j
    
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      d[i][j]=FAKEMAXINT;
     //First, set all the distances to MAXINT
      
    for(int i=1;i<=n;i++)
     d[i][i]=0; 
     //Distance to yourself is zero.
     
    for(int i=0;i<=2*m-1;i++)
     d[ e[i].a ][ e[i].b ]= e[i].c;
     //Direct edges reduce original distances.
    
    for(int k=1;k<=n;k++)//Use first k nodes...
     for(int i=1;i<=n;i++)//...to compute a path from i...
       for(int j=1;j<=n;j++)//...to j.
        if(d[i][k]+d[k][j]<d[i][j])//If you can use k to obtain a better route
         {
           d[i][j]=d[i][k]+d[k][j];//do it
           path[i][j]=k; //remember: k is the highest index needed on path from i to j
         }               //used for recovery
   
     for(int i=1;i<=n;i++)
      if(d[i][i]<0) {negcyc=true; return;} 
     //If a node can reach itself with negative cost negative cycles exist.
}

void PathReconstruction(int start,int end)//Reconstructs the path based on the next[][] matrix.
{
     int next=path[start][end];
     if(next==0)//There is a direct edge from start to end, add them to the queue
     {
        ret.push(start);
        ret.push(end);
     }
     if(next!=0)//Path start-end goes through next, solve recursively.
     {
         PathReconstruction(start,next);
         PathReconstruction(next, end);
     }
}

void PrintMatrix()//Simply prints the distance matrix
{    
   for(int i=1;i<=n;i++)
     {
       for(int j=1;j<=n;j++)
          printf("%d ",d[i][j]);
       printf("\n");
     }
}
     
void PrintPath(int start,int end)
{
     if(d[start][end]!=FAKEMAXINT)//If it's reachable
     {
        printf("Path:");
        PathReconstruction(start,end);//Reconstruct the path
        int curr;
        while(!ret.empty())//Print the vertices from the queue
        {
          curr=ret.front();
          ret.pop();
          if(ret.empty() || curr!=ret.front()) //Some vertices are pushed twice because
            printf(" %d",curr);                //of my ugly implementation. This prints
        }                                      //them in right order, feel free to implement
        printf(". Distance: %d.\n",d[start][end]);//this differently.
     } 
     else printf("No path.\n");
}    

int main(int argc, char *argv[])
{
    //input, 1 based numbering
    scanf("%d %d",&n,&m);
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
    FloydWarshall();//Do the algorithm and report if there are negative cycles
    if(negcyc) printf("Negative cycles exist! The results may be wrong.\n");
    //PrintMatrix(); //Prints the whole matrix of distances.
    start=1; end=n; //Arbitary values
    PrintPath(start,end);//Prints the distance from start to end, and the path.
    //system("PAUSE");
}
