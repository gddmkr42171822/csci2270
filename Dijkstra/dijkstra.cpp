/*
   dijkstra.cpp

   ------------------------------------------------------------

   A reprise of the 'graph.cpp' file, but modified for doing
   Dijkstra's algorithm.  All the graphs in this assignment are DAGs,
   though be aware that Dijkstra's does not require this. Only
   implement the parts you really need!

   You are responsible for implementing:

   Graph::isDAG(),

   Graph::dijkstra(Node*), and

   Graph::dijkstra(Node*, Node*).

   You will likely need to write some helper functions to babysit your
   Tree* and priority queue (or pq substitute). How you do this is up
   to you!

   ------------------------------------------------------------


   Your Name:

   Your Collaborators:

 */

#include "dijkstra.hpp"

using namespace std;

void vect_sort(vector<Node*> vect_nodes);

Graph::Graph() {
  // graphs are undirected by default
  directed = false;
}

Graph::~Graph() {

}

vector<Node*> Graph::getNodes() {
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  return edges;
}

int Graph::getClock() {
  return clock;
}

void Graph::addNode(Node& n) {
  nodes.push_back(&n);
}

void Graph::addEdge(Edge& e) {
  edges.push_back(&e);
}
 
void Graph::removeNode(Node& n) {
  for (vector<Node*>::iterator it = nodes.begin();
       it != nodes.end(); 
       it++) {
    if (&n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(Edge& e) {
  for (vector<Edge*>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (&e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  directed = val;
}

bool Graph::isDirected() {
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node& n) {
  set<Edge*> ret;
  for (size_t i = 0; i < edges.size(); i++) {
    Edge* edge = edges[i];
    if (edge->getStart() == &n) {
      ret.insert(edge);
    }
    if (!directed && edge->getEnd() == &n) {
      ret.insert(edge);
    }
  }
  return ret;
}

void Graph::clear() {
 	clock = 0;
	vector<Node*>::iterator it = nodes.begin();
  for (;it != nodes.end(); it++) {
    Node* n = *it;
    n->clear();
  }
  vector<Edge*>::iterator eit = edges.begin();
  for (;eit != edges.end(); eit++) {
    Edge* e = *eit;
    e->setType(UNDISCOVERED_EDGE);
  }

}

void Graph::tick(string message) {
  // optional
}

void Graph::dfs(Node& start) {
   clock++; 
  start.setColor(GRAY, clock);
  set<Edge*> adj = getAdjacentEdges(start);
  set<Edge*>::iterator it = adj.begin();
  Edge* e;
  Node* other;
  int col, dt, ft, rk;
  for (; it != adj.end(); it++) {
    e = *it;
    if (e->getStart() == &start) {
      other = e->getEnd();
    } else {
      other = e->getStart();
    }
    other->getDiscoveryInformation(col, dt, ft, rk);
    if (col == WHITE) {
      other->setPredecessor(start);
      e->setType(TREE_EDGE);
      dfs(*other);
    } else if (col == GRAY) {
      e->setType(BACK_EDGE);
    } else if (col == BLACK) {
      bool ancest = other->isAncestor(start);
      if (ancest) {
	e->setType(FORWARD_EDGE);
      } else {
	e->setType(CROSS_EDGE);
      }
    }
  }
  clock = clock + 1;
  start.setColor(BLACK, clock);
}

void Graph::dfs(Node& start, Node& finish) {
  // implement if you think it is necessary
}

/**
 * Perform Dijkstra's algorithm for finding the minimum path length
 * from the given start node to all other reachable nodes in the
 * graph.
 *
 * Return the spanning tree that is rooted at the given start node,
 * with a path to all reachable nodes.
 **/
Tree* Graph::dijkstra(Node* start){
Tree* tree = new Tree;
tree->setRoot(start);
start->setPathDistance(0);
 vector<Node*> graph_nodes = getNodes();
 vector<Node*> vect_nodes;
 vector<Node*>::iterator it = graph_nodes.begin();
 for (; it!= graph_nodes.end(); it++)
   {
    vect_nodes.push_back(*it);
   }
 // vect_sort(vect_nodes);
 
 while (!vect_nodes.empty())
   {

     Node* current =*vect_nodes.begin();
     vect_nodes.erase(vect_nodes.begin());
     float path_distance = current->getPathDistance();
     if ( path_distance == INFINITY)
       {
	 return tree;
       }    
     set<Edge*> adj_edges = getAdjacentEdges(*current);
     set<Edge*>::iterator edge_it = adj_edges.begin();
     Edge* e;
     Node* other;
     for (; edge_it != adj_edges.end(); edge_it++)
       {
	 e = *edge_it;
	 if (e->getStart() == current) {
	   other = e->getEnd();
	 } else {
	   other = e->getStart();

	 }
	 for (unsigned int i = 0; i < vect_nodes.size(); i++)
	   {
	     if ( vect_nodes[i] == other)
	     {	 
	       continue;
		}
	   }
	 float d = path_distance + e->getWeight();
	 if ( d < other->getPathDistance())
	   {
	     other->setPathDistance(d);
	     tree->update(other, other->getPredecessor(), current);
	     other->setPredecessor(*current);
	     vect_nodes.push_back(other);
	     vect_sort(vect_nodes);
	   }
       }
   }
  return tree;
}

void vect_sort(vector<Node*> vect_nodes)
{
  Node* temp;
  unsigned int size = vect_nodes.size();
      for (unsigned int j = size-1; j > 0; j--)
	{
		for (unsigned int i = 0; i < size-1 ; i++)
		{
			if ( vect_nodes[i]->getPathDistance() > vect_nodes[i+1]->getPathDistance())
			{
				temp = vect_nodes[i];
				vect_nodes[i] = vect_nodes[i+1];
				vect_nodes[i+1] = temp;
			}
	     }
	     size--;
	 }
}



/**
 * Perform Dijkstra's algorithm like in the other version, but end
 * the algorithm when a definitive path length is found to the given
 * end node. Note that the end node might be unreachable.
 *
 * Return the spanning tree that was found during this search. Note
 * that when an answer is found for the path from start to end, the
 * algorithm stops, so the tree may be incomplete compared with what
 * is produced from the single-argument version of the dijkstra
 * function.
 **/
Tree* Graph::dijkstra(Node* start, Node* end) {
  /*Tree* tree = new Tree;
  tree->setRoot(start);
  start->setPathDistance(0);
  //vector<Node*> graph_nodes = getNodes();
  vector<Node*> vect_nodes;
  vect_nodes.push_back(start);
  //vector<Node*>::iterator it = graph_nodes.begin();
 //for (; it!= graph_nodes.end(); it++)
  // {
   // vect_nodes.push_back(*it);
   //}
 //vect_sort(vect_nodes);
 for ( unsigned int i = 1; i < nodes.size(); i++)
 {
	 vect_nodes.insert(vect_nodes.begin(), nodes[i]);
 }
 while (!vect_nodes.empty())
   {

     Node* current = vect_nodes.back();
     vect_nodes.pop_back();
     //float path_distance = current->getPathDistance();
     if ( current == end)
     {
		 return tree;
	 }
     //if ( path_distance == INFINITY)
      // {
	 //return tree;
      // }    
     set<Edge*> adj_edges = getAdjacentEdges(*current);
     set<Edge*>::iterator edge_it = adj_edges.begin();
     Edge* e;
     Node* other;
     for (; edge_it != adj_edges.end(); edge_it++)
       {
	 e = *edge_it;
	 if (e->getStart() == current) {
	   other = e->getEnd();
	 } else {
	   other = e->getStart();
	 }
	 for (unsigned int i = 0; i < vect_nodes.size(); i++)
	   {
	     if ( vect_nodes[i] == other)
	     {	 
	       continue;
		}
	   }
	 float d = current->getPathDistance() + e->getWeight();
	 if ( d < other->getPathDistance())
	   {
	     other->setPathDistance(d);
	     tree->update(other, other->getPredecessor(), current);
	     other->setPredecessor(*current);
	     vect_nodes.push_back(other);
	     vect_sort(vect_nodes);
	   }
	}
   }*/
   Tree* tree = new Tree;
 tree->setRoot(start);
 vector<Node*> vec;
 vec.push_back(start);
 for(unsigned int i = 1; i< nodes.size(); i++)
 {
	  vec.insert(vec.begin(), nodes[i]);
	  nodes[i]->setPathDistance(INT_MAX);
	  
 }
 start->setPathDistance(0);
 while(!vec.empty())
 {
	  Node* temp= vec.back();
	  vec.pop_back();
	    if(temp==end)
	  {
		  return tree;
		  }
	  set<Edge*> alledges = getAdjacentEdges(*temp);
	set<Edge*>::iterator it = alledges.begin();
	for (; it != alledges.end(); it++)
	{
		Edge* wed = *it;
		Node* other= wed->getEnd();
		float dist= temp->getPathDistance() + wed->getWeight();
		if(dist <other->getPathDistance())
		{
			other->setPathDistance(dist);
			tree->update(other,NULL,temp);
			other->setPredecessor(*temp);
			}
		
		
	}
	  
 }
   
  return tree;
}

/**
 * Is this graph a DAG or not? Return true if it is, false if not.
 **/
bool Graph::isDAG() {
 	clear();
	vector<Node*> graph_nodes = getNodes();
	dfs(**(graph_nodes.begin()));
	vector<Edge*> graph_edges = getEdges();
	vector<Edge*>::iterator it = graph_edges.begin();
	for (; it != graph_edges.end(); it++)
	{
		Edge* edge = *it;
		int type_edge = edge->getType();
		if ( type_edge == BACK_EDGE )
		{
			return false;
		}
	}
  return true;
}

Node::Node(string s) {
  data = s;
}

Node::~Node() {

}

string Node::getData() {
  return data;
}

void Node::setRank(int r) {
  rank = r;
}

void Node::clear() {
  	this->color = WHITE; 
	this->discovery_time = -1; 
	this->completion_time = -1;
	this->rank = -1;
	this->predecessor = NULL;
	this->path_distance = INFINITY;

}

void Node::setColor(int search_color, int time) {
  color = search_color;
  if (color == BLACK) {
    completion_time = time;
  } else if (color == GRAY) {
    discovery_time = time;
  } else if (color == WHITE) {
    
  } else {
    cout << "BZZZT you passed in the wrong color." << endl;
	}

}

void Node::getDiscoveryInformation(int& color, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
  color = this->color;
  disco_time = this->discovery_time;
  finish_time = completion_time;
  bfs_rank = rank;

}

bool Node::isAncestor(Node& other) {
  if (predecessor == NULL) {
    return false;
  }
  if (&other == predecessor) {
    return true;
  }
  return predecessor->isAncestor(other);

}

void Node::setPredecessor(Node& other) {
  predecessor = &other;
}

Node* Node::getPredecessor() {
  return predecessor;
}

float Node::getPathDistance() const {
  return path_distance;
}

void Node::setPathDistance(float pd) {
  path_distance = pd;
}

Edge::Edge(Node& n1, Node& n2) {
  a = &n1;
  b = &n2;
  weight = 1.0;
}

Edge::Edge(Node& n1, Node& n2, float w) {
  a = &n1;
  b = &n2;
  weight = w;
}

Edge::~Edge() {
}

float Edge::getWeight() {
  return weight;
}

void Edge::setWeight(float val) {
  weight = val;
}

Node* Edge::getStart() {
  return a;
}

Node* Edge::getEnd() {
  return b;
}

int Edge::getType() {
  return type;
}

void Edge::setType(int edge_type) {
  type = edge_type;
}

ostream &operator << (ostream& out, Graph graph) {
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (size_t i = 0; i < graph.nodes.size(); i++) {
    Node* n = graph.nodes[i];
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (size_t i=0; i < graph.edges.size(); i++) {
    Edge* e = graph.edges[i];
    out << *e << ", ";
  }
  out << "]";
  return out;
}

ostream &operator << (std::ostream& out, Node node) {
  out << node.data << " (";
  if (node.color == WHITE) {
    out << "White ";
  } else if (node.color == GRAY) {
    out << "Gray ";
  } else if (node.color == BLACK) {
    out << "Black ";
  } else {
    out << "??? ";
  }
  out << node.discovery_time << "/" << node.completion_time;
  out << " bfs_rank: " << node.rank;
  out << ")";
  return out;
}

ostream &operator << (std::ostream& out, Edge edge) {
  out << *edge.a << " -- " << *edge.b;
  out << " (";
  if (edge.type == UNDISCOVERED_EDGE) {
    out << "Undiscovered";
  } else if (edge.type == TREE_EDGE) {
    out << "Tree";
  } else if (edge.type == BACK_EDGE) {
    out << "Back";
  } else if (edge.type == FORWARD_EDGE) {
    out << "Forward";
  } else if (edge.type == CROSS_EDGE) {
    out << "Cross";
  }
  out << ")";
  return out;
}

/**
 * Make a new tree node for the given node.
 **/
TreeNode::TreeNode(Node* data) {
  this->node = data;
}

/**
 * Find a TreeNode that has the given data in this tree's member list,
 * or NULL if none are found.
 **/
TreeNode* Tree::find(Node* data) {
  vector<TreeNode*>::iterator tnit = members.begin();
  for (;tnit != members.end(); tnit++) {
    TreeNode* tn = *tnit;
    if (tn->node == data) {
      return tn;
    }
  }
  return NULL;
}

/**
 * Updates the tree such that (a) child is inserted into the tree if
 * necessary, (b) old_parent no longer refers to child, and (c)
 * new_parent does.
 **/
void Tree::update(Node* child, Node* old_parent, Node* new_parent) {
  TreeNode* child_tn = find(child);
  TreeNode* old_parent_tn = find(old_parent);
  TreeNode* new_parent_tn = find(new_parent);
  // if both the child and parent were present, remove the
  // now-outdated relationship.
  if (child_tn != NULL && old_parent_tn != NULL) {
    vector<TreeNode*>::iterator tnit;
    tnit = std::find(old_parent_tn->children.begin(), 
		old_parent_tn->children.end(), child_tn);
    if (tnit != old_parent_tn->children.end()) {
      old_parent_tn->children.erase(tnit);
    }
  }
  // if child_tn is null it means we don't yet know about the
  // child. We should add a new TreeNode to the members list.
  if (child_tn == NULL) {
    child_tn = new TreeNode(child);
    members.push_back(child_tn);
  }
  // if new_parent_tn is null, that's a straight up bug.
  if (new_parent_tn == NULL) {
    cout << "WARNING: New parent has no tree node in tree." << endl;
    cout << "         This is definitely a bug." << endl;
  } else {
    new_parent_tn->children.push_back(child_tn);
  }
}

/**
 * Sets the root node of the tree, clears the membership list, and
 * inserts the root into that membership list.
 **/
void Tree::setRoot(Node* n) {
  root = new TreeNode(n);
  members.clear();
  members.push_back(root);
}

/**
 * Gives you the root of the tree.
 **/
TreeNode* Tree::getRoot() {
  return root;
}

/**
 * Private member function implementation. Prints the tree with
 * multi-level output depending on where you are. This is recursive.
 **/
void Tree::print_tree(TreeNode* tn, int lvl) {
  // leave the cout statements in
  for (int i=0; i < lvl; i++) {
    cout << " . ";
  }
  cout << tn->node->getData() << " dist: " << tn->node->getPathDistance() << endl;
  for (size_t i = 0; i < tn->children.size(); i++) {
    print_tree(tn->children[i], lvl+1);
  }
}

/**
 * Prints the tree in a nice output form to standard output.
 **/
void Tree::print_tree() {
  TreeNode* cursor = root;
  print_tree(cursor, 0);
}
