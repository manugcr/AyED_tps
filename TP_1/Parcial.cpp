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
		char nombre; // nombre que tendra la variable
		Nodo *next;
		tipolista dato;
		string instruccion;  // cadena que almacena una instruccion
	public:
		Nodo() {
			next=NULL;
		};
		Nodo(tipolista a) {
			dato=a;
			next=NULL;
		};
		Nodo(string cadena) {
			instruccion=cadena;
			next=NULL;
		};    // Constructor para inicializar Nodos en la lista de instrucciones
		Nodo(char a) {
			nombre=a;
			next=NULL;
		}; // Constructor para inicializar Nodos en la lista de variables
		Nodo *get_next() {
			return next;
		};

		void set_dato(tipolista a) {
			dato=a;
		};
		void set_next(Nodo *n) {
			next=n;
		};
		bool es_vacio() {
			return next==NULL;
		};
		char get_nombre() {
			return nombre;
		};
		tipolista get_dato() {
			return dato;
		};
		string get_instr() {
			return instruccion;
		};
};

class Lista {
	protected:
		Nodo *czo;
	public:
		Lista() {
			czo=new Nodo();
		};
		Lista(Nodo *n) {
			czo=n;
		};
		Lista *resto(void);
		Lista *copy(void);
		void del(void);
		void add(tipolista d);
		void addvar(char nombre); // crea un nuevo nodo que contiene la variable, definida por su nombre y un valor
		void addinstruccion(string ins); // crea un nuevo nodo que contiene la instruccion, que es pasada como parametro (string)
		void asignarValor(char, tipolista);
		void concat(Lista *l1);
		bool esvacia(void);
		char cabezavar(void);
		tipolista cabeza(void);
		tipolista ExtraeValor(char);
		string cabezastr(void); // devuelve la cabeza de la lista de instrucciones (como tipo string)
};

class Pila:public Lista {
	public:
		Pila() {
			Lista();
		};
		void apilar(tipolista x) {
			add(x);
		};
		tipolista tope(void) {
			return cabeza();
		};
		void desapilar(void) {
			del();
		};
		bool pilavacia() {
			return esvacia();
		};
};


void Lista::del(void) {
	Nodo *aux;
	aux=czo;
	czo=czo->get_next();
	delete aux;
}
void Lista::add(tipolista d) {
	Nodo *nuevo=new Nodo(d);
	nuevo->set_next(czo);
	czo=nuevo;
}

// funcion precedencia
// prcd(o1,'(') = 0 para todo o1 != de ')'
// prcd(o1,')') = 1 para todo o1 != de '('
// prcd('(',o2) = 0 para todo o2
// prcd(o1,o2)  = 1 para todo o1 >= precedencia que o2
int prcd(int o1,int o2) {
	if(o2=='(')
		if(o1==')') return 1;
		else return 0;
	if(o2==')')
		if(o1=='(') return 0;
		else return 1;
	if(o1=='(') return 0;

	if((o1=='*')||(o1=='/')) return 1;
	if(((o1=='+')||(o1=='-'))&&((o2=='+')||(o2=='-'))) return 1;
	else return 0;
}

// m�todos creados para el parcial---------------------------

char ExtraeNombre(string cadena) { // recorre el string pasado como parametro y extrae el nombre de la variable (de 'a' hasta 'z' inclusive)
	char n_variable;
	for(int i = 0; i<cadena.length() ; i++) {
		if( (cadena.at(i) >= 'a') && (cadena.at(i) <= 'z'))
			return n_variable = cadena.at(i);
	}
}
tipolista Lista::ExtraeValor(char n) { // busca la variable en la lista de variables a partir de su nombre, y retorna su valor como tipolista
	char b;
	if(esvacia()) {
		cout<<" Error, variable " << n << " no declarada";
		//return '\0';
		return -1;
	}
	if(n == czo->get_nombre()) {
		tipolista a = czo->get_dato(); // recupero el valor de la variable
		//return b = a+'0'; // conversion del integer a char
		return a;
	} else
		return resto()->ExtraeValor(n);
}

