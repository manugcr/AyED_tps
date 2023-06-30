#ifndef ADMIN_H
#define ADMIN_H

#include "Structs.h"
#include "List.h"
#include "Constants.h"

using namespace std;

class Administrator {
    private:
        bitset<1> adjacency_routers_matrix[256][256];
        int bandwidth_connections_matrix[256][256];
        List<List<Terminal *> *> *routers_terminals_list;
        List<Router *> *routers_list;
        int routers_timeout_matrix[256][256];
    public:
        Administrator(void);
        Administrator(int b_c_m[256][256], List<int> *t_l);
		Administrator(bitset<1> a_r_m[256][256], int b_c_m[256][256], List<int> *t_l);
        List<Router *> *extractConnectedRouters(int n);
        List<int> *extractBandwidths(int n);
        void setTerminals(List<int> *l);
        void buildAdjacencyRoutersMatrix(void);
        void fillWithRandomDatas(void);
        List<DATA> *createRandomDatas(bitset<8> r_IP, bitset<8> t_IP);
        void createRouters(void);
        int routersCount(void);
        void setPathToPackets(void);
        PACKET setNextRouterToPacket(PACKET p, bitset<8> b);
        bitset<8> searchOptimalPath(Router *i_r, Router *f_r);
        int dijkstra(int g[][256], int i_p, int f_p, int r_c);
        void calculateTimeouts(void);
        void simulationStep(void);
        bool hasFinished(void);
        int dataOutputCount(void);
        int dataInputCount(void);
        void showAdjacencyRoutersMatrix(void);
        void showBandwidthConnectionsMatrix(void);
        void showTimeoutMatrix(void);
        void showConnections(void);
        void showGeneratedDatas(void);
        void showReceivedDatas(void);
        void showPacketsInputs(void);
        void showDatasOutputsQueues(void);
        void showPacketsOutputsQueues(void);
        void showParcialDatas(void);
};

Administrator::Administrator(void){
}

Administrator::Administrator(int b_c_m[256][256], List<int> *t_l) {
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            adjacency_routers_matrix[i][j] = 0;
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            bandwidth_connections_matrix[i][j] = b_c_m[i][j];
    this->buildAdjacencyRoutersMatrix();
    routers_terminals_list = new List<List<Terminal *> *>();
    for(int i = 0; i < 256; i++)
        routers_terminals_list->add(new List<Terminal *>());
    this->setTerminals(t_l);
    routers_list = new List<Router *>();
    this->createRouters();
    this->fillWithRandomDatas();
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            routers_timeout_matrix[i][j] = MAXIMUM;
};

Administrator::Administrator(bitset<1> a_r_m[256][256], int b_c_m[256][256], List<int> *t_l) {
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            adjacency_routers_matrix[i][j] = a_r_m[i][j];
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            bandwidth_connections_matrix[i][j] = b_c_m[i][j];
    routers_terminals_list = new List<List<Terminal *> *>();
    for(int i = 0; i < 256; i++)
        routers_terminals_list->add(new List<Terminal *>());
    this->setTerminals(t_l);
    routers_list = new List<Router *>();
    this->createRouters();
    this->fillWithRandomDatas();
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            routers_timeout_matrix[i][j] = MAXIMUM;
};

List<Router *> *Administrator::extractConnectedRouters(int n) {
    List<Router *> *output = new List<Router *>();
    int routers_count = this->routersCount();
    for(int i = 0; i < routers_count; i++)
        if(adjacency_routers_matrix[n][i] == 1 && n != i)
            output->add(routers_list->take(i)->getData());
    return output;
}

List<int> *Administrator::extractBandwidths(int n) {
    List<int> *output = new List<int>();
    int routers_count = this->routersCount();
    for(int i = 0; i < routers_count; i++)
        if(bandwidth_connections_matrix[n][i] != 0)
            output->add(bandwidth_connections_matrix[n][i]);
    return output;
}

