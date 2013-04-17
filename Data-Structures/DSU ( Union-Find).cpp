//RandomUsername(Nikola Jovanovic)
//Union-Find(Disjoint Set Union)
//Implemented for: How Many Components? (z-trening)
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define MAXN 100010

using namespace std;

struct data
{
  int rank,p;//rank and parent
};

int n,q;
int v1,v2;
data uf[MAXN];//dsu
int xroot,yroot;
char command;
int components;

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

int main(int argc, char *argv[])
{
    scanf("%d %d",&n,&q); //graph with n vertices, 1 based...q queries
    components=n;//initial component number:n
    build();//build DSU
    for(int i=1;i<=q;i++)//process queries
    { 
         command='X';
         while( command != 'C' && command != 'A' )//Stupid input is stupid, ty Sasa.
               scanf( "%c", &command );//Just skip everything until you reach a command
          if(command=='A')
          {
            scanf("%d %d",&v1,&v2);
            if(connect(v1,v2)) components--;//if it connects two components
                                           //there's one component less. duh.
          }  
          else printf("%d ",components);
    }
    printf("\n");
    system("PAUSE");
    return  0;
}
 
