#ifndef pq_h
#define pq_h

#include <string>
#include "pq_struct.h"

using namespace std;

void insert(pq* &queue, string &text, float priority);

string remove(pq* &queue);

string peek(pq* &queue);

pq* init_priority_queue();

#endif
