#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "Structs.h"

using namespace std;

template<class T> class Tree { // Clase arbol
    private:
        Node<T>* root; 
        void searchTree(T x, Node<T>*& n); // Creates the search Tree
        void rid(Node<T>* aux); // Recorrido del arbol en preorden (raiz, izquierdo, derecho)
        void idr(Node<T>* aux); // Recorrido postorden (izquierdo, derecho, raiz)
        void ird(Node<T>* aux); // Recorrido inorden (izquierdo, raiz, derecho)
    public:
        Tree() {root = NULL;}; // Tree declaration
        ~Tree() {}; // Destructor
        void createSearchTree(T x); // Creates the search Tree
        void showTree() {rid(root);} // Mostramos el arbol en forma preorden (Raiz, izquierdo, derecho)
		void vectorData(string key, vector<objOrd>* vec, Node<T>* n); // Vector con datos de cada laureado del json
        Node<T>* getRoot() {return root;}; // returns the root of the Tree (Node)
};

template<class T> void Tree<T>::createSearchTree(T x) {
    searchTree(x, root);
}

template<class T> void Tree<T>::searchTree(T x, Node<T>*& n) {
    // La función searchTree() es un método que se utiliza para insertar elementos en un árbol binario 
	// La función toma dos argumentos: x, que es el elemento que se desea insertar en el árbol, y n, que es un puntero al nodo actual en el que se encuentra la función.
	// El primer paso que hace la función es comprobar si el nodo n es NULL (es decir, si el nodo no existe). 
	// Si es así, la función crea un nuevo nodo y le asigna el elemento x que se desea insertar. 
	// El nodo también tiene dos punteros, izq y der, que apuntan a los nodos hijo izquierdo y derecho, respectivamente. 
	// En este caso, como el nodo es nuevo, los punteros se inicializan en NULL.
	// Si el nodo n ya existe, la función comprueba si el elemento x que se desea insertar ya está en el árbol, utilizando la función isEqual(). 
	// Si el elemento ya existe, la función no hace nada y finaliza. Si el elemento no existe, la función continúa y determina en qué nodo se insertará el elemento.
	// La función utiliza el "tipo" y la "jerarquía" del elemento x y del nodo actual n para decidir dónde insertar el elemento. 
	// La función tiene una serie de condicionales que comprueban diferentes combinaciones de tipos y jerarquías, y en cada caso inserta el 
	// elemento en un nodo hijo izquierdo o derecho. Por ejemplo, si el tipo del nodo actual es "Array" y el tipo del elemento x es "Index", 
	// entonces la función insertará el elemento en el nodo hijo izquierdo.
	// La función utiliza recursión para seguir insertando el elemento en el árbol. 
	// Una vez que se ha insertado el elemento en un nodo hijo, la función llama a sí misma con el elemento y el nodo hijo como argumentos, 
	// y continúa insertando el elemento en el árbol de esta manera hasta que encuentra un nodo donde el elemento ya exista o donde no sea posible insertarlo.

    // el "*&" es para pasaje por referencia (todo lo q le "haga" a <n>,
	// en realidad se lo estoy haciendo al parámetro que le paso, en este caso, <root>)
    
    if (n == NULL) {
        n = new Node<T>;
        n->info = x;
        n->der = NULL;
        n->izq = NULL;
    }
    if (!isEqual(x, n->info)) {
        if ((n->info.type == "Array") && (x.type == "Index")) {
			searchTree(x, n->izq);
        }
        if ((n->info.type == "Index") && (x.type == "Key")) {
            if (n->der == NULL) {
                searchTree(x, n->izq); 	
            } else {
                searchTree(x, n->der);
            }
        }
        if ((n->info.type == "Array") && (x.type == "Key")) {
            searchTree(x, n->izq);
        }
        if ((n->info.type == "Key") && (x.type == "Value")) {
            if (n->izq != NULL) {
                searchTree(x, n->der);
            } else {
                searchTree(x, n->izq);
            }
        }
        if ((n->info.type == "Array") && (x.type == "Value")) {
            searchTree(x, n->izq);
        }
        if ((n->info.type == "Index") && (x.type == "Value")) {
            if (n->der != NULL) {
                searchTree(x, n->der);
            } else {
                searchTree(x, n->izq);
            }
        }
        if ((n->info.type == "Key") && (x.type == "Key")) {
            searchTree(x, n->der);
        }
        if ((n->info.type == "Array") && (x.type == "Array")) {
            searchTree(x, n->izq);
        }
        if ((n->info.type == "Index") && (x.type == "Array")) {
            if (n->der != NULL) {
                searchTree(x, n->der);
            } else {
                searchTree(x, n->izq);
            }
        }
        if ((n->info.type == "Key") && (x.type == "Array")) {
            searchTree(x, n->der);
        }
        if ((n->info.type == "Index") && (x.type == "Index")) {
            if (n->info.hierarchy == x.hierarchy) {
                searchTree(x, n->der);
            } else if (x.hierarchy < n->info.hierarchy) {
                if (n->der != NULL) {
                    searchTree(x, n->der);
                } else {
                    searchTree(x, n->izq);
                }
            }
        }
        if ((n->info.type == "Key") && (x.type == "Index")) {
            searchTree(x, n->der);
        }
    }  
}