void Administrator::setTerminals(List<int> *l) {
    int size = l->size();
    int counter = 0;
    int counter_IP = 0;
    bitset<8> t_IP;
    NodeList<int> *tmp = l->getHead();
    NodeList<List<Terminal *> *> *node_terminals_list = routers_terminals_list->getHead();
    while(tmp != NULL) {
        counter = tmp->getData();
        if(counter != 0)
            for(int i = 0; i < counter; i++) {
                node_terminals_list->getData()->add(new Terminal(t_IP = counter_IP));
                counter_IP++;
            }
        tmp = tmp->getNext();
        node_terminals_list = node_terminals_list->getNext();
    }
}

void Administrator::buildAdjacencyRoutersMatrix(void) {
    bool flag = false;
    int counter = 0;
    for(int i = 0; i < 256 && flag == false; i++) {
        flag = true;
        for(int j = 0; j < 256; j++) {
            if(bandwidth_connections_matrix[i][j] != 0) {
                adjacency_routers_matrix[i][j].set();
                flag = false;
            }
        }
        counter++;
    }
    for(int i = 0; i < counter-1; i++)
        adjacency_routers_matrix[i][i].set();
}

void Administrator::fillWithRandomDatas(void) {
    NodeList<List<Terminal *> *> *terminals_list = routers_terminals_list->getHead();
    NodeList<Terminal *> *terminal;
    int routers_count = this->routersCount();
    srand(time(NULL));
    for(int i = 0; i < routers_count; i++) {
        terminal = terminals_list->getData()->getHead();
        while(terminal != NULL) {
            terminal->getData()->setDataOutput(this->createRandomDatas(terminal->getData()->getRouterIP(), terminal->getData()->getTerminalIP()));
            terminal = terminal->getNext();
        }
        terminals_list = terminals_list->getNext();
    }
}

List<DATA> *Administrator::createRandomDatas(bitset<8> r_IP, bitset<8> t_IP) {
    List<DATA> *output = new List<DATA>();
    int routers_list_size = routers_list->size();
    int amount_of_datas = rand()%MAX_AMOUNT_DATAS+1;
    int amount_of_nodes;
    Router *router;
    bitset<8> tmp_IP;
    bitset<16> node;
    DATA tmp_data;
    for(int j = 0; j < amount_of_datas; j++) {
        tmp_data.data = new List<bitset<16>>();
        do
            router = routers_list->take(rand()%routers_list_size)->getData();
        while(router->getRouterIP() == r_IP || router->getConnectedTerminals()->size() == 0);
        tmp_IP = router->getRouterIP();
        for(int i = 0; i < 8; i++)
            node[i] = tmp_IP[i];
        tmp_IP = router->getConnectedTerminals()->take(rand()%router->getConnectedTerminals()->size())->getData()->getTerminalIP();
        for(int i = 0; i < 8; i++)
            node[i+8] = tmp_IP[i];
        tmp_data.data->add(node);
        for(int i = 0; i < 8; i++)
            node[i] = t_IP[i];
        for(int i = 0; i < 8; i++)
            node[i+8] = 0;
        tmp_data.data->add(node);
        amount_of_nodes = rand()%MAX_AMOUNT_NODES+1;
        for(int i = 0; i < amount_of_nodes; i++)
            tmp_data.data->add(rand()%65536);
        output->add(tmp_data);
    }
    return output;
}

void Administrator::createRouters(void) {
    NodeList<List<Terminal *> *> *terminals_list = routers_terminals_list->getHead();
    int routers_count = this->routersCount();
    bitset<8> r_IP;
    for(int i = 0; i < routers_count; i++) {
        routers_list->add(new Router(r_IP = i, terminals_list->getData(), this->extractBandwidths(i)));
        terminals_list = terminals_list->getNext();
    }
    NodeList<Router *> *router = routers_list->getHead();
    NodeList<Router *> *aux_router;
    List<Router *> *connected_routers;
    for(int i = 0; router != NULL; i++) {
        connected_routers = new List<Router *>();
        aux_router = routers_list->getHead();
        for(int j = 0; aux_router != NULL; j++) {
            if(adjacency_routers_matrix[i][j] == 1 && i != j)
                connected_routers->add(aux_router->getData());
            aux_router = aux_router->getNext();
        }
        router->getData()->setConnectedRouters(connected_routers);
        router = router->getNext();
    }
}

