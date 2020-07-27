/* Your code here! */
#include "maze.h"
#include <map>
#include <queue>
#include <vector>
SquareMaze::SquareMaze	(){
  height =0;
  width =0;
  size = 0 ;
}

void SquareMaze::makeMaze (int width, int height)
  {
    this->width = width;
    this->height = height;

  uptree.addelements(width*height);
  this->size = height*width;
	int n =0;
   srand (time(NULL));
  for (int i=0; i<size; i++){
    rightwall.push_back(true);
    downwall.push_back(true);
  }
  int checkone = 0;
	while (n<size/2){
		int x = rand()%(width-1);
		int y = rand()%(height-1);
    checkone = rand()%2;
    if(checkone){

			if (uptree.find(x+y*width)!=uptree.find(x+1+y*width)&&rightwall[x+y*width]==true){
				uptree.setunion((x+y*width),(x+1+y*width));
				rightwall[x+y*width] = false;
				n++;
        checkone = 0;
			}

  }
			else{
				if (uptree.find(x+y*width)!=uptree.find(x+(y+1)*width)&&downwall[x+y*width]==true){
					uptree.setunion((x+y*width),(x+(y+1)*width));
					downwall[x+y*width] = false;
					n++;
          checkone = 1;
				}
			}

	}

  for (int i=0; i<height-1; i++){       // current height index
    for (int j=0; j<width-1; j++){      // current width index
      if (checkone){
      if (uptree.find(i*width+j)!=uptree.find(i*width+j+1)&&rightwall[i*height+j]==true){
  			rightwall[i*width+j] = false;
  			uptree.setunion(i*width+j,i*width+j+1);
  		}
      if (uptree.find(i*width+j)!=uptree.find((i+1)*width+j)&&downwall[i*width+j]==true){
  			downwall[i*width+j] = false;
  			uptree.setunion(i*width+j,(i+1)*width+j);
  		}
      checkone = 0;

    }
    else{
      if (uptree.find(i*width+j)!=uptree.find((i+1)*width+j)&&downwall[i*width+j]==true){
        downwall[i*width+j] = false;
        uptree.setunion(i*width+j,(i+1)*width+j);
      }
      if (uptree.find(i*width+j)!=uptree.find(i*width+j+1)&&rightwall[i*height+j]==true){
  			rightwall[i*width+j] = false;
  			uptree.setunion(i*width+j,i*width+j+1);
  		}
      checkone = 1;

    }


    }
    // now check the downwall for rightmost column

      if (uptree.find(i*width+width-1)!= uptree.find((i+1)*width+width-1)&&downwall[i*width+width-1]==true){
        uptree.setunion(i*width+width-1,(i+1)*width+width-1);
        downwall[i*width+width-1] =false;
      }

  }

   // now check the bottom row
   for (int i =0; i<width-1; i++){
     if (uptree.find((height-1)*width+i)!=uptree.find((height-1)*width+i+1)&&rightwall[(height-1)*width+i]==true){
       uptree.setunion((height-1)*width+i,(height-1)*width+i+1);
       rightwall[(height-1)*width+i] = false;
     }
   }
}





  /*int counterx =0;
	int countery=0;

	for (int i=0; i<width*height;i++){
		if (uptree.find(i)!=uptree.find(i+1)&&counterx<width-1){
			rightwall[i] = false;
			uptree.setunion(i,i+1);
		}
		else{
			rightwall[i] = true;
		}
		counterx++;
		if (uptree.find(i)!=uptree.find(i+width)&&countery<height-1){
			downwall[i] = false;
			uptree.setunion(i,i+width);
		}
		else{
			downwall[i] = true;
		}




		if (counterx ==width){
			countery++;
			counterx =0;
		}

	}*/




bool SquareMaze::canTravel (int x, int y, int dir) const{
  if (dir==0&&x!=width-1){
    return rightwall[y*width+x];
  }
  if (dir==1&&y!=height-1)
  return downwall[y*width+x];

  if (dir==2&&x>0)
  return rightwall[y*width+x-1];

  if (dir==3&&y>0)
  return downwall[(y-1)*width+x];


  return false;
}

