#include <iostream>
#include "B.h"

using namespace std;

B::B(int anInt) : m_i(anInt)
{
	cout << "B::B(int)" << endl;
}
void B::f1( )
{	
	cout << "B::f1" << endl;
}
void B::f2( )
{	
	cout << "B::f2" << endl;
}
void B::f3( )
{	
	cout << "B::f3" << endl;
}
void B::f4( )
{	
	cout << "B::f4" << endl;
}

B::~B( )
{
	cout << "B::~B" << endl;
}