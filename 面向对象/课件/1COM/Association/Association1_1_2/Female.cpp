#include <string.h>
#include <iostream.h>

#include "Female.h"
#include "Male.h"

Female::Female(char* aName)
{
	strcpy(name,aName);
}

char* Female::getName( )
{
	return name;
}
	
void Female::isMarriedTo(Male* p)
{
	p->isMarriedTo(this); 
}

Male* Female::getHusband( )
{
	int len = Male::getNumOfObjs( );
	Male** theMen = Male::getAllObjs( );
	
	if (len < 0)
		return 0;
	int i = 0;
	while (i <= len)
	{
		if (theMen[i]->getWife( ) == this)
			return theMen[i];
		else
			i++;
	}
	return 0;	
}