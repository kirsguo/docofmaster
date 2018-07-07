
class MapSite
{
public:
	virtual void onEnter( ) = 0;
};

class Door : public MapSite
{
public:
	void onEnter( )
	{ }
};

class Wall : public MapSite
{
public:
	void onEnter( )
	{ }
};

enum Direction { N, E, S, W };

class Room : public MapSite
{
public:
	void onEnter( )
	{  }
	void setSide(Direction d, MapSite* pSite)
	{  }
private:
	MapSite* sides[4];
};

class Map
{
public:
	void addRoom(Room* pRoom)
	{  }
private:
	Room* rooms[200];
	int   numOfRoom;
};

class MazeGame
{
public:
	Map* createMap( );
	// other functions;
private:
	// data;
};

Map* MazeGame::createMap( )
{
	Map* theMap = new Map;
	Room* r1 = new Room;
	Room* r2 = new Room;
	Door* theDoor = new Door;

	r1->setSide(N, new Wall);
	r1->setSide(E, theDoor);
	r1->setSide(S, new Wall);
	r1->setSide(W, new Wall);

	r2->setSide(N, new Wall);
	r2->setSide(W, theDoor);
	r2->setSide(S, new Wall);
	r2->setSide(E, new Wall);

	theMap->addRoom(r1);
	theMap->addRoom(r2);
	
	return theMap;
}


int main( )
{
	MazeGame g;
	Map* aMap = g.createMap( );
	
	return 0;
}