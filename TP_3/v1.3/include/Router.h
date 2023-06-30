#ifndef ROUTER_H
#define ROUTER_H

#include "Structs.h"
#include "List.h"

using namespace std;

class Router {
    private:
        bitset<8> router_IP;
        List<Terminal *> *connected_terminals;
        List<Router *> *connected_routers;
        List<int> *bandwidths;
        List<PACKET> *packets_inputs;
        List<List<DATA> *> *datas_outputs_queues;
        List<List<PACKET> *> *packets_outputs_queues;
        List<PACKET> *parcial_datas;
    public:
        Router(void);
        Router(bitset<8> r_IP, List<Terminal *> *c_t, List<int> *b);
        bitset<8> extractFnlRouterIP(DATA d);
        bitset<8> extractFnlRouterIP(PACKET p);
        bitset<8> extractFnlTerminalIP(DATA d);
        bitset<8> extractFnlTerminalIP(PACKET p);
        bitset<8> extractInicialTerminalIP(DATA d);
        bitset<8> extractInicialTerminalIP(PACKET p);
        bitset<8> extractNextRouter(PACKET p);
        bitset<8> extractPartsTotal(PACKET p);
        bitset<8> extractPartPosition(PACKET p);
        bitset<16> extractPacketInfo(PACKET p);
        void setConnectedRouters(List<Router *> *l);
        bitset<8> getRouterIP(void);
        List<Terminal *> *getConnectedTerminals(void);
        List<Router *> *getConnectedRouters(void);
        List<PACKET> *getPacketsInputs(void);
        List<List<DATA> *> *getDatasOutputsQueues(void);
        List<List<PACKET> *> *getPacketsOutputsQueues(void);
        List<PACKET> *getParcialDatas(void);
        void sendToTerminalsRouterIP(void);
        List<PACKET> *convertDataToPackets(DATA d);
        void movePacketsToOutputsQueues(void);
        void sortPacketsQueues(void);
        void sendDatasToTerminals(void);
        void recieveDatasFromTerminals(void);
        void sendPacketsToRouters(void);
        void recievePacketsFromRouters(PACKET p);
        void checkBuildAndSortDatas(void);
        List<PACKET> *checkCompletedPacket(NodeList<PACKET> *n_p);
        List<PACKET> *sortPacketsList(List<PACKET> *l);
        void dlteFromParcialDatas(List<PACKET> *l, bool b);
        DATA buildData(List<PACKET> *l);
        void showConnectedTerminalsIP(void);
        void showConnectedRoutersIP(void);
        void showPacketsInputs(void);
        void showDatasOutputsQueues(void);
        void showPacketsOutputsQueues(void);
        void showParcialDatas(void);
};

Router::Router(void){
}

Router::Router(bitset<8> r_IP, List<Terminal *> *c_t, List<int> *b) {
    router_IP = r_IP;
    connected_terminals = c_t;
    connected_routers = new List<Router *>;
    bandwidths = b;
    packets_inputs = new List<PACKET>();
    datas_outputs_queues = new List<List<DATA> *>();
    packets_outputs_queues = new List<List<PACKET> *>();
    parcial_datas = new List<PACKET>();
    int terminals_count = c_t->size();
    for(int i = 0; i < terminals_count; i++)
    	datas_outputs_queues->add(new List<DATA>());
    this->sendToTerminalsRouterIP();
}

bitset<8> Router::extractFnlRouterIP(DATA d) {
    bitset<8> output;
    bitset<16> tmp = d.data->getHead()->getData();
    for(int i = 0; i < 8; i++)
        output[i] = tmp[i];
    return output;
}

bitset<8> Router::extractFnlRouterIP(PACKET p) {
    bitset<8> output;
    for(int i = 0; i < 8; i++)
        output[i] = p.packet[i];
    return output;
}

