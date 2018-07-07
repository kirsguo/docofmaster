
#ifndef __D__H__
#define __D__H__


#include "B.h"
class D : public B
{
public:
	D(int anInt = 0 ,int anotherInt = 0);
	void f1( );
	void f3( );  //不建议这么做，父类中是protected
	void g( );
	~D( );
protected:
	void h( );
private:
	int m_i;  //刻意与父类中数据同名
};

#endif