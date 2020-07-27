// your code here
#include "LNode.h"

void LNode::lookAtMeEven(Node **arr,int n){
for (int i=0; i<n;i=i+2){
  arr[i]->setLookingAt(this);
}
}

LNode::~LNode(){

}