bitset<8> Router::extractFnlTerminalIP(DATA d) {
    bitset<8> output;
    bitset<16> tmp = d.data->getHead()->getData();
    for(int i = 0; i < 8; i++)
        output[i] = tmp[i+8];
    return output;
}

bitset<8> Router::extractFnlTerminalIP(PACKET p) {
    bitset<8> output;
    for(int i = 0; i < 8; i++)
        output[i] = p.packet[i+8];
    return output;
}

bitset<8> Router::extractInicialTerminalIP(DATA d) {
    bitset<8> output;
    bitset<16> tmp = d.data->take(1)->getData();
    for(int i = 0; i < 8; i++)
        output[i] = tmp[i];
    return output;
}

bitset<8> Router::extractInicialTerminalIP(PACKET p) {
    bitset<8> output;
    for(int i = 0; i < 8; i++)
        output[i] = p.packet[i+16];
    return output;
}

bitset<8> Router::extractNextRouter(PACKET p) {
    bitset<8> output;
    for(int i = 0; i < 8; i++)
        output[i] = p.packet[i+24];
    return output;
}

bitset<8> Router::extractPartsTotal(PACKET p) {
    bitset<8> output;
    for(int i = 0; i < 8; i++)
        output[i] = p.packet[i+32];
    return output;
}

bitset<8> Router::extractPartPosition(PACKET p) {
    bitset<8> output;
    for(int i = 0; i < 8; i++)
        output[i] = p.packet[i+40];
    return output;
}

bitset<16> Router::extractPacketInfo(PACKET p) {
    bitset<16> output;
    for(int i = 0; i < 16; i++)
        output[i] = p.packet[i+48];
    return output;
}

void Router::setConnectedRouters(List<Router *> *l) {
    connected_routers = l;
    int routers_count = l->size();
        for(int i = 0; i < routers_count; i++)
            packets_outputs_queues->add(new List<PACKET>());
}

bitset<8> Router::getRouterIP(void) {
    return router_IP;
}

List<Terminal *> *Router::getConnectedTerminals(void) {
    return connected_terminals;
}

List<Router *> *Router::getConnectedRouters(void) {
    return connected_routers;
}

List<PACKET> *Router::getPacketsInputs(void) {
    return packets_inputs;
}

List<List<DATA> *> *Router::getDatasOutputsQueues(void) {
    return datas_outputs_queues;
}

List<List<PACKET> *> *Router::getPacketsOutputsQueues(void) {
    return packets_outputs_queues;
}

List<PACKET> *Router::getParcialDatas(void) {
    return parcial_datas;
}

void Router::sendToTerminalsRouterIP(void) {
    NodeList<Terminal *> *terminal = connected_terminals->getHead();
    while(terminal != NULL) {
        terminal->getData()->setRouterIP(router_IP);
        terminal = terminal->getNext();
    }
}

List<PACKET> *Router::convertDataToPackets(DATA d) {
    List<PACKET> *output = new List<PACKET>();
    NodeList<bitset<16>> *node = d.data->take(2);
    bitset<8> fnl_router_IP = extractFnlRouterIP(d);
    bitset<8> fnl_terminal_IP = extractFnlTerminalIP(d);
    bitset<8> inicial_terminal_IP = extractInicialTerminalIP(d);
    bitset<8> parts_total = d.data->size()-2;
    bitset<8> part_position;
    bitset<16> packet_info;
    int counter = 0;
    while(node != NULL) {
        PACKET packet;
        part_position = counter;
        packet_info = node->getData();
        for(int i = 0; i < 8; i++) {
            packet.packet[i] = fnl_router_IP[i];
            packet.packet[i+8] = fnl_terminal_IP[i];
            packet.packet[i+16] = inicial_terminal_IP[i];
            packet.packet[i+24] = 0;
            packet.packet[i+32] = parts_total[i];
            packet.packet[i+40] = part_position[i];
        }
        for(int i = 0; i < 16; i++)
            packet.packet[i+48] = packet_info[i];
        output->add(packet);
        node = node->getNext();
        counter++;
    }
    return output;
}

