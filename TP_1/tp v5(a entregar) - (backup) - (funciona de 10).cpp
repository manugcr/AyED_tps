/*Copyright (C) 2022 <Bruno Guglielmotti, Franco Rodriguez, Agustin Pallardó> 
This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published bythe Free Software
Foundation, either version 3 of the License, or at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with
this program.  If not, see LICENSE.txt or <http://www.gnu.org/licenses/>. */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;


//------------------------------------------------------------------------------------------//
//---------------------------CLASE VARIABLE-------------------------------------------------//
//------------------------------------------------------------------------------------------//
class Variable{
    private:
        int dato;//se empleara para aquellos que sean de tipo bool 0 para false y 1 para true
        string tipo;
        char nomb;
    public:
        Variable(){};//constructor sin parametros
        Variable(int d, string t, char n);//constructor del objeto
        ~Variable();

        void set_nomb(char n);
        void set_tipo(string t);
        void set_dato(int d);

        string get_tipo();
        char get_nomb();
        int get_dato();
};//fin de la clase variable

//implementacion de metodos de los objetos variable

Variable::Variable(int d, string t, char n){
    set_nomb(n);
    set_tipo(t);
    set_dato(d);
    cout<<"Objeto variable creado con exito"<<endl;
}

Variable::~Variable(){
}

void Variable::set_nomb(char n){
    nomb=n;
}

void Variable::set_tipo(string t){
    tipo=t;
}

void Variable::set_dato(int d){
    dato=d;
}

char Variable::get_nomb(){
    return nomb;
}

string Variable::get_tipo(){
    return tipo;
}

int Variable::get_dato(){
    return dato;
}
//----------------FIN CLASE VARIABLE E IMPLEMENTACIONES DE LA MISMA------------------------//
//-----------------------------------------------------------------------------------------//



//------------------------------------------------------------------------------------------//
//---------------------------CLASE INSTRUCCION----------------------------------------------//
//------------------------------------------------------------------------------------------//
class Instruccion{
    protected:
        string dato;//se empleara para aquellos que sean de tipo bool 0 para false y 1 para true
        int indice;//#################################################################################
    public:
        Instruccion(string t);//constructor del objeto
        ~Instruccion();

        void set_instruct(string d);
        string get_instruct();
        void ejecutar();
        string toStringDato(); //metodo para imprimir la instruccion
};//fin de la clase variable

//implementacion de los objetos variable
Instruccion::Instruccion(string d){
    set_instruct(d);
}

Instruccion::~Instruccion(){
}

void Instruccion::set_instruct(string d){
    dato=d;
}

string Instruccion::get_instruct(){
    return dato;
}

void Instruccion::ejecutar(){  
}

string Instruccion::toStringDato(){
    return "La instruccion es: "+dato;
}

//----------------FIN CLASE INSTRUCCION E IMPLEMENTACIONES DE LA MISMA---------------------//
//-----------------------------------------------------------------------------------------//


//---------------------------CLASE NODO----------------------------------------------------//
template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo(){ 
        next = NULL; 
    };
    Nodo(T a){
        dato = a; 
        next = NULL; 
    };
    void set_dato(T a){ 
        dato = a; 
    };
    void set_next(Nodo* n){ 
        next = n; 
    };
    T get_dato(){ 
        return dato; 
    };
    Nodo* get_next(){ 
        return next; 
    };
    bool es_vacio(){ 
        return next == NULL; 
    }
};
//---------------------FIN CLASE NODO E IMPLEMENTACIONES DE LA MISMA-----------------------//




