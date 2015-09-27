#ifndef Kirito_BigInteger
#define Kirito_BigInteger
#include <string>
namespace Obito
{
	class BigInteger      //大整数类
	{
	private:
		std::string m_op; //操作数
	public:
		std::string getOp()const;//获取操作数
		bool isEmpty()const;     //判断操作数是否为空
		int getOpLength()const;  //获取操作数长度
		void setOp(const std::string &op);//设置操作数
        //构造系列:
		BigInteger();
		BigInteger(const std::string &op);
		BigInteger(const BigInteger &bint);
		BigInteger & operator = (const BigInteger &bint);
		//功能:
		void print()const;      //显示
		BigInteger clone()const;//克隆
		bool operator == (const BigInteger &bint)const;//判断两个操作数是否相等
		bool operator != (const BigInteger &bint)const;
		int compareTo(const BigInteger &bint)const;    //比较大小(-1小 0等 1大)
		bool operator > (const BigInteger &bint)const;
		bool operator >= (const BigInteger &bint)const;
		bool operator < (const BigInteger &bint)const;
		bool operator <= (const BigInteger &bint)const;
		BigInteger abs()const;  //返回绝对值
		BigInteger operator + (const BigInteger &bint)const;//加法
		BigInteger operator - (const BigInteger &bint)const;//减法
		BigInteger operator * (const BigInteger &bint)const;//乘法
		BigInteger median(const BigInteger &bint)const;     //中位数
		BigInteger operator / (const BigInteger &bint)const;//除法
		BigInteger operator % (const BigInteger &bint)const;//取余
		BigInteger sqrt()const;                             //开方
	};
}
#endif