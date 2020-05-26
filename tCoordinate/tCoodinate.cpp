//GNSS�ڶ�����ҵ������ת��
/*���������������ֱ���
1.��ֱ������ת��Ϊ������� (�������ΪCoordinate.h�е�GC��,����ΪCC��)
2.�ɴ������ת��Ϊֱ������ (�������ΪCoordinate�е�CC��,����ΪGC��)
3.��ֱ������ת��Ϊվ�ĵ�ƽ���� (�������ΪCoordinate�е�SC��,����ΪCC��)
*/
#include <iostream>
#include"Coordinate.h"
#include"math.h"


using namespace std;

//��ֱ������ת��Ϊ������� (�������ΪCoordinate.h�е�GC��,����ΪCC��)
GC cc2gc(CC a,double semiMajorAxis,double Flattening) 
{
	//���徭�ȣ�γ�ȣ��߱���
	double b, l, h;

	//����X,Y,Z
	double x, y, z;
	x = a.x;
	y = a.y;
	z = a.z;

	//����̰���d,��һƫ����e2
	double e2,d;
	d = (1 - Flattening) * semiMajorAxis;
	e2 = 1 - pow(d / semiMajorAxis, 2);

	//����L,ע��ʹ��atan2�����ֲ�ͬ���޵�����
	l = atan2(y, x);

	//����B��î��Ȧ�뾶N,����b��ʼΪ0,����b2ȥ���Ա�
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

	//����h	
	h = pow(x * x + y * y, 0.5) / cos(b) - N;

	//����������c
	GC c(l, b, h);
	return c;
}

//�ɴ������ת��Ϊֱ������ (�������ΪCoordinate�е�CC��,����ΪGC��)
CC gc2cc(GC a, double semiMajorAxis, double Flattening)
{
	//���徭�ȣ�γ�ȣ��߱���
	double b, l, h;
	b = a.b;
	l = a.l;
	h = a.h;

	//����X,Y,Z
	double x, y, z;

	//����î��Ȧ�뾶N�͵�һƫ����e2
	double N, e2;	
	double d;
	d = (1 - Flattening) * semiMajorAxis;
	e2 = 1 - pow(d / semiMajorAxis, 2);
	N = semiMajorAxis / pow(1 - e2 * pow(sin(b), 2), 0.5);


	//���㲢��ֵx,y,z
	x = (N + h) * cos(b) * cos(l);
	y = (N + h) * cos(b) * sin(l);
	z = (N * (1 - e2) + h) * sin(b);


	//����ֱ������c
	CC c(x, y, z);
	return c;
}

//��ֱ������ת��Ϊվ�ĵ�ƽ���� (�������ΪCoordinate�е�SC��,����ΪCC��)
SC cc2sc(CC a,CC a2, double semiMajorAxis, double Flattening)
{
	//����A�㾭�ȣ�γ�ȣ��߱���
	double b, l, h;

	//����a���xyz��b���xyz��
	double x, y, z;
	double x2, y2, z2;
	x = a.x;
	y = a.y;
	z = a.z;
	x2 = a2.x;
	y2 = a2.y;
	z2 = a2.z;

	//�õ�a���b��l��h
	GC k = cc2gc(a, semiMajorAxis, Flattening);
	b = k.b;
	l = k.l;
	h = k.h;
	
	//���ab����������
	double xab, yab, zab;
	xab = x2 - x;
	yab = y2 - y;
	zab = z2 - z;

	//����վ������n,e,u������ֵ
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

	//��֤
	CC a(-2686431.025393, 4292457.822543, 3864951.768393);
	GC b = cc2gc(a, semiMajorAxis, Flattening);
	CC c = gc2cc(b, semiMajorAxis, Flattening);
	cout << c.x << endl;
	cout << c.y << endl;
	cout << c.z << endl;

	return 0;
}