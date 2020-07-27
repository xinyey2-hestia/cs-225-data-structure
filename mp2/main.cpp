#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
using namespace std;
#include<iostream>



int main() {
  Image first;
  Image second;
  Image third;
  Image four;
  first.readFromFile("1.png");

  four.readFromFile("i.png");

  second.readFromFile("2.png");

  third.readFromFile("3.png");

  StickerSheet sheet(second, 5);
  sheet.addSticker(third,40,53);
  sheet.addSticker(first,30,65);
  sheet.addSticker(first,166,233);
  sheet.removeSticker(1);
  sheet.removeSticker(0);
  sheet.addSticker(second,154,376);
  sheet.addSticker(four,556,477);
  sheet.addSticker(four,341,54);
  sheet.addSticker(second,122,333);
  StickerSheet opera(four,3);


  StickerSheet shee1(sheet);
  shee1.translate(1,888,888);
  cout<<"succeed"<<endl;
  shee1.changeMaxStickers(1);
  shee1.addSticker(four,365,233);

  Image out = shee1.render();
  cout<<"succeed"<<endl;

Image output = sheet.render();

output.writeToFile("myImage.png");
out.writeToFile("myge.png");
opera = shee1;
Image* operat = shee1.getSticker(0);
operat->writeToFile("opreeeee.png");



  return 0;
}
