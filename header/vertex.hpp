#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <string>
#include <list> 
using namespace std;

struct Vertex 
{
    // level of jug A 
    int A_level; 

    // level of jug B
    int B_level;

    // cost of the action taken
    int edge_weight;                
    
    // type of the action taken
    string str;                     
    
    // set to infinity for Dijkstra's shortest path  algorithm 
    int distance = 0xFFFF;

    // set to nullptr for Dijkstra's shortest path algorithm        
    Vertex* predecessor = nullptr;

    // list of all neighbor vertices   
    list<Vertex*> neighbor;         
  
    // inline struct Vertex Constructor 
    Vertex(int A_level, int B_level, int edge_weight, string str)
    : A_level(A_level), B_level(B_level), edge_weight(edge_weight), str(str){}
};

#endif  // __VERTEX_HPP__