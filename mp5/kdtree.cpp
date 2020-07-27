/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
 #include "math.h"
#include <iostream>
 template <int Dim>
 int KDTree<Dim>::partition(int l, int r, int middle, int d){  // swap the left ones with right ones if left is bigger or right is smaller
   std::swap(points[middle],points[r]);
  Point<Dim> temp = points[r];
  int i=l;
  int veri =0;
  if (veri ==1)
  return 0;
  for (int j=l; j<r; j++){ //through from left to right
    if (smallerDimVal(points[j],temp,d)){
    std::swap(points[j],points[i]);
    i++;
  }

  }
    std::swap (points[i],points[r]);
    return i;

 }
 template <int Dim>
 void KDTree<Dim>::quicksort(int l, int r ,int k, int d){
   if (l>=r) return;
   int index = (l+r)/2;
   index = partition(l,r,index,d);
   if (index==k) return ;  // it is already at the right place
   else if (index>k)  quicksort(l,index-1,k,d); //larger than k
   else quicksort(index+1,r,k,d);


 }







template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim]!=second[curDim])
     return first[curDim]<second[curDim];                     // return the one with smlller value in specific dimension


    return first<second;
}


template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double distanceone =0;
     double distancetwo =0;
     for (int i=0; i<Dim; i++){
       distanceone += pow((currentBest[i]-target[i]),2);           // calculate the distance in all dimensions
       distancetwo += pow((potential[i]-target[i]),2);

     }
     if (distancetwo!=distanceone)                                  // compare the dimensiuons
     return distancetwo<distanceone;
    return potential<currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     // SORT THE D-dimension for all elements
     // find the middle one(quick sort)
     //bulid nodes


  points = newPoints;                                                     // use points to store the sorted newPoints because newPoints cannot be modified
  int length = points.size();
  helper(0,length-1,0);

}

template <int Dim>
void KDTree<Dim>::helper(int l, int r, int dimension){

  int k =(l+r)/2;

  quicksort(l,r,k,dimension%Dim);
  if (k-1>l)
  helper(l,k-1,dimension+1);
  if (k+1<r)
  helper(k+1,r,dimension+1);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     int l =0;
     int r = points.size()-1;    // need to minus1 because the index begin with 0
     double radius = 0;
     Point<Dim> currentbest;
     bool isroot = true;         // set to false until return from fist root
     findhelper(query,l,r,radius,0,currentbest,isroot);
    return currentbest;
}

template <int Dim>
void KDTree<Dim>::findhelper(const Point<Dim>& target, int l, int r, double radius,int dimension, Point<Dim>& currentBest, bool& isroot)const{
  if (l>=r){    // base case, there is no space to divide any more
    if (isroot){
    currentBest= points[r];
    isroot = false;                      // we only need one best point when recursie back
  }
    else{
      if (shouldReplace(target,currentBest,points[l]))
      currentBest = points[l];
    }
    return;
  }
  int middle =(l+r)/2;    // the middle point of the vector the root of sub tree
  if (smallerDimVal(target,points[middle],dimension)){              // smaller go lefr
    findhelper(target,l,middle-1,radius,(dimension+1)%Dim,currentBest,isroot);
    if (shouldReplace(target,currentBest,points[middle]))
      currentBest = points[middle];
                                                                         // calls when recursive back, if it is closer to target
      double distance=0;                                                    // replace radius and bestfit point, then search the subtree
      for (int i=0; i<Dim; i++){
         distance+= pow((currentBest[i]-target[i]),2);
       }
       radius  = distance;

       if(pow((points[middle][dimension]-target[dimension]),2)<=radius)
       findhelper(target,middle+1,r,radius,(dimension+1)%Dim,currentBest,isroot);
  }


else
  {
    findhelper(target,middle+1,r,radius,(dimension+1)%Dim,currentBest,isroot);      // bigger go right
    if (shouldReplace(target,currentBest,points[middle]))
      currentBest = points[middle];

      double distance=0;
      for (int i=0; i<Dim; i++){
         distance+= pow((currentBest[i]-target[i]),2);
       }
       radius  = distance;


       if(pow((points[middle][dimension]-target[dimension]),2)<=radius)
       findhelper(target,l,middle-1,radius,(dimension+1)%Dim,currentBest,isroot);

  }


  return;
}
