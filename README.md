# bigint.h
这里是一个C++库，用来方便的使用高精度。

高精度容器bigint,支持输入输出流。支持以下操作：
```cpp
operator +(bigint a,bigint b)
operator =(string s)
operator =(bigint a,bigint b)
operator >(bigint a,bigint b)
operator <(bigint a,bigint b)
operator >=(bigint a,bigint b)
operator <=(bigint a,bigint b)
operator ==(bigint a,bigint b)
operator !=(bigint a,bigint b)
operator +=(bigint a,bigint b)
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
