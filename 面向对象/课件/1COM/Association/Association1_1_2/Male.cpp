#include <string.h>
#include <iostream.h>

#include "Male.h"
#include "Female.h"

Male* Male::objs[200];
int   Male::pos =-1;

Male* Male::newInstance(char* aName)
{
	Male* theNewObj = new Male(aName);
	objs[++pos] = theNewObj;
	return theNewObj;
}

Male::~Male( )
{
	int index = 0;
	while (objs[index] != this)
		index++;
	for (int i = index; i<pos;i++)
		objs[i] = objs[i+1];
	pos--;
}

int Male::getNumOfObjs( )
{
	return pos;
}

Male** Male::getAllObjs( )
{
	return objs;
}

Male::Male(char* aName)
{
	strcpy(name,aName);
	this->pWife = 0; 
}

Male::Male(const Male&)
{
}

void Male::isMarriedTo(Female* p)
{
	this->pWife = p;
}

char* Male::getName( )
{
	return name;
}

Female* Male::getWife( )
{
	return pWife;
}