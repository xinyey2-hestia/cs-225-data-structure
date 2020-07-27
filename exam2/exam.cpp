// Your code here!
#include "exam.h"
using namespace exam;

  Matrix exam::flip_vert(const Matrix &m){
 int column = m.get_num_columns();
 int row = m.get_num_rows();
 Matrix newm(row,column);
 for (int i=0; i<column;i++){
   for (int j =0; j<row;j++){

     newm.set_coord(j,i,m.get_coord(j,column-i-1));

   }
 }

 return newm;


  }
