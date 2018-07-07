#include <string.h>
#include <iostream.h>

#include "Male.h"
#include "Female.h"

Male::Male(char* aName)
{
	strcpy(name,aName);
	this->pWife = 0; 
}

void Male::isMarriedTo(Female* p)
{
	Male* pm;
	pm = p->getHusband( ); 
	if ( pm==0)
	{
		pWife = p;
		pWife->isMarriedTo(this);
	}
	else if (pm == this)
	{
		pWife = p;
	}

}

char* Male::getName( )
{
	return name;
}

Female* Male::getWife( )
{
	return pWife;
}