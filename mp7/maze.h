/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace cs225;
using namespace std;

class SquareMaze{
public:
  SquareMaze	();

  void makeMaze (int width, int height);

	bool canTravel (int x, int y, int dir) const;

	void setWall (int x, int y, int dir, bool exists);

	vector< int > solveMaze ();

	PNG* drawMaze () const;

	PNG* drawMazeWithSolution ();

  vector<int> solveMazehelper(int width, int height);

private:
  int width;
  int height;
  int size;
  DisjointSets uptree;
  vector<bool> rightwall;
  vector<bool>  downwall;
};

#endif
