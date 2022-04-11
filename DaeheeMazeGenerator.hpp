
#ifndef DAEHEEMAZEGENERATOR_HPP
#define DAEHEEMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
using namespace std;
class DaeheeMazeGenerator: public MazeGenerator
{
public:
   DaeheeMazeGenerator();
   virtual void generateMaze(Maze& maze);
   void RecursivePath(int x, int y,vector<vector<bool>>& visited, Maze& maze);
   vector<Direction> checkAllSide(int x, int y, vector<vector<bool>>& visited,Maze& maze);
   Direction nextCell(int& x, int& y, vector<Direction> &move);
};

#endif