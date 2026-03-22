/*这是Kruskal算法
时间复杂度：在对边进行排序时，若使用快速排序法，则时间复杂度为O(eloge)。在合并集合时，需要进行n-1次合并，由于每一次合并的时间复杂度为O(n)，
            因此合并的时间复杂度为O(n^2)
空间复杂度：辅助空间为数组nodeset[]，算法的空间复杂度为O(n)。不过本算法对于如何输入边的权值端点集合没有更好的办法，采用了邻接矩阵使得空间复杂度为O(n^2)。
优化拓展：合并集合的时间复杂度为O(n^2)，可以利用并查集进行优化，使合并集合的时间复杂度降至O(elogn)。/
*/
#include<iostream>
#include<climits>
#include<float.h>
#include<algorithm>
typedef struct Edge //边的存储集合
{
    int u,v; //边的两个端点
    double w; //权值
}Edge;
Edge *e;
int *nodeset; //集合号数组，相同集合号的节点表示这些节点已经连通
int n; //节点个数
bool cmp(Edge x,Edge y) //定义优先级，按边值进行升序排序
{
    return x.w<y.w;
}

bool merge(int u,int v) //合并集合
{
    int p=nodeset[u]; //p为节点u的集合号
    int q=nodeset[v];
    if(p==q) return false; //如果集合号相同，返回
    for(int i=0;i<n;++i) //检查所有节点，把集合号是q的改为p
    {
        if(nodeset[i]==q)
        {
            nodeset[i]=p;
        }
    }
    return true;
}

int kruskal() //求最小生成树
{
    double ans=0;
    int connectedPoint=1;
    for(int i=0;i<(n*n);++i)
    {
        if(merge(e[i].u,e[i].v))
        {
            ans+=e[i].w;
            ++connectedPoint;
            if(connectedPoint==n)
            {
                return ans;
            }
        }
    }
    std::cout<<"该图无法生成最小生成树";
    return -1;
}

int main()
{
    std::cout<<"输入节点个数n"<<std::endl;
    std::cin>>n;
    nodeset=new int[n]; //集合号数组
    for(int i=0;i<n;++i)
    {
        nodeset[i]=i; //为每个节点初始化一个集合号
    }
    e=new Edge[n*n];
    /*如何输入边的权值端点集合，下列是让用户自行输入点之间的情况。当然更加简化的情况是让用户自行输入边之间的情况
	如果只输入边之间的情况，若是无向图，那么每次输入一条边存储在边集后需要再将这条边两端点对换再存储一次，这样for循环的边界需要乘2*/
    int m=0;
    double **G=(double**)malloc(sizeof(double*)*n);
    for(int i=0;i<n;++i)
    {
        std::cout<<"输入节点"<<i<<"分别到所有节点的边的权值，如果权值为无穷大，或是节点到自身的边，输入任意负数。"<<std::endl;
        G[i]=(double*)malloc(sizeof(double)*n);
        for(int j=0;j<n;++j)
        {
            std::cin>>G[i][j];
            if(G[i][j]<0)
            {
                G[i][j]=DBL_MAX/2;
                e[m].u=i;
                e[m].v=j;
                e[m++].w=G[i][j];
            }
            else
            {
                e[m].u=i;
                e[m].v=j;
                e[m++].w=G[i][j];
            }
        }
    }
    std::sort(e,e+(n*n),cmp); //对边集按边权值大小进行升序排序
    std::cout<<"最小生成树的权值："<<kruskal()<<std::endl;
    return 0;
}


