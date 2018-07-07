#include "B.h"
#include "D.h"
#include "DD.h"

void main( )
{
	B* pB = new DD;
	pB->f1( );
	pB->f2( );
//	pB->f3( );
//	pB->f4( );
	delete pB;
}