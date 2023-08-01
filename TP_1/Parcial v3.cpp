//#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <cstring>

using namespace std;

int i=0;

char extraeNombreVariable(string cadena) { // recorre el string pasado como parametro y extrae el nombre de la variable (de 'a' hasta 'z' inclusive)
	char n_variable;
	for(int i = 0; i<cadena.length() ; i++) {
		if( (cadena.at(i) >= 'a') && (cadena.at(i) <= 'z'))
			return n_variable = cadena.at(i);
	}
}
int search(string a) { // recorre el arreglo "a" de string pasado como parametro en busca de palabras clave
	if(a.find("INT")!= -1) return 1;
	if(a.find("IF") != -1) return 2;
	if(a.find("=") != -1) return 3;
	if(a.find("JUMP") != -1) return 4;
	if(a.find("SHOW") != -1) return 5;
	if(a.find("THEN") != -1) return 6;
	if(a.find("BOOL")!= -1) return 7;
	if(a.find("<") != -1)	return 8;
	cout << "No se encontraron palabras clave" << endl;
	return -1;
}

T EvaluaExpresion(Lista* var, string cadena){ // es el codigo de la clase practica puesto como funcion
    int error=0;
    Pila *p=new Pila();
    string pf;
for(int i=0;(i<cadena.length())&&(!error);i++){
          if (cadena.at(i)=='{') p->apilar('{');
          if (cadena.at(i)=='[') p->apilar('[');
          if (cadena.at(i)=='(') p->apilar('(');

          if (cadena.at(i)=='}'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='{') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==']'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='[') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==')'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='(') error=1;
                                     else p->desapilar();
          }
    }
    if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK"<<endl;
    else cout<<endl<<"ERROR";

    cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
	//conversion de entrefijo a posfijo
      char d,p1;

      for(int j=0;j<cadena.length();j++)
      {
	  	  d=cadena.at(j);

      	  if( (d>='a') && (d<='z') ){ // si se encuentra una variable en la expresion

			tipolista a = var->ExtraeValorEntero(d);
			stringstream ss;
			ss << a;
			string str = ss.str();
            pf= pf+str; // guarda el valor que tiene la variable
            continue;
	      }

	      if ((d>='0')&&(d<='9')){
             	pf.push_back(d);
		}
		  else
	         {
			 	while((!p->pilavacia())&&(prcd(p->tope(),d)))
	                {
						p1=p->tope();
						p->desapilar();
						pf.push_back(' ');
						pf.push_back(p1);

					}
	           if((p->pilavacia())||(d!=')')){
	           			p->apilar(d);
	           			pf.push_back(' ');
			   }

		       else
			   		p->desapilar();
	      }
      }
      while(!p->pilavacia())
	      {
		  	p1=p->tope();
			p->desapilar();
			pf.push_back(' ');
			pf.push_back(p1);
		}

      cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;

// Evaluacion de la expresion en posfijo
  //int o1,o2;

  for(int i=0;(i<pf.length())&&(!error);++i){

     if(pf.at(i) == ' ')
	 	continue;

     else if(isdigit(pf.at(i))){

     	int num=0;
     	//extract full number
     	while(isdigit(pf.at(i)))
			{
			num = num * 10 + (int)(pf.at(i) - '0');
				i++;
			}
			i--;

			p->apilar(num);
	 }

	 else{

	 		int val1 = p->tope();
	 		p->desapilar();
			int val2 = p->tope();
			p->desapilar();

			switch (pf.at(i))
			{
			case '+': p->apilar(val2 + val1); break;
			case '-': p->apilar(val2 - val1); break;
			case '*': p->apilar(val2 * val1); break;
			case '/': p->apilar(val2/val1); break;

			}
	}

  }
  cout<<endl<<"\n\nResultado= "<<p->tope()<<endl;
  return p->tope();
}

