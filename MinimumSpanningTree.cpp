/*这是Prim算法解决最小生成树问题
时间复杂度：找最小和更新的执行次数均为n，需要重复执行n-1次，总的执行次数均为n^2，算法的时间复杂度为O(n^2)。
空间复杂度：辅助空间为变量i,j以及数组lowcost[]和closest[]，算法的空间复杂度为O(n)。
优化拓展：1.在查找lowcost[]数组的最小值时使用优先队列，每次出队一个最小值，时间复杂度为logn，执行n次，查找的时间复杂度为O(nlogn)。
          2.在更新数组lowcost[]和closest[]时，如果采用邻接表存储图，那么每次只需要检查节点t的邻接点（邻接点的数量等于度数），所有节点的度数之和等于边的两倍，
            检查更新的次数为e（边数），每次将更新数据入队，入队的时间复杂度为logn，更新的时间复杂度为O(elogn)。
*/
#include<iostream>
#include<limits.h>
#include<float.h>
#include<stdlib.h>
int main()
{
    int n;
    std::cout<<"输入节点个数n"<<std::endl;
    std::cin>>n;
    double **G=(double**)malloc(sizeof(double*)*n);
    for(int i=0;i<n;++i)
    {
	/*如何输入边的权值端点集合，下列是让用户自行输入点之间的情况。当然更加简化的情况是让用户自行输入边之间的情况
	如果只输入边之间的情况，若是无向图，那么每次输入一条边存储在边集后需要再将这条边两端点对换再存储一次，这样for循环的边界需要乘2*/
        std::cout<<"输入节点"<<i<<"分别到所有节点的边的权值，如果权值为无穷大，或是节点到自身的边，输入任意负数。"<<std::endl;
        G[i]=(double*)malloc(sizeof(double)*n);
        for(int j=0;j<n;++j)
        {
            std::cin>>G[i][j];
            if(G[i][j]<0)
            {
                G[i][j]=DBL_MAX/2;
            }
        }
    }
    bool *flag=(bool*)malloc(sizeof(bool)*n);
    int *closest=(int*)malloc(sizeof(int)*n);
    double *lowcost=(double*)malloc(sizeof(double)*n);

//初始化
    flag[0]=true; //初始时，集合U只有一个元素，即节点0
    lowcost[0]=0;
    for(int i=1;i<n;++i)
    {
            lowcost[i]=G[0][i];
            closest[i]=0;
            flag[i]=false;
    }

    while(1)
    {
    //在集合V-U中寻找距离集合U最近的节点t
        double temp=DBL_MAX;
        int t=0;
        for(int j=0;j<n;++j) //在集合V-U中寻找lowcost[j]最小的节点t
        {
            if(!flag[j]&&lowcost[j]<temp)
            {
                t=j;
                temp=lowcost[j];
            }
        }
        if(t==0)
        {
            break; //找不到节点t，跳出循环。
        }

    //更新数组lowcost[]和closest[]
        flag[t]=true; //将节点t添加到集合U中
        for(int j=0;j<n;++j)
        {
            if(!flag[j]&&G[t][j]<lowcost[j])
            {
                lowcost[j]=G[t][j];
                closest[j]=t;
            }
        }
    }

//将数组lowcost[]中的所有值加起来，即可得到最小生成树的权值之和
    double sumcost=0;
    for(int i=0;i<n;++i)
    {
        sumcost+=lowcost[i];
    }
    std::cout<<"最小生成树的权值之和是："<<sumcost<<std::endl;
//输出各节点应该与哪些节点相连
    for(int i=0;i<n;++i)
    {
        std::cout<<"节点"<<i<<"应该与节点"<<closest[i]<<"相连接"<<std::endl;
    }
    return 0;
}






