#include "../header/jug.hpp"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
    this->Ca   = Ca  ;   // capacity of the jug A
    this->Cb   = Cb  ;   // capacity of the jug B 
    this->N    = N   ;   // N gallons in B and 0 gallons in A is the solution
    this->cfA  = cfA ;   // is the cost to fill A
    this->cfB  = cfB ;   // is the cost to fill B
    this->ceA  = ceA ;   // is the cost to empty A
    this->ceB  = ceB ;   // is the cost to empty B
    this->cpAB = cpAB;   // is the cost to pour A to B
    this->cpBA = cpBA;   // is the cost to pour B to A

    fA  = "fill A"  ; 
    fB  = "fill B"  ;
    eA  = "empty A" ;
    eB  = "empty B" ; 
    pAB = "pour A B";
    pBA = "pour B A";

    // add the first vertex with empty jugs to the vector of vertex pointer  
    vertices.push_back(new Vertex(0,0,0, ""));    
}

Jug::~Jug(){
    for(unsigned i = 0; i < vertices.size(); ++i) {
        vertices.at(i)->neighbor.clear();
    }
    vertices.erase(vertices.begin(), vertices.end()); 
}

int Jug::solve(string &solution) {
    solution = "";    // empty string 

    // Invalid inputs. solution set to empty string
    if ( cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 
        || cpAB < 0 || cpBA < 0 || ( Ca <= 0 || Ca > Cb ) 
        || Cb < N  || Cb > 1000 ) {
        return -1;
    }   

    // build the graph and return the null if no solution, otherwise return the solution vertex
    Vertex* solution_vertex = this->build_graph(); 
    
    // Inputs are valid but a solution does not exist. solution set to empty string.
    if(!solution_vertex) {
        return 0;
    }
    
    // Solution is found and stores solution steps in solution string.
    solution = DijkstraShortestPath(this->vertices, solution_vertex); 
    return 1;
}

void Jug::fill_JugA(Vertex* pv) {
  // if A is not full take the action 
  if(pv->A_level < Ca) {
    // create a new vertex as the parent then update it with the action taken 
    Vertex* v = new Vertex(Ca, pv->B_level, cfA, fA);
    this->set_Vertex(pv, v);
  }
}

void Jug::fill_JugB(Vertex* pv) {
    // if B is not full take the action 
    if(pv->B_level < Cb) {
    // create a new vertex as the parent then update it with the action taken 
    Vertex* v = new Vertex(pv->A_level, Cb, cfB, fB);
    this->set_Vertex(pv, v);
  }
}

void Jug::empty_JugA(Vertex* pv) {
    // if A is not empty take the action 
    if(pv->A_level > 0) {
        // create a new vertex with the action taken 
        Vertex* v = new Vertex(0, pv->B_level, ceA, eA);
        this->set_Vertex(pv, v);
    }
}

void Jug::empty_JugB(Vertex* pv) {
    // if B is not empty take the action 
    if(pv->B_level > 0) {
        // create a new vertex with the action taken 
        Vertex* v = new Vertex(pv->A_level, 0, ceB, eB);
        this->set_Vertex(pv, v);
    }
}

void Jug::pour_AtoB(Vertex* pv) {
    // if A is empty or B is full dismiss action 
    if(( pv->A_level == 0 ) || ( pv->B_level == Cb )) {
        return; 
    }

    int a_new_level, b_new_level;

    // if the combined level of both jugs is less then capacity of B
    if(pv->A_level + pv->B_level < Cb) {
        a_new_level = 0;
        b_new_level = pv->B_level + pv->A_level;
    } else {
        a_new_level = pv->A_level - (Cb - pv->B_level);
        b_new_level = Cb;    
    }
    // create a new vertex with the action taken 
    Vertex* v = new Vertex(a_new_level, b_new_level, cpAB, pAB);
    
    this->set_Vertex(pv, v);
}

void Jug::pour_BtoA(Vertex* pv) {
    // if B is empty or A is full dismiss action 
    if(( pv->B_level == 0 ) || ( pv->A_level == Ca)) {
        return; 
    }

    int a_new_level, b_new_level;

    // if the combined level of both jugs is less then capacity of A
    if(pv->A_level + pv->B_level < Ca) {
        a_new_level = pv->A_level + pv->B_level;
        b_new_level = 0;
    } else {
        a_new_level = Ca;
        b_new_level = pv->B_level - (Ca - pv->A_level);  
    }
    // create a new vertex with the action taken 
    Vertex* v = new Vertex(a_new_level, b_new_level, cpBA, pBA);
    
    this->set_Vertex(pv, v);
}

Vertex* Jug::build_graph() {
    // After max number of actions, consider a solution does not exist. 
    unsigned max_vertices = 200000;
    
    // Built the graph 
    for(unsigned i = 0; i < this->vertices.size() ; ++i) {
        // Go through all 6 possible actions and check for solution
        fill_JugA( this->vertices.at(i));     // fill A 
        fill_JugB( this->vertices.at(i));     // fill B 
        empty_JugA(this->vertices.at(i));     // empty A 
        empty_JugB(this->vertices.at(i));     // empty B 
        pour_AtoB( this->vertices.at(i));     // pour A B 
        pour_BtoA( this->vertices.at(i));     // pour B A 
        
        if( isSolution(this->vertices.back()) ) { 
            return this->vertices.back();
        }

        // Solution does not exist
        if(i > max_vertices) {
            return nullptr;
        }
    }
    return nullptr;
}
 
bool Jug::exists(Vertex* v) {
    for (unsigned i = 0 ; i < this->vertices.size() ; ++i) {
        if(( v->A_level == this->vertices.at(i)->A_level) 
            && ( v->B_level == this->vertices.at(i)->B_level)) {
            return true;
        }
    }
    return false;
}

bool Jug::isSolution(Vertex* v) {
    if(( v->A_level == 0 ) && ( v->B_level == this->N )) {
        return true;
    } else {
        return false ;
    } 
} 
	
void Jug::set_Vertex(Vertex* pv, Vertex* v) {
    // add the vertex v to the parent's neighbor list
    pv->neighbor.push_back(v); 

    // add the vertex to vertices vector   
    this->vertices.push_back(v);
} 

string Jug::DijkstraShortestPath(vector<Vertex*> &vertices ,Vertex* v) {
    
  Vertex* currV ;               // create a current Vertex for while loop 
  vertices.at(0)->distance = 0; // set the first vertex distance to 0
  int path_distance;            // holds distance for diff paths  
  string solution = "";

  // visit all vertices in the graph
  for(unsigned vertex = 0; vertex < this->vertices.size(); vertex++) {
    // visit vertices with min distance from the head vertex first
    currV = this->vertices.at(vertex);   
    
    // update distance b/w the current Vertex and its neighbors
    for (auto i = currV->neighbor.begin(); i != currV->neighbor.end(); ++i) { 
         
      path_distance = currV->distance + i.operator*()->edge_weight;
      
      if(path_distance < i.operator*()->distance) {
        i.operator*()->distance = path_distance;    // update shortest distance 
        i.operator*()->predecessor = currV;         // update predecessor
      } 
    }

    if( isSolution(currV) && (currV->distance < v->distance)) {
      v = currV;
    } 
  }

  // Hold the vertices on the shortest path 
  stack<Vertex* > stack;
  currV = v; 
  while( currV->predecessor ) {
    stack.push(currV);
    currV = currV->predecessor; 
  } 

  // Go though the shortest path  
  while(!stack.empty()) {
    solution += stack.top()->str;
    solution += '\n';
    stack.pop();
  }

  solution += "success ";
  solution += to_string(v->distance);

  return solution;    
}
