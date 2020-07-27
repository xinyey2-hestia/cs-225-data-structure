#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include<vector>
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

using namespace cs225;
using namespace std;
/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_=png;
  stack_.push(start);
  tole=tolerance;
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
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
Point* temp=&(stack_.top());
return Iterator (temp,new DFS(png_,start_pt,tole));
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  Iterator endingone(NULL,this);
  return endingone;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
 stack_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */

  Point cur=stack_.top();
  visited[cur.x][cur.y]=1;
  stack_.pop();
  while (!stack_.empty()){

      Point next = stack_.top();
      if (visited[next.x][next.y]==0)
      break;

      stack_.pop();

  }
  return cur;


 }
/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
 Point t=stack_.top();
 return t;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return(stack_.size()==0);
}