void Router::movePacketsToOutputsQueues(void) {
    NodeList<PACKET> *packet = packets_inputs->getHead();
    bitset<8> next_router_IP;
    while(packet != NULL) {
        if(this->extractFnlRouterIP(packet->getData()) != router_IP) {
            next_router_IP = extractNextRouter(packet->getData());
            int counter = 0;
            NodeList<Router *> *router = connected_routers->getHead();
            while(router->getData()->getRouterIP() != next_router_IP) {
                router = router->getNext();
                counter++;
            }
            packets_outputs_queues->take(counter)->getData()->add(packet->getData());
        }
        else
            parcial_datas->add(packet->getData());
        packet = packet->getNext();
        packets_inputs->dlteHead(true);
    }
}

void Router::sortPacketsQueues(void) {
    NodeList<List<PACKET> *> *packets_queue = packets_outputs_queues->getHead();
    while(packets_queue != NULL) {
        if(!packets_queue->getData()->isEmpty()) {
            NodeList<PACKET> *packet = packets_queue->getData()->getHead();
            List<bitset<8>> *destinations_IP = new List<bitset<8>>();
            while(packet != NULL) {
                destinations_IP->add(this->extractFnlTerminalIP(packet->getData()));
                packet = packet->getNext();
            }
            destinations_IP = destinations_IP->listWithoutRepeat();
            packet = packets_queue->getData()->getHead();
            NodeList<bitset<8>> *search = destinations_IP->getHead();
            NodeList<PACKET> *browser;
            bool flag;
            while(packet != NULL && destinations_IP->size() > 0) {
                flag = true;
                browser = packet;
                while(browser != NULL && this->extractFnlTerminalIP(browser->getData()) != search->getData())
                    browser = browser->getNext();
                if(browser == NULL) {
                    NodeList<bitset<8>> *mark;
                    if(search->getNext() == NULL)
                        mark = destinations_IP->getHead();
                    else
                        mark = search->getNext();
                    destinations_IP->dlte(destinations_IP->position(search->getData()), true);
                    search = mark;
                    flag = false;
                }
                else if(browser != NULL && packet != browser)
                    packets_queue->getData()->swapData(packet, browser);
                if(flag) {
                    search = search->getNext();
                    if(search == NULL)
                        search = destinations_IP->getHead();
                }
                packet = packet->getNext();
            }
        }
        packets_queue = packets_queue->getNext();
    }
}

void Router::sendDatasToTerminals(void) {
    NodeList<Terminal *> *terminal = connected_terminals->getHead(); 
    NodeList<List<DATA> *> *datas_queue = datas_outputs_queues->getHead();
    while(terminal != NULL) {
        if(!datas_queue->getData()->isEmpty()) {
            terminal->getData()->recieveData(datas_queue->getData()->getHead()->getData());
            datas_queue->getData()->dlteHead(true);
        }
        terminal = terminal->getNext();
        datas_queue = datas_queue->getNext();
    }
}

void Router::recieveDatasFromTerminals(void) {
    NodeList<Terminal *> *terminal = connected_terminals->getHead();
    while(terminal != NULL) {
        if(terminal->getData()->hasDataOutput())
            packets_inputs->add(this->convertDataToPackets(terminal->getData()->sendData()));
        terminal = terminal->getNext();
    }
}

void Router::sendPacketsToRouters(void) {
    NodeList<int> *bandwidth = bandwidths->getHead();
    NodeList<Router *> *router = connected_routers->getHead();
    NodeList<List<PACKET> *> *packets_queue = packets_outputs_queues->getHead();
    NodeList<PACKET> *packet;
    while(router != NULL) {
        int counter = 0;
        packet = packets_queue->getData()->getHead();
        while(counter < bandwidth->getData() && packet != NULL) {
            router->getData()->recievePacketsFromRouters(packet->getData());
            packet = packet->getNext();
            packets_queue->getData()->dlteHead(true);
            counter++;
        }
        bandwidth = bandwidth->getNext();
        router = router->getNext();
        packets_queue = packets_queue->getNext();
    }
}

