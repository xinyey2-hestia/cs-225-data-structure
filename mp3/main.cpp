#include "list.h"
using namespace std;
#include <iostream>
int main() {
  List<int> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }
  cout<<list.size()<<endl;
  return 0;
}
