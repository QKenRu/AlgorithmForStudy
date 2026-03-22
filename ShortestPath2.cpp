#include<iostream>
#include<algorithm>
#include<limits.h>
#include<stack>
#include<queue>
#include<vector>
/*
相较于ShortestPath.cpp，在根据贪心策略查找集合V-S中dist[]最小节点t的这部分操作改用了优先队列，使时间复杂度降至O(logn)。不过在使用优先队列优化的Dijkstra算法中，while语句
至少执行了n次，queue.pop()语句的时间复杂度为logn，用语执行松弛操作的for语句执行了n^2次，内部que.push()的时间复杂度为logn。因此，语句的总执行次数为nlogn+n^2logn，算法
的总时间复杂度为O(n^2logn)。若采用邻接表，则松弛操作就不用每次都执行n次了，而是执行节点t的邻接点数（t的出度）就可以了，所有节点的出度之和为边数e,于是算法的总时间复杂度
为O(nlogn+elogn)。一般情况下e>=n，因此时间复杂度为O(elogn)。
*/
void dijkstra(int n,int u,int *p,int *dist,int *flag,int **G);
void findpath(int n,int u,int *p,int *dist); //输出源点到其他各节点的路径

struct node
{
    int u,dis; //定义节点u以及源点到节点u的最短路径长度dis
    node(){}
    node(int _u,int _dis) //定义构造函数
    {
        u=_u; dis=_dis;
    }
    bool operator < (const node &a) const
    {
        return dis>a.dis; //重载优先级运算符“<”，dis越小越优先
    }
};

int main()
{
    int n,u,input;
    std::cout<<"请分别输入节点个数n、源点u。"<<std::endl;
    std::cin>>n>>u;
    int **G=(int**)malloc(sizeof(int*)*(n+1));
    for(int i=1;i<=n;++i)
    {
        G[i]=(int*)malloc(sizeof(int*)*(n+1));
        std::cout<<"请输入节点"<<i<<"分别到节点1至节点"<<n<<"的距离，若某节点到另一节点的距离为无穷大或者是另一节点是其自身，请输入任意负数。"<<std::endl;
        for(int j=1;j<=n;++j)
        {
            std::cin>>input;
            if(input<0)
            {
                G[i][j]=INT_MAX/2;
            }
            else
            {
                G[i][j]=input;
            }
        }
    }
    int *dist=(int*)malloc(sizeof(int)*(n+1));
    int *flag=(int*)malloc(sizeof(int)*(n+1));
    int *p=(int*)malloc(sizeof(int)*(n+1));

    dijkstra(n,u,p,dist,flag,G);
    findpath(n,u,p,dist);
    return 0;
}
void dijkstra(int n,int u,int *p,int *dist,int *flag,int **G)
{
    std::priority_queue<node>que; //创建优先队列
    for(int i=1;i<=n;++i)
    {
        dist[i]=INT_MAX/2; //初始化所有距离为无穷大
        flag[i]=false;
        if(dist[i]==INT_MAX/2)
        {
            p[i]=-1; //源点u到节点i的路径长度为无穷大，这说明源点u与节点i不相符
        }
        else
        {
            p[i]=u; //节点i是源点u的邻接节点，设置节点i的前驱节点为源点u
        }
    }
    dist[u]=0;
    node vs=node(u,0);
    que.push(vs);
    while(!que.empty())
    {
        node it=que.top(); //优先队列的队头元素为dist的最小值
        que.pop();
        int t=it.u;
        if(flag[t]) //说明已经找到最短路径，节点t是队列中的重复元素
            continue;
        flag[t]=true;
        for(int j=1;j<=n;++j) //执行松弛操作
        {
            if(!flag[j]&&dist[j]>dist[t]+G[t][j])
            {
                dist[j]=dist[t]+G[t][j];
                p[j]=t;
                que.push(node(j,dist[j])); //把更新后的最短路径压入优先队列
            }
        }
    }
}
void findpath(int n,int u,int *p,int *dist) //输出源点到其他各节点的路径
{
    int x;
    std::stack<int>s;
    std::cout<<"源点为："<<u<<std::endl;
    for(int i=1;i<=n;++i)
    {
        x=p[i];
        while(x!=-1)
        {
            s.push(x);
            x=p[x];
        }
        std::cout<<"源点到其他各节点的最短路径为：";
        while(!s.empty())
        {
            std::cout<<s.top()<<"--";
            s.pop();
        }
        std::cout<<i<<";最短路径长度为："<<dist[i]<<std::endl;
    }
}