void Router::recievePacketsFromRouters(PACKET p) {
    packets_inputs->add(p);
}

void Router::checkBuildAndSortDatas(void) {
    DATA data;
    NodeList<Terminal *> *terminal;
    NodeList<PACKET> *packet = parcial_datas->getHead();
    NodeList<PACKET> *next_packet;
    List<PACKET> *completed_packets;
    bitset<8> fnl_terminal_IP;
    bitset<8> inicial_terminal_IP;
    bitset<8> parts_total;
    while(packet != NULL) {
        next_packet = packet;
        completed_packets = this->checkCompletedPacket(packet);
        if(completed_packets != NULL) {
            completed_packets = this->sortPacketsList(completed_packets);
            fnl_terminal_IP = this->extractFnlTerminalIP(packet->getData());
            inicial_terminal_IP = this->extractInicialTerminalIP(packet->getData());
            parts_total = this->extractPartsTotal(packet->getData());
            do
                next_packet = next_packet->getNext();
            while(next_packet != NULL && fnl_terminal_IP == this->extractFnlTerminalIP(next_packet->getData()) && parts_total == this->extractPartsTotal(next_packet->getData()) && inicial_terminal_IP == this->extractInicialTerminalIP(next_packet->getData()));
            data = this->buildData(completed_packets);
            terminal = connected_terminals->getHead();
            while(terminal->getData()->getTerminalIP() != fnl_terminal_IP)
                terminal = terminal->getNext();
            datas_outputs_queues->take(connected_terminals->position(terminal->getData()))->getData()->add(data);
            this->dlteFromParcialDatas(completed_packets, true);
        }
        else
            next_packet = next_packet->getNext();
        packet = next_packet;
    }
}

List<PACKET> *Router::checkCompletedPacket(NodeList<PACKET> *n_p) {
    List<PACKET> *output = new List<PACKET>();
    NodeList<PACKET> *packet = parcial_datas->getHead();
    bitset<8> fnl_terminal_IP = this->extractFnlTerminalIP(n_p->getData());
    bitset<8> inicial_terminal_IP = this->extractInicialTerminalIP(n_p->getData());
    bitset<8> parts_total = this->extractPartsTotal(n_p->getData());
    while(packet != NULL) {
        if(this->extractFnlTerminalIP(packet->getData()) == fnl_terminal_IP && this->extractPartsTotal(packet->getData()) == parts_total && this->extractInicialTerminalIP(packet->getData()) == inicial_terminal_IP)
            output->add(packet->getData());
        packet = packet->getNext();
    }
    if(output->size() == parts_total.to_ulong())
        return output;
    return NULL;
}

List<PACKET> *Router::sortPacketsList(List<PACKET> *l) {
    NodeList<PACKET> *packet = l->getHead();
    NodeList<PACKET> *browser;
    bitset<8> part;
    int counter = 0;
    while(packet != NULL) {
        browser = packet;
        part = counter;
        while(browser != NULL && this->extractPartPosition(browser->getData()) != part)
            browser = browser->getNext();
        if(browser != NULL && packet != browser)
            l->swapData(packet, browser);
        counter++;
        packet = packet->getNext();
    }
    return l;
}

void Router::dlteFromParcialDatas(List<PACKET> *l, bool b) {
    NodeList<PACKET> *packet = l->getHead();
    NodeList<PACKET> *tmp;
    int position;
    while(packet != NULL) {
        position = 0;
        tmp = parcial_datas->getHead();
        while(packet->getData().packet != tmp->getData().packet) {
            tmp = tmp->getNext();
            position++;
        }
        parcial_datas->dlte(position, b);
        packet = packet->getNext();
    }
}

