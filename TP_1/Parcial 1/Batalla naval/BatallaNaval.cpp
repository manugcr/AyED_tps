#include <cstdlib>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// ---------------------- Struct POSITION (Posicion)

typedef struct {
    bool flag; //indica si la estructura POSITION ya se encuentra ocupada
    int x; //posicion de la columna
    int y; //posicion de la fila
}POSITION;

// ---------------------- Class Node (Nodo)

template <class T> class Node {
    private:
        T data;
        Node* next;
    public:
        Node(void) {
            next = NULL;
        };
        Node(T d) {
            data = d;
            next = NULL;
        };
        void setData(T d) {
            data = d;
        };
        void setNext(Node* n) {
            next = n;
        };
        T getData(void) {
            return data;
        };
        Node* getNext(void) {
            return next;
        };
        bool isEmpty(void) {
            return next == NULL;
        }
};

// ---------------------- Class List (Lista)

template <class T> class List {
    private:
        Node<T>* start; //es el puntero al nodo cabeza de la lista
    public:
        List(void) {
            start = new Node<T>();
        };
        List(Node<T>* n) {
            start = n;
        };
        void add(T d); //agrega un nodo a la lista
        void dlte(void); //borra el nodo cabeza
        void dlteLast(void); //borra el ultimo nodo
        T head(void); //retorna el dato del nodo de la cabeza
        T tail(void); //retorna el dato del nodo de la cola
        List* rest(void); //retorna la lista actual sin el nodo cabeza
        bool isEmpty(void); //retorna true si la lista esta vacia
        string toPrint(string s); //recorre y retorna todos los datos de la lista en un string
};

template <class T> void List<T>::add(T d) {
    Node<T>* nw = new Node<T>(d);
    nw->setNext(start);
    start = nw;
}

template <class T> void List<T>::dlte(void) {
    if(!this->isEmpty()) {
        Node<T>* tmp = start;
        start = start->getNext();
        delete tmp;
    }
}

template <class T> void List<T>::dlteLast(void) {
    if(!this->isEmpty()) {
        if((start->getNext())->getNext() == NULL) {
            delete start->getNext();
            start->setNext(NULL);
        }
        else
            this->rest()->dlteLast();
    }
}

template <class T> T List<T>::head(void) {
    if(this->isEmpty()) {
        return NULL;
    }
    return start->getData();
}

template <class T> T List<T>::tail(void) {
    if(!this->isEmpty()) {
        if(this->rest()->isEmpty()) {
            return this->head();
        }
        return this->rest()->tail();
    }
    return NULL;
}

template <class T> List<T>* List<T>::rest(void) {
    List* l = new List(start->getNext());
    return l;
}

template <class T> bool List<T>::isEmpty(void) {
    return start->isEmpty();
}

template <class T> string List<T>::toPrint(string s) {
    if(this->isEmpty()) {
        return s;
    }
    else {
        ostringstream stm;
        stm<<this->head()<<endl<<this->rest()->toPrint(s);
        return stm.str();
    }
}

// ---------------------- Class Pile (Pila)

template <class T> class Pile:public List<T> {
    public:
        Pile(void) {
            List<T>();
        };
        void stack(T d) { //apila un elemento en la pila
            this->add(d);
        };
        void unstack(void) { //desapila un elemento de la pila
            this->dlte();
        };
        T take(void) { //retorna el dato proximo a salir (no lo elimina)
            return this->head();
        };
        bool pileIsEmpty(void) { //retorna true si la pila esta vacia
            return this->isEmpty();
        };
        string showPile(string s = "") { //recorre y retorna todos los datos de la pila en un string
            return this->toPrint(s);
        };
};

// ---------------------- Class Queue (Cola)

template <class T> class Queue :public List<T> {
    public:
        Queue(void) {
            List<T>();
        };
        void putInQueue(T d) { //encola un elemento en la cola
            this->add(d);
        };
        void takeOutOfQueue(void) { //desencola un elemento de la cola
            this->dlteLast();
        };
        T take(void) { //retorna el dato proximo a salir (no lo elimina)
            return this->tail();
        };
        bool queueIsEmpty(void) { //retorna true si la cola esta vacia
            return this->isEmpty();
        };
        string showQueue(string s = "") { //recorre y retorna todos los datos de la cola en un string
            return this->toPrint(s);
        };
};

// ---------------------- Class Boat (Barco)

