/*
作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。在地图上显示有多个分散的城市和一些连接城市的快速道路。每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。当其他城市有紧急求助电话给你的时候，你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。

输入格式:
输入第一行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0 ~ (N−1)；M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号。

第二行给出N个正整数，其中第i个数是第i个城市的救援队的数目，数字间以空格分隔。随后的M行中，每行给出一条快速道路的信息，分别是：城市1、城市2、快速道路的长度，中间用空格分开，数字均为整数且不超过500。输入保证救援可行且最优解唯一。

输出格式:
第一行输出最短路径的条数和能够召集的最多的救援队数量。第二行输出从S到D的路径中经过的城市编号。数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
20 30 40 10
0 1 1
1 3 2
0 3 3
0 2 2
2 3 2
输出样例:
2 60
0 1 3
*/
#include<iostream>
#include<climits>
#include<stack>
int totalCity,totalFastRoad,startCity,destination;
int *rescueTeam,*visitedCity,*shortDist,*path,*curRescueTeam;
int **roadNet;
int *numOFroads; //记录到达某个节点时有多少条路
int shortestPath()
{
    while(1)
    {
        int tempdis=INT_MAX/2;
        int t=-1;
        for(int j=0;j<totalCity;++j)
        {
            if(!visitedCity[j]&&shortDist[j]<tempdis)
            {
                t=j;
                tempdis=shortDist[j];
            }
        }
        if(t==-1)
        {
            break;
        }
        visitedCity[t]=1;
        for(int j=0;j<totalCity;++j)
        {
            if(!visitedCity[j] && shortDist[j]==shortDist[t]+roadNet[t][j])
            {
                if(curRescueTeam[t]+rescueTeam[j]>curRescueTeam[j])
                {
                    curRescueTeam[j]=curRescueTeam[t]+rescueTeam[j];
                    path[j]=t;
                }
                numOFroads[j]+=numOFroads[t];
            }
            else if(!visitedCity[j] && shortDist[j]>shortDist[t]+roadNet[t][j])
            {
                curRescueTeam[j]=curRescueTeam[t]+rescueTeam[j];
                shortDist[j]=shortDist[t]+roadNet[t][j];
                path[j]=t;
                numOFroads[j]=numOFroads[t];
            }
        }
    }
    return numOFroads[destination];
}
void findPath()
{
    int x,numOFrescueteam=0;
    std::stack<int>S;
    x=destination;
    while(1)
    {
        if(x==path[x])
        {
            S.push(x);
            numOFrescueteam+=rescueTeam[S.top()];
            break;
        }
        S.push(x);
        numOFrescueteam+=rescueTeam[S.top()];
        x=path[x];
    }
    std::cout<<numOFrescueteam<<std::endl;
    while(!S.empty())
    {
        if(S.size()!=1)
            std::cout<<S.top()<<" ";
        else
            std::cout<<S.top();
        S.pop();
    }
    return;
}
int main()
{
    std::cin>>totalCity>>totalFastRoad>>startCity>>destination;
    rescueTeam=new int[totalCity];
    visitedCity=new int[totalCity](); //初始化为0
    shortDist=new int[totalCity];
    curRescueTeam=new int[totalCity];
    path=new int[totalCity];
    roadNet=new int*[totalCity];
    numOFroads=new int[totalCity](); //初始化为0
    for(int i=0;i<totalCity;++i)
    {
        std::cin>>rescueTeam[i];
        roadNet[i]=new int[totalCity];
        for(int j=0;j<totalCity;++j)
        {
            roadNet[i][j]=INT_MAX/2;
        }
    }
    for(int i=0;i<totalFastRoad;++i)
    {
        int s,e,d;
        std::cin>>s>>e>>d;
        roadNet[s][e]=d;
        roadNet[e][s]=d;
    }

    for(int i=0;i<totalCity;++i)
    {
        shortDist[i]=INT_MAX/2;
        curRescueTeam[i]=rescueTeam[i];
        visitedCity[i]=0;
        path[i]=i;
        numOFroads[i]=0;
    }
    shortDist[startCity]=0;
    curRescueTeam[startCity]=rescueTeam[startCity];
    numOFroads[startCity]=1;
    std::cout<<shortestPath()<<" ";
    findPath();
    return 0;
}
