#ifndef LIST_H
#define LIST_H

using namespace std;

template<class T> class List {
    private:
		NodeList<T> *head; //es el puntero al nodo cabeza de la lista
		NodeList<T> *tail; //es el puntero al nodo cola de la lista
    public:
		List(void);
		List(NodeList<T> *n);
		void add(T d); //agrega un nodo en la cola de la lista
		void add(T d, int n); //agrega un nodo en la posicion n
		void add(List<T> *l); //concatena la lista l a la lista original
		void dlteHead(bool b); //borra el nodo cabeza donde b indica si se hara un borrado fisico del nodo
		void dlteTail(bool b); //borra el nodo cola donde b indica si se hara un borrado fisico del nodo
		void dlte(int n, bool b); //borra el nodo en la posicion n donde b indica si se hara un borrado fisico del nodo
		void clear(bool b); //borra todos los nodos de la lista donde b indica si se hara un borrado fisico del nodo
		NodeList<T> *getHead(void); //retorna un puntero al nodo cabeza
		NodeList<T> *getTail(void); //retorna un puntero al nodo cola
		NodeList<T> *take(int n); //retorna un puntero al nodo en la posicion n
		List *rest(void); //retorna la lista sin el nodo cola
		int size(void); //retorna un entero que indica la cantidad de nodos de la lista
		void swapData(int a, int b); //efectua un swap entre la informacion del nodo en la posicion a con el nodo en la posicion b
		void swapData(NodeList<T> *a, NodeList<T> *b); //efectua un swap entre la informacion del nodo a con el nodo b
		int position(T d); //retorna un entero indicando la posicion donde se encuentra el dato d
		List<T> *listWithoutRepeat(void); //retorna una lista con todos los datos de la lista sin repetir
		void show(void); //muestra todos los elementos de la lista
		void showDetailed(void); //muestra todos los elementos de la lista de forma detallada
		bool isEmpty(void); //retorna true si la lista esta vacia
};

template<class T> List<T>::List(void) {
    head = NULL;
    tail = NULL;
}

template<class T> List<T>::List(NodeList<T> *n){
	head = n;
	tail = n;
}

template<class T> void List<T>::add(T d) {
    if(head != NULL) {
        NodeList<T> *nw = new NodeList<T>(d, NULL, tail);
        tail->setNext(nw);
        tail = nw;
    }
    else {
        NodeList<T> *nw = new NodeList<T>(d, NULL, NULL);
        head = nw;
        tail = nw;
    }
}

template<class T> void List<T>::add(T d, int n) {
    if(n <= this->size() && n >= 0) {
        if(n == this->size())
            this->add(d);
        else if(n == 0) {
            NodeList<T> *nw = new NodeList<T>(d, head, NULL);
            head->setPrevious(nw);
            head = nw;
        }
        else {
            NodeList<T> *tmp = this->take(n);
            NodeList<T> *nw = new NodeList<T>(d, tmp, tmp->getPrevious());
            nw->getPrevious()->setNext(nw);
            tmp->setPrevious(nw);
        }
    }
}

template<class T> void List<T>::add(List<T> *l) {
    if(head != NULL) {
        tail->setNext(l->getHead());
        l->getHead()->setPrevious(tail);
        tail = l->getTail();
    }
    else {
        head = l->getHead();
        tail = l->getTail();
    }
}

template <class T> void List<T>::dlteHead(bool b) {
    if(!this->isEmpty()) {
        if(head != tail) {
            NodeList<T> *tmp = head;
            head = head->getNext();
            head->setPrevious();
            if(b)
                delete tmp;
        }
        else {
            NodeList<T> *tmp = head;
            head = NULL;
            tail = NULL;
            if(b)
                delete tmp;
        }
    }
}

template<class T> void List<T>::dlteTail(bool b) {
    if(!this->isEmpty()) {
        if(head != tail) {
            NodeList<T> *tmp = tail;
            tail = tail->getPrevious();
            tail->setNext();
            if(b)
                delete tmp;
        }
        else {
            NodeList<T> *tmp = tail;
            head = NULL;
            tail = NULL;
            if(b)
                delete tmp;
        }
    }
}

