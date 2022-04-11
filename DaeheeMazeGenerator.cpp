
#include <ics46/factory/DynamicFactory.hpp>
#include "DaeheeMazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,DaeheeMazeGenerator,"Daehee's Algorithm(Required)");

//default constructor with no argument
DaeheeMazeGenerator::DaeheeMazeGenerator()
{
}
//Generator 
void DaeheeMazeGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();
    vector<vector<bool>> visited(maze.getWidth(), vector<bool>(maze.getHeight(),false));
    //call recursive function
    RecursivePath(0,0,visited,maze);
}
//recursive function. Using backtrack to generate all maze and visit all cells.
void DaeheeMazeGenerator::RecursivePath(int x, int y, vector<vector<bool>>& visited, Maze& maze)
{
    //get direction vectors that have all possible move direction
    vector<Direction> validDirection = checkAllSide(x,y,visited,maze);
    visited[x][y] = true;
    //use while loop to run the recursive function
    while(validDirection.size() > 0)
    {
        int newX = x;
		int newY = y;
        //change the newX and newY, get the direction value
        Direction nextDirection = nextCell(newX,newY,validDirection);
        if(maze.wallExists(x,y,nextDirection))
        {
            maze.removeWall(x,y,nextDirection);
            //recursive
            RecursivePath(newX,newY,visited,maze);
        }
        validDirection = checkAllSide(x,y,visited,maze);
    }
}

//Source code From: https://en.cppreference.com/w/cpp/numeric/random/rand
//Randomly choose the direction and using & pointers to change the value of x(width) and y(height) and return direction that it moved
Direction DaeheeMazeGenerator::nextCell(int& x, int& y, vector<Direction> &move)
{
    int size = move.size();
    int idx = rand()% size;
    if(move[idx] == Direction::up)
    {
        y--;
        return move[idx];
    }
    else if(move[idx] == Direction::down)
    {
        y++;
        return move[idx];
    }
    else if(move[idx] == Direction::left)
    {
        x--;
        return move[idx];
    }
    else
    {
        x++;
        return move[idx];
    }
}

//Determine which direction is avaliable to generate the maze
vector<Direction> DaeheeMazeGenerator::checkAllSide(int x, int y, vector<vector<bool>>& visited, Maze& maze)
{
    vector<Direction> possible_Direction;
    if(x-1>=0 && !visited[x-1][y])
    {
        possible_Direction.push_back(Direction::left);
    }
    if(x+1 < maze.getWidth() && !visited[x+1][y])
    {
        possible_Direction.push_back(Direction::right);
    }
    if(y-1 >= 0 && !visited[x][y-1])
    {
        possible_Direction.push_back(Direction::up);
    }
    if(y+1 < maze.getHeight() && !visited[x][y+1])
    {
        possible_Direction.push_back(Direction::down);
    }
    return possible_Direction;
}