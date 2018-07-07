#include <string.h>
#include <iostream.h>
#include <stdio.h>

#include "Male.h"
#include "Female.h"


int main( )
{
	Male* pm1= Male::newInstance("m1");
	Male* pm2 = Male::newInstance("m2");
	Female* pf1 = new Female("f1");
	Female* pf2 = new Female("f2");

	pm1->isMarriedTo(pf1);
//	pm2->isMarriedTo(pf2); 
	pf2->isMarriedTo(pm2); 
	
	cout << pm1->getName( ) <<"---" << pm1->getWife( )->getName( ) << endl;  
	cout << pm2->getName( ) <<"---" << pm2->getWife( )->getName( ) << endl;  
	cout << endl << endl;
	cout << pf1->getName( )  <<"---" << pf1->getHusband( ) ->getName( ) << endl;
	cout << pf2->getName( )  <<"---" << pf2->getHusband( ) ->getName( ) << endl;

	delete pm1;
	delete pm2;
	delete pf1;
	delete pf2;

	Male* pm3= Male::newInstance("m3");
	Male* pm4 = Male::newInstance("m4");
	Female* pf3 = new Female("f3");
	Female* pf4 = new Female("f4");	
	pm3->isMarriedTo(pf3);
	pf4->isMarriedTo(pm4); 
	cout << pm3->getName( ) <<"---" << pm3->getWife( )->getName( ) << endl;  
	cout << pm4->getName( ) <<"---" << pm4->getWife( )->getName( ) << endl;  
	cout << endl << endl;
	cout << pf3->getName( )  <<"---" << pf3->getHusband( ) ->getName( ) << endl;
	cout << pf4->getName( )  <<"---" << pf4->getHusband( ) ->getName( ) << endl;
	delete pm3;
	delete pm4;
	delete pf3;
	delete pf4;

	char aChar = getchar( );
	return 0;
}
