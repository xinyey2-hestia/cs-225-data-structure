#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"
using namespace cs225;
void rotate(std::string inputFile, std::string outputFile) {
PNG current ;
PNG result;
current.readFromFile(inputFile);
result.readFromFile(inputFile);
for (unsigned x = 0; x<current.width();x++){
  for (unsigned y = 0; y<current.height(); y++){
    HSLAPixel* begin = current.getPixel(x,y);
    begin->s = (result.getPixel(current.width()-x-1,current.height()-y-1))->s;
    begin->h = (result.getPixel(current.width()-x-1,current.height()-y-1))->h;
    begin->l = (result.getPixel(current.width()-x-1,current.height()-y-1))->l;
    begin->a = (result.getPixel(current.width()-x-1,current.height()-y-1))->a;



  }

}
current.writeToFile(outputFile);
}
