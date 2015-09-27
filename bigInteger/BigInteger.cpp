#include "stdafx.h"

#include "BigInteger.h"
#include <iostream>
#include <exception>

namespace Obito
{
	std::string BigInteger::getOp()const
	{
		return m_op;
	}
	bool BigInteger::isEmpty()const
	{
		if(getOp().length()==0)
			return true;
		else
			return false;
	}
	int BigInteger::getOpLength()const
	{
		return getOp().length();
	}
	void BigInteger::setOp(const std::string &op)
	{
		if(op.length()>0)
			m_op=op;
		else
			m_op="0";
	}
	BigInteger::BigInteger()
	{
		setOp("0");
	}
	BigInteger::BigInteger(const std::string &op)
	{
		setOp(op);
	}
	BigInteger::BigInteger(const BigInteger &bint)
	{
		setOp(bint.getOp());
	}
	BigInteger & BigInteger::operator = (const BigInteger &bint)
	{
		setOp(bint.getOp());
		return *this;
	}
	void BigInteger::print()const
	{
		std::cout<<this->getOp()<<std::endl;
	}
	BigInteger BigInteger::clone()const
	{
		return BigInteger(this->getOp());
	}
	bool BigInteger::operator == (const BigInteger &bint)const
	{
		int n1=this->getOpLength();
		int n2=bint.getOpLength();
		if(n1!=n2)
			return false;
		for(int i=0;i<n1;i++)
		{
			if(this->getOp().at(i)!=bint.getOp().at(i))
				return false;
		}
		return true;
	}
	bool BigInteger::operator != (const BigInteger &bint)const
	{
		if(*this==bint)
			return false;
		else
			return true;
	}
	int BigInteger::compareTo(const BigInteger &bint)const
	{// -1: *this<bint  0: *this==bint  1: *this>bint
		if(*this==bint)
			return 0;
		int n1=this->getOpLength(),n2=bint.getOpLength();
		//先判断两数符号:
		int k1=this->getOp().at(0)=='-'?-1:1;
		int k2=bint.getOp().at(0)=='-'?-1:1;
		if(k1>k2)
			return 1;
		if(k1<k2)
			return -1;
		//两数同号(k1=k2):
		if(n1>n2)
			return k1;
		if(n1<n2)
			return -k1;
		char c1,c2;
		for(int i=0;i<n1;i++)
		{
			c1=this->getOp().at(i);
			c2=bint.getOp().at(i);
			if(c1>c2)
				return k1;
			if(c1<c2)
				return -k1;
		}
		return 0;
	}
	bool BigInteger::operator > (const BigInteger &bint)const
	{
		int k=this->compareTo(bint);
		if(k==1)
			return true;
		else
			return false;
	}
	bool BigInteger::operator >= (const BigInteger &bint)const
	{
		int k=this->compareTo(bint);
		if(k==-1)
			return false;
		else
			return true;
	}
	bool BigInteger::operator < (const BigInteger &bint)const
	{
		int k=this->compareTo(bint);
		if(k==-1)
			return true;
		else
			return false;
	}
	bool BigInteger::operator <= (const BigInteger &bint)const
	{
		int k=this->compareTo(bint);
		if(k==1)
			return false;
		else
			return true;
	}
	BigInteger BigInteger::abs()const
	{//返回操作数的绝对值(新对象):
		char k=this->getOp().at(0);
		if(k!='-')//原数为正
			return this->clone();
		else
			return BigInteger(this->getOp().substr(1,this->getOpLength()));
	}
	BigInteger BigInteger::operator + (const BigInteger &bint)const
	{
		int k1=this->getOp().at(0)=='-'?-1:1;
		int k2=bint.getOp().at(0)=='-'?-1:1;
		if(k1==1&&k2==1)//都为正数
		{
			int n1=this->getOpLength(),n2=bint.getOpLength();
			int N=(n1>n2?n1:n2)+1;//结果的最多有效位数
			char * op1=new char[N+1];
			char * op2=new char[N+1];
			char * op=new char[N+1];
			for(int i=0;i<n1;i++)
				op1[i]=this->getOp().at(n1-1-i)-'0';
			for(int i=n1;i<N;i++)
				op1[i]=0;
			for(int i=0;i<n2;i++)
				op2[i]=bint.getOp().at(n2-1-i)-'0';
			for(int i=n2;i<N;i++)
				op2[i]=0;
			op1[N]=op2[N]=op[N]='\0';
			for(int i=0;i<N;i++)
				op[i]=op1[i]+op2[i];
			for(int i=0;i<N-1;i++)
			{
				if(op[i]>9)
				{
					op[i+1]=op[i+1]+op[i]/10;
					op[i]=op[i]%10;
				}
			}
			int k=N;
			while(k>0&&op[k-1]==0) k--;//求出实际有效位数
			char change;
			for(int i=0;i<k/2;i++)
			{
				change=op[i];
				op[i]=op[k-1-i];
				op[k-1-i]=change;
			}
			for(int i=0;i<k;i++)
				op[i]=op[i]+'0';
			op[k]='\0';
			int m=std::strlen(op);
			char * result=new char[m+1];
			strcpy_s(result,m+1,op);
			delete []op1; delete []op2; delete []op;
			BigInteger add=BigInteger(std::string(result));
			delete []result;
			return add;
		}
		BigInteger op1=this->abs();
		BigInteger op2=bint.abs();
		if(k1==-1&&k2==-1)
		{//两数同负
			BigInteger result=op1+op2;
			result.setOp("-"+result.getOp());
			return result;
		}
		//两数异号:
		if(op1==op2) 
			return BigInteger(std::string("0"));
		int compare=op1.compareTo(op2);
		int k; //标记最终结果的正负
		if(k1*compare==1) k=1;
		else k=-1;
		BigInteger max,min;
		if(compare==1){ max=op1; min=op2; }
		else{ max=op2; min=op1; }
		BigInteger result=max-min;
		if(k==-1)
			result.setOp("-"+result.getOp());
		return result;
	}
	BigInteger BigInteger::operator - (const BigInteger &bint)const
	{
		if(*this==bint)
			return BigInteger(std::string("0"));
		int k1=this->getOp().at(0)=='-'?-1:1;
		int k2=bint.getOp().at(0)=='-'?-1:1;
		if(k1==1&&k2==1)
		{//两数同正:
			int k;//标记结果符号
			BigInteger max,min; //max记录被减数 min记录减数
			if(this->compareTo(bint)==1){ k=1; max=*this; min=bint; }
			else{ k=-1; max=bint; min=*this; }
			int n1=max.getOpLength(),n2=min.getOpLength();
			char * op1=new char[n1+1];//结果最多n1位,加上一位截止符'\0'
			char * op2=new char[n1+1];
			for(int i=0;i<n1;i++)
				op1[i]=max.getOp().at(n1-1-i)-'0';
			for(int i=0;i<n2;i++)
				op2[i]=min.getOp().at(n2-1-i)-'0';
			for(int i=n2;i<n1;i++)
				op2[i]=0;
			op1[n1]=op2[n1]='\0';
			char * temp=new char[n1+1];
			temp[n1]='\0';
			for(int i=0;i<n1;i++)
			{
				if(op1[i]>=op2[i])
					temp[i]=op1[i]-op2[i];
				else//需要向高位借位
				{
					temp[i]=10+op1[i]-op2[i];
					if(op1[i+1]>=1) op1[i+1]--;
					else//借一位还不够>_<
					{
						for(int j=i+1;j<n1;j++)
						{
							if(op1[j]==0) op1[j]=9;
							else{ op1[j]--; break; }
						}
					}
				}
			}
			int N=n1;
			while(N>0&&temp[N-1]==0) N--;
			temp[N]='\0';
			char * result=new char[N+1];
			for(int i=0;i<N;i++)
				result[i]=temp[N-1-i]+'0';
			result[N]='\0';
			std::string str=result;
			if(k==-1) str="-"+str;
			delete []op1; delete []op2;
			delete []temp; delete []result;
			return BigInteger(str);
		}
		BigInteger op1=this->abs();
		BigInteger op2=bint.abs();
		if(k1==-1&&k2==-1)
			return op2-op1;
		BigInteger result=op1+op2;
		if(k1==-1)
			result.setOp("-"+result.getOp());
		return result;
	}
	BigInteger BigInteger::operator * (const BigInteger &bint)const
	{
		int k1=this->getOp().at(0)=='-'?-1:1;
		int k2=bint.getOp().at(0)=='-'?-1:1;
		int k=(k1*k2==1?1:-1);//最终结果符号
		BigInteger temp1=this->abs();
		BigInteger temp2=bint.abs();
		int n1=temp1.getOpLength(),n2=temp2.getOpLength();
		int N=n1+n2;//最多N位
		char * op1=new char[N+1];
		char * op2=new char[N+1];
		for(int i=0;i<n1;i++) op1[i]=temp1.getOp().at(n1-1-i)-'0';
		for(int i=n1;i<N;i++) op1[i]=0;
		for(int i=0;i<n2;i++) op2[i]=temp2.getOp().at(n2-1-i)-'0';
		for(int i=n2;i<N;i++) op2[i]=0;
		op1[N]=op2[N]='\0';
		char * tempresult=new char[N+1];
		for(int i=0;i<N;i++) tempresult[i]=0;
		tempresult[N]='\0';
		//然后把每位相乘逐行累加到tempresult[]中，每读一行进行一次进位，以确保不会超值
		for(int i=0;i<n1;i++)
		{
			for(int j=0;j<n2;j++)
				tempresult[i+j]=tempresult[i+j]+op1[i]*op2[j];
			for(int p=i;p<N-1;p++)
			{
				if(tempresult[p]>9)
				{
					tempresult[p+1]=tempresult[p+1]+tempresult[p]/10;
					tempresult[p]=tempresult[p]%10;
				}
			}
		}
		int t=N;
		while(t>0&&tempresult[t-1]==0) t--;
		char * result=new char[t+1];
		for(int i=0;i<t;i++) result[i]=tempresult[t-1-i]+'0';
		result[t]='\0';
		std::string str=result;
		if(k==-1)
			str="-"+str;
		BigInteger multiply=BigInteger(str);
		delete []op1; delete op2;
		delete []tempresult; delete []result;
		return multiply;
	}
	BigInteger BigInteger::median(const BigInteger &bint)const
	{//返回左右操作数的中位数
		BigInteger total=*this+bint;
		int k=(total.getOp().at(0)=='-'?-1:1);//记录中位数的符号
		if(k==-1)
			total=total.abs();
		int N=total.getOpLength();
		char * temp1=new char[N+1];
		char * temp2=new char[N+1];
		for(int i=0;i<N;i++) 
			temp1[i]=total.getOp().at(i)-'0';
		temp1[N]=temp2[N]='\0';
		for(int i=0;i<N-1;i++)
		{
			temp2[i]=temp1[i]/2;
			temp1[i]=temp1[i]%2;
			temp1[i+1]=temp1[i+1]+10*temp1[i];
		}
		temp2[N-1]=temp1[N-1]/2;
		int t=N;
		while(temp2[N-t]==0){ t--; }
		char * result=new char[t+1];
		for(int i=0;i<t;i++)
			result[i]=temp2[N-t+i]+'0';
		result[t]='\0';
		std::string str=result;
		if(k==-1)
			str="-"+str;
		BigInteger Result(str);
		delete []temp1; delete []temp2; delete []result;
		return Result;
	}
	BigInteger BigInteger::operator / (const BigInteger &bint)const
	{
		if(bint.getOp().at(0)=='0'||
			(bint.getOp().at(0)=='-'&&bint.getOp().at(1)=='0'))
			throw std::exception();//除数为零
		BigInteger op1=this->abs();
		BigInteger op2=bint.abs();
		if(op1.compareTo(op2)==-1)//被除数绝对值<除数绝对值,结果直接为零
			return BigInteger(std::string("0"));
		int k1=this->getOp().at(0)=='-'?-1:1;
		int k2=bint.getOp().at(0)=='-'?-1:1;
		int k=(k1*k2==1?1:-1);//最终结果符号
		int n1=op1.getOpLength(),n2=op2.getOpLength();
		int N=n1-n2+2;
		char * temp=new char[N+1];
		temp[0]='1';
		for(int i=1;i<N;i++)
			temp[i]='0';
		temp[N]='\0';
		BigInteger max=BigInteger(std::string(temp));
		BigInteger min=BigInteger(std::string("0"));
		BigInteger center=max.median(min);
		BigInteger tempbint;
		bool w=true;
		while(w)
		{
			w=false;
			tempbint=center*op2;
			if(tempbint.compareTo(op1)==1)
			{//当前商过大:
				w=true;
				max=center;
			}
			else if(tempbint.compareTo(op1-op2)!=1)
			{//当前商过小:
				w=true;
				min=center;
			}
			center=max.median(min);
		}
		if(k==-1)
			center.setOp("-"+center.getOp());
		delete []temp;
		return center;
	}
	BigInteger BigInteger::operator % (const BigInteger &bint)const
	{
		if(bint.getOp().at(0)=='0'||
			(bint.getOp().at(0)=='-'&&bint.getOp().at(1)=='0'))
			throw std::exception();//除数为零
		BigInteger shang=*this/bint;
		BigInteger result=*this-bint*shang;
		return result;
	}
	BigInteger BigInteger::sqrt()const
	{
		BigInteger min=BigInteger(std::string("0"));
		if(this->getOp().at(0)=='0'||
			(this->getOp().at(0)=='-'&&this->getOp().at(1)=='0'))
			return min;
		if(this->compareTo(min)==-1)
			throw std::exception();
		BigInteger max=this->clone();
		BigInteger center=max.median(min);
		BigInteger overdecide=BigInteger(std::string("1"));
		BigInteger temp;
		int k=0;
		while((max-min).compareTo(overdecide)==1)
		{
			if(min*min==*this)
				return min;
			if(max*max==*this)
				return max;
			temp=center*center;
			k=temp.compareTo(*this);
			if(k==0)
				return center;
			else if(k==-1)
				min=center;
			else
				max=center;
			center=max.median(min);
		}
		return min;
	}
//end
}