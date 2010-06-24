#ifndef MAZE_H
#define MAZE_H

#include<iostream>
#include<string>
#include<fstream>		//for file actions
#include<cstdlib>		//For srand() & rand()
#include<ctime>			//For seeding srand(), with time()

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ios;

class Maze
{
	public:
		Maze(int x=20, int y=20, int enterX=0, int exitX=-1);

		void generate();
		bool printSVG(string fileName = "out.svg", bool solution = false, int scale = 10);
		void printScreen();
	private:
		void clearMaze();
		char findEmpty(int x, int y);
		void moveTo(int fromX, int fromY, int toX, int toY, char Dir);
		bool mazeFilled();

		static const unsigned MAXSIZE=302;	//This allows for a maze of up to 300x300
		int _x, _y, _enterX, _exitX;
		int _walls[MAXSIZE][MAXSIZE][2];	// [x][y][dir]  dir[0] = top  dir[1] = left
		char _path[MAXSIZE][MAXSIZE];		// 'd' down  'u' up  'r' right  'l' left  'e' exit
};

#endif