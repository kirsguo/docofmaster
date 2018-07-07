/*ģ��ʵ���������ľۺϣ�

���������

���ۺϵ��ڲ������������ҵ��ӿ� I3,I4
�ۺ��ߣ��ⲿ�������������ҵ��ӿ� I1,I2
OuterComponent��
	I1 { f1 }
	I2 { f2 }
InnerComponent:
	I3 { f3 }
	I4 { f4 }


Ŀ�꣺
1.�ڲ�������Ա��ⲿ����ۺ�ʹ�ã�
2.�ڲ�������Զ�����ʹ�ã�

�������δ���ǵ���Ҫ�������£�
1.���ü����������߼���
2.COM���ж���ؽӿڡ������ı�׼���壻
3.���ļ���ʽ��
4.��̬���ӿ��ʵ�ַ�ʽ��
5.bool�������͵ĺ������ý�������ֵ�жϣ�
���⣬���Եò�����֣��ܿ��ܴ���Bug.
*/

#include <iostream.h>
#include <stdio.h>

#define IID_I1  1
#define IID_I2  2
#define IID_I3  3
#define IID_I4  4
#define IID_IUnknown 5
#define IID_INonDelegatingUnknown 6  //����Ҫ���ͻ�֪��
#define IID_IClassFactory 7
#define CLSID_IDCompoentInner 8
#define CLSID_IDCompoentOuter 9

class IUnknown
{
public:
	virtual bool QueryInterface(int interfaceID, void** ppv) = 0;
	virtual void AddRef( ) = 0;
	virtual void Release( ) = 0;
};

class I1 : public IUnknown
{
public:
	virtual void f1( ) = 0;
};

class I2 : public IUnknown
{
public:
	virtual void f2( ) = 0;
};

class I3 : public IUnknown
{
public:
	virtual void f3( ) = 0;
};

class I4 : public IUnknown
{
public:
	virtual void f4( ) = 0;
};

class IClassFactory : public IUnknown
{
public:
	virtual bool CreateInstance(IUnknown* pOuter, int interfaceID, void** ppv) = 0;
};

class INonDelegatingUnknown 
{
//�Ա��ۺ������˵����������IUnknown�ӿ�
//����Ҫ���ͻ�֪����ֻ�豻���೧֪��.
public:
	virtual bool NondelegatingQueryInterface(int interfaceID, void** ppv) = 0;
	virtual void NondelegatingAddRef( ) = 0;
	virtual void NondelegatingRelease( ) = 0;
};

//_________________________________________________________________
//���ۺ������ʵ��
class InnerComponet : public I3, public I4, public INonDelegatingUnknown
{
private:
	long m_theCounter;
	IUnknown* m_pUnknownOuter;
public:
	InnerComponet(IUnknown* pUnknownOuter)
	{
		m_theCounter = 1;
		if (pUnknownOuter == 0)
			m_pUnknownOuter = reinterpret_cast<IUnknown*>
					(static_cast<INonDelegatingUnknown*>(this));
		else
			m_pUnknownOuter = pUnknownOuter;
	}

	/* ��Ȼ�������IUnknown�ӿ��еĺ��������Ա��ۺ������˵��
	���������������Ǽٵ�IUnknown�ӿ�ʵ�� */
	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		return m_pUnknownOuter->QueryInterface(interfaceID,ppv);
		//������Ϊ������ת��(����)��ȥ�ˣ�����˵�Ǽٵ�.
		//����ת������㣨�ۺ��ߣ���Ҳ����ת�����Լ�.
	}

	virtual void AddRef( )
	{
		m_pUnknownOuter->AddRef( );
	}
	virtual void Release( )
	{
		m_pUnknownOuter->Release( );
	}
	//����������������Ȼ���ֲ����棬���Ա��ۺ������˵��
	//����������IUnknown�ӿ�������������ʵ��.
	//���Լ���IUnknown�ӿڵ�ʵ��.
	virtual bool NondelegatingQueryInterface(int interfaceID, void** ppv)
	{
		if (interfaceID == IID_IUnknown)
			*ppv = static_cast<INonDelegatingUnknown*>(this);
		else if (interfaceID == IID_I3)
			*ppv = static_cast<I3*>(this);
		else if (interfaceID == IID_I4)
			*ppv = static_cast<I4*>(this);
		else
		{
			*ppv = 0;
			return false;
		}
		return true;
	}

	virtual void NondelegatingAddRef( )
	{
		m_theCounter++;
	}

	virtual void NondelegatingRelease( )
	{
		if (--m_theCounter == 0)
			delete this;
	}
	virtual void f3( )
	{
		cout << "f3 in the inner component is called." << endl;
	}
	virtual void f4( )
	{
		cout << "f4 in the inner component is called." << endl;
	}

};

