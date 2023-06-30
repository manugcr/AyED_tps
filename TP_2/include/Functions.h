#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ctype.h> // isDigit() function
#include <sstream> // strings
#include <vector> // vectors

#include "json.hpp" // json parsing - library https://github.com/nlohmann/json
#include "Node.h"
#include "Tree.h"
#include "Structs.h"

using namespace std;
using json = nlohmann::ordered_json; 

int jsonToVector(json objt, vector<obj>* ser, int hierarchy); 
int stringCompare(string string1, string string2);
void insertionSort(vector<objOrd>* vector);
void bubbleSort(vector<objOrd>* vector);
void createBinaryTree(vector<obj> vector, Tree<obj>* tree);
bool isEqual(obj object1, obj object2);
string searchValue(string key, Node<obj>* Node);
Tree<obj> sortTree(string key, vector<obj>* vectorJson, vector<objOrd>* vectorOrd, Tree<obj>* auxTree);

int jsonToVector(json object, vector<obj>* serial, int hierarchy) {
	// Es una función que convierte un objeto JSON en un vector de objetos. 
	// Dado un objeto JSON y un vector de objetos (serial), la función recorre el objeto JSON y agrega cada elemento 
	// del objeto JSON al vector de objetos en un formato específico.
	// La función comienza iterando sobre cada elemento del objeto JSON. 
	// Para cada elemento, la función comprueba si el elemento es un array o un objeto. 
	// Si es un array o un objeto, la función comprueba si la clave del elemento es un número. 
	// Si la clave es un número, la función agrega un objeto al vector de objetos con el tipo "Index" y la clave del elemento como datos. 
	// Si la clave no es un número, la función agrega un objeto al vector de objetos con el tipo "Array" y la clave del elemento como datos.
	// Si el elemento del objeto JSON no es un array o un objeto, la función agrega dos objetos al vector de objetos. 
	// El primer objeto tiene el tipo "Key" y la clave del elemento como datos, y el segundo objeto tiene el tipo "Valor" y el valor del elemento como datos.
	// La función devuelve un entero que indica la jerarquía del último elemento agregado al vector de objetos.
	
	// El valor 9999 se utiliza para establecer una jerarquía inicial alta para el primer elemento 
	// "Index" que se encuentre en el JSON, lo que permite que se recorran todos los elementos 
	// "Index" del JSON sin que se produzca un desbordamiento de la jerarquía.
	//
	// Por ejemplo
	// Cuando se recorre el elemento laureates, se encuentra un elemento Index con un valor de 1. 
	// La jerarquía de este elemento se determina como 9999 - 1 = 9998. Luego se recorre el elemento con el índice 1 y 
	// se encuentra otro elemento Index con un valor de 2. La jerarquía de este elemento se determina como 9998 - 1 = 9997. 
	// Así sucesivamente, hasta que se recorren todos los elementos Index del JSON.
	//
	// Al utilizar un valor alto para la jerarquía inicial, se asegura que todos los elementos Index del 
	// JSON tendrán una jerarquía distinta y se podrán ordenar correctamente en el vector resultante. 
	// Sin embargo, si el JSON tiene una profundidad muy grande (es decir, si tiene muchos elementos anidados), 
	// es posible que se produzca un desbordamiento de la jerarquía y se genere un error. 
	// Por eso, se recomienda utilizar un valor adecuado para la jerarquía inicial que permita recorrer 
	// todos los elementos del JSON sin generar un desbordamiento.
	
	// {"type": "Key", "data": "laureates", "hierarchy": 0}
    // {"type": "Array", "data": "", "hierarchy": 0}
    // {"type": "Index", "data": "0", "hierarchy": 1}
    // {"type": "Key", "data": "id", "hierarchy": 2}
    // {"type": "Value", "data": "1", "hierarchy": 2}
    // {"type": "Key", "data": "firstname", "hierarchy": 2}
    // {"type": "Value", "data": "Wilhelm Conrad", "hierarchy": 2}
    // {"type": "Key", "data": "surname", "hierarchy": 2}
    // {"type": "Value", "data": "Röntgen", "hierarchy": 2}
	// ...
	// { "type": "Key", "data": "id", "hierarchy": 0 },

	for (auto &iterator: object.items()) {
        if (iterator.value().type() == json::value_t::array || iterator.value().type() == json::value_t::object) {
            // pregunta si es un digito porque tambien podria ser un array cuya key es un numero
			if (isdigit(iterator.key()[0])) {
                obj n;
                n.type = "Index";
                n.data = iterator.key();
                n.hierarchy = hierarchy;
                serial->push_back(n);
                // si el tamaño es 9999 le saca 1 para que cuando vuelva a entrar el siguiente array va a ser de menor jerarquia asi despues se reinicia
				if (n.hierarchy == 9999) {
                    int a = jsonToVector(iterator.value(), serial, hierarchy-1);
                } else if (hierarchy > 1) {
                    int a = jsonToVector(iterator.value(), serial, hierarchy-2);
                } 
            } else {
                obj m;
                m.type = "Array";
                m.data = iterator.key();
                m.hierarchy = 0;
                serial->push_back(m);
                jsonToVector(iterator.value(), serial, hierarchy);
            }
        } else {
            obj k;
            obj v;
            k.type = "Key";
            k.data = iterator.key();
            k.hierarchy = 0;
            v.type = "Value";
            v.data = to_string(iterator.value());
            v.hierarchy = 0;
            serial->push_back(k);
            serial->push_back(v);
        }
    }
    return hierarchy-1;
}


