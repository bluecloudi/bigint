#ifndef bigint
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
std::string llong_to_string(long long x)
{
	std::string s;
	if(x<0) s.push_back('-'),x=abs(x);
	while(x)
	{
		s.push_back(x%10+'0');
		x/=10;
	}
	return s;
}

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
		void update(int x)
		{
			while(num[len]==0&&len>1) len--;
			while(x)
			{
				if(num.size()>=len+1) num[++len]=x%10;
				else num.push_back(x%10),len++;
				x%=10;
			}
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
			num.clear();
			num.push_back(0);
			for(int i=1,c=s.size();i<=len;i++)
			{
				num.push_back(s[c-i]-'0');
			}
			(*this).update(0);
		}
		void operator =(long long x)
		{
			*this=llong_to_string(x);
		}
		friend ostream& operator <<(ostream& out,BigInt val)
		{
			if(val.f==-1) out<<'-';
			for(int i=val.len;i>=1;i--)
			{
				out<<val[i];
			}
			return out;
		}
		friend istream& operator >>(istream& in,BigInt &val)
		{
			string s;
			in>>s;
			val=s;
			return in;
		}
		friend bool operator <(BigInt a,BigInt b)
		{
			if(a.f==-1&&b.f==1) return true;
			if(a.f==1&&b.f==-1) return false;
			if(a.f==1)
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
			else
			{
				if(a.len>b.len) return true;
				if(a.len<b.len) return false;
				for(int i=a.len;i>=1;i--)
				{
					if(a[i]>b[i]) return true;
					if(a[i]<b[i]) return false;
				}
				return false;
			}
		}
		friend bool operator >(BigInt a,BigInt b)
		{
			return b<a;
		}
		friend bool operator !=(BigInt a,BigInt b)
		{
			return a>b||a<b;
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
		friend BigInt operator +(BigInt a,BigInt b)
		{
			BigInt c;
			if(a.f==1) c.f=1;
			else c.f=-1;
			c.len=max(a.len,b.len);
			c.num.clear();
			c.num.push_back(0);
			int x=0;
			for(int i=1,p=0;i<=c.len;i++,p=0)
			{
				if(a.len>=i) p+=a[i];
				if(b.len>=i) p+=b[i];
				p+=x;
				c.num.push_back(p);
				x=c[i]/10;
				c[i]%=10;
			}
			c.update(x);
			return c;
		}
	};
	#define bigint BigInt
}
#endif
