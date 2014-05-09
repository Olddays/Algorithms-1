//RandomUsername(Nikola Jovanovic)
//Basic Geometry

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
#define MAXN 1000
#define lld long long

using namespace std;

struct point
{
    lld x,y;
};

int n;

lld dist(point a,point b)
{
	return sqrt( (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y) );
}

lld cross_product(point a,point b,point c)//ABxBC
{
    return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y);
    //>0 - left turn
    //<0 - right turn
    //=0 - collinear
}

double pointdis(point a,point b,point c) //dist(C,AB)
{
	return cross_product(a,b,c)/dist(a,b);
}

lld side(point a,point b,point c,point d)//A,B -> line |CD|
{
    return cross_product(c,d,a)*cross_product(c,d,b);
    //>0 = same turn = same side of |CD|
    //<0 = diff turn = diff side of |CD|
    //=0 = A or B on CD
}

bool intersect(point a,point b,point c,point d)//|AB| and |CD|
{
    if( side(a,b,c,d)<=0 && side(c,d,a,b)<=0 &&
    min(a.x,b.x)<=max(c.x,d.x) && min(c.x,d.x)<=max(a.x,b.x) &&
    min(a.y,b.y)<=max(c.y,d.y) && min(c.y,d.y)<=max(a.y,b.y) )
    return true;
    else return false;
    //lines intersect with segments + the projections intersect
}

double poly_area(point* pol)//area of the ccw polygon
{
	double p=0;
	int i=0,j=n-1;
	for(i=0;i<=n-1;i++)
	{
		p+=(pol[i].x+pol[j].x)*(pol[j].y-pol[i].y);
		j=i;
	}
	return p/2.0;
	//summing the projections
}

lld gcd(lld a,lld b)
{
   if(b==0) return a;
   return gcd(a,b);
}

lld poly_edge(point* pol)//Z points on the edge of the polygon
{
	lld s=0;
	for(int i=0;i<=n-1;i++)
 	{
		s+=gcd( abs(pol[i].x - pol[(i+1)%n].x), abs(pol[i].y - pol[(i+1)%n].y) );
	}
	return s;
}

lld inside(point* pol)//Z points inside the poly (Pick's theorem)
{
    lld a=poly_area(pol), b=poly_edge(pol);
	return a+1-b/2.0;
}

lld pip(point* pol,point x)//point in polygon
{
	//TODO:
	//1. Connecting x to outer space and checking intersections
	//2. Checking if leftturn(all sides of the polygon, x)
	//3. Connect pol[0] and pol[i] and check left turns
	//4. 3 using binary search
}

int main()
{
    return 0;
}
