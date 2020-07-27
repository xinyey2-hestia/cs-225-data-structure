#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image& picture,unsigned max){
arr= new Image*[max+1];
for (int i=0;i<max+1;i++){
  arr[i] = NULL;
}
arr[0] = new Image();
*arr[0] = picture;
index = max+1;
cur=1;
xcor = new int[max+1];
ycor = new int[max+1];
for (int i=0; i<max+1;i++){
  xcor[i]=0;
  ycor[i]=0;
}
}

void StickerSheet::clear(){


for (int i=0; i<index;i++){
  if(arr[i]!=NULL){
    delete arr[i];
    arr[i] =NULL;
  }
}
delete[] arr;
arr = NULL;
if (xcor!= NULL)
delete[] xcor;
xcor =NULL;
if (ycor!=NULL)
delete[] ycor;
ycor = NULL;
}
StickerSheet::~StickerSheet(){
clear();
}
void StickerSheet::copy(const StickerSheet& other){
  arr= new Image*[other.index];
  xcor =new int[other.index];
  ycor = new int[other.index];
  index = other.index;
  for (int i = 0; i<index;i++){
    xcor[i] = 0;
    ycor[i] = 0;

  }
  for (int i =0;i<other.index;i++){
    arr[i] = NULL;
  }

  for (int i = 0;i<index;i++){
    if (other.arr[i]!=NULL){
      arr[i] = new Image;
      *arr[i] = *(other.arr[i]);
      xcor[i] = other.xcor[i];
      ycor[i] = other.ycor[i];

    }
  }
}
StickerSheet::StickerSheet (const StickerSheet &other){
 copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
  if (this!=&other){

clear();
copy(other);
}
return *this;


}


void 	StickerSheet::changeMaxStickers (unsigned max){

if ((max+1) == index){
  return;
}
if ((max+1)>index){
  Image ** temp = new Image*[max+1];
  int* txor = new int[max+1];
  int* tyor =new int[max+1];

  for (int i=0;i<index;i++){

    temp[i] = arr[i];
    txor[i] = xcor[i];
    tyor[i] = ycor[i];

}
for (int i =index;i<max+1;i++){
  temp[i] = NULL;

}

delete[] arr;
delete xcor;
delete ycor;

arr = temp;
xcor = txor;
ycor = tyor;
index = max+1;
return;
}

if(max+1<index){
  Image ** temp = new Image*[max+1];
  int* txor = new int[max+1];
  int* tyor =new int[max+1];
  cur =0;
  for (int i=0;i<max+1;i++){

    temp[i] = arr[i];
    txor[i] = xcor[i];
    tyor[i] = ycor[i];
    cur++;


}
delete[] arr;
delete xcor;
delete ycor;

arr = temp;
xcor = txor;
ycor = tyor;
index = max+1;
}

return;
}


int 	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){

for (int i=1; i<index; i++){
  if (arr[i] == NULL){
    arr[i] = new Image;
    *arr[i] = sticker;
    xcor[i] = x;
    ycor[i] = y;
    return i;
  }

}

if (cur+1>index){
  return -1;
}
else{
arr[cur] = new Image;
*arr[cur] = sticker;
xcor[cur] = x;
ycor[cur] = y;
cur+=1;
return cur-1;
}

}

bool 	StickerSheet::translate (unsigned ind, unsigned x, unsigned y){
if ((ind+1>index)||(arr[ind+1]==NULL)){
  return false;
}
xcor[ind+1] = x;
ycor[ind+1] = y;
return true;
}


void 	StickerSheet::removeSticker (unsigned ind){

if (ind+1>index||(arr[ind+1]==NULL)){
  return;
}
delete arr[ind+1];
arr[ind+1] =NULL;



}


Image * 	StickerSheet::getSticker (unsigned ind) const{

if (ind+1>index||(arr[ind+1]==NULL)){
  return NULL;
}
else
  return arr[ind+1];

}


Image 	StickerSheet::render () const{
int needheight =0;
int needwidth =0;
for (int i=0;i<index;i++){
  if(arr[i]!=NULL){
    int curheight = arr[i]->height()+ycor[i];
    int curwidth = arr[i]->width()+xcor[i];
    if (curheight>needheight)
    needheight = curheight;
    if (curwidth>needwidth)
    needwidth = curwidth;
  }
}

Image output;
output.resize(needwidth,needheight);

HSLAPixel* current;

for (int z=0; z<index;z++){
  if (arr[z]!=NULL){
  int  objwidth = arr[z]->width();
    int objheight = arr[z]->height();
    int x =xcor[z];
    int y =ycor[z];

for(int i=0; i<objwidth;i++){
  for (int j=0;j<objheight;j++){
    current = output.getPixel(i+x,j+y);

    if(arr[z]->getPixel(i,j)->a!=0){
      current->a = arr[z]->getPixel(i,j)->a;
      current->h = arr[z]->getPixel(i,j)->h;
      current->l = arr[z]->getPixel(i,j)->l;
      current->s = arr[z]->getPixel(i,j)->s;
    }
  }
}
}


}

return output;
}
