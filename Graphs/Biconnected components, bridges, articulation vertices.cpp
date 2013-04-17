//RandomUsername(Nikola Jovanovic)
//Computing biconnected components, bridges and articulation vertices (nearly Tarjan)
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#define MAXN 100
using namespace std;

struct node
{
       int dfn,level,low,comp;//dfs numbering, dfs level, 'low', current component 
       vector<int> adj;//adjacency list
       bool art;//is art.p.
};

struct edge
{
 int a,b;
};

node a[MAXN];//graph
int n,m,v1,v2;
int dfscnt=1;//dfs numbering
int ccnt=1;//component numbering
stack<edge> compvs;//component reconstruction
edge pom;

void PrintComponent(int v,int x)//Printing components
{
   printf("Component %d:",ccnt++);
   pom.a=-1; pom.b=-1;
   while(!(pom.a==v && pom.b==x))//pop edges from the stack until you reach (v-x)
   {
        pom=compvs.top();
        compvs.pop();
        if(a[pom.a].comp!=ccnt)//if not visited in this iteration
        {
                 printf("%d ",pom.a);
                 a[pom.a].comp=ccnt;
        }
        if(a[pom.b].comp!=ccnt)//if not visited in this iteration
        {
                 printf("%d ",pom.b);
                 a[pom.b].comp=ccnt;
        }
   }
   printf("\n");
}

//l[v]=lowpoint[v]=min{dfn of v, min{lowpoint of v's children}
//dfn of a node that is obtained by a back edge from v or its children
void bcc_art_bridge(int v,int lvl)
{
     a[v].dfn=dfscnt++;//set dfn
     a[v].level=lvl;//set level
     a[v].low=a[v].dfn;//update low
     
     int limit=a[v].adj.size();
     int x,y;
     
     for(int i=0;i<limit;i++)//all neighbours
     {
        x=a[v].adj[i];//neighbour x
        if(a[x].dfn==0)//not visited
        {
           pom.a=v; pom.b=x; compvs.push(pom); //put on reconstruction stack
           bcc_art_bridge(x,lvl+1);//recurse
           a[v].low=min(a[v].low,a[x].low);//update low
           if(a[x].low>=a[v].dfn)//v is an articulation vertex
           {
              if(!a[v].art)//if this is the first time we discover v as an art.p.
              {
                cout<<"Art. point: "<<v<<endl;
                a[v].art=true;
              }
              PrintComponent(v,x);
           }
           if(a[x].low>a[v].dfn) //v-x is a bridge
              cout<<"Bridge: "<<x<<"-"<<v<<endl;
      
         
        }
        else if(a[x].level<a[v].level-1)// x-v is a back egde
        {
           pom.a=v; pom.b=x; compvs.push(pom); //put on reconstruction stack
           a[v].low=min(a[v].low,a[x].dfn); //update low
        }
     }
}

int main(int argc, char *argv[])
{
      scanf("%d %d",&n,&m);//input
      for(int i=0;i<=m-1;i++)//0-based numbering
       {
         scanf("%d %d",&v1,&v2);
         a[v1].adj.push_back(v2);
         a[v2].adj.push_back(v1);
       }
      if(a[0].adj.size()>1)//we deal with root differently
       {
          a[0].art=true;
          cout<<"Art. point: "<<0<<endl;//>1 neighbour => he is an art. v.
       }
      bcc_art_bridge(0,1);//go! The output is chaotic..
      system("PAUSE");
      return 0;
}
/*
Testcase from http://en.wikipedia.org/wiki/Biconnected_component
Vertex numbering=from the middle. For no reason.
14 16
1 2
2 3
0 3
0 1
0 4
4 5
5 6
6 7
6 9
9 8
9 10
10 11
11 12
12 13
11 13
13 6
*/
