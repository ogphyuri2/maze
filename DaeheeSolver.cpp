#include <ics46/factory/DynamicFactory.hpp>
#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "DaeheeSolver.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, DaeheeSolver, "DaeheeSolver(Required)");
//default constructor
DaeheeSolver::DaeheeSolver()
{
}
//solver generator
void DaeheeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    mazeSolution.restart();
    vector<vector<bool>> visited(maze.getWidth(), vector<bool>(maze.getHeight(),false));
    RecursiveTrack(0,0,visited,maze,mazeSolution);
}
//recursive function. using helper functions to get value and keep recursive until it complete the maze.
void DaeheeSolver::RecursiveTrack(int x, int y, vector<vector<bool>>& visited,const Maze & maze ,MazeSolution& mazeSolution)
{
    if(mazeSolution.isComplete())
    {
        return;
    }
    //marked as visited
    visited[x][y] = true;
    vector <Direction> availableDirections = possible_Side(x, y, visited, maze);
    //if solver move to location that can be move to other location, move solver to that direction
    if (availableDirections.size() > 0)
    {
        int newX = x;
        int newY = y;
        Direction nextDirection = nextMove(newX,newY,availableDirections);
        //let solver to move front
        mazeSolution.extend(nextDirection);
        RecursiveTrack(newX, newY, visited, maze, mazeSolution);
    }
    //backtracking, use backUp to move back the solver and re setting recursive function
    else
    {
        //let solver to move back
        mazeSolution.backUp();
        //get a previous cell value
        pair<int,int> cell = mazeSolution.getCurrentCell();
        RecursiveTrack(cell.first, cell.second, visited, maze, mazeSolution);
    }
}
//check adjacent cells. If there is wall or visited cell, solver cannot go to that direction
vector<Direction> DaeheeSolver::possible_Side(int x, int y,vector<vector<bool>>& visited,const Maze& maze)
{
    vector<Direction> availableDirections;
    if(!maze.wallExists(x,y,Direction::up) && !visited[x][y-1])
    {
        availableDirections.push_back(Direction::up);
    }
    if(!maze.wallExists(x,y,Direction::down) && !visited[x][y+1])
    {
        availableDirections.push_back(Direction::down);
    }
    if(!maze.wallExists(x,y,Direction::left) && !visited[x-1][y])
    {
        availableDirections.push_back(Direction::left);
    }
    if(!maze.wallExists(x,y,Direction::right) && !visited[x+1][y])
    {
        availableDirections.push_back(Direction::right);
    }
    return availableDirections;
}
//using & pointer to change the x and y value, and return the direction
Direction DaeheeSolver::nextMove(int& x, int& y, vector<Direction> &move)
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