void SquareMaze::setWall (int x, int y, int dir, bool exists){
  if (dir==0)
  rightwall[y*height+x] = exists;
  if (dir==1)
  downwall[y*height+x] = exists;
}
vector<int> SquareMaze::solveMazehelper(int width, int height){

  vector<int> path;
  map<int,int> parent;
  queue <int>myqueue;


  map <int, int> pathMap;
   bool visited [50][50];

   // initialize the array to be false
   for (int i = 0; i < width; i++ )
   {
       for (int j = 0; j < height; j++ )
       {
           visited[i][j] = false;
       }
   }

  visited[0][0] = true;
  myqueue.push(0);
  while (!myqueue.empty()){
    int cur = myqueue.front();
    myqueue.pop();

    if (canTravel(cur%width, cur/height,0)&&visited[(cur+1)%width][(cur+1)/height]==false){
        myqueue.push(cur+1);
        parent[cur+1] = cur;
        visited[(cur+1)%width][(cur+1)/height]=true;
      }
    if (canTravel(cur%width, cur/height,1)&&visited[(cur+width)%width][(cur+width)/height]==false){
        myqueue.push(cur+width);
        parent[cur+width] = cur;
      visited[(cur+width)%width][(cur+width)/height]=true;
    }

    if(canTravel(cur%width, cur/height,2)&&visited[(cur-1)%width][(cur-1)/height]==false){
      myqueue.push(cur-1);
      parent[cur-1] = cur;
      visited[(cur-1)%width][(cur-1)/height]=true;
    }
    if (canTravel(cur%width, cur/height,3)&&visited[(cur-width)%width][(cur-width)/height]==false){
      myqueue.push(cur-width);
      parent[cur-width] = cur;
      visited[(cur-width)%width][(cur-width)/height]=true;
    }



  }

  int maxlength =0;
  int maxindex =0;
  int count =0;
  for (int j=0; j<width; j++){
    count =0;
    int end = (height-1)*width+j;
    while(end!=0){
      end = parent[end];
      count++;
    }
    if (count>maxlength){
    maxlength = count;
    maxindex = j;
  }

  }

int endpoint = (height-1)*width +maxindex;
while (endpoint!=0){
  if ((parent[endpoint]-endpoint)==-1)
  path.push_back(0);
  else if ((parent[endpoint]-endpoint)==1)
  path.push_back(2);
  else if((parent[endpoint]-endpoint)==width)
  path.push_back(3);
  else if((parent[endpoint]-endpoint)==(-1*width) )
  path.push_back(1);

  endpoint= parent[endpoint];
}

 reverse(path.begin(),path.end());

  return path;
}
vector<int> SquareMaze::solveMaze (){
  std::cout << width << std::endl;
   return solveMazehelper(width, height);


}

PNG * 	SquareMaze::drawMaze () const{

  PNG* godbless = new PNG(10*width+1, 10*height+1);
  for (int i=10; i<10*width; i++){
    godbless->getPixel(i,0)-> h=0;
      godbless->getPixel(i,0)-> s=0;
        godbless->getPixel(i,0)-> l=0;
          godbless->getPixel(i,0)-> a=0;
  }
  for (int i=0;i<10*height; i++){
    godbless->getPixel(0,i)->h=0;
    godbless->getPixel(0,i)->s=0;
    godbless->getPixel(0,i)->l=0;
    godbless->getPixel(0,i)->a=0;
  }

  for (int y=0;y<height;y++){
    for (int x=0;x<width;x++){
      if (rightwall[y*width+x]==true){
        for(int k=0; k<=10;k++){
          godbless->getPixel((x+1)*10,y*10+k)->h=0;
          godbless->getPixel((x+1)*10,y*10+k)->s=0;
          godbless->getPixel((x+1)*10,y*10+k)->l=0;
          godbless->getPixel((x+1)*10,y*10+k)->a=0;
        }
      }
      if (downwall[y*width+x]==true){
        for(int k=0; k<=10;k++){
          godbless->getPixel(x*10+k,(y+1)*10)->h=0;
          godbless->getPixel(x*10+k,(y+1)*10)->s=0;
          godbless->getPixel(x*10+k,(y+1)*10)->l=0;
          godbless->getPixel(x*10+k,(y+1)*10)->a=0;
        }
      }
    }
  }

  return godbless;

}

PNG * SquareMaze::drawMazeWithSolution (){
  PNG * solved = new PNG(10,10);
  return solved;
}
