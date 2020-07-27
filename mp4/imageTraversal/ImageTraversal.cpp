#include <cmath>
#include <iterator>
#include <iostream>
#include<vector>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
using namespace cs225;
using namespace std;
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

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(Point* ptr,ImageTraversal* trav) {
  /** @todo [Part 1] */
  start=ptr;
  trav_=trav;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
/*if(trav_->empty())  //if nothing is in the container, that means traversal is end
{
  start=NULL;
  return *this;
}
*/

Point st=trav_->pop();

//cout<<st.x<<","<<st.y<<endl;
int right=st.x+1;
int righty=st.y;

int upx=st.x;
int upy=st.y+1;

int leftx=st.x-1;
int lefty=st.y;

int downy=st.x;
int downx=st.y-1;

int w=trav_->png_.width();
int h=trav_->png_.height();
//unsigned w1=trav_->png_.width();
//unsigned h1=trav_->png_.height();
//trav_->visited[st.x][st.y]=1;

 if(right<w)     //check whether the right point is in the bound
 {
    HSLAPixel* current=trav_->png_.getPixel(trav_->start_pt.x,trav_->start_pt.y);
    HSLAPixel* original=trav_->png_.getPixel(right,righty);
    double temp=calculateDelta(*current,*original);
    if(temp<trav_->tole&&trav_->visited[right][righty]==0) //check whether pixel difference is within tolearance and whether we visited it before
      {
        Point t2(right,righty);
        trav_->add(t2);

      }

 }

  if(upy<h)                 //if the first case fails, go to the point which is below, check whether the point is within bound
 {
   HSLAPixel* current=trav_->png_.getPixel(trav_->start_pt.x,trav_->start_pt.y);
   HSLAPixel* original=trav_->png_.getPixel(upx,upy);
   if(calculateDelta(*current,*original)<trav_->tole&&trav_->visited[upx][upy]==0)    //check tolearance and whether visited before adding
     {
       Point t2(upx,upy);
       trav_->add(t2);


 }

 }

  if(leftx>-1)
  //if (st.x-1<w1)
 {
   HSLAPixel* current=trav_->png_.getPixel(trav_->start_pt.x,trav_->start_pt.y);
   HSLAPixel* original=trav_->png_.getPixel(leftx,lefty);
   if(calculateDelta(*current,*original)<trav_->tole&&trav_->visited[leftx][lefty]==0)
     {
       Point t2(leftx,lefty);
       trav_->add(t2);


 }

 }

 if(downx>-1)
// if(st.y-1<h1)
 {
   HSLAPixel* current=trav_->png_.getPixel(trav_->start_pt.x,trav_->start_pt.y);
   HSLAPixel* original=trav_->png_.getPixel(downy,downx);
   if(calculateDelta(*current,*original)<trav_->tole&&trav_->visited[downy][downx]==0)
     {
       Point t2(downy,downx);
       trav_->add(t2);

    }

 }

 if(trav_->empty())
 {
   start=NULL;
   return *this;
}

*start=trav_->peek();




return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //cout<<this->start->x<<" "<<this->start->y<<endl;
  return *start;
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

   return(this->start!=other.start);
}
