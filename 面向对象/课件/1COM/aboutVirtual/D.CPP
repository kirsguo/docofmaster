#include <iostream>
#include "D.h"

using namespace std;

D::D(int anInt,int anotherInt) : B(anInt),m_i(anotherInt)
{
	cout << "D::D(int,int)" << endl;
}
void D::f1( )
{
	cout << "D::f1" << endl;
}

void D::f3( )
{
	cout << "D::f4" << endl;
}

D::~D( )
{
	cout << "D::~D" << endl;
}