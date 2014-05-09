//RandomUsername(Nikola Jovanovic)
//LCA
//<O(N logN), O(logN)>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#define MAXN 1010
#define LOGMAXN 11

using namespace std;

struct node
{
  vector<int> adj;//adjacency list
  int l,t;//level, tata
};

int n,m;
int v1,v2,logn;
node a[MAXN];//the tree
int dp[MAXN][LOGMAXN];//dp
//dp[i][j] is 2^jth ancestor of i

int log(int x)//simple function for computing log(x) cuz I know no better
{
      int ret=0;
      while(x>0)//just divide it while it's positive
      {
                 x/=2;
                 ret++;
      }
      return ret;
}

void Bfs()//simple bfs, used for finding the levels and the fathers of all nodes
{
     int curr,next,limit;
     queue<int> q;
     a[1].l=1;
     a[1].t=1;
     q.push(1);//start from root (node 1)
     while(!q.empty())
     {
       curr=q.front();
       q.pop();
       limit=a[curr].adj.size();
       for(int i=0;i<=limit-1;i++)//browse the adjacency list
       {
         next=a[curr].adj[i];
         if(a[next].l==0)//visit unvisited
         {
           a[next].l=a[curr].l+1;//set their level
           a[next].t=curr;      //and the father
           q.push(next);
         }
       }
     }
}

//so we initalize our dp[][]:
void Initialize()
{
     
     for(int i=1;i<=n;i++)
      for(int j=0;j<=logn;j++)
        dp[i][j]=-1;  //initialize on -1...
       
     for(int i=1;i<=n;i++)
      dp[i][0] = a[i].t;//...2^0th(1st) ancestor is a father
     
     //Dynamic programming:
     for(int j=1;j<=logn;j++)//fill all the columns
      for(int i=1;i<=n;i++)//fill all the rows
       if(dp[i][j-1]!=-1)// (1)
          dp[i][j] = dp[ dp[i][j-1] ][j-1];//(2)
     //(1) - If I got no 2^j-1 ancestor I also have no 2^j ancestor
     //(2) - My 2^j ancestor = my 2^j-1 ancestor's 2^j-1 ancestor
}

int Query(int p,int q)    //  Note: 1<<i <=> 2^i
{
      int logg=0;
      
      //WLOG q is closer to root (higher level)
      //if not, we swap
      if (a[p].l<a[q].l)
            swap(p,q);
            
      //we compute the value of log(level(p))
      //it's important as a bound for our search
      //(later log(a[q].l)?)
      logg=log(a[p].l);
      
      //we find the ancestor of p
      //on the same level as q
      for(int i=logg;i>=0;i--)
         if(a[p].l - (1<<i) >= a[q].l)//when p's level minus 2^i becomes larger
            p=dp[p][i];               //than q's level, we continue from that spot
   
      if (p == q)//if they are the same we found the lca
          return p;
   
     //now that we know they are on the same level
     //we compute LCA(p, q) using the values in dp[][]
     //similiar method as when we were searching for p's ancestor
      for(int i=logg;i>=0;i--)
         if(dp[p][i]!=-1 && dp[p][i]!=dp[q][i])//if their current ancestor isn't
           {                                   //the same we must go even higher
              p=dp[p][i];                      //so why not continue the search 
              q=dp[q][i];                      //with their respective ancestors
           }
      //we brought p and q very close (1 level under LCA), 
      //only thing left to do is return their father's value.
      return a[p].t;
}


int main(int argc, char *argv[])
{
     //input
      scanf("%d %d",&n,&m);
      logn=log(n);
      for(int i=0;i<=m-1;i++)
      {
             scanf("%d %d",&v1,&v2);//1 based graph
             a[v1].adj.push_back(v2);
             a[v2].adj.push_back(v1);//bidirectional 
      }
    Bfs();//Let's see what we're working with
    Initialize();//Some DP shit about to go down
    printf("Input queries:\n");//Bring it on, sucker
      int p,q,lca;
      while(1)
      {
              scanf("%d %d",&p,&q);
              printf("Level[p]:%d\n",a[p].l);
              printf("Level[q]:%d\n",a[q].l);
              lca=Query(p,q);//Simple as that
              printf("LCA:%d\n",lca);
              printf("Level[LCA]:%d\n",a[lca].l);
      }
    system("PAUSE");
    return  0;
}
