#ifndef STRUCTS_H
#define STRUCTS_H

#include <sstream> // strings
#include "Node.h"

using namespace std;

typedef struct { // Struct obj
    string type;
    string data;
    int hierarchy;
} obj;

typedef struct { // Struct objOrd
    Node<obj>* ind;
    string value;
} objOrd;


#endif