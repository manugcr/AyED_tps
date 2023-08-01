//#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <cstring>
using namespace std;
typedef long int tipolista;

class Nodo {
	protected:
		tipolista dato;
		Nodo *next;
		
		char nombre; // nombre que tendra la variable
		string instruccion;  // cadena que almacena una instruccion
	public:
		Nodo() { next=NULL; };
		Nodo(tipolista a) { dato=a; next=NULL; };
		Nodo *get_next() { return next; };
		void set_dato(tipolista a) { dato=a; };
		void set_next(Nodo *n) { next=n; };
		bool es_vacio() { return next==NULL; };
		tipolista get_dato() { return dato; };
		
		Nodo(string cadena) { instruccion=cadena; next=NULL; };   // Constructor para inicializar Nodos en la lista de instrucciones
		Nodo(char a) { nombre=a; next=NULL; }; // Constructor para inicializar Nodos en la lista de variables
		string get_instr() { return instruccion; };
		char get_nombre() { return nombre; };
};

class Lista {
	protected:
		Nodo *czo;
	public:
		// Metodos de la lista
		Lista() { czo=new Nodo(); };
		Lista(Nodo *n) { czo=n; };
		Lista *copy(void);
		Lista *resto(void);
		string cabezastr(void); // devuelve la cabeza de la lista de instrucciones
		bool esvacia(void);
		void del(void);
		void concat(Lista *l1);
		void add(tipolista d);		
		
		// Metodos para instrucciones
		void addinstruccion(string ins); // crea un nuevo nodo que contiene la instruccion, que es pasada como parametro (string)
};

// =======================
// Metodos clase Lista
// =======================
Lista *Lista::copy(void) {
	Lista *aux=new Lista();
	aux->concat(this);
	return aux;
}
Lista *Lista::resto(void) {
	Lista *l=new Lista(czo->get_next());
	return (l);
}
string Lista::cabezastr(void) { // retorna la cabeza de la lista de instrucciones
	if(esvacia()) {
		cout<<" Error, Cabeza de lista vacia1";
		return NULL;
	}
	return czo->get_instr();
}
bool Lista::esvacia(void) {
	return czo->es_vacio();
}
void Lista::del(void) {
	Nodo *aux;
	aux=czo;
	czo=czo->get_next();
	delete aux;
}
void Lista::concat(Lista *l1) {
	// le transfiere los datos de l1 a this
	if (!(l1->esvacia())) {
		this->addinstruccion(l1->cabezastr());
		this->concat(l1->resto());
	}
}
void Lista::addinstruccion(string cadena) { // anade las instrucciones a la lista de instrucciones pero en forma "ordenada"
	Nodo *nuevo=new Nodo(cadena);

	if(esvacia()) {
		nuevo->set_next(czo);
		czo=nuevo;
	} else {
		Nodo *aux = new Nodo(); // se crea un nodo auxiliar
		aux = czo;
		if(aux->get_next()->get_next() == NULL) { // si hay un solo nodo
			nuevo->set_next(aux->get_next());
			aux->set_next(nuevo);
		} else { // sino, itera hasta encontrar la posicion correcta
			while(aux->get_next()->get_next() != NULL) aux=aux->get_next();
			if(aux->get_next()->get_next() == NULL) {
				nuevo->set_next(aux->get_next());
				aux->set_next(nuevo);
			}
		}
	}
}









int main() {
	// Inicializo Listas
	Lista *instr = new Lista(); // lista que almacena instrucciones
	Lista *auxlista = new Lista(); // Lista auxiliar que es copia de la lista de instrucciones
	
	// lectura y apertura del archivo
	ifstream archivo;
	string temp;
	archivo.open("programa.txt", ios::in);
	while(getline(archivo,temp))
		cout<<temp<<endl;
	archivo.close();

//	auxlista = instr->copy();// guardo una copia de la lista en una lista auxiliar para el JUMP hacia arriba
//	while(!instr->esvacia()){
//		instruccion = instr->cabezastr(); // extrae la instruccion a ejecutar
//	}
	
	cout<<endl;
	//system("PAUSE");
	return 0;
}