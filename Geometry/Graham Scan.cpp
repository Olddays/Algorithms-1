//RandomUsername(Nikola Jovanovic)
//Graham Scan(Convex Hull) (nlogn)
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#define MAXN 10000

using namespace std;

const double PI = 3.1415926;

struct point
{
       int num;//all the points are numbered (input)
       int x,y; //coordinates
       double ang;//the angle this point and the starting point make with the x-axis
};

int n;//number of points
point points[MAXN];//all the points are stored here
int p,py,px;
vector<point> hull;//the hull is stored here
int hullsize;

bool cmp(point a,point b)//compare two points by their angles
{
     return a.ang<b.ang;
}

int turn(point p1, point p2, point p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    //cross product based
    //returns <0 if right turn, >0 if left turn, =0 when colinear
}

void Graham()//The algorithm
{
    //We found the starting point (during the input), now calculate the angles
    //every point and the starting point make with the x-axis
    double ylen,xlen;//lengths of sides
    for(int i=0;i<=n-1;i++)
     {  
         ylen=(double)(points[i].y-points[p].y);
         xlen=(double)(points[i].x-points[p].x);
         points[i].ang=atan2(ylen,xlen);//atan 2: [-PI,PI]. p=miny => [0,PI]
     }
    sort(points,points+n,cmp);//Do the harlem shake!
    //First two points must be in the hull, so add them to the vector and increase hullsize
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hullsize=2;
    point a=hull[0],b=hull[1],curr;//deep copies? yep! c# would fail here!
    //Do the scan:
    for(int i=2;i<=n-1;i++)//scan all the points
    {
            //a and b is the last fixed pair and we are now inspecting curr
            curr=points[i];
            while( turn(a,b,curr)>0 )//while not left turn or colinear:
            {                        //(colinears are taken cuz we need all the points on c.h.)
                   hull.pop_back();  //rollback!
                   hullsize--;       //remove the middle point, and try to match the others
                   a = hull[hullsize - 2];//second to last valid point
                   b = hull[hullsize - 1];//last valid point
            }
            hull.push_back(curr);//when curr is finaly satisfying the conditions
            hullsize++;          //add it to the hull and increase currsize
            a=b;                 //also, update the triplet 
            b=curr;              //we're observing
    }
}

int main()
{
    scanf("%d",&n);
    scanf("%d %d",&points[0].x,&points[0].y);//numbered from 0, the dots are. #yoda
    points[0].num=0;
    p=0, py=points[0].y, px=points[0].y;       //detecting a starting point
    for(int i=1;i<=n-1;i++)
    {
            scanf("%d %d",&points[i].x,&points[i].y);
            points[i].num=i;
            if(points[i].y<py || (points[i].y==py && points[i].x<px))//update starting point
                p=points[i].num, py=points[i].y, px=points[i].y;
    }
    Graham();//Do the scan
    //Print the hull:
    printf("Convex hull:\n");
    for(int i=0;i<=hullsize-1;i++)
      printf("%d ",hull[i].num);
    printf("\n");
    
    system("PAUSE");
    return 0;
}
/*
Test case:
10
1 -1
0 2
-3 -3
5 -2
4 1
6 3
2 5
1 -1
-3 5
-4 0
http://upload.wikimedia.org/wikipedia/commons/d/de/ConvexHull.svg
Stupid numbering, ignore it.
*/
