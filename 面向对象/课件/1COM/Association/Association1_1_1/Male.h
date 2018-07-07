#ifndef _Male_h_
#define _Male_h_

class Female;
class Male
{
public:
	Male(char* aName);
	void isMarriedTo(Female* p);
	char* getName( );
	Female* getWife( );
	
private:
	Female *pWife;
	char name[20];
};

#endif