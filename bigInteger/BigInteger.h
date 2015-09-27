#ifndef Kirito_BigInteger
#define Kirito_BigInteger
#include <string>
namespace Obito
{
	class BigInteger      //��������
	{
	private:
		std::string m_op; //������
	public:
		std::string getOp()const;//��ȡ������
		bool isEmpty()const;     //�жϲ������Ƿ�Ϊ��
		int getOpLength()const;  //��ȡ����������
		void setOp(const std::string &op);//���ò�����
        //����ϵ��:
		BigInteger();
		BigInteger(const std::string &op);
		BigInteger(const BigInteger &bint);
		BigInteger & operator = (const BigInteger &bint);
		//����:
		void print()const;      //��ʾ
		BigInteger clone()const;//��¡
		bool operator == (const BigInteger &bint)const;//�ж������������Ƿ����
		bool operator != (const BigInteger &bint)const;
		int compareTo(const BigInteger &bint)const;    //�Ƚϴ�С(-1С 0�� 1��)
		bool operator > (const BigInteger &bint)const;
		bool operator >= (const BigInteger &bint)const;
		bool operator < (const BigInteger &bint)const;
		bool operator <= (const BigInteger &bint)const;
		BigInteger abs()const;  //���ؾ���ֵ
		BigInteger operator + (const BigInteger &bint)const;//�ӷ�
		BigInteger operator - (const BigInteger &bint)const;//����
		BigInteger operator * (const BigInteger &bint)const;//�˷�
		BigInteger median(const BigInteger &bint)const;     //��λ��
		BigInteger operator / (const BigInteger &bint)const;//����
		BigInteger operator % (const BigInteger &bint)const;//ȡ��
		BigInteger sqrt()const;                             //����
	};
}
#endif