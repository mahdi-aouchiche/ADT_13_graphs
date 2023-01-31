#ifndef __JUG_HPP__
#define __JUG_HPP__

#include <iostream> 
#include <vector>
#include <stack>
#include "vertex.hpp"
using namespace std; 
 
class Jug 
{
  private:
    // Data 
    int Ca  ; // capacity of the jug A
    int Cb  ; // capacity of the jug B
    int cfA ; // is the cost to fill A
    int cfB ; // is the cost to fill B
    int ceA ; // is the cost to empty A
    int ceB ; // is the cost to empty B
    int cpAB; // is the cost to pour A to B
    int cpBA; // is the cost to pour B to A
    int N   ; // goal to have N gallons in jug B 

    // vector of Vertices pointer to hold the graph vertices 
    vector<Vertex* > vertices;

    // Strings representing the action taken from each edge
    string fA  ; 
    string fB  ;
    string eA  ;
    string eB  ; 
    string pAB ;
    string pBA ;
  
  public:
    // Constructor
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);

    // Destructor
    ~Jug();

    /*
      solve is used to check input and find the solution if one exists
      returns -1 if invalid inputs. solution set to empty string.
      returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
      returns 1 if solution is found and stores solution steps in solution string.
    */
    int solve(string &solution);

  private:
    // Functions to update vertex for the possible actions
    void fill_JugA(Vertex*  );
    void fill_JugB(Vertex*  );
    void empty_JugA(Vertex* );
    void empty_JugB(Vertex* );
    void pour_AtoB(Vertex*  );
    void pour_BtoA(Vertex*  );

    // Build the graph 
    Vertex* build_graph();

    // Checks if the new created vertex by taking an action exists or not 
    bool exists(Vertex* ); 

    // Checks each Vertex if it is the solution 
    bool isSolution(Vertex* ); 
	
    // add vertex V to the graph or to the neighbor's list 
    void set_Vertex(Vertex* , Vertex* );  

    // returns the shortest path in a string
    string DijkstraShortestPath(vector<Vertex*> & ,Vertex* );   
};

#endif  // __JUG_HPP__