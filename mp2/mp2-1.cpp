#include "Image.h"
using namespace std;
#include<iostream>
using namespace cs225;

int main() {
  Image alma;

  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");

  alma.readFromFile("alma.png");
  alma.scale(36,1000);
  cout<<"222"<<endl;
  alma.writeToFile("scale36.png");

  return 0;
}