class Boat {
    private:
        POSITION* position[4]; //guarda los casilleros donde se encuentra el barco (destructor: 4 - crucero: 3 - cañonero: 2 - submarino: 1)
        string boat; //define el tipo de barco ("destructor" - "crucero" - "cañonero" - "submarino")
        bool discovered; //es true si el barco ya se descubrio
    public:
        Boat(void);
        void setPosition(POSITION* p); //añade una posicion mas del barco al arreglo position
        void setDiscovered(void); //cambia la variable discovered a true y dependiendo de cuantos casilleros ocupa define el tipo de barco
        POSITION* getPosition(int i); //retorna la posicion del barco almacenada en la posicion i del arreglo
        string getBoat(void); //retorna el string del tipo de barco
        bool getDiscovered(void); //retorna true si el barco ya fue descubierto
};

Boat::Boat(void) {
    for(int i = 0; i < 4; i++) { //inicializo las posiciones del barco con la bandera en false
        POSITION* position_aux = new POSITION();
        position_aux->flag = false;
        position[i] = position_aux;
    }
    boat = "no descubierto";
    discovered = false; //inicializo el barco en "no descubierto"
}

void Boat::setPosition(POSITION* p) {
    for(int i = 0; i < 4; i++) {
        if(position[i]->flag == false) {
            position[i] = p;
            position[i]->flag = true;
            break;
        }
    }
}

void Boat::setDiscovered(void) {
    int counter = 0;
    for(int i = 0; i < 4; i++) { //cuento cuantas posiciones son usadas realmente en total
        if(position[i]->flag == true) {
            counter++;
        }
    }
    if(counter == 4) {
        boat = "destructor";
    }
    else if(counter == 3) {
        boat = "crucero";
    }
    else if(counter == 2) {
        boat = "cañonero";
    }
    else if(counter == 1) {
        boat = "submarino";
    }
    discovered = true;
}

POSITION* Boat::getPosition(int i) {
    return position[i];
}

string Boat::getBoat() {
    return boat;
}

bool Boat::getDiscovered(void) {
    return discovered;
}

// ---------------------- Class PositionsStack (Pila de posiciones)

class PositionsStack {
    private:
        Pile<POSITION*>* positions_stack; //almacena las posiciones a disparar
    public:
        PositionsStack(void);
        PositionsStack(POSITION* p); //constructor que inicializa y carga una primera posicion
        void stackPosition(POSITION* p); //agrega una posicion a la pila
        void unstackPosition(void); //desapila una posicion
        POSITION* take(void); //devuleve la posicion proxima a salir
};

PositionsStack::PositionsStack(void) {
}

PositionsStack::PositionsStack(POSITION* p) {
    positions_stack = new Pile<POSITION*>();
    positions_stack->stack(p);
}

void PositionsStack::stackPosition(POSITION* p) {
    positions_stack->stack(p);
}

void PositionsStack::unstackPosition(void) {
    positions_stack->unstack();
}

POSITION* PositionsStack::take(void) {
    return positions_stack->take();
}

// ---------------------- Class PilesQueue (Cola de pilas)

class PilesQueue {
    private:
        Queue<PositionsStack*>* piles_queue; //almacena en la cola las pilas de posiciones
    public:
        PilesQueue(void);
        POSITION* generateRandomPosition(void); //genera un elemento POSITION (posicion) aleatoria
        void fillQueue(void); //llena la cola con pilas de una sola posicion al azar
        void takeOutOfQueue(void); //desencola un elemento
        PositionsStack* take(void); //devuelve el dato proximo a salir
        void printPilesQueue(void); // (---PARA TEST---) imprime las posiciones iniciales generadas y almacenadas
};

PilesQueue::PilesQueue(void) {
    piles_queue = new Queue<PositionsStack*>();
}

POSITION* PilesQueue::generateRandomPosition(void) {
    POSITION* position = new POSITION();
    int n = rand()%100;
    int position_x = 0;
    int position_y = 0;
    for(int i = 0; i < n; i++) {
        position_x++;
        if(position_x == 10) {
            position_x = 0;
            position_y++;
        }
    }
    position->x = position_x;
    position->y = position_y;
    return position;
}

