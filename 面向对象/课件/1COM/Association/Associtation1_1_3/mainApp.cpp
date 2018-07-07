#include <string.h>
#include <iostream.h>
#include <stdio.h>

class Male;
class Female;
class Row
{
   public:
	Row( )
	{
	}
	Row(Male* aMale,Female* aFemale)
	{
		pM = aMale;
		pF = aFemale;
	}
	void setValue(Male*,Female*);
	Male* getMale( )
	{
		return pM;
	}
	Female* getFemale()
	{
		return pF;
	}
	~Row( );
   private:
	Male* pM;
	Female* pF;
};

class Table
{
   public:
	static Table* newInstance( )
	{
		if (theTable==0)
			theTable = new Table;
		return theTable;
	}

//	void addARow(Row*);
	void addARow(Male* pm,Female* pf)
	{
	   //.....
	   rows[no++] = new Row(pm,pf);	   	   	  
	}
	void show( );
	Male* getMaleBy(Female* pf)
	{
	   int pos;
	   for (pos = 0; pos < no; pos++)
    	    if (rows[pos]->getFemale( ) == pf)
				return (rows[pos]->getMale( ));
   	   return 0;		
	}
	Female* getFemaleBy(Male* pM)
	{
		int pos;
		for (pos = 0;pos < no; pos++)
			if (rows[pos]->getMale( ) == pM)
				return (rows[pos]->getFemale( ));
		return 0;
	}
		
//	bool isExist(Male*);
	~Table( )
	{ }
   private:
  	Table( )
	{
		no = 0;
	}
	Row* rows[200];
	int  no;
	static Table* theTable;
};
Table* Table::theTable = 0;

class Male
{
public:
	Male(char* aName)
	{
		pT = Table::newInstance( );
		strcpy(name,aName);
	}
	void isMarriedTo(Female* p)
	{
	  pT->addARow(this,p);	    
	}
	char* getName( )
	{
		return name;
	}
	Female* getWife( )
	{
	  return pT->getFemaleBy(this);
	}
private:
	Table* pT;
	char name[20];
};

class Female
{
public:
	Female(char* aName)
	{
		pT = Table::newInstance( );
		strcpy(name,aName);
	}
	char* getName( )
	{
		return name;
	}	
	void isMarriedTo(Male* p)
	{
	  //--- if (pT->isExist(this)==false)
	  //Row* pr = new Row(p,this);	
	  //pT->add(pr);	
	  pT->addARow(p,this);
	}
	Male* getHusband( )
	{
	  return pT->getMaleBy(this);		
	}
private:
	Table* pT;
	char name[20];
};
void Table::show( )
{
	for (int pos=0; pos <no; pos++)
		cout << rows[pos]->getMale( )->getName( ) << "----" << rows[pos]->getFemale( )->getName( ) << endl;
}
int main( )
{
	Table* t=Table::newInstance( ); // = new Table;
	Male* pm1= new Male("m1");
	Male* pm2 = new Male("m2");
	Female* pf1 = new Female("f1");
	Female* pf2 = new Female("f2");

	pm1->isMarriedTo(pf1);
	pm2->isMarriedTo(pf2); 

	t->show( ); 
	char aChar = getchar( );
	return 0;
}