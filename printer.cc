#include "printer.h"

#include <iostream>
#include <iomanip>

using namespace std;


// Constructor. Prints first two rows of output.
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : 
    numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
    // 9 types of objects, 3 given have multiple
    total = 6 + numStudents + numVendingMachines + numCouriers;
    buffer = new Info[total];

    // print starting message
    cout << "Parent\t";
    cout << "Gropoff\t";
    cout << "WATOff\t";
    cout << "Names\t";
    cout << "Truck\t";
    cout << "Plant\t";


    for (unsigned int i = 0; i < numStudents; i += 1) {
        cout << left << setw(8) << setfill(' ') << "Stud" + to_string(i);
    }

    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        cout << left << setw(8) << setfill(' ') << "Mach" + to_string(i);
    }

    for (unsigned int i = 0; i < numCouriers; i += 1) {
        cout << left << setw(8) << setfill(' ') << "Cour" + to_string(i);
    }

    cout << endl;

    for (unsigned int i = 0; i < total; i += 1) {
        cout << "******* ";
    }

    cout << endl;
}

Printer::~Printer(){
    flush();
    cout << "***********************" << endl; 
    delete [] buffer;
}


void Printer::print( Kind kind, char state ) {
    int index = getIndex(kind);
    if (buffer[index].filled) { flush(); }
    buffer[index].msg = state;
    buffer[index].filled = true;
}


// Prints state and single value
// groupoff - Dg
void Printer::print( Kind kind, char state, unsigned int value1 ) {
    int index = getIndex(kind);
    if (buffer[index].filled) { flush(); }
    buffer[index].msg = state;
    buffer[index].msg += to_string(value1);
    buffer[index].filled = true;
}

// prints state and 2 values
void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    int index = getIndex(kind);
    if (buffer[index].filled) { flush(); }
    buffer[index].msg = state;
    buffer[index].msg += to_string(value1) + "," + to_string(value2);
    buffer[index].filled = true;
}


void Printer::print( Kind kind, unsigned int lid, char state ) {
    int index = getIndex(kind, lid);
    if (buffer[index].filled) { flush(); }
    buffer[index].msg = state;
    buffer[index].filled = true;
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    int index = getIndex(kind, lid);
    if (buffer[index].filled) { flush(); }
    buffer[index].msg = state;
    buffer[index].msg += to_string(value1);
    buffer[index].filled = true;
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    int index = getIndex(kind, lid);
    if (buffer[index].filled) { flush(); }
    buffer[index].msg = state;
    buffer[index].msg += to_string(value1) + "," + to_string(value2);
    buffer[index].filled = true;
}

int Printer::getIndex(Kind kind, unsigned int lid){
    switch (kind) {
        case Parent:
            return 0;
        case Groupoff:
            return 1;
        case WATCardOffice:
            return 2;
        case NameServer:
            return 3;
        case Truck:
            return 4;
        case BottlingPlant:
            return 5;
        case Student:
            return 6 + lid;
        case Vending:
            return 6 + numStudents + lid;
        case Courier:
            return 6 + numStudents + numVendingMachines + lid;
        default:
            return -1;      // invalid type
    }
}

void Printer::flush( ) {
    for (unsigned int i = 0; i < total; ++i){
        if (buffer[i].filled) {
            cout << left << setw(8) << setfill(' ') << buffer[i].msg;
            buffer[i].filled = false;
        } else {
            cout << left << setw(8) << setfill(' ') << " ";
        }
    }
    cout << endl;
}