void PilesQueue::fillQueue(void) {
    bool board_aux[10][10]; //matriz de booleanos para registrar las posiciones random que ya existen
    for(int i = 0; i < 10; i++) { //inicializo la matriz de booleanos auxiliar en false
        for(int j = 0; j < 10; j++) {
            board_aux[i][j] = false;
        }
    }
    srand(time(NULL)); //genero una semilla para el rand()
    POSITION* position_aux = new POSITION();
    for(int i = 0; i < 100; i++) { //genero todas las posiciones del tablero de manera alazar, sin repetir
        do {
            position_aux = generateRandomPosition();
        } while(board_aux[position_aux->y][position_aux->x] != false); //genero posiciones random hasta que se genera una que no fue usada
        board_aux[position_aux->y][position_aux->x] = true;
        piles_queue->putInQueue(new PositionsStack(position_aux));
    }
    cout<<"\n-posiciones generadas y cargadas exitosamente-"<<endl;  //cout que corrobora que se carguen las 100 posiciones
}

void PilesQueue::takeOutOfQueue(void) {
    piles_queue->takeOutOfQueue();
}

PositionsStack* PilesQueue::take(void) {
    return piles_queue->take();
}

void PilesQueue::printPilesQueue() {
    for(int i = 0; i < 100; i++) {
        cout<<i<<" ["<<piles_queue->take()->take()->y<<"]["<<piles_queue->take()->take()->x<<"]"<<endl;
        piles_queue->takeOutOfQueue();
    }
}

// ---------------------- Class Game (Juego)

class Game {
    private:
        PilesQueue* piles_queue; //cola de pilas
        Boat* boats[10]; //almacena los 10 barcos que deberan ser descubiertos
        bool shots[10][10]; //matriz de booleanos donde se guardan los disparos realizados
    public:
        Game(void);
        void fillWithRandomPositions(void); //llena la cola de pilas con posiciones random
        POSITION* takePosition(void); //toma la posicion siquiente de la cola de pilas
        POSITION* shoot(void); //dispara eliminando la posicion de la pila, registrando en la matriz shots, mostrandola en consola y retornandola
        void recordShot(POSITION* p); //registra en la matriz de booleanos donde se realizo el disparo
        void recordBoat(POSITION* p, int n); //almacena en la posicion n la posicion p de un barco
        bool checkShotPosition(POSITION* p); //retorna true si la posicion ingresada es true en la matriz de booleanos
        void stackPositions1(POSITION* p); //apila las 4 direcciones siguientes posibles alrrededor de la posicion pasada por parametro
        void stackPositions2(POSITION* ip, POSITION* p); //apila las 2 posiciones siguientes posibles segun las posiciones pasadas por parametro
        void stackPositions3(POSITION* ip, POSITION* p); //apila las 2 posiciones siguientes posibles segun las posiciones pasadas por parametro
        void unstackPosition(void); //desapila una posicion de la pila
        void takeOutOfQueue(void); //desencola una pila de posiciones
        Boat* takeBoat(int n); //devuelve el barco numero n del arreglo pasado por parametro
        void printPilesQueue(void); // (---PARA TEST---) imprime las posiciones iniciales generadas y almacenadas
        void printBoats(void); //muestra el tablero con los casilleros de todos los barcos descubiertos
        void printShots(void); // (---PARA TEST---) muestro el tablero de booleanos
};

Game::Game(void) {
    piles_queue = new PilesQueue(); //genero la cola de pilas
    for(int i = 0; i < 10; i++) { //inicializo el arreglo de barcos con 10 barcos
        Boat* boat = new Boat();
        boats[i] = boat;
    }
    for(int i = 0; i < 10; i++) { //inicializo todos los elementos de la matriz board en false
        for(int j = 0; j < 10; j++) {
            shots[i][j] = false;
        }
    }
}

void Game::fillWithRandomPositions(void) {
    piles_queue->fillQueue();
}

POSITION* Game::takePosition(void) {
    return piles_queue->take()->take();
}

POSITION* Game::shoot(void) {
    POSITION* position = new POSITION();
    position = piles_queue->take()->take();
    cout<<"\ndisparo a: ["<<position->y<<"]["<<position->x<<"]";
    recordShot(position);
    piles_queue->take()->unstackPosition();
    return position;
}

void Game::recordShot(POSITION* p) {
    shots[p->y][p->x] = true;
}

void Game::recordBoat(POSITION* p, int n) {
    boats[n]->setPosition(p);
}

bool Game::checkShotPosition(POSITION* p) {
    return shots[p->y][p->x];
}

