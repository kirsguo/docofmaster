#ifndef _Male_h_
#define _Male_h_

class Female;
class Male
{
public:
	static Male* newInstance(char* aName);
	static int getNumOfObjs( );
	static Male** getAllObjs( );

	void isMarriedTo(Female* p);
	char* getName( );
	Female* getWife( );
	~Male( );
protected:
	Male(char* aName);
	Male(const Male&);
private:
	Female *pWife;
	char name[20];

	static Male*  objs[200];
	static int	   pos;	
};

#endif