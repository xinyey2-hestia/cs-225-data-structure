/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */


int GraphTools::findMinWeight(Graph& graph)
{

    /* Your code here! */

    for (Vertex v:graph.getVertices()){
      graph.setVertexLabel(v,"UNEXPLORED");
    }
    for (Edge e:graph.getEdges()){
      graph.setEdgeLabel(e.source, e.dest,"UNEXPLORED");
    }

    Vertex startpoint = graph.getStartingVertex();
    vector<Vertex> near = graph.getAdjacent(startpoint);
    Vertex min1 = startpoint;
    Vertex min2 = near[0];
    int currentsmall = graph.getEdgeWeight(startpoint,min2);

    queue <Vertex> q;
    graph.setVertexLabel(startpoint,"VISITED");
    q.push(startpoint);

    while(!q.empty()){
      Vertex v = q.front();
      q.pop();
      for (Vertex w: graph.getAdjacent(v)){
        if (graph.getVertexLabel(w)=="UNEXPLORED"){
          graph.setEdgeLabel(v,w,"DISCOVERY");
          graph.setVertexLabel(w,"VISITED");
          q.push(w);
          if (graph.getEdgeWeight(v,w)<currentsmall){
            currentsmall = graph.getEdgeWeight(v,w);
            min1 = v;
            min2 = w;
          }
        }
        else if(graph.getEdgeLabel(v,w)=="UNEXPLORED"){
          graph.setEdgeLabel(v,w,"CROSS");
          if (graph.getEdgeWeight(v,w)<currentsmall){
            currentsmall = graph.getEdgeWeight(v,w);
            min1 = v;
            min2 = w;
          }
        }
      }
    }

    graph.setEdgeLabel(min1,min2,"MIN");


    return currentsmall;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    unordered_map<Vertex, Vertex> Yvette;
    for (Vertex v:graph.getVertices()){
      graph.setVertexLabel(v,"UNEXPLORED");
    }
    for (Edge e:graph.getEdges()){
      graph.setEdgeLabel(e.source, e.dest,"UNEXPLORED");
    }
    queue <Vertex> q;
    graph.setVertexLabel(start,"VISITED");
    q.push(start);
    int count = 0; // layers
    int min  = 1000; // distance

    while(!q.empty()){
      Vertex v = q.front();
      q.pop();
      for (Vertex w: graph.getAdjacent(v)){
        if (graph.getVertexLabel(w)=="UNEXPLORED"){
          Yvette[w]=v;
          graph.setEdgeLabel(v,w,"DISCOVERY");
          graph.setVertexLabel(w,"VISITED");
          q.push(w);

        }
        else if(graph.getEdgeLabel(v,w)=="UNEXPLORED"){
          count++;
          graph.setEdgeLabel(v,w,"CROSS");

        }
      }
    }
    count = 0;
    while(end!=start){
      Vertex uplevel = Yvette[end];
      graph.setEdgeLabel(end,uplevel,"MINPATH");
      count++;
      end = uplevel;
    }



    return count;

}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
bool GraphTools::myfunction(Edge a, Edge b){
  return a.weight<b.weight;
}
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */

    unordered_map<Vertex, Vertex> Yvette;
    for (Vertex v:graph.getVertices()){
      graph.setVertexLabel(v,"UNEXPLORED");
    }
    for (Edge e:graph.getEdges()){
      graph.setEdgeLabel(e.source, e.dest,"UNEXPLORED");
    }

    DisjointSets forest;
    for (Vertex v:graph.getVertices()){
      forest.addelements(1);
    }

    vector<Edge> Q;
    for (Edge e:graph.getEdges()){
      Q.push_back(e);
    }
    std::sort(Q.begin(),Q.end(), myfunction);

    int edgelooped =0;

    while (edgelooped<(graph.getVertices().size()-1)){
      Vertex u = Q.front().source;
      Vertex v = Q.front().dest;
      Q.erase(Q.begin());
      if(forest.find(u)!=forest.find(v)){
        graph.setEdgeLabel(u,v,"MST");
        forest.setunion(forest.find(u),forest.find(v));
        edgelooped++;
      }
    }
}
