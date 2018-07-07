#include <iostream.h>
#include <process.h>

class Screen
{
public:
	Screen( );
	void moveToPoint(int anInt,int anotherInt);
	void writeChar(char aChar);
	void show( ) const;
private:
	char screenBuffer[20][24];
	int  currentX;
	int  currentY;
};

Screen::Screen( ): currentX(0),currentY(0)
{
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 24; j++)
			screenBuffer[i][j] = ' ';
}

void Screen::moveToPoint(int anInt,int anotherInt)
{
	if ((anInt >= 0)&&(anInt < 20))
		currentX = anInt;
	if ((anotherInt >= 0) && (anotherInt < 24))
		currentY = anotherInt;
	screenBuffer[currentX][currentY] = '_';
}

void Screen::writeChar(char aChar)
{
	screenBuffer[currentX][currentY] = aChar;
}

void Screen::show( ) const
{
	system("cls");
	for (int i=0; i<20; i++)
	{
		for (int j=0; j <24; j++)
			cout << screenBuffer[i][j];
		cout << endl;
	}
	system("pause");
}



class CommandBase //: public Command
{
public:
	CommandBase(Screen* aScreen)
	{
		pScreen = aScreen;
	}
protected:
	Screen* pScreen;
	void saveStateOfScreen( );
	void undo( );
	static Screen statesOfScreen[4];
	static int pos;
};

Screen CommandBase::statesOfScreen[4];
int CommandBase::pos = -1;

void CommandBase::saveStateOfScreen( )
{
	Screen aNewBackupScreen(*pScreen);
	if (pos < 4-1)
		statesOfScreen[++pos] = aNewBackupScreen;
	else
	{
		for (int i=0; i<3; i++)
			statesOfScreen[i] = statesOfScreen[i+1];
		statesOfScreen[3] = aNewBackupScreen;
	}
}
void CommandBase::undo( )
{
	if (pos >= 0)
	{
		*pScreen = statesOfScreen[pos];
		pos--;
	}
	pScreen->show( ); 
}


class MoveToCommand : public CommandBase
{
public:
	MoveToCommand(Screen* pScreen) : CommandBase(pScreen)
	{
	}
	void movePenTo(int aX, int aY)
	{
		saveStateOfScreen( );
		pScreen->moveToPoint(aX,aY);
		pScreen->show( );
	}
};

class WriteCommand : public CommandBase 
{
public:
	WriteCommand(Screen* pScreen) : CommandBase(pScreen)
	{
	} 
	void writeChar(char aChar)
	{
		saveStateOfScreen( );
		pScreen->writeChar(aChar);
		pScreen->show( );
	}
};

class UndoCommand : public CommandBase
{
public:
	UndoCommand( Screen* pScreen) : CommandBase(pScreen)
	{
	} 
	void undo( )
	{
		CommandBase::undo( );
	}
};
	

void main( )
{
	Screen* theScreen = new Screen;
	MoveToCommand mCommand(theScreen);
	WriteCommand  wCommand(theScreen);
	UndoCommand   uCommand(theScreen);

	mCommand.movePenTo(1,2);
	wCommand.writeChar('A');
	mCommand.movePenTo(2,4);
	wCommand.writeChar('b');
	uCommand.undo( );
	wCommand.writeChar('B');
	mCommand.movePenTo(4,8);
	wCommand.writeChar('C');
	mCommand.movePenTo(3,6);
	wCommand.writeChar('D');
	mCommand.movePenTo(5,10);
	wCommand.writeChar('E');
	uCommand.undo( ); 
	uCommand.undo( );
	uCommand.undo( );
	uCommand.undo( );
	mCommand.movePenTo(5,10);
	wCommand.writeChar('F');
	theScreen->show( );//可以去掉，在每个制图动作内部调用
}