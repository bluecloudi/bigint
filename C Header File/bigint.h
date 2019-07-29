#ifndef bigint
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
namespace std
{
	struct bigint{
		vector<int> num;
		long long len,f;
		bigint()
		{
			len=f=1;
			num.clear();
		}
		bigint(const bigint &b)
		{
			len=b.len;
			f=b.f;
			num=b.num;
		}
		bigint(int n)
		{
			num.clear();
			if(n==0)
			{
				f=1;len=1;
				num.push_back(0);num.push_back(0);
			}
			else
			{
				if(n<0)
				{
					f=-1;
					n=abs(n);
				}
				else f=1;
				num.push_back(0);
				while(n)
				{
					num.push_back(n%10);
					len++;
					n/=10;
				}
			}
                        
		}
		bigint(long long n)
		{
			num.clear();
			if(n==0)
			{
				f=1;len=1;
				num.push_back(0);num.push_back(0);
			}
			else
			{
				if(n<0)
				{
					f=-1;
					n=abs(n);
				}
				else f=1;
				num.push_back(0);
				while(n)
				{
					num.push_back(n%10);
					len++;
					n/=10;
				}
			}
		}
		bigint(char c[])
		{
			if(c[0]=='-') f=-1,len=strlen(c)-1;
			else f=1,len=strlen(c);
			num.clear();
			num.push_back(0);
			for(int i=1,p=strlen(c);i<=len;i++)
			{
				num.push_back(c[p-i]-'0');
			}
			(*this).update(0,0);
		}
		bigint(string s)
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
		void operator =(char c[])
		{
			if(c[0]=='-') f=-1,len=strlen(c)-1;
			else f=1,len=strlen(c);
			num.clear();
			num.push_back(0);
			for(int i=1,p=strlen(c);i<=len;i++)
			{
				num.push_back(c[p-i]-'0');
			}
			(*this).update(0,0);
		}
		void operator =(long long n)
		{
			int t=0;
			num.clear();
			if(n==0) f=1,len=1,num.push_back(0),num.push_back(0);
			else
			{
				if(n<0) f=-1,n=abs(n);
				else f=1;
				num.push_back(0);
				while(n)
				{
					num.push_back(n%10);
					t++;
					n/=10;
				}
				len=t;
			}
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
		friend bigint operator +(bigint a,string b)
		{
			return a+(bigint)(b);
		}
		friend bigint operator +(string a,bigint b)
		{
			return (bigint)(a)+b;
		}
		friend bigint operator +(string a,string b)
		{
			return (bigint)(a)+(bigint)(b);
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
		friend bigint operator <<(bigint a,long long b)
		{
			bigint c;
			c.f=a.f;
			c.num.clear();
			c.num.push_back(0);
			long long i;
			c.len=b+a.len;
			for(i=1;i<=b;i++)
			{
				c.num.push_back(0);
			}
			for(i=1;i<=a.len;i++)
			{
				c.num.push_back(a[i]);
			}
			return c;
		}
		friend bigint operator >>(bigint a,long long b)
		{
			bigint c;
			if(a.len<b) return 0ll;
			for(c.len=1;c.len+b<=a.len;c.len++) c[c.len]=a[c.len+b];
			return c;
		}
		friend bigint operator /(bigint a,bigint b)
		{
			bigint c,d;
			if(a<b) return 0ll;
			d=b<<a.len-b.len+1;
			if(a<d) d>>=1;
			c.len=d.len;
			for(;d.len>=1;d>>=1)
			{
				while(a>=d)
				{
					a-=d;
					c[d.len]++;
				}
			}
			return c;
		}
		friend bigint operator %(bigint a,bigint b)
		{
			bigint d;
			if(a<b) return 0ll;
			d=b<<a.len-b.len+1;
			if(a<d) d>>=1;
			for(;d.len>=1;d>>=1)
			{
				while(a>=d)
				{
					a-=d;
				}
			}
			return a;
		}
		friend void operator <<=(bigint &a,long long b)
		{
			a=a<<b;
		}
		friend void operator >>=(bigint &a,long long b)
		{
			a=a>>b;
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
		friend void operator /=(bigint &a,bigint b)
		{
			a=a/b;
		}
		friend void operator %=(bigint &a,bigint b)
		{
			a=a%b;
		}
		bigint operator ++(void)
		{
			*this+=1;
			return *this;
		}
		bigint operator ++(int)
		{
			bigint c=*this;
			*this+=1;
			return c;
		}
		bigint operator --(void)
		{
			*this-=1;
			return *this;
		}
		bigint operator --(int)
		{
			bigint c=*this;
			*this-=1;
			return c;
		}
		bool to_llong(long long &n)
		{
			bigint p=9223372036854775807;
			if(*this>p) return false;
			else
			{
				n=0;
				for(long long i=len;i>=1;i--)
				{
					n=n*10+num[i];
				}
				return true;
			}
		}
		string to_string()
		{
			string s;
			for(long long i=len;i>=1;i--)
			{
				s.push_back(num[i]+'0');
			}
			return s;
		}
	};
	bigint b_abs(bigint a)
	{
		bigint c=a;
		c.f=1;
		return c;
	}
}
#endif