void Lista::addvar(char n) { // a�ade (o inicializa) una variable en la lista de variables (utiliza otro constructor de nodo)
	Nodo *nuevo=new Nodo(n);
	nuevo->set_next(czo);
	czo=nuevo;
}
void Lista::addinstruccion(string cadena) { // a�ade las instrucciones a la lista de instrucciones pero en forma "ordenada"
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
void Lista::asignarValor(char n, tipolista valor) { // asigna el valor a una variable de la lista que es pasada como parametro junto con el valor
	if(esvacia())
		cout << " Error, Lista vacia";

	if(n == czo->get_nombre()) // si se encuentra la variable en la lista, asigna el valor pasado como parametro
		czo->set_dato(valor);
	else return this->resto()->asignarValor(n,valor);

}

string Lista::cabezastr(void) { // retorna la cabeza de la lista de instrucciones
	if(esvacia()) {
		cout<<" Error, Cabeza de lista vacia1";
		return NULL;
	}
	return czo->get_instr();
}

char Lista::cabezavar(void) { // retorna la cabeza de la lista de variables
	if(esvacia()) {
		cout<<" Error, Cabeza de lista vacia2";
		return '\0';
	}
	return czo->get_nombre();
}

tipolista EvaluaExpresion(Lista* var, string cadena) { // es el codigo de la clase practica puesto como funcion
	int error=0;
	Pila *p=new Pila();
	string pf;
	for(int i=0; (i<cadena.length())&&(!error); i++) {
		if (cadena.at(i)=='{') p->apilar('{');
		if (cadena.at(i)=='[') p->apilar('[');
		if (cadena.at(i)=='(') p->apilar('(');

		if (cadena.at(i)=='}') {
			if (p->pilavacia()) error=1;
			else if(p->tope()!='{') error=1;
			else p->desapilar();
		}
		if (cadena.at(i)==']') {
			if (p->pilavacia()) error=1;
			else if(p->tope()!='[') error=1;
			else p->desapilar();
		}
		if (cadena.at(i)==')') {
			if (p->pilavacia()) error=1;
			else if(p->tope()!='(') error=1;
			else p->desapilar();
		}
	}
	if((!error)&&p->pilavacia())cout<<endl<<"Todo OK"<<endl;
	else cout<<endl<<"ERROR";

	cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
	//conversion de entrefijo a posfijo
	char d,p1;

	for(int j=0; j<cadena.length(); j++) {
		d=cadena.at(j);

		if( (d>='a') && (d<='z') ) { // si se encuentra una variable en la expresion

			tipolista a = var->ExtraeValor(d);
			stringstream ss;
			ss << a;
			string str = ss.str();
			pf= pf+str; // guarda el valor que tiene la variable
			continue;
		}

		if ((d>='0')&&(d<='9')) {
			pf.push_back(d);
		} else {
			while((!p->pilavacia())&&(prcd(p->tope(),d))) {
				p1=p->tope();
				p->desapilar();
				pf.push_back(' ');
				pf.push_back(p1);

			}
			if((p->pilavacia())||(d!=')')) {
				p->apilar(d);
				pf.push_back(' ');
			}

			else
				p->desapilar();
		}
	}
	while(!p->pilavacia()) {
		p1=p->tope();
		p->desapilar();
		pf.push_back(' ');
		pf.push_back(p1);
	}

	cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;

// Evaluacion de la expresion en posfijo
	//int o1,o2;

	for(int i=0; (i<pf.length())&&(!error); ++i) {

		if(pf.at(i) == ' ')
			continue;

		else if(isdigit(pf.at(i))) {

			int num=0;
			//extract full number
			while(isdigit(pf.at(i))) {
				num = num * 10 + (int)(pf.at(i) - '0');
				i++;
			}
			i--;

			p->apilar(num);
		}

		else {

			int val1 = p->tope();
			p->desapilar();
			int val2 = p->tope();
			p->desapilar();

			switch (pf.at(i)) {
				case '+':
					p->apilar(val2 + val1);
					break;
				case '-':
					p->apilar(val2 - val1);
					break;
				case '*':
					p->apilar(val2 * val1);
					break;
				case '/':
					p->apilar(val2/val1);
					break;

			}
		}

	}
	cout<<endl<<"\n\nResultado= "<<p->tope()<<endl;
	return p->tope();
}

bool EvaluaBooleano(Lista* var, string cadena) { // es el codigo de la clase practica puesto como funcion
	int error=0;
	Pila *p=new Pila();
	string pf;
	for(int i=0; (i<cadena.length())&&(!error); i++) {
		if (cadena.at(i)=='{') p->apilar('{');
		if (cadena.at(i)=='[') p->apilar('[');
		if (cadena.at(i)=='(') p->apilar('(');

		if (cadena.at(i)=='}') {
			if (p->pilavacia()) error=1;
			else if(p->tope()!='{') error=1;
			else p->desapilar();
		}
		if (cadena.at(i)==']') {
			if (p->pilavacia()) error=1;
			else if(p->tope()!='[') error=1;
			else p->desapilar();
		}
		if (cadena.at(i)==')') {
			if (p->pilavacia()) error=1;
			else if(p->tope()!='(') error=1;
			else p->desapilar();
		}
	}
	if((!error)&&p->pilavacia())cout<<endl<<"Todo Ok"<<endl;
	else cout<<endl<<"ERROR";

	//cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo
	char d,p1;
	/*;
	*/
	for(int j=0; j<cadena.length(); j++) {
		d=cadena.at(j);

		if( (d>='a') && (d<='z') ) { // si se encuentra una variable en la expresion
			tipolista a = var->ExtraeValor(d);
			stringstream ss;
			ss << a;
			string str = ss.str();
			pf= pf+str; // guarda el valor que tiene la variable
			continue;
		}

		if ((d>='0')&&(d<='9')) {
			pf.push_back(d);
		} else {
			while((!p->pilavacia())&&(prcd(p->tope(),d))) {
				p1=p->tope();
				p->desapilar();
				pf.push_back(' ');
				pf.push_back(p1);

			}
			if((p->pilavacia())||(d!=')')) {
				p->apilar(d);
				pf.push_back(' ');
			} else
				p->desapilar();
		}
	}
	while(!p->pilavacia()) {
		p1=p->tope();
		p->desapilar();
		pf.push_back(' ');
		pf.push_back(p1);
	}
	//cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;

	for(int i=0; (i<pf.length())&&(!error); ++i) {

		if(pf.at(i) == ' ') {
			continue;
		} else if(isdigit(pf.at(i))) {
			int num=0;
			//extract full number
			while(isdigit(pf.at(i))) {
				num = num * 10 + (int)(pf.at(i) - '0');
				i++;
			}
			i--;

			p->apilar(num);
		}

		else {

			int val2 = p->tope();
			p->desapilar();
			int val1 = p->tope();
			p->desapilar();

			switch (pf.at(i)) {
				case '<':
					p->apilar(val1 < val2);
					break;
				case '>':
					p->apilar(val1 > val2);
					break;
				case '!':
					p->apilar(val2 != val1);
					break;
				case '=':
					p->apilar(val2 == val1);
					break;

			}
		}

		//cout<<endl<<"\n\nResultado= "<<p->tope()<<endl;

	}
	return p->tope();
}

/* INT = 1
 IF = 2
 = = 3
 JUMP = 4
 SHOW = 5
 THEN = 6*/
int BuscarPalabra(string a) { // recorre el arreglo "a" de string pasado como parametro en busca de palabras clave
	if(a.find("INT")!= -1) return 1;
	if(a.find("IF") != -1) return 2;
	if(a.find("=") != -1) return 3;
	if(a.find("JUMP") != -1) return 4;
	if(a.find("SHOW") != -1) return 5;
	if(a.find("THEN") != -1) return 6;
	if(a.find("BOOL")!= -1) return 7;
	cout << " No se encontraron palabras clave" << endl;
	return -1;
}

//-----------------------------------------------------------

bool Lista::esvacia(void) {
	return czo->es_vacio();
}

tipolista Lista::cabeza(void) {
	if(esvacia()) {
		cout<<" Error, Cabeza de lista vacia";
		return -1;
	}
	return czo->get_dato();
}

Lista *Lista::resto(void) {
	Lista *l=new Lista(czo->get_next());
	return (l);
}

void Lista::concat(Lista *l1) {
	// le transfiere los datos de l1 a this
	if (!(l1->esvacia())) {
		this->addinstruccion(l1->cabezastr());
		this->concat(l1->resto());
	}
}
Lista *Lista::copy(void) {
	Lista *aux=new Lista();
	aux->concat(this);
	return aux;
}

int main() {
	int i=0, aux=0, inicio=0, fin=0;
	string a, c, f, instruccion;
	stringstream b,e;

	// Declaracion de listas para variables e instrucciones -------
	Lista *instr = new Lista(); // lista que almacena instrucciones
	Lista *var = new Lista(); // Lista que almacena variables
	Lista *auxlista = new Lista(); // Lista auxiliar que es copia de la lista de instrucciones

	// lectura y apertura del archivo------
	ifstream archivo;
	string temp;
	archivo.open("programa.txt", ios::in);
	while(getline(archivo,temp))
		instr->addinstruccion(temp);
	archivo.close();

	// ejecucion de instrucciones-------
	auxlista = instr->copy();// guardo una copia de la lista en una lista auxiliar para el JUMP hacia arriba
	while(!instr->esvacia()) { // ejecucion principal, mientras en la lista de instrucciones haya elementos

		instruccion = instr->cabezastr(); // extrae la instruccion a ejecutar
		i++; // contador de lineas del programa
		cout<<"Busco palabra clave en instruccion: "<<instruccion<<endl;
		switch(BuscarPalabra(instruccion)) {
			case 1: // CASO INT x
				var->addvar(ExtraeNombre(instruccion)); // Declara variable entera (INT)
				instr = instr->resto();
				break;
			case 2: // Caso IF
				for(int j=0; j<instruccion.length(); j++) {
					if(instruccion.at(j) == '(') inicio = j;
					if(instruccion.at(j) == ')') fin = j;
				}
				for(int k = inicio; k<=fin; k++)
					c.push_back(instruccion.at(k));

				f = instruccion.substr(instruccion.find("THEN")+4);

				if(EvaluaBooleano(var,c)) {
					switch(BuscarPalabra(f)) {
						case 3:// si hay que hacer una asignacion
							var->asignarValor(ExtraeNombre(f), EvaluaExpresion(var,f.substr(f.find("=") + 1)));
							instr = instr->resto();
							break;
						case 4:// si hay que hacer un jump
							a = f.substr(f.find("JUMP")+4); // extrae el numero luego del JUMP
							b.clear(); // limpio el buffer
							b << a;
							b >> aux; // conversion de string a integer

							if(i>aux) { // Si se quiere ir a una linea anterior a la actual, se debe iterar la lista "al reves"
								i=1; // coloco contador de lineas en 1
								instr = auxlista; // vuelvo al principio de la lista
							}

							while(i<aux) {
								instr = instr->resto();    // mientras no se llegue a la l�nea que pide en el JUMP, itera los nodos
								i++;
							}
							break;
						case 5: // si hay que mostrar alguna expresion aritmetica
							cout << endl << EvaluaExpresion(var,instruccion.substr(instruccion.find("SHOW") +1 )) << endl;
							instr = instr->resto();
							break;
					}
				} else {
					instr = instr->resto();
				}
				break;
			case 3: // Caso x = n
				var->asignarValor(ExtraeNombre(instruccion), EvaluaExpresion(var,instruccion.substr(instruccion.find("=") + 1)));
				instr = instr->resto();
				break;
			case 4: // Caso JUMP
				a = instruccion.substr(instruccion.find("JUMP")+4); // extrae el numero luego del JUMP
				b << a;
				b >> aux; // conversion de string a integer
				if(i>aux) { // Si se quiere ir a una linea anterior a la actual, se debe iterar la lista "al reves"
					i=1; // coloco contador de lineas en 1
					instr = auxlista; // vuelvo al principio de la lista
				}
				while(i<aux) {
					instr = instr->resto();    // mientras no se llegue a la l�nea que pide en el JUMP, itera los nodos
					i++;
				}
				break;
			case 5: // Caso SHOW
				cout << endl << EvaluaExpresion(var,instruccion.substr(instruccion.find("SHOW")+4)) << endl;
				instr = instr->resto();
				break;
			case 7: // Caso BOOL
				var->addvar(ExtraeNombre(instruccion)); // declara variable booleana (BOOL)
				instr = instr->resto();
				break;
			default:
				break;
		}
	}
	cout<<endl;
	//system("PAUSE");
	return 0;
}