bool EvaluaBooleano(Lista* var, string cadena){ // es el codigo de la clase practica puesto como funcion
    int error=0;
    Pila *p=new Pila();
    string pf;
for(int i=0;(i<cadena.length())&&(!error);i++){
          if (cadena.at(i)=='{') p->apilar('{');
          if (cadena.at(i)=='[') p->apilar('[');
          if (cadena.at(i)=='(') p->apilar('(');

          if (cadena.at(i)=='}'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='{') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==']'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='[') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==')'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='(') error=1;
                                     else p->desapilar();
          }
    }
    if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK"<<endl;
    else cout<<endl<<"ERROR";

    //cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo
      char d,p1;
      /*;
*/
/*for(int j=0;j<cadena.length();j++)
  {
  	  d=cadena.at(j);

  	  if( (d>='a') && (d<='z') ){ // si se encuentra una variable en la expresion
		tipolista a = var->ExtraeValorEntero(d);
		stringstream ss;
		ss << a;
		string str = ss.str();
        pf= pf+str; // guarda el valor que tiene la variable
        continue;
      }

      if ((d>='0')&&(d<='9')){
         	pf.push_back(d);
	}
	  else
         {
		 	while((!p->pilavacia())&&(prcd(p->tope(),d)))
                {
					p1=p->tope();
					p->desapilar();
					pf.push_back(' ');
					pf.push_back(p1);

				}
           if((p->pilavacia())||(d!=')')){
           			p->apilar(d);
           			pf.push_back(' ');
		   }
	       else
		   		p->desapilar();
      }
  }
  while(!p->pilavacia())
      {
	  	p1=p->tope();
		p->desapilar();
		pf.push_back(' ');
		pf.push_back(p1);
	}
  //cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;

for(int i=0;(i<pf.length())&&(!error);++i){

 if(pf.at(i) == ' ')
 	continue;

 else if(isdigit(pf.at(i))){

 	int num=0;
 	//extract full number
 	while(isdigit(pf.at(i)))
		{
		num = num * 10 + (int)(pf.at(i) - '0');
			i++;
		}
		i--;

		p->apilar(num);
 }

 else{

 		int val2 = p->tope();
 		p->desapilar();
		int val1 = p->tope();
		p->desapilar();

		switch (pf.at(i))
		{
		case '<': p->apilar(val1 < val2);break;
		case '>': p->apilar(val1 > val2); break;
		case '!': p->apilar(val2 != val1); break;
		case '=': p->apilar(val2 == val1); break;

		}
}

//cout<<endl<<"\n\nResultado= "<<p->tope()<<endl;

}
return p->tope();
}*/


/*	La clase instruccion almacena objetos que son líneas del codigo que se quiere leer.
*   Al crearse un nuevo objeto, se inicializa el string que almacena la instruccion.
*   El metodo ejecutar() será reescrito en cada una de las sub clases.
*
*/
class Instruccion {
	private:
		string linea;
	public:
		Instruccion() {
			linea="";
		}
		Instruccion(string a) {
			this->linea = a;
		}
		string getInstruccion() {
			return linea;
		}; // getInstruccion devuelve la cabeza de la lista de instrucciones
		void setInstruccion(string ins) {
			linea = ins;
		}; // setInstruccion agrega una nueva instruccion (en orden)
		void ejecutar();

		char extraeNombreVariable(string cadena) { // recorre el string pasado como parametro y extrae el nombre de la variable (de 'a' hasta 'z' inclusive)
			char n_variable;
			for(int i = 0; i<cadena.length() ; i++) {
				if( (cadena.at(i) >= 'a') && (cadena.at(i) <= 'z'))
					return n_variable = cadena.at(i);
			}
		}
};

class Variable {
	private:
		char nombre; // un char que identifica el nombre de la variable
		long int valor; // Si es una variable booleana, guarda 1 en caso de ser true, y 0 en caso de ser false
		string tipo; // tipo de variable, si es INT, tipo="entero", si es BOOL, tipo="booleano"
	public:
		Variable() {
			this->nombre=' ';
			this->valor=0;
			this->tipo="";
		}
		Variable(char b, long int c, string d) {
			this->nombre = b;
			this->valor = c;
			this->tipo = d;
		}
		Variable(char b) {
			this->nombre = b;
			this->valor = 0;
			this->tipo = "";
		}
		//~Variable();
		char getNombre() {
			return this->nombre;
		}
		long int getValor() {
			return this->valor;
		}
		string getTipo() {
			return this->tipo;
		}
		void setNombre(char a) {
			this->nombre=a;
		}
		void setValor(long int v) {
			this->valor=v;
		}
		void setTipo(string t) {
			this->tipo = t;
		}
};

