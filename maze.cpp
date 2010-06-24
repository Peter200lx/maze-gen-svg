#include "maze.h"

Maze::Maze(int x, int y, int enterX, int exitX)
{
	srand((int)time(NULL));	//Iniitialize rand with time

	for(int i=0;i<MAXSIZE;i++)	{
		for(int j=0;j<MAXSIZE;j++)	{
			_walls[i][j][0] = 0;
			_walls[i][j][1] = 0;		//Initialize all arrays to 0
			_path[i][j] = '\0';
		}
	}

	_x = x;
	_y = y;
	_enterX = enterX;
	if((exitX > 0)&&(exitX < _x))
		_exitX = exitX;
	else
		_exitX = x-1;
}

void Maze::generate()
{
	for(int i=0;i<_x;i++)
		for(int j=0;j<_y;j++)	//Set up all internal walls
			_walls[i][j][0] = _walls[i][j][1] = 1;
	for(int i=0;i<_x;i++)		//Set up horizontal bottom walls
		_walls[i][_y][0] = 1;
	for(int i=0;i<_y;i++)		//Set up vertical right walls
		_walls[_x][i][1] = 1;
	_walls[_enterX][0][0] = 0;	//Set up entrance
	_walls[_exitX][_y][0] = 0;	//Set up exit

	clearMaze();	//clear select walls to make maze
}

bool Maze::printSVG(string fileName, bool solution, int scale)
{
	int s = scale;	//scale
	ofstream outS;
	outS.open(fileName.c_str(),ios::out);	//Open the given file
	if(!outS)		//If there were errors opening the file
	{
		cout << "Error opening File!!" << endl;	//Display error to screen
		return false;
	}else			//If file opened properly...
	{
		outS << "<svg width=\"" << (_x+2)*s << "\" height=\"" << (_y+2)*s << "\" ";	//Print <svg* meta data
		outS << "version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;

		outS << "  <g transform=\"translate("<<s<<','<<s<<")\" stroke=\"black\"";		//Print <g* shift and style data
		outS << " stroke-width=\"" << s/5 << "\" stroke-linecap=\"round\">" << endl;

		for(int i=0;i<_x+2;i++)
		{
			for(int j=0;j<_y+2;j++)
			{
				if(_walls[i][j][0])	//horizontal	(top of cell)
					outS << "    <line x1=\""<<i*s<<"\" y1=\""<<j*s<<"\" x2=\""<<i*s+s<<"\" y2=\""<<j*s<<"\" />"<<endl;
				if(_walls[i][j][1]) //vertical		(left of cell)
					outS << "    <line x1=\""<<i*s<<"\" y1=\""<<j*s<<"\" x2=\""<<i*s<<"\" y2=\""<<j*s+s<<"\" />"<<endl;
			}
		}
		outS << "  </g>" << endl;

		if(solution)
		{
			outS << "  <g transform=\"translate("<<s<<','<<s<<")\" stroke=\"red\"";		//Print <g* shift and style data
			outS << " stroke-width=\"" << s/5 << "\" stroke-linecap=\"round\">" << endl;

			int sY = 0;
			int sX = _enterX;
			while(_path[sX][sY] != 'e')
			{
				switch(_path[sX][sY])
				{
				case 'd':
					outS << "    <line x1=\""<<sX*s+s/2<<"\" y1=\""<<sY*s+s/2<<"\" x2=\""<<sX*s+s/2<<"\" y2=\""<<sY*s+s+s/2<<"\" />"<<endl;
					sY += 1;
					break;
				case 'l':
					outS << "    <line x1=\""<<sX*s-s/2<<"\" y1=\""<<sY*s+s/2<<"\" x2=\""<<sX*s+s/2<<"\" y2=\""<<sY*s+s/2<<"\" />"<<endl;
					sX -= 1;
					break;
				case 'u':
					outS << "    <line x1=\""<<sX*s+s/2<<"\" y1=\""<<sY*s-s/2<<"\" x2=\""<<sX*s+s/2<<"\" y2=\""<<sY*s+s/2<<"\" />"<<endl;
					sY -= 1;
					break;
				case 'r':
					outS << "    <line x1=\""<<sX*s+s/2<<"\" y1=\""<<sY*s+s/2<<"\" x2=\""<<sX*s+s+s/2<<"\" y2=\""<<sY*s+s/2<<"\" />"<<endl;
					sX += 1;
					break;
					default:
						cout << "ERROR in path following" << endl;
				}
			}
			outS << "  </g>" << endl;
		}
		outS << "</svg>" << endl;
	}
	outS.close();	//Close the file, no probem running this even if error opening file

	return true;
}

