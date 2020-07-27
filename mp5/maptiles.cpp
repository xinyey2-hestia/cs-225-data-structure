/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */

     MosaicCanvas* yvette = new MosaicCanvas(theSource.getRows(),theSource.getColumns()); // creates a new dynamically allocated MosaicCanvas, with the same number of rows and columns as the SourceImage
     vector<Point<3>> points;
     for (size_t i=0; i<theTiles.size(); i++){          // create a point vector for all tileimages in thetiles
       HSLAPixel temp = theTiles[i].getAverageColor();
       //double param[3];
       //param[0]= temp.h/360;
       //param[1]=temp.s;
       //param[2]= temp.l;
       Point<3> cur(temp.h/360,temp.s,temp.l);
       points.push_back(cur);
     }

     KDTree <3> lovetree(points);             // build the KD TREE!!!

     map <Point<3>, int> indexMap;
     for(size_t i = 0; i < points.size(); i++) {    // a map for future turn pixel to tileimage
		indexMap[points[i]] = i;
	}
     for (int i=0; i<theSource.getRows(); i++){
       for (int j=0; j<theSource.getColumns(); j++){
         HSLAPixel original = theSource.getRegionColor(i,j);   // get the original color to find neighbours one by one
         double param[3];
         //param[0]= original.h/360;
         //param[1]=original.s;
        // param[2]= original.l;
        // Point<3> cur(param);
         Point<3> needfind(original.h/360,original.s, original.l);         // for everypixerl in sourceimage find closest point in the KD tree
         Point<3> result = lovetree.findNearestNeighbor(needfind);        // map the corresponding tileimage
         int index =indexMap[result];
         yvette->setTile(i,j,theTiles[index]);
       }
     }

    return yvette;
}
