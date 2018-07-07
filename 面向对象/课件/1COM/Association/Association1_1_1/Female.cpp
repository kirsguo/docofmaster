#include <string.h>
#include <iostream.h>

#include "Female.h"
#include "Male.h"

Female::Female(char* aName)
{
	strcpy(name,aName);
	this->pHusband = 0;
}

char* Female::getName( )
{
	return name;
}
	
void Female::isMarriedTo(Male* p)
{
	Female* pf=p->getWife( ); 
	if (pf==0)
	{
		this->pHusband = p;
		pHusband->isMarriedTo(this);
	}
	else if (pf == this)
	{
		this->pHusband = p;
	}
}

Male* Female::getHusband( )
{
	return pHusband;		
}