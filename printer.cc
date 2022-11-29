#include <iostream>
#include <string>

#include "printer.h"

using std::cout, std::endl, std::string, std::to_string;


// Constructor. Prints first two rows of output.
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
    // 9 types of objects, 3 given have multiple
    unsigned int total = 6 + numStudents + numVendingMachines + numCouriers;
    buffer = new string[total + 1]{""};

    cout << "Parent\t";

    cout << "Groupoff\t";

    cout << "WATOff\t";

    cout << "Names\t";

    cout << "Truck\t";

    cout << "Plant\t";


    for (unsigned int i = 0; i < numStudents; i += 1) {
        cout << "Stud";
        cout << i;
        cout << "\t";
    }

    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        cout << "Mach";
        cout << i;
        cout << "\t";
    }

    for (unsigned int i = 0; i < numCouriers; i += 1) {
        cout << "Cour";
        cout << i;
        if (i != numCouriers - 1) cout << "\t";
    }

    cout << endl;

    for (unsigned int i = 0; i <= total; i += 1) {
        cout << "*******";
        if (i != total) cout << "\t";
    }

    cout << endl;
}


void Printer::print( Kind kind, char state ) {
    string out = to_string(state);
    flush(kind, out);
}


// Prints state and single value
// groupoff - Dg
void Printer::print( Kind kind, char state, unsigned int value1 ) {
    string out = to_string(state) + to_string(value1);
    flush(kind, out);
}

// prints state and 2 values
void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    string out = to_string(state) + to_string(value1) + "," + to_string(value2);
    flush(kind, out);
}


void Printer::print( Kind kind, unsigned int lid, char state ) {
    string out = to_string(state) + lid;
    flush(kind, out, lid);
}

void print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    string out = to_string(state) + to_string(value1) + "," + to_string(value2);
    flush(kind, out, lid);
}

void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    string out = to_string(state) + to_string(value1) + "," + to_string(value2);
    flush(kind, out, lid);
}


void Printer::flush( Kind kind, string turn = "", unsigned int lid = 0 ) {
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
        cout << buffer[i];
        buffer[i] = (i == id) ? turn : "";
        if (i < right) cout << "\t";
        else break;
    }

    cout << endl;
}

Printer::~Printer() {
    flush(Kind::Student);
    cout << "*****************";
    cout << endl;

    delete [] buffer;
}