class InnerComponetFactory : public IClassFactory
{
private:
	long m_theCounter;
public:
	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		if ((interfaceID == IID_IUnknown)
		     ||(interfaceID == IID_IClassFactory))
			*ppv = static_cast<IClassFactory*> (this);
		else
		{
			*ppv = 0;
			return false;
		}
		return true;
	}

	virtual void AddRef( )
	{
		m_theCounter++;
	}

	virtual void Release( ) 
	{
		if (--m_theCounter == 0)
			delete this;
	}
	virtual bool CreateInstance(IUnknown* pOuter, int interfaceID, void** ppv)
	{
		if ((pOuter!=0) && (interfaceID != IID_IUnknown))
			return false;
		InnerComponet* pInner = new InnerComponet(pOuter);
		bool returnValue = pInner->NondelegatingQueryInterface(interfaceID,ppv);
		return returnValue;
	}
};

//������ģ����ڲ������������
bool GetClassObject_InnerComponet(int classID,int interfaceID,void** ppv)
{
	if (classID != CLSID_IDCompoentInner)
		return false;
	InnerComponetFactory* pFactory = new InnerComponetFactory;
	bool returnValue = pFactory->QueryInterface(interfaceID,ppv);
	return returnValue;
}

//_________________________________________________________________

//������ⲿ������ۺ��ߣ���ʵ��
//�ⲿ���Ҳ����������������ڲ����(�ɾۺ����)��
//����û����ʵ�ֳɿɾۺ����.

class OuterComponent : public I1, public I2
{
private:
	I3* m_pI3;
	IUnknown* m_pInner;
	long m_theCounter;
public:
	OuterComponent( )
	{
		m_pI3 = 0;
		m_pInner = 0;
		m_theCounter = 1;
		IClassFactory* pInnerFactory;
		//������δ����������ֵ����ж�
		GetClassObject_InnerComponet(
				CLSID_IDCompoentInner,
				IID_IClassFactory,
				(void**)&pInnerFactory);
		IUnknown* pOuter = static_cast<I1*>(this);
		 pInnerFactory->CreateInstance(
				pOuter,IID_IUnknown,(void**)&m_pInner);
		m_pInner->QueryInterface(IID_I3,(void**)&m_pI3);
	}

	~OuterComponent( )
	{//�������´��룬��������û�������ü���
		if (m_pI3)
			m_pI3->Release( );
		if (m_pInner)
			m_pInner->Release( );
	}

	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		if (interfaceID == IID_IUnknown)
			*ppv = static_cast<I1*> (this);
		else if (interfaceID == IID_I1)
			*ppv = static_cast<I1*> (this);
		else if (interfaceID == IID_I2)
			*ppv = static_cast<I2*> (this);
		else if (interfaceID == IID_I3)
			*ppv = m_pI3;
		else
		{
			*ppv = 0;
			return false;
		}
		//���������ü�������д���������´��룬
		//����Ҫ�ں��ʵط�ƥ��Release��
		//reinterpret_cast<IUnknown*>(*ppv)->AddRef( );
		return true;
	}

	virtual void AddRef( )
	{
		m_theCounter++;
	}

	virtual void Release( )
	{
		if (--m_theCounter==0)
			delete this;
	}
	virtual void f1( )
	{
		cout << "f1 in the outer component is called." << endl;
	}
	virtual void f2( )
	{
		cout << "f2 in the outer component is called." << endl;
	}
};

