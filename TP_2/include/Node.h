#ifndef NODE_H
#define NODE_H

using namespace std;

template<class T> class Node { // Clase nodo
    public:
        T info;
    	Node* der;
		Node* izq;
};

#endif 