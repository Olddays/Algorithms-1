// RandomUsername(Nikola Jovanovic)
// Graham Scan (Convex Hull)
// O(nlogn)

#include <bits/stdc++.h>
#define MAXN 100005
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2

using namespace std;

/*
TP (http://oi59.tinypic.com/35b86pz.jpg):

IN:
15
-4 2    2 -4    4 -3    6 -2    -2 -1   3 2     -3 -4
4 3     2 6     5 3     4 6     -1 6    -1 2    0 -4    0 5

OUT:
7 14 2 3 4 10 11 9 12 1
*/

const double PI = 3.1415926535;

struct point
{
       double x, y;
       int idx;
       double ang; //the angle this point and the starting point make with the x-axis
       double qdist; //distance^2 from the starting point, for dealing with ang ties
       const bool operator < (const point b)
       const
       {
           if(ang == b.ang)
            return qdist < b.qdist;
           return ang < b.ang;
       }
};

int n; //number of points
point a[MAXN]; //all the points are stored here
point p; //starting point
vector<point> hull; //the hull is stored here

int turn(point p1, point p2, point p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    // cross product
    // <0 - right turn
    // >0 - left turn
    // =0 - collinear
}

void GrahamScan()
{
    hull.clear();

    //Starting point
    p = a[1];
    for(int i=2; i<=n; i++)
    {
        if( a[i].y < p.y || (a[i].y == p.y && a[i].x < p.x) )
            p = a[i];
    }

    //Calculate angles and sort
    for(int i=1; i<=n; i++)
    {
        //atan2: [-PI,PI]. p.y = miny => [0,PI]
        a[i].ang = atan2(a[i].y - p.y, a[i].x - p.x);
        a[i].qdist = (a[i].y - p.y) * (a[i].y - p.y) + (a[i].x - p.x) * (a[i].x - p.x);
    }
    sort(a+1, a+n+1);

    //Start the scan

    // intially, first two points are in the hull
    hull.push_back( a[1] );
    hull.push_back( a[2] );

    for(int i=3; i<=n; i++) //scan all the points
    {
        // we observe the turn last two points make with the point we're trying to introduce
        // while it's a right turn we discard the last hull point
        // we keep discarding until we can safely add a[i]
        // < - all points on the hull
        // <= - the least number of points on the hull (no 3 collinear)

        while( turn( hull[hull.size() - 2], hull[hull.size() - 1], a[i]) < 0 )
            hull.pop_back();
        hull.push_back(a[i]);
    }
}

int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%lf %lf", &a[i].x, &a[i].y);
        a[i].idx = i;
    }
    GrahamScan();

    //Output:
    printf("Convex hull:\n");
    for(int i=0; i<hull.size(); i++)
      printf("%d(%f, %f) ", hull[i].idx, hull[i].x, hull[i].y);

    return 0;
}
