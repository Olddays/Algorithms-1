//RandomUsername(Nikola Jovanovic)
//Heap (STL)
//Fuck you Velja .i. :*
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>
#define MAXN 100
using namespace std;
 
struct heapdata//a structure we will use in our heap
{
       int x,y,num;//some ints
};

struct cmp//a structure used when comparing two main structures
{
    bool operator()
    (const heapdata a,const heapdata b)//don't const ask me how const this works const 
    const
    {
         if(a.x==b.x)//like a normal operator from here
          return a.y<b.y;
         return a.x<b.x;
    }
};

priority_queue<heapdata,vector<heapdata>,cmp> q;//second argument is a container (vector)
heapdata pom;
int main(int argc, char *argv[])
{
    //pushing(logn)
    pom.x=5; pom.y=15; pom.num=1;
    q.push(pom);
    pom.x=5; pom.y=17; pom.num=2;
    q.push(pom);
    pom.x=2; pom.y=23; pom.num=3;
    q.push(pom);
    
    //reading(logn)
    while(!q.empty())
    {
      pom=q.top();
      q.pop();
      printf("%d\n",pom.num);//heap will print them sorted
      //it's a maxheap(minheap) so the max(min) goes first
      //I will never learn what is max and what is min
      //You can always flip the cmp function to find out ;)
    }
    system("PAUSE");
}
/*
Test task: burici (z-trening)
*/