template<class T> void Tree<T>::rid(Node<T>* aux) {
	// Este método recorre el árbol binario en preorden, es decir, primero visita la raíz del árbol, 
	// luego recorre el subárbol izquierdo y por último recorre el subárbol derecho.
	// Para cada nodo que visita, el método realiza las siguientes acciones:
	// 1) Si el tipo de dato del nodo es "Key", imprime el valor del nodo seguido de dos puntos y un espacio, 
	//    y luego recorre el subárbol izquierdo y derecho del nodo.
	// 2) Si el tipo de dato del nodo es "Index", imprime la palabra "Index" seguida de dos puntos y un espacio, 
	//    luego imprime el valor del nodo, y finalmente recorre el subárbol izquierdo y derecho del nodo.
	// 3) Si el tipo de dato del nodo es cualquier otro, imprime el valor del nodo y 
	//    luego recorre el subárbol izquierdo y derecho del nodo.
	// Al finalizar el recorrido del árbol, el método imprime una línea con una cadena de caracteres repetidos para separar cada elemento del árbol

    if (aux == NULL) return;
	if (aux->info.type == "Key") { // Si el tipo de dato es "Key" Imprime el valor del nodo seguido de dos puntos y un espacio
        if (aux->info.data == "id")
			cout << "=============================================================" << endl;
		cout << aux->info.data << ": ";
    } else if (aux->info.type == "Index") { // Si el tipo de dato es "Index" Imprime la palabra "Index" seguida de dos puntos y un espacio, luego imprime el valor del nodo
        cout << "\n" << "Index: " << aux->info.data << endl;
    } else { // Si el tipo de dato es cualquier otro Imprime el valor del nodo
        cout << aux->info.data << endl;
    }
    rid(aux->izq);
    rid(aux->der);
}

template<class T> void Tree<T>::idr(Node<T>* aux){
	if(aux != NULL){
		if (aux->info.type == "Key") {
            idr(aux->izq);
            idr(aux->der);
            cout << aux->info.data << ": ";
            cout << "=============================================================" << endl;
        } else {
            idr(aux->izq);
            idr(aux->der);
            cout << aux->info.data << endl;
        }
	}
}

template<class T> void Tree<T>::ird(Node<T>* aux){
	if(aux != NULL){
		if (aux->info.type == "Key") {
            idr(aux->izq);
            cout << aux->info.data << ": ";
            idr(aux->der);
            cout << "=============================================================" << endl;
        } else {
            idr(aux->izq);
            cout << aux->info.data << endl;
            idr(aux->der);
        }
	}
}

template<class T> void Tree<T>::vectorData(string key, vector<objOrd>* vec, Node<T>* n) {
	// Atravesar el árbol comenzando en el nodo n dado, y para cada nodo encontrado, agregue un objeto objOrd al vector vec dado,
	// que contiene el nodo y el valor del hijo izquierdo del nodo con la clave dada.
	// El método comienza declarando una variable local m de tipo objOrd,
	// e inicializándolo con el nodo actual n y el resultado de llamar a la función searchValue en key y n.
	// Luego agrega m al vector vec usando el método push_back.
	// Se comprueba si el nodo actual tiene un hijo derecho y, si lo tiene,
	// se llama recursivamente a sí mismo con el hijo derecho como argumento del nuevo nodo.
	// Este proceso continúa hasta que se ha recorrido todo el árbol.
	// recibe la key de busqueda, un vector a donde meter objetos struct objOrd
	// que tiene un campo puntero y otro valor, recibe también un puntero a node (que es index)
	
    objOrd m;
    m.ind = n;
    m.value = searchValue(key, n);
    vec -> push_back(m);
    if (n->der != NULL) {
        vectorData(key, vec, n->der);
    }
}


#endif 