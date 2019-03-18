#ifndef bigint
#include<iostream>
#include<vector>
namespace std
{
	struct BigInt{
		vector<int> num;
		int len,f;
		BigInt()
		{
			len=f=1;
			num.clear();
		}
		int& operator [](int index)
		{
			return num[index];
		}
		void operator =(BigInt b)
		{
			len=b.len;
			f=b.f;
			num=b.num;
		}
		void operator =(string s)
		{
			if(s[0]=='-') f=-1,len=s.size()-1;
			else f=1,len=s.size();
			int c=s.size();
			for(int i=1;i<=len;i++)
			{
				num[i]=s[c-i]-'0';
			}
		}
		friend istream& operator >>(istream& in,BigInt &val)
		{
			string s;
			in>>s;
			val=s;
			return in;
		}
		friend ostream& operator <<(ostream& out,const BigInt &val)
		{
			if(val.f==-1) out<<'-';
			for(int i=val.len;i>=1;i--)
			{
				out<<val.num[i];
			}
			return out;
		}
		friend BigInt operator +(BigInt a,BigInt b)
		{
			if(a.f==-1&&b.f==1)
			{
				a.f=1;
				return b-a;
			}
			if(a.f==1&&b.f==-1)
			{
				b.f=1;
				return a-b;
			}
			BigInt c;
			if(a.f==1) c.f=1;
			else c.f=-1;
			c.len=max(a.len,b.len);
			int i,x=0;
			for(i=1;i<=c.len;i++)
			{
				c[i]=a[i]+b[i]+x;
				x=c[i]/10;
				c[i]%=10;
			}
			if(x) c[++c.len]=x;
			return c;
		}
		friend BigInt operator -(BigInt a,BigInt b)
		{
			if(a.f==-1&&b.f==1)
			{
				b.f=-1;
				return a+b;
			}
			if(a.f==1&&b.f==-1)
			{
				b.f=1;
				return a+b;
			}
			if(a.f==-1&&b.f==-1)
			{
				a.f=1;
				b.f=1;
				return b-a;
			}
			BigInt c;
			if(a<b)
			{
				c.f=-1;
				c.len=b.len;
				for(int i=1;i<=b.len;i--)
				{
					c[i]=b[i]-a[i];
					if(c[i]<0) c[i]+=10,b[i+1]--;
				}
				while(c[c.len]==0&&c.len>1) c.len--;
			}
			else
			{
				c.f=1;
				c.len=a.len;
				for(int i=1;i<=a.len;i--)
				{
					c[i]=a[i]-b[i];
					if(c[i]<0) c[i]+=10,a[i+1]--;
				}
				while(c[c.len]==0&&c.len>1) c.len--;
			}
			return c;
		}
		friend bool operator <(BigInt a,BigInt b)
		{
			if(a.len<b.len) return true;
			if(a.len>b.len) return false;	
			for(int i=a.len;i>=1;i--)
			{
				if(a[i]<b[i]) return true;
				if(a[i]>b[i]) return false;
			}
			return false;
		}
		friend bool operator >(BigInt a,BigInt b)
		{
			return b<a;
		}
		friend bool operator !=(BigInt a,BigInt b)
		{
			return b<a||a>b;
		}
		friend bool operator ==(BigInt a,BigInt b)
		{
			return !(a!=b);
		}
		friend bool operator >=(BigInt a,BigInt b)
		{
			return !(a<b);
		}
		friend bool operator <=(BigInt a,BigInt b)
		{
			return !(a>b);
		}
		friend BigInt operator +=(BigInt a,const BigInt &b)
		{
			BigInt c=a+b;
			return c;
		}
		friend BigInt operator -=(BigInt a,const BigInt &b)
		{
			BigInt c=a-b;
			return c;
		}
	};
	#define bigint BigInt
}
#endif
