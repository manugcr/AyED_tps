#ifndef STRUCTS_H
#define STRUCTS_H

using namespace std;

typedef struct {
    bitset<64> packet;
} PACKET;

typedef struct {
    List<bitset<16>> *data;
} DATA;

#endif