template <class T> class Nodo {
	private:
		T dato;
		//tipolistabol bolean;
		//char nombre; // nombre que tendra la variable
		//bool estado; // si la variable es booleana, en este atributo se guarda si es true o false.
		//Instruccion comandos;  // objeto Instruccion que almacena las lineas del codig
		//Variable varia;
		//string tipo; // cadena que almacena el tipo de instruccion (INT o BOOL)
		Nodo *next;
	public:
		Nodo() {
			next=NULL;
		};
		Nodo(T a) {
			dato=a;
			next=NULL;
		};
		//Nodo(string cadena) { comandos = cadena; next=NULL;} // Constructor para inicializar Nodos en la lista de instrucciones
		//Nodo(char a, long int c, string d) {Variable(a,c,d); next=NULL;} // Constructor para inicializar Nodos en la lista de variables
		//void set_datoEnt(T a) {dato=a; };
		//void set_tipo(string b) { tipo=b;} ;
		void set_next(Nodo *n) {
			next=n;
		};
		//tipolista get_datoEnt() {return dato; }; // devuelve el dato (entero o booleano)
		//string get_tipo() {return tipo;} ; // agregado: devuelve el tipo (INT o BOOL) en forma de string
		//char get_nombre() {return nombre;};
		//string get_instr() {return comandos.getInstruccion();};
		T get_dato() {
			return dato;
		};
		Nodo *get_next() {
			return next;
		};
		bool es_vacio() {
			return next==NULL;
		}
};

template <class T> class Lista {
	private:
		Nodo<T> *czo;
	public:
		Lista() {
			czo=new Nodo<T>();
		};
		Lista(Nodo<T>* n) {
			czo=n;
		};
		void del(void);
		void add(T d);
		void addVar(T var); // crea un nuevo nodo que contiene la variable, definida por su nombre y un valor
		void addInstruccion(T ins); // crea un nuevo nodo que contiene la instruccion, que es pasada como parametro (string)
		T buscarVariable(char a); // Busca en la lista de variables la variable correspondiente al char pasado como parametro
		//void asignarValorEntero(char, tipolista);
		bool esvacia(void);
		T cabeza(void);
		//char cabezavar(void);
		//string cabezastr(void); // devuelve la cabeza de la lista de instrucciones (como tipo string)
		Lista *resto(void); //retorna el puntero al "resto" de la lista
		//resto= lo que queda de la lista sin la cabeza
		void concat(Lista *l1);
		Lista *copy(void);
		string toPrint(string p);
		void impre(void);
};

template <class T>class Pila:public Lista<T> {
	public:
		Pila() {
			Lista<T>();
		};
		void apilar(T x) {
			this->add(x);
		};
		T tope(void) {
			return this->cabeza();
		};
		void desapilar(void) {
			this->del();
		};
		bool pilavacia() {
			return this->esvacia();
		};
};

/*	Esta clase en su metodo ejecutar, declara una variable nueva
*   y la agrega a una lista
*
*/
class Declaracion:public Instruccion {
	private:
		string declaracion;
	public:
		// Constructores
		Declaracion() {
			this->declaracion="";
		};
		Declaracion(string linea) {
			this->declaracion=linea;
		};
		~Declaracion();
		// Metodos
		string getDeclaracion() {
			return this->declaracion;
		}
		void ejecutar(Lista<Variable> *variables, Lista<Instruccion> *instrucciones, int &i) {
			Variable *v = new Variable(extraeNombreVariable(this->getDeclaracion())); // Creo la variable con su nombre
			variables->add(*v); // Añado la variable a la lista de variables.
			if(search(this->getDeclaracion())==1) // Determino el tipo de la variable.Si es INT, setea tipo "entero". Si es BOOL, setea tipo "booleano"
				v->setTipo("entero");
			else if(search(this->getDeclaracion())==7)
				v->setTipo("booleano");
			i++;

			cout << endl << v->getTipo() << endl;
		}
};

