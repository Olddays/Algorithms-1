#include <bits/stdc++.h>
#define MAXN 100005
#define mid (l+r)/2

using namespace std;

//Segment Tree RMinQ Implementation
//Init O(N), Update O(log N), Query O(log N), memory bounded by 4N
//Practice Problem : http://www.spoj.com/problems/FREQUENT/

struct node //Node template
{
    bool NULLNODE; //useful for comparing
    int val;
    node()
    {
        NULLNODE = false;
    }
};

node segMerge(node a, node b) //RMinQ Merging
{
        //discard null values
        if(a.NULLNODE) return b;
        if(b.NULLNODE) return a;
        //actual comparison
        if(a.val < b.val)
            return a;
        return b;
}

int a[MAXN];
node seg[MAXN*4];


void Init(int idx, int l, int r)
{
    //First if missing, since you can't miss the point
    if(l == r)
    {
        //Leaf node
        seg[idx].val = a[l];
        return;
    }
    Init(2*idx, l, mid);
    Init(2*idx+1, mid + 1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1]);
}

void Update(int idx, node v, int vidx, int l, int r) // a[vidx] = v
{
    if(vidx>r || vidx<l)
    {
        return; //You missed the point
    }
    if(l == r) //Canonic cover is a single node
    {
        //Leaf node
        seg[idx] = v;
        return;
    }
    Update(2*idx, v, vidx, l, mid);
    Update(2*idx+1, v, vidx, mid+1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1]);
}

node Query(int idx, int lq, int rq, int l, int r) //[lq,dq] ?
{
    if(lq>r || rq<l)
    {
        node dummy;
        dummy.NULLNODE = true;
        return dummy;
    }
    if(l>=lq && r<=rq)
    {
        return seg[idx]; //Canonic cover
    }
    node leftChild = Query(2*idx, lq, rq, l, mid);
    node rightChild = Query(2*idx+1, lq, rq, mid+1, r);
    return segMerge(leftChild, rightChild);
}

int main()
{
    //Testing
    int n,q,kom;
    int vidx;
    node v;
    int lq,rq;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    Init(1, 1, n);
    scanf("%d",&q);
    for(int i=1; i<=q; i++)
    {
        scanf("%d",&kom);
        if(kom == 1) //update
        {
            scanf("%d %d",&vidx, &v.val);
            Update(1, v, vidx, 1, n);
        }
        else if(kom == 2) //query
        {
            scanf("%d %d",&lq,&rq);
            v = Query(1, lq, rq, 1, n);
            printf("%d\n",v.val);
        }
    }
    return 0;
}
