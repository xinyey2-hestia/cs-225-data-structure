#include "graph.h"
#include "dset.h"
#include <queue>
#include <vector>
using namespace std;

void BFS(Graph g){
  for(auto & i : g.getVertices()){
    g.setVertexLabel(i,"UE");
  }
  for(auto & i : g.getEdges()){
    g.setEdgeLabel(i,"UE");
  }
  for(auto & i : g.getVertices()){
    if(g.getVertexLabel(i) == "UE") BFS(g,i);
  }
}
void BFS(Graph g, Vertex v){
  queue q;
  g.setVertexLabel(v,"V");
  q.push(v);
  while(!q.empty()){
    Vertex v = q.front();
    q.pop();
    for(auto & i : g.getAdjacent(v)){
      if(g.getVertexLabel(i) == "UE"){
        g.setEdgeLabel(i,v,"D");
        q.push(i);
      }else if(g.getEdgeLabel(i,v) == "UE"){
        g.setEdgeLabel(i,v,"C");
      }
    }
  }
}

void DFS(Graph g){
  for(auto & i : g.getVertices()){
    g.setVertexLabel(i,"UE");
  }
  for(auto & i : g.getEdges()){
    g.setEdgeLabel(i,"UE");
  }
  for(auto & i : g.getVertices()){
    if(g.getVertexLabel(i) == "UE") DFS(g,i);
  }
}
void DFS(Graph g, Vertex v){
  g.setVertexLabel(v,"V");
  for(auto & i : g.getAdjacent(v)){
    if(g.getVertexLabel(i) == "UE"){
      g.setEdgeLabel(i,v,"D");
      DFS(g,i);
    }else if(g.getEdgeLabel(i,v) == "UE"){
      g.setEdgeLabel(i,v,"B");
    }
  }
}

void KruskalMST(Graph g){
  vector<Edge> edges = g.getEdges();
  std::sort(edges.begin(),edges.end());
  for(auto & i : g.getVertices()){
    g.setVertexLabel(i,"UE");
  }
  for(auto & i : g.getEdges()){
    g.setEdgeLabel(i.source,i.dest,"UE");
  }
  g.setVertexLabel(edges[0].source,"V");
  bool flag = true;
  unsigned i = 0;
  while(flag){
    if(g.getVertexLabel(edges[i].dest) == "UE"){
      g.setVertexLabel(edges[i].dest,"V");
      g.setEdgeLabel(edges[i].source,edges[i].dest,"MST");
    }
    i ++;
    flag = false;
    for(auto & i : g.getVertices()){
      if(g.getVertexLabel(i) == "UE"){
        flag = true;
      }
    }
  }
}

void PrimMST(Graph g, Vertex start, Vertex end){
  vector<Edge> e = g.getEdges();
  std::sort(e.begin(),e.end());
  Vertex start = e[0].source;
  for(auto & i : g.getVertices()){
    g.setVertexLabel(i,"B");
  }
  vector<int> d;
  vector<Vertex> p;
  d.resize(g.getVertices().size(),99999);
  p.resize(g.getVertices().size(),99999);
  d[start] = 0;
  vector<Vertex> q = g.getVertices();
  while(!q.empty()){
    int curr = 999999;
    unsigned idx = 0;
    for(unsigned j = 0; j < q.size() ; j++){
      if(d[q[j]] < curr){
        curr = d[q[j]];
        idx = j;
      }
    }
    Vertex m = q[idx];
    g.setVertexLabel(m,"A");
    for(auto & j : g.getAdjacent(m)){
      if(g.getVertexLabel(j) == "B"){
        if(g.getEdgeWeight(m,j) < d[j]){
          d[j] = g.getEdgeWeight(m,j);
          p[j] = m;
        }
      }
    }
    std::swap(q[idx],q[q.size()-1]);
    q.pop_back();
  }
  for(unsigned i = 0 ; i < p.size() ; i++){
    if(p[i] != 99999)
      g.setEdgeLabel(i,p[i],"MST");
  }
}

