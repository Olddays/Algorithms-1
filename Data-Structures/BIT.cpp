#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

//BIT
//Update O(log N), Query O(log N)
//Practice task: http://www.codechef.com/problems/SPREAD/
//Practice task: http://www.spoj.com/problems/INVCNT/

int n; //Array size
int a[MAXN]; //Array
int bit[MAXN]; //BIT

void Update(int i, int inc) // a[i]+=inc;
{
    while(i <= n)
    {
        bit[i] += inc;
        i += (i & -i);
    }
}

int Query(int i) // a[1]+..+a[i]
{
    int ret = 0;
    while(i >= 1)
    {
        ret += bit[i];
        i -= (i & -i);
    }
    return ret;
}

int RangeQuery(int l, int r)
{
    return Query(r) - Query(l-1);
}

int main()
{
    //Testing
    int q;
    int idx, inc;
    int l, r, kom;
    scanf("%d",&n);
    scanf("%d",&q);
    for(int i=1; i<=q; i++)
    {
        scanf("%d",&kom);
        if(kom == 1) //increment by inc
        {
            scanf("%d %d",&idx, &inc);
            Update(idx, inc);
        }
        else if(kom == 2) //sum [l,r]
        {
            scanf("%d %d",&l, &r);
            printf("%d\n",RangeQuery(l, r));
        }
    }
    return 0;
}