void Game::stackPositions1(POSITION* p) {
    for(int i = 0; i < 10; i++) { //desapilo las posiciones anteriores (en caso de haber)
        piles_queue->take()->unstackPosition();
    }
    if(p->x < 9 && shots[p->y][p->x+1] == false) {
        POSITION* position = new POSITION();
        position->x = p->x+1;
        position->y = p->y;
        piles_queue->take()->stackPosition(position);
    }
    if(p->x > 0 && shots[p->y][p->x-1] == false) {
        POSITION* position = new POSITION();
        position->x = p->x-1;
        position->y = p->y;
        piles_queue->take()->stackPosition(position);
    }
    if(p->y < 9 && shots[p->y+1][p->x] == false) {
        POSITION* position = new POSITION();
        position->x = p->x;
        position->y = p->y+1;
        piles_queue->take()->stackPosition(position);
    }
    if(p->y > 0 && shots[p->y-1][p->x] == false) {
        POSITION* position = new POSITION();
        position->x = p->x;
        position->y = p->y-1;
        piles_queue->take()->stackPosition(position);
    }
}

void Game::stackPositions2(POSITION* ip, POSITION* p) {
    for(int i = 0; i < 10; i++) { //desapilo las posiciones anteriores (en caso de haber)
        piles_queue->take()->unstackPosition();
    }
    if(ip->x-p->x != 0) { //caso si el barco se encuentra en posicion horizontal
        if(ip->x-p->x < 0) { //caso si ip < p
            if(shots[ip->y][ip->x+2] == false && ip->x+2 <= 9) { //corroboro que no se haya disparado en esa posicion ya 
                POSITION* position = new POSITION();
                position->x = ip->x+2;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y][ip->x-1] == false && ip->x-1 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x-1;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
        }
        else { //caso si ip > p
            POSITION* position = new POSITION();
            if(shots[ip->y][ip->x+1] == false && ip->x+1 <= 9) {
                POSITION* position = new POSITION();
                position->x = ip->x+1;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y][ip->x-2] == false && ip->x-2 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x-2;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
        }
    }
    else { //caso si el barco se encuentra en posicion vertical
        if(ip->y-p->y < 0) { //caso si ip < p
            if(shots[ip->y+2][ip->x] == false && ip->y+2 <= 9) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y+2;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y-1][ip->x] == false && ip->y-1 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y-1;
                piles_queue->take()->stackPosition(position);
            }
        }
        else { //caso si ip > p
            if(shots[ip->y+1][ip->x] == false && ip->y+1 <= 9) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y+1;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y-2][ip->x] == false && ip->y-2 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y-2;
                piles_queue->take()->stackPosition(position);
            }
        }
    }
}

void Game::stackPositions3(POSITION* ip, POSITION* p) {
    for(int i = 0; i < 10; i++) { //desapilo las posiciones anteriores (en caso de haber)
        piles_queue->take()->unstackPosition();
    }
    if(ip->x-p->x != 0) { //caso si el barco se encuentra en posicion horizontal
        if(ip->x-p->x < 0) { //caso si ip < p
            if(shots[ip->y][ip->x+3] == false && ip->x+3 <= 9) { //corroboro que no se haya disparado en esa posicion ya 
                POSITION* position = new POSITION();
                position->x = ip->x+3;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y][ip->x-1] == false && ip->x-1 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x-1;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
        }
        else { //caso si ip > p
            POSITION* position = new POSITION();
            if(shots[ip->y][ip->x+1] == false && ip->x+1 <= 9) {
                POSITION* position = new POSITION();
                position->x = ip->x+1;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y][ip->x-3] == false && ip->x-3 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x-3;
                position->y = ip->y;
                piles_queue->take()->stackPosition(position);
            }
        }
    }
    else { //caso si el barco se encuentra en posicion vertical
        if(ip->y-p->y < 0) { //caso si ip < p
            if(shots[ip->y+3][ip->x] == false && ip->y+3 <= 9) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y+3;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y-1][ip->x] == false && ip->y-1 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y-1;
                piles_queue->take()->stackPosition(position);
            }
        }
        else { //caso si ip > p
            if(shots[ip->y+1][ip->x] == false && ip->y+1 <= 9) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y+1;
                piles_queue->take()->stackPosition(position);
            }
            if(shots[ip->y-3][ip->x] == false && ip->y-3 >= 0) {
                POSITION* position = new POSITION();
                position->x = ip->x;
                position->y = ip->y-3;
                piles_queue->take()->stackPosition(position);
            }
        }
    }
}

void Game::unstackPosition(void) {
    piles_queue->take()->unstackPosition();
}