int stringCompare(string string1, string string2) {
	// Esta función compara dos cadenas de caracteres (strings) y devuelve un entero que indica si la primera cadena es mayor que, menor que o igual a la segunda cadena.
	// La función comienza declarando una variable local "path" que es igual al tamaño de la primera cadena. 
	// Si el tamaño de la segunda cadena es menor que el tamaño de la primera cadena, "path" se vuelve igual al tamaño de la segunda cadena. 
	// Esto se hace para determinar cuántos caracteres de cada cadena se deben comparar.
	// Luego, la función itera sobre cada carácter de cada cadena hasta llegar a la longitud máxima determinada por "path". 
	// Para cada par de caracteres en las dos cadenas, la función comprueba si el carácter de la primera cadena es mayor que, 
	// menor que o igual al carácter de la segunda cadena. Si el carácter de la primera cadena es mayor que el 
	// carácter de la segunda cadena, la función devuelve 1. Si el carácter de la primera cadena es menor que el carácter de la segunda cadena, 
	// la función devuelve -1. Si los caracteres son iguales, la función continúa iterando.
	// Si la función ha comparado todos los caracteres de ambas cadenas y no ha encontrado ninguna diferencia, devuelve 0, indicando que las cadenas son iguales.

	int path = string1.size();
    if (string1.size() < string2.size()) {
        path = string1.size();
    } else {
        path = string2.size();
    }
    for (int i = 0; i < path; i++) {
        if (string1.at(i) < string2.at(i)) {
            return -1;
        }
        if (string1.at(i) > string2.at(i)) {
            return 1;
        }
    }
    return 0;
}	
	
void insertionSort(vector<objOrd>* vector) {
	// 1) Se declara un objeto temp de la clase objOrd. Esta variable se usará para almacenar temporalmente el elemento actual del vector.
	// 2) Se itera sobre el vector desde el segundo elemento hasta el final. En cada iteración, se asigna el elemento actual del vector a la variable temp.
	// 3) Se declara una variable j inicializada con i-1, que indica la posición del elemento anterior al actual.
	// 4) Se entra en un bucle while que se ejecuta mientras j sea mayor o igual a cero y el valor del elemento almacenado en temp sea menor que el valor del elemento en la posición j del vector.
	// 5) Dentro del bucle, se desplaza el elemento en la posición j del vector a la posición j+1.
	// 6) Se decrementa j en uno, y se vuelve al paso 4.
	// 7) Cuando se sale del bucle, se intercala el elemento almacenado en temp en la posición j+1 del vector.
	// 8) Se continúa con la siguiente iteración del bucle externo, hasta que se hayan procesado todos los elementos del vector.

	objOrd temp;
    for (int i=1 ; i<vector->size() ; i++) {
        int j = i-1;
        temp = vector->at(i);
        while (j>=0 && stringCompare(temp.value, vector->at(j).value)<0) {
            vector->at(j+1) = vector->at(j);
            j--;
        }
        vector->at(j+1) = temp;
    }
}

void bubbleSort(vector<objOrd>* vector) {
  for (int i=0; i<vector->size() ; i++) {
    for (int j=0 ; j<vector->size()-1 ; j++) {
      if (stringCompare(vector->at(j).value, vector->at(j+1).value)>0) {
        objOrd temp = vector->at(j);
        vector->at(j) = vector->at(j+1);
        vector->at(j+1) = temp;
      }
    }
  }
}

