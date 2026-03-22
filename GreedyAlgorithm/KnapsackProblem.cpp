#include<iostream>
#include<algorithm>
#include<stdlib.h>
struct node
{
    double w; //每种物品的重量
    double v; //每种物品的价值
    double p; //每种物品的单位重量价值(价值/重量)
};
bool cmp(node a,node b) //自定义比较函数
{
    return a.p>b.p; //指定按照物品的单位重量价值进行排序
}
double solve(int n,double W,node* item);
int main()
{
    int n;
    double W;
    std::cout<<"输入物品个数n与背包容量W"<<std::endl;
    std::cin>>n>>W;
    node *item=(node*)malloc(sizeof(node)*n);
    for(int i=0;i<n;++i)
    {
        std::cout<<"分别输入物品"<<i<<"的重量与价值"<<std::endl;
        std::cin>>item[i].w>>item[i].v;
        item[i].p=item[i].v/item[i].w;
    }
    std::sort(item,item+n,cmp); //前两个参数分别为待排序数组的首地址和尾地址，cmp为比较函数
    std::cout<<solve(n,W,item)<<std::endl;
    return 0;
}
double solve(int n,double W,node* item)
{
    double sum=0.0; //sum表示已装入物品的价值之和
    double cleft=W; //背包的剩余容量
    for(int i=0;i<n;++i)
    {
        if(item[i].w<=cleft)
        {
            cleft-=item[i].w;
            sum+=item[i].v;
        }
        else
        {
            sum+=cleft*item[i].p;
            break;
        }
    }
    return sum;
}
