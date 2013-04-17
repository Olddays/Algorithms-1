//RandomUsername(Nikola Jovanovic)
//Binary Indexed Tree

#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

int n=10;
int a[10]={2,5,7,8,6,4,1,9,8,15};//Basic array
int mk[11];//misteriozna kumulativa AKA BIT.


int get(int i)//the get function, magic.
{
  int sum = 0;
	while (i >= 1)
    {
		sum += mk[i];
		i -= i & -i;
	}
	return sum;
}

void set(int i,int inc)//the set(increment by inc) function, magic.
{
	while (i <= n)
    {
		mk[i] += inc;
		i += i & -i;
	}
}

void build()//the build function, basic.
{
     for(int i=1;i<=n;i++)
      set(i,a[i-1]);
}

void print()//Testing
{
     for(int i=1;i<=10;i++)
     {
             printf("a:%d MK:%d SUM:%d\n",a[i-1],mk[i],get(i));
     }
}

int main(int argc, char *argv[])
{
    //test
    build();
    print();
    cout<<"Sum 1-3: "<<get(3)<<endl;
    cout<<"Sum 3-5: "<<get(5)-get(2)<<endl;
    cout<<"Sum  2-9: "<<get(9)-get(1)<<endl;
    set(4,10); cout<<"Incremented a[3] by 10."<<endl;
    set(1,3); cout<<"Incremented a[0] by 3."<<endl;
    cout<<"Sum 2-5: "<<get(5)-get(1)<<endl;
    //test
    system("PAUSE");
    return 0;
}
