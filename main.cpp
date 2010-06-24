/*
 * Programer: Peter Olson
 * Class: Cpt S 223; Winter 2010; Section 1
 * Programming Assignment: Maze Generation
 * Date: 4/1/2010
 * Description: Create a maze
 */
#include "maze.h"
#include<iostream>
#include<cstdlib>	//for atoi();
#include<string>

using std::string;
using std::cout;

int main(int argc, char *argv[])
{
	int width = 20, height = 20, entrance = 0, exit = -1;
	int scale = 20;
	bool solution = true;

	switch(argc)
	{
		case 4:
			argv[3][0]=='0'?solution=false:solution=true;
		case 3:
			width = atoi(argv[1]);
			height = atoi(argv[2]);
			break;
		case 7:
			scale = atoi(argv[6]);
		case 6:
			argv[5][0]=='0'?solution=false:solution=true;
		case 5:
			width = atoi(argv[1]);
			height = atoi(argv[2]);
			entrance = atoi(argv[3]);
			exit = atoi(argv[4]);
			break;
		case 1:
			break;
		case 2:
		default:
			cout << "Possible command line arguments\n";
			cout << "print_solution is a bool value (1,0) for making the out_solved.svg\n";
			cout << "exitX of -1 automaticly makes exit on last column\n\n";
			cout << "1 arguments: .exe this_help\n";
			cout << "2 arguments: .exe xxx yyy\n";
			cout << "3 arguments: .exe xxx yyy print_solution\n";
			cout << "4 arguments: .exe xxx yyy enterX exitX\n";
			cout << "5 arguments: .exe xxx yyy enterX exitX print_solution\n";
			cout << "6 arguments: .exe xxx yyy enterX exitX print_solution scale\n";
			return 0;
	}

	Maze M(width,height,entrance,exit);
	M.generate();
	M.printSVG("out.svg",false,scale);
	if(solution)
		M.printSVG("out_solved.svg",true,scale);
	if((width<=20)&&(height<=20))
		M.printScreen();
	return 0;
}