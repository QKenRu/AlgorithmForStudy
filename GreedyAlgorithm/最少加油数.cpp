/*
一辆加满油的汽车欲行驶到m公里外的终点，旅途中有若干加油站，并且每个加油站距离起点的公里数已知，汽车加满油后可行驶n公里。如何用最少的加油次数到达目的地。

输入格式:
第一行输入终点公里数m，和汽车加满油可行驶的公里数n，以及加油站的个数k。第二行输入k个整数分别代表从起点到终点的k个加油站距离起点的公里数。

输出格式:
输出最少的加油次数。

输入样例:
在这里给出一组输入。例如：

10 6 3
2 5 9
输出样例:
在这里给出相应的输出。例如：

1
*/
#include<iostream>
int main()
{
    int m,n,k,i;
    int curPosition=0;
    int count=0;
    int *gasStation,*visitedGS;
    std::cin>>m>>n>>k;
    gasStation=new int[k+1];
    visitedGS=new int[k+1]();
    for(i=1;i<=k;++i)
    {
        std::cin>>gasStation[i];
    }
    while(curPosition<m)
    {
        if(curPosition+n>=m)
        {
            break;
        }
        for(i=k;i>=1;--i)
        {
            if(curPosition+n>=gasStation[i] && visitedGS[i]!=1)
            {
                ++count;
                curPosition=gasStation[i];
                visitedGS[i]=1;
                break;
            }
        }
        if(i==0)
        {
            std::cout<<"The car is not able to achieve the destination.";
            return 0;
        }
    }
    std::cout<<count;
    return 0;
}