DATA Router::buildData(List<PACKET> *l) {
    DATA output;
    output.data = new List<bitset<16>>();
    NodeList<PACKET> *packet = l->getHead();
    bitset<8> fnl_router_IP = this->extractFnlRouterIP(packet->getData());
    bitset<8> fnl_terminal_IP = this->extractFnlTerminalIP(packet->getData());
    bitset<8> inicial_terminal_IP = this->extractInicialTerminalIP(packet->getData());
    bitset<16> tmp;
    for(int i = 0; i < 8; i++) {
        tmp[i] = fnl_router_IP[i];
        tmp[i+8] = fnl_terminal_IP[i];
    }
    output.data->add(tmp);
    for(int i = 0; i < 8; i++) {
        tmp[i] = inicial_terminal_IP[i];
        tmp[i+8] = 0;
    }
    output.data->add(tmp);
    while(packet != NULL) {
        output.data->add(this->extractPacketInfo(packet->getData()));
        packet = packet->getNext();
    }
    return output;
}

void Router::showConnectedTerminalsIP(void) {
    NodeList<Terminal *> *tmp = connected_terminals->getHead();
    if(tmp == NULL)
        cout<<" EMPTY";
    while(tmp != NULL) {
        cout<<" "<<tmp->getData()->getTerminalIP();
        tmp = tmp->getNext();
    }
}

void Router::showConnectedRoutersIP(void) {
    NodeList<Router *> *tmp = connected_routers->getHead();
    if(tmp == NULL)
        cout<<" EMPTY";
    while(tmp != NULL) {
        cout<<" "<<tmp->getData()->getRouterIP();
        tmp = tmp->getNext();
    }
}

void Router::showPacketsInputs(void) {
    NodeList<PACKET> *tmp = packets_inputs->getHead();
    if(tmp == NULL)
        cout<<"EMPTY"<<endl;
    while(tmp != NULL) {
        cout<<tmp->getData().packet<<endl;
        tmp = tmp->getNext();
    }
}

void Router::showDatasOutputsQueues(void) {
    NodeList<List<DATA> *> *queue = datas_outputs_queues->getHead();
    NodeList<Terminal *> *terminal = connected_terminals->getHead();
    NodeList<DATA> *data;
    if(queue == NULL)
        cout<<"\nno connected terminals";
    while(queue != NULL) {
        data = queue->getData()->getHead();
        cout<<"\n(terminal "<<terminal->getData()->getRouterIP()<<")";
        if(data == NULL)
            cout<<" EMPTY";
        while(data != NULL) {
            if(data != queue->getData()->getHead())
                cout<<"\n                   ";
            cout<<" "<<data->getData().data;
            data = data->getNext();
        }
        queue = queue->getNext();
        terminal = terminal->getNext();
    }
}

void Router::showPacketsOutputsQueues(void) {
    NodeList<List<PACKET> *> *queue = packets_outputs_queues->getHead();
    NodeList<Router *> *router = connected_routers->getHead();
    NodeList<PACKET> *packet;
    while(queue != NULL) {
        packet = queue->getData()->getHead();
        cout<<"\n(router "<<router->getData()->getRouterIP()<<")";
        if(packet == NULL)
            cout<<" EMPTY";
        while(packet != NULL) {
            if(packet != queue->getData()->getHead())
                cout<<"\n                 ";
            cout<<" "<<packet->getData().packet;
            packet = packet->getNext();
        }
        queue = queue->getNext();
        router = router->getNext();
    }
}

void Router::showParcialDatas(void) {
    NodeList<PACKET> *tmp = parcial_datas->getHead();
    if(tmp == NULL)
        cout<<"EMPTY"<<endl;
    while(tmp != NULL) {
        cout<<tmp->getData().packet<<endl;
        tmp = tmp->getNext();
    }
}

#endif
