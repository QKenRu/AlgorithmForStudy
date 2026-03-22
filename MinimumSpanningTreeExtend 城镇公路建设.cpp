/*
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多公路。

输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例:
12
*/
/*最小生成树，Prim算法或Kruskal算法
本题点集与边集比例不小于1:3，属于稀疏图，Kruskal算法更有优势*/
#include<iostream>
#include<climits>
#include<float.h>
#include<algorithm>
int totalTown,totalRoad;
typedef struct Edge
{
    int point1,point2;
    int weight;
}Edge;
Edge *edgeSet;
int *nodeSet;
bool cmp(Edge x,Edge y)
{
    return x.weight<y.weight; //对于结构体Edge，按照边权值进行升序排序
}
bool merge(int p1,int p2)
{
    int p=nodeSet[p1];
    int q=nodeSet[p2];
    if(p==q)
    {
        return false; //集合号相同，返回
    }
    for(int i=1;i<=totalTown;++i)
    {
        if(nodeSet[i]==q)
        {
            nodeSet[i]=p;
        }
    }
    return true;
}
int Kruskal()
{
    int ans=0,connectedTown=1; //connectedTown表示已连接的城镇树
    for(int i=0;i<totalRoad*2;++i)
    {
        if(merge(edgeSet[i].point1,edgeSet[i].point2))
        {
            ans+=edgeSet[i].weight;
            ++connectedTown;
            if(connectedTown==totalTown)
            {
                return ans;
            }
        }
    }
    return -1; //仍然有城镇未连接的情况
}
int main()
{
    std::cin>>totalTown>>totalRoad;
    edgeSet=new Edge[totalRoad*2]; //下标从0开始
    nodeSet=new int[totalTown+1]; //城镇编号是从1开始的
    for(int i=0;i<totalRoad*2;i+=2)
    { //这是无向图需要每次输入一条边后复制一条端点相反的边，所以循环边界要乘2
        std::cin>>edgeSet[i].point1>>edgeSet[i].point2>>edgeSet[i].weight;
        edgeSet[i+1].point1=edgeSet[i].point2;
        edgeSet[i+1].point2=edgeSet[i].point1;
        edgeSet[i+1].weight=edgeSet[i].weight;
    }
    for(int i=1;i<=totalTown;++i)
    {
        nodeSet[i]=i; //为每个节点初始化一个集合号
    }
    std::sort(edgeSet,edgeSet+totalRoad*2,cmp); //对边集按边权值大小进行升序排序
    int MST=Kruskal();
    std::cout<<MST;
    return 0;
}