int Administrator::routersCount(void) {
    int counter = 0;
    for(int i = 0; i < 256; i++)
        if(adjacency_routers_matrix[i][i] == 1)
            counter++;
    return counter;
}

void Administrator::setPathToPackets(void) {
    NodeList<Router *> *router = routers_list->getHead();
    NodeList<Router *> *fnl_router;
    NodeList<PACKET> *packet;
    bitset<8> fnl_router_IP;
    while(router != NULL) {
        packet = router->getData()->getPacketsInputs()->getHead();
        while(packet != NULL) {
            fnl_router_IP = router->getData()->extractFnlRouterIP(packet->getData());
            fnl_router = routers_list->getHead();
            while(fnl_router->getData()->getRouterIP() != fnl_router_IP)
                fnl_router = fnl_router->getNext();
            if(router->getData()->getRouterIP() != fnl_router_IP)
                packet->setData(this->setNextRouterToPacket(packet->getData(), this->searchOptimalPath(router->getData(), fnl_router->getData())));
            packet = packet->getNext();
        }
        router = router->getNext();
    }
}

PACKET Administrator::setNextRouterToPacket(PACKET p, bitset<8> b) {
    for(int i = 0; i < 8; i++)
        p.packet[i+24] = b[i];
    return p;
}

bitset<8> Administrator::searchOptimalPath(Router *i_r, Router *f_r) {
    int initial_point = routers_list->position(i_r);
    int fnl_point = routers_list->position(f_r);
    int path = this->dijkstra(routers_timeout_matrix, initial_point, fnl_point, this->routersCount());
    return routers_list->take(path)->getData()->getRouterIP();
}

int Administrator::dijkstra(int g[][256], int i_p, int f_p, int r_c) {
    int output;
    int previous_costs[r_c];
    int minimal_cost[r_c];
    int actual_point;
    int tmp_point;
    int min_distance;
    int nw_distance;
    bool visited[r_c];
    bool flag = true;
    for(int i = 0; i < r_c; i++) {
        visited[i] = false;
        minimal_cost[i] = MAXIMUM;
        previous_costs[i] = -1;
    }
    visited[i_p] = true;
    minimal_cost[i_p] = 0;
    actual_point = i_p;
    while(actual_point != f_p && flag == true) {
        flag = false;
        min_distance = MAXIMUM;
        for(int i = 0; i < r_c; i++)
            if(visited[i] == false) {
                nw_distance = minimal_cost[actual_point]+g[actual_point][i];
                if(nw_distance < minimal_cost[i]) {
                    minimal_cost[i] = nw_distance;
                    previous_costs[i] = actual_point;
                    flag = true;
                }
                if(minimal_cost[i] < min_distance) {
                    min_distance = minimal_cost[i];
                    tmp_point = i;
                    flag = true;
                }
            }
        actual_point = tmp_point;
        visited[actual_point] = true;
    }
    while(f_p != i_p) {
        output = f_p;
        f_p = previous_costs[f_p];
    }
    return output;
}

void Administrator::calculateTimeouts(void) {
    NodeList<Router *> *actual_router = routers_list->getHead();
    NodeList<Router *> *aux_router;
    NodeList<Router *> *aux_connected_router;
    NodeList<List<PACKET> *> *queue;
    int i = 0;
    int j;
    while(actual_router != NULL) {
        queue = actual_router->getData()->getPacketsOutputsQueues()->getHead();
        aux_connected_router = actual_router->getData()->getConnectedRouters()->getHead();
        while(queue != NULL) {
            aux_router = routers_list->getHead();
            j = 0;
            while(aux_router->getData() != aux_connected_router->getData()) {
                j++;
                aux_router = aux_router->getNext();
            }
            routers_timeout_matrix[i][j] = queue->getData()->size()/bandwidth_connections_matrix[i][j];
            queue = queue->getNext();
            aux_connected_router = aux_connected_router->getNext();
        }
        i++;
        actual_router = actual_router->getNext();
    }
}