class OuterComponetFactory : public IClassFactory
{
private:
	long m_theCounter;
public:
	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		if ((interfaceID == IID_IUnknown)
		     ||(interfaceID == IID_IClassFactory))
			*ppv = static_cast<IClassFactory*> (this);
		else
		{
			*ppv = 0;
			return false;
		}
		//reinterpret_cast<IUnknown*>(*ppv)->AddRef( );
		return true;
	}

	virtual void AddRef( )
	{
		m_theCounter++;
	}

	virtual void Release( ) 
	{
		if (--m_theCounter == 0)
			delete this;
	}
	virtual bool CreateInstance(IUnknown* pOuter, int interfaceID, void** ppv)
	{
		if (pOuter!=0) //���ﲻ���Ǳ��ۺ�
			return false;
		OuterComponent* theOuterComponent = new OuterComponent;
		bool returnValue = theOuterComponent->QueryInterface(interfaceID,ppv); 
		/*if (returnValue)
			theOuterComponent->Release( ); 
			*/
		return returnValue;
	}
};

bool GetClassObject_OuterComponet(int classID,int interfaceID,void** ppv)
{
	if (classID != CLSID_IDCompoentOuter)
		return false;
	OuterComponetFactory* pFactory = new OuterComponetFactory;
	bool returnValue = pFactory->QueryInterface(interfaceID,ppv);
	return returnValue;
}

int main( )
{
	cout << "�ⲿ���ģ����ԣ�" << endl;
	IClassFactory* pOuterFactory;
	GetClassObject_OuterComponet(
		CLSID_IDCompoentOuter,
		IID_IClassFactory,
		(void**)&pOuterFactory);
	IUnknown* pOuterComponent;
	pOuterFactory->CreateInstance(
			0,IID_IUnknown,(void**)&pOuterComponent); 
	I1* pI1;
	pOuterComponent->QueryInterface(IID_I1,(void**)&pI1);
	pI1->f1( ); 
	I2* pI2;
	pOuterComponent->QueryInterface(IID_I2,(void**)&pI2);
	pI2->f2( );
	I3* pI3;
	pOuterComponent->QueryInterface(IID_I3,(void**)&pI3);
	pI3->f3( );
	I4* pI4;
	pOuterComponent->QueryInterface(IID_I4,(void**)&pI4);

	bool bValue = pOuterComponent->QueryInterface(IID_I4,(void**)&pI4);
	if (bValue == false)
		cout << "Interface I4 is not supported by the outer component." <<endl;
	
	cout << endl << endl <<endl;
	cout << "�ڲ����������δ���ۺϣ�ģ����ԣ�" << endl;
	IClassFactory* pInnerFactory;
	GetClassObject_InnerComponet(
		CLSID_IDCompoentInner,
		IID_IClassFactory,
		(void**)&pInnerFactory);
	IUnknown* pInnerComponent;
	pInnerFactory->CreateInstance(
		0,IID_IUnknown,(void**)&pInnerComponent);
	I1*  pToI1;
	pInnerComponent->QueryInterface(IID_I1,(void**)&pToI1);
	if (bValue == false)
		cout << "Interface I1 is not supported by the inner component." <<endl;
	I2*  pToI2;
	pInnerComponent->QueryInterface(IID_I2,(void**)&pToI2);
	if (bValue == false)
		cout << "Interface I2 is not supported by the inner component." <<endl;
	I3*  pToI3;
	pInnerComponent->QueryInterface(IID_I3,(void**)&pToI3);
	pToI3->f3( ); 
	I4*  pToI4;
	pInnerComponent->QueryInterface(IID_I4,(void**)&pToI4);
	pToI4->f4( ); 
	cout << endl << endl;

	cout << "���������������" << endl;
	getchar( );
	return 0;
}

