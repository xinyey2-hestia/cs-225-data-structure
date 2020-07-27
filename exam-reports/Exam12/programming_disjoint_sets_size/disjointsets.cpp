#include "disjointsets.h"
using std::vector;

/**
 * Joins the set containing a and the set containing b.
 *
 * Should use union-by-size. In case of a tie, proceed as if the set containing
 * a has larger size than the set containing b.
 */
void DisjointSets::unionBySize(int a, int b) {
  // TODO: implement this function
  if (find(a)==find(b)){
    return;
  }
  int vol1 = simpleFind(a);
  int vol2 = simpleFind(b);
  int newsize = _data[vol1]+_data[vol2];

  if (_data[vol1]<=_data[vol2]){
    _data[vol2] = vol1;
    _data[vol1] = newsize;
  }
  else
  {
    _data[vol1] = vol2;
    _data[vol2] = newsize;
  }


}

/**
 * Finds the representative element of the set containing elem. Should compress
 * paths.
 */
int DisjointSets::find(int elem) {
  // TODO: modify this function to implement path compression
  if (_data[elem] < 0) {
    return elem;
  }
  return _data[elem] =find(_data[elem]);
}


/*************************************
 * PROVIDED CODE - no need to modify *
 *************************************/
void DisjointSets::makeSets(int num) {
  for (; num > 0; num--) {
    _data.push_back(-1);
  }
}

int DisjointSets::simpleFind(int elem) const {
  if (_data[elem] < 0) {
    return elem;
  }
  return simpleFind(_data[elem]);
}
