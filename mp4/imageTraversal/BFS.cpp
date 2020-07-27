
#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <vector>
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"
#include<iostream>
using namespace cs225;
using namespace std;
/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_=png;
  tole=tolerance;
  q.push(start);
   start_pt=start;
  visited.resize(png_.width(), vector<int> (png_.height()));
  for(unsigned i=0;i<png_.width();i++)
  {
    for(unsigned j=0;j<png_.height();j++)
    {
      visited[i][j]=0;
    }
  }


}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  Point* temp=&(q.front());
  Iterator st(temp,new BFS(png_,start_pt,tole));
  return st;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  Iterator i(NULL,this);
  return i;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  q.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */

  Point p=q.front();
  visited[p.x][p.y]=1;
  q.pop();
  while (!q.empty()){

      Point next = q.front();
      if (visited[next.x][next.y]==0)
      break;

      q.pop();

  }
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
 Point p=q.front();
  return p;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return (q.size()==0);
}
