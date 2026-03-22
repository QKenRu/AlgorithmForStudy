#include<iostream>
#include<algorithm>
struct Meet
{
    int beg,end; //会议的开始时间和结束时间
};
bool cmp(Meet x,Meet y)
{
    if(x.end==y.end) //结束时间相同时
    {
        return x.beg>y.beg; //按开始时间从晚到早排序
    }
    return x.end<y.end; //按结束时间从早到晚排序
}
int solve(int n,Meet* meet);
int main()
{
    int n;
    std::cout<<"请输入会议总数n"<<std::endl;
    std::cin>>n;
    Meet *meet=(Meet*)malloc(sizeof(Meet)*n);
    for(int i=0;i<n;++i)
    {
        std::cout<<"请分别输入会议"<<i<<"的开始时间与结束时间"<<std::endl;
        std::cin>>meet[i].beg>>meet[i].end;
    }
    std::cout<<solve(n,meet)<<std::endl;
    return 0;
}
int solve(int n,Meet* meet)
{
    std::sort(meet,meet+n,cmp); //对会议按结束时间进行递增排序
    int ans=0;
    int last=0;
    for(int i=0;i<n;++i)
    {
        if(meet[i].beg>=last) //如果会议i的开始时间晚于或等于刚才所选会议的结束时间
        {
            ++ans;
            last=meet[i].end; //记录刚才所选会议的结束时间
        }
    }
    return ans;
}
