#include<iostream>
#include<algorithm>
#include<limits.h>
#include<stack>
/*
时间复杂度：找最小以及松弛操作本身各执行了n词，需要重复n-1次，总的执行次数为n^2，时间复杂度为O(n^2)。
空间复杂度：辅助空间为数组flag[],p[]以及变量i,j,t,temp等，空间复杂度为O(n)
*/
void findpath(int n,int u,int *p,int *dist); //输出源点到其他各节点的路径
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



    for(int i=1;i<=n;++i) //初始化
    {
        dist[i]=G[u][i]; //初始化源点u到其他各个节点的最短路径长度
        flag[i]=false;
        if(dist[i]==INT_MAX/2)
        {
            p[i]=-1; //源点u到节点i的路径长度为无穷大，这说明源点u与节点i不相邻
        }
        else
        {
            p[i]=u; //节点i是源点u的邻接节点，设置节点i的前驱为源点u
        }
    }
    flag[u]=true; //初始化集合S，其中只有源点u
    dist[u]=0; //初始化源点u到自身的最短路径长度为0

//循环进行“找最小”和“执行松弛操作”直至无法找到距离源点u最近的节点t
    while(1)
    {
        int temp=INT_MAX/2,t=u;
        for(int j=1;j<=n;++j) //在集合V-S中查找距离源点u最近的节点t
        {
            if(!flag[j]&&dist[j]<temp)
            {
                t=j;
                temp=dist[j];
            }
        }
        if(t==u)
        {
            break; //找不到节点t，跳出循环
        }
        flag[t]=true; //将节点t添加到集合S中
        for(int j=1;j<=n;++j) //更新节点t的邻接节点j的最短路径长度，执行松弛操作
        {
            if(!flag[j]&&dist[j]>dist[t]+G[t][j])
            {
                dist[j]=dist[t]+G[t][j];
                p[j]=t;
            }
        }
    }



    findpath(n,u,p,dist);
    return 0;
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












