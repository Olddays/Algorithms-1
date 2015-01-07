#include <bits/stdc++.h>
#define MAXN 100005
#define mid (l+r)/2

using namespace std;

//Segment Tree With Lazy Propagation
//RminQ with interval increment updates
//Practice task : http://www.spoj.com/problems/HORRIBLE/

struct node //Node template
{
    bool NULLNODE; //useful for comparing
    int val;
    int lazy;
    node()
    {
        NULLNODE = false;
        lazy = 0;
    }
};

node segMerge(node a, node b, int currLazy) //RMinQ Merging
{
        //discard null values
        if(a.NULLNODE) return b;
        if(b.NULLNODE) return a;
        a.lazy = b.lazy = currLazy;

        //actual comparison
        if(a.val < b.val)
            return a;
        return b;
}

int a[MAXN];
node seg[MAXN*4];

void Print(int idx, int l, int r)
{
    //First if missing, since you can't miss the point
    if(l == r)
    {
        cout<<"["<<l<<","<<r<<"] : "<<seg[idx].val<<" "<<seg[idx].lazy<<endl;
        return;
    }
    Print(2*idx, l, mid);
    Print(2*idx+1, mid + 1, r);
    cout<<"["<<l<<","<<r<<"] : "<<seg[idx].val<<" "<<seg[idx].lazy<<endl;
}

void Init(int idx, int l, int r)
{
    //First if missing, since you can't miss the point
    seg[idx].lazy = 0;
    if(l == r)
    {
        //Leaf node
        seg[idx].val = a[l];
        return;
    }
    Init(2*idx, l, mid);
    Init(2*idx+1, mid + 1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1], seg[idx].lazy);
}

void Update(int idx, node v, int vil, int vir, int l, int r) // a[vil..vir] += v (just vals here)
{
    //Lazy Propagation, first!
    //We can use this form of lazy propagation because RMinQ and Update are additive and have the same impact on every node
    //Which is not the case in http://www.spoj.com/problems/HORRIBLE/
    if(seg[idx].lazy != 0) //There is a mark here
    {
        seg[idx].val += seg[idx].lazy; //Update
        if(l != r) //Propagate if not a leaf
        {
            seg[2*idx].lazy += seg[idx].lazy;
            seg[2*idx+1].lazy += seg[idx].lazy;
        }
        seg[idx].lazy = 0; //Reset
    }

    if(vil>r || vir<l)
    {
        return; //You missed the point
    }

    if(l>=vil && r<=vir) //Canonic cover
    {
        seg[idx].val += v.val;
        if(l != r) //Propagate if not a leaf
        {
            seg[2*idx].lazy += v.val;
            seg[2*idx+1].lazy += v.val;
        }
        return;
    }
    Update(2*idx, v, vil, vir, l, mid);
    Update(2*idx+1, v, vil, vir, mid+1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1], seg[idx].lazy);
    //cout<<idx<<" "<<seg[idx].val<<" "<<seg[idx].lazy<<" "<<l<<" "<<r<<endl;
}

node Query(int idx, int lq, int rq, int l, int r) //[lq,dq] ?
{
    //Lazy Propagation, first!
    //Actually here it should go second according to tutorials, but why not here for the sake of symmetry?
    if(seg[idx].lazy != 0) //There is a mark here
    {
        seg[idx].val += seg[idx].lazy; //Update
        if(l != r) //Propagate if not a leaf
        {
            seg[2*idx].lazy += seg[idx].lazy;
            seg[2*idx+1].lazy += seg[idx].lazy;
        }
        seg[idx].lazy = 0; //Reset
    }

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
    return segMerge(leftChild, rightChild, seg[idx].lazy);
}

int main()
{
     //Testing
    int n,q,kom;
    int vil,vir;
    node v;
    int lq,rq;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    Init(1, 1, n);
    //Print(1, 1, n);
    scanf("%d",&q);
    for(int i=1; i<=q; i++)
    {
        scanf("%d",&kom);
        if(kom == 1) //update
        {
            scanf("%d %d %d",&vil, &vir, &v.val);
            Update(1, v, vil, vir, 1, n);
        }
        else if(kom == 2) //query
        {
            scanf("%d %d",&lq,&rq);
            v = Query(1, lq, rq, 1, n);
            printf("%d\n",v.val);
        }
    //Print(1, 1, n);
    }
    return 0;
}
