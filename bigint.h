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
			len=0;
			f=1;
		}
		friend ostream& operator <<(ostream& out,const BigInt& val)
		{
			if(val.f==-1) out<<'-';
			for(int i=val.len;i>=1;i--)
			{
				out<<val.num[i];
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
		bool operator >(const BigInt &b)
		{
			if(len>b.len) return true;
			if(len<b.len) return false;	
			for(int i=len;i>=1;i--)
			{
				if(num[i]>b.num[i]) return true;
				if(num[i]<b.num[i]) return false;
			}
			return false;
		}
		bool operator <(const BigInt &b)
		{
			if(len<b.len) return true;
			if(len>b.len) return false;	
			for(int i=len;i>=1;i--)
			{
				if(num[i]<b.num[i]) return true;
				if(num[i]>b.num[i]) return false;
			}
			return false;
		}
		void operator =(const BigInt &b)
		{
			len=b.len;
			f=b.f;
			*this=b;
		}
		BigInt operator +(BigInt b)
		{
			BigInt c;
			if(b.f==-1&&f==1)
			{
				b.f=1;
				return *this-b;
			}
			if(f==-1&&b.f==1)
			{
				c=*this;
				c.f=1;
				return b-c;
			}   
			if(f==1) c.f=1;
			else c.f=-1;
			c.len=max(len,b.len);
			int x=0;
			for(int i=1;i<=c.len;i++)
			{
				c.num[i]=num[i]+b.num[i]+x;
				x=c.num[i]/10;
				c.num[i]%=10;
			}
			if(x!=0) c.num[++c.len]=x;
			return c;
		}
		void operator =(const string &s)
		{
			if(s[0]=='-')
			{
				f=-1;
				len=s.size()-1;
			} 
			else
			{
				f=1;
				len=s.size();
			} 
			num.clear();
			num.push_back(0);
			for(int i=1;i<=len;i++)
			{
				num.push_back(s[s.size()-i]-'0');
			}
		}
		BigInt operator -(BigInt b)
		{
			BigInt c;
			if(f==1&&b.f==-1)
			{
				b.f=1;
				return *this+b;
			}
			if(f==-1&&b.f==1)
			{
				c=*this;
				b.f=-1;
				return c+b;
			}
			if(*this<b)
			{
				c.f=-1;
				c.len=b.len;
				for(int i=1;i<=b.len;i--)
				{
					c.num[i]=b.num[i]-num[i];
					if(c.num[i]<0)
					{
						b.num[i+1]--;
						c.num[i]+=10;
					} 
				}
			}
			else
			{
				c.f=1;
				c.len=len;
				for(int i=1;i<=len;i--)
				{
					c.num[i]=num[i]-b.num[i];
					if(c.num[i]<0)
					{
						num[i+1]--;
						c.num[i]+=10;
					} 
				}
			}
			return c;
		}
		BigInt operator *(const BigInt &b)
		{
			BigInt c;
			if(f==-1&&b.f==-1) c.f=1;
			if(f==1&&b.f==1) c.f=1;
			if(f==1&&b.f==-1) c.f=-1;
			if(f==-1&&b.f==1) c.f=-1;
			c.len=len+b.len-1;
			int x=0,i,j;
			for(i=1;i<=len;i++)
			{
				for(j=1;j<=b.len;j++)
				{
					c.num[i+j-1]+=num[i]*b.num[j]+x;
					x=c.num[i+j-1]/10;
					c.num[i+j-1]%=10;
				}
				while(x)
				{
					if(i+b.len<=c.len) c.num[i+b.len]=x%10;
					else c.num[++c.len]=x%10;
					x/=10;
				}
			}
			return c;
 		}
	};
	#define bigint BigInt
}
#endif
