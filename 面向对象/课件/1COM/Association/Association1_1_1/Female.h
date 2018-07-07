#ifndef _Female_h_
#define _Female_h_

class Male;
class Female
{
public:
	Female(char* aName);
	char* getName( );
	void isMarriedTo(Male* p);
	Male* getHusband( );

private:
	Male* pHusband;
	char name[20];
};
#endif