//RandomUsername(Nikola Jovanovic)
//Heap
//Runtime: All operations in O(logn)
//Velja, how is this hard? Dude?

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
#define MAXN 1007

using namespace std;

int h[MAXN];
int lastel=0;

int top()
{
    return h[1];
}

void pop()
{
    h[1]=h[lastel--];
    int i=1;
    bool leaf=false;
    while(!leaf)
    {
            if(2*i+1<=lastel && h[2*i+1]>h[2*i] && h[2*i+1]>h[i])
             {
                 swap(h[i],h[2*i+1]);
                 i=2*i+1;
             }
            else if(2*i<=lastel && h[2*i]>h[2*i+1] && h[2*i]>h[i])
             {
                 swap(h[i],h[2*i]);
                 i*=2;
             }
            else leaf=true;
    }
}

void push(int x)
{
    h[++lastel]=x;
    int i=lastel;
    while(i!=1 && h[i/2]<h[i])
      {
          swap(h[i],h[i/2]);
          i/=2;
      }
}

bool Empty()
{
    return (lastel==0);
}

int Size()
{
    return lastel;
}

int main()
{
    push(2);
    push(6);
    push(1);
    push(7);
    printf("%d\n",top());//2 6 1 7
    pop();
    printf("%d\n",top());//2 6 1
    push(4);
    printf("%d\n",top());//2 6 1 4
    push(15);
    printf("%d\n",top()); //2 6 1 4 15
    while(!Empty())
        pop();
    printf("%d\n",Size());
    push(1); //-1
    printf("%d\n",top()); //1
}
