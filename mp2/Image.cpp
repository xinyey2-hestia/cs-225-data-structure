#include "Image.h"
using namespace std;
#include <cmath>
#include <cstdlib>

void Image::lighten(){
for (unsigned i=0; i<this->width();i++){
  for(unsigned j=0; j<this->height();j++ ){
    HSLAPixel* cur = this->getPixel(i,j);
    if ((cur->l+0.1)<=1)
    cur->l+=0.1;
    else
    cur->l =1;
  }
}

}


void Image::lighten(double amount){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->l+amount)<=1)
      cur->l+=amount;
      else
      cur->l =1;
    }
  }


}


void Image::darken(){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->l-0.1)>=0)
      cur->l=cur->l-0.1;
      else
      cur->l =0;
    }
  }

}


void 	Image::darken (double amount){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->l-amount)>=0)
      cur->l=cur->l-amount;
      else
      cur->l =0;
    }
  }

}


void 	Image::saturate (){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->s+0.1)<=1)
      cur->s+=0.1;
      else
      cur->s =1;
    }
  }


}


void 	Image::saturate (double amount){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->s+amount)<=1)
      cur->s+=amount;
      else
      cur->s =1;
    }
  }

}


void 	Image::desaturate (){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->s-0.1)>=0)
      cur->s=cur->s-0.1;
      else
      cur->s =0;
    }
  }

}


void 	Image::desaturate (double amount){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if ((cur->s-amount)>=0)
      cur->s=cur->s-amount;
      else
      cur->s=0;
    }
  }

}


void 	Image::grayscale (){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);


      cur->s=0;
    }
  }

}


void 	Image::rotateColor (double degrees){
  for (unsigned i=0; i<this->width();i++){
    for(unsigned j=0; j<this->height();j++ ){
      HSLAPixel* cur = this->getPixel(i,j);
      if((cur->h+degrees)>360){
        cur->h =cur->h+degrees-360;
      }
      else if((cur->h+degrees)<0){
        cur->h= cur->h+degrees+360;
      }
      else
      cur->h +=degrees;



    }
  }

}


void 	Image::illinify (){
  for (unsigned x= 0;x<this->width();x++){
    for (unsigned y=0; y<this->height();y++){
      HSLAPixel* current = this->getPixel(x,y);

      if (current->h ==0)
      current->h =11;
      else if (abs(current->h-11)<=180&&abs(216-current->h)<=180){
        if (abs(current->h-11)<abs(216-current->h))
        current->h = 11;
        else current->h =216;

      }
      else if (abs(current->h-11)>180){
        if (abs(371-current->h)<abs(current->h-216))
        current->h = 11;
        else current->h = 216;
      }
      else if (abs(216-current->h)>180){
        if ((144+current->h)<abs(current->h-11))
        current->h = 216;
        else current->h = 11;
      }
    }

}
}


void 	Image::scale (double factor){


if (factor>1){
  Image bigone;
  bigone.resize(this->width()*factor,this->height()*factor);
  for(int i=0; i<bigone.width();i++){
    for (int j=0; j<bigone.height();j++){

      (bigone.getPixel(i,j))->s = (this->getPixel(i/factor,j/factor))->s;
      (bigone.getPixel(i,j))->l = (this->getPixel(i/factor,j/factor))->l;
      (bigone.getPixel(i,j))->h = (this->getPixel(i/factor,j/factor))->h;
      (bigone.getPixel(i,j))->a = (this->getPixel(i/factor,j/factor))->a;
    }
  }
  *this = bigone;
}
else if (factor<1){

  int small = 1/factor;
  Image smallone;
  smallone.resize(this->width()*factor,this->height()*factor);
  for (int i =0;i<this->width()*factor;i++){
    for (int j=0;j<this->height()*factor;j++){
      (smallone.getPixel(i,j))->s = (this->getPixel(i*small,j*small))->s;
      (smallone.getPixel(i,j))->l = (this->getPixel(i*small,j*small))->l;
      (smallone.getPixel(i,j))->h = (this->getPixel(i*small,j*small))->h;
      (smallone.getPixel(i,j))->a = (this->getPixel(i*small,j*small))->a;


    }
  }
  *this = smallone;
}
else
this->resize(factor*this->width(),factor*this->height());


}


void 	Image::scale (unsigned w, unsigned h){
  unsigned y = this->height();
  unsigned x = this->width();
  unsigned fin = 0;
  double factor=1;
  if (w>h){
  fin = h;
  factor = (double)fin/y;
}
  else if (h>w){
  fin =w;
  factor = (double)fin/x;
}



  this->scale(factor);


}
