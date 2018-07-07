// ComponentA.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
class C : public IX, public IY  //����ṹ����һ����ʵ�����нӿ�
{
public:
	C( ) { theCounter = 0; otherData = 0; }
	virtual bool QueryInterface(int interfaceID,void** pValue);
	//����ӿڵı�ʶ��Ϊ����

	virtual void AddRef( ) { theCounter++ ; }
	virtual void Release( ) 
	{
		if (theCounter > 0)
			theCounter--;
		if (theCounter == 0)
			delete this;
	}
	virtual void f1( )
	{ 
		cout << "�ӿ�Ix��f1 ������" << endl;
	}
	virtual void f2( )
	{ 
		cout << "�ӿ�Ix��f2 ������" << endl;
	}
	virtual void g1( )
	{ 
		cout << "�ӿ�Iy��g1 ������" << endl;
	}
	virtual void g2( ) 
	{ 
		cout << "�ӿ�Iy��g2 ������" << endl;
	}

private:
	long theCounter;
	int otherData;
};



bool C::QueryInterface(int interfaceID,void** pValue)
{
	switch (interfaceID)
	{
		case IUnknownID :
		{
			*pValue = static_cast<IX*> (this);
			break;
		}
		case IXID :
		{
			*pValue = static_cast<IX*> (this);
			break;
		}
		case IYID :
		{
			*pValue = static_cast<IY*> (this);
			break;
		}
		default:
		return false;
	}
	this->AddRef( );
	return true;
}


class Factory : public IMyClassFactory //�೧�ӿڣ������ӿ�
{
public:
	Factory( ) { theCounter = 0; }
	virtual void AddRef( ) { theCounter++ ; }
	virtual void Release( ) 
	{
		if (theCounter > 0)
			theCounter--;
		if (theCounter == 0)
			delete this;
	}
	virtual bool QueryInterface(int interfaceID,void** pValue)
	{
		if ((interfaceID == IUnknownID ) || 
			(interfaceID == IClassFactoryID ))
		{
			*pValue = static_cast<IMyClassFactory* > (this) ;
			return true;
		}
		else
			return  false;
	}

	virtual bool CreateInstance(int interfaceID, void** pValue)
	{
		C* pC = new C;
		return (pC->QueryInterface( interfaceID,pValue));
	}
private:
	long theCounter;
};


IMyClassFactory* pTheFactory;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
 	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		pTheFactory = new Factory;
		char name[100];
		::GetModuleFileName(HINSTANCE(hModule), name, 100);
		cout << "�������λ���ǣ�" << name << endl ;	
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
//		delete pTheFactory; //�û�ͨ��Release�ͷţ�����Ҫ.
	}
	return TRUE;
}




extern "C" __declspec(dllexport) bool getComp(int CompID,int InterfaceID,void** theRet )
{
	C* pC = new C;
	return pC->QueryInterface(IUnknownID,&theRet);
	
}





extern "C" __declspec(dllexport) bool GetClassObject(int ComponetID,int ClassFactoryIID,void** pValue)
{
	if (ComponetID != CompAID )
		return false;
	if (ClassFactoryIID != IClassFactoryID )
		return false;
//	pTheFactory = new Factory;
	return pTheFactory->QueryInterface(ClassFactoryIID,pValue);
}
//extern "C" __declspec(dllexport) 

