/*	La clase instruccion almacena asigna una variable existente, su valor
*
*
*/
class Asignacion:public Instruccion {
	private:
		string linea;
	public:
		// Constructores
		Asignacion() {
			this->linea = "";
		};
		Asignacion(string linea) {
			this->linea = linea;
		};
		~Asignacion();
		//Metodos
		string getAsignacion() {
			return this->linea;
		}
		void ejecutar(Lista<Variable> *variables, Lista<Instruccion> *instrucciones, int i) {

			string s = this->getAsignacion().substr(this->getAsignacion().find("=")+1); // Extrae lo que haya a la derecha del signo =.
			//Variable *h = new Variable();
			//*h = variables->buscarVariable(extraeNombreVariable(this->getAsignacion()));
			//cout << endl << "h->getTipo() es: " << h->getTipo() << endl;
			//cout << endl << "h->getNombre() es: " << h->getNombre() << endl;

			//variables->asignarValor(extraeNombreVariable(this->getAsignacion()), EvaluaExpresion(var,instruccion.substr(instruccion.find("=") + 1)));
			i++;
		}

};

/*	Esta clase (en su metodo ejecutar) evalua lo que está dentro del paréntesis del IF, y devuelve true o false
*
*
*/
class Condicional:public Instruccion {
	private:
		string condicional;
		string getCondicional() {
			return this->condicional;
		}
	public:
		Condicional() {
			this->condicional="";
		};
		Condicional(string c) {
			this->condicional = c;
		};
		void ejecutar(Lista<Variable> *variables, Lista<Instruccion> *instrucciones, int i) {
			// parsear lo que esta dentro del parentesis
			// llamar a la funcion search en busca de operadores relacionales
			// Si hay operadores, evaluar la expresion
			// Si no hay operadores relacionales, buscar valor de la variable (antes buscar el char)
			i++;
		}
};

/* Esta clase altera la secuencia de ejecucion del programa
*/
class Salto:public Instruccion {
	private:
		string salto;
	public:
		Salto() {
			this->salto ="";
		};
		Salto(string jump) {
			this->salto = jump;
		};
		string getSalto() {
			return this->salto;
		};
		void ejecutar(Lista<Variable> *variables, Lista<Instruccion> *instrucciones, Lista<Instruccion> *listaaux, int &i) {
			stringstream b,e;
			string a;
			int aux=0;

			a = getSalto().substr(getSalto().find("JUMP")+4); // extrae el numero luego del JUMP
			b << a;
			b >> aux; // conversion de string a integer
			cout << "i es: " << i << " - aux es: " << aux << endl;
			if(i>aux) { // Si se quiere ir a una linea anterior a la actual, se debe iterar la lista "al reves"
				i=1; // coloco contador de lineas en 1
				instrucciones = listaaux; // vuelvo al principio de la lista
			}
			while(i<aux) {
				instrucciones = instrucciones->resto();    // mientras no se llegue a la línea que pide en el JUMP, itera los nodos*/
				i++;
			}
		}
};

class Show:public Instruccion {
	private:
		string mostrar;
	public:
		Show() {
			this->mostrar = "";
		};
		Show(string show) {
			this->mostrar = show;
		};
		string getMostrar() {
			return this->mostrar;
		};
		void ejecutar(Lista<Variable> *variables, Lista<Instruccion> *instrucciones, int i) {
			// parsear lo que esta luego del SHOW
			// preguntar por operadores relacionales o aritmeticos
			// Si no hay operadores de ningun tipo, buscar el valor de la variable en la lista de variables
			// llamar a evaluarexpresion o evaluabooleano
			// cout del resultado
		}
};

template <class T> T Lista<T>::buscarVariable(char n) { // busca la variable en la lista de variables a partir de su nombre, y retorna su valor como tipolista
	if(this->esvacia()) {
		cout<<" Error, variable " << n << " no declarada";
		//return '\0';
		return -1;
	}

	Variable *aux = new Variable(); // Variable auxiliar para comparar
	*aux=this->cabeza();

	if(n == aux->getNombre()) {
		return this->cabeza();
	} else
		return resto()->buscarVariable(n);
}

/*template <class T>void Lista<T>::del(void)
{    //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}*/

