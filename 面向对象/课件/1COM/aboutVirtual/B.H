#ifndef __B__H__
#define __B__H__

class B
{
public:
	B(int = 0);
	void f1( );
	void f2( );
	~B( );
protected:
	void f3( );
private:
	void f4( );
	int m_i;
};

#endif









/*
#ifndef __B__H__
#define __B__H__

class B
{
public:
	B(int = 0);
	virtual void f1( );
	virtual void f2( );
	virtual ~B( );
protected:
	virtual void f3( );
private:
	virtual void f4( );
	int m_i;
};

#endif

*/