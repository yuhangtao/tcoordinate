#pragma once

//����������ϵ
class GC
{
public:
	double b;//����γ��
	double l;//���徭��
	double h;//�����

	GC(double ls, double bs,double hs)
	{
		//���캯��������������ֵ
		l = ls;
		b = bs;
		h = hs;
	}

};

//����ֱ��������
class CC
{
public:
	double x;
	double y;
	double z;

	CC(double xs, double ys, double zs)
	{
		//���캯��������������ֵ
		x = xs;
		y = ys;
		z = zs;
	}

};

//����վ��������
class SC
{
public:
	double n;//������
	double e;//������
	double u;//��

	SC(double ns, double es, double us)
	{
		//���캯��������������ֵ
		n = ns;
		e = es;
		u = us;
	}

};