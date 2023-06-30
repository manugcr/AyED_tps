#include <ctype.h> // isDigit() function
#include <cstdlib> // EXIT_SUCCESS
#include <fstream> // ifstream()
#include <iostream> // inputs and outputs
#include <sstream> // strings
#include <vector> // vectors
#include "include/json.hpp" // json parsing

// library https://github.com/nlohmann/json
using namespace std;
using json = nlohmann::ordered_json; 

// ====================================================================
// ======================CLASSES and STRUCTS===========================
// ====================================================================
template<class T> class node { // Clase nodo
    public:
        T info;
    	node* der;
		node* izq;
};

typedef struct { // Struct obj
    string type;
    string data;
    int hierarchy;
} obj;

typedef struct { // Struct objOrd
    node<obj>* ind;
    string value;
} objOrd;

template<class T> class tree { // Clase arbol
    private:
        node<T>* root; 
        void searchTree(T x, node<T>*& n); // Creates the search tree
        void rid(node<T>* aux); // Recorrido del arbol en preorden (raiz, izquierdo, derecho)
        void idr(node<T>* aux); // Recorrido postorden (izquierdo, derecho, raiz)
        void ird(node<T>* aux); // Recorrido inorden (izquierdo, raiz, derecho)
    public:
        tree() {root = NULL;}; // tree declaration
        ~tree() {}; // Destructor
        void createSearchTree(T x); // Creates the search tree
        void showTree() {rid(root);} // Mostramos el arbol en forma preorden (Raiz, izquierdo, derecho)
		void vectorData(string key, vector<objOrd>* vec, node<T>* n); // Vector con datos de cada laureado del json
        node<T>* getRoot() {return root;}; // returns the root of the tree (node)
};

// ====================================================================
// ==========================TREE METHODS====================¡=========
// ====================================================================
template<class T> void tree<T>::createSearchTree(T x) {
    searchTree(x, root);
}

template<class T> void tree<T>::searchTree(T x, node<T>*& n) {
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
        n = new node<T>;
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

template<class T> void tree<T>::rid(node<T>* aux) {
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

template<class T> void tree<T>::idr(node<T>* aux){
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

template<class T> void tree<T>::ird(node<T>* aux){
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

template<class T> void tree<T>::vectorData(string key, vector<objOrd>* vec, node<T>* n) {
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

// ====================================================================
// ===========================DECLARATIONS=============================
// ====================================================================
int jsonToVector(json objt, vector<obj>* ser, int hierarchy); // Funcion indexar y organizar json
int stringCompare(string, string); // Funcion que compara dos strings
void createBinaryTree(vector<obj>vect, tree<obj>* arb); // Funcion crear tree binario con el json serial
void insertionSort(vector<objOrd>*); // Metodo de ordenamiento por insercion
bool isEqual(obj o1, obj o2); // Compara dos objetos y devuelve si son iguales o no
tree<obj> sortTree(string key, vector<obj>* vectorJson, vector<objOrd>* vectorOrd, tree<obj>* tree); // Ordena el arbol con el metodo de insercion
void bubbleSort(vector<objOrd>* vector);

// ====================================================================
// ==============================FUNCTIONS=============================
// ====================================================================
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
	
	// [{ "type": "Array", "data": "laureates", "hierarchy": 0 },
	// { "type": "Index", "data": "0", "hierarchy": 1 },
	// { "type": "Key", "data": "id", "hierarchy": 0 },
	// { "type": "Value", "data": "1", "hierarchy": 0 },
	// { "type": "Key", "data": "firstname", "hierarchy": 0 },
	// { "type": "Value", "data": "Wilhelm Conrad", "hierarchy": 0 },
	// { "type": "Key", "data": "surname", "hierarchy": 0 },
	// { "type": "Value", "data": "Röntgen", "hierarchy": 0 },
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

void createBinaryTree(vector<obj> vector, tree<obj>* tree) {
    for (int i=0 ; i<vector.size() ; i++) {
        tree->createSearchTree(vector[i]);
    }
}

bool isEqual(obj object1, obj object2) {
	// Funcion comparar igualdad de objs	
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

string searchValue(string key, node<obj>* node) {	
	// Es una función recursiva que busca un valor en un árbol. 
	// Dado una "clave" (key) y un nodo del árbol (node), la función buscará el valor correspondiente a la clave en el nodo y sus hijos.
	// La función comprueba si el hijo izquierdo del nodo es una clave y si su valor es igual a la clave que se está buscando. 
	// Si es así, devuelve el valor del nieto izquierdo del nodo.
	// Si el hijo izquierdo del nodo no es una clave o su valor no es igual a la clave que se está buscando, 
	// la función comprueba si el nodo es un índice. Si es así, busca recursivamente el valor de la clave en el hijo izquierdo del nodo.
	// Si el nodo no es un índice, la función comprueba si el nodo es una clave y si su valor es igual a la clave que se está buscando. 
	// Si es así, devuelve el valor del hijo izquierdo del nodo. Si no es así, busca recursivamente el valor de la clave en el hijo derecho del nodo.
	// Si la función no encuentra la clave en ningún lugar del árbol, no devuelve ningún valor.
		
    if (node->izq->info.type == "Key" && node->izq->info.data == key) {
        return node->izq->izq->info.data;
    } else if (node->info.type == "Index") {
        return searchValue(key, node->izq);
    } else if (node->info.type == "Key") {
        if (node->info.data == key) {
            return node->izq->info.data;
        } else { 
            return searchValue(key, node->der);
        }
    }
}

tree<obj> sortTree(string key, vector<obj>* vectorJson, vector<objOrd>* vectorOrd, tree<obj>* auxTree) {
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
	
	tree<obj> T1;
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

// ====================================================================
// =============================MAIN===================================
// ====================================================================
int main(int argc, char *argv[]) {
    // Read json
    ifstream i("json/jsonTest.json");
    auto j = nlohmann::ordered_json::parse(i);

    // Vectors
    vector<obj> serial;
    vector<objOrd> vectorToOrder;

    // Global trees
    tree<obj> T1;
    tree<obj> T2;

    // Index json
    jsonToVector(j, &serial, 9999);
    
	// Question sort
    string answer, key;
    cout << "Sort by \"key\" or by \"default\"?" << endl;
    cin >> answer;
    if (answer == "default" || answer == "Default" || answer == "d") {
        createBinaryTree(serial, &T1);	// Creamos el arbol binario con el json serializado
        cout << "============================================================" << endl;
        cout << "==================Compilation successful====================" << endl;
        cout << "============================================================" << endl;
        T1.showTree();
    } else if (answer == "key" || answer == "Key" || answer == "k") {
        cout << "Sort by key, {id, firstname, surname, born, bornCountry, year ...}" << endl;
        cin >> key;
        createBinaryTree(serial, &T1);	// Creamos el arbol binario con el json serializado
        cout << "============================================================" << endl;
        cout << "==================Compilation successful====================" << endl;
        cout << "============================================================" << endl;
        T2 = sortTree(key, &serial, &vectorToOrder, &T1);
        T2.showTree();
    }

    cout << "============================================================" << endl;
    cout << "======================Sort successful=======================" << endl;
    cout << "============================================================" << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}