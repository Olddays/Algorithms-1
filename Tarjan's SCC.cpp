//RandomUsername(Nikola Jovanovic)
//Computing strongly connected components, Tarjan's algorithm
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#define MAXN 100
using namespace std;

struct node
{
       int low,dfn;//dfs numbering, 'low'
       vector<int> adj;//neighbours
       bool onstack;
};

node a[MAXN];//graph
int n,m,b1,b2;
int dfscnt=1;//dfs numbering
stack<int> compvs;//output stack
int componentcount=1;//component count, duuh.

void PrintComponent(int v)//output v's component
{
    int x=-1;
    printf("Component %d: ",componentcount++);    
    while(x!=v)//pop from the output stack until you reach v
    {
         x=compvs.top();
         a[x].onstack=false;
         compvs.pop();
         printf("%d ",x);
    }
    printf("\n");
}

//l[v]=lowpoint[v]=min{dfn of v, min{lowpoint of v's children}
//dfn of a node that is obtained by a back edge from v or its children
void Tarjan(int v)
{
     compvs.push(v);  //add to the output stack
     a[v].onstack=true;//added
     a[v].dfn=dfscnt++;//update numbering
     a[v].low=a[v].dfn;//update low
     
     int limit=a[v].adj.size();
     int x;
     
     for(int i=0;i<limit;i++)//all neighbours
     {
        x=a[v].adj[i];//neighbour x
        if(a[x].dfn==0)//not visited 
        {
          Tarjan(x);//recurse
          a[v].low=min(a[v].low,a[x].low);//update low
        }
        else if(a[x].onstack)//if on stack
        {
          a[v].low=min(a[v].low,a[x].dfn);//update low
        }
     }
     if (a[v].low==a[v].dfn)//v is the head of a component, print v's subtree+v
       PrintComponent(v);   
}

int main(int argc, char *argv[])
{
      scanf("%d %d",&n,&m);//input
      for(int i=0;i<=m-1;i++)
       {
         scanf("%d %d",&b1,&b2);
         a[b1].adj.push_back(b2);//directed
       }
      Tarjan(0);//go!
      system("PAUSE");
      return 0;
}
/*
Testcase from http://en.wikipedia.org/wiki/Strongly_connected_component
Numbering is normal.
8 14
0 1
1 4
4 0
1 5
4 5
1 2
2 3
3 2
3 7
7 3
7 6
2 6
5 6
6 5
*/
