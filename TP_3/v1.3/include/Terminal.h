#ifndef TERMINAL_H
#define TERMINAL_H

#include <bitset>
#include "List.h"
#include "Structs.h"

using namespace std;

class Terminal {
    private:
        bitset<8> terminal_IP;
        bitset<8> router_IP;
        List<DATA> *data_input;
        List<DATA> *data_output;
    public:
        Terminal(void);
        Terminal(bitset<8> t_IP);
        void setRouterIP(bitset<8> r_IP);
        void setDataOutput(List<DATA> *l);
        bool hasDataOutput(void);
        DATA sendData(void);
        void recieveData(DATA d);
        bitset<8> getTerminalIP(void);
        bitset<8> getRouterIP(void);
        List<DATA> *getDataInput(void);
        List<DATA> *getDataOutput(void);
        void showTerminalDataInput(void);
        void showTerminalDataOutput(void);
};

Terminal::Terminal(){
}

Terminal::Terminal(bitset<8> t_IP){
    terminal_IP = t_IP;
    data_output = new List<DATA>();
    data_input = new List<DATA>();
}

void Terminal::setRouterIP(bitset<8> r_IP) {
    router_IP = r_IP;
}

void Terminal::setDataOutput(List<DATA> *l) {
    data_output = l;
}

bool Terminal::hasDataOutput(void) {
    return !data_output->isEmpty();
}

DATA Terminal::sendData(void) {
    DATA tmp = data_output->getHead()->getData();
    data_output->dlteHead(true);
    return tmp;
}

void Terminal::recieveData(DATA d) {
    data_input->add(d);
}

bitset<8> Terminal::getTerminalIP(void) {
    return terminal_IP;
}

bitset<8> Terminal::getRouterIP(void) {
    return router_IP;
}

List<DATA> *Terminal::getDataInput(void) {
    return data_input;
}

List<DATA> *Terminal::getDataOutput(void) {
    return data_output;
}

void Terminal::showTerminalDataInput(void) {
    cout<<"terminal IP: "<<terminal_IP<<endl;
    if(!data_input->isEmpty()) {
        NodeList<DATA> *data = data_input->getHead();
        NodeList<bitset<16>> *node;
        while(data != NULL) {
            node = data->getData().data->getHead();
            cout<<"- ";
            while(node != NULL) {
                cout<<node->getData()<<" ";
                node = node->getNext();
            }
            cout<<endl;
            data = data->getNext();
        }
    }
    else
        cout<<"- EMPTY LIST"<<endl;
}

void Terminal::showTerminalDataOutput(void) {
    cout<<"terminal IP: "<<terminal_IP<<endl;
    if(!data_output->isEmpty()) {
        NodeList<DATA> *data = data_output->getHead();
        NodeList<bitset<16>> *node;
        while(data != NULL) {
            node = data->getData().data->getHead();
            cout<<"- ";
            while(node != NULL) {
                cout<<node->getData()<<" ";
                node = node->getNext();
            }
            cout<<endl;
            data = data->getNext();
        }
    }
    else
        cout<<"- EMPTY LIST"<<endl;
}

#endif