//------------------------------------------------------------------------------------------//
//---------------------------CLASE LISTA----------------------------------------------------//
//------------------------------------------------------------------------------------------//
template <class T> class Lista {
private:
    void addO(T d, Nodo<T>* ant);
    void borrarD(T d, Nodo<T>* ant);
public:
    Nodo<T>* czo; //publico para poder acceder a el en el metodo "modif_nomb"

    Lista(){ 
        czo = new Nodo<T>(); 
    };
    Lista(Nodo<T>* n){ 
        czo = n; 
    };
    //~Lista(void);
    void add(T d); //sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void); //retorna el dato del primer nodo
    Lista* resto(void); //retorna el puntero al "resto" de la lista
                        //resto= lo que queda de la lista sin la cabeza
    string toPrint();
    void impre(void);
    T suma(T i);
    int  size();
    bool esta(T d);// detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); }//borra el nodo que contiene d
    void borrar(void); //borra la cabeza
    void borrar_last();//borra el ultimo
    void concat(Lista<T>* l1);// le transfiere los datos de l1 a this
    Lista<T>* copy(void);// hace una copia de la lista
    void inicio(int n);//deja "vivos" los n primeros nodos y borra el resto
    void addOrdenado(T d) { addO(d, NULL); }; //sumar nodos a la lista Ordenados de menor a MAYOR
    T last(); //retorna el dato del ultimo nodo
    void final(int n);//descarta los n primeros nodos de la lista
    T get(int n);//devuelve el nodo en la posición n de la lista
};
template <class T>
T Lista<T>::last()
{
    if (!this->esvacia()) {
        if (this->resto()->esvacia()){
            return this->cabeza();
        }
        return this->resto()->last();
    }return 0;
}

template <class T>
void Lista<T>::add(T d) //100
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
T Lista<T>::cabeza(void){
    
    return czo->get_dato();
}

template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}

template <class T>
string Lista<T>::toPrint()
{
    if (this->esvacia()) {
        return "";
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << " - " << this->resto()->toPrint() << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}

template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
}

template <class T> int Lista<T>::size()
{
    if (this->esvacia()){
        return 0;
    }
    return 1 + this->resto()->size();
}

template <class T> void Lista<T>::borrar(void)
{ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}

