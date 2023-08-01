#ifndef NODELIST_H
#define NODELIST_H

using namespace std;

template<class T> class NodeList {
    private:
		T data;
		NodeList<T> *next;
		NodeList<T> *previous;
    public:
		NodeList(void);
		NodeList(T d);
		NodeList(T d, NodeList<T> *n, NodeList<T> *p);
		void setData(T d) {data = d;};
		void setNext(void) {next = NULL;};
		void setNext(NodeList<T> *n) {next = n;};
		void setPrevious(void) {previous = NULL;};
		void setPrevious(NodeList<T> *p) {previous = p;};
		T getData(void) {return data;};
		NodeList<T> *getNext(void) {return next;};
		NodeList<T> *getPrevious(void) {return previous;};
		bool hasNext(void) {return next != NULL;};
		bool hasPrevious(void) {return previous != NULL;};
};

template<class T> NodeList<T>::NodeList(void) {
    next = NULL;
    previous = NULL;
}

template<class T> NodeList<T>::NodeList(T d) {
    data = d;
    next = NULL;
    previous = NULL;
}

template<class T> NodeList<T>::NodeList(T d, NodeList<T> *n, NodeList<T> *p) {
    data = d;
    next = n;
    previous = p;
}

#endif