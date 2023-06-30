#include <bitset>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "include/NodeList.h"
#include "include/List.h"
#include "include/Structs.h"
#include "include/Terminal.h"
#include "include/Router.h"
#include "include/Administrator.h"
#include "include/Constants.h"

using namespace std;

int main(int argc, char *argv[]) {
    bitset<1> adjacency_routers_matrix[256][256];
    int bandwidth_connections_matrix[256][256];
    List<int> *terminals_list = new List<int>();
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            adjacency_routers_matrix[i][j] = 0;
    for(int i = 0; i < 256; i++)
        for(int j = 0; j < 256; j++)
            bandwidth_connections_matrix[i][j] = 0;
    string line = "";
    int counter = 0;
    ifstream txt_toRead("config/configuration.txt");
    while(line != "adjacency_router_matrix =")
        getline(txt_toRead, line);
    for(int i = 0; line != "END"; i++) {
        getline(txt_toRead, line);
        counter = 0;
        for(int j = 0; j < line.length(); j++) {
            if(line[j] == '1')
                adjacency_routers_matrix[i][counter].set();
            if(line[j] != ' ')
                counter++;
        }
    }
    while(line != "bandwidth_connections_matrix =")
        getline(txt_toRead, line);
    for(int i = 0; line != "END"; i++) {
        getline(txt_toRead, line);
        counter = 0;
        for(int j = 0; j < line.length(); j++) {
            if(line[j] != ' ') {
                bandwidth_connections_matrix[i][counter] = atoi(&line[j]);
                counter++;
            }
        }
    }
    char aux[3];
    while(line != "terminals_list =")
        getline(txt_toRead, line);
    getline(txt_toRead, line);
    while(line != "END") {
        for(int j = 0; j < 3; j++)
            aux[j] = line[j];
        terminals_list->add(atoi(aux));
        getline(txt_toRead, line);
    }
    txt_toRead.close();
    Administrator *administrator = new Administrator(adjacency_routers_matrix, bandwidth_connections_matrix, terminals_list);
    cout<<endl;
    administrator->showAdjacencyRoutersMatrix();
    cout<<endl;
    administrator->showBandwidthConnectionsMatrix();
    cout<<endl;
    administrator->showConnections();
    cout<<endl;
    administrator->showGeneratedDatas();
    cout<<endl;
    system("PAUSE");
    
    cout<<"\n================================================================"<<endl;
    int step = 0;
    while((!administrator->hasFinished() || step == 0) && step < MAX_STEPS) {
        cout<<"\nsimulation step: "<<step<<endl;
        administrator->simulationStep();
        step++;
        cout<<endl;
        system("PAUSE");
        cout<<"\n================================================================"<<endl;
    }
    cout<<endl;
    administrator->showReceivedDatas();
    cout<<"\n================================================================"<<endl;
    if(step < 500) {
        cout<<"\n-SIMULATION FINISHED SUCCESSFULLY-"<<endl;
        cout<<"\ntotal steps: "<<step<<endl;
        cout<<"\n================================================================"<<endl;
    }
    else {
        cout<<"\n-SIMULATION ABORTED-"<<endl;
        cout<<"\ntotal steps: "<<step<<endl;
        cout<<"\n================================================================"<<endl;
    }
    cout<<endl;
    system("PAUSE");
    cout<<endl;
    return EXIT_SUCCESS;
}