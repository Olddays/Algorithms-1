//RandomUsername(Nikola Jovanovic)
//Segment Tree

//RangeMinimumQuery implementation, built on an array. 
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define MAXN 100
using namespace std;

int seg[2*MAXN]; //A segment tree is nearly twice as large as the array.
int a[MAXN]; //Basic array
int n,pom,ind,lq,dq;

void build(int i, int l, int d)//Building a segment tree.
{
 if (l>d) return;
 else if (d==l)//We hit the leaf.
 {
  seg[i] = a[d];
  return;
 }
 build(i*2, l, (d+l)/2);//Recurse
 build(i*2+1, (d+l)/2+1, d);//Recurse
 seg[i] = min(seg[i*2], seg[i*2+1]);//It's a RMQ so we take minimums.
}

void set(int i,int val,int index,int l,int d)
{
     if(d==l)
     {
             seg[i]=val; //first update leaf
     }
     else
     {
         if(index<=(d+l)/2)
          set(i*2,val,index,l,(d+l)/2);
         else set(i*2+1,val,index,(d+l)/2+1,d);
         seg[i] = min(seg[i*2], seg[i*2+1]);//after leaf update, update ancestors accordingly
     }
}

int get(int i, int lq, int dq, int l, int d)//get
{
     if (lq > d || dq < l)//no intersection with [lq,dq] (the query interval)
          return -1;
     else if(l>=lq && d<=dq)//[l,d] is in canonic cover of [lq,dq]
          return seg[i];
     int m1=get(2*i,lq,dq,l,(l+d)/2);//take both sons
     int m2=get(2*i+1,lq,dq,(l+d)/2+1,d);
     
     //pick the minimum
     if(m1==-1) return m2;
     if(m2==-1) return m1;
     if(m1<=m2) return m1;
     return m2;
}

void print(int i,int l,int d)//testing function
{
      printf("(%d-%d) : %d\n",l,d,seg[i]);
      if(l==d) return;
      print(2*i,l,(l+d)/2);
      print(2*i+1,(l+d)/2+1,d);
}

int main(int argc, char *argv[])
{
    //In
    scanf("%d",&n);
    for(int i=0;i<=n-1;i++) scanf("%d",&a[i]);
    build(1,0,n-1);
        print(1,0,n-1);
    //Set pom at ind
    scanf("%d %d",&pom,&ind);
    set(1,pom,ind,0,n-1);
        print(1,0,n-1);
    //Get on interval 1 - n-1
    scanf("%d %d",&lq,&dq);
    printf("%d",get(1,lq,dq,0,n-1));
    //Done
    system("PAUSE");
    return 0;
}
