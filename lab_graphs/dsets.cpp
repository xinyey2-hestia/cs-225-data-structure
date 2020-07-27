/* Your code here! */
#include "dsets.h"
using namespace std;

void DisjointSets::addelements	(	int num	){
  for (int i=0; i<num; i++){

    uptree.push_back(-1);
  }

  return;
}

int DisjointSets::find(int elem){
  if (uptree[elem]<0)
  return elem;
  else{
    return uptree[elem]=find(uptree[elem]);
  }
}


void DisjointSets::setunion	(	int a, int b){
  if (find(a)==find(b))
  return;
  int rot1 =find(a);
  int rot2= find(b);
  int newsize = uptree[rot1]+uptree[rot2];
  if (uptree[rot1]<uptree[rot2]){
    uptree[rot2] = rot1;
    uptree[rot1] = newsize;

  }
  else{
    uptree[rot1] = rot2;
    uptree[rot2] = newsize;
  }
}