template <class T> void Lista<T>::borrar_last(){ // borra el ultimo nodo
    if (!this->esvacia()) {
        if ((czo->get_next())->get_next() == NULL) {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else this->resto()->borrar_last();
    }
}

template <class T> void Lista<T>::concat(Lista<T>* l1){// le transfiere los datos de l1 a this
    if (!(l1->esvacia())){
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}

template <class T> Lista<T>* Lista<T>::copy(void)
{
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}

template <class T> void Lista<T>::inicio(int n)
{ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrar_last();
        this->inicio(n);
    }
}

template <class T> void Lista<T>::final(int n){
    //descarta los primeros n nodos de la lista
    if(n>0){
        this->borrar();
        this->final(n-1);
    }
}

template <class T> T Lista<T>::get(int n){
    //devuelve el elemento en la posición n de la lista
    this->final(n-1);
    return this->cabeza();
}

template <class T> void Lista<T>::impre(void)
{
    Nodo<T>* aux;
    aux = czo;
    while (aux->get_next() != NULL) {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}

template <class T>
void Lista<T>::addO(T d, Nodo<T>* ant)
{
    if (this->esvacia()) {//el primero
        this->add(d);
    }
    else {
        if (d < czo->get_dato()) {
            if (ant == NULL) {//al principio
                this->add(d);
            }
            else {//entre medio
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(ant->get_next());
                ant->set_next(nuevo);
            }
        }
        else {
            if ((czo->get_next())->get_next() == NULL) {//al final
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(czo->get_next());
                czo->set_next(nuevo);

            }
            else this->resto()->addO(d, czo);

        }
    }
}

template <class T> bool Lista<T>::esta(T d)
{// busca d en la lista
    if (this->esvacia()) return false;
    if (this->cabeza() == d) return true;

    return this->resto()->esta(d);
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T>* ant)
{
    if (!this->esvacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);

    }
}
//---------------------FIN CLASE LISTA E IMPLEMENTACIONES DE LA MISMA----------------------//
//-----------------------------------------------------------------------------------------//



//-----------------------------CLASE PILA---------------------------------------------------//
template <class T> class Pila :public Lista<T> {
public:
    Pila(void){ 
        Lista<T>();
    };
    void apilar(T d){ 
        this->add(d);
    };
    T tope(void){
        return this->cabeza();
    };
    void desapilar(void){ 
        this->borrar();
    };
    bool pilavacia(){ 
        return this->esvacia();
    };
};
//--------------------FIN CLASE PILA E IMPLEMENTACIONES DE LA MISMA------------------------//



//-----------------------------CLASE COLA---------------------------------------------------//
template <class T> class Cola :public Lista<T> {
public:
    Cola(void){ 
        Lista<T>(); 
    };
    //~Cola(void);
    T tope(){
        return this->last(); 
    };
    bool colavacia(void){ 
        return this->esvacia(); 
    };
    void encolar(T a){ 
        this->add(a);
    };
    void desencolar(void){
        this->borrar_last(); 
    };
    T ultimo(void){ 
        return this->cabeza(); 
    };
    Cola<T>* copyC(void);// hace una copia de la cola
    string imprimir(){ 
        return this->toPrint(); 
    };
    void inicioC(int n);
    void finalC(int n);
    T getC(int n);
};

template <class T> Cola<T>* Cola<T>::copyC(void){
    Cola<T>* aux = new Cola();
    aux->concat(this);
    return aux;
}

template <class T> void Cola<T>::inicioC(int n)
{ //deja "vivos" los n primeros nodos de la cola y borra el resto
    int aux = this->size() - n;
    this->final(aux);
}

template <class T> void Cola<T>::finalC(int n){
    //descarta los primeros n nodos de la cola
    int aux = this->size() - n;
    this->inicio(aux);
}

template <class T> T Cola<T>::getC(int n){
    //devuelve el elemento en la posición n de la cola
    int aux = this->size() - n;
    this->final(aux);
    return this->cabeza();
}

//--------------------FIN CLASE COLA E IMPLEMENTACIONES DE LA MISMA------------------------//



//--------------------LISTAS VARIABLES Y COLAS GLOBALES DEL PROGRAMA-----------------------//
Lista<Variable>* listVar = new Lista<Variable>();//lista para las variables
Cola<string>* listInstruct = new Cola<string>;//lista para las instrucciones que podemos modificar
Cola<string>* ListOriginal = new Cola<string>;//esta es la lista original, intocable



//------------------------CLASE INSTRUCCION DECLARACION-----------------------------------//
class InstructDec:public Instruccion{
    public:
        InstructDec();
        InstructDec(string i);//contructor
        //~InstructDec();//destructor

        void ejecutar(char c, Lista<Variable> *l);
        //acá borré el "getInstruct()" porque ya es un método de la clase padre y la va a llamar automáticamente
};



InstructDec::InstructDec(string i)
:Instruccion(i){//llama al contructor de la super clase
}
void InstructDec::ejecutar(char c, Lista<Variable> *l){
    //cout<<toStringDato()<<endl;
    //string dat = "El dato del nodo es: ";
    if( c =='i'){
        Variable* t = new Variable(0,"INT",dato.at(4));
        l->add(*t);
        //cout<<"Esto se ejecuto para int"<<endl;
        //cout<<dat+l->cabeza().get_tipo()<<endl;
    };
    if(c == 'b'){
        Variable* t = new Variable(0,"BOOL",dato.at(5));
        l->add(*t);
        //cout<<"Esto se ejecuto para bool"<<endl;
        //cout<<dat+l->cabeza().get_tipo()<<endl;
    };
}

//--------------FIN CLASE INSTRUCT-DEC E IMPLEMENTACIONES DE LA MISMA----------------------//
//-----------------------------------------------------------------------------------------//

Variable buscar_nomb(Lista<Variable>* l, char n){
    Lista<Variable>* listaux = new Lista<Variable>();
    Variable aux; //objeto a los fines de retonar algo y que se vea bien
    aux.set_dato(-1);

    listaux = l->copy();
    while(((listaux->cabeza().get_nomb())!=n)&&(!listaux->esvacia())){
        listaux->borrar();
    }
    if(listaux->esvacia()){
        return aux;
    }
    return listaux->cabeza();
        
};

template <class T> void modificar_nomb(Lista<Variable>* l, char name, T d){
    if(l->cabeza().get_nomb()!=name){
        modificar_nomb(l->resto(), name, d);
    }
    else{
        l->czo->set_dato(d);
    }
}

void borrar_nomb(Lista<Variable>* l, char name){
    if(l->cabeza().get_nomb()!=name){
        borrar_nomb(l->resto(), name);
    }
    else{
        l->borrar();
    }
}

//----------------------------FUNCION ELIMINAR ESPACIOS------------------------------------//
string clearSpace(string c){
    int largo, a=0;
    largo=c.length();
    while(c[a]!='\0'){
        if(c[a]==' '){
            for(int i=a;i<largo;i++){
                c[i]=c[i+1];
            }
        largo--;
        }
        a++;
    }
    return c;
}

//-------------------------FUNCION CARGA TXT--------------------------------//
void carga_txt(Cola<string>* a){
    //cout<<"vamos a abrir el archivo"<<endl;
    //cout<<"Si todo sale bien se deberian mostrar las lineas"<<endl;
    string arch = "test.txt";

    ifstream archivo(arch.c_str());
    string cadena;
    while(getline(archivo,cadena)){
        //cout<<cadena<<endl;
        a->encolar(cadena);
    }
    if(a->colavacia()){
        cout<<"No se encontro el archivo txt"<<endl;
        exit(EXIT_FAILURE);
    }
}


//-------------------FUNCION RECONOCE INSTRUCCION---------------------//
char reconocer(string i){
    if(i.rfind("INT",0) == 0){
        //cout<<"Es una declaracion de tipo Int"<<endl;
        return 'i';
    }
    else if(i.rfind("BOOL",0)==0){
        //cout<<"Es una declaracion de tipo bool"<<endl;
        return 'b';
    }   
    else if(i.rfind("IF",0)==0){
        //cout<<"Se trata de un if"<<endl;
        return 'f';
    }
    else if((i.at(2)=='=')||i.at(1)=='='){
        //cout<<"Se trata de una asignacion"<<endl;
        return 'a';
    }
    else if(i.rfind("JUMP",0)==0){
        //cout<<"Se trata de un salto"<<endl;
        return 'j';
    }
    else if(i.rfind("SHOW",0)==0){
        //cout<<"Se trata de una salida por pantalla"<<endl;
        return 's';
    }
};

//------------------------CLASE INSTRUCCION JUMP-------------------------------------//

class InstructJump:public Instruccion{
    public:
        InstructJump();
        InstructJump(string i);//contructor
        //~InstructDec();//destructor

        Cola<string> ejecutar(Cola<string> *l);
        //acá borré el "getInstruct()" porque ya es un método de la clase padre y la va a llamar automáticamente
};



InstructJump::InstructJump(string i)
:Instruccion(i){//llama al contructor de la super clase
}
Cola<string> InstructJump::ejecutar(Cola<string> *l){
    string aux;
    int salto;
    Cola<string>* listAux = new Cola<string>;
    listAux = l->copyC();//copiamos la cola original para no modificarla y siempre poder ir tanto para adelante como para atras
    
    //IF ( c ) THEN JUMP 12
    //cout<<"La instruccion es: "<<dato<<endl;
    aux =clearSpace(dato);//le sacamos los espacios para trabajar mejor
    aux= dato.erase(0,dato.find('P')+1);//aislamos la parte del string que nos interesa
    //cout<<"el salto es a la linea: "<<aux<<endl; 
    salto = stoi(aux);//transformacion del salto a int para poder identificar el nodo que nos interesa
    listAux->finalC(salto-2);

    return *listAux;
};


//-------------------------PASE DE INFIJO A POSTFIJO----------------------------------//
/*
 * @Return true si el parámetro es un '(' 
 */
bool esGrupoAbierto (const string& op){
    return op == "(";
}

/*
 * @Return true si el parametro es un ')' 
 */
bool esGrupoCerrado (const string& op){
    return op == ")";
}

/*
 * @Return true si el parametro es un '(' o un ')' 
 */
bool esAgrupacion (const string& op){
    return op == "(" || op == ")";
}

/*
 * @Return el orden de precedencia del operador indicado 
 */
int ordenDePrecedencia (const string& op){
    if (esAgrupacion(op)){ 
        return 1;
    }
    else if (op == "+" || op == "-"){
        return 2;
    }
    else if (op == "*" || op == "/"){
        return 3;
    }
    else{
        return 0;
    }
}

/*
 * @return un vector cuyos elementos son las palabras que conforman la notacion posfija 
 */
vector<string> infijoAPostfijo (const string& infijo)
{
    Pila<string> operadores;
    vector<string> postfijo;
    istringstream in(infijo);
    string palabra;
    while(in >> palabra)
    {
        int orden = ordenDePrecedencia(palabra);
        /*
         * Un orden 0 indica un operando -> lo agrega directamente al vector de salida
         */
        if (orden == 0)
        {
            postfijo.push_back(palabra);
        }
        /*
         * Un orden !=0 indica un operador. Primero extraer de la pila todos los operadores
         * leidos previamente de orden superior, despues poner en la pila.
         */
        else{
            //No extrae ningun operador cuando la palabra es un parentesis abierto
            if (!esGrupoAbierto(palabra)){
                while (operadores.size() > 0 && ordenDePrecedencia(operadores.tope()) >= orden)
                {
                    if (!esAgrupacion(operadores.tope())){
                        postfijo.push_back(operadores.tope());
                    }
                    operadores.borrar();
                }
            }
            operadores.apilar(palabra);
        }
    }

    //extrae los operadores restantes de la pila
    while (operadores.size() > 0)
    {
        if (!esAgrupacion(operadores.tope()))
        {
            postfijo.push_back(operadores.tope());
        }
        operadores.borrar();
    }

    return postfijo;
}
//------------------------FIN PASE DE INFIJO A POSTFIJO----------------------//



//--------------------------------FUNCION SEPARAR----------------------------//
/*
 * @return un vector cuyos elementos son las subcadenas de un string que se extraen de este
 * cada vez que en el mismo se encuentra el caracter "delim" 
 */
std::vector<std::string> separa(std::string str, char delim){
    std::vector<std::string> resultado;
    std::istringstream isstream(str);
    std::string palabra;
    
    /*
     * getline: Extrae caracteres de isstream y los almacena en palabra hasta que se encuentra el carácter 
     * de delimitación delim (o el carácter de nueva línea '\n')
     */
    while(std::getline(isstream, palabra, delim)){
        resultado.push_back(palabra);
    }
    return resultado;
}

//-------------------------CALCULADORA POST-FIJA-------------------------//
int CalculadoraPostfija(string operacion, Lista<Variable>* vars){
    string j = operacion;
    vector<string> v = separa(j, 32);
    string l="";
    for(int i=0;i<=v.size()-1;i++){
        string p=v[i];
        l+=" "+p+" ";
    }
    vector<string> pf = infijoAPostfijo(l);
    Pila<string> *pfp = new Pila<string>();
    Pila<int> *aux = new Pila<int>();

    for(int i=pf.size()-1;i>=0;i--){
        pfp->apilar(pf[i]);
    }
    while(!(pfp->esvacia())){
        if((pfp->tope()[0]>=97) && (pfp->tope()[0]<=122)){
            aux->apilar(buscar_nomb(vars,pfp->tope()[0]).get_dato());
            pfp->desapilar();
        }
        else if(ordenDePrecedencia(pfp->tope())==0){
            aux->apilar(stoi(pfp->tope()));
            pfp->desapilar();
        }
        else if(pfp->tope()[0]==32){
            pfp->desapilar();
        }
        else if(pfp->tope()[0]==42 && !(aux->esvacia())){
            int a = aux->tope();
            aux->desapilar();
            int b = aux->tope();
            aux->desapilar();
            aux->apilar(a*b);
            pfp->desapilar();
        }
        else if(pfp->tope()[0]==43 && !(aux->esvacia())){
            int a = aux->tope();
            aux->desapilar();
            int b = aux->tope();
            aux->desapilar();
            aux->apilar(a+b);
            pfp->desapilar();
        }
        else if(pfp->tope()[0]==45 && !(aux->esvacia())){
            int a = aux->tope();
            aux->desapilar();
            int b = aux->tope();
            aux->desapilar();
            aux->apilar(b-a);
            pfp->desapilar();
        }
        else if(pfp->tope()[0]==47 && !(aux->esvacia())){
            int a = aux->tope();
            aux->desapilar();
            int b = aux->tope();
            aux->desapilar();
            aux->apilar(b/a);
            pfp->desapilar();
        }
    }

    return aux->tope();
};


//---------------------------CALCULADORA BOOLEANA--------------------------------//
bool calculadoraBool(int a, int b, string oper, Lista<Variable> *vars){
    bool resultado;

    if(oper.find('=')==string::npos && oper.find('>')!=string::npos){
        resultado = a > b;
    }
    else if(oper.find('=')==string::npos && oper.find('<')!=string::npos){
        resultado = a < b;
    }
    else if(oper.find('=')!=string::npos && oper.find('!')==string::npos && oper.find('<')==string::npos && oper.find('>')==string::npos){
        resultado = a == b;
    }
    else if(oper.find('!')!=string::npos && oper.find('=')!=string::npos){
        resultado = a != b;
    }
    else if(oper.find('=')!=string::npos && oper.find('>')!=string::npos){
        resultado = a >= b;
    }
    else if(oper.find('=')!=string::npos && oper.find('<')!=string::npos){
        resultado = a <= b;
    }
    else if(oper.find('=') == string::npos && oper.find('>') == string::npos && oper.find('<') == string::npos && oper.find('!') == string::npos){
        resultado = stoi(oper);
    }
    
    return resultado;
}



//--------------------------CLASE INSTRUCCION ASIGNACION-------------------------//
class InstructAsign:public Instruccion{
    private:
        Lista<Variable> *vars;
    public:
        InstructAsign();
        /*
         * Contructor: recibe como parametro un string de asignacion como por ej: "a = 8 + b + 15"
         * y la lista de variables definidas a las cuales se les quiere asignar un valor. 
         */
        InstructAsign(string i, Lista<Variable> *list)
        :Instruccion(i){
            vars=list;
        };

        /*
         * Método ejecutar, ejecuta una asignación 
         */
        void ejecutar(){
            Lista<Variable> *listaux = vars->copy();
            Lista<Variable> *listaux2 = vars->copy();
            Lista<Variable> *listaux3 = vars->copy();
            //cout<<"\nla variable es: "<<dato.at(0);
            if(buscar_nomb(vars, dato.at(0)).get_tipo()=="INT"){
                string aux = dato;
                string oper = aux.erase(0,4);
                int value = CalculadoraPostfija(oper, vars);
                Variable v = buscar_nomb(vars, dato[0]);
                v.set_dato(value);
                modificar_nomb(vars, dato[0], v);
            }
            else if(buscar_nomb(vars, dato.at(0)).get_tipo()=="BOOL"){
                string aux=dato;
                string oper=aux.erase(0,4);
                bool result;
                string term1;
                string term2;
                if(dato.find("+")!=string::npos||dato.find("-")!=string::npos||dato.find("*")!=string::npos||dato.find("/")!=string::npos){
                    int cuentaspace;
                    int i=0;
                    while(oper.at(i)!='>' && oper.at(i)!='<' && oper.at(i)!='=' && oper.at(i)!='!'){
                        term1+=oper.at(i);
                        i++;
                    }
                    
                    i = 0;
                    while(i<oper.length()){
                        if(oper.at(i)=='>' || oper.at(i)=='<' || oper.at(i)=='=' || oper.at(i)=='!'){
                            cuentaspace = i + 1;
                            i=oper.length();//corta el while
                        }else{
                            i++;
                        }
                    }
                    
                    if(oper.at(cuentaspace)=='='){
                        cuentaspace++;
                    }

                    i=cuentaspace;
                    while(i<oper.length()){
                        term2+=oper.at(i);
                        i++;
                    }

                    int resterm1 = CalculadoraPostfija(term1, listaux);
                    int resterm2 = CalculadoraPostfija(term2, listaux2);

                    result=calculadoraBool(resterm1, resterm2, oper, listaux3);

                    Variable var;
                    var = buscar_nomb(vars,dato.at(0));
                    var.set_dato(result);
                    modificar_nomb(vars,dato.at(0),var);
                }
                //oper: a > b
                else{
                    if(oper.find('=') == string::npos && oper.find('>') == string::npos && oper.find('<') == string::npos && oper.find('!') == string::npos){
                        result = stoi(oper);
                        Variable var = buscar_nomb(vars,dato.at(0));
                        var.set_dato(result);
                        modificar_nomb(vars,dato.at(0),var);
                    }
                    else{
                        vector<string> words = separa(oper, 32);
                        int a = CalculadoraPostfija(words[0],listaux);
                        int b = CalculadoraPostfija(words[2],listaux2);
                        result=calculadoraBool(a,b,oper,listaux3);
                        Variable var = buscar_nomb(vars,dato.at(0));
                        var.set_dato(result);
                        modificar_nomb(vars,dato.at(0),var);
                    }
                }
            }
        };
};


//------------------------CLASE INSTRUCCION SHOW-------------------------------------//

class InstructShow:public Instruccion{
    public:
        InstructShow();
        InstructShow(string i);//contructor
        //~InstructDec();//destructor

        void ejecutar(Lista<Variable>* li);
        //acá borré el "getInstruct()" porque ya es un método de la clase padre y la va a llamar automáticamente
};



InstructShow::InstructShow(string i)
:Instruccion(i){//llama al contructor de la super clase
}
void InstructShow::ejecutar(Lista<Variable>* li){
    Variable k;
    Lista<Variable> *listaux=li->copy();
    string temp;
    string aux = dato;//para guardar el char que necesito
    temp = aux.erase(0,5);
    int most = CalculadoraPostfija(temp, listaux);
    if(!li->esvacia()){
        cout<<"\n"<<most;
    }else{
        cout<<"\nLa lista de variables esta vacia";
    }
};



//------------------------FUNCIO BUSQUEDA DE CARACTER-------------------------------------//
int busqChar(char c, string s){
    int i = 0;
    while(i<s.length()){
        if(s.at(i)==c){
            return i;
        }else{
            i++;
        }
    }
};

//prototipo funcion ejecucion
void ejecucion(char);

//------------------------CLASE INSTRUCCION IF-------------------------------------//

class InstructIf:public Instruccion{
   protected:
        Lista<Variable> *vars;
   public:
        InstructIf();
        InstructIf(string i, Lista<Variable> *list);//constructor
        void ejecutar(Cola<string>* l2);
};

InstructIf::InstructIf(string i, Lista<Variable> *list)
:Instruccion(i){//llama al contructor de la super clase
    vars=list;
}
void InstructIf::ejecutar(Cola<string>* l2){
    string p1;//variable para aislar la parte del if
    string p2;//variable para aislar la parte del then
    //cout<<dato<<endl;
    int a;
    int b;
    a = busqChar('F',dato);//guarda el indice de F
    b = busqChar('T',dato);//guarda el indice de T
    p1=dato.substr(a+2,b-3);//aisla la expresion del if
    a = busqChar('N',dato);//guarda el indice de N
    b = dato.length();//guarda el final de la expresion
    p2 = dato.substr(a+2,b);//aisla la expresion del then
    //( a )
    //cout<<"\nP2 vale:"<<p2;
    vector<string> aus = separa(p1,32);
    string oper="";
    for(int i=1;i<aus.size()-1;i++){
        oper+=" "+aus[i];
    }
    oper.erase(0,1);

    Lista<Variable> *listaux = vars->copy();
    Lista<Variable> *listaux2 = vars->copy();
    Lista<Variable> *listaux3 = vars->copy();
    bool result; //dice si p1 es true o false (valor de p1)
    string term1;
    string term2;
    

    if(oper.find("+")!=string::npos||dato.find("-")!=string::npos||dato.find("*")!=string::npos||dato.find("/")!=string::npos){
        int cuentaspace;
        int i=0;
        while(oper.at(i)!='>' && oper.at(i)!='<' && oper.at(i)!='=' && oper.at(i)!='!'){
            term1+=oper.at(i);
            i++;
        }
                    
        i = 0;
    
        while(i<oper.length()){
            if(oper.at(i)=='>' || oper.at(i)=='<' || oper.at(i)=='=' || oper.at(i)=='!'){
              
                cuentaspace = i + 1;
                i=oper.length();//corta el while
            }else{
                
                i++;
            }
        }       
        if(oper.at(cuentaspace)=='='){
            cuentaspace++;
        }
        i=cuentaspace;
        while(i<oper.length()){
            term2+=oper.at(i);
            i++;
        }
        int resterm1 = CalculadoraPostfija(term1, listaux);
        int resterm2 = CalculadoraPostfija(term2, listaux2);

        result=calculadoraBool(resterm1, resterm2, oper, listaux3);
    }
    else{ 
        if(oper.find('=') == string::npos && oper.find('>') == string::npos && oper.find('<') == string::npos && oper.find('!') == string::npos){
            Variable var=buscar_nomb(listaux, clearSpace(oper).at(0));
            result = var.get_dato();
        }
        else{
            vector<string> words = separa(oper, 32);
            int a = CalculadoraPostfija(words[0],listaux);
            int b = CalculadoraPostfija(words[2],listaux2);
            result = calculadoraBool(a,b,oper,listaux3);
        }
    }
    if(result){
        ejecucion(reconocer(p2));
    }
};



char selector; //variable para manejar el switch

int main(){
    //cout<<"Inicio del programa: "<<endl;
    //carga del archivo txt a la lista
    carga_txt(listInstruct);//despues de esto tenemos una cola con todas las instrucciones en string
    ListOriginal = listInstruct->copyC();//ahora tenemos una copia fiel de las instrucciones del txt
    char selector;
    while(!listInstruct->esvacia()){
    selector = reconocer(listInstruct->tope());
    ejecucion(selector);
    cout<<endl;
    listInstruct->desencolar();
    cout<<endl;
    }
    
    

}

//------------------------FUNCION MADRE DE EJECUCION-------------------------------------//
void ejecucion(char c){
    switch (c){
        case 'i':
        {
            //Aca se ejecuta InstructDec.ejecutar()
            InstructDec k(listInstruct->tope());
            k.ejecutar(c,listVar);
            break;
        }
        case 'b':
            {
            //Aca se ejecuta InstructDec.ejecutar() pero de bool"
            InstructDec k(listInstruct->tope());
            k.ejecutar(c,listVar);
            break;
            }
        case 'f':
            {
            //"Aca se ejecuta InstIf.ejecutar()"
            InstructIf k(listInstruct->tope(), listVar);
            k.ejecutar(listInstruct);
            break;
            }
        case 'a':
            {
            //"Aca se ejecuta InstAsig.ejecutar 
            InstructAsign k(listInstruct->tope(),listVar);
            k.ejecutar();
            cout<<"Asignacion realizada"<<endl;
            break;
            }
        
        case 'j':
            {
            //"Aca se ejecuta InstSalt.ejecutar()"
            InstructJump k(listInstruct->tope()); 
            *listInstruct = k.ejecutar(ListOriginal);
            break;
            }
        
        case 's':
            {
            //Aca se ejecuta InstMuest.ejecutar()"<<endl;
            InstructShow k(listInstruct->tope());
            k.ejecutar(listVar);
            break;
            }
    }
}