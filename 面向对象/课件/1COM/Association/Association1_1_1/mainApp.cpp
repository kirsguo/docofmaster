#include <string.h>
#include <iostream.h>
#include <stdio.h>

#include "Male.h"
#include "Female.h"


int main( )
{
	Male* pm1= new Male("m1");
	Male* pm2 = new Male("m2");
	Female* pf1 = new Female("f1");
	Female* pf2 = new Female("f2");

	pm1->isMarriedTo(pf1);
	pm2->isMarriedTo(pf2); 
	
	cout << pm1->getName( ) <<"---" << pm1->getWife( )->getName( ) << endl;  
	cout << pm2->getName( ) <<"---" << pm2->getWife( )->getName( ) << endl;  
	cout << endl << endl;
	cout << pf1->getName( )  <<"---" << pf1->getHusband( ) ->getName( ) << endl;
	cout << pf2->getName( )  <<"---" << pf2->getHusband( ) ->getName( ) << endl;

	delete pm1;
	delete pm2;
	delete pf1;
	delete pf2;

	char aChar = getchar( );
	return 0;
}