void createBinaryTree(vector<obj> vector, Tree<obj>* tree) {
    for (int i=0 ; i<vector.size() ; i++) {
        tree->createSearchTree(vector[i]);
    }
}

bool isEqual(obj object1, obj object2) {	
	if (object1.type != object2.type) {
        return false;
    }
    if (object1.data != object2.data) {
        return false;
    }
    if (object1.hierarchy != object2.hierarchy) {
        return false;
    }
    return true;
}

string searchValue(string key, Node<obj>* Node) {
    // Es una función recursiva que busca un valor en un árbol. 
	// Dado una "clave" (key) y un nodo del árbol (node), la función buscará el valor correspondiente a la clave en el nodo y sus hijos.
	// La función comprueba si el hijo izquierdo del nodo es una clave y si su valor es igual a la clave que se está buscando. 
	// Si es así, devuelve el valor del nieto izquierdo del nodo.
	// Si el hijo izquierdo del nodo no es una clave o su valor no es igual a la clave que se está buscando, 
	// la función comprueba si el nodo es un índice. Si es así, busca recursivamente el valor de la clave en el hijo izquierdo del nodo.
	// Si el nodo no es un índice, la función comprueba si el nodo es una clave y si su valor es igual a la clave que se está buscando. 
	// Si es así, devuelve el valor del hijo izquierdo del nodo. Si no es así, busca recursivamente el valor de la clave en el hijo derecho del nodo.
	// Si la función no encuentra la clave en ningún lugar del árbol, no devuelve ningún valor.
				
    if (Node->izq->info.type == "Key" && Node->izq->info.data == key) {
        return Node->izq->izq->info.data;
    } else if (Node->info.type == "Index") {
        return searchValue(key, Node->izq);
    } else if (Node->info.type == "Key") {
        if (Node->info.data == key) {
            return Node->izq->info.data;
        } else { 
            return searchValue(key, Node->der);
        }
    }
}

Tree<obj> sortTree(string key, vector<obj>* vectorJson, vector<objOrd>* vectorOrd, Tree<obj>* auxTree) {
    // Esta función toma cuatro argumentos: una cadena de caracteres llamada "key", dos vectores llamados "vectorJson" y "vectorOrd", y un árbol llamado "auxTree". 
	// La función devuelve un árbol de objetos llamado "T1".
	// La función comienza declarando un árbol "T1" vacío. Luego, llama a un método "vectorData" en el árbol "auxTree" con 
	// los argumentos "key", "vectorOrd" y el hijo izquierdo del nodo raíz de "auxTree". 
	// Esto rellena el vector "vectorOrd" con algún tipo de información.
	// A continuación, llama a una función "insertionSort" en "vectorOrd" para ordenar los elementos del vector. 
	// Luego, agrega un elemento al árbol "T1" usando el método "createSearchTree" y el primer elemento del vector "vectorJson".
	// El siguiente bucle "for" recorre el vector "vectorOrd" y establece el hijo derecho de cada nodo en NULL. 
	// Luego, otro bucle "for" recorre el vector "vectorOrd" desde el penúltimo elemento hasta el primero, y establece el hijo derecho del nodo actual en el nodo siguiente del vector.
	// Finalmente, la función establece el hijo izquierdo del nodo raíz de "T1" en el primer nodo del vector "vectorOrd" y devuelve "T1".
	
	// Root
	// |
	// +-- Array: "laureates"
	// |
	// +-- Index: "0"
	// |   |
	// |   +-- Key: "id"
	// |   |   |
	// |   |   +-- Value: "1"
	// |   |
	// |   +-- Key: "firstname"
	// |   |   |
	// |   |   +-- Value: "Wilhelm Conrad"
	// |   |
	// |   +-- Key: "surname"
	// |   |   |
	// |   |   +-- Value: "Röntgen"
	// ... ...
	
	Tree<obj> T1;
    auxTree->vectorData(key, vectorOrd, auxTree->getRoot()->izq);
//    bubbleSort(vectorOrd);
    insertionSort(vectorOrd);
    T1.createSearchTree(vectorJson->at(0));
    // Limpiador de nodos derechos
    for (int i=0 ; i<vectorOrd->size() ; i++) {
        vectorOrd->at(i).ind->der = NULL;
    }
    // pre anidacion de nodos
    for (int i=vectorOrd->size()-2 ; i>=0 ; i--) {
        vectorOrd->at(i).ind->der = vectorOrd->at(i+1).ind;
    }
    T1.getRoot()->izq = vectorOrd->at(0).ind;
    return T1;
}   

#endif // FUNCTIONS_H