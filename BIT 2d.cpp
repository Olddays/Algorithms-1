//RandomUsername(Nikola Jovanovic)
//BIT 2D (Implement for the task: MATSUM(SPOJ))

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define MAXN 1024
using namespace std;

long long bit[MAXN+1][MAXN+1];//BIT
int t,n,i1,j1,i2,j2,val,sum=0;
char pom[5];

void set(int i,int j,int val)//Works like 1D just with one more nested loop.
{
    int j1;
    while(i<=n)
    {
                  j1=j;
                  while(j1<=n)
                  {
                    bit[i][j1]+=val;
                    j1+=(j1 & -j1);
                  }
                  i+=(i & -i);
    }
}

long long get(int i,int j)//Works like 1D just with one more nested loop.
{
    int j1;
    long long sum=0;
    while(i>=1)
    {
                  j1=j;
                  while(j1>=1)
                  {
                    sum+=bit[i][j1];
                    j1-=(j1 & -j1);
                  }
                  i-=(i & -i);
    }
    return sum;
}

int get_sq(int i1,int j1,int i2,int j2)//Inclusion-exclusion principle for rect sum(sq=rect)
{
    long long sum=get(i2,j2)-get(i1-1,j2)-get(i2,j1-1)+get(i1-1,j1-1);
    int ret=sum;
    return ret;
}


int clear()//duh.
{
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      bit[i][j]=0;
}

int main(int argc, char *argv[])
{
           //Task related stuff, only impotant stuff:
            scanf("%d",&n);
            clear();
            pom[2]='X';
            while(pom[2]!='D')//END
            {
               scanf("%s",pom);
               if(pom[2]=='T')//SET
               {
                       scanf("%d %d %d",&i1,&j1,&val);
                       val-=get_sq(i1+1,j1+1,i1+1,j1+1);//Because we wanna set the value 
                       //of matrix[i1][j1] to val, and BIT works with increments, what
                       //we do first is read what is actually the value of matrix[i1][j1]
                       //and adjust val so that it's an increment
                       set(i1+1,j1+1,val);//Thus, we increment
               }
               else if(pom[2]=='M')//SUM
               {
                       scanf("%d %d %d %d",&i1,&j1,&i2,&j2);
                       sum=get_sq(i1+1,j1+1,i2+1,j2+1); //This. We get a sum of a rectangle.                      printf("%d\n",sum);   
               }
            }
    
    system("PAUSE");
    return 0;
}
