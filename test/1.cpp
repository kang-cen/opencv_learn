#include<iostream>
using namespace std;

int main()
{
        int a[5]={1,2,3,4,5};
        int* ptr=a;
        for(int i=0;i<5;i++)
        {
            *ptr++=a[i];//先用后++，那么++什么呢？应该是++地址 所以指向下一位
            cout<<"i= "<<i<<"  ptr value  "<<*ptr<<endl;
            cout<<"a["<<i<<"]="<<a[i]<<endl;
        }
        return 0;

}