package Counter;

/**
* Counter/CountHolder.java .
* ��IDL-to-Java ������ (����ֲ), �汾 "3.2"����
* ��count.idl
* 2012��4��10�� ���ڶ� ����11ʱ48��30�� CST
*/

public final class CountHolder implements org.omg.CORBA.portable.Streamable
{
  public Counter.Count value = null;

  public CountHolder ()
  {
  }

  public CountHolder (Counter.Count initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = Counter.CountHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    Counter.CountHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return Counter.CountHelper.type ();
  }

}
