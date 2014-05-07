maze-gen-svg
============

Maze generator that produces SVG images of the resulting maze and solution.

This was originally written in 2010 for CptS 233 @ WSU.

####Compiling

    g++ main.cpp maze.cpp -o maze

####Possible command line arguments

    xxx is an int for the x width of the maze (default 20)
    yyy is an int for the y height of the maze (default 20)
    enterX is an int for the column to enter the map (from the top, default 0)
    exitX is an int for the column to exit the map (from the bottom, default -1)
      exitX of -1 makes exit on last column
    print-solution is a bool value (1,0) for making the out-solved.svg (default 1)
    scale is an int for size of SVG render (default 20)

1. `maze this-help` _This is invalid and will print out help on the CLI_
2. `maze xxx yyy`
3. `maze xxx yyy print-solution`
4. `maze xxx yyy enterX exitX`
5. `maze xxx yyy enterX exitX print-solution`
6. `maze xxx yyy enterX exitX print-solution scale`
