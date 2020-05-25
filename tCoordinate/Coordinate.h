#pragma once

//定义大地坐标系
class GC
{
public:
	double b;//定义纬度
	double l;//定义经度
	double h;//定义高

	GC(double ls, double bs,double hs)
	{
		//构造函数，给变量赋初值
		l = ls;
		b = bs;
		h = hs;
	}

};

//定义直角坐标类
class CC
{
public:
	double x;
	double y;
	double z;

	CC(double xs, double ys, double zs)
	{
		//构造函数，给变量赋初值
		x = xs;
		y = ys;
		z = zs;
	}

};

//定义站心坐标类
class SC
{
public:
	double n;//北方向
	double e;//东方向
	double u;//高

	SC(double ns, double es, double us)
	{
		//构造函数，给变量赋初值
		n = ns;
		e = es;
		u = us;
	}

};