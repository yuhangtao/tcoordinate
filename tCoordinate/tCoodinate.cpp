//GNSS第二次作业：坐标转换
/*包含三个函数：分别是
1.由直角坐标转换为大地坐标 (输出类型为Coordinate.h中的GC类,输入为CC类)
2.由大地坐标转换为直角坐标 (输出类型为Coordinate中的CC类,输入为GC类)
3.由直角坐标转换为站心地平坐标 (输出类型为Coordinate中的SC类,输入为CC类)
*/
#include <iostream>
#include"Coordinate.h"
#include"math.h"


using namespace std;

//由直角坐标转换为大地坐标 (输出类型为Coordinate.h中的GC类,输入为CC类)
GC cc2gc(CC a,double semiMajorAxis,double Flattening) 
{
	//定义经度，纬度，高变量
	double b, l, h;

	//定义X,Y,Z
	double x, y, z;
	x = a.x;
	y = a.y;
	z = a.z;

	//计算短半轴d,第一偏心率e2
	double e2,d;
	d = (1 - Flattening) * semiMajorAxis;
	e2 = 1 - pow(d / semiMajorAxis, 2);

	//计算L,注意使用atan2，区分不同象限的区别
	l = atan2(y, x);

	//计算B和卯酉圈半径N,假设b初始为0,定义b2去做对比
	double b2;
	double N;
	b = 0;
	N = semiMajorAxis / pow(1 - e2 * sin(b) * sin(b), 0.5);
	b2 = atan((z + N * e2 * sin(b)) / pow(x * x + y * y, 0.5));
	while (fabs(b - b2) >=0.0000000000000000001)
	{
		b = b2;
		N = semiMajorAxis / pow(1 - e2 * sin(b) * sin(b), 0.5);
		b2 = atan((z + N * e2 * sin(b)) / pow(x * x + y * y, 0.5));
	}

	//计算h	
	h = pow(x * x + y * y, 0.5) / cos(b) - N;

	//定义大地坐标c
	GC c(l, b, h);
	return c;
}

//由大地坐标转换为直角坐标 (输出类型为Coordinate中的CC类,输入为GC类)
CC gc2cc(GC a, double semiMajorAxis, double Flattening)
{
	//定义经度，纬度，高变量
	double b, l, h;
	b = a.b;
	l = a.l;
	h = a.h;

	//定义X,Y,Z
	double x, y, z;

	//计算卯酉圈半径N和第一偏心率e2
	double N, e2;	
	double d;
	d = (1 - Flattening) * semiMajorAxis;
	e2 = 1 - pow(d / semiMajorAxis, 2);
	N = semiMajorAxis / pow(1 - e2 * pow(sin(b), 2), 0.5);


	//计算并赋值x,y,z
	x = (N + h) * cos(b) * cos(l);
	y = (N + h) * cos(b) * sin(l);
	z = (N * (1 - e2) + h) * sin(b);


	//定义直角坐标c
	CC c(x, y, z);
	return c;
}

//由直角坐标转换为站心地平坐标 (输出类型为Coordinate中的SC类,输入为CC类)
SC cc2sc(CC a,CC a2, double semiMajorAxis, double Flattening)
{
	//定义A点经度，纬度，高变量
	double b, l, h;

	//定义a点的xyz和b点的xyz；
	double x, y, z;
	double x2, y2, z2;
	x = a.x;
	y = a.y;
	z = a.z;
	x2 = a2.x;
	y2 = a2.y;
	z2 = a2.z;

	//得到a点的b，l，h
	GC k = cc2gc(a, semiMajorAxis, Flattening);
	b = k.b;
	l = k.l;
	h = k.h;
	
	//算出ab两点的坐标差
	double xab, yab, zab;
	xab = x2 - x;
	yab = y2 - y;
	zab = z2 - z;

	//定义站心坐标n,e,u，并赋值
	double n, e, u;
	n = -sin(b) * cos(l) * xab - sin(b) * sin(l) * yab + cos(b) * zab;
	e = -sin(l) * xab + cos(l) * yab;
	u = cos(b) * cos(l) * xab + cos(b) * sin(l) * yab + sin(b) * zab;

	SC c(n, e, u);
	return c;

}

int main() 
{
	double semiMajorAxis, Flattening;
	semiMajorAxis = 6378137.0;
	Flattening = 1 / 298.257223563;

	//验证
	CC a(-2686431.025393, 4292457.822543, 3864951.768393);
	GC b = cc2gc(a, semiMajorAxis, Flattening);
	CC c = gc2cc(b, semiMajorAxis, Flattening);
	cout << c.x << endl;
	cout << c.y << endl;
	cout << c.z << endl;

	return 0;
}