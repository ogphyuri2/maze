
#ifndef DAEHEESOLVER_HPP
#define DAEHEESOLVER_HPP
#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include "Maze.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
class DaeheeSolver: public MazeSolver
{
public:
   DaeheeSolver();
   virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
   void RecursiveTrack(int x, int y, vector<vector<bool>>& visited, const Maze & maze, MazeSolution& mazeSolution);
   vector<Direction> possible_Side(int x, int y,vector<vector<bool>>& visited,const Maze& maze);
   Direction nextMove(int& x, int& y, vector<Direction> &move);
};

#endif