void Maze::printScreen()
{
	cout << ' ';
	for(int i=0;i<_x;i++)		//print out top cell numbers
		cout << ' ' << i%10;

	for(int i=0;i<=_y;i++)
	{
		cout << endl << " ";
		for(int j=0;j<=_x;j++)
		{
			if(_walls[j][i][1]) //vertical		(left of cell)
				cout << '|';
			else if(_walls[j][i][0])	//horizontal	(top of cell)
				cout << '-';
			else
				cout << ' ';
			if(_walls[j][i][0])	//horizontal	(top of cell)
				cout << '-';
			else
				cout << ' ';
		}
		cout << endl << i%10;	//print out left cell numbers
		for(int j=0;j<=_x;j++)
		{
			if(_walls[j][i][1]) //vertical		(left of cell)
				cout << '|' << ' ';
			else
				cout << "  ";
		}
	}
	cout <<endl;
}

void Maze::clearMaze()
{
	int curX = _exitX, curY = _y - 1;	//Start clearing maze from exit
	int nextX = -1, nextY = -1;
	char nextD = '\0';
	bool deadEnd = false;
	_path[curX][curY] = 'e';			//Set exit cell to 'e'

	do{
		nextD = findEmpty(curX,curY);		//find avialable directions, randomly pick one
		if(nextD != '\0')			//If there is an aviable direction
		{
			switch(nextD)			//Move next? to that position
			{
				case 'u':
					nextX = curX;
					nextY = curY-1;
					break;
				case 'd':
					nextX = curX;
					nextY = curY+1;
					break;
				case 'l':
					nextX = curX-1;
					nextY = curY;
					break;
				case 'r':
					nextX = curX+1;
					nextY = curY;
					break;
				case '\0':
					cout << "ERROR in nextD switch, NULL result" << endl; 
				default:
					nextX = -1;
					nextY = -1;
					cout << "ERROR int result from findEmpty" << endl;
			}

			moveTo(curX,curY,nextX,nextY,nextD);	//clear wall between, set _path[cur?] to direction came from

			curX = nextX;		//move loop to new cell
			curY = nextY;
			deadEnd = false;
		}else
		{
			switch(_path[curX][curY])	//find direction we came from
			{
				case 'u':			//move back in that direction
					curY -= 1;
					break;
				case 'd':
					curY += 1;
					break;
				case 'l':
					curX -= 1;
					break;
				case 'r':
					curX += 1;
					break;
				case 'e':
					cout << "ERROR current location is end" << endl;
					break;
				case '\0':
					cout << "ERROR current location is NULL" << endl;
					break;
				default:
					cout << "ERROR in value of _path[cur?]" << endl;
			}
			deadEnd = true;
		}
	}while((!deadEnd)||(!mazeFilled()));//Continue until a dead-end and the maze is filled
}

char Maze::findEmpty(int x, int y)
{
	char ret = '\0';	//Return NULL if no direction found
	char possib[4] = {0,0,0,0};
	int num = -1;

	if((x+1 < _x)&&(!_path[x+1][y]))
	{						//If possible to move in this direction
		num++;				//Say we've found a direction
		possib[num] = 'r';	//Add direction to array
	}
	if((y+1 < _y)&&(!_path[x][y+1]))
	{
		num++;
		possib[num] = 'd';
	}
	if((x-1 >= 0)&&(!_path[x-1][y]))
	{
		num++;
		possib[num] = 'l';
	}
	if((y-1 >= 0)&&(!_path[x][y-1]))
	{
		num++;
		possib[num] = 'u';
	}

	if(num >= 0)	//If at least one direction has been found
		ret = possib[rand()%(num+1)];	//Randomly pick one from array

	return ret;
}

	//clear wall between, set _path[cur?] to direction came from
void Maze::moveTo(int fromX, int fromY, int toX, int toY, char Dir)
{
	if(Dir == 'u')
	{
		_path[toX][toY] = 'd';			//Set backtrack path
		_walls[fromX][fromY][0] = 0;	//Clear wall inbetween
	}
	else if(Dir == 'l')
	{
		_path[toX][toY] = 'r';
		_walls[fromX][fromY][1] = 0;
	}
	else if(Dir == 'd')
	{
		_path[toX][toY] = 'u';
		_walls[toX][toY][0] = 0;
	}
	else if(Dir == 'r')
	{
		_path[toX][toY] = 'l';
		_walls[toX][toY][1] = 0;
	}
	else
		cout << "Error, moveTo called with null Dir" << endl;
}

bool Maze::mazeFilled()
{
	for(int i=0;i<_x;i++)
		for(int j=0;j<_y;j++)	
			if(_path[i][j] == '\0')
				return false;
	return true;
}