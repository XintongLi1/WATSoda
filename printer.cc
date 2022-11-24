#include <iostream>
#include <string>

#include "printer.h"

using std::cout, std::endl, std::string, std::to_string;

#ifdef NOOUTPUT
#define PRINT( stmt )
#else
#define PRINT( stmt ) cout << stmt
#endif // NOOUTPUT


string get_state(Voter::States state) {
    switch(state){
        case Voter::States::Start:
            return "S";
        case Voter::States::Vote:
            return "V";
        case Voter::States::Block:
            return "B";
        case Voter::States::Unblock:
            return "U";
        case Voter::States::Barging:
            return "b";
        case Voter::States::NextTourSize:
            return "N";
        case Voter::States::Done:
            return "D";
        case Voter::States::Complete:
            return "C";
        case Voter::States::Going:
            return "G";
        case Voter::States::Terminated:
            return "T";
        default:
            return "X";
    }
}


// Constructor. Prints first two rows of output.
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
    // 9 types of objects, 3 given have multiple
    int total = 6 + numStudents + numVendingMachines + numCouriers;
    buffer = new string[total + 1]{""};

    PRINT("Parent\t");

    PRINT("Groupoff\t");

    PRINT("WATOff\t");

    PRINT("Names\t");

    PRINT("Truck\t");

    PRINT("Plant\t");


    for (unsigned int i = 0; i < numStudents; i += 1) {
        PRINT("Stud");
        PRINT(i);
        PRINT("\t");
    }

    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        PRINT("Mach");
        PRINT(i);
        PRINT("\t");
    }

    for (unsigned int i = 0; i < numCouriers; i += 1) {
        PRINT("Cour");
        PRINT(i);
        if (i != numCouriers - 1) PRINT("\t");
    }

    PRINT(endl);

    for (unsigned int i = 0; i <= total; i += 1) {
        PRINT("*******");
        if (i != ) PRINT("\t");
    }

    PRINT(endl);
}

// Prints state
// parent - S F
// groupoff - S F
// WATCCard - S W F
// server - S F
// truck - S X F

void Printer::print( Kind kind, char state ) {
    string out = get_state(state);
    flush(kind, out);
}


// Prints state and single value
// groupoff - Dg
void Printer::print( Kind kind, char state, unsigned int value1 ) {
    string out = get_state(state) + to_string(value1);
    flush(kind, out);
}

// prints state and 2 values
void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    string out = get_state(state) + to_string(value1) + "," + to_string(value2);
    flush(kind, out);
}

// Not sure what lid means??
void Printer::print( Kind kind, unsigned int lid, char state ) {
    string out = get_state(state);
    flush(kind, out);
}


void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    string out = get_state(state) + to_string(value1);
    flush(kind, out);
}

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ) {
    string out = get_state(state) + to_string(value1) + "," + to_string(value2);
    flush(kind, out);
}

void Printer::flush(unsigned int id = 0, string turn = "") {
    unsigned int right = total;

    if (turn != "" && buffer[id] == "") {
        buffer[id] = turn;
        return;
    }

    for (int i = total; i >= 0; i -= 1) {
        if (buffer[i] != "") {
            right = i;
            break;
        }
    }

    for (unsigned int i = 0; i < right + 1; i += 1) {
        PRINT(buffer[i]);
        buffer[i] = (i == id) ? turn : "";
        if (i < right) PRINT("\t");
        else break;
    }

    PRINT(endl);
}

Printer::~Printer() {
    flush();
    PRINT("*****************");
    PRINT(endl);

    delete [] buffer;
}