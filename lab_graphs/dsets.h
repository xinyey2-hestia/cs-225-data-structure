/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>
using namespace std;

class DisjointSets{
public:
  vector<int> uptree;      // inside arr which stores the data
  void addelements(int num);
  int find(int elem);
  void setunion(int a, int b);
};
#endif
