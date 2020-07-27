#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */


double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    //PNG & png, const Point PNG & png, const Point
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  it = NULL;
  start = Point(-1,-1);
  picture = PNG();
  tolerance =0.0;
  x= -1;
  y= -1;
  height =0;
  width =0;


}


ImageTraversal::Iterator::Iterator(ImageTraversal *a){
  it = a;
  start = a->getpoint();
  picture = a->getpng();
  x = start.x;
  y = start.y;
  tolerance = a->gettolerance();
  height = picture.height();
  width = picture.width();

  for (unsigned i=0; i<height; i++){
    vector<bool> visited;
    for (unsigned j =0 ; j<width; j++){
      visited.push_back(false);

    }
    isvisited.push_back(visited);
  }
}

 void ImageTraversal::Iterator::move(){
   if (x+1<width){
     Point right(x+1,y);
     if (!isvisited[right.x][right.y]&&calculateDelta(*picture.getPixel(start.x,start.y),*picture.getPixel(right.x,right.y))<tolerance){
       it->add(right);
     }
   }

   if (y+1<height){
     Point up(x,y+1);
     if (!isvisited[up.x][up.y]&&calculateDelta(*picture.getPixel(start.x,start.y),*picture.getPixel(up.x,up.y))<tolerance){
       it->add(up);
     }
   }

   if (x!=0){
     Point left(x-1,y);
     if (!isvisited[left.x][left.y]&&calculateDelta(*picture.getPixel(start.x,start.y),*picture.getPixel(left.x,left.y))<tolerance){
       it->add(left);
     }
   }

   if (y!=0){
     Point down(x,y-1);
     if (!isvisited[down.x][down.y]&&calculateDelta(*picture.getPixel(start.x,start.y),*picture.getPixel(down.x,down.y))<tolerance){
       it->add(down);
     }
   }
 }
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.


 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point temp = it->pop();
  x = temp.x;
  y = temp.y;

  isvisited[x][y]=true;
  move();



 while (!it->empty()){
   temp = it->peek();
   if (!isvisited[temp.x][temp.y])
   break;

   it->pop();
 }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */

  return this->it->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

    if(this==&other)
    return false;

   return(&this->it->getpoint()!=&other.it->getpoint());

}

ImageTraversal::~ImageTraversal(){

}
ImageTraversal::Iterator::~Iterator(){
  delete it;
}
