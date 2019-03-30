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
	struct bigint{
		vector<int> num;
		int len,f;
		bigint()
		{
			len=f=1;
			num.clear();
		}
		void update(int x,int j)
		{
			if(j==1)
			{
				while(x)
				{
					if(num.size()-1>=len+1) num[++len]=x%10;
					else num.push_back(x%10),len++;
					x/=10;
				}
			}
			else
			{
				if(j==2) while(num[len]==0&&len>1) len--;
				else
				{
					while(x)
					{
						if(num.size()-1>=len+1) num[++len]=x%10;
						else num.push_back(x%10),len++;
						x/=10;
					}
					while(num[len]==0&&len>1) len--;
				}
			} 
		}
		int& operator [](int index)
		{
			return num[index];
		}
		void operator =(bigint b)
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
			(*this).update(0,0);
		}
		void operator =(long long x)
		{
			*this=llong_to_string(x);
		}
		friend ostream& operator <<(ostream& out,bigint val)
		{
			if(val.f==-1) out<<'-';
			for(int i=val.len;i>=1;i--)
			{
				out<<val[i];
			}
			return out;
		}
		friend istream& operator >>(istream& in,bigint &val)
		{
			string s;
			in>>s;
			val=s;
			return in;
		}
		friend bool operator <(bigint a,bigint b)
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
		friend bool operator >(bigint a,bigint b)
		{
			return b<a;
		}
		friend bool operator !=(bigint a,bigint b)
		{
			return a>b||a<b;
		}
		friend bool operator ==(bigint a,bigint b)
		{
			return !(a!=b);
		}
		friend bool operator >=(bigint a,bigint b)
		{
			return !(a<b);
		}
		friend bool operator <=(bigint a,bigint b)
		{
			return !(a>b);
		}
		friend bigint operator +(bigint a,bigint b)
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
			bigint c;
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
			c.update(x,1);
			return c;
		}
		friend bigint operator -(bigint a,bigint b)
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
			bigint c;
			c.num.clear();
			c.num.push_back(0);
			if(a<b)
			{
				c.len=b.len;
				c.f=-1;
				for(int i=1;i<=c.len;i++)
				{
					if(i<=a.len) c.num.push_back(b[i]-a[i]);
					else c.num.push_back(b[i]);
					if(c[i]<0) b[i+1]--,c[i]+=10;
				}
			}
			else
			{
				c.len=a.len;
				c.f=1;
				for(int i=1;i<=c.len;i++)
				{
					if(i<=b.len) c.num.push_back(a[i]-b[i]);
					else c.num.push_back(a[i]);
					if(c[i]<0) a[i+1]--,c[i]+=10;
				}
			}
			c.update(0,0);
			return c;
		}
		friend bigint operator *(bigint a,bigint b)
		{
			bigint c;
			if(a.f==b.f) c.f=1;
			else c.f=-1;
			c.num.push_back(0);
			int x=0;
			c.len=0;
			for(int i=1;i<=a.len;i++,x=0)
			{
				for(int j=1;j<=b.len;j++)
				{
					if(i+j-1>c.len) c.num.push_back(a[i]*b[j]+x),c.len++;
					else c[i+j-1]+=a[i]*b[j]+x;
					x=c[i+j-1]/10;
					c[i+j-1]%=10;
				}
				c.update(x,1);
			}
			return c;
		}
		friend void operator +=(bigint &a,bigint b)
		{
			a=a+b;
		}
		friend void operator -=(bigint &a,bigint b)
		{
			a=a-b;
		}
		friend void operator *=(bigint &a,bigint b)
		{
			a=a*b;
		}
	};
}
std::bigint b_abs(std::bigint a)
{
	std::bigint c=a;
	c.f=1;
	return c;
}
#endif
