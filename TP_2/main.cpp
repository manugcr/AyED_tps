#include <fstream> // ifstream()
#include <iostream> // inputs and outputs

#include "include/json.hpp" // json parsing - library https://github.com/nlohmann/json
#include "include/Node.h"
#include "include/Tree.h"
#include "include/Structs.h"
#include "include/Functions.h"

using namespace std;
using json = nlohmann::ordered_json; 

// ====================================================================
// =============================MAIN===================================
// ====================================================================
int main(int argc, char *argv[]) {
    // Read json
    ifstream i("json/jsonTest2.json");
    auto j = nlohmann::ordered_json::parse(i);

    // Vectors
    vector<obj> serial;
    vector<objOrd> vectorToOrder;

    // Global trees
    Tree<obj> T1;
    Tree<obj> T2;

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
        cout << "Sort by key, {id,firstname, surname, born, bornCountry ...}" << endl;
        cin >> key;
        createBinaryTree(serial, &T1);	// Creamos el arbol binario con el json serializado
        cout << "============================================================" << endl;
        cout << "==================Compilation successful====================" << endl;
        cout << "============================================================" << endl;
        T2 = sortTree(key, &serial, &vectorToOrder, &T1);
        T2.showTree();
    }

    cout << "============================================================" << endl;
    cout << "======================Program ended=========================" << endl;
    cout << "============================================================" << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}