void Administrator::simulationStep(void) {
    NodeList<Router *> *node_router = routers_list->getHead();
    Router *router;
    while(node_router != NULL) {
        router = node_router->getData();
        router->sendPacketsToRouters();
        router->sendDatasToTerminals();
        router->recieveDatasFromTerminals();
        router->checkBuildAndSortDatas();
        node_router = node_router->getNext();
    }
    this->calculateTimeouts();
    this->setPathToPackets();
    cout<<endl;
    this->showPacketsInputs();
    node_router = routers_list->getHead();
    while(node_router != NULL) {
        router = node_router->getData();
        router->movePacketsToOutputsQueues();
        router->sortPacketsQueues();
        node_router = node_router->getNext();
    }
    cout<<endl;
    this->showDatasOutputsQueues();
    cout<<endl;
    this->showPacketsOutputsQueues();
    cout<<endl;
    this->showTimeoutMatrix();
    cout<<endl;
    this->showParcialDatas();
}

bool Administrator::hasFinished(void) {
    bool flag = true;
    NodeList<Router *> *router = routers_list->getHead();
    NodeList<Terminal *> *terminal;
    NodeList<List<PACKET> *> *packets_queue;
    NodeList<List<DATA> *> *datas_queue;
    while(router != NULL && flag == true) {
        if(!router->getData()->getPacketsInputs()->isEmpty())
            flag = false;
        if(!router->getData()->getParcialDatas()->isEmpty())
            flag = false;
        packets_queue = router->getData()->getPacketsOutputsQueues()->getHead();
        while(packets_queue != NULL && flag == true) {
            if(!packets_queue->getData()->isEmpty())
                flag = false;
            packets_queue = packets_queue->getNext();
        }
        datas_queue = router->getData()->getDatasOutputsQueues()->getHead();
        while(datas_queue != NULL && flag == true) {
            if(!datas_queue->getData()->isEmpty())
                flag = false;
            datas_queue = datas_queue->getNext();
        }
        router = router->getNext();
    }
    return flag;
}

int Administrator::dataOutputCount(void) {
    int counter = 0;
    NodeList<List<Terminal *> *> *terminals_list = routers_terminals_list->getHead();
    NodeList<Terminal *> *terminal;
    while(terminals_list != NULL) {
        terminal = terminals_list->getData()->getHead();
        while(terminal != NULL) {
            counter += terminal->getData()->getDataOutput()->size();
            terminal = terminal->getNext();
        }
        terminals_list = terminals_list->getNext();
    }
    return counter;
}

int Administrator::dataInputCount(void) {
    int counter = 0;
    NodeList<List<Terminal *> *> *terminals_list = routers_terminals_list->getHead();
    NodeList<Terminal *> *terminal;
    while(terminals_list != NULL) {
        terminal = terminals_list->getData()->getHead();
        while(terminal != NULL) {
            counter += terminal->getData()->getDataInput()->size();
            terminal = terminal->getNext();
        }
        terminals_list = terminals_list->getNext();
    }
    return counter;
}

void Administrator::showAdjacencyRoutersMatrix(void) {
    cout<<"-ADJACENCY ROUTERS MATRIX-"<<endl<<endl;
    int aux = this->routersCount();
    if(aux != 0) {
        for(int i = 0; i < aux; i++) {
            cout<<"| ";
            for(int j = 0; j < aux; j++)
                printf("%1i ", adjacency_routers_matrix[i][j]);
            cout<<"|"<<endl;
        }
    }
    else
        cout<<"EMPTY"<<endl;
}

