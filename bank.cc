#include "bank.h"

Bank::Bank( unsigned int numStudents ) : numStudents(numStudents) {
    studentBalances = new unsigned int [numStudents]{0};
}

Bank::~Bank() {
    delete [] studentBalances;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    studentBalances[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while (studentBalances[id] < amount){
        _Accept( deposit );
    }
    studentBalances[id] -= amount;
} 