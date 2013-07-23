// 
// pq_struct.h
// 
// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
//
// You will turn in this file and pq.cpp to retrograde.
//
// Your Name:Robert Werthman

#ifndef pq_struct_h
#define pq_struct_h
#include <string>
using namespace std;

struct pq {
  float priority;
  string text;
  pq* next;
  pq* parent;
};

#endif
