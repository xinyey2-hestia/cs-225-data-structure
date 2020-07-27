#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
 MyColorPicker::MyColorPicker(double love): love(love){}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel yvette(0,0.5,love);
  if (x%2==0&&y%2==0){
    love =1;
  }
  return yvette;
}