void Game::takeOutOfQueue(){
    piles_queue->takeOutOfQueue();
}

Boat* Game::takeBoat(int n) {
    return boats[n];
}

void Game::printPilesQueue(void) {
    piles_queue->printPilesQueue();
}

void Game::printBoats(void) {
    bool flag;
    for(int i = 0; i < 10; i++) {
        cout<<"|";
        for(int j = 0; j < 10; j++) {
            flag = false;
            for(int k = 0; k < 10; k++) {
                if(boats[k]->getDiscovered() == true) {
                    for(int l = 0; l < 4; l++) {
                        if(boats[k]->getPosition(l)->flag == true && boats[k]->getPosition(l)->x == j && boats[k]->getPosition(l)->y == i) {
                            flag = true;
                        }
                    }
                }
            }
            if(flag == true) {
                cout<<"x|";
            }
            else {
                cout<<" |";
            }
        }
        cout<<endl;
    }
}

void Game::printShots(void) {
    for(int i = 0; i < 10; i++) {
        cout<<"|";
        for(int j = 0; j < 10; j++) {
            cout<<shots[i][j]<<"|";
        }
        cout<<endl;
    }
}

// ---------------------- Class MAIN (MAIN)

int main(int argc, char* argv[]) {
    Game* game = new Game();
    int discovered_boats = -1; //contador para posicion de barcos descubiertos (iniciado en -1 para que en la primera sea 0)
    game->fillWithRandomPositions(); //lleno la cola de pilas con posiciones iniciales
    while(discovered_boats < 9) { //codigo y desarrollo del juego
        //DESARROLLO DE LA PARTIDA
        POSITION* position = new POSITION();
        do { //busco que la posicion siguiente a disparar no se haya efectuado, en tal caso, desapilo la posicion ya usada
            position = game->takePosition();
            if(game->checkShotPosition(position) == true) {
                game->unstackPosition();
            }
        } while(game->checkShotPosition(position) == true);
        position = game->shoot(); //efectuo un disparo
        char condition;
        cout<<" ingresar estado: ";
        cin>>condition; //ingreso por consola los caracteres: 'a' -> (agua) 'v' -> (averiado) 'h' -> (hundido)
        if(condition == 'v') { //if por si consigo el primer averiado de una serie
            //PROCEDIMIENTO PARA CUANDO ENCUENTRO EL PRIMER AVERIADO
            POSITION* initial_position = new POSITION();
            initial_position = position; //guardo la primera posicion donde consegui un averiado
            discovered_boats++; //sumo un barco mas que fue descubierto
            game->recordBoat(position, discovered_boats); //guardo la posicion del averiado en el barco descubierto actual
            game->stackPositions1(position); //apilo las 4 posibles posiciones para continuar (arriba - abajo - izquierda - derecha)
            do {
                position = game->shoot(); //efectuo un disparo y guardo la posicion disparada en la variable position
                cout<<" ingresar estado: ";
                cin>>condition; //ingreso por consola los caracteres: 'a' -> (agua) 'v' -> (averiado) 'h' -> (hundido)
            } while(condition == 'a'); //while por si consigo el segundo averiado de una serie o logro hundir el barco
            if(condition == 'v') { //if por si encuentro el segundo averiado de una serie (else por si hundo al segundo disparo)
                //PROCEDIMIENTO PARA CUANDO ENCUENTRO EL SEGUNDO AVERIADO
                game->recordBoat(position, discovered_boats); //guardo la posicion del averiado en el barco descubierto actual
                game->stackPositions2(initial_position, position); //apilo las 2 posiciones posibles siguientes a continuar
                do {
                    position = game->shoot(); //efectuo un disparo y guardo la posicion disparada en la variable position
                    cout<<" ingresar estado: ";
                    cin>>condition; //ingreso por consola los caracteres: 'a' -> (agua) 'v' -> (averiado) 'h' -> (hundido)
                } while(condition == 'a');
                if(condition == 'v') { //if por si encuentro el tercer averiado de una serie (else por si hundo al tercer disparo)
                    //PROCEDIMIENTO PARA CUANDO ENCUENTRO EL TERCER AVERIADO
                    game->recordBoat(position, discovered_boats); //guardo la posicion del averiado en el barco descubierto actual
                    game->stackPositions3(initial_position, position); //apilo las 2 posiciones posibles siguientes a continuar
                    do {
                        position = game->shoot(); //efectuo un disparo y guardo la posicion disparada en la variable position
                        cout<<" ingresar estado: ";
                        cin>>condition; //ingreso por consola los caracteres: 'a' -> (agua) 'v' -> (averiado) 'h' -> (hundido)
                    } while(condition == 'a');
                    if(condition == 'h') {
                        //PROCEDIMIENTO PARA CUANDO ENCUENTRO EL CUARTO Y ULTIMO AVERIADO (3 AVERIADOS + HUNDIDO) (DESTRUCTOR)
                        game->recordBoat(position, discovered_boats); //guardo la posicion del hundido en el barco descubierto actual
                        game->takeBoat(discovered_boats)->setDiscovered();
                        cout<<"\nse descubrio un -"<<game->takeBoat(discovered_boats)->getBoat()<<"- en las posiciones ";
                        for(int i = 0; i < 4; i++) {
                            if(game->takeBoat(discovered_boats)->getPosition(i)->flag == true) {
                                cout<<"["<<game->takeBoat(discovered_boats)->getPosition(i)->y<<"]["<<game->takeBoat(discovered_boats)->getPosition(i)->x<<"] ";
                            }
                            else {
                                break;
                            }
                        }
                        cout<<endl;
                        condition = 'a';
                    }
                }
                else {
                    //PROCEDIMIENTO PARA CUANDO HUNDI EL BARCO (2 AVERIADOS + HUNDIDO) (CRUCERO)
                    game->recordBoat(position, discovered_boats); //guardo la posicion del hundido en el barco descubierto actual
                    game->takeBoat(discovered_boats)->setDiscovered();
                    cout<<"\nse descubrio un -"<<game->takeBoat(discovered_boats)->getBoat()<<"- en las posiciones ";
                    for(int i = 0; i < 4; i++) {
                        if(game->takeBoat(discovered_boats)->getPosition(i)->flag == true) {
                            cout<<"["<<game->takeBoat(discovered_boats)->getPosition(i)->y<<"]["<<game->takeBoat(discovered_boats)->getPosition(i)->x<<"] ";
                        }
                        else {
                            break;
                        }
                    }
                    cout<<endl;
                    condition = 'a';
                }
            }
            else {
                //PROCEDIMIENTO PARA CUANDO HUNDI EL BARCO (1 AVERIADO + HUNDIDO) (CAÑONERO)
                game->recordBoat(position, discovered_boats); //guardo la posicion del hundido en el barco descubierto actual
                game->takeBoat(discovered_boats)->setDiscovered();
                cout<<"\nse descubrio un -"<<game->takeBoat(discovered_boats)->getBoat()<<"- en las posiciones ";
                for(int i = 0; i < 4; i++) {
                    if(game->takeBoat(discovered_boats)->getPosition(i)->flag == true) {
                        cout<<"["<<game->takeBoat(discovered_boats)->getPosition(i)->y<<"]["<<game->takeBoat(discovered_boats)->getPosition(i)->x<<"] ";
                    }
                    else {
                        break;
                    }
                }
                cout<<endl;
                condition = 'a';
            }
        }
        if(condition == 'h') { //if por si consigo hundir un barco a la primera
            //PROCEDIMIENTO PARA CUANDO HUNDI EL BARCO (HUNDIDO AL PRIMER INTENTO) (SUBMARINO)
            discovered_boats++;
            game->recordBoat(position, discovered_boats); //guardo la posicion del hundido en el barco descubierto actual
            game->takeBoat(discovered_boats)->setDiscovered();
            cout<<"\nse descubrio un -"<<game->takeBoat(discovered_boats)->getBoat()<<"- en la posicion ";
            for(int i = 0; i < 4; i++) {
                if(game->takeBoat(discovered_boats)->getPosition(i)->flag == true) {
                    cout<<"["<<game->takeBoat(discovered_boats)->getPosition(i)->y<<"]["<<game->takeBoat(discovered_boats)->getPosition(i)->x<<"] ";
                }
                else {
                    break;
                }
            }
            cout<<endl;
            condition = 'a';
        }
        game->takeOutOfQueue();
    }
    cout<<endl;
    cout<<"tablero de barcos descubiertos:"<<endl;
    game->printBoats();
    cout<<endl;
    cout<<"tablero de posiciones disparadas:"<<endl;
    game->printShots();
    cout<<endl;
    cout<<"posiciones no disparadas:"<<endl;
    game->printPilesQueue();

    //final del programa
    system("PAUSE");
    return EXIT_SUCCESS;
}