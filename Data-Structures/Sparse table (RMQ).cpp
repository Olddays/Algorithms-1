//RandomUsername (Nikola Jovanovic)
//Sparse table (RMQ)
//http://wiki.xfer.hr/konstantna/

#include <bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 20
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2

using namespace std;

/*
A structure that supports RMQ queries
Init : O(nlogn)
Query : O(1)
Update : /
Memory : O(nlogn)

Implemented for : http://www.spoj.com/problems/ARRAYSUB/
*/

//Maximum

int n, k;
int a[MAXN];
int cs[MAXLOGN][MAXN]; //cs[a][b] = max [ b, b + 2^a )
int pow2[MAXN]; //pow2[i] is the largest power of two not larger than i

void InitPow2() //precompute pow2[i]
{
  pow2[1] = 0; // 2^0 <= 1
  for (int i = 2; i < MAXN; i++)
    pow2[i] = pow2[i/2] + 1;
}

void Init() //initialize the structure
{
  for (int i = 1; i <= n; i++)
  {
    cs[0][i] = a[i]; //max [i, i+1) = a[i]
  }

  for(int deg = 0; (1 << deg) <= n; deg++) // calculate cs[deg][]
  {
    for(int i = 1; i <= n; i++) //calculate cs[deg][i]
    {
      // DP relation : cs[deg+1][b] = max(cs[deg][b], cs[deg][b + (1 << deg)])
      if(i + (1<<deg) <= n)
        cs[deg+1][i] = max( cs[deg][i], cs[deg][i + (1<<deg)] );
      else
        cs[deg+1][i] = cs[deg][i];
    }
  }
}

int Query(int a, int b)
{
  //max on [a,b]
  int fpt = pow2[b + 1 - a]; //fpt = pow2[interval_length]
  //max of first fpt and last fpt numbers in the interval
  //have to overlap (if they don't fpt can be larger)
  return max( cs[fpt][a], cs[fpt][b + 1 - (1 << fpt)] );
}

int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
    }
    scanf("%d", &k);
    InitPow2();
    Init();
    for(int i=1; i+k-1<=n; i++)
    {
        printf("%d ",Query(i, i+k-1));
    }
    //3 7 7 5
    return 0;
}
