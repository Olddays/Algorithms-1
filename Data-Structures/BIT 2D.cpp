#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

//BIT 2D
//Update O(log^2 N), Query O(log^2 N)
//Practice task: http://www.codechef.com/problems/MATSUM/

using namespace std;

int n, m; //n x m matrix
int a[MAXN][MAXN]; //matrix
int bit[MAXN][MAXN]; //BIT

//Works like 1D just with one more nested loop

void Update(int i,int j,int inc)
{
    int j1;
    while(i <= n)
    {
                  j1 = j;
                  while(j1 <= m)
                  {
                    bit[i][j1] += inc;
                    j1 += (j1 & -j1);
                  }

                  i += (i & -i);
    }
}

int Query(int i,int j)
{
    int ret = 0;
    int j1;
    while(i >= 1)
    {
                  j1 = j;
                  while(j1 >= 1)
                  {
                    ret += bit[i][j1];
                    j1 -= (j1 & -j1);
                  }

                  i -= (i & -i);
    }
    return ret;
}

int RectangleQuery(int i1, int j1, int i2, int j2) //Inc-Exc
{
    return Query(i2, j2) - Query(i1 - 1, j2) - Query(i2, j1 - 1) + Query(i1 - 1, j1 - 1);
}

int main()
{
    //Testing
    int q;
    int i1, j1, i2, j2, inc;
    int l, r, kom;
    scanf("%d %d",&n, &m);
    scanf("%d",&q);
    for(int i=1; i<=q; i++)
    {
        scanf("%d",&kom);
        if(kom == 1) //increment by inc
        {
            scanf("%d %d %d",&i1, &j1, &inc);
            Update(i1, j1, inc);
        }
        else if(kom == 2) //sumRectangle (i1,j1) - (i2,j2)
        {
            scanf("%d %d %d %d",&i1, &j1, &i2, &j2);
            printf("%d\n",RectangleQuery(i1, j1, i2, j2));
        }
    }
    return 0;
}