template<class T> void List<T>::dlte(int n, bool b) {
    if(!this->isEmpty() && n < this->size() && n >= 0) {
        if(n == 0)
            this->dlteHead(b);
        else if(n == this->size()-1)
            this->dlteTail(b);
        else {
            NodeList<T> *tmp = this->take(n);
            tmp->getNext()->setPrevious(tmp->getPrevious());
            tmp->getPrevious()->setNext(tmp->getNext());
            if(b)
                delete tmp;
        }
    }
}

template<class T> void List<T>::clear(bool b) {
    while(head != NULL)
        this->dlteTail(b);
}

template<class T> NodeList<T> *List<T>::getHead(void) {
    return head;
}

template<class T> NodeList<T> *List<T>::getTail(void) {
    return tail;
}

template<class T> NodeList<T> *List<T>::take(int n) {
    if(!this->isEmpty() && n < this->size() && n >= 0) {
        if(n == 0)
            return head;
        if(n == this->size()-1)
            return tail;
        return this->rest()->take(n);
    }
    return NULL;
}

template<class T> List<T> *List<T>::rest(void) {
    List* tmp = new List(tail->getPrevious());
    return tmp;
}

template<class T> int List<T>::size(void) {
    if(this->isEmpty())
        return 0;
    else
        return 1+this->rest()->size();
}

template<class T> void List<T>::swapData(int a, int b) {
    T tmp = this->take(a)->getData();
    this->take(a)->setData(this->take(b)->getData());
    this->take(b)->setData(tmp);
}

template<class T> void List<T>::swapData(NodeList<T> *a, NodeList<T> *b) {
    T tmp = a->getData();
    a->setData(b->getData());
    b->setData(tmp);
}

template<class T> int List<T>::position(T d) {
    if(!this->isEmpty()) {
        int counter = 0;
        NodeList<T> *tmp = head;
        while(tmp->getData() != d) {
            tmp = tmp->getNext();
            counter++;
        }
        return counter;
    }
}

template<class T> List<T> *List<T>::listWithoutRepeat(void) {
    if(!this->isEmpty()) {
        NodeList<T> *tmp1 = head;
        NodeList<T> *tmp2;
        List<T> *list_without_repeat = new List<T>();
        list_without_repeat->add(tmp1->getData());
        while(tmp1 != NULL) {
            tmp2 = list_without_repeat->getHead();
            bool flag = false;
            while(tmp2 != NULL && flag == false) {
                if(tmp1->getData() == tmp2->getData())
                    flag = true;
                tmp2 = tmp2->getNext();
            }
            if(flag != true)
                list_without_repeat->add(tmp1->getData());
            tmp1 = tmp1->getNext();
        }
        return list_without_repeat;
    }
    return NULL;
}

template<class T> void List<T>::show() {
    if(!this->isEmpty()) {
        NodeList<T> *tmp = head;
        do {
            cout<<endl<<tmp->getData();
            tmp = tmp->getNext();
        } while(tmp != NULL);
    }
    else
        cout<<"\nEMPTY LIST";
    cout<<endl;
}

template<class T> void List<T>::showDetailed(void) {
    if(!this->isEmpty()) {
        NodeList<T> *tmp = head;
        do {
            cout<<endl<<tmp->getData();
            if(tmp->getPrevious() != NULL)
                cout<<" - previous: "<<tmp->getPrevious()->getData();
            else
                cout<<" - previous: NULL";
            if(tmp->getNext() != NULL)
                cout<<" - next: "<<tmp->getNext()->getData();
            else
                cout<<" - next: NULL";
            tmp = tmp->getNext();
        } while(tmp != NULL);
        cout<<"\nhead: "<<head->getData();
        cout<<"\ntail: "<<tail->getData();
    }
    else {
        cout<<"\nEMPTY LIST";
        if(head != NULL)
            cout<<"\nhead: "<<head->getData();
        else
            cout<<"\nhead: NULL";
        if(tail != NULL)
            cout<<"\ntail: "<<tail->getData();
        else
            cout<<"\ntail: NULL";
    }
    cout<<endl;
}

template<class T> bool List<T>::isEmpty(void) {
    return head == NULL;
}


#endif