template <class T> void Lista<T>::add(T d) { // Añade nodos a la lista, como si fuera una pila LIFO
	Nodo<T>* nuevo = new Nodo<T>(d);
	nuevo->set_next(czo);
	czo = nuevo;
}
template <class T> void Lista<T>::addInstruccion(T d) { // añade las instrucciones a la lista de instrucciones pero en forma "ordenada", es decir, primero se agrega la primer linea del txt, luego la segunda, y así
	Nodo<T> *nuevo=new Nodo<T>(d);

	if(esvacia()) {
		nuevo->set_next(czo);
		czo=nuevo;
	} else {
		Nodo<T> *aux = new Nodo<T>(); // se crea un nodo auxiliar
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

// métodos creados para el parcial---------------------------

/*char extraeNombreVariable(string cadena){ // recorre el string pasado como parametro y extrae el nombre de la variable (de 'a' hasta 'z' inclusive)
     char n_variable;
     for(int i = 0; i<cadena.length() ; i++){
        if( (cadena.at(i) >= 'a') && (cadena.at(i) <= 'z'))
            return n_variable = cadena.at(i);
     }
}*/
/*long int Lista<T>::extraeValor(char n){ // busca la variable en la lista de variables a partir de su nombre, y retorna su valor como tipolista
    char b;
    if(esvacia()){
        cout<<" Error, variable " << n << " no declarada";
        //return '\0';
        return -1;
        }
    if(n == czo->get_nombre()){
        T valor = czo->get_datoEnt(); // recupero el valor de la variable
        //return b = a+'0'; // conversion del integer a char
        return valor;
    }else
        return resto()->ExtraeValorEntero(n);
}

tipolistabol Lista::ExtraeValorBoleano(char n){ // busca la variable en la lista de variables a partir de su nombre, y retorna su valor como tipolista
    char b;
    if(esvacia()){
        cout<<" Error, variable " << n << " no declarada";
        //return '\0';
        return -1;
        }
    if(n == czo->get_nombre()){
        tipolistabol a = czo->get_datoBol(); // recupero el valor booleano de la variable
        //return b = a+'0'; // conversion del integer a char
        return a;
    }else
        return resto()->ExtraeValorBoleano(n);
}

void Lista::addVar(char n, string b){ // añade (o inicializa) una variable en la lista de variables (utiliza otro constructor de nodo)
     Nodo *nuevo=new Nodo(n);
     nuevo->set_next(czo);
     nuevo->set_tipo(b);
     czo=nuevo;
}
void Lista::addInstruccion(string cadena){ // añade las instrucciones a la lista de instrucciones pero en forma "ordenada", es decir, primero se agrega la primer linea del txt, luego la segunda, y así
     Nodo *nuevo=new Nodo(cadena);

     if(esvacia()){
        nuevo->set_next(czo);
        czo=nuevo;
     }else{
            Nodo *aux = new Nodo(); // se crea un nodo auxiliar
            aux = czo;
           if(aux->get_next()->get_next() == NULL){ // si hay un solo nodo
                nuevo->set_next(aux->get_next());
                aux->set_next(nuevo);
           }
           else{ // sino, itera hasta encontrar la posicion correcta
                while(aux->get_next()->get_next() != NULL) aux=aux->get_next();
                    if(aux->get_next()->get_next() == NULL){
                        nuevo->set_next(aux->get_next());
                        aux->set_next(nuevo);
                    }
           }
        }
}*/
/*template <class T> void Lista<T>::asignarValor(char n, T valor){ // asigna el valor a una variable de la lista que es pasada como parametro junto con el valor
    if(esvacia())
        cout << "Error, Lista vacia";

// Acá tengo que preguntar si la varable es INT o BOOL, para saber qué set tengo que usar

    if(n == czo->get_nombre()){ // si se encuentra la variable en la lista, asigna el valor pasado como parametro
        czo->set_datoEnt(valor);
		}
    else return this->resto()->asignarValor(n,valor);

}
/*
string Lista::cabezastr(void){ // retorna la cabeza de la lista de instrucciones
    if(esvacia()){
                cout<<" Error, Cabeza de lista vacia1";
                return NULL;
    }
    return czo->get_instr();
}

char Lista::cabezavar(void){ // retorna la cabeza de la lista de variables
    if(esvacia()){
                cout<<" Error, Cabeza de lista vacia2";
                return '\0';
    }
    return czo->get_nombre();
}

tipolista EvaluaExpresion(Lista* var, string cadena){ // es el codigo de la clase practica puesto como funcion
    int error=0;
    Pila *p=new Pila();
    string pf;
for(int i=0;(i<cadena.length())&&(!error);i++){
          if (cadena.at(i)=='{') p->apilar('{');
          if (cadena.at(i)=='[') p->apilar('[');
          if (cadena.at(i)=='(') p->apilar('(');

          if (cadena.at(i)=='}'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='{') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==']'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='[') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==')'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='(') error=1;
                                     else p->desapilar();
          }
    }
    if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK"<<endl;
    else cout<<endl<<"ERROR";

    cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo
      char d,p1;

      for(int j=0;j<cadena.length();j++)
      {
	  	  d=cadena.at(j);

      	  if( (d>='a') && (d<='z') ){ // si se encuentra una variable en la expresion

			tipolista a = var->ExtraeValorEntero(d);
			stringstream ss;
			ss << a;
			string str = ss.str();
            pf= pf+str; // guarda el valor que tiene la variable
            continue;
	      }

	      if ((d>='0')&&(d<='9')){
             	pf.push_back(d);
		}
		  else
	         {
			 	while((!p->pilavacia())&&(prcd(p->tope(),d)))
	                {
						p1=p->tope();
						p->desapilar();
						pf.push_back(' ');
						pf.push_back(p1);

					}
	           if((p->pilavacia())||(d!=')')){
	           			p->apilar(d);
	           			pf.push_back(' ');
			   }

		       else
			   		p->desapilar();
	      }
      }
      while(!p->pilavacia())
	      {
		  	p1=p->tope();
			p->desapilar();
			pf.push_back(' ');
			pf.push_back(p1);
		}

      cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;

// Evaluacion de la expresion en posfijo
  //int o1,o2;

  for(int i=0;(i<pf.length())&&(!error);++i){

     if(pf.at(i) == ' ')
	 	continue;

     else if(isdigit(pf.at(i))){

     	int num=0;
     	//extract full number
     	while(isdigit(pf.at(i)))
			{
			num = num * 10 + (int)(pf.at(i) - '0');
				i++;
			}
			i--;

			p->apilar(num);
	 }

	 else{

	 		int val1 = p->tope();
	 		p->desapilar();
			int val2 = p->tope();
			p->desapilar();

			switch (pf.at(i))
			{
			case '+': p->apilar(val2 + val1); break;
			case '-': p->apilar(val2 - val1); break;
			case '*': p->apilar(val2 * val1); break;
			case '/': p->apilar(val2/val1); break;

			}
	}

  }
  cout<<endl<<"\n\nResultado= "<<p->tope()<<endl;
  return p->tope();
}

bool EvaluaBooleano(Lista* var, string cadena){ // es el codigo de la clase practica puesto como funcion
    int error=0;
    Pila *p=new Pila();
    string pf;
for(int i=0;(i<cadena.length())&&(!error);i++){
          if (cadena.at(i)=='{') p->apilar('{');
          if (cadena.at(i)=='[') p->apilar('[');
          if (cadena.at(i)=='(') p->apilar('(');

          if (cadena.at(i)=='}'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='{') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==']'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='[') error=1;
                                     else p->desapilar();
          }
          if (cadena.at(i)==')'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='(') error=1;
                                     else p->desapilar();
          }
    }
    if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK"<<endl;
    else cout<<endl<<"ERROR";

    //cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo
      char d,p1;
      /*;
*/
/*for(int j=0;j<cadena.length();j++)
  {
  	  d=cadena.at(j);

  	  if( (d>='a') && (d<='z') ){ // si se encuentra una variable en la expresion
		tipolista a = var->ExtraeValorEntero(d);
		stringstream ss;
		ss << a;
		string str = ss.str();
        pf= pf+str; // guarda el valor que tiene la variable
        continue;
      }

      if ((d>='0')&&(d<='9')){
         	pf.push_back(d);
	}
	  else
         {
		 	while((!p->pilavacia())&&(prcd(p->tope(),d)))
                {
					p1=p->tope();
					p->desapilar();
					pf.push_back(' ');
					pf.push_back(p1);

				}
           if((p->pilavacia())||(d!=')')){
           			p->apilar(d);
           			pf.push_back(' ');
		   }
	       else
		   		p->desapilar();
      }
  }
  while(!p->pilavacia())
      {
	  	p1=p->tope();
		p->desapilar();
		pf.push_back(' ');
		pf.push_back(p1);
	}
  //cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;

for(int i=0;(i<pf.length())&&(!error);++i){

 if(pf.at(i) == ' ')
 	continue;

 else if(isdigit(pf.at(i))){

 	int num=0;
 	//extract full number
 	while(isdigit(pf.at(i)))
		{
		num = num * 10 + (int)(pf.at(i) - '0');
			i++;
		}
		i--;

		p->apilar(num);
 }

 else{

 		int val2 = p->tope();
 		p->desapilar();
		int val1 = p->tope();
		p->desapilar();

		switch (pf.at(i))
		{
		case '<': p->apilar(val1 < val2);break;
		case '>': p->apilar(val1 > val2); break;
		case '!': p->apilar(val2 != val1); break;
		case '=': p->apilar(val2 == val1); break;

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
/*int search(string a){ // recorre el arreglo "a" de string pasado como parametro en busca de palabras clave
    if(a.find("INT")!= -1) return 1;
    if(a.find("IF") != -1) return 2;
    if(a.find("=") != -1) return 3;
    if(a.find("JUMP") != -1) return 4;
    if(a.find("SHOW") != -1) return 5;
    if(a.find("THEN") != -1) return 6;
	if(a.find("BOOL")!= -1) return 7;
    cout << "No se encontraron palabras clave" << endl;
    return -1;
}*/

//-----------------------------------------------------------

template <class T>bool Lista<T>::esvacia(void) {
	return czo->es_vacio();
}

template <class T>T Lista<T>::cabeza(void) {
	/* if (this->esvacia()) {
	       cout << " Error, Cabeza de lista vacia";
	       return NULL;
	   }*/
	return czo->get_dato();
}

template <class tipolista> Lista<tipolista> *Lista<tipolista>::resto(void) {
	Lista *l=new Lista(czo->get_next());
	return (l);
}

template <class T> void Lista<T>::concat(Lista<T>* l1) {
	// le transfiere los datos de l1 a this
	if (!(l1->esvacia())) {
		this->concat(l1->resto());
		this->add(l1->cabeza());
	}
}

template <class T> Lista<T>* Lista<T>::copy(void) {
	Lista<T>* aux = new Lista();
	aux->concat(this);
	return aux;
}

int main() {

	int i=0, aux=0, inicio=0, fin=0;
	string a, c, f, instruccionNext;
	stringstream b,e;

	// Declaración de listas para variables e instrucciones -------

	Lista<Instruccion> *instrucciones = new Lista<Instruccion>(); // lista que almacena instrucciones
	Lista<Variable> *var = new Lista<Variable>(); // Lista que almacena variables
	Lista<Instruccion> *auxlista = new Lista<Instruccion>(); // Lista auxiliar (copia de la lista de instrucciones)

	// lectura y apertura del archivo------

	ifstream archivo;
	string temp;
	archivo.open("programa - copia.txt", ios::in);
	while(getline(archivo,temp)) {
		Instruccion *i = new Instruccion(temp);
		instrucciones->addInstruccion(*i);
	}
	archivo.close();

	// ejecucion de instrucciones-------
	auxlista = instrucciones->copy();// guardo una copia de la lista en una lista auxiliar para el JUMP hacia arriba

	// Itero la lista de instrucciones
	Instruccion *comando = new Instruccion(); // Iterador para recorrer la lista
	while(!instrucciones->esvacia()) {
		*comando = instrucciones->cabeza();
		switch(search(comando->getInstruccion())) {
			case 1: {
				Declaracion *d = new Declaracion(comando->getInstruccion());
				d->ejecutar(var,instrucciones,i);
				//Variable *h = new Variable();

				//*h=var->cabeza();

				//cout << endl << "nombre:" << h->getNombre();
				//cout << endl << "tipo:" << h->getTipo();
				instrucciones = instrucciones->resto();
				break;
			}
			//case 2: //Condicional *c = new Condicional(comando->getInstruccion());
			//c->ejecutar(*var,comando->getInstruccion());

			//instr = instr->resto();*/
			case 3: {
				Asignacion *a = new Asignacion(comando->getInstruccion());
				//a->ejecutar(var,instrucciones,i);
				cout << "asignacion" << endl;
				instrucciones = instrucciones->resto();
				break;
			}
			case 4: {
				Salto *s = new Salto(comando->getInstruccion());
				cout << "estoy haciendo un jump" << endl;
				s->ejecutar(var,instrucciones,auxlista,i);
				break;
			}
			//case 5:
			//case 6:
			case 7: {
				Declaracion *d = new Declaracion(comando->getInstruccion());
				d->ejecutar(var,instrucciones,i);
				cout << endl << "i en switch es: " << i << endl;
				instrucciones = instrucciones->resto();
				break;
			}

			default:
				break;
		}

	}
	/*Variable *h = new Variable();
	*h=var->cabeza();
	cout << h->getNombre();
	*h=var->resto()->cabeza();
	cout << h->getNombre();*/

	// ejecucion de instrucciones-------

	/*while(!instr->esvacia()){ // ejecucion principal, mientras en la lista de instrucciones haya elementos

	nextInstruccion = instr->getInstruccion(); // extrae la instruccion a ejecutar
	i++; // contador de lineas del programa
	    switch(buscarPalabra(instruccion)){
	        case 1: var->addvar(ExtraeNombre(instruccion)); // declara variable entera (INT)
	                instr = instr->resto();
	                break;
	        case 2: for(int j=0; j<instruccion.length(); j++){
	                    if(instruccion.at(j) == '(') inicio = j;
	                    if(instruccion.at(j) == ')') fin = j;
	                }
	                for(int k = inicio;k<=fin;k++)
	                    c.push_back(instruccion.at(k));

	                f = instruccion.substr(instruccion.find("THEN")+4);

	                if(EvaluaBooleano(var,c)){
	                  switch(buscarPalabra(f)){
	                        case 3:// si hay que hacer una asignacion
	                                var->asignarValor(ExtraeNombre(f), EvaluaExpresion(var,f.substr(f.find("=") + 1)));
	                                instr = instr->resto();
	                                break;
	                        case 4:// si hay que hacer un jump
	                                a = f.substr(f.find("JUMP")+4); // extrae el numero luego del JUMP
	                                b.clear(); // limpio el buffer
	                                b << a; b >> aux; // conversion de string a integer

	                                if(i>aux){ // Si se quiere ir a una linea anterior a la actual, se debe iterar la lista "al reves"
	                                    i=1; // coloco contador de lineas en 1
	                                    instr = auxlista; // vuelvo al principio de la lista
	                                }

	                                while(i<aux){instr = instr->resto(); i++;} // mientras no se llegue a la línea que pide en el JUMP, itera los nodos
	                                break;
	                        case 5: // si hay que mostrar alguna expresion aritmetica
	                                cout << endl << EvaluaExpresion(var,instruccion.substr(instruccion.find("SHOW") +1 )) << endl;
	                                instr = instr->resto();
	                                break;
	                        }
	                }
	                else{instr = instr->resto();}
	                break;
	        case 3: var->asignarValor(ExtraeNombre(instruccion), EvaluaExpresion(var,instruccion.substr(instruccion.find("=") + 1)));
	                instr = instr->resto();
	                break;
	        case 4: a = instruccion.substr(instruccion.find("JUMP")+4); // extrae el numero luego del JUMP
	                b << a; b >> aux; // conversion de string a integer
	                if(i>aux){ // Si se quiere ir a una linea anterior a la actual, se debe iterar la lista "al reves"
	                    i=1; // coloco contador de lineas en 1
	                    instr = auxlista; // vuelvo al principio de la lista
	                }
	                while(i<aux){instr = instr->resto(); i++;} // mientras no se llegue a la línea que pide en el JUMP, itera los nodos
	                break;
	        case 5: cout << endl << EvaluaExpresion(var,instruccion.substr(instruccion.find("SHOW")+4)) << endl;
	                instr = instr->resto();
	                break;
	        case 7: var->addvar(ExtraeNombre(instruccion)); // declara variable booleana (BOOL)
	                instr = instr->resto();
	                break;
	        default: break;
	    }*/

	//}

	cout<<endl;
//system("PAUSE");
	return 0;
}
