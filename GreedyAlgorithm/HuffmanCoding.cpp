/*
时间复杂度：在霍夫曼树构建函数HuffmanTree()中，外层i与内层j组成了双重循环，基本语句共执行(n-1)*(3n-2)/2次；在霍夫曼编码求解函数HuffmanCode()中，编码和输出编码的
            时间复杂度都接近n^2，因此总算法的时间复杂度为O(n^2)。
空间复杂度：存储空间主要耗费在节点结构体数组与编码结构体数组上，霍夫曼编码数组HuffNode[]中的节点有n个，每个节点都包含bit[maxbit]和start两个域，其中maxbit通常取n，
            因此算法空间复杂度为O(n*maxbit)即O(n*n)即O(n^2)。
拓展优化：1.在函数HuffmanTree()中，当寻找权值最小的节点时使用优先队列，时间复杂度为logn，执行n-1次，总的时间复杂度为O(nlogn)；
          2.在函数HuffmanCode()中，通过在霍夫曼编码数组HuffNode[]中定义一个动态数组来存储编码，可以极大地节省空间。
*/
#include<iostream>
#include<algorithm>
#include<limits.h>
#include<float.h>
typedef struct
{ //节点结构体
    double weight; //权值
    int parent; //双亲
    int lchild; //左子节点
    int rchild; //右子节点
    char value; //节点表示的字符
}HNodeType;

typedef struct
{ //编码结构体
    int *bit; //编码存储数组
    int start; //编码开始下标
}HCodeType;

void HuffmanTree(HNodeType *HuffNode,int n) //构建霍夫曼树
{
    for(int i=0;i<2*n-1;++i) //初始化，因为合并会产生额外的n-1个节点，所以霍夫曼总节点数为2*n-1
    {
        HuffNode[i].weight=0;
        HuffNode[i].parent=-1;
        HuffNode[i].lchild=-1;
        HuffNode[i].rchild=-1;
    }
    for(int i=0;i<n;++i)
    {
        std::cout<<"输入第"<<i<<"个子节点的表示字符和权值"<<std::endl;
        std::cin>>HuffNode[i].value>>HuffNode[i].weight;
    }
    double m1,m2; //两个最小权值节点的权值，m1为最小值，m2为次小值
    int x1,x2; //两个最小权值节点的编号
    for(int i=0;i<n-1;++i) //执行n-1次合并
    {
        m1=m2=DBL_MAX; //初始化为最大值
        x1=x2=-1; //初始化为-1
        for(int j=0;j<n+i;++j) //查找两个无双亲且权值最小的节点
        {
            if(HuffNode[j].parent==-1&&HuffNode[j].weight<m1)
            {
                m2=m1;
                x2=x1;
                m1=HuffNode[j].weight;
                x1=j;
            }
            else if(HuffNode[j].parent==-1&&HuffNode[j].weight<m2)
            {
                m2=HuffNode[j].weight;
                x2=j;
            }
        }
        HuffNode[x1].parent=n+i; //x1的父节点为编号为n+i的新节点
        HuffNode[x2].parent=n+i; //x2同上
        HuffNode[n+i].weight=m1+m2; //新节点的权值为两个最小权值之和
        HuffNode[n+i].lchild=x1; //新节点的左子节点为x1
        HuffNode[n+i].rchild=x2; //新节点的右子节点为x2
    }
}

void HuffmanCode(HCodeType *HuffCode,HNodeType *HuffNode,int n) //霍夫曼编码
{
    HCodeType cd; //定义临时变量cd，用于存放解码时的信息
    cd.bit=(int*)malloc(sizeof(int)*n);
    int c,p;
    for(int i=0;i<n;++i)
    {
        c=i;
        p=HuffNode[c].parent;
        cd.start=n-1;
        while(p!=-1)
        {
            if(HuffNode[p].lchild==c)
            {
                cd.bit[cd.start]=0;
            }
            else
            {
                cd.bit[cd.start]=1;
            }
            --cd.start; //前移一位
            c=p;
            p=HuffNode[c].parent;
        }
        //把叶子节点的编码信息从临时变量cd中复制过来，放入编码结构体数组
        for(int j=cd.start+1;j<n;++j)
        {
            HuffCode[i].bit[j]=cd.bit[j];
        }
        HuffCode[i].start=cd.start;
    }
}

int main()
{
    int n;
    std::cout<<"输入霍夫曼树的叶子节点个数n"<<std::endl;
    std::cin>>n;
    HNodeType *HNT=(HNodeType*)malloc(sizeof(HNodeType)*(2*n-1));
    HCodeType *HCT=(HCodeType*)malloc(sizeof(HCodeType)*n);
    for(int i=0;i<n;++i)
    {
        HCT[i].bit=(int*)malloc(sizeof(int)*n);
    }
    HuffmanTree(HNT,n);
    HuffmanCode(HCT,HNT,n);
    std::cout<<"各叶子节点编号所表示字符、权值与霍夫曼编码如下"<<std::endl;
    for(int i=0;i<n;++i)
    {
        std::cout<<"叶子节点编号："<<i<<"，表示字符："<<HNT[i].value<<"，权值："<<HNT[i].weight<<"，霍夫曼编码：";
        for(int j=HCT[i].start+1;j<n;++j)
        {
            std::cout<<HCT[i].bit[j];
        }
        std::cout<<std::endl;
    }
    return 0;
}