int Dis(Graph g, Vertex start, Vertex end){
  for(auto & i : g.getVertices()){
    g.setVertexLabel(i,"B");
  }
  vector<int> d;
  vector<Vertex> p;
  d.resize(g.getVertices().size(),99999);
  p.resize(g.getVertices().size(),99999);
  d[start] = 0;
  vector<Vertex> q = g.getVertices();
  while(!q.empty()){
    int curr = 999999;
    unsigned idx = 0;
    for(unsigned j = 0; j < q.size() ; j++){
      if(d[q[j]] < curr){
        curr = d[q[j]];
        idx = j;
      }
    }
    Vertex m = q[idx];
    g.setVertexLabel(m,"A");
    for(auto & j : g.getAdjacent(m)){
      if(g.getVertexLabel(j) == "B"){
        if(1 + d[m] < d[j]){
          d[j] = 1 + d[m];
          p[j] = m;
        }
      }
    }
    std::swap(q[idx],q[q.size()-1]);
    q.pop_back();
  }
  Vertex i = end;
  while(p[i] != 99999){
    g.setEdgeLabel(i,p[i],"MINPATH");
    i = p[i];
  }
  return d[end];
}




 bool BFS(graph g){
   for (auto &i:g.getVertices()){
     g.setVertexLabel(i, "uncolor");
   }
   vector <vertex> V =g.getVertices();
   queue q;
   g.setVertexLabel(V[0],"0");
   q.push(V[0]);
   while (!q.empty()){
     Vertex v = q.front();
     q.pop();
     for (auto &i:g.getAdjacent(v)){
       string laber = v.getVertexLabel();
       if (adj[i].getVertexLabel()==label){
         return false;
       }
       if (g.getVertexLabel(i)=="uncolor"){
         string nlaber = "1";
         if (label==nlabel){
           nlabel = "0";
         }
         g.setVertexLabel(adj[i],nlabel);
         q.push(adj[i]);
       }

     }
   }
   return true;
 }








 void GraphTools::shortest_path(Graph &graph, Vertex start, Vertex end){
     vector<Vertex> vec = graph.getVertices();
     vector<int> dis;
     vector<size_t> pre;
     vector<bool> visited;
     for(size_t i=0;i<vec.size();i++){
         dis.push_back(INT_MAX);
         pre.push_back(99);
         visited.push_back(false);
     }

     dis[start] = 0;
     size_t count = 0;
     while(count<vec.size()){
         size_t curr = 0;
         int currDis = INT_MAX;
         for(size_t i=0;i<vec.size();i++){
             if(dis[i] < currDis && visited[i] == false){
                 curr = i;
                 currDis = dis[i];
             }
         }

         visited[curr] = true;
         vector<Vertex> adj = graph.getAdjacent(curr);
         for(size_t i=0;i<adj.size();i++){
             if((graph.getEdgeWeight(curr,adj[i])+currDis) < dis[adj[i]]){
                 dis[adj[i]] = graph.getEdgeWeight(curr,adj[i]) + currDis;
                 pre[adj[i]] = curr;
             }
         }

         count = count+1;
     }

     size_t curr = end;
     while(curr != 99){
         size_t next = pre[curr];
         if(next != 99){graph.setEdgeLabel(curr, next, "MST");}
         curr = next;
     }

 }


















 /**
  * @file graph_tools.cpp
  * This is where you will implement several functions that operate on graphs.
  * Be sure to thoroughly read the comments above each function, as they give
  *  hints and instructions on how to solve the problems.
  */

 #include "graph_tools.h"
 #include <iostream>
 #include <queue>
 #include "edge.h"
 #include <vector>
 #include <utility>
 #include <climits>
 #include "graph.h"
 #include <unordered_map>
 #include "dsets.h"
 #include <algorithm>
 #include <map>
 using namespace std;
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
     vector<Vertex> ver = graph.getVertices();
     unordered_map<Vertex, bool> visited;
     for(size_t i=0;i<ver.size();i++){
       visited.insert(std::pair<Vertex, bool>(ver[i], false));
     }
     queue<Vertex> BFS;
     Vertex start = graph.getStartingVertex();
     BFS.push(start);
     visited.find(start)->second = true;
     pair<Vertex, Vertex> minPair;
     int minWeight = INT_MAX;
     while(!BFS.empty()){
       Vertex curr = BFS.front();
       BFS.pop();
       vector<Vertex> adj = graph.getAdjacent(curr);
       for(size_t i=0;i<adj.size();i++){
         if(visited.find(adj[i])->second == false){
             visited.find(adj[i])->second = true;
             graph.setEdgeLabel(curr, adj[i], "DISCOVERY");
             BFS.push(adj[i]);
         }
         else if(graph.getEdgeLabel(curr, adj[i]) != "DISCOVERY"){
           graph.setEdgeLabel(curr, adj[i], "CROSS");
         }
         if(graph.getEdgeWeight(curr, adj[i])<minWeight){
           minPair = make_pair(curr, adj[i]);
           minWeight = graph.getEdgeWeight(curr, adj[i]);
         }
       }
     }

     graph.setEdgeLabel(minPair.first, minPair.second, "MIN");
     return graph.getEdgeWeight(minPair.first, minPair.second);
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
     vector<Vertex> ver = graph.getVertices();
     unordered_map<Vertex, bool> visited;
     unordered_map<Vertex, Vertex> travel;
     for(size_t i=0;i<ver.size();i++){
       visited.insert(std::pair<Vertex, bool>(ver[i], false));
     }
     queue<Vertex> BFS;
     BFS.push(start);
     visited[start] = true;
     while(!BFS.empty()){
       Vertex curr = BFS.front();
       BFS.pop();
       vector<Vertex> adj = graph.getAdjacent(curr);
       for(size_t i=0;i<adj.size();i++){
         if(visited[adj[i]] == false){
           visited[adj[i]] = true;
           graph.setEdgeLabel(curr, adj[i], "DISCOVERY");
           BFS.push(adj[i]);
           travel[adj[i]] = curr;
         }
         else if(graph.getEdgeLabel(curr, adj[i]) != "DISCOVERY"){
           graph.setEdgeLabel(curr, adj[i], "CROSS");
         }
       }
     }

     Vertex front = travel[end];
     graph.setEdgeLabel(end, front, "MINPATH");
     cout<<"get here"<<endl;
     int count = 1;
     while(front != start){
       Vertex temp = travel[front];
       graph.setEdgeLabel(front, temp, "MINPATH");
       count = count+1;
       front = temp;
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
 void GraphTools::findMST(Graph& graph)
 {
     /* Your code here! */
     vector<Edge> vec = graph.getEdges();
     vector<Vertex> vec2 = graph.getVertices();
     vector<int> weightVec;
     unordered_map<int, vector<Edge>> myEdges;
     DisjointSets connected;
     for(size_t i=0; i<vec.size();i++){
       weightVec.push_back(vec[i].weight);
       (myEdges[vec[i].weight]).push_back(vec[i]);
     }
     for(size_t i=0; i<vec2.size();i++){
       connected.addelements((int)vec2[i]);
     }
     std::sort(weightVec.begin(), weightVec.end());
     for(size_t i=0;i<weightVec.size();i++){
       Edge curr = (myEdges[weightVec[i]]).back();
       (myEdges[weightVec[i]]).pop_back();
       if(connected.find((int)curr.source)!=connected.find((int)curr.dest)){
         graph.setEdgeLabel(curr.source, curr.dest, "MST");
         connected.setunion((int)curr.source, (int)curr.dest);
       }
     }

 }

 void GraphTools::DFS(Graph& graph){
   Vertex start = graph.getStartingVertex();
   vector<Vertex> vec = graph.getVertices();
   map<size_t, int> visited;
   for(size_t i=0;i<vec.size();i++){
     visited[vec[i]] = 0;
   }
   DFS_Helper(graph, start, visited);
 }

 void GraphTools::DFS_Helper(Graph &graph, Vertex v, map<size_t, int> &visited){
   visited[v] = 1;
   vector<Vertex> vec= graph.getAdjacent(v);
   for(size_t i=0;i<vec.size();i++){
     Vertex curr = vec[i];
     if(visited[curr] == 0){
       graph.setEdgeLabel(v, curr, "DISCOVERY");
       DFS_Helper(graph, curr, visited);
     }
     else if(graph.getEdgeLabel(curr, v) != "DISCOVERY"){
       graph.setEdgeLabel(curr, v, "CROSS");
     }
   }
 }

 void GraphTools::shortest_path(Graph &graph, Vertex start, Vertex end){
   vector<Vertex> vec = graph.getVertices();
   vector<int> dis;
   vector<size_t> pre;
   vector<bool> visited;
   for(size_t i=0;i<vec.size();i++){
     dis.push_back(INT_MAX);
     pre.push_back(99);
     visited.push_back(false);
   }

   dis[start] = 0;
   size_t count = 0;
   while(count<vec.size()){
     size_t curr = 0;
     int currDis = INT_MAX;
     for(size_t i=0;i<vec.size();i++){
       if(dis[i] < currDis && visited[i] == false){
         curr = i;
         currDis = dis[i];
       }
     }

     visited[curr] = true;
     vector<Vertex> adj = graph.getAdjacent(curr);
     for(size_t i=0;i<adj.size();i++){
       if((graph.getEdgeWeight(curr,adj[i])+currDis) < dis[adj[i]]){
         dis[adj[i]] = graph.getEdgeWeight(curr,adj[i]) + currDis;
         pre[adj[i]] = curr;
       }
     }

     count = count+1;
   }

   size_t curr = end;
   while(curr != 99){
     size_t next = pre[curr];
     if(next != 99){graph.setEdgeLabel(curr, next, "MST");}
     curr = next;
   }

 }


 void GraphTools::travel(Graph &graph, Vertex start, int n){
   vector<Vertex> vec = graph.getVertices();
   map<size_t, int> visited;
   for(size_t i=0;i<vec.size();i++){
     visited[vec[i]] = 0;
   }

   vector<size_t> path;
   bool yes = BFST(graph, start, 0, path, n, visited, start);
   cout<<"yse"<<endl;
   path.push_back(start);
   cout<<"yes2"<<endl;
   for(size_t i=0;i<path.size()-1;i++){
     //graph.setEdgeLabel(path[i], path[i+1], "MST");
     cout<<graph.getVertexLabel(path[i])<<endl;
   }
 }

 bool GraphTools::BFST(Graph &graph, Vertex v, int turns, vector<size_t> &path, int n , map<size_t, int> &visited, Vertex start){
   visited[v] = 1;
   vector<Vertex> adj = graph.getAdjacent(v);
   for(size_t i=0; i<adj.size();i++){
     if(turns == n && adj[i] == start){
       path.push_back(v);
       cout<<"get in1"<<endl;
       return true;
     }
   }
   cout<<graph.getVertexLabel(v)<<endl;
   for(size_t i=0; i<adj.size();i++){
     if(visited[adj[i]] == 0){
       bool yes = BFST(graph, adj[i],  turns+1, path, n , visited, start);
       if(yes == true){path.push_back(v);return true;}
     }
   }

   visited[v] = 0;
   return false;
 }