void Administrator::showBandwidthConnectionsMatrix(void) {
    cout<<"-BANDWIDTH CONNECTIONS MATRIX-"<<endl<<endl;
    int aux = this->routersCount();
    if(aux != 0) {
        for(int i = 0; i < aux; i++) {
            cout<<"| ";
            for(int j = 0; j < aux; j++)
                printf("%1i ", bandwidth_connections_matrix[i][j]);
            cout<<"|"<<endl;
        }
    }
    else
        cout<<"EMPTY"<<endl;
}

void Administrator::showTimeoutMatrix(void) {
    cout<<"-ROUTERS TIMEOUT MATRIX-"<<endl<<endl;
    int aux = this->routersCount();
    if(aux != 0) {
        for(int i = 0; i < aux; i++) {
            cout<<"| ";
            for(int j = 0; j < aux; j++)
                printf("%4i ", routers_timeout_matrix[i][j]);
            cout<<"|"<<endl;
        }
    }
    else
        cout<<"EMPTY"<<endl;
}

void Administrator::showConnections(void) {
    NodeList<Router *> *router = routers_list->getHead();
    cout<<"-CONNECTIONS-"<<endl;
    while(router != NULL) {
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP()<<endl;
        cout<<"connected terminals IP's:";
        router->getData()->showConnectedTerminalsIP();
        cout<<endl;
        cout<<"connected routers IP's:";
        router->getData()->showConnectedRoutersIP();
        router = router->getNext();
        cout<<endl;
    }
}

void Administrator::showGeneratedDatas(void) {
    NodeList<Router *> *router = routers_list->getHead();
    NodeList<Terminal *> *terminal;
    cout<<"-GENERATED DATAS-"<<endl;
    while(router != NULL) {
        terminal = router->getData()->getConnectedTerminals()->getHead();
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP()<<endl;
        if(terminal == NULL)
            cout<<"no connected terminals"<<endl;;
        while(terminal != NULL) {
            terminal->getData()->showTerminalDataOutput();
            terminal = terminal->getNext();
        }
        router = router->getNext();
    }
    cout<<"\ntotal generated datas: "<<this->dataOutputCount()<<endl;
}

void Administrator::showReceivedDatas(void) {
    NodeList<Router *> *router = routers_list->getHead();
    NodeList<Terminal *> *terminal;
    cout<<"-RECEIVED DATAS-"<<endl;
    while(router != NULL) {
        terminal = router->getData()->getConnectedTerminals()->getHead();
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP()<<endl;
        if(terminal == NULL)
            cout<<"no connected terminals"<<endl;;
        while(terminal != NULL) {
            terminal->getData()->showTerminalDataInput();
            terminal = terminal->getNext();
        }
        router = router->getNext();
    }
    cout<<"\ntotal received datas: "<<this->dataInputCount()<<endl;
}

void Administrator::showPacketsInputs(void) {
    NodeList<Router *> *router = routers_list->getHead();
    cout<<"-PACKETS INPUTS-"<<endl;
    while(router != NULL) {
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP()<<endl;
        router->getData()->showPacketsInputs();
        router = router->getNext();
    }
}

void Administrator::showDatasOutputsQueues(void) {
    NodeList<Router *> *router = routers_list->getHead();
    cout<<"-DATAS OUTPUTS QUEUES-"<<endl;
    while(router != NULL) {
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP();
        router->getData()->showDatasOutputsQueues();
        cout<<endl;
        router = router->getNext();
    }
}

void Administrator::showPacketsOutputsQueues() {
    NodeList<Router *> *router = routers_list->getHead();
    cout<<"-PACKETS OUTPUTS QUEUES-"<<endl;
    while(router != NULL) {
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP();
        router->getData()->showPacketsOutputsQueues();
        cout<<endl;
        router = router->getNext();
    }
}

void Administrator::showParcialDatas(void) {
    NodeList<Router *> *router = routers_list->getHead();
    cout<<"-PARCIAL DATAS-"<<endl;
    while(router != NULL) {
        cout<<"\nrouter IP: "<<router->getData()->getRouterIP()<<endl;
        router->getData()->showParcialDatas();
        router = router->getNext();
    }
}

#endif