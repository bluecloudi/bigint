# bigint.h V1.0.1
这里是一个C++库，用来方便的使用高精度。

高精度整数容器bigint,支持输入输出流、比较大小、++、--和五则运算（加、减、乘、除、%）。亦支持以下操作：
```cpp
operator bigint <<(bigint a,long long b) //将a在十进制中向左移b位
operator bigint >>(bigint a,long long b) //将a在十进制中向右移b位
```
下面是一个例子：
```cpp
#include<bigint.h>
#include<iostream>
using namespace std;
int main()
{
  bigint a,b;
  cin>>a>>b;
  cout<<a+b<<endl;
  return 0;
}
```
仍在更新中，请大家支持。
